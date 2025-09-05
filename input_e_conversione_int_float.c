#include <stdio.h> //serve solo per getchar()
#include <stdbool.h>
#include "header_conversione.h"

#define INIZIO_ARRAY 0
#define VALORE_INZIALIZZATO -1

static bool check_flag_opzionali(int rif)
{
	switch (rif) {
	case flag_quit:
	case flag_diametro:
	case flag_ntagl:
	case flag_profondita:
	case flag_cutspeed:
	case flag_coef_mat:
	case flag_feedrate_generale:
	case flag_rpm:
	case flag_feedspeed:
		return true;
		break;
	default:
		return false;
	}
}

static float conv_num(int *stringa1, int len1, int pos_sep) //per le conversioni di valori interi basta impostare il separatore alla posizione massima
{
	int i1;
	float totale1 = 0;
	float coefficiente = 0.1;
	
	for(i1=0;i1<pos_sep;i1++)
		coefficiente = coefficiente * 10;
	for(i1=0;i1<len1;i1++) {
		if (i1 != pos_sep) {
			printf("\n%f\n", stringa1[i1] * coefficiente);
			totale1 += (float) (stringa1[i1] * coefficiente);
			coefficiente = coefficiente / 10;
		}
	}
	return totale1;
}

struct inserimento input_val(const int max_len)
{
	int i1, appoggio1, comando1[max_len], pos_sep;
	bool flag_eof = false;
	struct inserimento dato_inserito;
	
	//inizializzazioni
	pos_sep = VALORE_INZIALIZZATO;
	dato_inserito.flag = val_default;
	dato_inserito.numero = 0;
	for (i1 = INIZIO_ARRAY; i1 < max_len; i1++)
		comando1[i1] = 0;
	
	appoggio1 = getchar();
	if (check_flag_opzionali(appoggio1) == false) {
		dato_inserito.flag = input_non_valido;
	} else {
		if (appoggio1 == flag_quit) {
			dato_inserito.flag = flag_quit;
			return dato_inserito;
		} else {
			dato_inserito.flag = appoggio1;
		}
	}
	
	i1 = INIZIO_ARRAY - 1;
	while ((dato_inserito.flag != input_non_valido) && (flag_eof == false)) {
		i1++;
		if (i1 > max_len) {
			dato_inserito.flag = input_non_valido;
			break;
		}
		appoggio1 = getchar();
		if ((appoggio1 >= '0') && (appoggio1 <= '9')) {
			comando1[i1] = appoggio1 - '0';	//conversione da char a int
		} else {
			switch (appoggio1) {
			case ',':
			case '.':
				if (pos_sep == VALORE_INZIALIZZATO)
					pos_sep = i1;
				else
					dato_inserito.flag = input_non_valido;
				break;
			case '\n':
			case EOF:
				flag_eof = true;
				break;
			default:
				dato_inserito.flag = input_non_valido;
				break;
			}
		}
	}
	if (flag_eof == false) {
		while ((appoggio1 != '\n') && (appoggio1 != EOF)) 
			appoggio1 = getchar(); //svuota stdin
	}
	if (dato_inserito.flag != input_non_valido) {
		if (pos_sep == VALORE_INZIALIZZATO)
			pos_sep = i1;
		dato_inserito.numero = conv_num(comando1,i1,pos_sep);
	}
	return dato_inserito;
}