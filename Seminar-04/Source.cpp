#include <iostream>

using namespace std;

#define DIMENSIUNE_BUFFER 100

enum TipMoneda
{
	EURO,
	DOLAR,
	LIRA
};

class CursValutar
{
private:
	const unsigned id;
	TipMoneda tipMoneda;
	float comisionBanca;
	unsigned valabilitateZile;
	char* numeBanca;

	double* istoricValori;
	unsigned numarInregistrari;

	static unsigned numarCursuriValutare;

protected:
	double valoareRON;

public:
	CursValutar() : id(numarCursuriValutare)
	{
		this->tipMoneda = TipMoneda::EURO;
		this->valoareRON = 0;
		this->comisionBanca = 0.0f;
		this->valabilitateZile = 0;
		this->numeBanca = nullptr;
		this->istoricValori = nullptr;
		this->numarInregistrari = 0;

		CursValutar::numarCursuriValutare++;
	}

	CursValutar(TipMoneda tipMoneda, double valoareRON, float comisionBanca,
		unsigned valabilitateZile, const char* numeBanca) : id(numarCursuriValutare)
	{
		this->tipMoneda = tipMoneda;
		this->valoareRON = valoareRON;
		this->comisionBanca = comisionBanca;
		this->valabilitateZile = valabilitateZile;

		if (numeBanca != nullptr)
		{
			unsigned dimensiune = strlen(numeBanca) + 1;
			this->numeBanca = new char[dimensiune];
			strcpy_s(this->numeBanca, dimensiune, numeBanca);
		}
		else
		{
			this->numeBanca = nullptr;
		}

		this->istoricValori = nullptr;
		this->numarInregistrari = 0;

		CursValutar::numarCursuriValutare++;
	}

	CursValutar(const CursValutar& altCursValutar) : id(numarCursuriValutare)
	{
		this->tipMoneda = altCursValutar.tipMoneda;
		this->valoareRON = altCursValutar.valoareRON;
		this->comisionBanca = altCursValutar.comisionBanca;
		this->valabilitateZile = altCursValutar.valabilitateZile;

		if (altCursValutar.numeBanca != nullptr)
		{
			unsigned dimensiune = strlen(altCursValutar.numeBanca) + 1;
			this->numeBanca = new char[dimensiune];
			strcpy_s(this->numeBanca, dimensiune, altCursValutar.numeBanca);
		}
		else
		{
			this->numeBanca = nullptr;
		}

		if (altCursValutar.istoricValori != nullptr && altCursValutar.numarInregistrari > 0)
		{
			this->numarInregistrari = altCursValutar.numarInregistrari;
			this->istoricValori = new double[this->numarInregistrari];

			for (unsigned i = 0; i < altCursValutar.numarInregistrari; i++)
			{
				this->istoricValori[i] = altCursValutar.istoricValori[i];
			}
		}
		else
		{
			this->numarInregistrari = 0;
			this->istoricValori = nullptr;
		}

		CursValutar::numarCursuriValutare++;
	}

	CursValutar& operator=(const CursValutar& altCursValutar)
	{
		if (this == &altCursValutar)
		{
			return *this;
		}

		this->tipMoneda = altCursValutar.tipMoneda;
		this->valoareRON = altCursValutar.valoareRON;
		this->comisionBanca = altCursValutar.comisionBanca;
		this->valabilitateZile = altCursValutar.valabilitateZile;

		if (this->numeBanca != nullptr)
		{
			delete[] this->numeBanca;
		}

		if (altCursValutar.numeBanca != nullptr)
		{
			unsigned dimensiune = strlen(altCursValutar.numeBanca) + 1;
			this->numeBanca = new char[dimensiune];
			strcpy_s(this->numeBanca, dimensiune, altCursValutar.numeBanca);
		}
		else
		{
			this->numeBanca = nullptr;
		}

		if (this->istoricValori != nullptr)
		{
			delete[] this->istoricValori;
		}

		if (altCursValutar.istoricValori != nullptr && altCursValutar.numarInregistrari > 0)
		{
			this->numarInregistrari = altCursValutar.numarInregistrari;
			this->istoricValori = new double[this->numarInregistrari];

			for (unsigned i = 0; i < altCursValutar.numarInregistrari; i++)
			{
				this->istoricValori[i] = altCursValutar.istoricValori[i];
			}
		}
		else
		{
			this->istoricValori = nullptr;
			this->numarInregistrari = 0;
		}

		return *this;
	}

	double getValoareRON() const
	{
		return this->valoareRON;
	}

	void setValoareRON(double valoareRON)
	{
		if (valoareRON > 0)
		{
			this->valoareRON = valoareRON;
		}
		else
		{
			cout << "Valoarea RON nu s-a modificat. Valoarea noua in RON este zero sau negativa." << endl;
		}
	}

	void setIstoricValori(unsigned numarInregistrari, const double* valoriSursa)
	{
		if (numarInregistrari == 0 || valoriSursa == nullptr)
		{
			return;
		}

		if (this->istoricValori != nullptr)
		{
			delete[] this->istoricValori;
		}

		this->numarInregistrari = numarInregistrari;
		this->istoricValori = new double[this->numarInregistrari];

		for (unsigned i = 0; i < this->numarInregistrari; i++)
		{
			this->istoricValori[i] = valoriSursa[i];
		}
	}

	void setValoareIstorica(unsigned index, double valoare) 
	{
		if (this->istoricValori != nullptr && index < this->numarInregistrari) 
		{
			this->istoricValori[index] = valoare;
		}
	}

	~CursValutar()
	{
		if (this->numeBanca != nullptr)
		{
			delete[] this->numeBanca;
			this->numeBanca = nullptr;
		}

		if (this->istoricValori != nullptr)
		{
			delete[] this->istoricValori;
			this->istoricValori = nullptr;
		}
	}

	double convertesteInValuta(double sumaRON);

	friend void comparaComisioane(const CursValutar& cursValutar1, const CursValutar& cursValutar2);
	friend ostream& operator<<(ostream& ostream, const CursValutar& cursValutar);
	friend istream& operator>>(istream& istream, CursValutar& cursValutar);
};
unsigned CursValutar::numarCursuriValutare = 0;

double CursValutar::convertesteInValuta(double sumaRON)
{
	if (sumaRON <= 0 || this->valoareRON <= 0)
	{
		return 0.0;
	}

	double comision = sumaRON * this->comisionBanca;
	double sumaNeta = sumaRON - comision;

	double sumaValuta = sumaNeta / this->valoareRON;

	return sumaValuta;
}

ostream& operator<<(ostream& ostream, const CursValutar& cursValutar)
{
	ostream << "\nID-ul cursului valutar este: " << cursValutar.id << endl;

	ostream << "\tCursul valutar pentru moneda: ";
	switch (cursValutar.tipMoneda)
	{
	case TipMoneda::EURO:
		ostream << "EURO";
		break;
	case TipMoneda::DOLAR:
		ostream << "DOLAR";
		break;
	case TipMoneda::LIRA:
		ostream << "LIRA";
		break;
	default:
		ostream << "Necunoscuta";
		break;
	}
	ostream << endl;

	ostream << "\tValoare in RON este: " << cursValutar.valoareRON << endl;
	ostream << "\tComisionul perceput de banca este: " << cursValutar.comisionBanca << endl;
	ostream << "\tValabilitatea in zile este: " << cursValutar.valabilitateZile << endl;

	ostream << "\tNumele bancii este: ";
	if (cursValutar.numeBanca != nullptr)
	{
		ostream << cursValutar.numeBanca;
	}
	else
	{
		ostream << "necunoscut";
	}
	ostream << endl;

	ostream << "\tValorile istorice sunt: ";
	if (cursValutar.istoricValori != nullptr && cursValutar.numarInregistrari > 0)
	{
		for (unsigned i = 0; i < cursValutar.numarInregistrari; i++)
		{
			ostream << cursValutar.istoricValori[i] << " ";
		}
	}
	else
	{
		ostream << "nu exista";
	}
	ostream << endl;

	return ostream;
}

istream& operator>>(istream& istream, CursValutar& cursValutar)
{
	cout << "\nSelectati moneda (0 - EURO, 1 - DOLAR, 2 - LIRA): ";
	int optiuneMoneda;
	istream >> optiuneMoneda;
	cursValutar.tipMoneda = (TipMoneda)optiuneMoneda;

	cout << "Introduceti valoarea in RON: ";
	istream >> cursValutar.valoareRON;

	cout << "Introduceti comisionul perceput de banca: ";
	istream >> cursValutar.comisionBanca;

	cout << "Introduceti valabilitatea in zile: ";
	istream >> cursValutar.valabilitateZile;

	cin.ignore();

	char buffer[DIMENSIUNE_BUFFER];
	cout << "Introduceti numele bancii: ";
	istream.getline(buffer, DIMENSIUNE_BUFFER);

	if (cursValutar.numeBanca != nullptr)
	{
		delete[] cursValutar.numeBanca;
		cursValutar.numeBanca = nullptr;
	}

	if (buffer[0] != '\0')
	{
		unsigned dimensiune = strlen(buffer) + 1;
		cursValutar.numeBanca = new char[dimensiune];
		strcpy_s(cursValutar.numeBanca, dimensiune, buffer);
	}

	return istream;
}

void comparaComisioane(const CursValutar& cursValutar1, const CursValutar& cursValutar2)
{
	if (cursValutar1.comisionBanca > cursValutar2.comisionBanca)
	{
		cout << "Banca " << cursValutar1.numeBanca <<
			" are comisioane mai mari ca banca " << cursValutar2.numeBanca << endl;
	}
	else if (cursValutar1.comisionBanca < cursValutar2.comisionBanca)
	{
		cout << "Banca " << cursValutar1.comisionBanca <<
			" are comisioane mai mici ca banca " << cursValutar2.comisionBanca << endl;
	}
	else
	{
		cout << "Ambele banci au aceleasi comisioane" << endl;
	}
}

class CursValutarRomanesc : public CursValutar
{
private:
	double valoareRONPreferentiala;

public:
	CursValutarRomanesc()
	{
		this->valoareRONPreferentiala = 0;
	}

	CursValutarRomanesc(double valoareRONPreferentiala)
	{
		this->valoareRONPreferentiala = valoareRONPreferentiala;
	}

	CursValutarRomanesc(double valoareRONPreferentiala, TipMoneda tipMoneda, double valoareRON,
		float comisionBanca, unsigned valabilitateZile, const char* numeBanca)
		: CursValutar(tipMoneda, valoareRON, comisionBanca, valabilitateZile, numeBanca)
	{
		this->valoareRONPreferentiala = valoareRONPreferentiala;
	}

	void afisareCursValutarRomanesc()
	{
		cout << *this;
		cout << "\tValoarea RON preferentiala este: " << this->valoareRONPreferentiala << " (valoarea RON normala este: "
			<< this->valoareRON << ")" << endl;
	}

	double getValoareRONPreferentiala() const
	{
		return this->valoareRONPreferentiala;
	}

	void setValoareRONPreferentiala(double valoareRONPreferentiala)
	{
		if (valoareRONPreferentiala > 0)
		{
			this->valoareRONPreferentiala = valoareRONPreferentiala;
		}
	}
};

int main()
{
	CursValutar euroLei(TipMoneda::EURO, 5.2780, 0.01f, 1, "Banca 1");
	cout << euroLei;

	CursValutar dolarLei(TipMoneda::DOLAR, 4.60, 0.05f, 5, "Banca 2");
	cout << dolarLei;

	CursValutar lireLei;
	// operator>>(cin, euroLei);
	cin >> lireLei;
	cout << lireLei;

	double valoriIstoriceEuro[] = { 4.9520, 4.9680, 4.9750, 4.9800 };
	euroLei.setIstoricValori(4, valoriIstoriceEuro);
	cout << euroLei;

	euroLei.setValoareRON(4.98);
	cout << "\nValoarea RON a euroLei dupa folosirea setter-ului: " << euroLei.getValoareRON() << endl;

	cout << "\nValoarea in valuta a 500 RON este: " << euroLei.convertesteInValuta(500) << endl;

	CursValutar euroLeiCopie = euroLei;
	euroLeiCopie.setValoareIstorica(0, 1000);
	cout << euroLeiCopie;
	cout << euroLei;

	// dolarLei.operator=(euroLei);
	dolarLei = euroLei;
	cout << euroLei;
	// operator<<(cout, dolarLei);
	cout << dolarLei;

	CursValutarRomanesc euroLeiPreferential(5.20);
	cout << euroLeiPreferential;
	euroLeiPreferential.afisareCursValutarRomanesc();

	CursValutarRomanesc dolarLeiPreferential(4.60, TipMoneda::DOLAR, 4.70, 0.05f, 5, "Banca Romaneasca 1");
	cout << dolarLeiPreferential;
	dolarLeiPreferential.afisareCursValutarRomanesc();

	return 0;
}
