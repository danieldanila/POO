#include <iostream>

using namespace std;

#define DIMENSIUNE_BUFFER 100

enum TipMoneda
{
	EURO,
	DOLAR,
	LIRA
};

struct CursValutar
{
	TipMoneda tipMoneda = TipMoneda::EURO;
	double valoareRON = 0;
	float comisionBanca = 0.0f;
	unsigned valabilitateZile = 0;
	char* numeBanca = nullptr;

	double* istoricValori = nullptr;
	unsigned numarInregistrari = 0;

	void afiseazaCursValutar() const
	{
		cout << "\nCursul valutar pentru moneda: ";

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

		cout << "Valorile istorice sunt: ";
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

	void modificaValoareRON(double valoareNouaRON)
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

	void eliberareMemorie()
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
};

CursValutar creazaCursValutar(TipMoneda tipMoneda, double valoareRON, float comisionBanca, unsigned valabilitateZile, const char* numeBanca)
{
	CursValutar cursValutar;

	cursValutar.tipMoneda = tipMoneda;
	cursValutar.valoareRON = valoareRON;
	cursValutar.comisionBanca = comisionBanca;
	cursValutar.valabilitateZile = valabilitateZile;

	if (numeBanca != nullptr)
	{
		unsigned dimensiune = strlen(numeBanca) + 1;
		cursValutar.numeBanca = new char[dimensiune];
		strcpy_s(cursValutar.numeBanca, dimensiune, numeBanca);
	}

	return cursValutar;
}

CursValutar citesteCursValutar()
{
	CursValutar cursValutar;

	cout << "\nSelectati moneda (0 - EURO, 1 - DOLAR, 2 - LIRA): ";
	int optiuneMoneda;
	cin >> optiuneMoneda;
	cursValutar.tipMoneda = (TipMoneda)optiuneMoneda;

	cout << "Introduceti valoarea in RON: ";
	cin >> cursValutar.valoareRON;

	cout << "Introduceti comisionul perceput de banca: ";
	cin >> cursValutar.comisionBanca;

	cout << "Introduceti valabilitatea in zile: ";
	cin >> cursValutar.valabilitateZile;

	cin.ignore();

	char buffer[DIMENSIUNE_BUFFER];
	cout << "Introduceti numele bancii: ";
	cin.getline(buffer, DIMENSIUNE_BUFFER);

	unsigned dimensiune = strlen(buffer) + 1;
	cursValutar.numeBanca = new char[dimensiune];
	strcpy_s(cursValutar.numeBanca, dimensiune, buffer);

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
	CursValutar euroLei = creazaCursValutar(TipMoneda::EURO, 5.2780, 0.01f, 1, "Banca 1");
	euroLei.afiseazaCursValutar();

	CursValutar dolarLei = creazaCursValutar(TipMoneda::DOLAR, 4.60, 0.05f, 5, "Banca 2");
	dolarLei.afiseazaCursValutar();

	CursValutar lireLei = citesteCursValutar();
	lireLei.afiseazaCursValutar();

	euroLei.modificaValoareRON(4.98);
	euroLei.afiseazaCursValutar();

	//CursValutar* eroare = nullptr;
	//eroare->modificaValoareRON(10);

	double valoriIstoriceEuro[] = { 4.9520, 4.9680, 4.9750, 4.9800 };
	euroLei.numarInregistrari = 4;

	initializeazaIstoricValori(&euroLei.istoricValori, euroLei.numarInregistrari, valoriIstoriceEuro);
	euroLei.afiseazaCursValutar();

	euroLei.eliberareMemorie();
	dolarLei.eliberareMemorie();
	//lireLei.eliberareMemorie();

	return 0;
}
