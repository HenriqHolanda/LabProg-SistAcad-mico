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
Periodo *procurarPeriodo(Periodo *head, int codigo)
{
    while (head != NULL && head->codigo != codigo)
    {
        head = head->next;
    }
    return head;
}
// Função para imprimir a lista
void imprimirPeriodo(Periodo *head)
{
    while (head != NULL)
    {
        printf("%d ", head->codigo);
        head = head->next;
    }
    printf("\n");
}

// Função principal
int main()
{
    Periodo *head = NULL;

    inserirPeriodo(&head, 5);
    inserirPeriodo(&head, 3);
    inserirPeriodo(&head, 7);
    inserirPeriodo(&head, 4);

    printf("Lista original: ");
    imprimirPeriodo(head);

    printf("Buscando o elemento 7: ");
    Periodo *result = procurarPeriodo(head, 7);
    if (result != NULL)
    {
        printf("Encontrado!\n");
    }
    else
    {
        printf("Não encontrado!\n");
    }

    printf("Removendo o elemento 3...\n");
    removerPeriodo(&head, 3);
    printf("Lista após remoção: ");
    imprimirPeriodo(head);

    return 0;
}