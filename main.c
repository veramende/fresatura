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
static void calcola_rpm(struct parametri  *f_param);
static void rpm_da_cutspeed(struct parametri  *f_param);
static void calcola_feedspeed(struct parametri *f_param);
static void calcola_feedrate(struct parametri *f_param);
static void calcola_cutspeed(struct parametri *f_param);
static void calcola_mat_asp_giro(struct parametri *f_param);
static void calcola_mat_asp_giro_dente(struct parametri *f_param);
static void calcola_potenza(struct parametri *f_param);
static void cascata_dipendenze(struct parametri *f_param, int val_cambiato);

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
	strcat(param1[i_ntagl].dicitura_menu,			" -              numero taglienti: %1.0f\n");
	param1[i_ntagl].valore = 1;
	
	param1[i_diametro].dicitura_menu[0] = (char)flag_diametro;
	param1[i_diametro].dicitura_menu[1] = 0;
	strcat(param1[i_diametro].dicitura_menu,		" -                diametro fresa: %1.0f mm\n");
	param1[i_diametro].valore = 1;
	
	param1[i_profondita].dicitura_menu[0] = (char)flag_profondita;
	param1[i_profondita].dicitura_menu[1] = 0;
	strcat(param1[i_profondita].dicitura_menu,		" -           profondita' passata: %2.1f mm\n");
	
	param1[i_cutspeed].dicitura_menu[0] = (char)flag_cutspeed;
	param1[i_cutspeed].dicitura_menu[1] = 0;
	strcat(param1[i_cutspeed].dicitura_menu,		" -            velocita' rotativa: %1.2f m/min\n\n");
	
	param1[i_coef_mat].dicitura_menu[0] = (char)flag_coef_mat;
	param1[i_coef_mat].dicitura_menu[1] = 0;
	strcat(param1[i_coef_mat].dicitura_menu,		" - Kc, resisten specifica taglio: %2.1f N/mm^2\n");
	
	param1[i_feedrate].dicitura_menu[0] = (char)flag_feedrate;
	param1[i_feedrate].dicitura_menu[1] = 0;
	strcat(param1[i_feedrate].dicitura_menu,		" -     avanzamento nel materiale: %1.2f mm/giro\n");
	
	param1[i_rpm].dicitura_menu[0] = (char)flag_rpm;
	param1[i_rpm].dicitura_menu[1] = 0;
	strcat(param1[i_rpm].dicitura_menu,				" -                           RPM: %5.0f\n");
	param1[i_rpm].valore = 1;
	
	param1[i_feedspeed].dicitura_menu[0] = (char)flag_feedspeed;
	param1[i_feedspeed].dicitura_menu[1] = 0;
	strcat(param1[i_feedspeed].dicitura_menu,		" -         velocita' avanzamento: %2.1f m/min\n\n");
	
	strcpy(param1[i_kw].dicitura_menu,				"                potenza assorbita: %3.2f KW\n");
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
			if (val_appoggio.numero <= 60000) {
				param1[i_rpm].valore = val_appoggio.numero;
				cascata_dipendenze(param1, i_rpm);
			}
			break;
		case flag_feedspeed:
			if (val_appoggio.numero  < 20) {
				param1[i_feedspeed].valore = val_appoggio.numero;
				cascata_dipendenze(param1, i_feedspeed);
			}
			break;
		case flag_diametro:
			if (val_appoggio.numero <= 10) {
				param1[i_diametro].valore = val_appoggio.numero;
				cascata_dipendenze(param1, i_diametro);
			}
			break;
		case flag_ntagl:
			if (val_appoggio.numero < 10) {
				param1[i_ntagl].valore = (int)val_appoggio.numero;
				cascata_dipendenze(param1, i_ntagl);
			}
			break;
		case flag_profondita:
			param1[i_profondita].valore = val_appoggio.numero;
			cascata_dipendenze(param1, i_profondita);
			break;
		case flag_cutspeed:
			param1[i_cutspeed].valore = val_appoggio.numero;
			cascata_dipendenze(param1, i_cutspeed);
			break;
		case flag_coef_mat:
			param1[i_coef_mat].valore = val_appoggio.numero;
			cascata_dipendenze(param1, i_coef_mat);
			break;
		case flag_feedrate:
			param1[i_feedrate].valore = val_appoggio.numero;
			cascata_dipendenze(param1, i_feedrate);
			break;
		default:
			break;
		}
	} while (val_appoggio.flag != flag_quit);
	return 0; //****************************** fine *************************************************
}

static void calcola_rpm(struct parametri  *f_param)
{
	f_param[i_rpm].valore = (f_param[i_feedspeed].valore * 1000) / f_param[i_feedrate].valore;
}
static void rpm_da_cutspeed(struct parametri  *f_param)
{
	f_param[i_rpm].valore = (f_param[i_cutspeed].valore * 1000) / (PI_GRECO * f_param[i_diametro].valore);
}
static void calcola_feedspeed(struct parametri *f_param)
{
	f_param[i_feedspeed].valore = f_param[i_feedrate].valore * 0.001 * f_param[i_rpm].valore ;
}

static void calcola_feedrate(struct parametri *f_param)
{
	f_param[i_feedrate].valore = (f_param[i_feedspeed].valore * 1000) / f_param[i_rpm].valore;
}

static void calcola_cutspeed(struct parametri *f_param)
{
	f_param[i_cutspeed].valore = f_param[i_rpm].valore * PI_GRECO * f_param[i_diametro].valore * 0.001;
}

static void calcola_mat_asp_giro_dente(struct parametri *f_param)
{
	f_param[i_mat_asp_dente].valore = (f_param[i_feedrate].valore * f_param[i_diametro].valore * f_param[i_profondita].valore) / f_param[i_ntagl].valore;
}

static void calcola_potenza(struct parametri *f_param) {
	f_param[i_kw].valore = (f_param[i_coef_mat].valore * f_param[i_feedspeed].valore * f_param[i_diametro].valore * f_param[i_profondita].valore) / (60000);
}

static void cascata_dipendenze(struct parametri *f_param, int val_cambiato)
{
	switch (val_cambiato){
	case i_cutspeed:
		rpm_da_cutspeed(f_param);
		calcola_feedrate(f_param);	//copia di cascata_rpm senza cutspeed ovviamente
		calcola_mat_asp_giro_dente(f_param);
		break;
	case i_rpm:
		calcola_cutspeed(f_param);
		calcola_feedrate(f_param);
		calcola_mat_asp_giro_dente(f_param);
		break;
	case i_feedspeed:
		calcola_feedrate(f_param);
		calcola_mat_asp_giro_dente(f_param);
		calcola_potenza(f_param);
		break;
	case i_diametro:
		calcola_cutspeed(f_param);
		calcola_mat_asp_giro_dente(f_param);
		calcola_potenza(f_param);
		break;
	case i_ntagl:
		calcola_mat_asp_giro_dente(f_param);
		break;
	case i_profondita:
		calcola_mat_asp_giro_dente(f_param);
		calcola_potenza(f_param);
		break;
	case i_feedrate:
		calcola_rpm(f_param);
		calcola_mat_asp_giro_dente(f_param);
		break;
	case i_coef_mat:
		calcola_potenza(f_param);
		break;
	}
}
