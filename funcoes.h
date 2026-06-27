#ifndef funcoes_h //basicamente isso eh padrao em .h, aqui estao as "assinaturas" das funcoes (evita bugs futuros e repeticao dos codigos)
#define funcoes_h

#define MAX_CHAR 150
#define MAX_TAREFAS 100
#define MAX_FUNCIONARIOS 100

struct dados {
    char atividade[MAX_TAREFAS][MAX_CHAR];
    char upperAtividade[MAX_TAREFAS][MAX_CHAR];
    int status[MAX_TAREFAS];
    int prioridade[MAX_TAREFAS];
    int contador;
};

struct usuario {
    int id;
    char senha[MAX_CHAR];
    char nome[MAX_CHAR];
};

void Transfor_Maius(char inter[]);
void RemoverEspacos(char frase[], char frase2[]);
int  VerificarEspacos(char frase[MAX_CHAR]);
int  checar_id(int ident, struct usuario y[], int total);
int  posicao_id(int ident, struct usuario y[], int total);
int  checar_sen(char sen[], struct usuario y[], int pos);
int  comparaDigitadaCadastradas(char buscar_ativ[], struct dados x[], struct usuario y[], int total, int *posAtv, int pos);

#endif