#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crea_cunicoli();
void gioca();
int cunicoli = 0;

int main () {
time_t t;
srand((unsigned)time(&t));

char scelta [100];


do {
  system("clear");
  printf("********SABBIE*********\n");
  printf("Scegli una delle seguenti opzioni: \n");
  printf("1) Crea cunicoli\n");
  printf("2) Gioca\n");
  printf("3) Termina gioco\n");
  scanf("%s", scelta );


  while (scelta[1] != '\0'){
  system("clear");
  printf("Scelta non valida\n");
  printf("********SABBIE*********\n");
  printf("Scegli una delle seguenti opzioni: \n");
  printf("1) Crea cunicoli\n");
  printf("2) Gioca\n");
  printf("3) Termina gioco\n");
  scanf("%s", scelta );
}

    switch (scelta[0]) {
      case '1':
      cunicoli = 1;
      crea_cunicoli();
      break;
      case '2':
      if(cunicoli == 0){
        scelta[0] = 55;
        }
        else {
          cunicoli = 0;
          gioca();
        }

      break;
      case '3':
      printf("Gioco terminato\n");
      exit(0);
      break;
      default:
      printf("\n\nScelta non valida\n");
      break;

      }

  }


  while (scelta[0] != 49 && scelta[0] != 50 && scelta[0] != 51  );

}
