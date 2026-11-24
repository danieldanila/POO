#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>

class ContBancar
{
private:
	double sold;
	char* titular;
	const int id;

	static int numarConturiBancare;

protected:
	static void valideazaText(const char* text, const char* numeCamp)
	{
		if (text == nullptr || text[0] == '\0')
		{
			throw std::invalid_argument(std::string(numeCamp) + " nu poate fi gol.");
		}
	}

	static char* copiazaText(const char* text, const char* numeCamp)
	{
		ContBancar::valideazaText(text, numeCamp);

		char* copieText = new char[std::strlen(text) + 1];
		strcpy_s(copieText, std::strlen(text) + 1, text);
		return copieText;
	}

	static double valideazaValoareNenegativa(double valoare, const char* numeCamp)
	{
		if (!std::isfinite(valoare) || valoare < 0)
		{
			throw std::invalid_argument(std::string(numeCamp) + " nu poate fi nefinit sau negativ.");
		}

		return valoare;
	}

public:
	ContBancar() : sold(valideazaValoareNenegativa(0.0, "Sold")), titular(copiazaText("Necunoscut", "Titular")), id(++numarConturiBancare) {}

	ContBancar(const char* titular, double sold) : sold(valideazaValoareNenegativa(sold, "Sold")), titular(copiazaText(titular, "Titular")), id(++numarConturiBancare) {}

	ContBancar(const ContBancar& altul) : sold(valideazaValoareNenegativa(altul.sold, "Sold")), titular(copiazaText(altul.titular, "Titular")), id(++numarConturiBancare) {}

	ContBancar& operator=(const ContBancar& altul)
	{
		if (this != &altul)
		{
			double soldNou = ContBancar::valideazaValoareNenegativa(altul.sold, "Sold");

			char* titularNou = ContBancar::copiazaText(altul.titular, "Titular");
			delete[] this->titular;
			this->titular = titularNou;

			this->sold = soldNou;
		}

		return *this;
	}

	~ContBancar()
	{
		delete[] this->titular;
	}

	double getSold() const
	{
		return this->sold;
	}

	static int getNumarConturiBancare()
	{
		return ContBancar::numarConturiBancare;
	}

	void adaugaLaSold(double suma)
	{
		ContBancar::valideazaValoareNenegativa(suma, "SumaSold");

		const double soldNou = this->sold + suma;
		ContBancar::valideazaValoareNenegativa(soldNou, "SoldNou");

		this->sold = soldNou;
	}

	friend std::ostream& operator<<(std::ostream& out, const ContBancar& contBancar)
	{
		out << "ID: " << contBancar.id
			<< ", titular: " << contBancar.titular
			<< ", sold: " << contBancar.sold;

		return out;
	}

	friend std::istream& operator>>(std::istream& in, ContBancar& contBancar)
	{
		std::string titularNou;
		std::cout << "Titular: ";
		if (!std::getline(in >> std::ws, titularNou))
		{
			return in;
		}

		double soldNou;
		std::cout << "Sold: ";
		if (!(in >> soldNou))
		{
			return in;
		}

		try
		{
			ContBancar::valideazaValoareNenegativa(soldNou, "Sold");
			char* copieTitular = ContBancar::copiazaText(titularNou.c_str(), "Titular");

			delete[] contBancar.titular;
			contBancar.titular = copieTitular;

			contBancar.sold = soldNou;
		}
		catch (const std::invalid_argument&)
		{
			in.setstate(std::ios::failbit);
			throw;
		}

		return in;
	}
};

int ContBancar::numarConturiBancare = 0;

class ContEconomii : public ContBancar
{
private:
	char* tipDobanda;

public:
	ContEconomii() : ContBancar(), tipDobanda(copiazaText("Standard", "TipDobanda")) {}

	ContEconomii(const char* titular, double sold, const char* tipDobanda) : ContBancar(titular, sold), tipDobanda(copiazaText(tipDobanda, "TipDobanda")) {}

	ContEconomii(const ContEconomii& altul) : ContBancar(altul), tipDobanda(copiazaText(altul.tipDobanda, "TipDobanda")) {}

	ContEconomii& operator=(const ContEconomii& altul)
	{
		if (this != &altul)
		{
			char* tipNou = ContBancar::copiazaText(altul.tipDobanda, "TipDobanda");

			try
			{
				ContBancar::operator=(altul);
			}
			catch (...)
			{
				delete[] tipNou;
				throw;
			}

			delete[] this->tipDobanda;
			this->tipDobanda = tipNou;
		}

		return *this;
	}

	~ContEconomii()
	{
		delete[] this->tipDobanda;
	}

	void aplicaDobanda(double procent)
	{
		ContBancar::valideazaValoareNenegativa(procent, "ProcentDobanda");

		const double dobanda = this->getSold() * procent / 100.0;
		ContBancar::valideazaValoareNenegativa(dobanda, "DobandaCalculata");

		this->adaugaLaSold(dobanda);
	}

	friend std::ostream& operator<<(std::ostream& out, const ContEconomii& contEconomii)
	{
		out << static_cast<const ContBancar&>(contEconomii);
		out << ", tip dobanda: " << contEconomii.tipDobanda;

		return out;
	}

	friend std::istream& operator>>(std::istream& in, ContEconomii& contEconomii)
	{
		in >> static_cast<ContBancar&>(contEconomii);
		if (!in)
		{
			return in;
		}

		std::string tipDobandaNou;
		std::cout << "Tip dobanda: ";
		if (!std::getline(in >> std::ws, tipDobandaNou))
		{
			return in;
		}

		try
		{
			char* copieTipDobanda = ContBancar::copiazaText(tipDobandaNou.c_str(), "TipDobanda");

			delete[] contEconomii.tipDobanda;
			contEconomii.tipDobanda = copieTipDobanda;
		}
		catch (const std::invalid_argument&)
		{
			in.setstate(std::ios::failbit);
			throw;
		}

		return in;
	}
};

int main()
{
	try
	{
		ContEconomii contImplicit;
		std::cout << "\nConstructor fara parametrii: " << contImplicit;

		ContEconomii contEconomiiA("Compania A", 1000.5, "Variabila");
		std::cout << "\nConstructor cu parametrii: " << contEconomiiA;

		ContEconomii copieCont(contEconomiiA);
		std::cout << "\nConstructor de copiere: " << copieCont;

		ContEconomii contEconomiiB("Compania B", 2500.0, "Standard");
		std::cout << "\nInainte de operator=: " << contEconomiiB;

		contEconomiiB = contEconomiiA;
		std::cout << "\nDupa operator=: " << contEconomiiB;

		contEconomiiA.adaugaLaSold(900.5);
		std::cout << "\nDupa adaugare sold: " << contEconomiiA;

		contEconomiiA.aplicaDobanda(4.5);
		std::cout << "\nDupa aplicare dobanda: " << contEconomiiA;

		ContEconomii contEconomiiC;
		std::cout << "\n\nIntroduceti date pentru contEconomiiC:\n";
		std::cin >> contEconomiiC;

		if (!std::cin)
		{
			throw std::runtime_error("Date invalide la citirea contEconomiiC.");
		}

		std::cout << "\nDupa citire: " << contEconomiiC;

		std::cout << "\nNumarul de ID-uri atribute: " << ContBancar::getNumarConturiBancare();
	}
	catch (const std::exception& e)
	{
		std::cerr << "\nEroare: " << e.what() << "\nProgramul se opreste.\n";
		return 1;
	}

	const int numarCompanii = 2;
	const int conturiPerCompanie = 2;

	ContEconomii** matrice = nullptr;

	try
	{
		matrice = new ContEconomii * [numarCompanii] {};

		for (int i = 0; i < numarCompanii; i++)
		{
			matrice[i] = new ContEconomii[conturiPerCompanie];
		}

		std::cout << "\n\nMatrice:";
		for (int i = 0; i < numarCompanii; i++)
		{
			for (int j = 0; j < conturiPerCompanie; j++)
			{
				std::cout << "\nCompania " << i + 1 << ", contul " << j + 1 << ":\n";
				std::cin >> matrice[i][j];

				if (!std::cin)
				{
					throw std::runtime_error("Date invalide la citirea contului de economii.");
				}
			}
		}

		std::cout << "\nConturile din matrice:\n";
		for (int i = 0; i < numarCompanii; i++)
		{
			for (int j = 0; j < conturiPerCompanie; j++)
			{
				std::cout << "\n[" << i << "][" << j << "] " << matrice[i][j];
			}
		}

		std::cout << "\n\nContul de economii de pe prima linie si prima coloana din matrice: " << matrice[0][0];

		ContEconomii* p = &matrice[0][0];
		std::cout << "\nContul de economii de pe prima linie si prima coloana din matrice, accesat prin pointer: " << *p;

		p->aplicaDobanda(5.0);
		std::cout << "\nDupa aplicare dobanda, accesat prin pointer: " << *p;
		std::cout << "\nDupa aplicare dobanda: " << matrice[0][0];
	}
	catch (const std::exception& e)
	{
		std::cerr << "\nEroare: " << e.what() << "\nProgramul se opreste.\n";

		if (matrice != nullptr)
		{
			for (int i = 0; i < numarCompanii; i++)
			{
				delete[] matrice[i];
			}
		}

		delete[] matrice;

		return 1;
	}

	for (int i = 0; i < numarCompanii; i++)
	{
		delete[] matrice[i];
	}
	delete[] matrice;

	return 0;
}