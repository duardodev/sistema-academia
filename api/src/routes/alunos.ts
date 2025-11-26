import { Router } from 'express';
import { Aluno } from '../types/types';
import { pool } from '../db';

const router = Router();

// GET - listar todos os alunos
router.get('/alunos', async (_, res) => {
  try {
    const query = `
      SELECT * FROM aluno;
    `;

    const resultado = await pool.query(query);

    return res.status(200).json(resultado.rows);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao buscar alunos' });
  }
});

// POST - inserir aluno
router.post('/alunos', async (req, res) => {
  const { cpf, nome, data_nascimento, sexo, telefone } = req.body as Aluno;

  try {
    const query = `
      INSERT INTO aluno (cpf, nome, data_nascimento, sexo, telefone)
      VALUES ($1, $2, $3, $4, $5)
      RETURNING *;
    `;

    const valores = [cpf, nome, data_nascimento, sexo, telefone];
    const resultado = await pool.query(query, valores);

    return res.status(201).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao inserir aluno' });
  }
});

// PUT - atualizar dados do aluno
router.put('/alunos/:id', async (req, res) => {
  const { id } = req.params;
  const { nome, data_nascimento, sexo, telefone } = req.body as Aluno;

  try {
    const query = `
      UPDATE aluno
      SET nome = $2,
          data_nascimento = $3,
          sexo = $4,
          telefone = $5
      WHERE id_aluno = $1
      RETURNING *;
    `;

    const valores = [id, nome, data_nascimento, sexo, telefone];
    const resultado = await pool.query(query, valores);

    if (resultado.rows.length === 0) {
      return res.status(404).json({ erro: 'Aluno não encontrado!' });
    }

    return res.status(200).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao atualizar aluno!' });
  }
});

// DELETE - remover aluno
router.delete('/alunos/:id', async (req, res) => {
  const { id } = req.params;

  try {
    const query = `
      DELETE FROM aluno WHERE id_aluno = $1 RETURNING *;
    `;

    const resultado = await pool.query(query, [id]);

    if (resultado.rows.length === 0) {
      return res.status(404).json({ erro: 'Aluno não encontrado' });
    }

    return res.status(200).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao deletar aluno!' });
  }
});

export default router;
