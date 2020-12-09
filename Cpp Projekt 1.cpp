#include <iostream>
#include "RandomNameGenerator.hpp"
#include <variant>
#include <vector>

using namespace std;

double wynInz = 4000, wynMkr = 3000, wynMag = 2000, wynRob = 1500;
double cInz = 3, cMkr = 1, cMag = 3, cRob = 4;

struct Pracownik
{
protected:
	string imie;
	double wynagrodzenie;
	double wydajnosc;
};

struct inz : public Pracownik
{
	inz() {
		imie = get_random_name();
		wynagrodzenie = wynInz;
		wydajnosc = cInz;
		wydzial = "Najlepszy na swiecie MEiL";
	}
	inz(string wyd) : wydzial{ wyd } {
		imie = get_random_name();
		wynagrodzenie = wynInz;
		wydajnosc = cInz;
	}
	void print()
	{
		cout << "Zawod: Inzynier \t Imie: " << imie << "\t Wydzial: " << wydzial << "\t Wynagrodzenie: " << wynagrodzenie << "\t Wydajnosc: " << wydajnosc << endl;
	}
private:
	string wydzial;
};

struct mag : public Pracownik
{
	mag() {
		imie = get_random_name();
		wynagrodzenie = wynMag;
		wydajnosc = cMag;
		widlak = false;
	}
	mag(bool wid) : widlak{ wid } {
		imie = get_random_name();
		wynagrodzenie = wynMag;
		wydajnosc = cMag;
	}
	void print()
	{
		cout << "Zawod: Magazynier \t Imie: " << imie << "\t Jazda wozkiem? " << widlak << "\t Wynagrodzenie: " << wynagrodzenie << "\t Wydajnosc: " << wydajnosc << endl;
	}
private:
	bool widlak;
};

struct mkr : public Pracownik
{
	mkr() {
		imie = get_random_name();
		wynagrodzenie = wynMkr;
		wydajnosc = cMkr;
		follow = 30;
	}
	mkr(int fol) : follow{ fol } {
		imie = get_random_name();
		wynagrodzenie = wynMkr;
		wydajnosc = cMkr;
	}
	void print()
	{
		cout << "Zawod: Marketer \t Imie: " << imie << "\t Followersi " << follow << "\t Wynagrodzenie: " << wynagrodzenie << "\t Wydajnosc: " << wydajnosc << endl;
	}
private:
	int follow;
};

struct rob : public Pracownik
{
	rob() {
		imie = get_random_name();
		wynagrodzenie = wynRob;
		wydajnosc = cRob;
		but = 43;
	}
	rob(float b) : but{ b } {
		imie = get_random_name();
		wynagrodzenie = wynRob;
		wydajnosc = cRob;
	}
	void print()
	{
		cout << "Zawod: Robotnik \t Imie: " << imie << "\t Numer buta: " << but << "\t Wynagrodzenie: " << wynagrodzenie << "\t Wydajnosc: " << wydajnosc << endl;
	}
private:
	float but;
};

int main()
{
	string komenda = "nic";
	cout << "Witaj w enterpr Co." << endl;
	cout << "Aktualny stan firmy) " << endl;
	cout << "Mozesz wykonac jedna z ponizszych akcji)" << endl;
	cout << "\t - lp - wylistuj pracownikow \n \t - zinz - zatrudnij inzyniera \n";
	cout << "\t - zmag - zatrudnij magazyniera \n \t - zmkr - zatrudnij marketera \n";
	cout << "\t - zrob - zatrudnij robotnika \n \t - wkr - wez kredyt \n \t - kt - koniec tury, zacznij nowy miesiac \n";
	cin >> komenda;
	while (1)
	{
		if (komenda == "lp")
		{
			cout << "Wybrales wylistowanie pracownikow" << endl;
			break;
		}
		else if (komenda == "zinz")
		{
			cout << "Wybrales zatrudnienie inzyniera" << endl;
			break;
		}
		else if (komenda == "zmag")
		{
			cout << "Wybrales zatrudnienie magazyniera" << endl;
			break;
		}
		else if (komenda == "zmkr")
		{
			cout << "Wybrales zatrudnienie marketera" << endl;
			break;
		}
		else if (komenda == "zrob")
		{
			cout << "Wybrales zatrudnienie robotnika" << endl;
			break;
		}
		else if (komenda == "wkr")
		{
			cout << "Wybrales wziecie kredytu" << endl;
			break;
		}
		else if (komenda == "kt")
		{
			cout << "Wybrales koniec tury" << endl;
			break;
		}
		else
		{
			cout << "Nie wybrales nic, powtorz wybor" << endl;
			cin >> komenda;
		}
	}
	return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
