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
	int valabilitateZile = 0;
	char* numeBanca = nullptr;

	double* istoricValori = nullptr;
	unsigned dimensiuneIstoric = 0;

	void afiseazaCursValutar()
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
		}
		cout << endl;

		cout << "\tValoare in RON este: " << this->valoareRON << endl;
		cout << "\tComisionul perceput de banca este: " << this->comisionBanca << endl;
		cout << "\tValabilitatea in zile este: " << this->valabilitateZile << endl;

		if (this->numeBanca != nullptr)
		{
			cout << "\Numele bancii este: " << this->numeBanca << endl;
		}
		else
		{
			cout << "\Numele bancii este nedefinit";
		}

		cout << endl;
	}

	void modificaValoareRON(double valoareNouaRON)
	{
		if (valoareNouaRON > 0)
		{
			//(*cursValutar).valoareRON = valoareNouaRON;
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
	}
};

CursValutar creazaCursValutar(TipMoneda tipMoneda, double valoareRON, float comisionBanca, int valabilitateZile, const char* numeBanca)
{
	CursValutar cursValutar;

	cursValutar.tipMoneda = tipMoneda;
	cursValutar.valoareRON = valoareRON;
	cursValutar.comisionBanca = comisionBanca;
	cursValutar.valabilitateZile = valabilitateZile;

	unsigned dimensiune = strlen(numeBanca) + 1;
	cursValutar.numeBanca = new char[dimensiune];
	strcpy_s(cursValutar.numeBanca, dimensiune, numeBanca);

	return cursValutar;
}

CursValutar citesteCursValutar()
{
	CursValutar cursValutar;

	cout << "\nIntroduceti moneda (EURO - 0, DOLAR - 1, LIRA - 2): ";
	int monedaAleasa;
	cin >> monedaAleasa;

	switch (monedaAleasa)
	{
	case 0:
		cursValutar.tipMoneda = TipMoneda::EURO;
		break;
	case 1:
		cursValutar.tipMoneda = TipMoneda::DOLAR;
		break;
	case 2:
		cursValutar.tipMoneda = TipMoneda::LIRA;
		break;
	default:
		cursValutar.tipMoneda = TipMoneda::EURO;
	}

	cout << "Introduceti valoarea in RON: ";
	cin >> cursValutar.valoareRON;

	cout << "Introduceti comisionul perceput de banca: ";
	cin >> cursValutar.comisionBanca;

	cout << "Introduceti valabilitatea in zile: ";
	cin >> cursValutar.valabilitateZile;

	char buffer[DIMENSIUNE_BUFFER];
	cout << "Introduceti numele bancii: ";
	cin.get();
	cin.getline(buffer, DIMENSIUNE_BUFFER);

	unsigned dimensiune = strlen(buffer) + 1;
	cursValutar.numeBanca = new char[dimensiune];
	strcpy_s(cursValutar.numeBanca, dimensiune, buffer);

	return cursValutar;
}

void initializareIstoricValori(double** istoricValori, unsigned dimensiuneIstoricValori, double* valori)
{
	if (*istoricValori != nullptr)
	{
		delete[] * istoricValori;
		*istoricValori = nullptr;
	}

	if (dimensiuneIstoricValori <= 0)
	{
		return;
	}

	*istoricValori = new double[dimensiuneIstoricValori];

	for (int i = 0; i < dimensiuneIstoricValori; i++)
	{
		(*istoricValori)[i] = valori[i];
		//(*istoricValori)  = valori + i;
	}
}

int main()
{
	CursValutar euroLei = creazaCursValutar(TipMoneda::EURO, 5.2780, 0.01f, 1, "Banca 1");
	euroLei.afiseazaCursValutar();

	unsigned dimensiuneIstoricValori = 3;
	double valori[] = { 5.22, 5.33, 5.44 };
	initializareIstoricValori(&euroLei.istoricValori, dimensiuneIstoricValori, valori);

	CursValutar dolarLei = creazaCursValutar(TipMoneda::DOLAR, 4.60, 0.05f, 5, "Banca 2");
	dolarLei.afiseazaCursValutar();

	//CursValutar lireLei = citesteCursValutar();
	//lireLei.afiseazaCursValutar();

	euroLei.modificaValoareRON(100);
	euroLei.afiseazaCursValutar();

	//CursValutar* eroare = nullptr;
	//eroare->modificaValoareRON(100);

	euroLei.eliberareMemorie();
	dolarLei.eliberareMemorie();
	//lireLei.eliberareMemorie();

	return 0;
}
