#include <stdio.h>
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>

int main();
void crea_cunicoli();
void gioca ();
static void ins_caverna(struct Caverna** primo_cunicolo);
static void canc_caverna(struct Caverna** primo_cunicolo, int cont_cancella);
static void stampa_cunicoli(struct Caverna** primo_cunicolo);
static void quantita_melassa(struct Caverna** cunicolo);
static void back_to_Crea_cunicoli();
static void imprevisto(struct Caverna** cunicolo);
static void avanza( struct Scavatrice** famiglia);
static void abbatti (struct Scavatrice** famiglia, struct Caverna**primo_cunicolo);
 static void menu_gioca(struct Scavatrice**  famiglia, struct Caverna** primo_cunicolo);
static void elimina_lista(struct Caverna** primo_cunicolo);
static void gestione_melassa(struct Scavatrice** famiglia);
static void gestione_imprevisto (struct Scavatrice** famiglia, struct Caverna** primo_cunicolo);
static void gestione_serbatoio (struct Scavatrice** famiglia);
static void gestione_stato (struct Scavatrice** famiglia, struct Caverna** primo_cunicolo);
static void nuovaquantita_melassa(struct Caverna** cunicolo);
static void nuovo_imprevisto(struct Caverna** cunicolo);
static void aggira(struct Caverna** primo_cunicolo, struct Scavatrice** famiglia);
static void gestione_nuovostato (struct Caverna** cunicolo);
static void scontro();
static void reset();
static void fine_gioca();
static void gestione_stato_aggira(struct Caverna** cunicolo);






static struct Caverna* primo_cunicolo_arvais = NULL; //puntatore al primo cunicolo Arvais
static struct Caverna* primo_cunicolo_hartonen = NULL;//puntatore al primo cunicolo Hartonen
static struct Scavatrice* scavatrice_arvais = NULL;
static struct Scavatrice* scavatrice_hartonen = NULL;
static int cont_cancella_arvais = 0;//conta quante caverne Arvais sono state cancellate
static int cont_cancella_hartonen = 0;//conta quante caverne Hartonen sono state inserite
static int stato_hartonen = 0; //indica se sono state inserite tutte le caverne Hartonen
static int stato_arvais = 0;//indica se sono state inserite tutte le caverne Arvais
static char back [30];
static char scelta_dir[30]; //Array per la scelta della direzione
static char scelta_mappa[30]; //array per la scelta della mappa da stampare
static char scelta_cancella[30];//array per scegliere a quale famiglia cancellare l'ultima caverna
static char scelta_re_ins[30];//array per scegliere a quale famiglia re-inserire le caverne dopo che sono state cancellate
static int caverne_arvais = 0;//conta quante caverne Arvais sono state inserite
static int caverne_hartonen = 0;//conta quante caverne Hartonen sono state inserite
static char scelta_gioca[100];//array per la scelta di quale azione compiere nel menu
static char scelta_aggiunta [40];//Array per la scelta dell'aggiunta di melassa
static char scelta_abbatti[40];//array per scegliere dove abbattere
static int serb_arvais = 0; //contiene il puntatore al serbatoio di energia arvais
static int serb_hartonen = 0;//contiene il puntatore al serb di energia di hartonen
static int serb_arvais_raccolta = 0;//contiene il puntatore al serbatoio di raccolta arvais
static int serb_hartonen_raccolta = 0;//contiene il puntatore al serbatoio di raccolta di hartonen





//FUNZIONE MENU CREA CUNICOLI
void crea_cunicoli() {

char scelta [10];
char scelta_famiglia[10];


do {
    system("clear");
    printf("Scegli una delle seguenti opzioni: \n");
    printf("1) Inserisci caverna\n");
    printf("2) Cancella caverna\n");
    printf("3) Stampa cunicoli\n");
    printf("4) Chiudi cunicoli\n");

    scanf("%s", scelta);


    while (scelta[1] != '\0'){
    system("clear");

    printf("Scegli una delle seguenti opzioni: \n");
    printf("1) Inserisci caverna\n");
    printf("2) Cancella caverna\n");
    printf("3) Stampa cunicoli\n");
    printf("4) Chiudi cunicoli\n");

    scanf("%s", scelta);
  }

      switch (scelta[0]) {

              case '1':
                if (stato_arvais == 1 && stato_hartonen == 1) {//controlla se entrambe le mappe di gioco sono state create
                            printf("Le caverne delle due famiglie sono state create sono state già create\n");
                            printf("Premere 1 per tornare al menù\n");
                            printf("Premere 2 per re-inserire le caverna di Arvais\n");
                            printf("Premere 3 per re-inserire le caverne di Hartonen\n");
                              scanf("%s", scelta);
                              switch(scelta[0]){
                              case '1':
                                crea_cunicoli();
                                break;
                              case '2':
                                for(int i = 0; i < 10; i++){
                                  canc_caverna(&primo_cunicolo_arvais, cont_cancella_arvais);
                                }
                                cont_cancella_arvais = 0;
                                for(int i = 0; i < 10; i++){
                                  ins_caverna(&primo_cunicolo_arvais);
                                }
                                printf("Hai inserito le caverne Arvais\n");

                               stato_arvais =1;
                                back_to_Crea_cunicoli();
                                break;

                            case '3':

                              for(int i = 0; i < 10; i++){
                                canc_caverna(&primo_cunicolo_hartonen, cont_cancella_hartonen);
                              }
                              cont_cancella_arvais = 0;
                              for(int i = 0; i < 10; i++){
                                ins_caverna(&primo_cunicolo_hartonen);
                              }
                              printf("Hai inserito le caverne Hartonen\n");

                              stato_hartonen=1;
                              back_to_Crea_cunicoli();
                              break;

                            default:
                                back_to_Crea_cunicoli();
                              }
                            }//Controlla se l'utente ha inserito entrambe le caverne
                    else {//se le caverne di una delle due non sono state inserite
                        if ( cont_cancella_arvais != 0 || cont_cancella_hartonen != 0) {//controlla se ci sono alcune caverne cancellate
                          do{
                            printf("Caverne Arvais cancellate: %d\n", cont_cancella_arvais);
                            printf("Caverne Hartonen cancellate: %d\n", cont_cancella_hartonen);
                            printf("Premere 1 per inserire le caverne mancanti di Arvais\n");
                            printf("Premere 2 per inserire le caverne mancanti di Hartonen\n");
                            scanf("%s", scelta_re_ins);

                              while(scelta_re_ins[1] != '\0'){
                                printf("Caverne Arvais cancellate: %d\n", cont_cancella_arvais);
                                printf("Caverne Hartonen cancellate: %d\n", cont_cancella_hartonen);
                                printf("Premere 1 per inserire le caverne mancanti di Arvais\n");
                                printf("Premere 2 per inserire le caverne mancanti di Hartonen\n");
                                scanf("%s", scelta_re_ins);
                              }

                            switch (scelta_re_ins[0]){
                              case '1':
                              if (cont_cancella_arvais == 0){
                                stato_arvais = 0;
                                printf("non ci sono caverne da re-inserire\n");
                              }
                              else {
                                for(int i = 0; i <cont_cancella_arvais; i++){
                                  ins_caverna(&primo_cunicolo_arvais);

                                }
                                printf("Hai creato i cunicoli degli Arvais\n");
                              }
                                stato_arvais=1;
                                cont_cancella_arvais= 0;
                                back_to_Crea_cunicoli();
                                break;

                              case '2':
                              if (cont_cancella_hartonen == 0){
                                stato_hartonen = 0;
                                printf("non ci sono caverne da re-inserire\n");
                              }
                                else{
                                for(int i = 0; i < cont_cancella_hartonen; i++){
                                  ins_caverna(&primo_cunicolo_hartonen);
                                }
                                printf("Hai creato i cunicoli degli Hartonen\n");
                              }
                                stato_hartonen = 1;
                                cont_cancella_hartonen =0;
                                back_to_Crea_cunicoli();
                                break;

                              default:
                                printf("Scelta non valida\n");
                                break;


                            }
                          }while (scelta_re_ins[0] != 49 && scelta_re_ins[0] != 50);


                            }
                            else {//se non ci sono caverne cancellate
                              do {
                                printf("Scegliere la famiglia da cui iniziare:\n");
                                printf("1) Arvais\n");
                                printf("2) Hartonen\n");
                                scanf("%s", scelta_famiglia);

                              while(scelta_famiglia[1] != '\0'){
                                printf("Scegliere la famiglia da cui iniziare:\n");
                                printf("1) Arvais\n");
                                printf("2) Hartonen\n");
                                scanf("%s", scelta_famiglia);
                                }

                                switch(scelta_famiglia[0]){
                                  case '1':
                                    for(int i = 0; i < 10; i++){
                                      ins_caverna(&primo_cunicolo_arvais);
                                      caverne_arvais += 1;
                                    }
                                    printf("Hai creato i cunicoli degli Arvais\n");
                                    stato_arvais=1;
                                    back_to_Crea_cunicoli();
                                    break;
                                  case '2':
                                    for(int i = 0; i < 10; i++){
                                      ins_caverna(&primo_cunicolo_hartonen);
                                      caverne_hartonen += 1;
                                    }
                                    printf("Hai creato i cunicoli degli Hartonen\n");
                                    stato_hartonen=1;
                                    back_to_Crea_cunicoli();
                                    break;
                                  default:
                                   printf("carattere errato\n" );
                                   break;
                                 }


                                } while (scelta_famiglia[0] != 49 && scelta_famiglia[0] != 50);
                                  }
                                    }
              break;


              case '2': //se l'utente digita "cancella caverna"



                do {
                  printf("Di quale famiglia vuoi cancellare l'ultima caverna inserita?\n");
                  printf("1) Arvais\n");
                  printf("2) Hartonen\n");
                  scanf("%s", scelta_cancella);

                while(scelta_cancella[1] != '\0'){
                  printf("Di quale famiglia vuoi cancellare l'ultima caverna inserita?\n");
                  printf("1) Arvais\n");
                  printf("2) Hartonen\n");
                  scanf("%s", scelta_cancella);
                }


                switch(scelta_cancella[0]){
                case '1':
                  if (caverne_arvais == 0){
                    printf("Non ci sono caverne da poter cancellare\n");
                      stato_arvais = 0;
                  }
                  else {
                    cont_cancella_arvais = cont_cancella_arvais + 1;
                    canc_caverna(&primo_cunicolo_arvais, cont_cancella_arvais);
                    stato_arvais = 0;
                  }
                    back_to_Crea_cunicoli();
                    break;
                case '2':
                  if(caverne_hartonen == 0) {
                      printf("Non ci sono caverne da poter cancellare\n");
                      stato_hartonen = 0;
                  }
                  else {
                    cont_cancella_hartonen = cont_cancella_hartonen + 1;
                    canc_caverna(&primo_cunicolo_hartonen, cont_cancella_hartonen);
                    stato_hartonen = 0;
                  }
                    back_to_Crea_cunicoli();
                    break;
                  default:
                    printf("scelta non valida\n");
                      back_to_Crea_cunicoli();
                    break;
                }

              } while (scelta_cancella[0] != 49 && scelta_cancella[0] != 50);

              break;



              case '3':

                do {
                  printf("Quale mappa vuoi visualizzare?\n");
                  printf("1) Mappa degli Arvais\n");
                  printf("2) Mappa degli Hartonen\n");
                  scanf("%s", scelta_mappa);

                  while(scelta_mappa[1] != '\0'){
                    printf("Quale mappa vuoi visualizzare?\n");
                    printf("1) Mappa degli Arvais\n");
                    printf("2) Mappa degli Hartonen\n");
                    scanf("%s", scelta_mappa);
                  }

                  switch(scelta_mappa[0]){
                    case '1':
                      stampa_cunicoli(&primo_cunicolo_arvais);
                      back_to_Crea_cunicoli();
                      break;
                    case '2':
                      stampa_cunicoli(&primo_cunicolo_hartonen);
                      back_to_Crea_cunicoli();
                      break;
                    default:
                      printf("scelta non valida\n");
                      back_to_Crea_cunicoli();
                      break;
                    }
            } while (scelta_mappa[0] != 49 && scelta_mappa[0] != 50);

              break;

              case '4':

              if (stato_arvais == 1  && stato_hartonen == 1){
                main();
              }
              else {

                printf("Non puoi uscire senza creare i cunicoli di entrambe le famiglie\n");
                back_to_Crea_cunicoli();

            }
              break;

              default:
              printf("\n\nScegli ancora\n");
              break;
            }

        }while (scelta[0] != 49 && scelta[0] != 50 && scelta[0] != 51 && scelta[0] != 52 );
      }

//FUNZIONE CHE INSERISCE LE CAVERNE
static void ins_caverna (struct Caverna** primo_cunicolo) {
char scelta_utente[10];


  Caverna* nuova_caverna = (Caverna*) malloc(sizeof(Caverna));//crea un nuovo nodo caverna

  quantita_melassa(&nuova_caverna);
  imprevisto(&nuova_caverna);

  do {

  system("clear");
  printf("Scegliere la tipologia di caverna che si vuole creare:\n");
  printf("1) Normale\n");
  printf("2) Speciale\n");
  printf("3) Accidentata\n");
  scanf("%s", scelta_utente);

  while (scelta_utente[1] != '\0'){
    system("clear");
    printf("Scegliere la tipologia di caverna che si vuole creare:\n");
    printf("1) Normale\n");
    printf("2) Speciale\n");
    printf("3) Accidentata\n");
    scanf("%s", scelta_utente);

  }
  switch(scelta_utente[0]){
    case '1':
    nuova_caverna -> Stato = NORMALE;
    break;
    case '2':
    nuova_caverna -> Stato = SPECIALE;
    break;
    case '3':
    nuova_caverna -> Stato = ACCIDENTATA;
    break;
    default:
    printf("Scelta non valida\n");
    break;
  }
} while(scelta_utente[0] != 49 && scelta_utente[0] != 50 && scelta_utente[0] != 51);

  nuova_caverna -> avanti = NULL;
  nuova_caverna -> destra = NULL;
  nuova_caverna -> sinistra = NULL;

  if (*primo_cunicolo == NULL) {
  *primo_cunicolo = nuova_caverna;

  }
    else {
      do{
        printf("Dove vuoi posizionare la caverna?\n");
        printf("1) Avanti\n");
        printf("2) Destra\n");
        printf("3) Sinistra\n");
        scanf("%s", scelta_dir);

        while(scelta_dir[1] != '\0'){
          printf("Dove vuoi posizionare la caverna?\n");
          printf("1) Avanti\n");
          printf("2) Destra\n");
          printf("3) Sinistra\n");
          scanf("%s", scelta_dir);
        }

          switch(scelta_dir[0]){
            case '1':
              nuova_caverna -> avanti = *primo_cunicolo;
              *primo_cunicolo = nuova_caverna;
              break;
            case '2':
              nuova_caverna -> destra = *primo_cunicolo;
              *primo_cunicolo = nuova_caverna;
              break;
            case '3':
              nuova_caverna -> sinistra = *primo_cunicolo;
              *primo_cunicolo = nuova_caverna;
              break;
            default:
              printf("inserire un altro valore\n");
            break;
          }

      } while (scelta_dir[0] != 49 && scelta_dir[0] != 50 && scelta_dir[0] != 51);
    }
  return;
}

//FUNZIONE CHE CANCELLA LE CAVERNE
static void canc_caverna(struct Caverna** primo_cunicolo, int cont_cancella){



    if (*primo_cunicolo == NULL) {
      printf("Non ci sono cunicoli\n");
      cont_cancella = 0;
    }
    else {
      if ((*primo_cunicolo) -> avanti != NULL){
      Caverna* temp = (*primo_cunicolo)-> avanti;
      free(*primo_cunicolo);
      *primo_cunicolo = temp;
      printf("\nHai cancellato %d caverne\n", cont_cancella);
    }
    else {
      if ((*primo_cunicolo) -> destra != NULL) {
        Caverna* temp = (*primo_cunicolo)-> destra;
        free(*primo_cunicolo );
        *primo_cunicolo = temp;
        printf("\nHai cancellato %d caverne\n", cont_cancella);
      }
      else {

        Caverna* temp = (*primo_cunicolo)-> sinistra;
        free(*primo_cunicolo);
        *primo_cunicolo = temp;
        printf("\nHai cancellato %d caverne\n", cont_cancella);

      }
    }
  }


    return;
}

//FUNZIONE CHE STAMPA LE MAPPE DI GIOCO
static void stampa_cunicoli(struct Caverna** primo_cunicolo) {



  if (*primo_cunicolo == NULL) {
    printf("\nNon sono state create caverne\n");
  }
    else {
      Caverna* pScan = *primo_cunicolo;

      do {

        switch(pScan-> Stato) {
          case 1:
            printf("\nTipo Caverna: Normale\n");
            printf("Il puntatore al nodo successivo è : %p \n", pScan);

            break;
          case 2:
            printf("\nTipo Caverna: Speciale\n");
            printf("Il puntatore al nodo successivo è : %p\n", pScan);

            break;
          case 3:
            printf("\nTipo Caverna: Accidentata\n");
            printf("Il puntatore al nodo successivo è : %p\n", pScan);

            break;
          default:
            printf("\nScelta non valida\n");
            break;
        }

    if (pScan -> avanti != NULL){
      printf("Direzione caverna: AVANTI\n");
        pScan = pScan -> avanti;
    } else {
      if(pScan -> destra != NULL){
        printf("Direzione caverna: DESTRA\n");
          pScan = pScan -> destra;
      }
      else {
        if (pScan -> sinistra != NULL){
        printf("Direzione caverna: SINISTRA\n");
          pScan = pScan -> sinistra;
        }
        else {
          printf("Direzione non specificata\n");
            pScan = NULL;
        }
      }
    }
  } while(pScan != NULL);// continua finche pScan è diverso da NULL
}
  return;
}

//FUNZIONE CHE RANDOMIZZA LA QUANTITA DELLA MELASSA
static void quantita_melassa(struct Caverna** cunicolo) {


  int num;

  num = rand() % 100;

  if (num >= 0 && num < 50){
    (*cunicolo) -> Melassa = NESSUNA;

    }
    else {
      if (num >= 50 && num < 80) {
        (*cunicolo) -> Melassa = POCA;

      }
      else {
      (*cunicolo) -> Melassa = MOLTA;

    }
  }
}

//FUNZIONE CHE TORNA AL MENU "CREA CUNICOLI"
static void back_to_Crea_cunicoli(){

  do {
    printf("\nPremere 1 per tornare al menu\n");
    scanf("%s", back);

    while(back[1] != '\0'){
      printf("\nPremere 1 per tornare al menu\n");
      scanf("%s", back);
    }

    switch(back[0]){
      case '1':
      crea_cunicoli();
      break;
      default:
      printf("carattere non valido\n");
      break;
    }
  }  while(back[0] != '1');

}

//FUNZIONE CHE RANDOMIZZA L'IMPREVISTO
static void imprevisto(struct Caverna** cunicolo) {



  int num;

  num = rand() % 100;

  if (num >= 0 && num < 50) {
    (*cunicolo) -> Imprevisto = NESSUN_IMPREVISTO;

  }
  else {
    if (num >= 50 && num <= 85){
    (*cunicolo) -> Imprevisto = CROLLO;

  }
    else {
      (*cunicolo) -> Imprevisto = BACO;

    }
  }
}

//FUNZIONE CHE GESTISCE L'OPZIONE GIOCA
void gioca () {


  int conta_turni = 0;


Scavatrice* scavatrice_arvais = (Scavatrice*) malloc(sizeof(Scavatrice));
Scavatrice* scavatrice_hartonen = (Scavatrice*) malloc(sizeof(Scavatrice));
scavatrice_arvais->pos_attuale = primo_cunicolo_arvais;
scavatrice_hartonen->pos_attuale = primo_cunicolo_hartonen;
scavatrice_arvais -> serb_energia = 4;
scavatrice_hartonen ->serb_energia = 4;


for(int i = 0; i < 10; i++) {
  conta_turni++;

  menu_gioca (&scavatrice_arvais, &primo_cunicolo_arvais);
  serb_arvais = scavatrice_arvais -> serb_energia;
  serb_arvais_raccolta = scavatrice_arvais ->serb_raccolta;
  menu_gioca (&scavatrice_hartonen, &primo_cunicolo_hartonen);
  serb_hartonen = scavatrice_hartonen -> serb_energia;
  serb_hartonen_raccolta = scavatrice_hartonen ->serb_raccolta;




}
reset();
fine_gioca();


}

//FUNZIONE PER AVANZARE
static void avanza(struct Scavatrice** famiglia){

Caverna* pos_Scavatrice = (*famiglia) -> pos_attuale;


if(pos_Scavatrice -> avanti != NULL){
  printf("\nCi siamo spostati in AVANTI\n");
  (*famiglia)->pos_attuale =(*famiglia)-> pos_attuale-> avanti;
}//gestisce la poszione della caverna
    else {
  if(pos_Scavatrice -> sinistra != NULL){
    printf("\nCi siamo spostati a SINISTRA\n");
    (*famiglia)->pos_attuale =(*famiglia) ->pos_attuale -> sinistra;
  }
  else {
    if(pos_Scavatrice -> destra != NULL){
      printf("\nCi siamo spostati a DESTRA\n");
    (*famiglia)->pos_attuale = (*famiglia) -> pos_attuale -> destra;
    }
    else {
    (*famiglia)->pos_attuale = NULL;
      printf("\nla direzione non è specificata\n");

    }
  }
}

}

//FUNZIONE PER ABBATTERE
static void abbatti (struct Scavatrice** famiglia, struct Caverna** primo_cunicolo)  {


Caverna* nuova_caverna = (Caverna*) malloc(sizeof(Caverna));

nuovaquantita_melassa(&nuova_caverna);
nuovo_imprevisto(&nuova_caverna);
gestione_nuovostato(&nuova_caverna);


nuova_caverna -> avanti = NULL;
nuova_caverna -> sinistra = NULL;
nuova_caverna -> destra = NULL;

Caverna* pos_Scavatrice = (*famiglia)->pos_attuale;

if(pos_Scavatrice -> destra != NULL){
  printf("\nLa caverna in cui ci troviamo è situata a destra\n");
  printf("Perciò, possiamo abbattere solo in avanti e a sinistra\n");
  do {
  printf("\nIn che direzione desideri abbattere?\n");
  printf("1) Avanti\n");
  printf("2) Sinistra\n");
  scanf("%s", scelta_abbatti);

  while(scelta_abbatti[1] != '\0'){
    printf("\nIn che direzione desideri abbattere?\n");
    printf("1) Avanti\n");
    printf("2) Sinistra\n");
    scanf("%s", scelta_abbatti);
  }

  switch(scelta_abbatti[0]){
    case '1':
      printf("\nHai deciso di abbattere una caverna in avanti\n");
      elimina_lista(&pos_Scavatrice -> destra);
      pos_Scavatrice -> destra = NULL;
      pos_Scavatrice-> avanti = nuova_caverna;

      break;
    case '2':
      printf("\nHai deciso di abbattere una caverna a sinistra\n");
      elimina_lista(&pos_Scavatrice -> destra);
      pos_Scavatrice -> destra = NULL;
      pos_Scavatrice -> sinistra = nuova_caverna;

      break;
    default:
      printf("Digitare un altro numero\n");
      scelta_abbatti[0] = 52;
      break;
    }

  }while(scelta_abbatti[0] != 49 && scelta_abbatti[0] != 50);


} else if(pos_Scavatrice -> sinistra != NULL){
      printf("\nLa caverna in cui ci troviamo è situata a sinistra\n");
      printf("Perciò, possiamo abbattere solo in avanti e a destra\n");
      do {
      printf("\nIn che direzione desideri abbattere?\n");
      printf("1) Avanti\n");
      printf("2) Destra\n");
      scanf("%s", scelta_abbatti);

      while(scelta_abbatti[1] != '\0'){
        printf("\nIn che direzione desideri abbattere?\n");
        printf("1) Avanti\n");
        printf("2) Destra\n");
        scanf("%s", scelta_abbatti);
      }

      switch(scelta_abbatti[0]){
        case '1':
          printf("\nHai deciso di abbattere una caverna in avanti\n");
          elimina_lista(&pos_Scavatrice -> sinistra);
          pos_Scavatrice -> sinistra = NULL;
          pos_Scavatrice-> avanti = nuova_caverna;
          break;
        case '2':
          printf("\nHai deciso di abbattere una caverna a destra\n");
          elimina_lista(&pos_Scavatrice -> sinistra);
          pos_Scavatrice ->sinistra = NULL;
          pos_Scavatrice -> destra = nuova_caverna;
          break;
        default:
          printf("\nScelta non valida\n");
          scelta_abbatti[0] = 52;
          break;
        }

    } while(scelta_abbatti[0] != 49 && scelta_abbatti[0] != 50);

  } else  if(pos_Scavatrice -> avanti != NULL){
        printf("\nLa caverna in cui ci troviamo è situata in avanti\n");
        printf("Perciò, possiamo abbattere solo a destra e a sinistra\n");
        do {
        printf("\nIn che direzione desideri abbattere?\n");
        printf("1) Destra\n");
        printf("2) Sinistra\n");
        scanf("%s", scelta_abbatti);

        while(scelta_abbatti[1] != '\0'){
          printf("\nIn che direzione desideri abbattere?\n");
          printf("1) Destra\n");
          printf("2) Sinistra\n");
          scanf("%s", scelta_abbatti);
        }

        switch(scelta_abbatti[0]){
          case '1':
            printf("\nHai deciso di abbattere una caverna a destra\n");
            elimina_lista(&pos_Scavatrice -> avanti);
            pos_Scavatrice ->avanti = NULL;
            pos_Scavatrice-> destra = nuova_caverna;
            break;
          case '2':
            printf("\nHai deciso di di abbatere una caverna a sinistra\n");
            elimina_lista(&pos_Scavatrice -> avanti);
            pos_Scavatrice -> avanti = NULL;
            pos_Scavatrice -> sinistra = nuova_caverna;
            break;
          default:
            printf("\nScelta non valida\n");
            scelta_abbatti[0] = 52;
            break;
            }

          } while(scelta_abbatti[0] != 49 && scelta_abbatti[0] != 50);

        } else {

          do {
          printf("\nIn che direzione desideri abbattere?\n");
          printf("1) Avanti\n");
          printf("2) Destra\n");
          printf("3) Sinistra\n");
          scanf("%s", scelta_abbatti);

          while(scelta_abbatti[1] != '\0'){
            printf("\nIn che direzione desideri abbattere?\n");
            printf("1) Avanti\n");
            printf("2) Destra\n");
            printf("3) Sinistra\n");
            scanf("%s", scelta_abbatti);
          }

          switch(scelta_abbatti[0]){
            case '1':
              printf("\nHai deciso di abbattere una caverna in avanti\n");
              pos_Scavatrice-> avanti = nuova_caverna;
              break;
            case '2':
              printf("\nHai deciso di abbattere una caverna a destra\n ");
              pos_Scavatrice -> destra = nuova_caverna;
              break;
            case '3':
              printf("\nHai deciso di abbattere una caverna a sinistra\n ");
              pos_Scavatrice -> sinistra = nuova_caverna;
              break;
            default:
              printf("\nScelta non valida\n");
              scelta_abbatti[0] = 56;
              break;
          }

      } while(scelta_abbatti[0] != 49 && scelta_abbatti[0] != 50 && scelta_abbatti[0] != 51);

  }

}

//FUNZIONE CHE ELIMINA LA MAPPA
static void elimina_lista(struct Caverna** primo_cunicolo){

  Caverna* curr = *primo_cunicolo;
  Caverna *succ;

  while ( curr != NULL ){
    if(curr -> avanti != NULL){
    succ = curr -> avanti;
    free(curr);
    curr = succ;
      }
      else{
        if (curr ->destra != NULL){
          succ = curr -> destra;
          free(curr);
          curr = succ;
        }
          else {
            if (curr ->sinistra != NULL) {
            succ =curr -> sinistra;
            free(curr);
            curr = succ;
          }
          else {
            curr = NULL;
          }
}
}
}
}

//MENU DI SCELTE DELLA FUNZIONE GIOCA
static void menu_gioca(struct Scavatrice**  famiglia, struct Caverna** primo_cunicolo){

  int p_scavatrice = 0;
  int num;


   printf("\n\nBenvenuto %s\n",(primo_cunicolo_arvais==(*primo_cunicolo))? "Arvais":"Hartonen" );

  do {


  printf("Scegli l'azione da eseguire:\n");
  printf("1) Avanza\n");
  printf("2) Abbatti\n");
  printf("3) Aggira\n");
  printf("4) Uscita\n");

  scelta_gioca[0] = '\0';
  scanf("%s", scelta_gioca);

  while (scelta_gioca[1] != '\0') {
  printf("Scelta non valida\n");
  printf("Scegli l'azione da eseguire:\n");
  printf("1) Avanza\n");
  printf("2) Abbatti\n");
  printf("3) Aggira\n");
  printf("4) Uscita\n");

  scelta_gioca[0] = '\0';

  scanf("%s",  scelta_gioca);
  }

  switch (scelta_gioca[0]) {
  case '1':

  num =  1 + rand() %100;

    p_scavatrice= p_scavatrice + 3;


  if (num > 0 && num < p_scavatrice){
    printf("Le due scavatrici si sono incontrate\n");
    printf("Vincerà la famiglia che ha maggior energia\n");
    scontro();
  }

  else  if ((*famiglia)->pos_attuale ->Imprevisto == CROLLO) {
    printf("Si è verificato un crollo\n");
    printf("Puoi solo aggirare\n");
    scelta_gioca[0] = 55;
  }
  else {
  if((*famiglia)-> pos_attuale -> avanti == NULL && (*famiglia)-> pos_attuale -> destra == NULL && (*famiglia)-> pos_attuale -> sinistra == NULL ) {
      printf("Non puoi avanzare\n");
      printf("Puoi abbattere una caverna\n");
      scelta_gioca[0] = 55;
    }

    else {
    avanza(famiglia);
    gestione_stato (famiglia, primo_cunicolo);

    gestione_melassa(famiglia);
    gestione_imprevisto(famiglia, primo_cunicolo);

    gestione_serbatoio(famiglia);

  }
}

    break;
  case '2':
p_scavatrice= p_scavatrice + 3;
  if ((*famiglia)->pos_attuale -> Imprevisto == CROLLO) {
    printf("Si è verificato un crollo\n");
    printf("Puoi solo aggirare\n");
    scelta_gioca[0] = 55;
  }
  else {
    abbatti(famiglia, primo_cunicolo);
    (*famiglia)->serb_energia--;

    if((*famiglia) -> serb_energia < 0){
    printf("\n\nLa famiglia %s ha perso in quanto ha esaurito la sua energia\n",(primo_cunicolo_arvais==(*primo_cunicolo))? "Arvais":"Hartonen" );
      printf("La famiglia %s ha vinto\n", (primo_cunicolo_arvais==(*primo_cunicolo))? "Hartonen":"Arvais");

      int scelta_u;
      do {

      printf("Premi 1 per tornare al menu principale\n");
      printf("premi 0 per uscire dal gioco\n");
      scanf("%d", &scelta_u);

      if(scelta_u != 0 && scelta_u != 1)
        printf("Errore di inserimento, reinserire la tua scelta\n");


      } while(scelta_u != 0 && scelta_u != 1);
      if (scelta_u == 0){
      printf("Hai scelto di uscire dal gioco\n");
      printf("GAME OVER!\n");
      exit(0);
    }
    else {
      printf("Hai scelto di tornare al menù iniziale\n");
      reset();
      main();
    }
    }
  }

    break;
  case '3':
  p_scavatrice= p_scavatrice + 3;
  if ((*famiglia)->pos_attuale -> Imprevisto != CROLLO) {
    printf("Non posso usare la funzione aggira\n");
    scelta_gioca[0] = 55;
  }
  else {
    printf("Hai aggirato la caverna crollata\n");
    aggira(primo_cunicolo, famiglia);

  }
    break;

    case '4':

    if ((*famiglia) -> pos_attuale -> Stato == USCITA){
      printf("la famiglia %s ha trovato l'uscita\n", (primo_cunicolo_arvais==(*primo_cunicolo))? "Arvais": "Hartonen");
      printf("Il gioco è terminato\n");

      int scelta_u;
      do {

      printf("Premi 1 per tornare al menu principale\n");
      printf("premi 0 per uscire dal gioco\n");
      scanf("%d", &scelta_u);

      if(scelta_u != 0 && scelta_u != 1)
        printf("Errore di inserimento, reinserire la tua scelta\n");


      } while(scelta_u != 0 && scelta_u != 1);
      if (scelta_u == 0){
      printf("Hai scelto di uscire dal gioco\n");
      printf("GAME OVER!\n");
      exit(0);
    }
    else {
      printf("Hai scelto di tornare al menù iniziale\n");
      main();
    }
    }
    else {
      printf("Non puoi uscire\n");
      scelta_gioca[0] = 55;
    }
    break;


  default:
    printf("Scelta non valida\n");
    break;
  }

} while (scelta_gioca[0] != 49 && scelta_gioca[0] != 50 && scelta_gioca[0] != 51 && scelta_gioca[0] != 52);

}

//GESTISCE LA MELASSA NELLE CAVERNE
static void gestione_melassa(struct Scavatrice** famiglia){




        if((*famiglia)-> pos_attuale-> Melassa == NESSUNA){
          printf("\nLa caverna non contiene melassa\n");

        }//gestisce la quantità di melassa nella caverna
        else if  ((*famiglia)-> pos_attuale -> Melassa == POCA){
              printf("\nLa caverna contiene un'unità di melassa\n");
              do{
              printf("Dove vuoi aggiungere la melassa?\n");
              printf("1) Serbatoio di energia\n");
              printf("2) Serbatoio di raccolta\n");
              scanf("%s", scelta_aggiunta);
              while (scelta_aggiunta[1] != '\0' ){
              printf("Dove vuoi aggiungere la melassa?\n");
              printf("1) Serbatoio di energia\n");
              printf("2) Serbatoio di raccolta\n");
              scanf("%s", scelta_aggiunta);
              }
              switch(scelta_aggiunta[0]){
                case '1':
                (*famiglia)->serb_energia++;
                break;
                case '2':
                (*famiglia)->serb_raccolta++;
                break;
                default:
                printf("Scelta non valida\n");
                scelta_aggiunta[0] = 52;
                break;
              }

            } while (scelta_aggiunta[0] != 49 && scelta_aggiunta[0] != 50);
            }
            else {

            printf("\nLa caverna contiene tre unità di melassa\n");
            do{
            printf("Dove vuoi aggiungere la melassa?\n");
            printf("1) Serbatoio di energia\n");
            printf("2) Serbatoio di raccolta\n");
            scanf("%s", scelta_aggiunta);
            while (scelta_aggiunta[1] != '\0' ){
            printf("Dove vuoi aggiungere la melassa?\n");
            printf("1) Serbatoio di energia\n");
            printf("2) Serbatoio di raccolta\n");
            scanf("%s", scelta_aggiunta);
            }
            switch(scelta_aggiunta[0]){
              case '1':
              (*famiglia)->serb_energia = (*famiglia) -> serb_energia + 3;
              break;
              case '2':
              (*famiglia)->serb_raccolta = (*famiglia) -> serb_energia + 3;
              break;
              default:
              printf("Scelta non valida\n");
              scelta_aggiunta[0] = 52;
              break;
            }

          } while (scelta_aggiunta[0] != 49 && scelta_aggiunta[0] != 50);
          }
        }

//GESTISCE L'IMPREVISTO NELLE CAVERNE
static void gestione_imprevisto (struct Scavatrice** famiglia, struct Caverna** primo_cunicolo){



  if  ((*famiglia)-> pos_attuale ->Imprevisto == NESSUN_IMPREVISTO){
        printf("\nNessun imprevisto\n");
      }//gestisce l'imprevisto
        else if ((*famiglia) -> pos_attuale->Imprevisto == CROLLO) {
            printf("\nSi è verificato un crollo\n");
            printf("Per uscire dalle macerie è necessario un prelievo dal serbatoio di energia\n");
            (*famiglia)->serb_energia--;

            if((*famiglia) -> serb_energia < 0){
            printf("\n\nLa famiglia %s ha perso\n",(primo_cunicolo_arvais==(*primo_cunicolo))? "Arvais":"Hartonen" );
              printf("La famiglia %s ha vinto\n", (primo_cunicolo_arvais==(*primo_cunicolo))? "Hartonen":"Arvais");

              int scelta_u;
              do {

              printf("Premi 1 per tornare al menu principale\n");
              printf("premi 0 per uscire dal gioco\n");
              scanf("%d", &scelta_u);

              if(scelta_u != 0 && scelta_u != 1)
                printf("Errore di inserimento, reinserire la tua scelta\n");


              } while(scelta_u != 0 && scelta_u != 1);
              if (scelta_u == 0){
              printf("Hai scelto di uscire dal gioco\n");
              printf("GAME OVER!\n");
              exit(0);
            }
            else {
              printf("Hai scelto di tornare al menù iniziale\n");
              reset();
              main();
            }
            }
            }
              else {

                printf("\nOps! Abbiamo incontrato un Baco\n");
                printf("Ci ha risucchiato tutte le riserve nei nostri due serbatoi\n");
                (*famiglia) -> serb_energia = 0;
                (*famiglia) ->serb_raccolta = 0;

            }
      }

//GESTISCE I SERBATOI DELLE FAMIGLIE
static void gestione_serbatoio (struct Scavatrice** famiglia){

  if ((*famiglia)->serb_energia > 4) {
    (*famiglia)->serb_energia = 4;

    printf("\nIl tuo serbatoio di energia è di 4 unità\n");
  }

  else {

    printf("\nIl tuo serbatoio di energia è di %d unità\n", (*famiglia)->serb_energia);
  }

  if((*famiglia) -> serb_raccolta > 10){
    (*famiglia) ->  serb_raccolta = 10;
    printf("\nIl tuo serbatoio di energia è di 10 unità\n");
  }
  else {
    printf("\nIl tuo serbatoio di raccolta è di %d unità", (*famiglia)-> serb_raccolta);
  }
}

//GESTISCE LO STATO DELLE CAVERNE
static void gestione_stato (struct Scavatrice** famiglia, struct Caverna** primo_cunicolo) {
  Caverna* pos_Scavatrice = (*famiglia) -> pos_attuale;
  switch(pos_Scavatrice -> Stato){

      case 1:
      printf("La caverna che abbiamo incontrato è di tipo NORMALE\n");
      break;

      case 2:
      printf("La caverna che abbiamo incontrato è di tipo SPECIALE\n");
      printf("Il serbatoio di energia verrà incrementato di un unità\n");
      (*famiglia)->serb_energia++;

      break;

      case 3:
      printf("Abbiamo incontrato una caverna di tipo ACCIDENTATA\n");
      printf("Essa ci ha portato all' utilizzo di un' unità di melassa\n");
      (*famiglia)->serb_energia--;

                  if((*famiglia) -> serb_energia < 0){
                  printf("\n\nLa famiglia %s ha perso in quanto ha esaurito la sua energia\n",(primo_cunicolo_arvais==(*primo_cunicolo))? "Arvais":"Hartonen" );
                    printf("La famiglia %s ha vinto\n", (primo_cunicolo_arvais==(*primo_cunicolo))? "Hartonen":"Arvais");

                    int scelta_u;
                    do {

                    printf("Premi 1 per tornare al menu principale\n");
                    printf("premi 0 per uscire dal gioco\n");
                    scanf("%d", &scelta_u);

                    if(scelta_u != 0 && scelta_u != 1)
                      printf("Errore di inserimento, reinserire la tua scelta\n");


                    } while(scelta_u != 0 && scelta_u != 1);
                    if (scelta_u == 0){
                    printf("Hai scelto di uscire dal gioco\n");
                    printf("GAME OVER!\n");
                    exit(0);
                  }
                  else {
                    printf("Hai scelto di tornare al menù iniziale\n");
                    reset();
                    main();
                  }
                  }


      break;

      default:
      printf("Scelta non valida \n");
      break;
    }
}

//RANDOMIZZA LA QUANTITA DI MELASSA PER LA NUOVA CAVERNA ABBATTUTA
static void nuovaquantita_melassa(struct Caverna** cunicolo) {


  int num;

  num = rand() % 100;

  if (num >= 0 && num < 40){
    (*cunicolo) -> Melassa = NESSUNA;

    }
    else {
      if (num >= 40 && num < 80) {
        (*cunicolo) -> Melassa = POCA;

      }
      else {
      (*cunicolo) -> Melassa = MOLTA;

    }
  }
}

//RANDOMIZZA IL NUOVO IMPREVISTO PER LA NUOVA CAVERNA ABBATTUTA
static void nuovo_imprevisto(struct Caverna** cunicolo) {

  int num;

  num = rand() % 100;

  if (num >= 0 && num < 40) {
    (*cunicolo) -> Imprevisto = NESSUN_IMPREVISTO;

  }
  else {
    if (num >= 40 && num <= 80){
    (*cunicolo) -> Imprevisto = CROLLO;

  }
    else {
      (*cunicolo) -> Imprevisto = BACO;

    }
  }
}

//GESTISCE LA FUNZIONE AGGIRA
static void aggira(struct Caverna** primo_cunicolo, struct Scavatrice** famiglia){

  Caverna* nuova_caverna = (Caverna*)malloc(sizeof(Caverna));

  quantita_melassa(&nuova_caverna);
  imprevisto(&nuova_caverna);
  gestione_stato_aggira(&nuova_caverna);




  if ((*famiglia)->pos_attuale->avanti != NULL) {
    nuova_caverna -> avanti = (*famiglia)->pos_attuale->avanti;
    nuova_caverna -> sinistra = NULL;
    nuova_caverna -> destra = NULL;
  }
  else if ((*famiglia)->pos_attuale -> destra != NULL){
    nuova_caverna -> destra = (*famiglia)->pos_attuale->destra;
    nuova_caverna -> sinistra = NULL;
    nuova_caverna -> avanti = NULL;
  }
  else if ((*famiglia)->pos_attuale -> sinistra != NULL){
    nuova_caverna -> sinistra = (*famiglia)->pos_attuale-> sinistra;
    nuova_caverna ->destra = NULL;
    nuova_caverna -> avanti = NULL;
} else {
  nuova_caverna -> sinistra = NULL;
  nuova_caverna ->destra = NULL;
  nuova_caverna -> avanti = NULL;
}


free((*famiglia)->pos_attuale);
(*famiglia)->pos_attuale = nuova_caverna;
primo_cunicolo = &nuova_caverna;



}

//GESTISCE LO STATO DELLE NUOVE CAVERNE ABBATTUTE
static void gestione_nuovostato (struct Caverna** cunicolo){

  int p_scavatrice=0, p_accidentata=20, p_normale, p_speciale, p_uscita=0;
  int num;

  num=1+rand()%100;

  p_scavatrice=p_scavatrice+3;
  p_uscita=p_uscita+5;
  p_normale = (100-p_accidentata-p_uscita)/2;
  p_speciale = (100-p_accidentata-p_uscita)/2;


        if (num>1 && num <=20){
            /*printf("La nuova caverna è di tipo ACCIDENTATA\n");*/
            (*cunicolo)  -> Stato = ACCIDENTATA;
          }
         else if (num>20 && num <=(20+p_speciale)){
          /*  printf("La nuova caverna è di tipo NORMALE\n");*/
            (*cunicolo) -> Stato =NORMALE;

          }
        else if (num>(20+p_speciale) && num <=(20+p_speciale+p_normale)){
          /*  printf("La nuova caverna è di tipo SPECIALE\n");*/
            (*cunicolo)  -> Stato = SPECIALE;

          }
        else if (num>(20+p_speciale+p_normale) && num <=100){
          /*  printf("Hai incontrato l'Uscita\n");*/
            (*cunicolo) -> Stato = USCITA;

          }

}

//GESTISCE LO SCONTRO QUANDO LE SCAVATRICE SI INCONTRANO
static void scontro(){

  if ( serb_arvais > serb_hartonen)
    printf("\nLa famiglia Arvais ha vinto lo scontro\n");
    else
    printf("\nLa famiglia Hartonen ha vinto lo scontro\n");

    int scelta_u;
    do {

    printf("Premi 1 per tornare al menu principale\n");
    printf("premi 0 per uscire dal gioco\n");
    scanf("%d", &scelta_u);
    if(scelta_u != 0 && scelta_u != 1)
      printf("Errore di inserimento, reinserire la tua scelta\n");


    } while(scelta_u != 0 && scelta_u != 1);
    if (scelta_u == 0){
    printf("Hai scelto di uscire dal gioco\n");
    exit(0);
    }
    else {
    printf("Hai scelto di tornare al menù iniziale\n");
    reset();
    main();
    }
  }

//RESETTA TUTTO ALLA FINE DEL GIOCO
static void reset(){
      cont_cancella_arvais = 0;
      cont_cancella_hartonen = 0;
      stato_hartonen = 0;
      stato_arvais = 0;
      free (scavatrice_arvais) ;
      scavatrice_arvais = NULL;
      free (scavatrice_hartonen) ;
      scavatrice_hartonen = NULL;
      free (primo_cunicolo_arvais);
      primo_cunicolo_arvais = NULL;
      free (primo_cunicolo_hartonen);
      primo_cunicolo_hartonen = NULL;
      stato_arvais = 0;
      stato_hartonen = 0;
      caverne_arvais = 0;
      caverne_hartonen = 0;
    

    }

//FUNZIONE CHE SI ATTIVA SOLO SE ENTRAMBE LE FAMIGLIA FINISCONO IL GIOCO
static void fine_gioca() {
  printf("\n\nSiete entrambi arrivati alla fine del gioco\n");
  printf("Vincerà la famiglia che ha piu melassa nel serbatoio di raccolta\n");
      if ( serb_arvais_raccolta > serb_hartonen_raccolta){
        printf("\nLa famiglia Arvais ha vinto lo scontro\n");
      }
        else{
        printf("\nLa famiglia Hartonen ha vinto lo scontro\n");
}
        int scelta_u;
        do {

        printf("Premi 1 per tornare al menu principale\n");
        printf("premi 0 per uscire dal gioco\n");
        scanf("%d", &scelta_u);
        if(scelta_u != 0 && scelta_u != 1)
          printf("Errore di inserimento, reinserire la tua scelta\n");


        } while(scelta_u != 0 && scelta_u != 1);
        if (scelta_u == 0){
        printf("Hai scelto di uscire dal gioco\n");
        printf("GAME OVER!!\n");
        exit(0);
        }
        else {
        printf("Hai scelto di tornare al menù iniziale\n");
        reset();
        main();
        }

    }

//RANDOMIZZA LO STATO DELLE NUOVE CAVERNE AGGIRATE
static void gestione_stato_aggira(struct Caverna** cunicolo){

  int num;

  num = 1 + rand() % 100;

  if (num > 0 && num <= 40){
    (*cunicolo) -> Stato =NORMALE;
  }
  else if (num > 40 && num < 75 ){
    (*cunicolo) -> Stato = ACCIDENTATA;
  }
  else {
    (*cunicolo)-> Stato = SPECIALE;
  }
}
