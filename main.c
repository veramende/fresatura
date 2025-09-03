#include <stdio.h>
#include <string.h>
//********************************* costanti ************************
#define PI_GRECO 3.14
#define MAX_CHAR 5 //lunghezza massima campi input
#define MAX_STRING 80

struct parametri {
	float valore;
	char dicitura_menu[MAX_STRING];
};
//**************** funzioni e tipi **********************************
#include "header_conversione.h"
static void calcola_rpm(struct parametri  *cr_param);
static void calcola_feedspeed(struct parametri *ca_param);
static void calcola_feedrate(struct parametri *ct_param);
static void calcola_cutspeed(struct parametri *cc_param);

int main()
{
	struct parametri param1[opzioni_disponibili];	//array contenente i parametri di fresatura
	struct inserimento val_appoggio;
	int i1;
	//********************************* inizializzazioni *************************************
	for (i1 = 0; i1 < opzioni_disponibili; i1++)
		param1[i1].valore = 0;
	
	param1[i_ntagl].dicitura_menu[0] = (char)flag_ntagl;
	param1[i_ntagl].dicitura_menu[1] = 0;
	strcat(param1[i_ntagl].dicitura_menu,			" -              numero taglienti: %1.0f m/min\n");
	
	param1[i_diametro].dicitura_menu[0] = (char)flag_diametro;
	param1[i_diametro].dicitura_menu[1] = 0;
	strcat(param1[i_diametro].dicitura_menu,		" -                diametro fresa: %1.0f mm\n");
	
	param1[i_profondita].dicitura_menu[0] = (char)flag_profondita;
	param1[i_profondita].dicitura_menu[1] = 0;
	strcat(param1[i_profondita].dicitura_menu,		" -           profondita' passata: %2.1f m/min\n");
	
	param1[i_cutspeed].dicitura_menu[0] = (char)flag_cutspeed;
	param1[i_cutspeed].dicitura_menu[1] = 0;
	strcat(param1[i_cutspeed].dicitura_menu,		" -            velocita' rotativa: %1.2f mm\n");
	
	param1[i_coef_mat].dicitura_menu[0] = (char)flag_coef_mat;
	param1[i_coef_mat].dicitura_menu[1] = 0;
	strcat(param1[i_coef_mat].dicitura_menu,		" - coefficiente taglio materiale: %2.1f m/min\n");
	
	param1[i_feedrate].dicitura_menu[0] = (char)flag_feedrate;
	param1[i_feedrate].dicitura_menu[1] = 0;
	strcat(param1[i_feedrate].dicitura_menu,		" -          avanzamento per giro: %1.2f mm\n");
	
	param1[i_rpm].dicitura_menu[0] = (char)flag_rpm;
	param1[i_rpm].dicitura_menu[1] = 0;
	strcat(param1[i_rpm].dicitura_menu,				" -                           RPM: %5.0f\n");
	
	param1[i_feedspeed].dicitura_menu[0] = (char)flag_feedspeed;
	param1[i_feedspeed].dicitura_menu[1] = 0;
	strcat(param1[i_feedspeed].dicitura_menu,		" -         velocita' avanzamento: %2.1f m/min\n");
	
	strcpy(param1[i_kw].dicitura_menu,				"                potenza assorbita: %3.2f KW\n");
	strcpy(param1[i_mat_asp_giro].dicitura_menu,	"     materiale asportato per giro: %2.2f mm^3\n");
	strcpy(param1[i_mat_asp_dente].dicitura_menu,	"        mat asport x giro x dente: %2.2f mm^3\n");

	//******************************** codice ***********************************************
	do{	
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
		for (i1=0; i1 < opzioni_disponibili; i1++) {	//**************************refresh schermata*************************
			printf(param1[i1].dicitura_menu, param1[i1].valore);
		}
		printf("q - quit\n\n");	//***************************************************************************************************
		val_appoggio = input_val(MAX_CHAR);
		switch (val_appoggio.flag) {
		case flag_rpm:
			param1[i_rpm].valore = val_appoggio.numero;
			calcola_feedrate(param1);	//ricalcolo la velocità di avanzamento per mantenere lo stesso feed rate
			break;
		case flag_feedspeed:
			param1[i_feedspeed].valore = val_appoggio.numero;
			calcola_feedrate(param1);
			break;
		case flag_diametro:
			param1[i_diametro].valore = val_appoggio.numero;
			break;
		case flag_ntagl:
			break;
		case flag_profondita:
			break;
		case flag_cutspeed:
			break;
		case flag_coef_mat:
			break;
		case flag_feedrate:
			break;
		default:
			break;
		}
	} while (val_appoggio.flag != flag_quit);
	return 0; //****************************** fine *************************************************
}

static void calcola_rpm(struct parametri  *cr_param)
{
	if ((cr_param[i_feedspeed].valore > 0) && (cr_param[i_feedrate].valore > 0))
		cr_param[i_rpm].valore = (cr_param[i_feedspeed].valore * 1000) / cr_param[i_feedrate].valore;
}
static void calcola_feedspeed(struct parametri *ca_param)
{
	if ((ca_param[i_feedrate].valore > 0) && (ca_param[i_rpm].valore > 0))
		ca_param[i_feedspeed].valore = ca_param[i_feedrate].valore * 0.001 * ca_param[i_rpm].valore ;
}
static void calcola_feedrate(struct parametri *cfr_param)
{
	if ((cfr_param[i_feedspeed].valore > 0) && (cfr_param[i_rpm].valore > 0))
		cfr_param[i_feedrate].valore = (cfr_param[i_feedspeed].valore * 1000) / cfr_param[i_rpm].valore;
}

static void calcola_cutspeed(struct parametri *cc_param)
{
	if ((cc_param[i_rpm].valore > 0) && (cc_param[i_diametro].valore > 0))
		cc_param[i_cutspeed].valore = (cc_param[i_rpm].valore * PI_GRECO * cc_param[i_diametro].valore * 0.001);
}

