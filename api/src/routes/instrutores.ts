import { Router } from 'express';
import { pool } from '../db';
import { Instrutor } from '../types/types';

const router = Router();

// GET - buscar todos os instrutores
router.get('/instrutores', async (_, res) => {
  try {
    const query = `
      SELECT * FROM instrutor;
    `;

    const resultado = await pool.query(query);

    return res.status(200).json(resultado.rows);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao buscar instrutores!' });
  }
});

// POST - cadastrar instrutor
router.post('/instrutores', async (req, res) => {
  const { nome, telefone, turno, especialidade } = req.body as Instrutor;

  try {
    const query = `
      INSERT INTO instrutor (nome, telefone, turno, especialidade)
      VALUES ($1, $2, $3, $4)
      RETURNING *;
    `;

    const valores = [nome, telefone, turno, especialidade];

    const resultado = await pool.query(query, valores);

    return res.status(201).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao cadastrar instrutor!' });
  }
});

// PUT - atualizar dados do instrutor
router.put('/instrutores/:id', async (req, res) => {
  const { id } = req.params;
  const { nome, telefone, turno, especialidade } = req.body as Instrutor;

  try {
    const query = `
      UPDATE instrutor  
      SET nome = COALESCE($2, nome),
          telefone = COALESCE($3, telefone),
          turno = COALESCE($4, turno),
          especialidade = COALESCE($5, especialidade)
      WHERE id_instrutor = $1
      RETURNING *;
    `;

    const valores = [id, nome, telefone, turno, especialidade];
    const resultado = await pool.query(query, valores);

    if (resultado.rows.length === 0) {
      return res.status(404).json({ erro: 'Instrutor não encontrado' });
    }

    return res.status(200).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao atualizar instrutor!' });
  }
});

// DELETE - deletar instrutor
router.delete('/instrutores/:id', async (req, res) => {
  const { id } = req.params;

  try {
    const query = `
      DELETE FROM instrutor WHERE id_instrutor = $1 RETURNING *;
    `;

    const resultado = await pool.query(query, [id]);

    if (resultado.rows.length === 0) {
      return res.status(404).json({ erro: 'Instrutor não encontrado' });
    }

    return res.status(200).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao deletar instrutor!' });
  }
});

export default router;
