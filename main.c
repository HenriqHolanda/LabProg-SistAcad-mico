#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

typedef struct Periodo
{
    int codigo;
    Aluno *alunos;
    Disciplina *disciplinas;
    struct Periodo *next;
    struct Periodo *previous;
} Periodo;

// Para ter a referencia do primeiro
Periodo *periodos = NULL;

// Funções de busca
Aluno *buscarAlunocodigo(Periodo *p, int codigo){
    Aluno *aux = p->alunos;
    Aluno *ant = NULL;
    while (aux->codigo != codigo && aux != NULL)
    {   
        ant = aux;
        aux = aux->next;
    }
    return aux;
}
Aluno *buscarAlunonome(Periodo *p, const char* nome)
{   
    Aluno *ant;
    Aluno *aux = p->alunos;
    while (aux->nome != nome && aux != NULL)
    {
        ant = aux; 
        aux = aux->next;
    }
    return aux;
}
Disciplina *buscarDisciplinacodigo(Periodo *p, int codigo)
{
    Disciplina *ant = NULL;
    Disciplina *aux = p->disciplinas;
    while (aux->codigo != codigo && aux != NULL)
    {
        ant = aux;
        aux = aux->next;
    }

    return aux;

}
Disciplina *buscarDisciplinanome(Periodo *p, const char* nome)
{   
    Disciplina *ant = NULL;
    Disciplina *aux = p->disciplinas;
    while (aux->nome != nome && aux != NULL)
    {
        ant = aux;
        aux = aux->next;
    }
    return aux;
}
Periodo *buscarPeriodo(int codigo)
{
    Periodo *aux = periodos;
    while (aux->codigo < codigo && aux != NULL)
    {
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
void novoAluno()
{
}
void removerAluno()
{
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
void removerDisciplina()
{
}

void criarPeriodo(int codigop)
{
    Periodo *novoPeriodo = (Periodo *)malloc(sizeof(Periodo));
    Periodo *aux = buscarPeriodo(codigop);
    if (aux == NULL || aux->codigo != codigop)
    {
        novoPeriodo->codigo = codigop;
        novoPeriodo->alunos = NULL;
        novoPeriodo->disciplinas = NULL;
        novoPeriodo->next = NULL;
        if (periodos == NULL)
            periodos = novoPeriodo;
        else
        {
            if (aux->previous == NULL)
            {
                aux->previous = novoPeriodo;
                novoPeriodo->next = aux;
                periodos = novoPeriodo;
            }
            else
            {
                aux->previous->next = novoPeriodo;
                aux->previous = novoPeriodo;
                novoPeriodo->previous = aux->previous;
                novoPeriodo->next = aux;
            }
        }
        printf("Período cadastrado com sucesso\n\n");
    }
    else
    {
        printf("Período já cadastrado\n\n");
        free(novoPeriodo);
    }
}
void removerPeriodo(float codigo)
{
    // vou ter que remover todos os alunos e disciplinas
    Periodo *aux = buscarPeriodo(codigo);
    if (aux == NULL)
    {
        printf("Período não encontrado");
    }
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
        printf("Codigo: %d Nome: %s \n",atual->codigo ,atual->nome);
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
        printf("Codigo: %d Nome: %s \n",atual->codigo ,atual->nome);
        atual = atual->next;
    }
    printf("\n");
}

void imprimirPeriodos()
{
    Periodo *current = periodos;
    if (current == NULL)
    {
        printf("\nAinda não há periodos armazenados\n\n");
    }
    while (current != NULL)
    {
        printf("Periodos armazenados: \n");
        printf("%.1f \n", current->codigo/10);
        current = current->next;
    }
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

void menuPeriodo(Periodo *p){
    int close = 0;
    while (close == 0)
    {   
        
        //variáveis para usar no switch;
        int c1, c2;
        float f1, f2;
        Disciplina d1;
        Aluno a1;
        char n1[50];
        char n2[50];

        printf("O que voce deseja fazer?\n");
        printf("1 - Listar Disciplinas\n");
        printf("2 - Listar Alunos\n");
        printf("3 - Consultar uma disciplina\n");
        printf("4 - Consultar um aluno\n");
        printf("5 - Adicionar uma Disciplina\n");
        printf("6 - Adicionar um aluno\n");
        printf("7 - Remover uma Disciplina\n");
        printf("8 - Remover um aluno\n");
        printf("9 - Voltar ao menu principal\n");

        int choice1;
        scanf("%d", &choice1);
        fflush(stdin);
        switch (choice1)
        {
        case 1:
            imprimirDisciplinas(p);
            break;
        case 2:
            imprimirAlunos(p);
            break;
        case 3:
            printf("Você deseja buscar pelo código ou nome da disciplina: \n");
            printf("1 - código\n");
            printf("2 - nome\n");
            scanf(" %d", &c1);
            if(c1 == 1){
                printf("Digite o código da disciplina: ");
                scanf(" %d", &c2);

                d1 = *buscarDisciplinacodigo(p, c2);
                printf("Codigo: %d, Nome:%s, Creditos: %d, Professor: %s, \n", d1.codigo, d1.nome, d1.creditos, d1.professor);
            }
            if(c1 == 2){
                printf("Digite o nome da disciplina: ");
                fgets(n1, sizeof(n1), stdin);

                d1 = *buscarDisciplinanome(p, n1);
                printf("Codigo: %d, Nome:%s, Creditos: %d, Professor: %s, \n", d1.codigo, d1.nome, d1.creditos, d1.professor);

            }

            if(c1 < 1 || c1 > 2){
                printf("Opção invalida");
            }
            break;
        case 4:
            printf("Você deseja buscar pelo codigo ou nome do Aluno: \n");
            printf("1 - codigo\n");
            printf("2 - nome\n");
            scanf(" %d", &c1);
            if(c1 == 1){
                printf("Digite o codigo do Aluno: ");
                scanf(" %d", &c2);

                a1 = *buscarAlunocodigo(p, c2);
                printf("Codigo: %d, Nome:%s, CPF: %s\n", a1.codigo, a1.nome, a1.CPF);
            }
            if(c1 == 2){
                printf("Digite o nome do Aluno: ");
                fgets(n1, sizeof(n1), stdin);

                a1 = *buscarAlunonome(p, n1);
                printf("Codigo: %d, Nome:%s, CPF: %s\n", a1.codigo, a1.nome, a1.CPF);

            }

            if(c1 < 1 || c1 > 2){
                printf("Opção invalida");
            }
            break;
        case 5:
            printf("Digite o codigo da nova disciplina: ");
            scanf(" %d", &c1);
            printf("Digite o nome da nova disciplina: ");
            fgets(n1, sizeof(n1), stdin);
            printf("Digite a quantidade de créditos da nova disciplina: ");
            scanf(" %d", &c2);
            printf("Digite o nome do professor da nova disciplina: ");
            fgets(n2, sizeof(n2), stdin);

            criarDisciplina(p, c1, n1, n2, n1);
            break;

        case 6:
            printf("Digite o codigo do novo Aluno: ");
            scanf(" %d", &c1);
            printf("Digite o nome da nova disciplina: ");
            fgets(n1, sizeof(n1), stdin);
            printf("Digite o CPF da nova disciplina: ");
            scanf(" %d", &c2);

            criarAluno(p, c1, n1, n2);
            break;

        case 7:
            printf("Você deseja remover pelo código ou nome da disciplina: \n");
            printf("1 - código\n");
            printf("2 - nome\n");
            if(c1 == 1){
                printf("Digite o código da disciplina: ");
                scanf(" %d", &c2);

                d1 = *buscarDisciplinacodigo(p, c2);
                
            }
            if(c1 == 2){
                printf("Digite o nome da disciplina: ");
                scanf(" %s", &n1);

                d1 = *buscarDisciplinanome(p, n1);
                
            }
            scanf(" %d", &c1);
            break;
        case 8:
            printf("Você deseja remover pelo código ou nome do Aluno: \n");
            printf("1 - código\n");
            printf("2 - nome\n");
            if(c1 == 1){
                printf("Digite o código da disciplina: ");
                scanf(" %d", &c2);

                a1 = *buscarAlunocodigo(p, c2);
                
            }
            if(c1 == 2){
                printf("Digite o nome da disciplina: ");
                scanf(" %s", &n1);

                a1 = *buscarAlunonome(p, n1);
                
            }
            scanf(" %d", &c1);
            break;
            break;
        case 9:
            close++;
            break;
        default:
            printf("\nOpção Inválida!\n");
            break;
        }
    }
}


void menuDois()
{
    imprimirPeriodos();
    float escolha;
    printf("Escreva o periodo no formato ano.semestre [Ex: 2018.1]\n");
    printf("Digite o periodo: ");
    scanf(" %f", &escolha);
    fflush(stdin);
    Periodo *p = buscarPeriodo((int)round(escolha*10));
    if (p == NULL)
        printf("O período digitado não consta nos arquivos");
    else
    {
        menuPeriodo(p);
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
    codigo = ano + 10 * semestre;
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
    Logo();
    menuPrincipal();

    printf("Ate mais!\n");
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