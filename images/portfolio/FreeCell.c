#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct no
{
  short numero;
  char naipe;
  struct no *prox;
} stCarta;

stCarta *primMesa[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
stCarta *primNaipe[4] = {NULL, NULL, NULL, NULL};
stCarta *temp[4] = {NULL, NULL, NULL, NULL};
stCarta *primMonte = NULL;

void geraBaralho(void)
{
  int i, j;

  for (i = 3; i < 7; i++)
  {
    for (j = 1; j < 14; j++)
    {
      stCarta *baralho = (stCarta *)malloc(sizeof(stCarta));

      baralho->numero = j;
      baralho->naipe = i;
      baralho->prox = primMonte;
      primMonte = baralho;
    }
  }
}

void embaralhaBaralho()
{
  int cont, pos;
  stCarta *aux;
  for (int x = 0; x < 1000; x++)
  {
    cont = 0;
    stCarta *ant = NULL;
    stCarta *atual = primMonte;
    pos = rand() % 52;
    while (cont < pos)
    {
      ant = atual;
      atual = atual->prox;
      cont++;
    }
    if (pos == 0)
    {
      x--;
    }
    else
    {
      ant->prox = atual->prox;
      atual->prox = primMonte;
      primMonte = atual;
    }
  }
}

void distribuirMesa(void)
{
  int i, j;
  stCarta *atual = primMonte;
  stCarta *aux = NULL;
  stCarta *ult = NULL;
  for (i = 0; i < 8; i++)
  {
    if (i < 4)
    {
      aux = atual;
      for (j = 0; j < 7; j++)
      {
        ult = atual;
        atual = atual->prox;
      }
      ult->prox = NULL;
      primMesa[i] = aux;
    }
    else
    {
      aux = atual;
      for (j = 0; j < 6; j++)
      {
        ult = atual;
        atual = atual->prox;
      }
      ult->prox = NULL;
      primMesa[i] = aux;
    }
  }
}

void imprime()
{
  int i;
  stCarta *atual = primMesa[0];
  stCarta *aux = NULL;

  printf("[TEMP]=");
  for (i = 0; i < 4; i++)
  {
    if (temp[i] != NULL)
    {
      printf(" %d-[%d/%c] ", i, temp[i]->numero, temp[i]->naipe);
    }
    else
    {
      printf(" %d-[ ] ", i);
    }
  }
  printf("\n");
  for (i = 0; i < 4; i++)
  {
    printf("[NAIPE %d]= ", i);
    aux = primNaipe[i];
    while (aux != NULL)
    {
      printf("[%.2d/%c] ", aux->numero, aux->naipe);
      aux = aux->prox;
    }
    printf("\n");
  }
  printf("\n");

  for (i = 0; i < 8; i++)
  {
    printf("[MESA %d] = ", i);
    while (atual != NULL)
    {
      printf("[%.2d/%c] ", atual->numero, atual->naipe);
      atual = atual->prox;
    }
    printf("\n");
    atual = primMesa[i + 1];
  }
}

void moveMesaTemp()
{
  int m = 0, t = 0;
  stCarta *carta = NULL;
  printf("De qual pilha na mesa a carta deve ser retirada: ");
  scanf("%d", &m);

  printf("Qual a posicao voce quer inserir no temporario: ");
  scanf("%d", &t);
  if ((m >= 0) && (m < 8) && (t >= 0) && (t < 4))
  {
    carta = primMesa[m];
    primMesa[m] = primMesa[m]->prox;
    temp[t] = carta;
  }
}

void moveTempMesa()
{
  int m = 0, t = 0;
  printf("Qual posicao temporario sera utilizada: ");
  scanf("%d", &t);

  printf("Em qual mesa a carta deve ser inserida: ");
  scanf("%d", &m);

  if ((m >= 0) && (m < 8) && (t >= 0) && (t < 4) && (temp[t] != NULL))
  {
    if (temp[t]->numero == (primMesa[m]->numero) - 1)
    {
      if (((temp[t]->naipe == 3) && (primMesa[m]->naipe != 4) && (primMesa[m]->naipe != 3)) ||
          ((temp[t]->naipe == 4) && (primMesa[m]->naipe != 3) && (primMesa[m]->naipe != 4)) ||
          ((temp[t]->naipe == 5) && (primMesa[m]->naipe != 6) && (primMesa[m]->naipe != 5)) ||
          ((temp[t]->naipe == 6) && (primMesa[m]->naipe != 5) && (primMesa[m]->naipe != 6)))
      {
        temp[t]->prox = primMesa[m];
        primMesa[m] = temp[t];
        temp[t] = NULL;
      }
      else
      {
        printf("\nERRO PARA INSERIR O NAIPE\n\n");
      }
    }
    else
    {
      printf("\nERRO PARA INSERIR O NUMERO\n\n");
    }
  }
  else
  {
    printf("\nERRO PARA INSERIR NA MESA\n\n");
  }
}

void moveMesaNaipe(void)
{
  int m = 0, n = 0;
  stCarta *thaty = NULL;
  printf("Qual mesa sera retirada a carta:\n");
  scanf("%d", &m);
  printf("Em qual posicao do Naipe inserida:\n");
  scanf("%d", &n);
  if ((primNaipe[n] == NULL) && (primMesa[m]->numero == 1))
  {
    primNaipe[n] = primMesa[m];
    primMesa[m] = primMesa[m]->prox;
    primNaipe[n]->prox = NULL;
  }
  else
  {
    if (primNaipe[n] != NULL)
    {
      if ((primMesa[m]->numero == (primNaipe[n]->numero) + 1) && (primMesa[m]->naipe == primNaipe[n]->naipe))
      {
        thaty = primMesa[m];
        primNaipe[n]->prox = primMesa[m];
        primMesa[m] = primMesa[m]->prox;
        thaty->prox = NULL;
      }
      else
        printf("ERRO DE POSICAO OU DE CARTA\n");
    }
    else
      printf("ERRO DE POSICAO OU DE CARTA\n");
  }
}

int main(int argc, char *argv[])
{
  int op = 0;
  srand(time(NULL));
  geraBaralho();
  embaralhaBaralho();
  distribuirMesa();
  while (op != 4)
  {
    imprime();
    printf("\n------------------\n");
    printf("\n");
    printf("(1)Move Mesa-Naipe\n");
    printf("(2)Move Mesa-Temp\n");
    printf("(3)Move Temp-Mesa\n");
    printf("(4)Sair\n");
    printf("\n");
    printf("Opcao: ");
    scanf("%d", &op);
    getchar();
    switch (op)
    {
    case 1:
      moveMesaNaipe();
      break;
    case 2:
      moveMesaTemp();
      break;
    case 3:
      moveTempMesa();
      break;
    default:
      printf("Opcao Invalida.\n");
      break;
    }
  }
  return 0;
}