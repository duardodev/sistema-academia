export interface Aluno {
  id_aluno: number;
  cpf: string;
  nome: string;
  data_nascimento: string;
  telefone: string;
  sexo: 'Masculino' | 'Feminino';
}

export interface Plano {
  id_plano: number;
  tipo: 'Mensal' | 'Trimestral' | 'Semestral' | 'Anual';
  valor: number;
  validade: number;
  descricao?: string;
}

export interface Matricula {
  id_matricula: number;
  id_aluno: number;
  id_plano: number;
  status: 'Ativa' | 'Inativa' | 'Suspensa' | 'Cancelada';
  dataInicio: string;
  dataTermino?: string;
}

export interface Instrutor {
  id_instrutor: number;
  nome: string;
  especialidade?: string;
  turno: 'Manhã' | 'Tarde' | 'Noite' | 'Integral';
  telefone: string;
}

export interface Equipamento {
  id_equipamento: string;
  nome: string;
  tipo?: string;
  marca?: string;
  status: 'Disponível' | 'Manutenção' | 'Indisponível';
}
