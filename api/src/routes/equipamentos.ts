import { Router } from 'express';
import { pool } from '../db';
import { Equipamento } from '../types/types';

const router = Router();

// GET - buscar equipamentos
router.get('/equipamentos', async (_, res) => {
  try {
    const query = `
      SELECT * FROM equipamento;
    `;

    const resultado = await pool.query(query);

    return res.status(200).json(resultado.rows);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao buscar equipamentos!' });
  }
});

// POST - cadastrar equipamento
router.post('/equipamentos', async (req, res) => {
  const { nome, status, marca, tipo } = req.body as Equipamento;

  try {
    const query = `
      INSERT INTO equipamento (nome, status, marca, tipo)
      VALUES ($1, $2, $3, $4)
      RETURNING *;
    `;

    const valores = [nome, status, marca, tipo];
    const resultado = await pool.query(query, valores);

    return res.status(201).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao cadastrar equipamento!' });
  }
});

// PUT - atualizar dados do equipamento
router.put('/equipamentos/:id', async (req, res) => {
  const { id } = req.params;
  const { nome, status, marca, tipo } = req.body as Equipamento;

  try {
    const query = `
      UPDATE equipamento
      SET nome = COALESCE($2, nome),
          status = COALESCE($3, status),
          marca = COALESCE($4, marca),
          tipo = COALESCE($5, tipo)
      WHERE id_equipamento = $1
      RETURNING *;
    `;

    const valores = [id, nome, status, marca, tipo];
    const resultado = await pool.query(query, valores);

    if (resultado.rows.length === 0) {
      return res.status(404).json({ erro: 'Equipamento não encontrado!' });
    }

    return res.status(200).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao atualizar dados do equipamento!' });
  }
});

// DELETE - deletar equipamento
router.delete('/equipamentos/:id', async (req, res) => {
  const { id } = req.params;

  try {
    const query = `
      DELETE FROM equipamento WHERE id_equipamento = $1 RETURNING *;
    `;

    const resultado = await pool.query(query, [id]);

    if (resultado.rows.length === 0) {
      return res.status(404).json({ erro: 'Equipamento não encontrado!' });
    }

    return res.status(200).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao deletar equipamento!' });
  }
});

export default router;
