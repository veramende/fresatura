#include <stdio.h> //serve solo per getchar()
#include "header_conversione.h"

#define INIZIO_ARRAY 0
#define VALORE_INZIALIZZATO -1

struct inserimento input_val(int max_len)
{
	int i1, appoggio1, comando1[max_len], iv_len, pos_sep;
	struct inserimento dato_inserito;
	
	int iterazioni = 0;
	
	//inizializzazioni
	pos_sep = VALORE_INZIALIZZATO;
	dato_inserito.flag = val_default;
	dato_inserito.numero = 0;
	i1 = INIZIO_ARRAY;
	
	while (dato_inserito.flag == val_default) {
		appoggio1 = getchar();
		if ((appoggio1 >= '0') && (appoggio1 <= '9')) {
			comando1[i1] = appoggio1;
			i1++;
			if (i1 > (max_len))
				dato_inserito.flag = input_non_valido; 
		} else {
			switch (appoggio1) {
			case fac_quit:
				dato_inserito.flag = quit;
				break;
			case fac_diametro:
				dato_inserito.flag = inserire_diametro;
				break;
			case ',':
			case '.':
				if (pos_sep == VALORE_INZIALIZZATO)
					pos_sep = i1;
				else
					dato_inserito.flag = input_non_valido;
				break;
			case '\n':
			case EOF:
				if (i1 == INIZIO_ARRAY) 
					dato_inserito.flag = input_vuoto;
				else
					dato_inserito.flag = input_corretto;
			default:
				dato_inserito.flag = input_non_valido;
				break;
			}
		}
	}
	if ((dato_inserito.flag != input_corretto) && (dato_inserito.flag != input_vuoto)) {
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
