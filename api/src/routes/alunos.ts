import { Router } from 'express';
import { Aluno } from '../types/alunos';
import { pool } from '../db';

const router = Router();

// GET - lista todos os alunos
router.get('/alunos', async (_, res) => {
  const query = `
    SELECT * FROM aluno;
  `;

  try {
    const resultado = await pool.query(query);

    return res.status(200).json(resultado.rows);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao buscar alunos' });
  }
});

// GET - Busca aluno por ID
router.get('/alunos/:id', async (req, res) => {
  const { id } = req.params;

  const query = `
    SELECT * FROM aluno WHERE id_aluno = $1;
  `;

  try {
    const result = await pool.query(query, [id]);

    if (result.rows.length === 0) {
      return res.status(404).json({ erro: 'Aluno não encontrado' });
    }

    return res.status(200).json(result.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao buscar aluno' });
  }
});

// POST - insere aluno
router.post('/alunos', async (req, res) => {
  const { cpf, nome, dataNascimento, sexo, telefone } = req.body as Aluno;

  try {
    const query = `
      INSERT INTO aluno (cpf, nome, data_nascimento, sexo, telefone)
      VALUES ($1, $2, $3, $4, $5)
      RETURNING *;
    `;

    const valores = [cpf, nome, dataNascimento, sexo, telefone];

    const resultado = await pool.query(query, valores);

    return res.status(201).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao inserir aluno' });
  }
});

// PUT - atualiza dados do aluno
router.put('/alunos/:id', async (req, res) => {
  const { id } = req.params;
  const { nome, dataNascimento, sexo, telefone } = req.body as Aluno;

  try {
    const queryParaChecagem = `SELECT * FROM ALUNO WHERE id_aluno = $1`;
    const resultadoDaChecagem = await pool.query(queryParaChecagem, [id]);

    if (resultadoDaChecagem.rows.length === 0) {
      return res.status(404).json({ erro: 'Aluno não encontrado!' });
    }

    const query = `
      UPDATE aluno
      SET nome = COALESCE($2, nome),
          data_nascimento = COALESCE($3, data_nascimento),
          sexo = COALESCE($4, sexo),
          telefone = COALESCE($5, telefone)
      WHERE id_aluno = $1
      RETURNING *;
    `;

    const valores = [id, nome, dataNascimento, sexo, telefone];

    const resultado = await pool.query(query, valores);

    return res.status(200).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao atualizar aluno!' });
  }
});

// DELETE - remove aluno
router.delete('/alunos/:id', async (req, res) => {
  const { id } = req.params;

  try {
    const queryParaChecagem = `SELECT * FROM aluno WHERE id_aluno = $1`;
    const resultadoDaChecagem = await pool.query(queryParaChecagem, [id]);

    if (resultadoDaChecagem.rows.length === 0) {
      return res.status(404).json({ erro: 'Aluno não encontrado' });
    }

    const query = `
      DELETE FROM aluno WHERE id_aluno = $1 RETURNING *;
    `;

    const resultado = await pool.query(query, [id]);

    return res.status(200).json(resultado.rows[0]);
  } catch (erro) {
    console.error(erro);
    return res.status(500).json({ erro: 'Erro ao deletar aluno!' });
  }
});

export default router;
