#include <stdio.h>
#include <string.h>
//********************************* costanti ************************
#define PI_GRECO 3.14
#define MAX_CHAR 5 //lunghezza massima campi input
#define MAX_STRING 80

enum flag_ok_stampa{
	non_stampare = 0,
	ok_stampa,
};

struct parametri {
	float valore;
	char dicitura_menu[MAX_STRING];
	int flag_stampa;
};
//**************** funzioni e tipi **********************************
#include "header_conversione.h"
static void refresh_schermata(struct parametri *rs_param, const int rs_cursore);
static void check_stampa(struct parametri *cs_param, const int indice);
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
	for (i1 = 0; i1 < opzioni_disponibili; i1++) {
		param1[i1].valore = 0;
		param1[i1].flag_stampa = non_stampare;
	}
	strcpy(param1[i_diametro].dicitura_menu,		"                     diametro: %1.0f mm");
	strcpy(param1[i_ntagl].dicitura_menu,			"             numero taglienti: %1f m/min");
	strcpy(param1[i_profondita].dicitura_menu,		"          profondita' passata: %2.1f m/min");
	strcpy(param1[i_cutspeed].dicitura_menu,		"           velocita' rotativa: %1.2f mm");
	strcpy(param1[i_coef_mat].dicitura_menu,		"coefficiente taglio materiale: %2.1f m/min");
	strcpy(param1[i_rpm].dicitura_menu,				"                          RPM: %5.0f");
	strcpy(param1[i_feedspeed].dicitura_menu,		"        velocita' avanzamento: %2.1f m/min");
	strcpy(param1[i_feedrate].dicitura_menu,		"         avanzamento per giro: %1.2f mm");
	strcpy(param1[i_mat_asp_giro].dicitura_menu,	" materiale asportato per giro: %2.2f mm^3");
	strcpy(param1[i_mat_asp_dente].dicitura_menu,	"    mat asport x giro x dente: %2.2f mm^3");
	strcpy(param1[i_kw].dicitura_menu,				"            potenza assorbita: %3.2f KW");
	param1[i_rpm].flag_stampa = ok_stampa;
	param1[i_feedspeed].flag_stampa = ok_stampa;
	i1 = i_rpm;
	//******************************** codice ***********************************************
	do{	
		refresh_schermata(param1, i1);
		val_appoggio = input_val(MAX_CHAR, ch_main);
		switch (val_appoggio.flag) {
		case input_corretto:
			switch (val_appoggio.indice) {
			case fac_diametro:
				param1[i_diametro].valore = val_appoggio.numero;
				param1[i_diametro].flag_stampa = ok_stampa;
				break;
			case fac_ntagl:
				break;
			case fac_profondita:
				break;
			case fac_cutspeed:
				break;
			case fac_coef_mat:
				break;
			case fac_feedrate:
				break;
			default:
				param1[i1].valore = val_appoggio.numero;
				switch (i1) {
				case i_rpm:
					calcola_feedrate(param1);	//ricalcolo la velocità di avanzamento per mantenere lo stesso feed rate
					break;
				case i_feedspeed:
					calcola_feedrate(param1);
					break;
				default:
					break;
				}
			}
			break;
		case input_vuoto:
			i1++;
			if (i1 > i_feedspeed) 
				i1 = i_rpm;
			break;
		default:
			break;
		}
	} while (val_appoggio.flag != quit);
	return 0; //****************************** fine *************************************************
}

static void refresh_schermata(struct parametri *rs_param, const int rs_cursore)
{
	int i1;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
	for (i1=0; i1 < opzioni_disponibili; i1++) {
		if (rs_param[i1].flag_stampa == ok_stampa) {
			printf(rs_param[i1].dicitura_menu, rs_param[i1].valore);
			if (i1 == rs_cursore)
				printf(" <--");
			printf("\n");
		}
	}
	printf("\n\n");
}

static void check_stampa(struct parametri *cs_param, const int indice)
{
	if (cs_param[indice].valore == 0)
		cs_param[indice].flag_stampa = non_stampare;
	else
		cs_param[indice].flag_stampa = ok_stampa;
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
	if ((cc_param[i_rpm].valore > 0) && (cc_param[i_diametro].valore > 0)) {
		cc_param[i_cutspeed].valore = (cc_param[i_rpm].valore * PI_GRECO * cc_param[i_diametro].valore * 0.001);
		check_stampa(cc_param, i_cutspeed);
	}
}

