import express from 'express';
import alunosRotas from './routes/alunos';
import planosRotas from './routes/planos';
import matriculasRotas from './routes/matriculas';
import instrutoresRotas from './routes/instrutores';
import equipamentosRotas from './routes/equipamentos';

const app = express();
app.use(express.json());

app.use('/api', alunosRotas);
app.use('/api', planosRotas);
app.use('/api', matriculasRotas);
app.use('/api', instrutoresRotas);
app.use('/api', equipamentosRotas);

app.listen(3000, () => {
  console.log('Servidor rodando na porta 3000!');
});
