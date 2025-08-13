enum valori_flag {
	input_non_valido = -2, 
	quit, 
	input_vuoto, 
	val_default, 
	input_corretto
};

struct inserimento {
	enum valori_flag flag;
	float numero;
};

//funzioni
struct inserimento input_val(int max_len);
float conv_ascii_num(int *primo_val, int len1, int pos_sep); //conversione da stringa a float
