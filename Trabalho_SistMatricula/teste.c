#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um aluno
typedef struct Aluno {
    int codigo;
    char nome[50];
    char cpf[15];
    struct Aluno *prox;
} Aluno;

// Estrutura para representar uma disciplina
typedef struct Disciplina {
    int codigo;
    char nome[50];
    char professor[50];
    int creditos;
    struct Disciplina *prox;
} Disciplina;

// Estrutura para representar um período
typedef struct Periodo {
    int numero;
    Aluno *alunos;
    Disciplina *disciplinas;
    struct Periodo *prox;
} Periodo;

// Função para criar um novo aluno
Aluno* criarAluno(int codigo, const char* nome, const char* cpf) {
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    if (novoAluno == NULL) {
        printf("Erro ao alocar memória para aluno.\n");
        exit(1);
    }
    novoAluno->codigo = codigo;
    strcpy(novoAluno->nome, nome);
    strcpy(novoAluno->cpf, cpf);
    novoAluno->prox = NULL;
    return novoAluno;
}

// Função para criar uma nova disciplina
Disciplina* criarDisciplina(int codigo, const char* nome, const char* professor, int creditos) {
    Disciplina *novaDisciplina = (Disciplina *)malloc(sizeof(Disciplina));
    if (novaDisciplina == NULL) {
        printf("Erro ao alocar memória para disciplina.\n");
        exit(1);
    }
    novaDisciplina->codigo = codigo;
    strcpy(novaDisciplina->nome, nome);
    strcpy(novaDisciplina->professor, professor);
    novaDisciplina->creditos = creditos;
    novaDisciplina->prox = NULL;
    return novaDisciplina;
}

// Função para criar um novo período
Periodo* criarPeriodo(int numero) {
    Periodo *novoPeriodo = (Periodo *)malloc(sizeof(Periodo));
    if (novoPeriodo == NULL) {
        printf("Erro ao alocar memória para período.\n");
        exit(1);
    }
    novoPeriodo->numero = numero;
    novoPeriodo->alunos = NULL;
    novoPeriodo->disciplinas = NULL;
    novoPeriodo->prox = NULL;
    return novoPeriodo;
}

// Função para adicionar um aluno a um período
void adicionarAluno(Periodo *periodo, Aluno *aluno) {
    aluno->prox = periodo->alunos;
    periodo->alunos = aluno;
}

// Função para adicionar uma disciplina a um período
void adicionarDisciplina(Periodo *periodo, Disciplina *disciplina) {
    disciplina->prox = periodo->disciplinas;
    periodo->disciplinas = disciplina;
}

// Função para imprimir os alunos de um período
void imprimirAlunos(Periodo *periodo) {
    printf("Alunos do período %d:\n", periodo->numero);
    Aluno *atual = periodo->alunos;
    while (atual != NULL) {
        printf("Código: %d, Nome: %s, CPF: %s\n", atual->codigo, atual->nome, atual->cpf);
        atual = atual->prox;
    }
}

// Função para imprimir as disciplinas de um período
void imprimirDisciplinas(Periodo *periodo) {
    printf("Disciplinas do período %d:\n", periodo->numero);
    Disciplina *atual = periodo->disciplinas;
    while (atual != NULL) {
        printf("Código: %d, Nome: %s, Professor: %s, Créditos: %d\n", atual->codigo, atual->nome, atual->professor, atual->creditos);
        atual = atual->prox;
    }
}

int main() {
    // Criando alguns alunos e disciplinas
    Aluno *aluno1 = criarAluno(1, "Joao", "111.111.111-11");
    Aluno *aluno2 = criarAluno(2, "Maria", "222.222.222-22");
    Disciplina *disciplina1 = criarDisciplina(1, "Matematica", "Fulano", 4);
    Disciplina *disciplina2 = criarDisciplina(2, "Portugues", "Ciclano", 3);

    // Criando um período e adicionando alunos e disciplinas a ele
    Periodo *periodo1 = criarPeriodo(1);
    adicionarAluno(periodo1, aluno1);
    adicionarAluno(periodo1, aluno2);
    adicionarDisciplina(periodo1, disciplina1);
    adicionarDisciplina(periodo1, disciplina2);

    // Imprimindo os alunos e disciplinas do período
    imprimirAlunos(periodo1);
    imprimirDisciplinas(periodo1);

    // Liberando a memória alocada
    free(aluno1);
    free(aluno2);
    free(disciplina1);
    free(disciplina2);
    free(periodo1);

    return 0;
}
