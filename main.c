#include <stdio.h>
#include<string.h>

#define MAX_CHAR 5 //lunghezza massima campi input
#define NUM_OPZIONI 6 //numero di voci a menu
#define PI_GRECO 3.14
#define INIZIO_ARRAY 0
//indici relativi ai campi del menu
#define IND_NTAGLIENTI 0 //campo 0 - prima voce
#define IND_DIAMETRO 1
#define IND_RPM 2
#define IND_CUTSPEED 3
#define IND_FEEDSPEED 4		//avanzamento in m/min (velocità)
#define IND_FEEDRATE 5		//avanzamento in mm/giro

#include "header_conversione.h"

void refresh_schermata(float *rs_param);

static inline void calcola_RPM(float *cr_param) {
	cr_param[IND_RPM] = (cr_param[IND_CUTSPEED] * 1000) / (PI_GRECO * cr_param[IND_DIAMETRO]);
}
static inline void calcola_cutspeed(float *cc_param) {
	cc_param[IND_CUTSPEED] = cc_param[IND_RPM] * PI_GRECO * cc_param[IND_DIAMETRO] * 0.001;
}
static inline void calcola_avanzamento(float *ca_param) {
	ca_param[IND_FEEDSPEED] = ca_param[IND_FEEDRATE] * ca_param[IND_RPM] * ca_param[IND_NTAGLIENTI] * 0.001;
}
static inline void calcola_feedrate(float *ct_param) {
	ct_param[IND_FEEDRATE] = (ct_param[IND_FEEDSPEED] * 1000) / (ct_param[IND_RPM] * ct_param[IND_NTAGLIENTI]);
}

int main()
{	
	float param1[NUM_OPZIONI] = {1,4,15000,0,4,0};	//valori iniziali
	char dicitura_input [NUM_OPZIONI][30];
	struct inserimento val_appoggio;
	int i1;
	
	calcola_cutspeed(param1);	//inizializzazioni
	calcola_feedrate(param1);
	strcpy(dicitura_input[IND_NTAGLIENTI],	"n. taglienti: ");
	strcpy(dicitura_input[IND_DIAMETRO],	"diametro (mm): ");
	strcpy(dicitura_input[IND_RPM],			"RPM: ");
	strcpy(dicitura_input[IND_CUTSPEED],	"velocita rotazione (m/min): ");
	strcpy(dicitura_input[IND_FEEDSPEED],	"velocita avanz (m/min): ");
	strcpy(dicitura_input[IND_FEEDRATE],	"avanzamento per giro: ");
	
	i1 = INIZIO_ARRAY;
	
	do{
		refresh_schermata(param1);
		printf("%s",dicitura_input[i1]);
		val_appoggio = input_val(MAX_CHAR); //input campo menu	
		if (val_appoggio.flag > input_vuoto){
			param1[i1] = val_appoggio.numero;
			switch (i1) {
			case IND_NTAGLIENTI:
				calcola_avanzamento(param1);//ricalcolo la velocità di avanzamento per mantenere lo stesso feed rate
				break;
			case IND_DIAMETRO:
				calcola_cutspeed(param1);	//mantengo gli stessi giri ma avrò una velocità rotativa diversa
				break;
			case IND_RPM:
				calcola_cutspeed(param1);	//ricalcolo la velocità rotativa
				calcola_avanzamento(param1);//ricalcolo la velocità di avanzamento per mantenere lo stesso feed rate
				break;
			case IND_CUTSPEED:				//settare questo parametro manualmente serve solo x ricavare i giri
				calcola_RPM(param1);
				calcola_avanzamento(param1);//allineo velocità di avanzamento a nuova velocità rotativa mantenendo lo stesso feed rate
				break;
			case IND_FEEDSPEED:
				calcola_feedrate(param1);
				break;
			case IND_FEEDRATE:
				calcola_avanzamento(param1);
				break;
			default:
				break;
			}
		} else if (val_appoggio.flag == input_vuoto) {
			if (i1 < NUM_OPZIONI - 1)
				i1++;
			else 
				i1 = INIZIO_ARRAY;
		}
	} while (val_appoggio.flag != quit);
	
	return 0; 
}

void refresh_schermata(float *rs_param)
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
	printf("numero di taglienti:         %1.0f\n",rs_param[IND_NTAGLIENTI]);
	printf("diametro fresa:              %1.1f mm\n",rs_param[IND_DIAMETRO]);
	printf("RPM:                         %5.0f\n",rs_param[IND_RPM]);
	printf("velocita' taglio:            %3.1f m/min\n",rs_param[IND_CUTSPEED]);
	printf("velocita' avanzamento:       %2.1f m/min\n\n",rs_param[IND_FEEDSPEED]);
	printf("avanzamento per giro:        %1.2f mm\n",rs_param[IND_FEEDRATE]);
	printf("\n\n");
}
