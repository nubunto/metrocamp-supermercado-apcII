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

int Produtos_buscar_genero(Produtos, char*, void*);
int Produtos_buscar_nome(Produtos, char*, void*);
int Produtos_buscar_ano(Produtos, int, void*);
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
  char ano_buf[4];
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

void buscar_produto_preco(Produtos);
void relatorio(Produtos p) {
  int i = 0;
  for(i = 0; i < p.lim; i++) {
    printf("Codigo: %d -- Nome: %s -- Genero: %s -- Ano: %d -- Preco: %f\n", p.ps[i].codigo, p.ps[i].nome, p.ps[i].genero, p.ps[i].ano, p.ps[i].preco);
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
  p.ps = malloc(sizeof(Produto)*MAX_PRODUCTS);

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
      // TODO buscar_produto(p);
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
