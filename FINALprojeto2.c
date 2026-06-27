#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.c" // arquivo c

#define MAX_CHAR 150
#define MAX_TAREFAS 100
#define MAX_FUNCIONARIOS 100

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
            getchar();

            if(numero < 0 || numero >= x[pos].contador) {
                printf("\nAtividade nao existe.\n");
                printf("\nDeseja tentar novamente?\n[1] Sim\n[2] Nao\n");
                scanf("%d", &res);
                getchar();
            } else {
                do{
                    res = 2;
                    printf("\nPara qual status deseja tranferi-la?\n");
                    printf("[2] A fazer -> Em andamento\n[3] Em andamento -> Concluido\n");
                    scanf("%d", &x[pos].status[numero]); //salva o status na posicao da atividade escolhida
                    getchar();
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
        for(j=0; j<x[i].contador; j++){
            if(x[i].status[j] == 3){
                somaConcluido++;//vai somar todas as atv concluidas de um colaborador
            }
        }
        classificacao[i]=somaConcluido;//armazena as somas soq fora de ordem
        posicao[i]=i;//tipo um id do colaborador soq ligado a posicao, tb ta fora de ordem
    }
    int aux, ajuda;
    for(i=0; i<total-1; i++){//coloca as somas em ordem e as classificaçoes tb
        for(j=0; j<total-i-1; j++){
            if(classificacao[j]<classificacao[j+1]){
                aux=classificacao[j];
                ajuda=posicao[j];
                classificacao[j]=classificacao[j+1];
                posicao[j]=posicao[j+1];
                classificacao[j+1]=aux;
                posicao[j+1]=ajuda;
            }
        }
    }
    printf("=======================\n");
    printf("        RANKING        \n");
    printf("=======================\n\n");
    int pos;

    for(i=0; i<total; i++){
        pos=i;
        printf("%d lugar - %s - %d atividades concluidas\n", pos+1, y[posicao[i]].nome, classificacao[i]);
    }

}

void cadastrarAtividade(struct dados x[], struct usuario y[], int total, int *posAtv, int pos){
    printf("\n===============================");
    printf("\n     CADASTRO DE ATIVIDADE     ");
    printf("\n===============================\n");
    if (x[pos].contador >= MAX_TAREFAS) { // verificao de limite de tarefas
        printf("\nLimite de tarefas atingido.\n");
    } else {
        int k, invalida=0, posBusca, posColabBusca;
        int indiceAtual=x[pos].contador;
        
        printf("\nNome da atividade(max %d caracteres): ", MAX_CHAR);
        fgets(x[pos].atividade[indiceAtual], MAX_CHAR, stdin);//salva do teclado
        invalida = comparaDigitadaCadastradas(x[pos].atividade[indiceAtual], x, y, total, posAtv, pos);//ve se ja existe ou se eh so espaco
        if(invalida==1){
            printf("\nAtividade já cadastrada anteriormente.\n");
        }else if(invalida==2){
            printf("\nAtividade vazia (invalida).\n");
        }else{
            x[pos].atividade[indiceAtual][strcspn(x[pos].atividade[indiceAtual], "\n")] = '\0';
            for (k = 0; k <= strlen(x[pos].atividade[indiceAtual]); k++) { 
                x[pos].upperAtividade[indiceAtual][k] = toupper(x[pos].atividade[indiceAtual][k]);
            }
            char temp[MAX_CHAR];
            RemoverEspacos(x[pos].upperAtividade[indiceAtual], temp);
            
            x[pos].status[indiceAtual] = 1; // status da ativ sempre comeca sendo [1] a fazer
            
            do {
                printf("\nQual a prioridade da atividade?\n[1]ALTA\n[2]MEDIA\n[3]BAIXA\n:");
                scanf("%d", &x[pos].prioridade[indiceAtual]);
                getchar();
                if (x[pos].prioridade[indiceAtual] < 1 || x[pos].prioridade[indiceAtual] > 3) {
                    printf("\nEntrada invalida! Tente novamente!");
                }
            } while (x[pos].prioridade[indiceAtual] < 1 || x[pos].prioridade[indiceAtual] > 3);
            printf("\nAtividade cadastrada com sucesso!\n");
            x[pos].contador++;
        }
    }
}

void buscarAtividade(struct dados x[], struct usuario y[], int total, int *posAtv, int pos){
    printf("\n===============================");
    printf("\n      BUSCA DE ATIVIDADE       ");
    printf("\n===============================\n");

    int i, validador=0, totalAtv=0;
    char frase[MAX_CHAR];

    if(x[pos].contador>0){
        
        printf("\nDigite o nome da atividade que deseja buscar: ");
        fgets(frase, MAX_CHAR, stdin);

        int validador;
        validador=comparaDigitadaCadastradas(frase, x, y, total, posAtv, pos);

        if(validador==0){
            printf("\nAtividade não encontrada.");
        }else if(validador==2){
            printf("\nAtividade vazia(invalida).");
        }else{
            printf("\nAtividade encontrada!\n");
            printf("%s\n", x[pos].atividade[*posAtv]);
            printf("\nPrioridade: ");
            if(x[pos].prioridade[*posAtv]==1){
                printf("Alta");
            }
            if(x[pos].prioridade[*posAtv]==2){
                printf("Media");
            }
            if(x[pos].prioridade[*posAtv]==3){
                printf("Baixa");
            }

            printf("\n\nStatus - ");
            if(x[pos].status[*posAtv]==1){
                printf("A fazer");
            }else if(x[pos].status[*posAtv]==2){
                printf("Em andamento");
            }else if(x[pos].status[*posAtv]==3){
                printf("Concluida");
            }
        }
    }else{
        printf("\nNenhuma atividade cadastrada.\n");
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
                    printf("\nSenha incorreta.\n1 - Tentar novamente\n2 - Sair\n:");
                    do{
                        scanf("%d", &flag2);
                        getchar();
                        if(flag2<1 || flag2>2){
                            printf("\nOpcao invalida. Digite novamente: ");
                        }
                    }while(flag2<1 || flag2>2);
                    if(flag2==1){//se escolheu tentar novamente, volta pro loop
                        flag2=0;
                    }else{//sai caso n queira tentar novamente
                        return -1;
                    }
                }
            } while (flag2 == 0);
            
            return pos;
        } else {
            do {
                printf("\nId nao existe. O que deseja?\n[1]Sair\n[2]Digitar novamente\n:");
                scanf("%d", &nao_sei);
                getchar(); 
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

int LerArquivo(struct dados x[], struct usuario y[], int *total){
    FILE *arquivo = fopen("empresa.txt", "r");
    if(arquivo==NULL){
        return 0;
    }
    int i=0, j=0;

    while(i<MAX_FUNCIONARIOS && fscanf(arquivo, "%d\n", &y[i].id)==1){//enquanto tiver dentro do limite de funcionarios e obter sucesso na leitura do id
        fgets(y[i].nome, MAX_CHAR, arquivo);
        y[i].nome[strcspn(y[i].nome, "\n")] = 0;
        fgets(y[i].senha, MAX_CHAR, arquivo); 
        y[i].senha[strcspn(y[i].senha, "\n")] = 0;
        fscanf(arquivo, "%d\n", &x[i].contador);//le o contador de atividades do funcionario i

        for(j=0; j<x[i].contador; j++){//percorre todas as atividades do funcionario i

            fscanf(arquivo, "%d\n", &x[i].status[j]);

            fgets(x[i].atividade[j], MAX_CHAR, arquivo);//le a atividade[j] do usuario [i] no arquivo
            x[i].atividade[j][strcspn(x[i].atividade[j], "\n")] = 0; //troca \n por \0

            fgets(x[i].upperAtividade[j], MAX_CHAR, arquivo);// le a atividade em maiúsculo no arquivo
            x[i].upperAtividade[j][strcspn(x[i].upperAtividade[j], "\n")] = 0; // troca \n por \0

            fscanf(arquivo, "%d\n", &x[i].prioridade[j]);
        }
        i++;
    }
    fclose(arquivo);
    *total=i;
    return i;
}

void SalvaArquivo(struct dados x[], struct usuario y[], int total){
    FILE *arquivo = fopen("empresa.txt", "w");
    
    if(arquivo == NULL){
        return;
    }

    int i=0, j=0;

    for(i=0; i<total; i++){
        fprintf(arquivo, "%d\n%s\n%s\n%d\n", y[i].id, y[i].nome, y[i].senha, x[i].contador);
        for(j=0; j<x[i].contador; j++){
            fprintf(arquivo, "%d\n%s\n%s\n%d\n", x[i].status[j], x[i].atividade[j], x[i].upperAtividade[j], x[i].prioridade[j]);
        }
    }
    fclose(arquivo);
}

int main() {
    //VARIAVEIS PARA TODOS==============================
    int flag = 1, opcao, i = 0, ok = 1, pos, posColab, res, posAtv;
    int total = 0, f = 0, retornar = 0;
    //==================================================

    struct dados x[MAX_FUNCIONARIOS];
    struct usuario y[MAX_FUNCIONARIOS];

    LerArquivo(x, y, &total);

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
                    getchar();
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
                getchar();
                if (opcao < 1 || opcao > 10) {
                    printf("\nOpcao invalida!");
                }
            } while (opcao < 1 || opcao > 10); //repete o scanf ate a opcao ser valida

            limpar_tela();

            switch (opcao) {
                case 1:
                    cadastrarAtividade(x, y, total, &posAtv, pos);
                    break;

                case 2:
                    listagemAtividades(pos, x);
                    break;

                case 3:
                    MovimentarAtiv(x, pos);
                    break;
                case 4:
                    AtividadeColaborador(x, y, total);
                    break;
                case 5://buscar atividade
                    buscarAtividade(x, y, total, &posAtv, pos);
                    break;
                case 6:
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

    SalvaArquivo(x, y, total);
    printf("\nDados salvos com sucesso!\nFim do programa.\n");

    return 0;
}