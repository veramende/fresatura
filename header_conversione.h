enum valori_flag {
	input_non_valido = 0,
	val_default,
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
	//inseribili opzionali
	i_diametro,
	i_ntagl,
	i_profondita,
	i_coef_mat,
	//calcolabili e definibili
	i_cutspeed,
	i_feedrate_generale,
	//solo calcolabili
	i_feedrate_per_tagliente,
	i_kw,
	opzioni_disponibili,
};

struct inserimento {
	int flag;
	float numero;
};

//funzioni
struct inserimento input_val(int max_len);

