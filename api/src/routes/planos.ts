import { Router } from 'express';
import { pool } from '../db';
import { Plano } from '../types/types';

const router = Router();

// GET - listar todos os planos
router.get('/planos', async (_, res) => {
  const query = `
    SELECT * FROM plano ORDER BY valor ASC;
  `;

  try {
    const result = await pool.query(query);

    return res.status(200).json(result.rows);
  } catch (error) {
    console.error(error);
    return res.status(500).json({ error: 'Erro ao buscar planos' });
  }
});

// POST - inserir plano
router.post('/planos', async (req, res) => {
  const { tipo, valor, validade, descricao } = req.body as Plano;

  try {
    const query = `
      INSERT INTO plano (tipo, valor, validade, descricao)
      VALUES ($1, $2, $3, $4)
      RETURNING *;
    `;

    const values = [tipo, valor, validade, descricao];

    const result = await pool.query(query, values);

    return res.status(201).json(result.rows[0]);
  } catch (error) {
    console.error(error);
    return res.status(500).json({ error: 'Erro ao criar plano' });
  }
});

// PUT - atualizar plano
router.put('/planos/:id', async (req, res) => {
  const { id } = req.params;
  const { tipo, valor, validade, descricao } = req.body as Plano;

  try {
    const checkQuery = `SELECT * FROM plano WHERE id_plano = $1`;
    const checkResult = await pool.query(checkQuery, [id]);

    if (checkResult.rows.length === 0) {
      return res.status(404).json({ error: 'Plano não encontrado' });
    }

    const query = `
      UPDATE plano
      SET tipo = COALESCE($2, tipo),
          valor = COALESCE($3, valor),
          validade = COALESCE($4, validade),
          descricao = COALESCE($5, descricao)
      WHERE id_plano = $1
      RETURNING *;
    `;

    const values = [id, tipo, valor, validade, descricao];

    const result = await pool.query(query, values);

    return res.status(200).json(result.rows[0]);
  } catch (error) {
    console.error(error);
    return res.status(500).json({ error: 'Erro ao atualizar plano' });
  }
});

// DELETE - remover plano
router.delete('/planos/:id', async (req, res) => {
  const { id } = req.params;

  try {
    const checkQuery = `SELECT * FROM plano WHERE id_plano = $1`;
    const checkResult = await pool.query(checkQuery, [id]);

    if (checkResult.rows.length === 0) {
      return res.status(404).json({ error: 'Plano não encontrado' });
    }

    const query = `
      DELETE FROM plano WHERE id_plano = $1 RETURNING *;
    `;

    const result = await pool.query(query, [id]);

    return res.status(200).json(result.rows[0]);
  } catch (error) {
    console.error(error);
    return res.status(500).json({ error: 'Erro ao deletar plano' });
  }
});

export default router;
