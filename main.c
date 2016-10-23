/************************************************************
 * Nome Aluno: Bruno Luis Panuto Silva RA: 1510029160 *
 * Nome Aluno: Leonardo Silva RA: 1510027479 *
 * Data: 20/09/2016 *
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


// Opções dos menus
#define OP_CADASTRAR 1
#define OP_EXCLUIR 2
#define OP_BUSCAR 3
#define OP_RELATORIO 4
#define OP_SAIR 6
#define OP_BUSCAR_NOME 1
#define OP_BUSCAR_GENERO 2
#define OP_BUSCAR_ANO 3

// constantes de tamanho
#define MAX_CHAR 1024
#define MAX_PRODUCTS 512

// códigos de erro
#define SUCCESS 0x5
#define ERR_FULL 0xf0011

typedef struct Produto {
  int codigo;
  char nome[MAX_CHAR];
  char genero[MAX_CHAR];
  int ano;
  float preco;
} Produto;

// guarda o número de produtos cadastrados
// e o array de produtos
typedef struct Produtos {
  int lim;
  Produto *ps;
} Produtos;

// Cadastra um produto no vetor p->ps
int Produtos_cadastrar(Produtos *p, Produto c) {
  if (p->lim >= MAX_PRODUCTS) {
    return ERR_FULL;
  }

  p->ps[p->lim++] = c;
  return SUCCESS;
}

// trata o retorno dos erros, caso seja necessário
void handle_err(int rc) {
  switch(rc) {
  case SUCCESS:
    break;
  case ERR_FULL:
    printf("ERRO: Limite máximo de produtos atingido. Esta é uma versão free. Para conseguir cadastrar mais produtos, por favor, contacte o administrador do seu sistema.\n\n");
  }
}


// Exclui um produto do vetor P->ps
int Produtos_excluir(Produtos* P, int code) {
  int i = 0;
  for(i = 0; i < P->lim; i++) {
    int r = P->ps[i].codigo == code;
    if(r == 1) {
      int j = 0;
      for(j = i; j < P->lim; j++) {
        P->ps[j] = P->ps[j+1];
      }
      P->lim--;
      return SUCCESS;
    }
  }
  return SUCCESS;
}


// Formata um produto na tela
void Produto_print(Produto P) {
  printf("Nome: %s -- Genero: %s -- Ano: %d -- Preco: %.2f\n", P.nome, P.genero, P.ano, P.preco);
}


// Faz uma busca de produtos por gênero e printa os produtos achados na tela
int Produtos_buscar_genero(Produtos P, char* genero){
  int i = 0;
  for (i = 0;i < P.lim; i++) {
    int r = strcmp(P.ps[i].genero, genero);
    if (r == 0) {
      Produto_print(P.ps[i]);
    }
  }
}

// Faz uma busca de produtos por nome e printa os produtos achados na tela
int Produtos_buscar_nome(Produtos P, char* nome) {
  int i = 0;
  for (i = 0;i < P.lim; i++) {
    int r = strcmp(P.ps[i].nome, nome);
    if (r == 0) {
      Produto_print(P.ps[i]);
    }
  }
}

// Faz uma busca de produtos por ano e printa os produtos achados na tela
int Produtos_buscar_ano(Produtos P, int ano){
  int i = 0;
  for (i = 0;i < P.lim; i++) {
    if (P.ps[i].ano == ano) {
      Produto_print(P.ps[i]);
    }
  }
    
}

// limpa uma string recebida via fgets, tirando a quebra de linha do final e adicionando um null byte
void cleanup(char* str) {
  if (strlen(str) > 0 && str[strlen(str) - 1] == '\n') {
    str[strlen(str)-1] = '\0';
  }
}

// Cadastra um produto no array P->ps
void cadastrar_produto(Produtos *P) {
  Produto p;
  printf("\n==== CADASTRO DE PRODUTO ====\n");
  printf("Digite o codigo: ");
  char code_buf[10];
  fgets(code_buf, sizeof code_buf, stdin);
  int code = atoi(code_buf);
  p.codigo = code;

  printf("Digite o nome: ");
  fgets(p.nome, sizeof(p.nome), stdin);
  cleanup(p.nome);

  printf("Digite o genero: ");
  fgets(p.genero, sizeof(p.genero), stdin);
  cleanup(p.genero);

  printf("Digite o ano de fabricacao: ");
  char ano_buf[10];
  int ano;
  fgets(ano_buf, sizeof ano_buf, stdin);
  cleanup(ano_buf);
  ano = atoi(ano_buf);
  p.ano = ano;

  printf("Digite o preco: ");
  char preco_buf[10];
  float preco;
  fgets(preco_buf, sizeof preco_buf, stdin);
  cleanup(preco_buf);
  preco = atof(preco_buf);
  p.preco = preco;

  int rc = Produtos_cadastrar(P, p);
  handle_err(rc);
}

// exclui um produto do array P->ps
void excluir_produto(Produtos* P) {
  printf("\n*** Excluir produto ***\n");
  printf("Digite o codigo do produto: ");
  char code[10];
  fgets(code, sizeof code, stdin);
  int c = atoi(code);
  handle_err(Produtos_excluir(P, c));
}

// Submenu de buscas
void buscar_produto_menu() {
  printf("\n==== OPCOES DE BUSCA ====\n");
  printf("1. Buscar por nome\n");
  printf("2. Buscar por genero\n");
  printf("3. Buscar por ano\n");
  printf("6. Voltar para o menu inicial\n");
}

// faz validações de diferentes opções para determinar qual das funções de busca chamar
void buscar_produto(Produtos P){
  int op = 0;
  char buf[10];
  buscar_produto_menu();
  
  fgets(buf, sizeof buf, stdin);
  op = atoi(buf);
  while(op != OP_SAIR) {
    switch(op) {
    case OP_BUSCAR_NOME:
      printf("Digite o nome do produto: ");
      char nome[MAX_CHAR];
      fgets(nome, sizeof nome, stdin);
      cleanup(nome);
      Produtos_buscar_nome(P, nome);
      break;
    case OP_BUSCAR_GENERO:
      printf("Digite o genero do produto: ");
      char genero[MAX_CHAR];
      fgets(genero, sizeof genero, stdin);
      cleanup(genero);
      Produtos_buscar_genero(P, genero);
      break;
    case OP_BUSCAR_ANO:
      printf("Digite o ano do produto: ");
      char ano[MAX_CHAR];
      int i_ano;
      fgets(ano, sizeof ano, stdin);
      i_ano = atoi(ano);
      Produtos_buscar_ano(P, i_ano);
      break;
    }  
    buscar_produto_menu();
    fgets(buf, sizeof buf, stdin);
    op = atoi(buf);
  }
}

// Busca os produtos que estão em determinada faixa de preço
int Produtos_buscar_preco(Produtos P, float min, float max) {
  int i = 0;
  for(i = 0; i < P.lim; i++) {
    if(P.ps[i].preco >= min && P.ps[i].preco <= max) {
      Produto_print(P.ps[i]);
    }
  }
}

// printa a quantidade de produtos por gênero
int Produtos_qtd_produtos_genero(Produtos P) {
  int i = 0;
  char* generos[P.lim*2];
  for(i = 0; i < P.lim; i++) {
    generos[i] = P.ps[i].genero;
  }
  char* visited[P.lim*2];
  int visited_lim = 0;
  for(i = 0; i < P.lim; i++) {
    char* genero = generos[i];

    int qtd = 1, j = 0;
    for(j = i+1; j < P.lim; j++) {
      if((strcmp(generos[j], genero)) == 0) {
        qtd++;
      }
    }
    int k = 0, was_printed = 0;
    for(k = 0; k < visited_lim; k++) {
      if((strcmp(visited[k], genero)) == 0) {
        was_printed = 1;
      }
    }
    if(!was_printed) {
      printf("Genero %s tem %d produtos\n", genero, qtd);
      visited[visited_lim++] = genero;
    }
  }
}

// Imprime na tela um relatório contendo os preços em determinada faixa de preço
// e a quantidade de produtos por gênero
void relatorio(Produtos P) {
  printf("\n*** Relatorio ***\n");
  float p_min = 0;
  char p_min_buf[10];
  printf("Digite um preço minimo: ");
  fgets(p_min_buf, sizeof p_min_buf, stdin);
  p_min = atof(p_min_buf);

  float p_max = 0;
  char p_max_buf[10];
  printf("Digite um preço maximo: ");
  fgets(p_max_buf, sizeof p_max_buf, stdin);
  p_max = atof(p_max_buf);

  printf("\n*** Produtos nessa faixa de preco ***\n");
  handle_err(Produtos_buscar_preco(P, p_min, p_max));
  printf("\n*** Quantidade de produtos por gênero ***\n");
  handle_err(Produtos_qtd_produtos_genero(P));
}

// menu principal
void menu() {
  printf("\n==== SUPERMERCADO STO ANTONIO ====\nMenu Principal\n");
  printf("1. Cadastrar produto\n");
  printf("2. Excluir produto\n");
  printf("3. Buscar produto\n");
  printf("4. Relatorio\n");
  printf("6. Sair\n");
}

int main() {
  Produtos p;
  p.lim = 0;
  p.ps = (Produto*)malloc(sizeof(Produto)*MAX_PRODUCTS);

  int op = 0;
  char buf[10];
  menu();
  fgets(buf, sizeof buf, stdin);
  op = atoi(buf);
  while(op != OP_SAIR) {
    switch(op) {
    case OP_CADASTRAR:
      cadastrar_produto(&p);
      break;
    case OP_EXCLUIR:
      excluir_produto(&p);
      break;
    case OP_BUSCAR:
      buscar_produto(p);
      break;
    case OP_RELATORIO:
      relatorio(p);
    }
    menu();
    fgets(buf, sizeof buf, stdin);
    op = atoi(buf);
  }
  return 0;
}
