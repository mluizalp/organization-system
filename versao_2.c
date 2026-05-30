#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR 100

int main(){

    int flag=1, opcao, i=0, tam;
    char atividade[50][MAX_CHAR], upperAtividade[50][MAX_CHAR];//matrizes pra escrita e leitura do arquivo
    int status[50]={0};//1 a fazer, 2 em andamento, 3 concluido
    int contador=0;//conta as tarefas
    char buscar_ativ[MAX_CHAR];//variavel para ler a atividade buscada
    int numero;//variavel para a movimentacao de atividades
    FILE *arquivo;
    int ok = 1;

    while(flag==1){//loop do menu
        printf("\n===============================");
        printf("\n             MENU              ");
        printf("\n===============================");
        printf("\n\n1 - Cadastrar nova atividade\n2 - Listagem das atividades\n3 - Movimentacao das atividades\n4 - Quantidade de atividades\n5 - Busca de atividade\n6 - Encerrar");
        do{
            printf("\nDigite o numero da opcao desejada: ");
            scanf("%d", &opcao);
            scanf("%*c");

            if(opcao<1 || opcao>6){
                printf("\nOpcao invalida!");
            }
        }while(opcao<1 || opcao>6);//repete o scanf ate a opcao ser valida

        switch(opcao){
            case 1:
                printf("===============================");
                printf("\n     CADASTRO DE ATIVIDADE     ");
                printf("\n===============================");
                do{
                    printf("\n\nNome da atividade(max 100 caracteres): ");
                    fgets(atividade[i], MAX_CHAR, stdin);//salva do teclado na matriz
                    atividade[i][strcspn(atividade[i], "\n")] = 0;//remove o \n q o fgets salva no final
                    for(int k=0; k<sizeof(atividade[i]); k++){
                        upperAtividade[i][k] = atividade[i][k];
                        upperAtividade[i][k] = toupper(upperAtividade[i][k]);
                    }
                    status[i]=1;//status da atividade smp começa sendo [1] - a fazer
                    
                    printf("Atividade cadastrada com sucesso!");

                    i++;
                    contador++;
                    
                    do{
                        printf("\nDeseja cadastrar outra atividade?\n1 - sim\n2 - nao\n");
                        scanf("%d", &ok);
                        scanf("%*c");
                        if(ok<1 || ok>2){
                            printf("\nOpcao invalida!");
                        }
                    }while(ok<1 || ok>2);//repete o scanf ate a opcao ser valida

                }while(ok==1);//repete enqt a pessoa quiser salvar atividade

                break;
            case 2:// ok? so precisamos ver como iremos trabalhar com o arquivo e status (caso essa se mantenha)
                printf("===============================");
                printf("\n    LISTAGEM DE ATIVIDADES     ");
                printf("\n===============================");
                printf("\nA FAZER:");
                for(int j = 0; j < contador; j++) {
                    if (status[j] == 1) {
                        printf("\n - %s", atividade[j]);
                    }
                }
                printf("\nEM ANDAMENTO:");
                for(int j = 0; j < contador; j++) {
                    if (status[j] == 2) {
                        printf("\n - %s", atividade[j]);
                    }
                }
                printf("\nCONCLUIDO:");
                for(int j = 0; j < contador; j++) {
                    if (status[j] == 3) {
                        printf("\n - %s", atividade[j]);
                    }
                }

                break;
            case 3:
                printf("===============================");
                printf("\n   MOVIMENTACAO DE ATIVIDADES  ");
                printf("\n===============================\n");
                for(int j=0; j<contador; j++){//seguindo a ideia de clara, imprime a lsita de atividades e usuario escolhe numero
                    printf("%d - ", j);
                    puts(atividade[j]);
                }
                printf("\nDigite o numero da atividade que deseja movimentar: ");
                scanf("%d", &numero);
               
                do{
                    printf("\nPara qual status deseja tranferi-la?\n");
                    printf("[1] A fazer\n[2] Em andamento\n[3] Concluida\n");
                    scanf("%d", &status[numero]);//salva o status na posicao da atividade escolhida
                    if(status[numero]<1 || status[numero]>3){
                        printf("\nStatus invalido!");
                    }//testa se o animal n digitou outro numero pro status
                }while(status[numero]<1 || status[numero]>3);
                printf("\nTransferencia concluida!");
                break;
            case 4://ok? (caso essa se mantenha)
                printf("===============================");
                printf("\n   QUANTIDADE DE ATIVIDADES    ");
                printf("\n==============================");
                
                int Fazer = 0, Andamento = 0, Concluido = 0;

                for(int j = 0; j < contador; j++) {
                    if(status[j] == 1) {
                        Fazer++;
                    } else if (status[j] == 2) {
                        Andamento++;
                    } else if (status[j] == 3) {
                        Concluido++;
                    }
                }//vai olhar o vetor status e vê os números (classificacao), ai ele vai la e vai somando 

                printf("\nA fazer: %d", Fazer);
                printf("\nEm andamento: %d", Andamento);
                printf("\nConcluido: %d", Concluido);
                printf("\nTotal: %d", contador);
 
                break;
            case 5:
                printf("===============================");
                printf("\n      BUSCA DE ATIVIDADE       ");
                printf("\n===============================");
                int validador=0, pos;
                do{ 
                    printf("\nDigite o nome da atividade: ");
                    fgets(buscar_ativ, sizeof(buscar_ativ), stdin);//le a atividade q o usuario digitou
                    buscar_ativ[strcspn(buscar_ativ, "\n")] = '\0';//tira o \n
                    for (int j = 0; buscar_ativ[j] != '\0'; j++) {
                        buscar_ativ[j] = toupper(buscar_ativ[j]);//deixa tudo maiusculo para a busca
                    }
                    for(int j=0; j<contador; j++){
                        if(strcmp(upperAtividade[j], buscar_ativ)==0){//se a string de busca e a original maiuscula forem iguais
                            pos=j;//salva a posicao da atividade encontrada
                            validador=1;//confirma q foi encontrado p terminar a verificacao
                        }
                    }
                    if(validador==0){
                        printf("\nAtividade não encontrada.");
                    }
                }while(validador==0);

                printf("\nAtividade encontrada!\n");
                puts(atividade[pos]);
                printf("\nStatus - ");
                if(status[pos]==1){
                    printf("A fazer");
                }else if(status[pos]==2){
                    printf("Em andamento");
                }else if(status[pos]==3){
                    printf("Concluida");
                }

                break;
            case 6:
                flag=2;
                break;
        }
    }

    arquivo=fopen("atividades.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;   
    }//caso o fopen falhe

    for(int p=0; p<contador; p++){               
        fprintf(arquivo,"%d\n%s\n%s", status[p], atividade[p], upperAtividade[p]);//salva o status e a atividade no arquivo
    }

    fclose(arquivo);

    return 0;

}
