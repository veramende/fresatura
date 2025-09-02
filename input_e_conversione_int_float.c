#include <stdio.h> //serve solo per getchar()
#include "header_conversione.h"

#define INIZIO_ARRAY 0
#define VALORE_INZIALIZZATO -1

struct inserimento input_val(const int max_len, const int chiamante)
{
	int i1, appoggio1, comando1[max_len], iv_len, pos_sep;
	struct inserimento dato_inserito;
	
	int iterazioni = 0;
	
	//inizializzazioni
	pos_sep = VALORE_INZIALIZZATO;
	dato_inserito.flag = val_default;
	dato_inserito.numero = 0;
	dato_inserito.indice = fac_default;
	
	for (i1 = INIZIO_ARRAY; dato_inserito.flag == val_default; i1++) {
		if (i1 > (max_len)) {
			dato_inserito.flag = input_non_valido;
			break;
		}
		appoggio1 = getchar();
		if ((appoggio1 >= '0') && (appoggio1 <= '9')) {
			comando1[i1] = appoggio1;
		} else {
			if ((i1 == INIZIO_ARRAY) && (chiamante == ch_main)) {
				switch (appoggio1) {
				case fac_quit:
					dato_inserito.flag = quit;
					break;
				case fac_diametro:
					dato_inserito.indice = i_diametro;
					break;
				case fac_ntagl:
					dato_inserito.indice = i_ntagl;
					break;
				case fac_profondita:
					dato_inserito.indice = i_profondita;
					break;
				case fac_cutspeed:
					dato_inserito.indice = i_cutspeed;
					break;
				case fac_coef_mat:
					dato_inserito.indice = i_coef_mat;
					break;
				case fac_feedrate:
					dato_inserito.indice = i_feedrate;
					break;
				case '\n':
				case EOF:
					dato_inserito.flag = input_vuoto;
					break;
				default:
					dato_inserito.flag = input_non_valido;
					break;
				}
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
					dato_inserito.flag = input_corretto;
					break;
				default:
					dato_inserito.flag = input_non_valido;
					break;
				}
			}
		}
	}
	if ((dato_inserito.flag != input_corretto) && (dato_inserito.flag != input_vuoto) && (dato_inserito.flag != mod_facoltativo)) {
		while ((appoggio1 != '\n') && (appoggio1 != EOF)) 
			appoggio1 = getchar(); //svuota stdin
	}
	
	if (dato_inserito.flag == input_corretto) {
		iv_len = i1;
		if (pos_sep == VALORE_INZIALIZZATO)
			pos_sep = iv_len;
		dato_inserito.numero = conv_ascii_num(comando1,iv_len,pos_sep);
	}
	return dato_inserito;
}

float conv_ascii_num(int *stringa1, int len1, int pos_sep) //per le conversioni di valori interi basta impostare il separatore alla posizione massima
{
	int i1;
	float totale1 = 0;
	float coefficiente = 0.1;
	
	for(i1=0;i1<pos_sep;i1++) coefficiente = coefficiente * 10;
	
	for(i1=0;i1<len1;i1++) {
		if ((stringa1[i1] != '.') && (stringa1[i1] != ',')) {
			totale1 += (float)(stringa1[i1]-'0')*coefficiente;
			coefficiente = coefficiente / 10;
		}
	}
	return totale1;
}
