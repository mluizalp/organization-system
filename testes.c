#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include <assert.h>

void teste_Transfor_Maius(void) {
    char texto[MAX_CHAR] = "Comprar cafe";
    Transfor_Maius(texto);
    assert(strcmp(texto, "COMPRAR CAFE") == 0);

    char vazio[MAX_CHAR] = "";
    Transfor_Maius(vazio);
    assert(strcmp(vazio, "") == 0);

    printf("[OK] teste_Transfor_Maius\n");
}

void teste_VerificarEspacos(void) {
    char so_espacos[MAX_CHAR] = "   ";
    assert(VerificarEspacos(so_espacos) == 1); // deve falar q eh vazio (so espacos)

    char com_texto[MAX_CHAR] = "  Cafe  ";
    assert(VerificarEspacos(com_texto) == 0); // nao eh vazio

    char string_vazia[MAX_CHAR] = "";
    assert(VerificarEspacos(string_vazia) == 1); // string vazia tambem conta como "vazia"

    printf("[OK] teste_VerificarEspacos\n");
}

void teste_RemoverEspacos(void) {
    char entrada1[MAX_CHAR] = "Estudar    C   ";
    char saida1[MAX_CHAR];
    RemoverEspacos(entrada1, saida1);
    assert(strcmp(entrada1, "Estudar C") == 0);

    char entrada2[MAX_CHAR] = "OI";
    char saida2[MAX_CHAR];
    RemoverEspacos(entrada2, saida2);
    assert(strcmp(entrada2, "OI") == 0);

    printf("[OK] teste_RemoverEspacos\n");
}

void teste_checar_id_e_posicao_id(void) {
    struct usuario y[3];
    y[0].id = 10100;
    y[1].id = 10101;
    y[2].id = 10102;

    assert(checar_id(10101, y, 3) == 1);   // id existe na lista
    assert(checar_id(99999, y, 3) == 0);   // id nao existe

    assert(posicao_id(10102, y, 3) == 2);  // devolve a posicao correta
    assert(posicao_id(50000, y, 3) == -1); // nao encontra devolve -1

    printf("[OK] teste_checar_id_e_posicao_id\n");
}// o 3 ali eh pq ele esta olhando a quantidade

void teste_checar_sen(void) {
    struct usuario y[1];
    strcpy(y[0].senha, "Canario123");

    assert(checar_sen("Canario123", y, 0) == 1); // senha certa
    assert(checar_sen("errada", y, 0) == 0);        // senha errada

    printf("[OK] teste_checar_sen\n");
} // aqui usa 0 pq eh a posicao (indice), como eu sei a posicao que quero, eh mais facil so colocar a posicao

void teste_comparaDigitadaCadastradas_duplicidade(void) {
    // 1 colaborador (posicao 0) com 1 atividade ja cadastrada
    struct dados x[1];
    struct usuario y[1];
    int posAtv;

    x[0].contador = 1;
    strcpy(x[0].atividade[0], "Estudar C");
    strcpy(x[0].upperAtividade[0], "ESTUDAR C");

    // deve falar se tiver atividades duplicadas
    // com espacos extras e letras maiusculas/minusculas diferentes
    int resultado = comparaDigitadaCadastradas("  estudar   c  \n", x, &posAtv, 0);
    assert(resultado == 1);       // 1 = encontrou (duplicada)
    assert(posAtv == 0);          // encontrou na posicao certa

    // busca sem resultado valido
    int resultado2 = comparaDigitadaCadastradas("Outra coisa\n", x, &posAtv, 0);
    assert(resultado2 == 0);      // 0 = nao encontrou

    // deve retornar 2 (entrada invalida)
    int resultado3 = comparaDigitadaCadastradas("    \n", x, &posAtv, 0);
    assert(resultado3 == 2);      // 2 = invalida (so espacos)

    printf("[OK] teste_comparaDigitadaCadastradas_duplicidade\n");
}

int main(void) {

    teste_Transfor_Maius();
    teste_VerificarEspacos();
    teste_RemoverEspacos();
    teste_checar_id_e_posicao_id();
    teste_checar_sen();
    teste_comparaDigitadaCadastradas_duplicidade();

    printf("\nTudo certinho!\n");
    return 0;
}