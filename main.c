#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//********************************* costanti ************************
#define PI_GRECO 3.14
#define MAX_RPM 10000
#define MAX_CHAR 6 //lunghezza massima campi input compreso eof
#define MAX_STRING 80
#define INIZIO_ARRAY 0

enum flag_menu {
	flag_quit = 'q',
	flag_diametro = 'd',
	flag_ntagl = 'n',
	flag_profondita = 'p',
	flag_cutspeed = 'c',
	flag_coef_mat = 'k',	//coefficiente di forza di taglio specifica per materiale
	flag_feedrate_generale = 'f',
	flag_rpm = 'r',
	flag_feedspeed = 'a',
};

enum indici {
	//parametri del software cam
	i_rpm,
	i_feedspeed,
	//inseribili
	i_diametro,
	i_ntagl,
	i_profondita,
	i_coef_mat,
	//calcolabili e definibili
	i_cutspeed,
	i_feedrate_generale,
	//solo calcolabili
	i_feedrate_per_tagliente,
	i_coppia_richiesta,
	i_potenza_richiesta,
	opzioni_disponibili,
};

struct voci_menu {
	float valore;
	char flag;
	char dicitura_menu[MAX_STRING];
};

static void calcola_rpm_da_feedspeed(struct voci_menu  *f_param);
static void calcola_rpm_da_cutspeed(struct voci_menu  *f_param);
static void calcola_feedspeed(struct voci_menu *f_param);
static void calcola_feedrate_generale(struct voci_menu *f_param);
static void calcola_feedrate_per_tagliente(struct voci_menu *f_param);
static void calcola_cutspeed(struct voci_menu *f_param);
static void calcola_potenza_richiesta(struct voci_menu *f_param);
static void calcola_coppia_richiesta(struct voci_menu *f_param);
static void calcola_coppia_richiesta(struct voci_menu *f_param);
static void cascata_dipendenze(struct voci_menu *f_param, int val_cambiato);
static int controllo_primo_carattere(int cerca, struct voci_menu *cfo_param);
static void inizializza(struct voci_menu *iniz_param);
static void stampa_schermata_menu(struct voci_menu *menu_param);
static int scelta_dipendenza(struct voci_menu *s_param, const int opz1, const int opz2);
static int lettura_stdin(char *stringa);
static float conv_num(char *stringa1, const int len1);


int main()
{
	struct voci_menu param1[opzioni_disponibili];	//array contenente i parametri di fresatura
	int prefisso, indice_voce_menu, len_str;
	char valore_letterale[MAX_CHAR];
	inizializza(param1);
	do{	
		stampa_schermata_menu(param1);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
	for (i1=INIZIO_ARRAY; i1 < opzioni_disponibili; i1++) {
		printf(param1[i1].dicitura_menu, param1[i1].valore);
	}
	printf("q - quit\n\n");
		prefisso = getchar();
		indice_voce_menu = controllo_primo_carattere(prefisso, param1);
		if ((indice_voce_menu < opzioni_disponibili) && (prefisso != flag_quit)) {
			len_str = lettura_stdin(valore_letterale);
			if (len_str > 0) {
				param1[indice_voce_menu].valore = conv_num(valore_letterale, len_str);
				cascata_dipendenze(param1, indice_voce_menu);
				if (indice_voce_menu == i_feedrate_generale) {
					switch (scelta_dipendenza(param1, i_rpm, i_feedspeed)) {
					case flag_rpm:
						calcola_rpm_da_feedspeed(param1);
						cascata_dipendenze(param1, i_rpm);
						break;
					case flag_feedspeed:
						calcola_feedspeed(param1);
						cascata_dipendenze(param1, i_feedspeed);
						break;
					default:
						break;
					}
				}
			}	
		}
	} while (prefisso != flag_quit);
	return 0;
}

static void calcola_rpm_da_feedspeed(struct voci_menu  *f_param)
{
	if (f_param[i_feedrate_generale].valore == 0) //controllo denominatore
		f_param[i_feedrate_generale].valore = 1;
	f_param[i_rpm].valore = (f_param[i_feedspeed].valore * 1000) / f_param[i_feedrate_generale].valore;
}

static void calcola_rpm_da_cutspeed(struct voci_menu  *f_param)
{
	if (f_param[i_diametro].valore == 0) //controllo denominatore
		f_param[i_diametro].valore = 1;
	f_param[i_rpm].valore = (f_param[i_cutspeed].valore * 1000) / (PI_GRECO * f_param[i_diametro].valore);
}

static void calcola_feedspeed(struct voci_menu *f_param)
{
	f_param[i_feedspeed].valore = f_param[i_feedrate_generale].valore * 0.001 * f_param[i_rpm].valore ;
}
static void calcola_feedrate_generale(struct voci_menu *f_param)
{
	if (f_param[i_rpm].valore == 0)	//controllo denominatore
		f_param[i_rpm].valore = 1;
	f_param[i_feedrate_generale].valore = (f_param[i_feedspeed].valore * 1000) / f_param[i_rpm].valore;
}

static void calcola_feedrate_per_tagliente(struct voci_menu *f_param)
{
	if (f_param[i_ntagl].valore == 0)	//controllo denominatore
		f_param[i_ntagl].valore = 1;
	f_param[i_feedrate_per_tagliente].valore = f_param[i_feedrate_generale].valore / f_param[i_ntagl].valore;
}

static void calcola_cutspeed(struct voci_menu *f_param)
{
	f_param[i_cutspeed].valore = f_param[i_rpm].valore * PI_GRECO * f_param[i_diametro].valore * 0.001;
}

static void calcola_potenza_richiesta(struct voci_menu *f_param)
{
	f_param[i_potenza_richiesta].valore = (f_param[i_coef_mat].valore * f_param[i_feedspeed].valore * f_param[i_diametro].valore * f_param[i_profondita].valore) / 60000;
}

static void calcola_coppia_richiesta(struct voci_menu *f_param)
{
	f_param[i_coppia_richiesta].valore = (f_param[i_potenza_richiesta].valore * 30000) / (f_param[i_rpm].valore * PI_GRECO);
}


static void cascata_dipendenze(struct voci_menu *f_param, int val_cambiato)
{
	switch (val_cambiato){
	case i_cutspeed:
		calcola_rpm_da_cutspeed(f_param);
		calcola_feedrate_generale(f_param);
		calcola_feedrate_per_tagliente(f_param);
		break;
	case i_rpm:
		calcola_cutspeed(f_param);
		calcola_feedrate_generale(f_param);
		calcola_feedrate_per_tagliente(f_param);
	calcola_coppia_richiesta(f_param);
		break;
	case i_feedspeed:
		calcola_feedrate_generale(f_param);
		calcola_feedrate_per_tagliente(f_param);
		calcola_potenza_richiesta(f_param);
	calcola_coppia_richiesta(f_param);
		break;
	case i_diametro:
		calcola_cutspeed(f_param);
		calcola_potenza_richiesta(f_param);
	calcola_coppia_richiesta(f_param);
		break;
	case i_ntagl:
		calcola_feedrate_per_tagliente(f_param);
		break;
	case i_profondita:
		calcola_potenza_richiesta(f_param);
	calcola_coppia_richiesta(f_param);
		break;
	case i_feedrate_generale:
		calcola_feedrate_per_tagliente(f_param);
		break;
	case i_coef_mat:
		calcola_potenza_richiesta(f_param);
	calcola_coppia_richiesta(f_param);
		break;
	}
}

static int scelta_dipendenza(struct voci_menu *s_param, const int opz1, const int opz2)
{
	const int max_len = 34;
	char stringa_troncata[max_len], scelta;
	do {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("2 valori dipendono dal parametro modificato, quale vuoi ricalcolare?\n");
		strncpy(stringa_troncata, s_param[opz1].dicitura_menu, max_len -1);
		stringa_troncata[max_len - 1] = '\0';
		printf("%s\n", stringa_troncata);
		strncpy(stringa_troncata, s_param[opz2].dicitura_menu, max_len -1);
		stringa_troncata[max_len - 1] = '\0';
		printf("%s\n\n", stringa_troncata);
		scelta = getchar();
		if ((scelta != '\n') && (scelta != EOF)) {
			while ((getchar() != '\n') && (getchar() != EOF)) {
			} //svuota stdin
		}
	} while ((scelta != flag_quit) && (scelta != s_param[opz1].flag) && (scelta != s_param[opz2].flag));
	return scelta;
}

static void inizializza(struct voci_menu *iniz_param)
{
	int i1,i2;
	for (i1 = INIZIO_ARRAY; i1 < opzioni_disponibili; i1++) {
		iniz_param[i1].valore = 0;
		iniz_param[i1].flag = ' ';
	}
	iniz_param[i_ntagl].flag = (char)flag_ntagl;
	iniz_param[i_diametro].flag = (char)flag_diametro;
	iniz_param[i_profondita].flag = (char)flag_profondita;
	iniz_param[i_cutspeed].flag = (char)flag_cutspeed;
	iniz_param[i_coef_mat].flag = (char)flag_coef_mat;
	iniz_param[i_feedrate_generale].flag = (char)flag_feedrate_generale;
	iniz_param[i_rpm].flag = (char)flag_rpm;
	iniz_param[i_feedspeed].flag = (char)flag_feedspeed;
	for (i1 = INIZIO_ARRAY; i1 < opzioni_disponibili; i1++) {
		for (i2 = INIZIO_ARRAY; i2 < MAX_STRING; i2++)
			iniz_param[i1].dicitura_menu[i2] = 0;
		iniz_param[i1].dicitura_menu[INIZIO_ARRAY] = iniz_param[i1].flag;
	}
	strcat(iniz_param[i_ntagl].dicitura_menu,				  "-			   numero taglienti: %1.0f\n");
	strcat(iniz_param[i_diametro].dicitura_menu,			   "-				 diametro fresa: %1.1f mm\n");
	strcat(iniz_param[i_profondita].dicitura_menu,			 "-			profondita' passata: %2.1f mm\n");
	strcat(iniz_param[i_cutspeed].dicitura_menu,			   "-			 velocita' rotativa: %1.2f m/min\n\n");
	strcat(iniz_param[i_coef_mat].dicitura_menu,			   "- Kc, resistenz specifica taglio: %2.1f N/mm^2 o MPa\n");
	strcat(iniz_param[i_feedrate_generale].dicitura_menu,	  "-			 avanzamento x giro: %1.3f mm/giro\n");
	strcat(iniz_param[i_rpm].dicitura_menu,					"-							RPM: %5.0f\n");
	strcat(iniz_param[i_feedspeed].dicitura_menu,			  "-		  velocita' avanzamento: %2.1f m/min\n\n");
	strcat(iniz_param[i_potenza_richiesta].dicitura_menu,	  "-			 potenza necessaria: %3.2f KW\n");
	strcat(iniz_param[i_coppia_richiesta].dicitura_menu,	   "-			  coppia necessaria: %3.2f N/m\n");
	strcat(iniz_param[i_feedrate_per_tagliente].dicitura_menu, "- avanzamento x giro x tagliente: %1.3f mm/giro\n");
}

static void stampa_schermata_menu(struct voci_menu *menu_param)
{
	int i1;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
	for (i1=INIZIO_ARRAY; i1 < opzioni_disponibili; i1++) {
		printf(menu_param[i1].dicitura_menu, menu_param[i1].valore);
	}
	printf("q - quit\n\n");
}

static int controllo_primo_carattere(int cerca, struct voci_menu *cfo_param)
{
	int i1;
	for(i1 = INIZIO_ARRAY; i1 < opzioni_disponibili; i1++) {
		if (cerca == cfo_param[i1].flag)
			break;
	}
	if (i1 < opzioni_disponibili)
		return i1;
	else
		return opzioni_disponibili;
}

static int lettura_stdin(char *stringa)
{
	char appoggio1;
	int i1 = INIZIO_ARRAY;
	bool flag_separatore = false;
	bool flag_eof = false;
	do{
		appoggio1 = getchar();
		if ((appoggio1 >= '0') && (appoggio1 <= '9')) {
			stringa[i1] = appoggio1;
		} else {
			switch (appoggio1){
			case '.':
			case ',':
				if (flag_separatore == false) {
					flag_separatore = true;
					stringa[i1] = appoggio1;
				} else {
					i1 = MAX_CHAR;
				}
				break;
			case '\n':
			case EOF:
				flag_eof = true;
				break;
			default:
				i1 = MAX_CHAR;
				break;
			}
		} 
		i1++;
	}while ((i1 < MAX_CHAR) && (flag_eof == false));

	if (flag_eof == false) {
		while (getchar() != '\n') {
		}
		return 0;
	} else {
		stringa[i1] = 0;	//char fine stringa
		return i1;			//lunghezza stringa
	}
}
		
static float conv_num(char *stringa1, const int len1)
{
	int i1, posizione_separatore;
	float totale1 = 0;
	float coefficiente = 0.1;
	
	posizione_separatore = len1;
	for(i1 = INIZIO_ARRAY; i1 < len1 - 1; i1++) {
		if ((stringa1[i1] != ',') && (stringa1[i1] != '.')) {
			coefficiente = coefficiente * 10;
		} else {
			posizione_separatore = i1;
			break;
		}
	}

	for(i1 = INIZIO_ARRAY; i1 < len1 - 1; i1++) {
		if (i1 != posizione_separatore) {
			totale1 += ((stringa1[i1] - '0') * coefficiente);
			coefficiente = coefficiente / 10;
		}
	}
	return totale1;
}
