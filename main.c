#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Periodo *p;
// Função para adicionar um aluno a uma lista de alunos
void criarAluno(Periodo *periodo, int codigo, const char *nome, const char *CPF)
{
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    if (novoAluno == NULL)
    {
        printf("Erro ao alocar memória para novo aluno\n");
        exit(1);
    }
    novoAluno->codigo = codigo;
    strcpy(novoAluno->nome, nome);
    strcpy(novoAluno->CPF, CPF);
    novoAluno->next = periodo->alunos;
    periodo->alunos = novoAluno;
}

// Função para adicionar uma disciplina a um período
void criarDisciplina(Periodo *periodo, int codigo, const char *nome, const char *professor, int creditos)
{
    Disciplina *novaDisciplina = (Disciplina *)malloc(sizeof(Disciplina));
    if (novaDisciplina == NULL)
    {
        printf("Erro ao alocar memória para nova disciplina\n");
        exit(1);
    }
    novaDisciplina->codigo = codigo;
    strcpy(novaDisciplina->nome, nome);
    strcpy(novaDisciplina->professor, professor);
    novaDisciplina->creditos = creditos;
    novaDisciplina->next = periodo->disciplinas;
    periodo->disciplinas = novaDisciplina;
}

void removerAluno(Periodo *periodo, int codigo)
{
    Aluno *atual = periodo->alunos;
    Aluno *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            if (anterior == NULL)
            {
                periodo->alunos = atual->next;
            }
            else
            {
                anterior->next = atual->next;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
    printf("Aluno com o codigo %d nao encontrado no periodo %d\n", codigo, periodo->codigo);
}

// Função para remover uma disciplina de um período
void removerDisciplina(Periodo *periodo, int codigo)
{
    Disciplina *atual = periodo->disciplinas;
    Disciplina *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            if (anterior == NULL)
            {
                periodo->disciplinas = atual->next;
            }
            else
            {
                anterior->next = atual->next;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
    printf("Disciplina com o codigo %d nao encontrada no periodo %d\n", codigo, periodo->codigo);
}

// Função para buscar um aluno em um período
Aluno *buscarAlunoCodigo(Periodo *periodo, int codigo)
{
    Aluno *alunoAtual = periodo->alunos;
    while (alunoAtual != NULL)
    {
        if (alunoAtual->codigo == codigo)
        {
            return alunoAtual;
        }
        alunoAtual = alunoAtual->next;
    }
    return NULL; // Se não encontrar, retorna NULL
}

// Função para buscar uma disciplina em um período
Disciplina *buscarDisciplinaCodigo(Periodo *periodo, int codigo)
{
    Disciplina *disciplinaAtual = periodo->disciplinas;
    while (disciplinaAtual != NULL)
    {
        if (disciplinaAtual->codigo == codigo)
        {
            return disciplinaAtual;
        }
        disciplinaAtual = disciplinaAtual->next;
    }
    return NULL; // Se não encontrar, retorna NULL
}

// Função para buscar um aluno usando o nome
Aluno *buscarAlunoNome(Periodo *periodo, const char *nome)
{
    Aluno *alunoAtual = periodo->alunos;
    while (alunoAtual != NULL)
    {
        if (!strcmp(alunoAtual->nome, nome))
        {
            return alunoAtual;
        }
        alunoAtual = alunoAtual->next;
    }
    return NULL; // Se não encontrar, retorna NULL
}

// Função para buscar uma disciplina usando o nome
Disciplina *buscarDisciplinaNome(Periodo *periodo, const char *nome)
{
    Disciplina *disciplinaAtual = periodo->disciplinas;
    while (disciplinaAtual != NULL)
    {
        if (!strcmp(disciplinaAtual->nome, nome))
        {
            return disciplinaAtual;
        }
        disciplinaAtual = disciplinaAtual->next;
    }
    return NULL; // Se não encontrar, retorna NULL
}

// Função para criar um novo período
Periodo *criarPeriodo(int codigo)
{
    Periodo *novoPeriodo = (Periodo *)malloc(sizeof(Periodo));
    if (novoPeriodo == NULL)
    {
        printf("Erro ao alocar memória para novo período\n");
        exit(1);
    }
    novoPeriodo->codigo = codigo;
    novoPeriodo->alunos = NULL;      // Inicializa a lista de alunos como vazia
    novoPeriodo->disciplinas = NULL; // Inicializa a lista de disciplinas como vazia
    novoPeriodo->next = NULL;
    novoPeriodo->previous = NULL;
    return novoPeriodo;
}

// Função para inserir um novo nó na lista mantendo-a ordenada
void inserirPeriodo(Periodo **head, int codigo)
{
    Periodo *novoPeriodo = criarPeriodo(codigo);
    if (*head == NULL)
    {
        *head = novoPeriodo;
        return;
    }
    if (codigo < (*head)->codigo)
    {
        novoPeriodo->next = *head;
        (*head)->previous = novoPeriodo;
        *head = novoPeriodo;
        return;
    }
    Periodo *current = *head;
    while (current->next != NULL && current->next->codigo < codigo)
    {
        current = current->next;
    }
    novoPeriodo->next = current->next;
    if (current->next != NULL)
    {
        current->next->previous = novoPeriodo;
    }
    current->next = novoPeriodo;
    novoPeriodo->previous = current;
}

// Função para remover um nó da lista
void removerPeriodo(Periodo **head, int codigo)
{
    if (*head == NULL)
    {
        return;
    }
    Periodo *current = *head;
    while (current != NULL && current->codigo != codigo)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        return;
    }
    if (current->previous != NULL)
    {
        current->previous->next = current->next;
    }
    else
    {
        *head = current->next;
    }
    if (current->next != NULL)
    {
        current->next->previous = current->previous;
    }
    free(current);
}

// Função para buscar um elemento na lista
Periodo *buscarPeriodo(Periodo *head, int codigo)
{
    while (head != NULL && head->codigo != codigo)
    {
        head = head->next;
    }
    return head;
}

void imprimirAlunos(Periodo *periodo)
{
    printf("Alunos do periodo %d:\n", periodo->codigo);
    Aluno *alunoAtual = periodo->alunos;
    while (alunoAtual != NULL)
    {
        printf("Codigo: %d, Nome: %s, CPF: %s\n", alunoAtual->codigo, alunoAtual->nome, alunoAtual->CPF);
        alunoAtual = alunoAtual->next;
    }
}

// Função para buscar e imprimir todas as disciplinas de um período
void imprimirDisciplinas(Periodo *periodo)
{
    printf("Disciplinas do periodo %d:\n", periodo->codigo);
    Disciplina *disciplinaAtual = periodo->disciplinas;
    while (disciplinaAtual != NULL)
    {
        printf("Codigo: %d, Nome: %s, Professor: %s, Creditos: %d\n", disciplinaAtual->codigo, disciplinaAtual->nome, disciplinaAtual->professor, disciplinaAtual->creditos);
        disciplinaAtual = disciplinaAtual->next;
    }
}
// Função para imprimir a lista
void imprimirPeriodo(Periodo *head)
{
    while (head != NULL)
    {
        int ano = head->codigo / 10;
        int semestre = head->codigo - 10 * ano;
        printf("%d.%d\n", ano, semestre);
        head = head->next;
    }
    printf("\n");
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

void menuPeriodo(Periodo *p)
{
    int close = 0;
    while (close == 0)
    {

        // variáveis para usar no switch;
        int c1, c2;
        // float f1, f2;
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
            if (c1 == 1)
            {
                printf("Digite o código da disciplina: ");
                scanf(" %d", &c2);

                d1 = *buscarDisciplinaCodigo(p, c2);
                printf("Codigo: %d, Nome:%s, Creditos: %d, Professor: %s, \n", d1.codigo, d1.nome, d1.creditos, d1.professor);
            }
            if (c1 == 2)
            {
                printf("Digite o nome da disciplina: ");
                fgets(n1, sizeof(n1), stdin);

                d1 = *buscarDisciplinaNome(p, n1);
                printf("Codigo: %d, Nome:%s, Creditos: %d, Professor: %s, \n", d1.codigo, d1.nome, d1.creditos, d1.professor);
            }

            if (c1 < 1 || c1 > 2)
            {
                printf("Opção invalida");
            }
            break;
        case 4:
            printf("Você deseja buscar pelo codigo ou nome do Aluno: \n");
            printf("1 - codigo\n");
            printf("2 - nome\n");
            scanf(" %d", &c1);
            if (c1 == 1)
            {
                printf("Digite o codigo do Aluno: ");
                scanf(" %d", &c2);

                a1 = *buscarAlunoCodigo(p, c2);
                printf("Codigo: %d, Nome:%s, CPF: %s\n", a1.codigo, a1.nome, a1.CPF);
            }
            if (c1 == 2)
            {
                printf("Digite o nome do Aluno: ");
                fgets(n1, sizeof(n1), stdin);

                a1 = *buscarAlunoNome(p, n1);
                printf("Codigo: %d, Nome:%s, CPF: %s\n", a1.codigo, a1.nome, a1.CPF);
            }

            if (c1 < 1 || c1 > 2)
            {
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

            criarDisciplina(p, c1, n1, n2, c2);
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
            if (c1 == 1)
            {
                printf("Digite o código da disciplina: ");
                scanf(" %d", &c2);

                d1 = *buscarDisciplinaCodigo(p, c2);
            }
            if (c1 == 2)
            {
                printf("Digite o nome da disciplina: ");
                scanf(" %s", n1);

                d1 = *buscarDisciplinaNome(p, n1);
            }
            scanf(" %d", &c1);
            break;
        case 8:
            printf("Você deseja remover pelo código ou nome do Aluno: \n");
            printf("1 - código\n");
            printf("2 - nome\n");
            if (c1 == 1)
            {
                printf("Digite o código da disciplina: ");
                scanf(" %d", &c2);

                a1 = *buscarAlunoCodigo(p, c2);
            }
            if (c1 == 2)
            {
                printf("Digite o nome da disciplina: ");
                scanf(" %s", n1);

                a1 = *buscarAlunoNome(p, n1);
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
    imprimirPeriodo(p);
    float escolha;
    printf("Escreva o periodo no formato ano.semestre [Ex: 2018.1]\n");
    printf("Digite o periodo: ");
    scanf(" %f", &escolha);
    fflush(stdin);
    int esc = (int)(escolha * 10 + 0.5);
    Periodo *p = buscarPeriodo(p, esc);
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
    codigo = ano * 10 + semestre;
    inserirPeriodo(&p, codigo);
    printf("\n");
}
// Menu de Remoção de Período
void menuQuatro()
{
    int ano, semestre;
    float codigo;
    printf("Digite o ano [ex: 2024]: ");
    scanf("%d", &ano);
    fflush(stdin);
    printf("Digite o semestre [1 ou 2]: ");
    scanf("%d", &semestre);
    fflush(stdin);
    codigo = ano * 10 + semestre;
    removerPeriodo(&p, codigo);
    printf("\n");
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
            imprimirPeriodo(p);
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
