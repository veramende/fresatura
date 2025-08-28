#include <stdio.h>
#include<string.h>
//********************************* costanti ************************
#define PI_GRECO 3.14
#define MAX_CHAR 5 //lunghezza massima campi input
#define NUM_OPZIONI 4 //numero di voci a menu
#define IND_DIAMETRO 0
#define IND_RPM 1
#define IND_FEEDSPEED 2		//avanzamento in m/min (velocità)
#define IND_FEEDRATE 3		//spessore truciolo asportato ad ogni giro per singolo tagliente
//**************** funzioni e tipi **********************************
#include "header_conversione.h"
static inline void calcola_rpm(float *cr_param) {
	cr_param[IND_RPM] = (cr_param[IND_FEEDSPEED] * 1000) / cr_param[IND_FEEDRATE];
}
static inline void calcola_feedspeed(float *ca_param) {
	ca_param[IND_FEEDSPEED] = ca_param[IND_FEEDRATE] * 0.001 * ca_param[IND_RPM] ;
}
static inline void calcola_feedrate(float *ct_param) {
	ct_param[IND_FEEDRATE] = (ct_param[IND_FEEDSPEED] * 1000) / ct_param[IND_RPM];
}

void refresh_schermata(float *rs_param);
static inline float calcola_cutspeed(float *cc_param) {
	return (cc_param[IND_RPM] * PI_GRECO * cc_param[IND_DIAMETRO] * 0.001);
}

int main()
{
	float param1[NUM_OPZIONI];	//array contenente i parametri di fresatura
	char dicitura_input [NUM_OPZIONI][30];
	struct inserimento val_appoggio;
	int i1;
	//********************************* inizializzazioni *************************************
	for (i1 = 0; i1 < NUM_OPZIONI; i1++)
		param1[i1] = 0;
	calcola_feedspeed(param1);
	strcpy(dicitura_input[IND_RPM],			"RPM");
	strcpy(dicitura_input[IND_FEEDSPEED],	"velocita avanz (m/min)");
	strcpy(dicitura_input[IND_FEEDRATE],	"avanzamento per giro");
	i1 = IND_RPM;
	//******************************** codice ***********************************************
	do{
		refresh_schermata(param1);
		printf("(q - quit, d - diametro fresa, i - impegno in larghezza %%)\ninserire %s: ",dicitura_input[i1]);
		val_appoggio = input_val(MAX_CHAR);
		switch (val_appoggio.flag) {
		case input_corretto:
			param1[i1] = val_appoggio.numero;
			switch (i1) {
			case IND_RPM:
				calcola_feedspeed(param1);	//ricalcolo la velocità di avanzamento per mantenere lo stesso feed rate
				break;
			case IND_FEEDSPEED:
				calcola_feedrate(param1);
				break;
			case IND_FEEDRATE:
				calcola_rpm(param1);
				break;
			default:
				break;
			}
			break;
		case input_vuoto:
			i1++;
			if (i1 == NUM_OPZIONI) 
				i1 = IND_RPM;
			break;
		case inserire_diametro:
			do{
				refresh_schermata(param1);
				printf("inserire diametro (q - quit): ");
				val_appoggio = input_val(1);
			} while ((val_appoggio.flag != input_corretto) && (val_appoggio.flag != quit));
			param1[IND_DIAMETRO] = val_appoggio.numero;
			break;
		default:
			break;
		}
	} while (val_appoggio.flag != quit);
	return 0; //****************************** fine *************************************************
}

void refresh_schermata(float *rs_param)
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
	if (rs_param[IND_DIAMETRO] > 0) {
		printf("       diametro fresa: %1.1f mm\n",rs_param[IND_DIAMETRO]);
		printf("                  RPM: %5.0f (%3.1f m/min)\n",rs_param[IND_RPM], calcola_cutspeed(rs_param));
	}else{
		printf("                  RPM: %5.0f\n",rs_param[IND_RPM]);
	}
	printf("velocita' avanzamento: %2.1f m/min\n\n",rs_param[IND_FEEDSPEED]);
	printf(" avanzamento per giro: %1.2f mm\n",rs_param[IND_FEEDRATE]);
	printf("\n\n");
}	