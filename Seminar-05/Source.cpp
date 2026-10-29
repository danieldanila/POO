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
public:
	class Banca
	{
	private:
		char* nume;
		float comision;

	public:
		Banca(const char* nume = nullptr, float comision = 0.0f)
		{
			if (nume != nullptr)
			{
				unsigned dimensiune = strlen(nume) + 1;
				this->nume = new char[dimensiune];
				strcpy_s(this->nume, dimensiune, nume);
			}
			else
			{
				this->nume = nullptr;
			}

			this->comision = comision;
		}

		Banca(const Banca& altaBanca)
		{
			if (altaBanca.nume != nullptr)
			{
				unsigned dimensiune = strlen(altaBanca.nume) + 1;
				this->nume = new char[dimensiune];
				strcpy_s(this->nume, dimensiune, altaBanca.nume);
			}
			else
			{
				this->nume = nullptr;
			}

			this->comision = altaBanca.comision;
		}

		Banca& operator=(const Banca& altaBanca)
		{
			if (this == &altaBanca)
			{
				return *this;
			}

			if (this->nume != nullptr)
			{
				delete[] this->nume;
			}

			if (altaBanca.nume != nullptr)
			{
				unsigned dimensiune = strlen(altaBanca.nume) + 1;
				this->nume = new char[dimensiune];
				strcpy_s(this->nume, dimensiune, altaBanca.nume);
			}
			else
			{
				this->nume = nullptr;
			}

			this->comision = altaBanca.comision;

			return *this;
		}

		const char* getNume() const
		{
			return this->nume;
		}

		void setNume(const char* nume)
		{
			if (this->nume != nullptr)
			{
				delete[] this->nume;
				this->nume = nullptr;
			}

			if (nume != nullptr)
			{
				unsigned dimensiune = strlen(nume) + 1;
				this->nume = new char[dimensiune];
				strcpy_s(this->nume, dimensiune, nume);
			}
		}

		float getComision() const
		{
			return this->comision;
		}

		void setComision(float comision)
		{
			if (comision >= 0)
			{
				this->comision = comision;
			}
		}

		~Banca()
		{
			if (this->nume != nullptr)
			{
				delete[] this->nume;
				this->nume = nullptr;
			}
		}

		friend ostream& operator<<(ostream& ostream, const Banca& banca)
		{
			ostream << "\tNumele bancii este: ";
			if (banca.nume != nullptr)
			{
				ostream << banca.nume;
			}
			else
			{
				ostream << "necunoscut";
			}
			ostream << endl;

			ostream << "\tComisionul perceput de banca este: " << banca.comision << endl;

			return ostream;
		}
	};
private:
	const unsigned id;
	TipMoneda tipMoneda;
	unsigned valabilitateZile;

	Banca banca;

	double* istoricValori;
	unsigned numarInregistrari;

	static unsigned numarCursuriValutare;

protected:
	double valoareRON;

public:
	CursValutar(TipMoneda tipMoneda = TipMoneda::EURO, double valoareRON = 0, float comisionBanca = 0.0f,
		unsigned valabilitateZile = 0, const char* numeBanca = nullptr) : id(numarCursuriValutare), banca(numeBanca, comisionBanca)
	{
		this->tipMoneda = tipMoneda;
		this->valoareRON = valoareRON;
		this->valabilitateZile = valabilitateZile;

		this->istoricValori = nullptr;
		this->numarInregistrari = 0;

		CursValutar::numarCursuriValutare++;
	}

	CursValutar(const CursValutar& altCursValutar) : id(numarCursuriValutare), banca(altCursValutar.banca)
	{
		this->tipMoneda = altCursValutar.tipMoneda;
		this->valoareRON = altCursValutar.valoareRON;
		this->valabilitateZile = altCursValutar.valabilitateZile;

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
		this->valabilitateZile = altCursValutar.valabilitateZile;

		this->banca = altCursValutar.banca;

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

	CursValutar& operator-=(const CursValutar& cursValutar)
	{
		this->valoareRON -= cursValutar.valoareRON;
		return *this;
	}

	CursValutar& operator-=(double valoareRON)
	{
		this->valoareRON -= valoareRON;
		return *this;
	}

	bool operator<(const CursValutar& cursValutar) const
	{
		return this->valoareRON < cursValutar.valoareRON;
	}

	CursValutar& operator++()
	{
		this->valoareRON += 0.01;
		return *this;
	}

	CursValutar operator++(int)
	{
		CursValutar copie = *this;
		this->valoareRON += 0.01;
		return copie;
	}

	double& operator[](unsigned index) const
	{
		if (this->istoricValori != nullptr && index < this->numarInregistrari)
		{
			return this->istoricValori[index];
		}
	}

	explicit operator double() const
	{
		return this->valoareRON;
	}

	double operator()(double sumaRON)
	{
		return this->convertesteInValuta(sumaRON);
	}

	void operator()(double valoareRON, float comision)
	{
		if (valoareRON > 0 && comision >= 0)
		{
			this->valoareRON = valoareRON;
			this->banca.setComision(comision);
		}
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
		if (this->istoricValori != nullptr)
		{
			delete[] this->istoricValori;
			this->istoricValori = nullptr;
		}
	}

	double convertesteInValuta(double sumaRON);

	friend ostream& operator<<(ostream& ostream, const CursValutar& cursValutar);
	friend istream& operator>>(istream& istream, CursValutar& cursValutar);

	friend CursValutar operator+(const CursValutar& cursValutar1, const CursValutar& cursValutar2);
	friend CursValutar operator+(const CursValutar& cursValutar, double valoareRON);
	friend CursValutar operator+(double valoareRON, const CursValutar& cursValutar);

	friend void comparaComisioane(const CursValutar& cursValutar1, const CursValutar& cursValutar2);
};
unsigned CursValutar::numarCursuriValutare = 0;

double CursValutar::convertesteInValuta(double sumaRON)
{
	if (sumaRON <= 0 || this->valoareRON <= 0)
	{
		return 0.0;
	}

	double comision = sumaRON * this->banca.getComision();
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
	ostream << "\tValabilitatea in zile este: " << cursValutar.valabilitateZile << endl;

	ostream << cursValutar.banca;

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

	cout << "Introduceti valabilitatea in zile: ";
	istream >> cursValutar.valabilitateZile;

	cout << "Introduceti comisionul perceput de banca: ";
	float comision = 0.0f;
	istream >> comision;
	cursValutar.banca.setComision(comision);

	cin.ignore();

	char buffer[DIMENSIUNE_BUFFER];
	cout << "Introduceti numele bancii: ";
	istream.getline(buffer, DIMENSIUNE_BUFFER);

	if (buffer[0] != '\0')
	{
		cursValutar.banca.setNume(buffer);
	}

	return istream;
}

CursValutar operator+(const CursValutar& cursValutar1, const CursValutar& cursValutar2)
{
	CursValutar rezultat = cursValutar1; 

	rezultat.valoareRON = cursValutar1.valoareRON + cursValutar2.valoareRON;

	return rezultat;
}

CursValutar operator+(const CursValutar& cursValutar, double valoareRON)
{
	CursValutar rezultat = cursValutar;

	rezultat.valoareRON += valoareRON;

	return rezultat;
}

CursValutar operator+(double valoareRON, const CursValutar& cursValutar)
{
	return cursValutar + valoareRON;
}

void comparaComisioane(const CursValutar& cursValutar1, const CursValutar& cursValutar2)
{
	if (cursValutar1.banca.getComision() > cursValutar2.banca.getComision())
	{
		cout << "Banca " << cursValutar1.banca.getNume() <<
			" are comisioane mai mari ca banca " << cursValutar2.banca.getNume() << endl;
	}
	else if (cursValutar1.banca.getComision() < cursValutar2.banca.getComision())
	{
		cout << "Banca " << cursValutar1.banca.getNume() <<
			" are comisioane mai mici ca banca " << cursValutar2.banca.getNume() << endl;
	}
	else
	{
		cout << "Ambele banci au aceleasi comisioane" << endl;
	}
}

inline double calculeazaMedieValori(double valoare1, double valoare2)
{
	return (valoare1 + valoare2) / 2.0;
}

class CursValutarRomanesc : public CursValutar
{
private:
	double valoareRONPreferentiala;

public:
	CursValutarRomanesc(double valoareRONPreferentiala = 0, TipMoneda tipMoneda = TipMoneda::EURO, double valoareRON = 0,
		float comisionBanca = 0.0f, unsigned valabilitateZile = 0, const char* numeBanca = nullptr)
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

	CursValutar euroLeiModificat = euroLei + dolarLei;
	euroLeiModificat = 1.0 + euroLeiModificat;
	euroLeiModificat = euroLeiModificat + 0.5;
	cout << euroLeiModificat;

	euroLeiModificat -= dolarLei;
	euroLeiModificat -= 1.5;
	cout << euroLeiModificat;

	cout << endl << "Cursul modificat este mai ";
	euroLei < euroLeiModificat ? cout << "mare" : cout << "mic";
	cout << endl;

	cout << ++euroLeiModificat;

	CursValutar euroLeiModificatVechi = euroLeiModificat++;
	cout << euroLeiModificat;
	cout << euroLeiModificatVechi;

	cout << "\nPrima valoare istorica (index 0): " << euroLei[0] << endl;

	euroLei[0] = 5.291;
	cout << "\nNoua valoare istorica la index 0: " << euroLei[0] << endl;

	double sumaCalculata = (double)euroLei + 10.0;
	cout << "\nSuma calculata prin cast explicit: " << sumaCalculata << endl;

	cout << "\nValoarea in valuta pentru 1000 RON (folosind operator()): " << euroLei(1000.0) << endl;

	euroLei(6.29, 0.35f);
	cout << euroLei;

	double media = calculeazaMedieValori(euroLei.getValoareRON(), dolarLei.getValoareRON());
	cout << "\nMedia valorilor: " << media << endl;

	CursValutarRomanesc euroLeiPreferential(5.20);
	cout << euroLeiPreferential;
	euroLeiPreferential.afisareCursValutarRomanesc();

	CursValutarRomanesc dolarLeiPreferential(4.60, TipMoneda::DOLAR, 4.70, 0.05f, 5, "Banca Romaneasca 1");
	cout << dolarLeiPreferential;
	dolarLeiPreferential.afisareCursValutarRomanesc();

	return 0;
}
