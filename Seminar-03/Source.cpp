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

	void afiseazaCursValutar() const
	{
		cout << "\nID-ul cursului valutar este: " << this->id << endl;

		cout << "\tCursul valutar pentru moneda: ";
		switch (this->tipMoneda)
		{
		case TipMoneda::EURO:
			cout << "EURO";
			break;
		case TipMoneda::DOLAR:
			cout << "DOLAR";
			break;
		case TipMoneda::LIRA:
			cout << "LIRA";
			break;
		default:
			cout << "Necunoscuta";
			break;
		}
		cout << endl;

		cout << "\tValoare in RON este: " << this->valoareRON << endl;
		cout << "\tComisionul perceput de banca este: " << this->comisionBanca << endl;
		cout << "\tValabilitatea in zile este: " << this->valabilitateZile << endl;

		cout << "\tNumele bancii este: ";
		if (this->numeBanca != nullptr)
		{
			cout << this->numeBanca;
		}
		else
		{
			cout << "necunoscut";
		}
		cout << endl;

		cout << "\tValorile istorice sunt: ";
		if (this->istoricValori != nullptr && this->numarInregistrari > 0)
		{
			for (int i = 0; i < this->numarInregistrari; i++)
			{
				cout << this->istoricValori[i] << " ";
			}
		}
		else
		{
			cout << "nu exista";
		}
		cout << endl;
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

		for (int i = 0; i < this->numarInregistrari; i++)
		{
			this->istoricValori[i] = valoriSursa[i];
		}
	}

	static CursValutar citesteCursValutar()
	{
		cout << "\nSelectati moneda (0 - EURO, 1 - DOLAR, 2 - LIRA): ";
		int optiuneMoneda;
		cin >> optiuneMoneda;

		cout << "Introduceti valoarea in RON: ";
		double valoareRON;
		cin >> valoareRON;

		cout << "Introduceti comisionul perceput de banca: ";
		float comisionBanca;
		cin >> comisionBanca;

		cout << "Introduceti valabilitatea in zile: ";
		unsigned valabilitateZile;
		cin >> valabilitateZile;

		cin.ignore();

		char buffer[DIMENSIUNE_BUFFER];
		cout << "Introduceti numele bancii: ";
		cin.getline(buffer, DIMENSIUNE_BUFFER);

		return CursValutar((TipMoneda)optiuneMoneda, valoareRON, comisionBanca, valabilitateZile, buffer);
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
		this->afiseazaCursValutar();
		cout << "\tValoarea RON preferentiala este: " << this->valoareRONPreferentiala << endl;
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
	euroLei.afiseazaCursValutar();

	CursValutar dolarLei(TipMoneda::DOLAR, 4.60, 0.05f, 5, "Banca 2");
	dolarLei.afiseazaCursValutar();

	CursValutar lireLei = CursValutar::citesteCursValutar();
	lireLei.afiseazaCursValutar();

	double valoriIstoriceEuro[] = { 4.9520, 4.9680, 4.9750, 4.9800 };
	euroLei.setIstoricValori(4, valoriIstoriceEuro);
	euroLei.afiseazaCursValutar();

	euroLei.setValoareRON(4.98);
	cout << "\nValoarea RON a euroLei dupa folosirea setter-ului: " << euroLei.getValoareRON() << endl;

	cout << "\nValoarea in valuta a 500 RON este: " << euroLei.convertesteInValuta(500) << endl;

	CursValutarRomanesc euroLeiPreferential(4.80);
	euroLeiPreferential.afiseazaCursValutar();
	euroLeiPreferential.afisareCursValutarRomanesc();
	
	CursValutarRomanesc dolarLeiPreferential(4.80, TipMoneda::DOLAR, 4.60, 0.05f, 5, "Banca Romaneasca 1");
	dolarLeiPreferential.afiseazaCursValutar();
	dolarLeiPreferential.afisareCursValutarRomanesc();

	return 0;
}
