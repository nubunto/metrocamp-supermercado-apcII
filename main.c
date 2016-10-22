/************************************************************
 * Nome Aluno: Bruno Luis Panuto Silva RA: 1510029160 *
 * Nome Aluno: Leonardo Silva RA: *
 * Data: 20/09/2016 *
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define OP_CADASTRAR 1
#define OP_EXCLUIR 2
#define OP_BUSCAR 3
#define OP_BUSCAR_PRECO 4
#define OP_RELATORIO 5
#define OP_SAIR 6
#define OP_BUSCAR_NOME 1
#define OP_BUSCAR_GENERO 2
#define OP_BUSCAR_ANO 3

#define MAX_CHAR 1024
#define MAX_PRODUCTS 512

#define SUCCESS 0x5
#define ERR_FULL 0xf0011

typedef struct Produto {
  int codigo;
  char nome[MAX_CHAR];
  char genero[MAX_CHAR];
  int ano;
  float preco;
} Produto;

typedef struct Produtos {
  int lim;
  Produto *ps;
} Produtos;

int Produtos_cadastrar(Produtos *p, Produto c) {
  if (p->lim >= MAX_PRODUCTS) {
    return ERR_FULL;
  }

  p->ps[p->lim++] = c;
  return SUCCESS;
}

void handle_err(int rc) {
  switch(rc) {
  case SUCCESS:
    break;
  case ERR_FULL:
    printf("ERRO: Limite máximo de produtos atingido. Esta é uma versão free. Para conseguir cadastrar mais produtos, por favor, contacte o administrador do seu sistema.\n\n");
  }
}

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

void Produto_print(Produto P) {
  printf("Nome: %s -- Genero: %s -- Ano: %d -- Preco: %.2f\n", P.nome, P.genero, P.ano, P.preco);
}

int Produtos_buscar_genero(Produtos P, char* genero){
  int i = 0;
  for (i = 0;i < P.lim; i++) {
    int r = strcmp(P.ps[i].genero, genero); // r == 0 se nome do produto == nome
    if (r == 0) {
      Produto_print(P.ps[i]);
    }
  }
    
}

int Produtos_buscar_nome(Produtos P, char* nome) {
  int i = 0;
  for (i = 0;i < P.lim; i++) {
    int r = strcmp(P.ps[i].nome, nome); // r == 0 se nome do produto == nome
    if (r == 0) {
      Produto_print(P.ps[i]);
    }
  }
    
}

int Produtos_buscar_ano(Produtos P, int ano){
  int i = 0;
  for (i = 0;i < P.lim; i++) {
    if (P.ps[i].ano == ano) {
      Produto_print(P.ps[i]);
    }
  }
    
}

int Produtos_relatorio(Produtos, void*);

void cleanup(char* str) {
  if (strlen(str) > 0 && str[strlen(str) - 1] == '\n') {
    str[strlen(str)-1] = '\0';
  }
}

void cadastrar_produto(Produtos *P) {
  Produto p;
  printf("==== CADASTRO DE PRODUTO ====\n");
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
  char ano_buf[5];
  int ano;
  fgets(ano_buf, sizeof ano_buf, stdin);
  ano = atoi(ano_buf);
  p.ano = ano;

  printf("Digite o preco: ");
  char preco_buf[10];
  float preco;
  fgets(preco_buf, sizeof preco_buf, stdin);
  preco = atof(preco_buf);
  p.preco = preco;

  int rc = Produtos_cadastrar(P, p);
  handle_err(rc);
}


void excluir_produto(Produtos* P) {
  printf("*** Excluir produto ***\n");
  printf("Digite o codigo do produto: ");
  char code[10];
  fgets(code, sizeof code, stdin);
  int c = atoi(code);
  handle_err(Produtos_excluir(P, c));
}

void buscar_produto_menu() {
  printf("==== OPCOES DE BUSCA ====\n");
  printf("1. Buscar por nome\n");
  printf("2. Buscar por genero\n");
  printf("3. Buscar por ano\n");
  printf("6. Voltar para o menu inicial\n");
}


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

void buscar_produto_preco(Produtos);

void relatorio(Produtos p) {
  int i = 0;
  for(i = 0; i < p.lim; i++) {
    Produto_print(p.ps[i]);
  }
}

void menu() {
  printf("==== SUPERMERCADO STO ANTONIO ====\nMenu Principal\n");
  printf("1. Cadastrar produto\n");
  printf("2. Excluir produto\n");
  printf("3. Buscar produto\n");
  printf("4. Buscar produto por preco\n");
  printf("5. Relatorio\n");
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
    case OP_BUSCAR_PRECO:
      // TODO buscar_produto_preco(p);
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
