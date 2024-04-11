#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Decidimos comentar o código linha a linha mais para entendermos melhor o que estamos fazendo do que por necessidade.

//Pensamos em jeitos diferentes no qual usariamos uma lista única de disciplinas(identificando período pelo código) ou uma única lista de alunos. 
//Porém vamos fazer do jeito que esta no slide(Uma lista de alunos e uma lista de disciplinas por período).

//primeiro vamos definir os tipos Periodo, aluno e disciplina.

//Typedef para colocar outro nome em struct aluno
typedef struct Aluno{
    int codigo; //int que recebe o código do aluno
    char nome[50]; //array de char para receber o nome
    char CPF[16];  //array de char para receber o CPF

    struct Aluno *next; //Ponteiro que vai apontar para o próximo Nó.

}Aluno;//tipo Aluno

typedef struct Disciplina{
    int codigo; //int que recebe o código da disciplina
    char nome[50]; //array de char para receber o nome da disciplina
    char professor[50]; //array de char para receber o nome do professor
    int creditos; //inteiro que recebe o número de créditos ta disciplina  
    
    struct Disciplina *next; //ponteiro que aponta para o próximo nó
    
}Disciplina; //tipo Disciplina

typedef struct Periodo{
    int ano; // inteiro que vai guardar o ano do período
    int semestre; //inteiro que vai guardar o semestre do período
    Aluno *alunos; //ponteiro do tipo Aluno (já criado) onde teremos a lista encadeada de alunos.
    Disciplina *disciplinas; //ponteiro do tipo Disciplina (já criado) onde teremos a lista encadeada de disciplinas
    struct Periodo *next;

}Periodo;//tipo Periodo

Periodo *periodos = NULL;

//Agora que definimos nossos 3 tipos e as informações de cada um deles, vamos escrever as funções para criar cada um deles.

//Esse p no final de cada parâmetro é só para diferenciar oque é paramêtro ao escrever a função.
Aluno* criarAluno(int codigop, const char* nomep, const char* CPFp){
    Aluno* novoAluno = (Aluno *)malloc(sizeof(Aluno));
    if(novoAluno == NULL){
        printf("Erro ao alocar memória para aluno");
        exit(1);
    }

    novoAluno->codigo = codigop;
    strcpy(novoAluno->nome, nomep);
    strcpy(novoAluno->CPF, CPFp);
    novoAluno->next = NULL;
    return novoAluno;

}

Disciplina* criarDisciplina(int codigop, const char* nomep, const char* professorp, int creditosp){
    Disciplina* novaDisciplina = (Disciplina *)malloc(sizeof(Aluno));
    if(novaDisciplina == NULL){
        printf("Erro ao alocar memória para aluno");
        exit(1);
    }

    novaDisciplina->codigo = codigop;
    strcpy(novaDisciplina->nome, nomep);
    strcpy(novaDisciplina->professor, professorp);
    novaDisciplina->creditos = creditosp;
    novaDisciplina->next = NULL;
    return novaDisciplina;

}

Periodo* criarPeriodo(int ano, int semestre) {

    Periodo *novoPeriodo = (Periodo *)malloc(sizeof(Periodo));
    if (novoPeriodo == NULL) {
        printf("Erro ao alocar memória para Periodo.\n");
        exit(1);
    }

    novoPeriodo->ano = ano;
    novoPeriodo->semestre = semestre;
    novoPeriodo->alunos = NULL;
    novoPeriodo->disciplinas = NULL;
    novoPeriodo->next = NULL;

    return novoPeriodo;
}

void adicionarAluno(Periodo *Periodo, Aluno *aluno) {
    aluno->next = Periodo->alunos;
    Periodo->alunos = aluno;
}

void adicionarPeriodo(Periodo *periodop){
    periodop->next = periodos;
    periodos = periodop;


}

void adicionarDisciplina(Periodo *periodo, Disciplina *disciplina) {
    disciplina->next = periodo->disciplinas;
    periodo->disciplinas = disciplina;
}

void imprimirAlunos(Periodo *periodop) {
    printf("Alunos do periodo %d.%d:\n", periodop->ano, periodop->semestre);
    Aluno *atual = periodop->alunos;
    while (atual != NULL) {
        printf("codigo: %d, Nome: %s, CPF: %s\n", atual->codigo, atual->nome, atual->CPF);
        atual = atual->next;
    }
}

void imprimirDisciplinas(Periodo *periodop) {
    printf("Disciplinas do periodo %d.%d:\n", periodop->ano, periodop->semestre);
    Disciplina *atual = periodop->disciplinas;
    while (atual != NULL) {
        printf("codigo: %d, Nome: %s, Professor: %s, Creditos: %d\n", atual->codigo, atual->nome, atual->professor, atual->creditos);
        atual = atual->next;
    }
}

void imprimirPeriodos(){
    printf("Periodos armazenados: \n");
    Periodo *current = periodos;
    if(current == NULL){
        printf("Nao existe período nenhum periodo armazenado\n");
    }
    while(current != NULL){
        printf("%d.%d \n", current->ano, current->semestre);
        current = current->next;
    }
    
}



int main(){
    FILE *logo = fopen("Logo.txt", "r");
    if (logo == NULL){
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    char linha[600];
    while(fgets(linha, sizeof(linha), logo) != NULL){
        printf("%s", linha);
    }

    fclose(logo);

    printf("\n");
    printf("\n");
    printf("\n");

    int close = 0;


    while(close == 0){       

        char choice1, choice2;
        
        printf("O que voce deseja fazer?\n");
        printf("1 - Listar os Periodos armazenados\n");
        printf("2 - Consultar dados de um Periodo\n");
        printf("3 - Adicionar um Periodo\n");
        printf("4 - Excluir um Periodo\n");
        printf("5 - fechar o programa\n");

        scanf(" %c", &choice1);

        if (choice2 < 49 || choice2 > 53){
            printf("Por favor responda com uma opção valida \n");
        }

        if(choice1 == '1'){
            printf("1");
            printf("\n");

            imprimirPeriodos();

            printf("O que você deseja fazer?\n");
            printf("1 - Voltar para o menu principal\n");
            printf("2 - Encerrar o programa");
            scanf(" %c", &choice2);
            
            if (choice2 < 49 || choice2 > 50){
                printf("Por favor responda com uma opção valida \n");
            }

            //Não preciso fazer nada para o programa continuar rodando

            if(choice2 == '2'){
                close = 1;
            }

        }

        if(choice1 == '2'){
            printf("2");
        }

        if(choice1 == '3'){
            printf("3");

        }

        if(choice1 == '4'){
            printf("4");
        }
    }

}