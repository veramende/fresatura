enum valori_flag {
	input_non_valido = -2,
	quit, 
	input_vuoto, 
	val_default, 
	input_corretto,
	mod_facoltativo,
};

enum indici {
	//parametri del software cam
	i_rpm,
	i_feedspeed,
	//inseribili opzionali
	i_diametro,
	i_ntagl,		//da fare
	i_profondita,	//da fare
	i_coef_mat,		//da fare
	//calcolabili e definibili
	i_feedrate,
	i_cutspeed,
	//solo calcolabili
	i_mat_asp_giro,		//da fare - mm^3/giro --> (profondita * diametro utile * avanzamento) / rpm
	i_mat_asp_dente, 	//da fare - materiale asportato / n taglienti
	i_kw, //da fare (materiale asportato * coefficiente taglio materiale) / (60 * 1000) - risultato in KW
	opzioni_disponibili,
};

struct inserimento {
	int flag;
	int indice;
	float numero;
};

enum input_facoltativi {
	fac_default = -1,
	fac_quit = 'q',
	fac_diametro = 'd',
	fac_ntagl = 'n',
	fac_profondita = 'p',
	fac_cutspeed = 'c',
	fac_coef_mat = 'm',	//coefficiente di forza di taglio specifica per materiale
	fac_feedrate = 'f',
};

enum opzioni chiamante {
	ch_main;
	ch_ricors;
};

//funzioni
struct inserimento input_val(int max_len);
float conv_ascii_num(int *primo_val, int len1, int pos_sep); //conversione da stringa a float
