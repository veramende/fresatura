float input_val(int max_len)	//in presenza di casi particolari viene restitutito il flag:
								// 0: quando la stringa inserita è vuota (solo tasto invio)
								//-1: quando viene premuto il tasto 'q' (quit)
								//-2: quando l'input non è valido (stringa troppo lunga o caratteri speciali)
{
	int i1, flag1, appoggio1, comando1[max_len], len2, ind_sep = -1;
	
	flag1 = 1;
	i1 = 0;
	while(flag1 == 1) //primo array per rappresentare parte intera
	{
		appoggio1 = getchar();
		if ((appoggio1 >= '0') && (appoggio1 <= '9'))
		{
			comando1[i1] = appoggio1;
			i1++;
			if (i1 > (max_len)) flag1 = -2; //se troppi caratteri mando in errore
		}
		else
		{
			switch (appoggio1)
			{
				case '\n':
				case EOF:
					if (i1 == 0) flag1 = 0; //segnalo stringa vuota
					else flag1 = 2;			//stringa ok
					break;
				case 'q':
					flag1 = -1;
					break;
				case '.':
				case ',':
					if (ind_sep == -1) ind_sep = i1; 	//segnalo che è stato trovato un separatore salvando la sua posizione
					else flag1 = -2; 					//se ci sono 2 separatori (punto o virgola) la stringa è sbagliata
					break;
				default: //se nessuno dei precedenti vuol dire che è un carattere non consentito
					flag1 = -2;
					break;
			}
		}
	}
	if (flag1 < 0) while ((appoggio1 != '\n') && (appoggio1 != EOF)) appoggio1 = getchar(); //se non ho rilevato la fine del buffer lo vado a svuotare
	if (flag1 != 2) return flag1;
	
	len2 = i1;
	if (ind_sep == -1) ind_sep = len2; //se non è stata inserita la virgola lo tratto come un intero
	return conv_ascii_num(comando1,len2,ind_sep);
}

float conv_ascii_num(int *primo_val, int len1, int pos_sep) //per le conversioni di valori interi basta impostare il separatore alla posizione massima
{
	int i1;
	float totale1 = 0;
	float coefficiente = 0.1;
	
	for(i1=0;i1<pos_sep;i1++) coefficiente = coefficiente * 10;
	
	for(i1=0;i1<len1;i1++)
	{
		if ((primo_val[i1] != '.') && (primo_val[i1] != ',')) //chiaramente escludo la virgola
		{
			totale1 += (float)(primo_val[i1]-48)*coefficiente;
			coefficiente = coefficiente / 10;
		}
	}
	return totale1;
}
