#include <stdio.h>

enum Quantita_melassa {NESSUNA , POCA, MOLTA = 3};
enum Tipo_imprevisto {NESSUN_IMPREVISTO, CROLLO, BACO};
enum Tipo_Caverna {NORMALE = 1,SPECIALE = 2, ACCIDENTATA = 3, USCITA};



struct Scavatrice {

  struct Caverna *pos_attuale;
  int serb_raccolta ;
  int serb_energia ;

};
typedef struct Scavatrice Scavatrice;




struct Caverna {

  struct Caverna *avanti;
  struct Caverna *sinistra;
  struct Caverna *destra;
  enum Quantita_melassa Melassa;
  enum Tipo_imprevisto Imprevisto;
  enum Tipo_Caverna Stato;


};
typedef struct Caverna Caverna;
