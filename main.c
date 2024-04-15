#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

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
typedef struct Rel
{
    int periodo;
    int codaluno;
    int coddisciplina;
    struct Rel *next;

} Rel;

// Primeiros nós
Periodo *p = NULL;
Rel *r = NULL;
// Função para adicionar um aluno a uma lista de alunos
void criarAluno(Periodo *periodo, int codigo, const char *nome, const char *CPF)
{
    Aluno *alunoAtual = periodo->alunos;
    while (alunoAtual != NULL)
    {
        if (alunoAtual->codigo == codigo)
        {
            printf("Codigo já cadastrado\n\n");
            return; // Retorna 1 se o código já existe
        }
        alunoAtual = alunoAtual->next;
    }
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
    Disciplina *disciplinaAtual = periodo->disciplinas;
    while (disciplinaAtual != NULL)
    {
        if (disciplinaAtual->codigo == codigo)
        {
            printf("Codigo já cadastrado\n\n");
            return; // Retorna 1 se o código já existe
        }
        disciplinaAtual = disciplinaAtual->next;
    }
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

// Função para remover um aluno de um período
void removerAlunoCodigo(Periodo *periodo, int codigo)
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
    printf("Aluno com o codigo %d nao encontrado\n", codigo);
}

// Função para remover uma disciplina de um período
void removerDisciplinaCodigo(Periodo *periodo, int codigo)
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
    printf("Disciplina com o codigo %d nao encontrada\n\n", codigo);
}

// Função para remover um aluno pelo nome
void removerAlunoNome(Periodo *periodo, const char *nome)
{
    Aluno *atual = periodo->alunos;
    Aluno *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
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
    printf("Aluno com o nome %s nao encontrado\n\n", nome);
}

// Função para remover uma disciplina pelo nome
void removerDisciplinaNome(Periodo *periodo, const char *nome)
{
    Disciplina *atual = periodo->disciplinas;
    Disciplina *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
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
    printf("Disciplina com o codigo %s nao encontrada\n\n", nome);
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

// Função para buscar e imprimir todas as disciplinas de um período
void imprimirAlunos(Periodo *periodo)
{
    int ano = periodo->codigo / 10;
    int semestre = periodo->codigo - 10 * ano;
    printf("Alunos do periodo %d.%d:\n", ano, semestre);
    Aluno *alunoAtual = periodo->alunos;
    while (alunoAtual != NULL)
    {
        printf("Codigo: %d, Nome: %s\n", alunoAtual->codigo, alunoAtual->nome);
        alunoAtual = alunoAtual->next;
    }
    printf("\n");
}

// Função para buscar e imprimir todas as disciplinas de um período
void imprimirDisciplinas(Periodo *periodo)
{
    int ano = periodo->codigo / 10;
    int semestre = periodo->codigo - 10 * ano;
    printf("Disciplinas do periodo %d.%d:\n", ano, semestre);
    Disciplina *disciplinaAtual = periodo->disciplinas;
    while (disciplinaAtual != NULL)
    {
        printf("Codigo: %d, Nome: %s\n", disciplinaAtual->codigo, disciplinaAtual->nome);
        disciplinaAtual = disciplinaAtual->next;
    }
    printf("\n");
}

// Função para imprimir a lista
void imprimirPeriodo(Periodo *head)
{
    int c = 0;

    while (head != NULL)
    {
        int ano = head->codigo / 10;
        int semestre = head->codigo - 10 * ano;
        printf("%d.%d\n", ano, semestre);
        head = head->next;
        c++;
    }

    if (c == 0)
    {
        printf("Nenhum periodo armazenado\n");
    }
    printf("\n");
}

// Função para salvar os dados em arquivo
void salvarPeriodos(Periodo *head, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Percorre a lista de períodos e escreve cada um no arquivo
    Periodo *periodoAtual = head;
    while (periodoAtual != NULL)
    {
        fprintf(arquivo, "%d\n", periodoAtual->codigo);

        // Salva os alunos do período
        Aluno *alunoAtual = periodoAtual->alunos;
        while (alunoAtual != NULL)
        {
            fprintf(arquivo, "ALUNO,%d,%s,%s,1\n", alunoAtual->codigo, alunoAtual->nome, alunoAtual->CPF);
            alunoAtual = alunoAtual->next;
        }

        // Salva as disciplinas do período
        Disciplina *disciplinaAtual = periodoAtual->disciplinas;
        while (disciplinaAtual != NULL)
        {
            fprintf(arquivo, "DISCIPLINA,%d,%s,%s,%d\n", disciplinaAtual->codigo, disciplinaAtual->nome, disciplinaAtual->professor, disciplinaAtual->creditos);
            disciplinaAtual = disciplinaAtual->next;
        }

        // Escreve uma linha em branco para separar os períodos
        fprintf(arquivo, "\n");

        periodoAtual = periodoAtual->next;
    }

    fclose(arquivo);
}
// Função para coletar os dados do arquivo
Periodo *lerPeriodos(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    Periodo *head = NULL;         // Cabeça da lista de períodos
    Periodo *periodoAtual = NULL; // Aponta para o período atual durante a leitura

    char linha[100]; // Buffer para armazenar cada linha lida do arquivo

    // Percorre o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        // Se a linha estiver em branco, passa para o próximo período
        if (strcmp(linha, "\n") == 0)
        {
            continue;
        }

        // Se a linha começa com um número, é o código de um novo período
        int codigo;
        if (sscanf(linha, "%d", &codigo) == 1)
        {
            // Cria um novo período e o adiciona à lista
            Periodo *novoPeriodo = criarPeriodo(codigo);
            if (head == NULL)
            {
                head = novoPeriodo;
            }
            else
            {
                periodoAtual->next = novoPeriodo;
            }
            periodoAtual = novoPeriodo;
        }
        else
        {
            // Caso contrário, é uma linha de aluno ou disciplina
            char tipo[20];
            int codigo;
            char nome[50];
            char naosei[50]; // cpf ou professor
            int creditos;

            sscanf(linha, "%[^,],%d,%[^,],%[^,],%d", tipo, &codigo, nome, naosei, &creditos);

            // Verifica se é uma linha de aluno ou disciplina
            if (strcmp(tipo, "ALUNO") == 0)
            {
                // Adiciona o aluno ao período atual
                criarAluno(periodoAtual, codigo, nome, naosei);
            }
            else if (strcmp(tipo, "DISCIPLINA") == 0)
            {
                // Adiciona a disciplina ao período atual
                criarDisciplina(periodoAtual, codigo, nome, naosei, creditos);
            }
        }
    }
    fclose(arquivo);
    return head;
}
Rel *Matricula(int periodop, int codalunop, int coddisciplinap)
{
    Rel *novaMatricula = (Rel *)malloc(sizeof(Rel));
    if (novaMatricula == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novaMatricula->periodo = periodop;
    novaMatricula->codaluno = codalunop;
    novaMatricula->coddisciplina = coddisciplinap;
    novaMatricula->next = NULL;
    return novaMatricula;
}

void inserirMatricula(Rel **head, int periodop, int codalunop, int coddisciplinap)
{
    Rel *novaMatricula = Matricula(periodop, codalunop, coddisciplinap);
    if (*head == NULL)
    {
        *head = novaMatricula;
    }
    else
    {
        Rel *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = novaMatricula;
    }
}

void salvarRel(Rel *r, const char *q)
{
    FILE *arquivo = fopen(q, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Percorre a lista de períodos e escreve cada um no arquivo
    Rel *rAtual = r;
    while (rAtual != NULL)
    {
        fprintf(arquivo, "%d,%d,%d\n", rAtual->periodo, rAtual->codaluno, rAtual->coddisciplina);
        // Escreve uma linha em branco para separar os períodos

        rAtual = rAtual->next;
    }

    fclose(arquivo);
}
Rel *lerRel(const char *q)
{
    FILE *arquivo = fopen(q, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }
    char linha[16];

    Rel *rel = NULL;
    Rel *relAtual = NULL;
    int periodo, aluno, disciplina;
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        sscanf(linha, "%d,%d,%d", &periodo, &aluno, &disciplina);
        Rel *novaRel = Matricula(periodo, aluno, disciplina);
        if (rel == NULL)
        {
            rel = novaRel;
        }
        else
        {
            relAtual->next = novaRel;
        }
        relAtual = novaRel;
    }

    fclose(arquivo);
    return rel;
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
        Rel *busca = r;

        printf("\nO que voce deseja fazer?\n");
        printf("1 - Listar Disciplinas\n");
        printf("2 - Listar Alunos\n");
        printf("3 - Consultar uma disciplina\n");
        printf("4 - Consultar um aluno\n");
        printf("5 - Adicionar uma Disciplina\n");
        printf("6 - Adicionar um aluno\n");
        printf("7 - Remover uma Disciplina\n");
        printf("8 - Remover um aluno\n");
        printf("9 - Matricular Aluno em Disciplina\n");
        printf("10 - Desmatricular Aluno em Disciplina\n");
        printf("11 - Voltar ao menu principal\n");

        int choice1;
        scanf("%d", &choice1);
        limparBuffer();
        switch (choice1)
        {
        case 1:
            printf("\n");
            imprimirDisciplinas(p);
            break;
        case 2:
            printf("\n");
            imprimirAlunos(p);
            break;
        case 3:
            printf("\n");
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
                printf("Alunos Matriculados: \n");
                while (busca != NULL)
                {
                    if (busca->periodo == p->codigo && busca->coddisciplina == d1.codigo)
                    {
                        a1 = *buscarAlunoCodigo(p, busca->codaluno);
                        printf("Codigo: %d, Nome: %s \n", a1.codigo, a1.nome);
                    }
                    busca = busca->next;
                }
                printf("\n");
            }
            if (c1 == 2)
            {
                printf("Digite o nome da disciplina: ");
                fgets(n1, sizeof(n1), stdin);

                d1 = *buscarDisciplinaNome(p, n1);
                printf("Codigo: %d, Nome:%s, Creditos: %d, Professor: %s, \n", d1.codigo, d1.nome, d1.creditos, d1.professor);
                printf("Alunos Matriculados: \n");
                while (busca != NULL)
                {
                    if (busca->periodo == p->codigo && busca->coddisciplina == d1.codigo)
                    {
                        a1 = *buscarAlunoCodigo(p, busca->codaluno);
                        printf("Codigo: %d, Nome: %s \n", a1.codigo, a1.nome);
                    }
                    busca = busca->next;
                }
                printf("\n");
            }

            if (c1 < 1 || c1 > 2)
            {
                printf("Opção invalida");
            }
            break;
        case 4:
            printf("\n");
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
                printf("Disciplinas do aluno: \n");
                while (busca != NULL)
                {
                    if (busca->periodo == p->codigo && busca->codaluno == a1.codigo)
                    {
                        d1 = *buscarDisciplinaCodigo(p, busca->coddisciplina);
                        printf("Código: %d, Nome da Disciplina: %s \n", d1.codigo, d1.nome);
                    }
                    busca = busca->next;
                }
                printf("\n");
            }
            if (c1 == 2)
            {
                printf("Digite o nome do Aluno: ");
                fgets(n1, sizeof(n1), stdin);

                a1 = *buscarAlunoNome(p, n1);
                printf("Codigo: %d, Nome:%s, CPF: %s\n", a1.codigo, a1.nome, a1.CPF);
                printf("Disciplinas do aluno: \n");
                while (busca != NULL)
                {
                    if (busca->periodo == p->codigo && busca->codaluno == a1.codigo)
                    {
                        d1 = *buscarDisciplinaCodigo(p, busca->coddisciplina);
                        printf("Código: %d, Nome da Disciplina: %s \n", d1.codigo, d1.nome);
                    }
                    busca = busca->next;
                }
            }

            if (c1 < 1 || c1 > 2)
            {
                printf("Opção invalida");
            }
            break;
        case 5:
            printf("\n");
            printf("Digite o codigo da nova disciplina: ");
            scanf(" %d", &c1);
            limparBuffer();
            printf("Digite o nome da nova disciplina: ");
            scanf("%99[^\n]", n1);
            limparBuffer();
            printf("Digite a quantidade de créditos da nova disciplina: ");
            scanf(" %d", &c2);
            limparBuffer();
            printf("Digite o nome do professor da nova disciplina: ");
            scanf("%99[^\n]", n2);
            limparBuffer();
            criarDisciplina(p, c1, n1, n2, c2);
            break;

        case 6:
            printf("\n");
            printf("Digite o codigo do novo Aluno: ");
            scanf(" %d", &c1);
            limparBuffer();
            printf("Digite o nome da novo Aluno: ");
            scanf("%99[^\n]", n1);
            limparBuffer();
            printf("Digite o CPF do novo Aluno: ");
            scanf(" %d", &c2);
            limparBuffer();
            criarAluno(p, c1, n1, n2);
            break;

        case 7:
            printf("\n");
            printf("Você deseja remover pelo código ou nome da disciplina: \n");
            printf("1 - código\n");
            printf("2 - nome\n");
            scanf("%d", &c1);
            limparBuffer();
            if (c1 == 1)
            {
                printf("Digite o código da disciplina: ");
                scanf(" %d", &c2);
                limparBuffer();
                removerDisciplinaCodigo(p, c2);
            }
            if (c1 == 2)
            {
                printf("Digite o nome da disciplina: ");
                scanf("%99[^\n]", n1);
                limparBuffer();
                removerDisciplinaNome(p, n1);
            }
            break;
        case 8:
            printf("\n");
            printf("Você deseja remover pelo código ou nome do Aluno: \n");
            printf("1 - código\n");
            printf("2 - nome\n");
            scanf("%d", &c1);
            limparBuffer();
            if (c1 == 1)
            {
                printf("Digite o código da disciplina: ");
                scanf(" %d", &c2);
                removerAlunoCodigo(p, c2);
            }
            if (c1 == 2)
            {
                printf("Digite o nome da disciplina: ");
                scanf("%99[^\n]", n1);
                limparBuffer();
                removerAlunoNome(p, n1);
            }
            break;
        case 9:
            printf("Digite o codigo do aluno que voce deseja matricular: ");
            scanf(" %d", &c1);
            limparBuffer();
            printf("Digite o codigo da disciplina que você deseja matricular: ");
            scanf(" %d", &c2);
            limparBuffer();

            inserirMatricula(&r, p->codigo, c1, c2);
            break;
        case 10:
            printf("Digite o codigo do aluno que voce deseja desmatricular: ");
            scanf(" %d", &c1);
            printf("Digite o codigo da disciplina que você deseja desmatricular: ");
            // scanf(" %d", &c2);
            break;
        case 11:
            close++;
            break;
        default:
            printf("\n");
            printf("\nOpção Inválida!\n");
            break;
        }
    }
}

void menuDois()
{
    imprimirPeriodo(p);

    int ano, semestre;
    int codigo;
    printf("Digite o ano [ex: 2024]: ");
    scanf("%d", &ano);
    limparBuffer();
    printf("Digite o semestre [1 ou 2]: ");
    scanf("%d", &semestre);
    limparBuffer();
    codigo = ano * 10 + semestre;
    Periodo *periodo = buscarPeriodo(p, codigo);
    if (periodo == NULL)
        printf("O período digitado nao consta nos arquivos");
    else
    {
        menuPeriodo(periodo);
    }
}

// Menu de Inserção de Período
void menuTres()
{
    int ano, semestre;
    int codigo;
    printf("Digite o ano [ex: 2024]: ");
    scanf("%d", &ano);
    limparBuffer();
    printf("Digite o semestre [1 ou 2]: ");
    scanf("%d", &semestre);
    limparBuffer();
    codigo = ano * 10 + semestre;
    inserirPeriodo(&p, codigo);
    printf("\n");
}
// Menu de Remoção de Período
void menuQuatro()
{
    int ano, semestre;
    int codigo;
    printf("Digite o ano [ex: 2024]: ");
    scanf("%d", &ano);
    limparBuffer();
    printf("Digite o semestre [1 ou 2]: ");
    scanf("%d", &semestre);
    limparBuffer();
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
        limparBuffer();
        switch (choice1)
        {
        case 1:
            printf("\n");
            imprimirPeriodo(p);
            break;
        case 2:
            printf("\n");
            menuDois();
            break;
        case 3:
            printf("\n");
            menuTres();
            break;
        case 4:
            printf("\n");
            menuQuatro();
            break;
        case 5:
            printf("\n");
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
    p = lerPeriodos("dado.txt");
    r = lerRel("rel.txt");
    Logo();
    menuPrincipal();
    salvarPeriodos(p, "dado.txt");
    salvarRel(r, "rel.txt");
    printf("Ate mais!\n");
    return 0;
}
