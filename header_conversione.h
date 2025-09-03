enum valori_flag {
	input_non_valido = 0, 
	val_default,
	input_corretto,
	flag_quit = 'q',
	flag_diametro = 'd',
	flag_ntagl = 'n',
	flag_profondita = 'p',
	flag_cutspeed = 'c',
	flag_coef_mat = 'm',	//coefficiente di forza di taglio specifica per materiale
	flag_feedrate = 'f',
	flag_rpm = 'r',
	flag_feedspeed = 'a',
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
	i_cutspeed,
	i_feedrate,
	//solo calcolabili
	i_mat_asp_giro,		//da fare - mm^3/giro --> (profondita * diametro utile * avanzamento) / rpm
	i_mat_asp_dente, 	//da fare - materiale asportato / n taglienti
	i_kw, //da fare (materiale asportato * coefficiente taglio materiale) / (60 * 1000) - risultato in KW
	opzioni_disponibili,
};

struct inserimento {
	int flag;
	float numero;
};

enum opzioni_chiamante {
	ch_main,
	ch_ricors,
};

//funzioni
struct inserimento input_val(int max_len);
float conv_num(int *primo_val, int len1, int pos_sep); //conversione da stringa a float
bool check_flag_opzionali(int rif);
