#include <stdio.h>
#include<string.h>
//********************************* costanti ************************
#define PI_GRECO 3.14
#define MAX_CHAR 5 //lunghezza massima campi input
enum indici {
	i_diametro = 0,
	i_larghezza, //da fare
	i_profondita, //da fare
	i_rpm,
	i_feedspeed,
	i_feedrate,
	i_materiale_asportato, //da fare - mm^3 al min, profondita * impegno in arghezza * feedspeed * 1000
	i_potenza_assorbita, //da fare (materiale asportato * coefficiente taglio materiale) / (60 * 1000) - risultato in KW
	opzioni_disponibili,
};
//**************** funzioni e tipi **********************************
#include "header_conversione.h"
static inline void calcola_rpm(float *cr_param) {
	cr_param[i_rpm] = (cr_param[i_feedspeed] * 1000) / cr_param[i_feedrate];
}
static inline void calcola_feedspeed(float *ca_param) {
	ca_param[i_feedspeed] = ca_param[i_feedrate] * 0.001 * ca_param[i_rpm] ;
}
static inline void calcola_feedrate(float *ct_param) {
	ct_param[i_feedrate] = (ct_param[i_feedspeed] * 1000) / ct_param[i_rpm];
}

void refresh_schermata(float *rs_param, const int rs_cursore);
static inline float calcola_cutspeed(float *cc_param) {
	return (cc_param[i_rpm] * PI_GRECO * cc_param[i_diametro] * 0.001);
}

int main()
{
	float param1[opzioni_disponibili];	//array contenente i parametri di fresatura
	char dicitura_input [opzioni_disponibili][30];
	struct inserimento val_appoggio;
	int i1;
	//********************************* inizializzazioni *************************************
	for (i1 = 0; i1 < opzioni_disponibili; i1++)
		param1[i1] = 0;
	calcola_feedspeed(param1);
	strcpy(dicitura_input[i_rpm],			"RPM");
	strcpy(dicitura_input[i_feedspeed],	"velocita avanz (m/min)");
	strcpy(dicitura_input[i_feedrate],	"avanzamento per giro");
	i1 = i_rpm;
	//******************************** codice ***********************************************
	do{	
		refresh_schermata(param1, i1);
		printf("(q - quit, d - diametro fresa, i - impegno in larghezza %%)\ninserire %s: ",dicitura_input[i1]);
		val_appoggio = input_val(MAX_CHAR);
		switch (val_appoggio.flag) {
		case input_corretto:
			param1[i1] = val_appoggio.numero;
			switch (i1) {
			case i_rpm:
				calcola_feedspeed(param1);	//ricalcolo la velocità di avanzamento per mantenere lo stesso feed rate
				break;
			case i_feedspeed:
				calcola_feedrate(param1);
				break;
			case i_feedrate:
				calcola_rpm(param1);
				break;
			default:
				break;
			}
			break;
		case input_vuoto:
			i1++;
			if (i1 > i_feedrate) 
				i1 = i_rpm;
			break;
		case inserire_diametro:
			do{
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
				printf("inserire diametro (q - quit): ");
				val_appoggio = input_val(1);
			} while ((val_appoggio.flag != input_corretto) && (val_appoggio.flag != quit));
			param1[i_diametro] = val_appoggio.numero;
			break;
		case inserire_impegno_in_larghezza:
			do{
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
				printf("inserire impegno fresa in larghezza (q - quit): ");
				val_appoggio = input_val(1);
			} while ((val_appoggio.flag != input_corretto) && (val_appoggio.flag != quit));
			param1[i_larghezza] = val_appoggio.numero;
			break;
		default:
			break;
		}
	} while (val_appoggio.flag != quit);
	return 0; //****************************** fine *************************************************
}

void refresh_schermata(float *rs_param, const int rs_cursore)
{
	char rs_video[opzioni_disponibili][60],rs_appoggio[30];
	int i1;
	
	for (i1=0; i1 < opzioni_disponibili; i1++)
		strcpy(rs_video[i1], "\n");
	
	if (rs_param[i_diametro] > 0) {
		strcpy(rs_video[i_diametro],	"        diametro fresa: %1.1f mm");
		strcpy(rs_video[i_rpm],		"                  RPM: %5.0f (");
		sprintf(rs_appoggio,"%3.1f m/min)", calcola_cutspeed(rs_param));
		strcat(rs_video[i_rpm], rs_appoggio);
	} else {
		strcpy(rs_video[i_rpm],		"                  RPM: %5.0f");
	}
	strcpy(rs_video[i_feedspeed],		"velocita' avanzamento: %2.1f m/min");
	strcpy(rs_video[i_feedrate],		"avanzamento per giro: %1.2f mm");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
	
	for (i1=0; i1 < opzioni_disponibili; i1++) {
		if (strlen(rs_video[i1]) > 1) {
			printf(rs_video[i1], rs_param[i1]);
			if (i1 == rs_cursore)
				printf(" <--");
			printf("\n");
		}
	}
	printf("\n\n");
}	

