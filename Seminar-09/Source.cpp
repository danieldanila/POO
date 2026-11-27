#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

class ContBancar
{
private:
	double sold;
	char* titular;
	const int id;

	static int numarConturiBancare;

	static const int LUNGIME_MAXIMA_TEXT = 10000;

protected:
	static void valideazaText(const char* text, const char* numeCamp)
	{
		if (text == nullptr || text[0] == '\0')
		{
			throw std::invalid_argument(std::string(numeCamp) + " nu poate fi gol.");
		}

		if (std::strlen(text) > ContBancar::LUNGIME_MAXIMA_TEXT)
		{
			throw std::invalid_argument(std::string(numeCamp) + " depaseste lungimea maxima.");
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

	static bool scrieTextBinar(std::ofstream& fout, const char* text)
	{
		try
		{
			ContBancar::valideazaText(text, "TextBinar");
		}
		catch (const std::invalid_argument&)
		{
			fout.setstate(std::ios::failbit);
			return false;
		}

		int lungime = static_cast<int>(std::strlen(text));

		fout.write(reinterpret_cast<const char*>(&lungime), sizeof(lungime));

		if (!fout)
		{
			return false;
		}

		fout.write(text, sizeof(text[0]) * lungime);

		return static_cast<bool>(fout);
	}

	static bool citesteTextBinar(std::ifstream& fin, std::string& text)
	{
		int lungime = 0;
		fin.read(reinterpret_cast<char*>(&lungime), sizeof(lungime));

		if (!fin)
		{
			return false;
		}

		if (lungime <= 0 || lungime > ContBancar::LUNGIME_MAXIMA_TEXT)
		{
			fin.setstate(std::ios::failbit);
			return false;
		}

		std::string textNou;
		textNou.resize(lungime);
		fin.read(&textNou[0], sizeof(textNou[0]) * lungime);

		if (!fin)
		{
			return false;
		}

		text = textNou;
		return true;
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

	friend std::ofstream& operator<<(std::ofstream& fout, const ContBancar& contBancar)
	{
		fout << contBancar.id << " " << std::quoted(contBancar.titular) << " " << contBancar.sold;

		return fout;
	}

	void serializareBinara(std::ofstream& fout) const
	{
		fout.write(reinterpret_cast<const char*>(&this->id), sizeof(this->id));

		if (!fout)
		{
			return;
		}

		if (!scrieTextBinar(fout, this->titular))
		{
			return;
		}

		fout.write(reinterpret_cast<const char*>(&this->sold), sizeof(this->sold));
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

	friend std::ifstream& operator>>(std::ifstream& fin, ContBancar& contBancar)
	{
		int id;
		std::string titularNou;
		double soldNou;

		if (!(fin >> id >> std::quoted(titularNou) >> soldNou))
		{
			return fin;
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
			fin.setstate(std::ios::failbit);
			throw;
		}

		return fin;
	}

	void deserializareBinara(std::ifstream& fin)
	{
		int idCitit;
		fin.read(reinterpret_cast<char*>(&idCitit), sizeof(idCitit));

		if (!fin)
		{
			return;
		}

		std::string titularNou;
		if (!citesteTextBinar(fin, titularNou))
		{
			return;
		}

		double soldNou;
		fin.read(reinterpret_cast<char*>(&soldNou), sizeof(soldNou));

		if (!fin)
		{
			return;
		}

		try
		{
			ContBancar::valideazaValoareNenegativa(soldNou, "Sold");
			char* copieTitular = ContBancar::copiazaText(titularNou.c_str(), "Titular");

			delete[] this->titular;
			this->titular = copieTitular;

			this->sold = soldNou;
		}
		catch (const std::invalid_argument&)
		{
			fin.setstate(std::ios::failbit);
			throw;
		}
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

	friend std::ofstream& operator<<(std::ofstream& fout, const ContEconomii& contEconomii)
	{
		fout << static_cast<const ContBancar&>(contEconomii) << " " << std::quoted(contEconomii.tipDobanda);

		return fout;
	}

	void serializareBinara(std::ofstream& fout) const
	{
		ContBancar::serializareBinara(fout);

		if (!fout)
		{
			return;
		}

		scrieTextBinar(fout, this->tipDobanda);
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

	friend std::ifstream& operator>>(std::ifstream& fin, ContEconomii& contEconomii)
	{
		fin >> static_cast<ContBancar&>(contEconomii);

		if (!fin)
		{
			return fin;
		}

		std::string tipDobandaNou;
		if (!(fin >> std::quoted(tipDobandaNou)))
		{
			return fin;
		}

		try
		{
			char* copieTipDobanda = ContBancar::copiazaText(tipDobandaNou.c_str(), "TipDobanda");

			delete[] contEconomii.tipDobanda;
			contEconomii.tipDobanda = copieTipDobanda;
		}
		catch (const std::invalid_argument&)
		{
			fin.setstate(std::ios::failbit);
			throw;
		}

		return fin;
	}

	void deserializareBinara(std::ifstream& fin)
	{
		ContBancar::deserializareBinara(fin);

		if (!fin)
		{
			return;
		}

		std::string tipDobandaNou;
		if (!citesteTextBinar(fin, tipDobandaNou))
		{
			return;
		}
			
		try
		{
			char* copieDobanda = ContBancar::copiazaText(tipDobandaNou.c_str(), "TipDobanda");

			delete[] this->tipDobanda;
			this->tipDobanda = copieDobanda;
		}
		catch (const std::invalid_argument&)
		{
			fin.setstate(std::ios::failbit);
			throw;
		}
	}
};

int main()
{
	try
	{
		ContEconomii contEconomiiA("Compania A", 1000.5, "Variabila");
		ContEconomii contEconomiiB("Compania B", 2500.0, "Standard");
		ContEconomii contEconomiiC("Compania C", 50.35, "Variabila");

		std::ofstream fisierScriereText;
		fisierScriereText.open("conturiEconomii.txt", std::ios::out | std::ios::trunc);

		if (!fisierScriereText)
		{
			throw std::runtime_error("Nu s-a putut deschide fișierul text pentru scriere.");
		}

		fisierScriereText << contEconomiiA << '\n';
		fisierScriereText << contEconomiiB << '\n';
		fisierScriereText << contEconomiiC << '\n';

		if (!fisierScriereText)
		{
			throw std::runtime_error("Eroare la scrierea fisierului text.");
		}
		
		fisierScriereText.close();

		if (!fisierScriereText)
		{
			throw std::runtime_error("Eroare la inchiderea fisierului text.");
		}

		std::ifstream fisierCitireText;
		fisierCitireText.open("conturiEconomii.txt", std::ios::in);

		if (!fisierCitireText)
		{
			throw std::runtime_error("Nu s-a putut deschide fișierul text pentru citire.");
		}

		ContEconomii c1, c2, c3;

		if (!(fisierCitireText >> c1 >> c2 >> c3))
		{
			throw std::runtime_error("Eroare la citirea fisierului text.");
		}
		
		fisierCitireText.close();

		if (!fisierCitireText)
		{
			throw std::runtime_error("Eroare la inchiderea fisierului text.");
		}

		std::cout << c1 << "\n" << c2 << "\n" << c3 << "\n";

		std::ofstream fisierScriereBinar;
		fisierScriereBinar.open("conturiEconomii.bin", std::ios::binary | std::ios::out | std::ios::trunc);

		if (!fisierScriereBinar)
		{
			throw std::runtime_error("Nu s-a putut deschide fișierul binar pentru scriere.");
		}
	
		contEconomiiA.serializareBinara(fisierScriereBinar);
		contEconomiiB.serializareBinara(fisierScriereBinar);
		contEconomiiC.serializareBinara(fisierScriereBinar);

		if (!fisierScriereBinar)
		{
			throw std::runtime_error("Eroare la scrierea fisierului binar.");
		}
		
		fisierScriereBinar.close();

		if (!fisierScriereBinar)
		{
			throw std::runtime_error("Eroare la inchiderea fisierului binar.");
		}

		std::ifstream fisierCitireBinar;
		fisierCitireBinar.open("conturiEconomii.bin", std::ios::binary | std::ios::in);
		
		if (!fisierCitireBinar)
		{
			throw std::runtime_error("Nu s-a putut deschide fișierul binar pentru citire.");
		}

		ContEconomii c4, c5, c6;

		c4.deserializareBinara(fisierCitireBinar);
		c5.deserializareBinara(fisierCitireBinar);
		c6.deserializareBinara(fisierCitireBinar);

		if (!fisierCitireBinar)
		{
			throw std::runtime_error("Eroare la citirea fisierului binar.");
		}
		
		fisierCitireBinar.close();

		if (!fisierCitireBinar)
		{
			throw std::runtime_error("Eroare la inchiderea fisierului binar.");
		}

		std::cout << c4 << "\n" << c5 << "\n" << c6 << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << "\nEroare: " << e.what() << "\nProgramul se opreste.\n";
		return 1;
	}

	return 0;
}