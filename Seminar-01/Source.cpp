#include <iostream>

using namespace std;

struct CursValutar
{
	string numeMoneda = "";
	double valoareRON = 0;
	float comisionBanca = 0.0f;
	int valabilitateZile = 0;
};

CursValutar creazaCursValutar(string numeMoneda, double valoareRON, float comisionBanca, int valabilitateZile)
{
	CursValutar cursValutar;

	cursValutar.numeMoneda = numeMoneda;
	cursValutar.valoareRON = valoareRON;
	cursValutar.comisionBanca = comisionBanca;
	cursValutar.valabilitateZile = valabilitateZile;

	return cursValutar;
}

CursValutar citesteCursValutar()
{
	CursValutar cursValutar;

	cout << "\nIntroduceti numele monedei: ";
	cin >> cursValutar.numeMoneda;

	cout << "Introduceti valoarea in RON: ";
	cin >> cursValutar.valoareRON;

	cout << "Introduceti comisionul perceput de banca: ";
	cin >> cursValutar.comisionBanca;

	cout << "Introduceti valabilitatea in zile: ";
	cin >> cursValutar.valabilitateZile;

	return cursValutar;
}

void afiseazaCursValutar(const CursValutar& cursValutar)
{
	cout << "\nCursul valutar pentru moneda: " << cursValutar.numeMoneda << endl;
	cout << "\tValoare in RON este: " << cursValutar.valoareRON << endl;
	cout << "\tComisionul perceput de banca este: " << cursValutar.comisionBanca << endl;
	cout << "\tValabilitatea in zile: " << cursValutar.valabilitateZile << endl;
	cout << endl;
}

CursValutar modificaPrinValoareValoareRON(CursValutar cursValutar, double valoareNouaRON)
{
	if (valoareNouaRON > 0)
	{
		cursValutar.valoareRON = valoareNouaRON;
	}

	return cursValutar;
}

void modificaPrinPointerValoareRON(CursValutar* cursValutar, double valoareNouaRON)
{
	if (cursValutar != nullptr && valoareNouaRON > 0)
	{
		//(*cursValutar).valoareRON = valoareNouaRON;
		cursValutar->valoareRON = valoareNouaRON;
	}
	else
	{
		cout << "Valoarea RON nu s-a modificat. Cursul valutar primit este nullptr sau valoarea noua in RON este zero sau negativa." << endl;
	}
}

void modificaPrinReferintaValoareRON(CursValutar& cursValutar, double valoareNouaRON)
{
	if (valoareNouaRON > 0)
	{
		cursValutar.valoareRON = valoareNouaRON;
	}
}

int main()
{
	CursValutar euroLei = creazaCursValutar("EURO", 5.2780, 0.01f, 1);
	afiseazaCursValutar(euroLei);

	CursValutar dolarLei = creazaCursValutar("DOLAR", 4.60, 0.05f, 5);
	afiseazaCursValutar(dolarLei);

	CursValutar lireLei = citesteCursValutar();
	afiseazaCursValutar(lireLei);

	euroLei = modificaPrinValoareValoareRON(euroLei, 4.98);
	afiseazaCursValutar(euroLei);

	modificaPrinPointerValoareRON(&euroLei, 100);
	afiseazaCursValutar(euroLei);

	modificaPrinReferintaValoareRON(euroLei, 500);
	afiseazaCursValutar(euroLei);

	modificaPrinPointerValoareRON(nullptr, 10);

	return 0;
}
