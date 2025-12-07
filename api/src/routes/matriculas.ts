import { Router } from 'express';
import { pool } from '../db';
import { Matricula } from '../types/types';

const router = Router();

// GET - buscar todas matrículas
router.get('/matriculas', async (_, res) => {
  const query = `
    SELECT
      m.*,
      a.nome as nome_aluno,
      p.tipo as tipo_plano,
      p.valor as valor_plano
    FROM matricula m
    JOIN aluno a ON m.id_aluno = a.id_aluno
    JOIN plano p ON m.id_plano = p.id_plano
    ORDER BY m.data_inicio DESC;
  `;

  try {
    const resultado = await pool.query(query);

    return res.status(200).json(resultado.rows);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao buscar matrículas!' });
  }
});

// POST - cadastrar nova matrícula
router.post('/matriculas', async (req, res) => {
  const { id_aluno, id_plano, status, dataInicio, dataTermino } = req.body as Matricula;

  if (!id_aluno || !id_plano) {
    return res.status(400).json({
      erro: 'Aluno e plano são obrigatórios',
    });
  }

  try {
    const query = `
      INSERT INTO matricula (id_aluno, id_plano, status, data_inicio, data_termino)
      VALUES ($1, $2, $3, COALESCE($4, CURRENT_DATE), $5)
      RETURNING *;
    `;

    const valores = [id_aluno, id_plano, status || 'ativa', dataInicio, dataTermino];

    const resultado = await pool.query(query, valores);

    return res.status(201).json({
      matricula: resultado.rows[0],
    });
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao criar matrícula' });
  }
});

// PUT - atualizar matrícula
router.put('/matriculas/:id', async (req, res) => {
  const { id } = req.params;
  const { id_plano, status, dataInicio, dataTermino } = req.body as Matricula;

  try {
    const query = `
      UPDATE matricula
      SET id_plano = COALESCE($2, id_plano),
          status = COALESCE($3, status),
          data_inicio = COALESCE($4, data_inicio),
          data_termino = COALESCE($5, data_termino)
      WHERE id_matricula = $1
      RETURNING *;
    `;

    const values = [id, id_plano, status, dataInicio, dataTermino];
    const resultado = await pool.query(query, values);

    if (resultado.rows.length === 0) {
      return res.status(404).json({ erro: 'Matrícula não encontrada' });
    }

    return res.status(200).json({
      matricula: resultado.rows[0],
    });
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao atualizar matrícula' });
  }
});

// DELETE - deletar matrícula
router.delete('/matriculas/:id', async (req, res) => {
  const { id } = req.params;

  try {
    const queryParaChecar = `SELECT * FROM matricula WHERE id_matricula = $1`;
    const resultadoDaChecagem = await pool.query(queryParaChecar, [id]);

    if (resultadoDaChecagem.rows.length === 0) {
      return res.status(404).json({ erro: 'Matrícula não encontrada' });
    }

    const query = `
      DELETE FROM matricula WHERE id_matricula = $1 RETURNING *;
    `;

    const resultado = await pool.query(query, [id]);

    return res.status(200).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao deletar matrícula' });
  }
});

export default router;
