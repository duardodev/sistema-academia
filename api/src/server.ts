import express from 'express';
import alunosRotas from './routes/alunos';

const app = express();
app.use(express.json());

app.use('/api', alunosRotas);

app.listen(3000, () => {
  console.log('Servidor rodando na porta 3000!');
});
