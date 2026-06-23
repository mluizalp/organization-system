#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    int classificacao;
};

void AtividadeColaborador (struct dados x[], struct usuario y[], int total) {
    printf("\n===============================");
    printf("\n   ATIVIDADES POR COLABORADOR  ");
    printf("\n===============================\n");
    
    int j; 
    for (j = 0; j < total; j++) {
        int aFazer = 0, emAndamento = 0, concluido = 0;
        int k = 0;
        for (k = 0; k < x[j].contador; k++) {
            if (x[j].status[k] == 1) {
                aFazer++;
            } else if (x[j].status[k] == 2) {
                emAndamento++;
            } else if (x[j].status[k] == 3) {
                concluido++;
            }
        }
        printf("- Colaborador: %s\nA fazer: %d\nEm andamento: %d\nConcluido: %d\nTotal: %d\n\n", y[j].nome, aFazer, emAndamento, concluido, x[j].contador);

    }
}

void MovimentarAtiv (struct dados x[], int pos) {
    int numero;
    printf("\n===============================");
    printf("\n   MOVIMENTACAO DE ATIVIDADES  ");
    printf("\n===============================\n");
                
    if(x[pos].contador>0){
        int j, res = 2;

        for(j=0; j<x[pos].contador; j++){ //imprime a lista de atividades e usuario escolhe numero
            if (x[pos].status[j] != 3) {
                printf("%d - ", j);
                puts(x[pos].atividade[j]);
            }
        }

        do {
            printf("\nDigite o numero da atividade que deseja movimentar: ");
            scanf("%d", &numero);

            if(numero < 0 || numero >= x[pos].contador) {
                printf("\nAtividade nao existe.\n");
                printf("\nDeseja tentar novamente?\n[1] Sim\n[2] Nao\n");
                scanf("%d", &res);
            } else {
                do{
                    res = 2;
                    printf("\nPara qual status deseja tranferi-la?\n");
                    printf("[2] A fazer -> Em andamento\n[3] Em andamento -> Concluido\n");
                    scanf("%d", &x[pos].status[numero]); //salva o status na posicao da atividade escolhida
                    if(x[pos].status[numero]<2 || x[pos].status[numero]>3){
                        printf("\nStatus invalido!");
                    } //testa se o usuario n digitou outro numero pro status
                }while(x[pos].status[numero]<2 || x[pos].status[numero]>3);

                printf("\nTransferencia concluida!\n");
            }
        } while (res == 1);
        
    }else{
        printf("\nNenhuma atividade cadastrada.\n");
    }

}

void Lista_colab(struct usuario y[], int total) {
    printf("\n===============================");
    printf("\n         COLABORADORES         ");
    printf("\n===============================");
    int j;
    printf("\n");
    for (j = 0; j < total; j++) {
        printf("\n%d - %s", j + 1, y[j].nome);
    }
}

void Transfor_Maius(char inter[]) {
    for (int k = 0; k < strlen(inter); k++) {
        inter[k] = toupper(inter[k]); //transforma em maiusculo para comparar
    }
}

void RemoverEspacos(char frase[], char frase2[]) {
    int a = 0, b = 0;
    for (a = 0; a < strlen(frase); a++) { //remove espacos extras
        if (frase[a] != ' ') {
            frase2[b] = frase[a];
            if (frase[a + 1] == ' ') {
                frase2[b + 1] = ' ';
                b++;
            }
            b++;
        }
    }
    frase2[b] = '\0';
    if (b > 0 && frase2[b - 1] == ' ') { //remove espacos extras
        frase2[b - 1] = '\0';
    }
    strcpy(frase, frase2);
}

int VerificarEspacos(char frase[MAX_CHAR]) { // evitar salvar oq tiver so espacos
    int Retorno = 1;
    int i;
    for (i = 0; i < strlen(frase); i++) {
        if (frase[i] != ' ' && frase[i] != '\n') {
            Retorno = 0; //frase valida
            break;
        }
    }
    return Retorno;
}

void limpar_tela() { // pesquisei pq elas eram diferentes p W e L, ai po, nada inclusivo ne
    #ifdef _WIN32 // basicamente, se for windows, _WIN32 existe
        system("cls"); // usa esse
    #else // se nao for Windows
        system("clear");
    #endif // fecha o bloco
}

void cadastro_usuario(struct usuario y[], int *total) {
    int flag = 1;
    if (*total >= MAX_FUNCIONARIOS) {
        printf("\nSistema lotado, por favor fale com a gerencia");
        return; // so retorna msm
    }
    int k = *total;
    y[k].id = 10100 + k;
    printf("\n===============================");
    printf("\n      CADASTRO DE USUARIO      ");
    printf("\n===============================");
    printf("\nID gerado (lembre-se dele para entrar): %d", y[k].id);

    do { // looping para nome valido
        printf("\nDigite seu nome: ");
        fgets(y[k].nome, MAX_CHAR, stdin);
        y[k].nome[strcspn(y[k].nome, "\n")] = '\0'; // evita problema
        flag = VerificarEspacos(y[k].nome);
        if (flag) {
            printf("\nNao eh permitido o cadastro de nomes vazios");
        }
    } while (flag);

    do { // looping para senha valida
        printf("\nSenha (digite sua senha): ");
        fgets(y[k].senha, MAX_CHAR, stdin);
        y[k].senha[strcspn(y[k].senha, "\n")] = '\0'; // evita problema
        flag = VerificarEspacos(y[k].senha);
        if (flag) {
            printf("\nDigite uma senha válida!");
        }
    } while (flag);

    (*total)++; // incrementar a quantidade de gente
    printf("\nCadastro realizado com sucesso! Bom trabalho!");
}

int checar_id(int ident, struct usuario y[], int total) {
    int j;
    for (j = 0; j < total; j++) {
        if (y[j].id == ident) {
            return 1;
        }
    }
    return 0;
}

int posicao_id(int ident, struct usuario y[], int total) {
    int j;
    for (j = 0; j < total; j++) {
        if (y[j].id == ident) {
            return j;
        }
    }
    return -1;
}

int checar_sen(char sen[], struct usuario y[], int pos) {
    if (strcmp(y[pos].senha, sen) == 0) {
        return 1;
    }
    return 0;
}

void listagemAtividades(int pos, struct dados x[]){
    printf("\n===============================");
    printf("\n    LISTAGEM DE ATIVIDADES     ");
    printf("\n===============================");
    int j;
    printf("\nA FAZER:");
    for (j = 0; j < x[pos].contador; j++) {
        if (x[pos].status[j] == 1) {
            printf("\n - %s", x[pos].atividade[j]);
        }
    }
    printf("\nEM ANDAMENTO:");
    for (j = 0; j < x[pos].contador; j++) {
        if (x[pos].status[j] == 2) {
            printf("\n - %s", x[pos].atividade[j]);
        }
    }
    printf("\nCONCLUIDO:");
    for (j = 0; j < x[pos].contador; j++) {
        if (x[pos].status[j] == 3) {
            printf("\n - %s", x[pos].atividade[j]);
        }
    }
    printf("\n");

}

void estatistica(struct dados x[], struct usuario y[], int total){
    
    int j, soma=0;
    int aFazer = 0, emAndamento = 0, concluido = 0, alta=0, media=0, baixa=0;
    for (j = 0; j < total; j++) {//percorre todos os colaboradores
        int k = 0;
        for (k = 0; k < x[j].contador; k++) {//percorre a atividade de cada colaborador
            if (x[j].status[k] == 1) {
                aFazer++;
                soma++;
            } else if (x[j].status[k] == 2) {
                emAndamento++;
                soma++;
            } else if (x[j].status[k] == 3) {
                concluido++;
                soma++;
            }

            if(x[j].prioridade[k]==1){
                alta++;
            }else if(x[j].prioridade[k]==2){
                media++;
            }else if(x[j].prioridade[k]==3){
                baixa++;
            }
        }
    }

    printf("========================");
    printf("\n      ESTATISTICAS      ");
    printf("\n========================\n\n");
    printf("Colaboradores: %d\n\n", total);
    printf("Atividades: %d\n", soma);
    printf("\nA fazer: %d\nEm andamento: %d\nConcluido: %d\n", aFazer, emAndamento, concluido);
    printf("\nAlta prioridade: %d", alta);
    printf("\nMedia prioridade: %d", media);
    printf("\nBaixa prioridade: %d\n\n", baixa);
}

void ranking(struct dados x[], struct usuario y[], int total){
    int classificacao[total];
    int posicao[total];
    int somaConcluido, i, j;
    for(i=0; i<total; i++){//percorre os colaboradores
        somaConcluido=0;
        for(j=0; j<x[j].contador; j++){
            if(x[i].status[j] == 3){
                somaConcluido++;//vai somar todas as atv concluidas de um colaborador
            }
        }
        classificacao[i]=somaConcluido;//armazena os totais soq fora de ordem
        posicao[i]=i;//tipo um id do colaborador soq ligado a posicao, tb ta fora de ordem
    }
    int aux, ajuda;
    for(i=0; i<total-1; i++){//coloca os totais em ordem 
        for(j=0; j<total-i-1; i++){
            if(classificacao[i]<classificacao[i+1]){
                aux=classificacao[i];
                ajuda=posicao[i];
                classificacao[i]=classificacao[i+1];
                posicao[i]=posicao[i+1];
                classificacao[i+1]=aux;
                posicao[i+1]=ajuda;
            }
        }
    }
    printf("=======================\n");
    printf("        RANKING        \n");
    printf("=======================\n\n");
    int pos;

    for(i=0; i<total; i++){
        pos=i;
        printf("%d lugar - %s - %d atividades concluidas\n", pos+1, y[posicao[i]].nome, x[posicao[i]].classificacao);
    }

}

int entrar_usuario(struct usuario y[], int total) {
    //Variaveis daqui
    int ident, flag = 1, pos = 0, ok = 1, nao_sei, flag2 = 0;
    char sen[MAX_CHAR];
    printf("\n===============================");
    printf("\n       ACESSO DE USUARIO       ");
    printf("\n===============================");
    do { // socorro tem muita verificacao
        printf("\nDigite seu id: ");
        scanf("%d", &ident);
        getchar();
        flag = checar_id(ident, y, total); // ve se existe ne
        if (flag) {
            pos = posicao_id(ident, y, total); // pega a posicao do id
            do {
                printf("\nSenha: ");
                fgets(sen, MAX_CHAR, stdin);
                sen[strcspn(sen, "\n")] = '\0'; // tirar o \n para nao ficar dando problema
                flag2 = checar_sen(sen, y, pos); // ve se existe E se eh a do id
                if (flag2) {
                    printf("\nAcesso liberado ao usuario: %s", y[pos].nome);
                } else {
                    printf("\nSenha incorreta. Tente novamente!");
                }
            } while (flag2 == 0);
            return pos;
        } else {
            do {
                printf("\nId nao existe. O que deseja?\n[1]Sair\n[2]Digitar novamente\n:");
                scanf("%d", &nao_sei);
                if (nao_sei == 1) {
                    return -1;
                } else if (nao_sei == 2) {
                    ok = 0;
                } else {
                    printf("\nEntrada invalida");
                }
            } while (nao_sei < 1 || nao_sei > 2);
        }
    } while (ok == 0);
    return -1;
}

int main() {
    //VARIAVEIS PARA TODOS==============================
    int flag = 1, opcao, i = 0, ok = 1, pos, res;
    char buscar_ativ[MAX_CHAR];
    int total = 0, f = 0, retornar = 0;
    //==================================================

    //Funcao ler arquivo - quando a gente entender a parte de arquivo

    struct dados x[MAX_FUNCIONARIOS];
    struct usuario y[MAX_FUNCIONARIOS];

    int j;
    for (j = 0; j < MAX_FUNCIONARIOS; j++) {
        x[j].contador = 0;
    } // tirar quando a gente ajeitar o arquivo (aq eh so para nao ficar com lixo de memoria por enquanto)

    do {
        flag = 1;
        f = 0;
        retornar = 0; // essas variaveis evitam repeticoes nos cases e auxiliam na volta

        printf("\n==============================");
        printf("\n         BEM VINDO!           ");
        printf("\n==============================");

        do { // tela inicial
            printf("\nO que deseja?");
            printf("\n[1]Cadastro\n[2]Entrar\n[3]Sair\n");
            scanf("%d", &res);
            getchar();
            if (res < 1 || res > 3) { // Validacao de resposta
                printf("\nResposta invalida! Tente novamente");
            }
            if (res == 1) { // se ele quiser se cadastrar
                cadastro_usuario(y, &total); // Chama a funcao de cadastro
                limpar_tela();
                do {
                    printf("\nDeseja entrar?\n[1]Sim\n[2]Nao\n: "); // otimizacao para permitir a entrada apos cadastro
                    scanf("%d", &f);
                    if (f < 1 || f > 2) { // Validacao
                        printf("\nResposta invalida! Tente novamente");
                    }
                } while (f < 1 || f > 2);
            }
            limpar_tela();
            if (res == 2 || f == 1) { // Chama a funcao de entrada
                pos = entrar_usuario(y, total);
                if (pos == -1) {
                    printf("\nSistema finalizado"); // caso ele opte por sair
                    return 0;
                } else {
                    i = x[pos].contador; // comecar de onde o usuario parou (tava dando conflito)
                    res = 3; // aqui eh para sair do while
                }
                limpar_tela();
            } else if (res == 3) {
                printf("\nSistema finalizado!!!");
                return 0;
            }
        } while (res != 3);

        ////////////////////// Menu inicial //////////////////////////////

        while (flag == 1) { //loop do menu
            printf("\n===============================");
            printf("\n             MENU              ");
            printf("\n===============================");
            printf("\n\n1 - Cadastrar nova atividade\n2 - Listagem das atividades\n3 - Movimentacao das atividades\n4 - Quantidade de atividades por colaborador\n5 - Busca de atividades\n6 - Listagem de colaboradores\n7 - Estatistica geral\n8 - Ranking de produtividade\n9 - Salvar e Encerrar\n10 - Voltar ao inicio\n");
            do {
                printf("\nDigite o numero da opcao desejada: ");
                scanf("%d", &opcao);
                scanf("%*c");
                if (opcao < 1 || opcao > 10) {
                    printf("\nOpcao invalida!");
                }
            } while (opcao < 1 || opcao > 10); //repete o scanf ate a opcao ser valida

            limpar_tela();

            switch (opcao) {
                case 1:
                    printf("\n===============================");
                    printf("\n     CADASTRO DE ATIVIDADE     ");
                    printf("\n===============================\n");
                    if (x[pos].contador >= MAX_TAREFAS) { // verificao de limite de tarefas
                        printf("\nLimite de tarefas atingido.\n");
                    } else {
                        int k;
                        do {
                            int apenasEspacos = 0, jaExiste = 0, igual;
                            do {
                                printf("\nNome da atividade(max 100 caracteres): ");
                                fgets(x[pos].atividade[i], MAX_CHAR, stdin); //salva do teclado
                                x[pos].atividade[i][strcspn(x[pos].atividade[i], "\n")] = '\0'; // tirar o \n
                                apenasEspacos = VerificarEspacos(x[pos].atividade[i]);
                                char copia[MAX_CHAR]; // variavel copia
                                strcpy(copia, x[pos].atividade[i]); // copiando
                                char inter[MAX_CHAR]; // variavel intermediaria
                                RemoverEspacos(copia, inter); // tirar espacos inuteis
                                Transfor_Maius(inter); // colocar em maiusculo
                                for (k = 0; k < x[pos].contador; k++) {
                                    igual = strcmp(inter, x[pos].upperAtividade[k]); // recebe 0 caso sejam iguais
                                    if (igual == 0) {
                                        printf("\nAtividade ja cadastrada anteriormente. Digite outra:\n");
                                        jaExiste = 1; // retorna 1 pra indicar q eh invalida
                                        break;
                                    } else {
                                        jaExiste = 0;
                                    }
                                }
                            } while (apenasEspacos == 1 || jaExiste == 1);

                            for (k = 0; k < strlen(x[pos].atividade[i]); k++) { //tranformar em maius p/ salvar no upper
                                x[pos].upperAtividade[i][k] = toupper(x[pos].atividade[i][k]);
                            }
                            char corrigida[MAX_CHAR];
                            RemoverEspacos(corrigida, x[pos].upperAtividade[i]);
                            x[pos].status[i] = 1; // status da ativ sempre comeca sendo [1] a fazer
                            printf("\nAtividade cadastrada com sucesso!\n");
                            do {
                                printf("\nQual a prioridade da atividade?\n[1]ALTA\n[2]MEDIA\n[3]BAIXA\n:");
                                scanf("%d", &x[pos].prioridade[i]);
                                if (x[pos].prioridade[i] < 1 || x[pos].prioridade[i] > 3) {
                                    printf("\nEntrada invalida! Tente novamente!");
                                }
                            } while (x[pos].prioridade[i] < 1 || x[pos].prioridade[i] > 3);
                            i++;
                            x[pos].contador++;
                            do {
                                printf("\nDeseja cadastrar outra atividade?\n1 - sim\n2- nao\n");
                                scanf("%d", &ok);
                                scanf("%*c"); //limpa o buffer
                                if (ok < 1 || ok > 2) {
                                    printf("\nOpcao invalida!");
                                }
                            } while (ok < 1 || ok > 2); //repete o scanf ate a opcao ser valida
                        } while (ok == 1);
                    }
                    break;

                case 2:
                    limpar_tela();
                    listagemAtividades(pos, x);
                    break;

                case 3:
                    MovimentarAtiv(x, pos);
                    break;
                case 4:
                    AtividadeColaborador(x, y, total);
                    break;
                case 5:
                    break;
                case 6:
                    limpar_tela();
                    Lista_colab(y, total);
                    break;
                case 7://estatistica
                    estatistica(x, y, total);
                    break;
                case 8://ranking de atividade
                    ranking(x, y, total);
                    break;
                case 9:
                    flag = 0;
                    break;
                case 10:
                    flag = 0;
                    retornar = 1;
                    break;
            }
        }
    } while (retornar); // isso aq vai dar opcao p o usuario voltar la
    return 0;
}