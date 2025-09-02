enum valori_flag {
	input_non_valido = -2,
	quit, 
	input_vuoto, 
	val_default, 
	input_corretto,
	inserire_diametro,
};

struct inserimento {
	int flag;
	float numero;
};

enum input_facoltativi {
	fac_quit = 'q',
	fac_diametro = 'd',
	fac_ntagl = 'n',
	fac_profondita = 'p',
	fac_cutspeed = 'c',
	fac_coef_mat = 'm',	//coefficiente di forza di taglio specifica per materiale
	fac_feedrate = 'f',
};

//funzioni
struct inserimento input_val(int max_len);
float conv_ascii_num(int *primo_val, int len1, int pos_sep); //conversione da stringa a float
