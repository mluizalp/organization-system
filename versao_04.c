#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tamanhos máximos
#define MAX_CHAR 100
#define MAX_TAREFAS 50

// Função que evita salvar atividade que só tem espaços
int VerificarEspacos(char frase[MAX_CHAR]) {
    int Retorno = 1;

    for (int i = 0; i < strlen(frase); i++) {
        if (frase[i] != ' ' && frase[i] != '\n') {
            Retorno = 0; // frase válida
            break;
        }
    }
    if (Retorno == 1) { // Frase inválida porque só tem espaços
        printf("\nAtividade invalida. Digite novamente.\n");
    }
    return Retorno;
}

// Função para abrir e ler o arquivo, depois copiar os dados pras matrizes do código
int LerArquivo(int status[], char atividade[][MAX_CHAR], char upperAtividade[][MAX_CHAR], int *contador) {
    FILE *arquivo = fopen("atividades.txt", "r"); // "r" de read
    if (arquivo == NULL) { // Verifica se deu tudo certo pra abrir o arquivo
        return 0; 
    }

    int iii = 0;
    
    // Enquanto estiver dentro do limite de tarefas e a leitura for bem sucedida
    while (iii < MAX_TAREFAS && fscanf(arquivo, "%d\n", &status[iii]) == 1) { 
        
        fgets(atividade[iii], MAX_CHAR, arquivo);
        atividade[iii][strcspn(atividade[iii], "\n")] = 0; // Troca \n por \0

        fgets(upperAtividade[iii], MAX_CHAR, arquivo); 
        upperAtividade[iii][strcspn(upperAtividade[iii], "\n")] = 0;

        iii++; // Vai para a próxima linha do arquivo
    }

    fclose(arquivo);
    *contador = iii; // Atualiza o contador geral de tarefas cadastradas
    return iii;      // Retorna a quantidade de registros carregados
}

// Função que salva os dados de novo no arquivo
void escreveDados(int status[], char atividade[][MAX_CHAR], char upperAtividade[][MAX_CHAR], int contador) {
    FILE *arquivo = fopen("atividades.txt", "w"); // "w" de write

    if (arquivo == NULL) {
        return;
    }

    for (int p = 0; p < contador; p++) {
        fprintf(arquivo, "%d\n%s\n%s\n", status[p], atividade[p], upperAtividade[p]);
    }

    fclose(arquivo);
}

// Controla a exibição e a leitura da opção do menu
int ler_opcao() {
    int opcao;

    printf("\n===============================");
    printf("\n             MENU              ");
    printf("\n===============================");
    printf("\n1 - Cadastrar nova atividade");
    printf("\n2 - Listagem das atividades");
    printf("\n3 - Movimentacao das atividades");
    printf("\n4 - Quantidade de atividades");
    printf("\n5 - Busca de atividade");
    printf("\n6 - Encerrar\n");
    
    do {
        printf("\nDigite o numero da opcao desejada: ");
        scanf("%d", &opcao);
        scanf("%*c"); // Limpa o buffer do teclado

        if (opcao < 1 || opcao > 6) {
            printf("Opcao invalida! Tente novamente.\n");
        }
        
    } while (opcao < 1 || opcao > 6); // Repete se for menor que 1 ou maior que 6
    
    return opcao;
}

void cadastrar_atividade(int status[], char atividade[][MAX_CHAR], char upperAtividade[][MAX_CHAR], int *contador, int *i) {
    printf("\n===============================");
    printf("\n     CADASTRO DE ATIVIDADE     ");
    printf("\n===============================");
    
    int ok = 1;
    
    do {
        int apenasEspacos = 0, jaExiste = 0, igual;
        
        if (*contador >= MAX_TAREFAS) {
            printf("Limite de tarefas atingido!\n");
            break;
        }

        do {
            printf("\nNome da atividade(max 100 caracteres): ");
            fgets(atividade[*i], MAX_CHAR, stdin); // Salva do teclado na matriz
            atividade[*i][strcspn(atividade[*i], "\n")] = '\0'; // Tira o \n
            
            apenasEspacos = VerificarEspacos(atividade[*i]);
            if (apenasEspacos == 1) continue;

            char copia[MAX_CHAR];
            strcpy(copia, atividade[*i]);
            for (int k = 0; k < strlen(copia); k++) {
                copia[k] = toupper(copia[k]); // transforma a copia em maiusculo pra comparar
            }

            jaExiste = 0;
            for (int k = 0; k < *contador; k++) {
                igual = strcmp(copia, upperAtividade[k]); // Recebe 0 caso sejam iguais
                if (igual == 0) {
                    printf("\nAtividade ja cadastrada anteriormente. Digite outra:\n");
                    jaExiste = 1; 
                    break;
                }
            }
            
        } while (apenasEspacos == 1 || jaExiste == 1);

        for (int k = 0; k <= strlen(atividade[*i]); k++) { // <= para copiar o '\0'
            upperAtividade[*i][k] = toupper(atividade[*i][k]);
        }
        status[*i] = 1; // Status da atividade padrão começa sendo "1 - a fazer"

        printf("\nAtividade cadastrada com sucesso!\n");

        (*i)++;
        (*contador)++;

        do {
            printf("\nDeseja cadastrar outra atividade?\n1 - sim\n2 - nao\n");
            scanf("%d", &ok);
            scanf("%*c"); 
            
            if (ok < 1 || ok > 2) {
                printf("\nOpcao invalida!");
            }
            
        } while (ok < 1 || ok > 2); 

    } while (ok == 1); 
}

void listar_atividade(int status[], char atividade[][MAX_CHAR], int contador) {
    printf("\n===============================");
    printf("\n    LISTAGEM DE ATIVIDADES     ");
    printf("\n===============================");
    
    printf("\n\nA FAZER:");
    for (int j = 0; j < contador; j++) {
        if (status[j] == 1) {
            printf("\n %d - %s", j, atividade[j]); 
        }
    }
    
    printf("\n\nEM ANDAMENTO:");
    for (int j = 0; j < contador; j++) {
        if (status[j] == 2) {
            printf("\n %d - %s", j, atividade[j]);
        }
    }
    
    printf("\n\nCONCLUIDO:\n");
    for (int j = 0; j < contador; j++) {
        if (status[j] == 3) {
            printf("\n %d - %s", j, atividade[j]);
        }
    }
    
}

void movimentar_atividade(int status[], char atividade[][MAX_CHAR], int contador) {
    printf("\n===============================");
    printf("\n   MOVIMENTACAO DE ATIVIDADES  ");
    printf("\n===============================");
    
    int numero;
    
    if (contador > 0) {
        // Imprime a lista de atividades e usuário escolhe número
        for (int j = 0; j < contador; j++) { 
            printf("%d - %s [%s]\n", j, atividade[j], 
                   status[j] == 1 ? "A fazer" : (status[j] == 2 ? "Em andamento" : "Concluida"));
        }
        
        // Valida o número da atividade que será movimentada
        do {
            printf("\nDigite o numero da atividade que deseja movimentar: ");
            scanf("%d", &numero);
            scanf("%*c"); // Limpa o buffer
            
            if (numero < 0 || numero >= contador) {
                printf("Numero de atividade invalido! Tente novamente.\n");
            }
            
        } while (numero < 0 || numero >= contador);

        do {
            printf("\nPara qual status deseja tranferi-la?\n");
            printf("[1] A fazer\n[2] Em andamento\n[3] Concluida\n");
            printf("Escolha: ");
            scanf("%d", &status[numero]);
            scanf("%*c"); // Limpa o buffer
            
            if (status[numero] < 1 || status[numero] > 3) {
                printf("Status invalido! Escolha de 1 a 3.\n");
            }
            
        } while (status[numero] < 1 || status[numero] > 3);
        
        printf("\nTransferencia concluida!\n");
        
    } else {
        printf("\nNenhuma atividade cadastrada.\n");
    }
}

void quantidade_atividade(int status[], int contador) {
    printf("\n===============================");
    printf("\n   QUANTIDADE DE ATIVIDADES    ");
    printf("\n===============================");

    int Fazer = 0, Andamento = 0, Concluido = 0, total = 0;

    if (contador > 0) {
        for (int j = 0; j < contador; j++) {
            if (status[j] == 1) {
                Fazer++;
            } else if (status[j] == 2) {
                Andamento++;
            } else if (status[j] == 3) {
                Concluido++;
            }
        }
    }

    total = Fazer + Andamento + Concluido;

    printf("\nA fazer: %d", Fazer);
    printf("\nEm andamento: %d", Andamento);
    printf("\nConcluido: %d", Concluido);
    printf("\nTotal: %d\n", total);
}

void buscar_atividade(int status[], char atividade[][MAX_CHAR], int contador) {
    printf("\n===============================");
    printf("\n      BUSCA DE ATIVIDADE       ");
    printf("\n===============================\n");
    
    if (contador <= 0) {
        printf("Nenhuma atividade cadastrada para buscar.\n");
        return;
    }

    // Chama a função listar_atividade
    listar_atividade(status, atividade, contador);

    int codigo_busca;
    
    // Só permite buscar por código válido
    do {
        printf("Digite o codigo da atividade que deseja buscar: ");
        scanf("%d", &codigo_busca);
        
        scanf("%*c"); 

        if (codigo_busca < 0 || codigo_busca >= contador) {
            printf("Código inválido.\n");
        }
        
    } while (codigo_busca < 0 || codigo_busca >= contador);

    printf("Atividade encontrada!");
    printf("\nCodigo: %d", codigo_busca);
    printf("\nNome:   %s", atividade[codigo_busca]);
    printf("\nStatus: ");
    
    if (status[codigo_busca] == 1) printf("A fazer\n");
    else if (status[codigo_busca] == 2) printf("Em andamento\n");
    else if (status[codigo_busca] == 3) printf("Concluida\n");
    
}

int main() {
    int flag = 1, opcao, i = 0;
    char atividade[MAX_TAREFAS][MAX_CHAR];
    char upperAtividade[MAX_TAREFAS][MAX_CHAR]; // Matrizes pra escrita e leitura do arquivo
    int status[MAX_TAREFAS] = {0};               // 1 a fazer, 2 em andamento, 3 concluido, 0 vazio
    int contador = 0;                            // Conta as tarefas

    // Inicializa carregando dados do arquivo
    LerArquivo(status, atividade, upperAtividade, &contador);
    i = contador;

    while (flag == 1) {
        opcao = ler_opcao();

        switch (opcao) {
            case 1: 
                cadastrar_atividade(status, atividade, upperAtividade, &contador, &i);
                break;
                
            case 2:
                listar_atividade(status, atividade, contador);
                break;
                
            case 3:
                movimentar_atividade(status, atividade, contador);
                break;
                
            case 4:
                quantidade_atividade(status, contador);
                break;
                
            case 5:
                buscar_atividade(status, atividade, contador); 
                break;
                
            case 6:
                flag = 2; 
                break;
                
            default:
                // Altera a flag para encerrar o while
                printf("Opção Inválida!\n");
                break;
        }
    }

    // Grava as alterações de volta no arquivo antes de sair
    escreveDados(status, atividade, upperAtividade, contador);
    
    printf("Os dados foram salvos. Programa encerrado.\n");

    return 0;
}