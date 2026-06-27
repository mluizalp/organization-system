#include <string.h>
#include <ctype.h>
#include "funcoes.h" // declaracao doq ele vai usar, usa h por padrao pq significa "header" mas podia ser outra letra eu acho

void Transfor_Maius(char inter[]) {
    for (int k = 0; k < (int)strlen(inter); k++) {
        inter[k] = toupper(inter[k]); //transforma em maiusculo para comparar
    }
}

void RemoverEspacos(char frase[], char frase2[]) {
    int a = 0, b = 0;
    for (a = 0; a < (int)strlen(frase); a++) { //remove espacos extras
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
    for (i = 0; i < (int)strlen(frase); i++) {
        if (frase[i] != ' ' && frase[i] != '\n') {
            Retorno = 0; //frase valida
            break;
        }
    }
    return Retorno;
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

//le oq o usuario digitar e compara c tudo q tem cadastrado -> usa no cadastro e na busca
int comparaDigitadaCadastradas(char buscar_ativ[], struct dados x[], struct usuario y[], int total, int *posAtv, int pos){

    int j, validador=0, apenasEspacos = 0;
    char copia[MAX_CHAR];
    char textoAnalise[MAX_CHAR];

    (void)y;     // parametro nao usado nesta funcao, mas mantido pra bater com a assinatura original
    (void)total; // idem

    strcpy(textoAnalise, buscar_ativ);

    textoAnalise[strcspn(textoAnalise, "\n")] = '\0';//tira o \n
    apenasEspacos = VerificarEspacos(textoAnalise);
    if(apenasEspacos == 1){
        return 2;//retorna q eh apenas espacos (invalida)
    }
    RemoverEspacos(textoAnalise, copia); // tirar espacos inuteis
    Transfor_Maius(copia); // colocar em maiusculo

    for(j=0; j<x[pos].contador; j++){
        if(strcmp(x[pos].upperAtividade[j], copia)==0){//se a string digitada e a original maiuscula forem iguais
            *posAtv=j;//salva a posicao da atividade encontrada
            validador=1;//confirma q foi encontrado p terminar a verificacao
            break;
        }
    }

    return validador;
}