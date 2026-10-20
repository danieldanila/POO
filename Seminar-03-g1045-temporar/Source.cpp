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
	const int id;
	TipMoneda tipMoneda;
	double valoareRON;
	float comisionBanca;
	unsigned valabilitateZile;
	char* numeBanca;

	double* istoricValori;
	unsigned numarInregistrari;

	static unsigned numarCursuriValutare;

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

	CursValutar(TipMoneda moneda) : id(1)
	{
		this->tipMoneda = moneda;
	}

	CursValutar(TipMoneda moneda) : tipMoneda(moneda), id(1)
	{

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
			cout << endl;
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

	void setValoareRON(double valoareNouaRON)
	{
		if (valoareNouaRON > 0)
		{
			//(*this).valoareRON = valoareNouaRON;
			this->valoareRON = valoareNouaRON;
		}
		else
		{
			cout << "Valoarea RON nu s-a modificat. Valoarea noua in RON este zero sau negativa." << endl;
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

	void actualizareCursValutar();
};
unsigned CursValutar::numarCursuriValutare = 0;

void CursValutar::actualizareCursValutar()
{
	// ....
}

class CasaSchimb
{
private:
	CursValutar cursValutar;
};

class CursValutarRomania : public CursValutar
{
private:
	double valoareRONPreferentiala;

public:
	CursValutarRomania()
	{
		this->valoareRONPreferentiala = 0;
	}

	CursValutarRomania(double valoareRONPreferentiala)
	{
		this->valoareRONPreferentiala = valoareRONPreferentiala;
	}

	CursValutarRomania(double valoareRONPreferentiala, TipMoneda tipMoneda, double valoareRON,
		float comisionBanca, unsigned valabilitateZile, const char* numeBanca)
		: CursValutar(tipMoneda, valoareRON, comisionBanca, valabilitateZile, numeBanca)
	{
		this->valoareRONPreferentiala = valoareRONPreferentiala;
	}

	void afisareCursValutarRomania()
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

CursValutar citesteCursValutar()
{
	CursValutar cursValutar;

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

	//char buffer[DIMENSIUNE_BUFFER];
	//cout << "Introduceti numele bancii: ";
	//cin.getline(buffer, DIMENSIUNE_BUFFER);

	//const char* bufferConstant;
	//unsigned dimensiune = strlen(buffer) + 1;
	//bufferConstant = new char[dimensiune];
	//strcpy_s(bufferConstant, dimensiune, buffer);

	//
	//CursValutar(optiuneMoneda, valoareRON, comisionBanca, valabilitateZile, buffer);

	return cursValutar;
}

void initializeazaIstoricValori(double** istoricValori, unsigned numarElemente, const double* valoriSursa)
{
	if (istoricValori == nullptr || numarElemente <= 0)
	{
		return;
	}

	if (*istoricValori != nullptr)
	{
		delete[] * istoricValori;
	}

	*istoricValori = new double[numarElemente];

	for (int i = 0; i < numarElemente; i++)
	{
		(*istoricValori)[i] = valoriSursa[i];
		//*(*istoricValori + i) = *(valoriSursa + i);
	}
}

int main()
{
	CursValutar euroLei(TipMoneda::EURO, 5.2780, 0.01f, 1, "Banca 1");
	euroLei.afiseazaCursValutar();

	CursValutar dolarLei(TipMoneda::DOLAR, 4.60, 0.05f, 5, "Banca 2");
	dolarLei.afiseazaCursValutar();

	//CursValutar lireLei = citesteCursValutar();
	//lireLei.afiseazaCursValutar();

	euroLei.setValoareRON(4.98);
	euroLei.afiseazaCursValutar();

	cout << euroLei.getValoareRON() << endl;

	//CursValutar* eroare = nullptr;
	//eroare->modificaValoareRON(10);

	//double valoriIstoriceEuro[] = { 4.9520, 4.9680, 4.9750, 4.9800 };
	//euroLei.numarInregistrari = 4;

	//initializeazaIstoricValori(&euroLei.istoricValori, euroLei.numarInregistrari, valoriIstoriceEuro);
	//euroLei.afiseazaCursValutar();

	CursValutarRomania euroLeiPreferential(4.80);

	euroLeiPreferential.afiseazaCursValutar();

	CursValutarRomania dolarLeiPreferential(4.80, TipMoneda::DOLAR, 4.60, 0.05f, 5, "Banca 3");
	dolarLeiPreferential.afiseazaCursValutar();

	dolarLeiPreferential.afisareCursValutarRomania();


	return 0;
}
