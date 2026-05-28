#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR 100

int main(){

    int flag=1, opcao, i=0, tam;
    char atividade[50][MAX_CHAR], atividadeLida[50][MAX_CHAR];//matrizes pra escrita e leitura do arquivo
    int status[50];//0 a fazer, 1 em andamento, 2 concluido
    int contador=0;//conta as tarefas
    int resposta;//variavel para o case 3 
    char buscar_ativ [50];//variavel para ler a atividade buscada
    int numero;//variavel para a movimentacao de atividades
    FILE *arquivo;

    while(flag==1){//loop do menu
        printf("===============================");
        printf("\n             MENU              ");
        printf("\n===============================");
        printf("\n\n1 - Cadastrar nova atividade\n2 - Listagem das atividades\n3 - Movimentacao das atividades\n4 - Quantidade de atividades\n5 - Busca de atividade\n");
        do{
            printf("\nDigite o numero da opcao desejada: ");
            scanf("%d", &opcao);
            scanf("%*c");

            if(opcao<1 || opcao>5){
                printf("\nOpcao invalida!");
            }
        }while(opcao<1 || opcao>5);//repete o scanf ate a opcao ser valida

        switch(opcao){
            case 1:
                printf("===============================");
                printf("\n     CADASTRO DE ATIVIDADE     ");
                printf("\n===============================");
                do{
                    printf("\n\nNome da atividade(max 100 caracteres): ");
                    fgets(atividade[i], MAX_CHAR, stdin);//salva do teclado na matriz
                    atividade[i][strcspn(atividade[i], "\n")] = 0;//remove o \n q o fgets salva no final
                    status[i]=0;//status da atividade smp começa sendo a fazer

                    arquivo=fopen("atividades.txt", "a");
                    fprintf(arquivo,"%d\n%s\n", status[i], atividade[i]);//salva o status e a atividade no arquivo
                    fclose(arquivo);
                    
                    i++;
                    
                    do{
                        printf("\nDeseja cadastrar outra atividade?\n1 - sim\n2 - nao\n");
                        scanf("%d", &flag);
                        scanf("%*c");
                        if(flag<1 || flag>2){
                            printf("\nOpcao invalida!");
                        }
                    }while(flag<1 || flag>2);//repete o scanf ate a opcao ser valida

                }while(flag==1);//repete enqt a pessoa quiser salvar atividade

                break;
            case 2:// ok? so precisamos ver como iremos trabalhar com o arquivo e status (caso essa se mantenha)
                printf("===============================");
                printf("\n    LISTAGEM DE ATIVIDADES     ");
                printf("\n===============================");
                printf("\nA FAZER:");
                for(int j = 0; j < contador; j++) {
                    if (status[j] == 0) {
                        printf("\n - %s", atividade[j]);
                    }
                }
                printf("\nEM ANDAMENTO:");
                for(int j = 0; j < contador; j++) {
                    if (status[j] == 1) {
                        printf("\n - %s", atividade[j]);
                    }
                }
                printf("\nCONCLUIDO:");
                for(int j = 0; j < contador; j++) {
                    if (status[j] == 2) {
                        printf("\n - %s", atividade[j]);
                    }
                }

                break;
            case 3: //aqui eu pensei em tipo, listar as atividades e o usuaria digita o numero da que quer e afins(na lista), mas se preferirem da para fazer pegando o nome mesmo, ai teria que trocar
                printf("===============================");
                printf("\n   MOVIMENTACAO DE ATIVIDADES  ");
                printf("\n===============================");
                //////coloca a listagem aqui (ordem)
                printf("\nDigite o numero da atividade que deseja movimentar: ");
                scanf("%d", &numero);
                ////criar um mecanismo para buscar o numero em relacao ao nome
                printf("\nPara qual status deseja tranferi-la?\n");
                printf("[1] A fazer\n[2] Em andamento\n[3] Concluida\n");
                scanf("%d", &resposta);
                /////////// mecanismo para movimentar
                printf("\nTransferencia concluida!");
                break;
            case 4://ok? (caso essa se mantenha)
                printf("===============================");
                printf("\n   QUANTIDADE DE ATIVIDADES    ");
                printf("\n==============================");
                
                int Fazer = 0, Andamento = 0, Concluido = 0;

                for(int j = 0; j < contador; j++) {
                    if(status[j] == 0) {
                        Fazer++;
                    } else if (status[j] == 1) {
                        Andamento++;
                    } else if (status[j] == 2) {
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
                printf("\nDigite o nome da atividade: ");
                fgets(buscar_ativ, sizeof(buscar_ativ), stdin);
                buscar_ativ[strcspn(buscar_ativ, "\n")] = '\0';//tira o \n
                for (int i = 0; buscar_ativ[i] != '\0'; i++) {
                    buscar_ativ[i] = toupper(buscar_ativ[i]);
                }//aqui vai deixar tudo maiusculo logo para a busca
                //////////adicionar um mecanismo de busca no arquivo que o coloque em maiusculo tambem, nao sei fazer :D
                break;
        }

        do{
            printf("\n\nDeseja continuar?\n\n1 - sim\n2 - nao\n");
            scanf("%d", &flag);
            if(flag<1 || flag>2){
                printf("\nOpcao invalida!");
            }
        }while(flag<1 || flag>2);//repete o scanf ate a opcao ser valida
    }

    return 0;

}
