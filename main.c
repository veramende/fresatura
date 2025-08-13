#include <stdio.h>

#define MAX_CHAR 5 //lunghezza massima campi input
#define NUM_OPZIONI 6 //numero di voci a menu
#define PI_GRECO 3.14
#define INIZIO_ARRAY 0
//indici relativi ai campi del menu
#define IND_NTAGLIENTI 0 //campo 0 - prima voce
#define IND_DIAMETRO 1
#define IND_RPM 2
#define IND_CUTSPEED 3
#define IND_FEEDSPEED 4
#define IND_SPESSORET 5
//malori massimi per ogni campo
#define MAX_NTAGLIENTI 6
#define MAX_DIAMETRO 12
#define MAX_RPM 60000
#define MAX_CUTSPEED 999
#define MAX_FEEDSPEED 20
#define MAX_SPESSORE 2

#include "header_conversione.h"

void refresh_schermata(float *rs_param);

static inline void calcola_RPM(float *cr_param) {
	cr_param[IND_RPM] = (cr_param[IND_CUTSPEED] * 1000) / (PI_GRECO * cr_param[IND_DIAMETRO]);
}
static inline void calcola_cutspeed(float *cc_param) {
	cc_param[IND_CUTSPEED] = cc_param[IND_RPM] * PI_GRECO * cc_param[IND_DIAMETRO] * 0.001;
}
static inline void calcola_avanzamento(float *ca_param) {
	ca_param[IND_FEEDSPEED] = ca_param[IND_SPESSORET] * ca_param[IND_RPM] * ca_param[IND_NTAGLIENTI] * 0.001;
}
static inline void calcola_truciolo(float *ct_param) {
	ct_param[IND_SPESSORET] = (ct_param[IND_FEEDSPEED] * 1000) / (ct_param[IND_RPM] * ct_param[IND_NTAGLIENTI]);
}

int main()
{	
	float param1[NUM_OPZIONI] = {1,4,15000,0,4,0};	//valori iniziali
	struct inserimento val_appoggio;
	int max_rif, i1;
	
	calcola_cutspeed(param1);	//inizializzazioni
	calcola_truciolo(param1);
	i1 = INIZIO_ARRAY;
	
	do{
		refresh_schermata(param1);
		printf("inserisci ");
		switch (i1) {
		case IND_NTAGLIENTI:
			printf("numero taglienti: ");
			max_rif = MAX_NTAGLIENTI;
			break;
		case IND_DIAMETRO:
			printf("diametro fresa: ");
			max_rif = MAX_DIAMETRO;
			break;
		case IND_RPM:
			printf("RPM: ");
			max_rif = MAX_RPM;
			break;
		case IND_CUTSPEED:
			printf("velocita' di taglio (rotazione): ");
			max_rif = MAX_CUTSPEED;
			break;
		case IND_FEEDSPEED:
			printf("velocita' di avanzamento: ");
			max_rif = MAX_FEEDSPEED;
			break;
		case IND_SPESSORET:
			printf("spessore truciolo: ");
			max_rif = MAX_SPESSORE;
			break;
		}
		
		val_appoggio = input_val(MAX_CHAR); //input campo menu
		if (val_appoggio.numero > max_rif) 
			val_appoggio.numero = max_rif; //se sforo il valore massimo consentito
		
		if (val_appoggio.flag > input_vuoto){
			param1[i1] = val_appoggio.numero;
			switch (i1) {
			case IND_DIAMETRO:
				calcola_cutspeed(param1);
			case IND_RPM:
				calcola_cutspeed(param1);
				break;
			case IND_CUTSPEED:
				calcola_RPM(param1);
				break;
			case IND_SPESSORET:
				calcola_avanzamento(param1);
				break;
			}
			calcola_truciolo(param1);
		} else {
			if (val_appoggio.flag == input_vuoto) {
				if (i1 < NUM_OPZIONI - 1)
					i1++;
				else 
					i1 = INIZIO_ARRAY;
			}
		}
	} while (val_appoggio.flag != quit); //FINE DO - WHILE
	
	return 0; 
}

void refresh_schermata(float *rs_param)
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
	printf("\n	numero di taglienti:		%1.0f\n",rs_param[IND_NTAGLIENTI]);
	printf("\n	diametro fresa:			%1.1f mm\n",rs_param[IND_DIAMETRO]);
	printf("\n		RPM:			%5.0f\n",rs_param[IND_RPM]);
	printf("\n	 velocita' taglio:		%3.1f m/min\n",rs_param[IND_CUTSPEED]);
	printf("\nvelocita' avanzamento:			%2.1f m/min\n",rs_param[IND_FEEDSPEED]);
	printf("\n	spessore truciolo:		%1.2f\n\n\n",rs_param[IND_SPESSORET]);
}
