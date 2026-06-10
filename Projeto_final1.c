#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR 100
#define MAX_TAREFAS 50

//evita salvar atividade q so tem espaços
int VerificarEspacos(char frase[MAX_CHAR]){
    int Retorno=1;

    for(int i=0; i<strlen(frase); i++){
        if(frase[i]!=' ' && frase[i]!='\n'){
            Retorno=0;//frase valida
            break;
        }
    }
    if(Retorno==1){//frase invalida pq so tem espaços)
        printf("\nAtividade invalida. Digite novamente.\n");
    }
    return Retorno;
}

//essa daq vai abrir e ler o arquivo, dps copiar os dados pras matrizes do codigo
int LerArquivo(int status[], char atividade[][MAX_CHAR], char upperAtividade[][MAX_CHAR], int *contador){
    FILE *arquivo = fopen("atividades.txt", "r");//"r" de read
    if (arquivo == NULL) {//isso verifica se deu tudo certo pra abrir o arquivo
        return 0; 
    }

    int iii=0;

    while(iii < MAX_TAREFAS && fscanf(arquivo, "%d\n", &status[iii]) == 1){//enquanto tiver dentro do limite de tarefas e a leitura obter sucesso
        
        fgets(atividade[iii], MAX_CHAR, arquivo);//le a atividade[i] no arquivo
        atividade[iii][strcspn(atividade[iii], "\n")] = 0; //troca \n por \0

        fgets(upperAtividade[iii], MAX_CHAR, arquivo);// le a atividade em maiúsculo no arquivo
        upperAtividade[iii][strcspn(upperAtividade[iii], "\n")] = 0; // troca \n por \0

        iii++;//vai p proxima linha do arquivo
    }

    fclose(arquivo);
    *contador = iii; // atualiza o contador geral de tarefas cadastradas
    return iii;      // retorna a quantidade de registros carregados
}

//essa salva os dados de novo no arquivo
void escreveDados(int status[], char atividade[][MAX_CHAR], char upperAtividade[][MAX_CHAR], int contador){
    FILE *arquivo = fopen("atividades.txt", "w");//"w" de write

    if(arquivo==NULL){
        return;
    }

    for(int p=0; p<contador; p++){
        fprintf(arquivo, "%d\n%s\n%s\n", status[p], atividade[p], upperAtividade[p]);
    }

    fclose(arquivo);
}

int main(){

    int flag=1, opcao, i=0;
    char atividade[MAX_TAREFAS][MAX_CHAR], upperAtividade[MAX_TAREFAS][MAX_CHAR];//matrizes pra escrita e leitura do arquivo
    int status[MAX_TAREFAS]={0};//1 a fazer, 2 em andamento, 3 concluido, 0 vazio
    int contador=0;//conta as tarefas
    char buscar_ativ[MAX_CHAR];//variavel para ler a atividade buscada
    int numero;//variavel para a movimentacao de atividades
    int ok = 1;

    LerArquivo(status, atividade, upperAtividade, &contador);
    i=contador;

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
                printf("\n===============================");
                printf("\n     CADASTRO DE ATIVIDADE     ");
                printf("\n===============================\n");
                do{
                    int apenasEspacos=0, jaExiste=0, igual;
                    do{
                        printf("\nNome da atividade(max 100 caracteres): ");
                        fgets(atividade[i], MAX_CHAR, stdin);//salva do teclado na matriz
                        atividade[i][strcspn(atividade[i], "\n")] = '\0';//tira o \n
                        apenasEspacos=VerificarEspacos(atividade[i]);
                        char copia[MAX_CHAR];
                        strcpy(copia, atividade[i]);
			
			char inter[MAX_CHAR];//variavel intermediaria			
			//tira espacos extras
			for(int k=0; k<contador; k++) {

                        int b=0, c=0;//incrementam pos das letras

                         for(b=0; b<strlen(atividade[i]); b++){
                                if(copia[b]!=' '){
                                    inter[c]=copia[b];
                                    if(copia[b+1]==' '){
                                        inter[c+1]=' ';
                                        c++;
                                    }
                                c++;
                                }
                         }

                       inter[c]='\0';
                       }
		      //finaliza
			
                       for(int k=0; k<strlen(copia); k++){
                            inter[k]=toupper(inter[k]);//transforma a copia em maiusculo pra comparar
                       }			
	

                       for(int k=0; k<contador; k++){
                            igual=strcmp(inter,upperAtividade[k]);//recebe 0 caso sejam iguais
                            if(igual==0){
                                printf("\nAtividade ja cadastrada anteriormente. Digite outra:\n");
                                jaExiste=1;//retorna 1 pra indicar q eh invalida
                                break;
                            }else{
                                jaExiste=0;
                            }
                        }
                        
                    }while(apenasEspacos==1 || jaExiste==1);

                    for(int k=0; k<strlen(atividade[i]); k++){
                        upperAtividade[i][k] = toupper(atividade[i][k]);
                    }
		   
		   //tirar espacos extras do upper
		   for(int k=0; k<contador; k++) {
			char corrigida[MAX_CHAR];
  			int b=0, c=0;//incrementam pos das letras

   			for(b=0; b<strlen(atividade[i]); b++){
        			if(upperAtividade[i][b]!=' '){
           			   corrigida[c]=upperAtividade[i][b];
           			   if(upperAtividade[i][b+1]==' '){
               				corrigida[c+1]=' ';
               			       c++;
          			   }
           			c++;
        			}
   		      }
    		      corrigida[c]='\0';
   		      strcpy(upperAtividade[i], corrigida);
		   }
		   //finaliza 		   
			
                    status[i]=1;//status da atividade smp começa sendo [1] - a fazer

                    printf("\nAtividade cadastrada com sucesso!\n");

                    i++;
                    contador++;

                    do{
                        printf("\nDeseja cadastrar outra atividade?\n1 - sim\n2 - nao\n");
                        scanf("%d", &ok);
                        scanf("%*c");//limpa o buffer
                        if(ok<1 || ok>2){
                            printf("\nOpcao invalida!");
                        }
                    }while(ok<1 || ok>2);//repete o scanf ate a opcao ser valida

                }while(ok==1);//repete enqt a pessoa quiser salvar atividade

                break;
            case 2:
                printf("\n===============================");
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
                printf("\n");
                break;
            case 3:
                printf("\n===============================");
                printf("\n   MOVIMENTACAO DE ATIVIDADES  ");
                printf("\n===============================\n");
                
                if(contador>0){
                    for(int j=0; j<contador; j++){//imprime a lista de atividades e usuario escolhe numero
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
                        }//testa se o usuario n digitou outro numero pro status
                    }while(status[numero]<1 || status[numero]>3);
                    printf("\nTransferencia concluida!\n");
                }else{
                    printf("\nNenhuma atividade cadastrada.\n");
                }

                break;
            case 4:
                printf("\n===============================");
                printf("\n   QUANTIDADE DE ATIVIDADES    ");
                printf("\n==============================");

                int Fazer = 0, Andamento = 0, Concluido = 0, total=0;

                if(contador>0){
                    for(int j = 0; j < contador; j++) {
                        if(status[j] == 1) {
                            Fazer++;
                        } else if (status[j] == 2) {
                            Andamento++;
                        } else if (status[j] == 3) {
                            Concluido++;
                        }
                    }//vai olhar o vetor status e vê os números (classificacao), ai ele vai la e vai somando
                }

                total=Fazer+Andamento+Concluido;

                printf("\nA fazer: %d", Fazer);
                printf("\nEm andamento: %d", Andamento);
                printf("\nConcluido: %d", Concluido);
                printf("\nTotal: %d", total);

                break;
            case 5:
                printf("\n===============================");
                printf("\n      BUSCA DE ATIVIDADE       ");
                printf("\n===============================");
                int validador=0, pos;

                if(contador>0){
                        printf("\nDigite o nome da atividade: ");
                        fgets(buscar_ativ, sizeof(buscar_ativ), stdin);//le a atividade q o usuario digitou
                        buscar_ativ[strcspn(buscar_ativ, "\n")] = '\0';//tira o \n

                        for (int j = 0; buscar_ativ[j] != '\0'; j++) {
                            buscar_ativ[j] = toupper(buscar_ativ[j]);//deixa tudo maiusculo para a busca
                        }

			//tirar espacos extras
			for(int k=0; k<contador; k++) {
                        char troca[MAX_CHAR];
                        int b=0, c=0;//incrementam pos das letras

                         for(b=0; b<strlen(atividade[i]); b++){
                                if(buscar_ativ[b]!=' '){
                                    troca[c]=buscar_ativ[b];
                                    if(buscar_ativ[b+1]==' '){
                                        troca[c+1]=' ';
                                        c++;
                                    }
                                c++;
                                }
                         }

                       troca[c]='\0';
		      strcmp(buscar_ativ, troca);
                       }

                        for(int j=0; j<contador; j++){
                            if(strcmp(upperAtividade[j], buscar_ativ)==0){//se a string de busca e a original maiuscula forem iguais
                                pos=j;//salva a posicao da atividade encontrada
                                validador=1;//confirma q foi encontrado p terminar a verificacao
                            }
                        }

                        if(validador==0){
                            printf("\nAtividade não encontrada.");
                        }else {
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
		     }
                }else{
                    printf("\nNenhuma atividade cadastrada.\n");
                }

                break;
            case 6:
                flag=2;
                break;
        }
    }

    escreveDados(status, atividade, upperAtividade, contador);
    printf("Os dados foram salvos. Programa encerrado.");

    return 0;

}
