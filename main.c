#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição das entidades principais
typedef struct Aluno
{
    int codigo;
    char nome[50];
    char CPF[16];
    struct Aluno *next;
} Aluno;

typedef struct Disciplina
{
    int codigo;
    char nome[50];
    char professor[50];
    int creditos;
    struct Disciplina *next;
} Disciplina;
// Lógica usada para implementar matricula
typedef struct Rel
{
    int codigo;
    int codDisc;
    int codAluno;
    float codPeriodo;
} Rel;
typedef struct Periodo
{
    float codigo;
    Aluno *alunos;
    Disciplina *disciplinas;
    struct Periodo *next;
    struct Periodo *previous;
} Periodo;
// Para ter a referencia do primeiro
Periodo *periodos = NULL;
Rel *rels = NULL;
// Funções de busca
Aluno *buscarAluno(Periodo *p, int codigo)
{
    Aluno *aux = p->alunos;
    while (aux->codigo != codigo && aux != NULL)
    {
        aux = aux->next;
    }
    return aux;
}
Disciplina *buscarDisciplina(Periodo *p, int codigo)
{
    Disciplina *aux = p->disciplinas;
    while (aux->codigo < codigo && aux != NULL)
    {
        aux = aux->next;
    }
    return aux;
}
Periodo *buscarPeriodo(float codigo)
{ // Retorna o ultimo elemento, o menor entre os maiores ou null
    Periodo *aux = periodos;

    while (aux != NULL && aux->codigo < codigo)
    {
        if (aux->next == NULL)
            break;
        aux = aux->next;
    }
    return aux;
}
// Funções auxiliares para criação de Entidades
void criarAluno(Periodo **p, int codigop, const char *nomep, const char *CPFp)
{
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    if (novoAluno == NULL)
    {
        printf("Erro ao alocar memória para aluno\n\n");
        exit(1);
    }
    novoAluno->codigo = codigop;
    strcpy(novoAluno->nome, nomep);
    strcpy(novoAluno->CPF, CPFp);
    Aluno *aux = (*p)->alunos;
    (*p)->alunos = novoAluno;
    novoAluno->next = aux;
    printf("Aluno cadastrado com sucesso\n\n");
}

void removerAluno(Periodo **p, int codigo)
{
    Aluno *aux = buscarAluno((*p), codigo);
    if (aux == NULL)
        printf("Aluno não encontrado\n\n");
    else
        free(aux);
}

void criarDisciplina(Periodo **p, int codigop, const char *nomep, const char *professorp, int creditosp)
{
    Disciplina *novaDisciplina = (Disciplina *)malloc(sizeof(Aluno));
    if (novaDisciplina == NULL)
    {
        printf("Erro ao alocar memória para aluno\n\n");
        exit(1);
    }
    novaDisciplina->codigo = codigop;
    strcpy(novaDisciplina->nome, nomep);
    strcpy(novaDisciplina->professor, professorp);
    novaDisciplina->creditos = creditosp;
    Disciplina *aux = (*p)->disciplinas;
    (*p)->disciplinas = novaDisciplina;
    novaDisciplina->next = aux;
    printf("Disciplina cadastrada com sucesso\n\n");
}
void novaDisciplina()
{
}
void removerDisciplina(Periodo **p, int codigo)
{
    Disciplina *aux = buscarDisciplina((*p), codigo);
    if (aux == NULL)
        printf("Disciplina não encontrada\n\n");
    else
        free(aux);
}

void criarPeriodo(float codigop)
{

    Periodo *novoPeriodo = (Periodo *)malloc(sizeof(Periodo));
    Periodo *aux = buscarPeriodo(codigop);
    if (aux == NULL || aux->codigo != codigop)
    {
        novoPeriodo->codigo = codigop;
        novoPeriodo->alunos = NULL;
        novoPeriodo->disciplinas = NULL;
        novoPeriodo->next = NULL;
        if (aux == NULL)
            periodos = novoPeriodo;
        else if (aux->previous == NULL)
        {
            aux->previous = novoPeriodo;
            novoPeriodo->next = aux;
            periodos = novoPeriodo;
        }
        else if (aux->next == NULL)
        {
            aux->next = novoPeriodo;
            novoPeriodo->previous = aux;
        }
        else
        {
            Periodo *previous = aux->previous;
            previous->next = novoPeriodo;
            previous = novoPeriodo;
            novoPeriodo->previous = previous;
            novoPeriodo->next = aux;
        }

        printf("Período cadastrado com sucesso\n\n");
    }
    else
    {
        printf("Período já cadastrado\n\n");
    }
}
void removerPeriodo(float codigo)
{
    // vou ter que remover todos os alunos e disciplinas
    Periodo *aux = buscarPeriodo(codigo);
    if (aux == NULL || aux->codigo != codigo)
        printf("Período não encontrado");
    else
        free(aux);
}
// Matricula de alunos
void matricularAluno()
{
}

// Funções de Output
void imprimirAlunos(Periodo *periodop)
{
    printf("Alunos do periodo %.1f:\n", periodop->codigo);
    Aluno *atual = periodop->alunos;
    while (atual != NULL)
    {
        printf("codigo: %d, Nome: %s, CPF: %s\n", atual->codigo, atual->nome, atual->CPF);
        atual = atual->next;
    }
    printf("\n");
}

void imprimirDisciplinas(Periodo *periodop)
{
    printf("Disciplinas do periodo %.1f:\n", periodop->codigo);
    Disciplina *atual = periodop->disciplinas;
    while (atual != NULL)
    {
        printf("codigo: %d, Nome: %s, Professor: %s, Creditos: %d\n", atual->codigo, atual->nome, atual->professor, atual->creditos);
        atual = atual->next;
    }
    printf("\n");
}

int imprimirPeriodos()
{
    Periodo *current = periodos;
    if (current == NULL)
    {
        printf("\nAinda não há periodos armazenados\n\n");
        return 0;
    }
    printf("Periodos armazenados: \n");
    while (current != NULL)
    {
        printf("%.1f \n", current->codigo);
        current = current->next;
    }
    return 1;
}
// Logo do início
void Logo()
{
    FILE *logo = fopen("Logo.txt", "r");
    if (logo == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    char linha[600];
    while (fgets(linha, sizeof(linha), logo) != NULL)
    {
        printf("%s", linha);
    }
    fclose(logo);
    printf("\n");
    printf("\n");
    printf("\n");
}
// Menus para dividir operações
// menu de Acesso ao Período
void menuDois()
{
    int result = imprimirPeriodos();
    if (result)
        return;
    float escolha;
    printf("Digite o período: ");
    scanf("%f", &escolha);
    fflush(stdin);
    Periodo *p = buscarPeriodo(escolha);
    if (p == NULL)
        printf("O período digitado não consta na base");
    else
    {
    }
}
// Menu de Inserção de Período
void menuTres()
{
    int ano, semestre;
    float codigo;
    printf("Digite o ano [ex: 2024]: ");
    scanf("%d", &ano);
    fflush(stdin);
    printf("Digite o semestre [1 ou 2]: ");
    scanf("%d", &semestre);
    fflush(stdin);
    codigo = ano + 0.1 * semestre;
    criarPeriodo(codigo);
}
// Menu de Remoção de Período
void menuQuatro()
{
}
// Tela inicial do programa
void menuPrincipal()
{
    int close = 0;
    while (close == 0)
    {
        printf("O que voce deseja fazer?\n");
        printf("1 - Listar os Periodos\n");
        printf("2 - Acessar Período\n");
        printf("3 - Adicionar um Periodo\n");
        printf("4 - Excluir um Periodo\n");
        printf("5 - Fechar o programa\n");

        int choice1;
        scanf("%d", &choice1);
        fflush(stdin);
        switch (choice1)
        {
        case 1:
            imprimirPeriodos();
            break;
        case 2:
            menuDois();
            break;
        case 3:
            menuTres();
            break;
        case 4:
            menuQuatro();
            break;
        case 5:
            close++;
            break;
        default:
            printf("\nOpção Inválida!\n");
            break;
        }
    }
}

int main()
{
    // Logo();
    // menuPrincipal();

    // printf("Até mais!\n");
    criarPeriodo(2023.1);
    criarPeriodo(2022.1);
    imprimirPeriodos();
    criarPeriodo(2024.1);
    imprimirPeriodos();
    criarPeriodo(2022.2);
    imprimirPeriodos();
    criarPeriodo(2024.2);
    imprimirPeriodos();
    return 0;
}

// Aluno *carregarAlunos()
// {
// }
// Disciplina *carregarDisciplinas()
// {
// }
// void carregarDados()
// {
// }