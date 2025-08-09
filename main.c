#include <stdio.h>

#define MAX_CHAR 5
#define NUM_OPZIONI 6
#define PI_GRECO 3.14

#include "header_funz.h"
#include "input_e_conversione_int_float.c"

int main()
{	
	float param1[NUM_OPZIONI] = {1,4,15000,0,4,0};	//valori iniziali	
	//0 - num taglienti
	//1 - diametro
	//2 - RPM
	//3 - velocità taglio
	//3 - avanzamento
	//5 - spessore truciolo

	int max_rif, i1;
	float float_appoggio;
	
	calcola_cutspeed(param1);	//valori iniziali
	calcola_truciolo(param1);		//valori iniziali
	
	i1 = 0;
	while (i1 >= 0) 
	{
		refresh_schermata(param1);
		printf("inserisci ");
		switch (i1)
		{
			case 0:
				printf("numero taglienti: ");
				max_rif = 6;
				break;
			case 1:
				printf("diametro fresa: ");
				max_rif = 12;
				break;
			case 2:
				printf("RPM: ");
				max_rif = 60000;
				break;
			case 3:
				printf("velocita' di taglio (rotazione): ");
				max_rif = 999;
				break;
			case 4:
				printf("velocita' di avanzamento: ");
				max_rif = 20;
				break;
			case 5:
				printf("spessore truciolo: ");
				max_rif = 2;
				break;
		}
		
		float_appoggio = input_val(MAX_CHAR);
		if (float_appoggio > max_rif) float_appoggio = max_rif;
		
		if (float_appoggio > 0) 
		{
			param1[i1] = float_appoggio;
			max_rif = 0; //riciclo max_rif come flag	
			switch (i1)
			{
				case 1: //diametro fresa
					calcola_cutspeed(param1);
				case 2: //RPM
					calcola_cutspeed(param1);
					break;
				case 3: //velocità di taglio
					calcola_RPM(param1);
					break;
				case 5: //spessore truciolo
					calcola_avanzamento(param1);
					break;
			}
			calcola_truciolo(param1);
		}
		else
		{
			switch ((int)float_appoggio)
			{
				case 0: //scorrere voce
					if (i1 < NUM_OPZIONI - 1) i1++;
					else i1 = 0;
					break;
				case -1:
					i1 = (int)float_appoggio; //quit
					break;

			}
		}
	}
	return 0; 
}

void calcola_RPM(float *cr_param){ cr_param[2] = (cr_param[3] * 1000) / (PI_GRECO * cr_param[1]);}
void calcola_cutspeed(float *cc_param){cc_param[3] = cc_param[2] * PI_GRECO * cc_param[1] * 0.001;}
void calcola_avanzamento(float *ca_param){ca_param[4] = ca_param[5] * ca_param[2] * ca_param[0] * 0.001;}
void calcola_truciolo(float *ct_param){ ct_param[5] = (ct_param[4] * 1000) / (ct_param[2] * ct_param[0]);}

void refresh_schermata(float *rs_param)
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); //clear screen
	printf("\n	numero di taglienti:		%1.0f\n",*rs_param);
	printf("\n	diametro fresa:			%1.1f mm\n",*(rs_param + 1));
	printf("\n		RPM:			%5.0f\n",rs_param[2]);
	printf("\n	 velocita' taglio:		%3.1f m/min\n",rs_param[3]);
	printf("\nvelocita' avanzamento:			%2.1f m/min\n",rs_param[4]);
	printf("\n	spessore truciolo:		%1.2f\n\n\n",rs_param[5]);
}
