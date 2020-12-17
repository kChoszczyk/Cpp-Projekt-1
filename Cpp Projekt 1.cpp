#include <iostream>
#include "RandomNameGenerator.hpp"
#include <variant>
#include <cmath>
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 12;


struct k_Pracownik
{
protected:
	string imie;
};

struct inz : public k_Pracownik
{
	inz() {
		imie = get_random_name();
		wydzial = "MEiL";
	}
	inz(string wyd) : wydzial{ wyd } {
		imie = get_random_name();
	}
	void print()
	{
		cout << "Zawod: Inzynier \t Imie: " << imie << "\t Wydzial: \t" << wydzial << endl;
	}
private:
	string wydzial;
};

struct mag : public k_Pracownik
{
	mag() {
		imie = get_random_name();
		widlak = false;
	}
	mag(bool wid) : widlak{ wid } {
		imie = get_random_name();
	}
	void print()
	{
		cout << "Zawod: Magazynier \t Imie: " << imie << "\t Jazda wozkiem?\t";
		if (widlak)
			cout << "Tak" << endl;
		else
			cout << "Nie" << endl;
	}
private:
	bool widlak;
};

struct mkr : public k_Pracownik
{
	mkr() {
		imie = get_random_name();
		follow = 30;
	}
	mkr(int fol) : follow{ fol } {
		imie = get_random_name();
	}
	
	void print()
	{
		cout << "Zawod: Marketer \t Imie: " << imie << "\t Followersi \t" << follow << endl;
	}
private:
	int follow;
};

struct rob : public k_Pracownik
{
	rob() {
		imie = get_random_name();
		but = 43;
	}
	rob(float b) : but{ b } {
		imie = get_random_name();
	}
	void print()
	{
		cout << "Zawod: Robotnik \t Imie: " << imie << "\t Numer buta: \t" << but << endl;
	}
private:
	float but;
};

struct kredyt
{
	kredyt() : maks_rat{ 36 }, dlug{ 0 }, pozostale_raty{ 0 }, rata{ 0 } {}

	kredyt(double dl, int rat, int mx) : maks_rat{ mx }
	{
		if (rat <= maks_rat)
			pozostale_raty = rat;
		else
		{
			cout << "Przekroczyles limit rat, przypisano maksymalna liczbe rat, czyli: " << maks_rat << endl;
			pozostale_raty = maks_rat;
		}
		dlug = dl * pow(odsetki, pozostale_raty);
		rata = dlug / pozostale_raty;
		cout << "Calkowita kwota twojego kredytu wyniosla: " << dlug << endl;
		cout << "Wysokosc raty wynosi: " << rata << endl;
	}

	kredyt operator=(kredyt k)
	{
		return k;
	}

	double splac_rate()
	{
		dlug = dlug - rata;
		return rata;
	}
	double get_dlug()
	{
		return dlug;
	}
	double get_rata()
	{
		return rata;
	}

	
private:
	double dlug;
	int pozostale_raty;
	double rata;
	const int maks_rat;
	const double odsetki = 1.005;
};

struct PrinterPracownikow
{
	template <typename T>
	void operator() (T& prac)
	{
		prac.print();
	}
};

struct Firma
{
	using pracownik_typ = variant <inz, mag, mkr, rob>;
	
	Firma(int mx) : maks_rat{ mx }
	{
		Pracownicy = make_unique<pracownik_typ[]>(max_prac);
		Kredyty = make_unique<kredyt[]>(max_kred);
		n_pracownikow = 4;
		n_kredytow = 0;
		n_inz = 1; n_mag = 1; n_mkr = 1; n_rob = 1;
		Pracownicy[0] = inz{};
		Pracownicy[1] = mag{};
		Pracownicy[2] = mkr{};
		Pracownicy[3] = rob{};
		for (int i = 0; i < N; i++)
			historia_przychodow[i] = 0;
		stan_konta = start_kasa;
		stan_mag = 0;
		zadluzenie = 0;
	}

	void drukuj_pracownikow()
	{
		cout << "Masz " << n_pracownikow << " pracownikow " << endl;
		cout << "Sa to:" << endl; cout << n_inz << "\tInzynierow zarabiajacych po\t" << wynInz << endl;
		cout << n_mkr << "\tMarketerow zarabiajacych po\t" << wynMkr << endl;
		cout << n_mag << "\tMagazynierow zarabiajacych po\t" << wynMag << endl;
		cout << n_rob << "\tRobotnikow zarabiajacych  po\t" << wynRob << endl;
		cout << "Suma ich zarobkow wynosi " << get_wynagrodzenia() << endl;
		cout << "Oto twoi pracownicy " << endl;
		for (int i = 0; i < n_pracownikow; i++)
			visit(PrinterPracownikow(),Pracownicy[i]);
	}
	void wez_kredyt(double kwota, int liczba_rat)
	{
		if (n_kredytow < max_kred)
		{
			Kredyty[n_kredytow] = kredyt{ kwota,liczba_rat,maks_rat };
			if (zadluzenie + Kredyty[n_kredytow].get_dlug() < M * wartosc_firmy())
			{
				zadluzenie += Kredyty[n_kredytow].get_dlug();
				n_kredytow++;
			}
			else
			{
				cout << "Splac stare dlugi, zanim wezmiesz nowe lub zwieksz wartosc spolki, przekroczyles kwote zadluzenia" << endl;
			}
		}
		else
		{
			cout << "Masz za duzo roznych kredytow" << endl;
		}
	}
	void zatrudnij(const pracownik_typ prac)
	{
		switch (prac.index())
		{
		case 0:
			n_inz++;
			break;
		case 1:
			n_mag++;
			break;
		case 2:
			n_mkr++;
			break;
		case 3:
			n_rob++;
			break;
		}
		Pracownicy[n_pracownikow] = prac;
		n_pracownikow++;
	}
	double get_zadluzenie() { return zadluzenie; }
	void get_kredyty()
	{
		cout << "Masz " << n_kredytow << " kredytow" << endl;
		cout << "Twoje zadluzenie wynosi " << zadluzenie << endl;
		cout << "Oznacza to, ze mozesz wziac jeszcze " << max_kred - n_kredytow << " kredytow na laczna sume zadluzenia " << M * wartosc_firmy() << endl;
		double suma_rat=0;
		for (int i = 0; i < n_kredytow; i++)
		{
			suma_rat += Kredyty[i].get_rata();
		}
		cout << "Twoje raty w tym miesiacu wyniosa " << suma_rat << endl;
	}
	void zaplac_wynagrodzenie()
	{
		double wyplaty = get_wynagrodzenia();
		stan_konta -= wyplaty;
	}
	double get_wynagrodzenia()
	{
		return wynInz * n_inz + wynMag * n_mag + wynMkr * n_mkr + wynRob * n_rob;
	}
	void otrzymaj_przychod()
	{
		double przychod = oblicz_przychod();
		stan_konta += przychod;
		for (int i = N-1; i > 0; i--)
			historia_przychodow[i] = historia_przychodow[i-1];
		historia_przychodow[0] = przychod;
	}
	void zaplac_raty()
	{
		for (int i = 0; i < n_kredytow; i++)
		{
			double rata = Kredyty[i].splac_rate();
			stan_konta -= rata;
			zadluzenie -= rata;
			if (Kredyty[i].get_dlug() < 0.1)
			{
				for (int j = i; j < (N-1); j++)
					Kredyty[j] = Kredyty[j + 1];
				n_kredytow--;
				i--;
			}
		}
	}

	const double get_stan_mag(){ return stan_mag; }
	const double get_stan_konta() { return stan_konta; }
	double wartosc_firmy()
	{ 
		double suma = 0;
		for (int i = 0; i < N; i++)
			suma += historia_przychodow[i];
		return suma / N;
	}

private:
	const double oblicz_przychod()
	{
		srand(time(NULL));
		int poj_mag = n_mag * cMag;
		double cena = n_inz * cInz * ((rand() % 41) + 80) / 100;
		int popyt = n_mkr * cMkr;
		int prod_max = n_rob * cRob;
		int prod, sprzed;
		if (poj_mag < (prod_max + stan_mag))
			prod = poj_mag;
		else
			prod = prod_max + stan_mag;
		if (popyt < prod)
			sprzed = popyt;
		else
			sprzed = prod;
		stan_mag = prod - sprzed;
		return sprzed * cena;
	}

	double historia_przychodow[N];
	double stan_konta;
	int n_kredytow;
	unique_ptr<kredyt[]> Kredyty;
	int n_pracownikow;
	unique_ptr<pracownik_typ[]> Pracownicy;
	int n_inz, n_mag, n_mkr, n_rob;
	int stan_mag;
	public:
	double zadluzenie;

	const double wynInz = 4000, wynMkr = 3000, wynMag = 2000, wynRob = 1500;
	const double cInz = 144.99;
	const int cRob = 90, cMag = 70, cMkr = 61;
	const double M = 1.56;
	const double start_kasa = 30000;
	const int max_prac = 1000;
	const int max_kred = 12;
	const int maks_rat;
};

struct Gra
{
	using pracownik_typ = variant <inz, mag, mkr, rob>;
	Gra()
	{
		firma = make_unique<Firma>(maks_rat);
		cout << "Witaj w enterpr Co." << endl;
		wygrana = false;
		przegrana = false;
		miesiac = 0;
	}

	void akcja_gracza()
	{
		string komenda;
		string temp;
		int pom_int;
		float pom_float;
		double pom_double;

		cout << endl;
		cout << "Wcisnij Enter" << endl;
		
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(std::cin, temp);
		cout << "Miesiac " << miesiac << endl;
		cout << "Wartosc twojej spolki wynosi: " << firma->wartosc_firmy() << endl;
		cout << "Twoj stan konta wynosi: " << firma->get_stan_konta() << endl;
		cout << "Wynagrodzenia wynosza: " << firma->get_wynagrodzenia() << endl;
		cout << "Na magazynie znajduje sie " << firma->get_stan_mag() << " sztuk produktu." << endl;
		firma->get_kredyty();
		cout << "Mozesz wykonac jedna z ponizszych akcji: " << endl;
		cout << "\t - lp - wylistuj pracownikow \n \t - zinz - zatrudnij inzyniera \n";
		cout << "\t - zmag - zatrudnij magazyniera \n \t - zmkr - zatrudnij marketera \n";
		cout << "\t - zrob - zatrudnij robotnika \n \t - wkr - wez kredyt \n \t - kt - koniec tury, zacznij nowy miesiac \n";
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> komenda;
		cout << endl;
		while (1)
		{
			if (komenda == "lp")
			{
				cout << "Wybrales wylistowanie pracownikow." << endl;
				firma->drukuj_pracownikow();
				break;
			}
			else if (komenda == "zinz")
			{
				cout << "Wybrales zatrudnienie inzyniera." << endl;
				cout << "Wpisz nazwe wydzialu jaki ma ukonczyc (wpisanie 'dom' przypisuje wydzial domyslny)" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> temp;
				if (temp == "dom")
				{
					inz t{};
					firma->zatrudnij(t);
				}
				else
				{
					inz t{temp};
					firma->zatrudnij(t);
				}
				break;
			}
			else if (komenda == "zmag")
			{
				cout << "Wybrales zatrudnienie magazyniera." << endl;
				cout << "Czy powinien on prowadzic wozek widlowy? (Wpisz tak, jesli powinien lub cokolwiek innego jesli nie)" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> temp;
				if (temp == "tak")
				{
					mag t{ true };
					firma->zatrudnij(t);
				}
				else
				{
					mag t{};
					firma->zatrudnij(t);
				}
				break;
			}
			else if (komenda == "zmkr")
			{
				cout << "Wybrales zatrudnienie marketera." << endl;
				cout << "Ilu powinien miec followersow na IG? (Wpisanie liczby mniejszej lub rownej 10 przypisuje wartosc domyslna)" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> pom_int;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Nieprawidlowy numer, przypisano wartosc domyslna" << endl;
				}
				if (pom_int <= 10)
				{
					mkr t{};
					firma->zatrudnij(t);
				}
				else
				{
					mkr t{ pom_int };
					firma->zatrudnij(t);
				}
				break;
			}
			else if (komenda == "zrob")
			{
				cout << "Wybrales zatrudnienie robotnika" << endl;
				cout << "Jaki powinien miec rozmiar buta? (Wpisanie liczby spoza zakresu <36, 50> przypisuje wartosc domyslna)" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> pom_float;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Nieprawidlowy numer, przypisano wartosc domyslna" << endl;
				}
				if ((pom_float <= 50) && (pom_float >= 36))
				{
					rob t{pom_float};
					firma->zatrudnij(t);
				}
				else
				{
					rob t{};
					firma->zatrudnij(t);
				}
				break;
			}
			else if (komenda == "wkr")
			{
				cout << "Wybrales wziecie kredytu." << endl;
				cout << "Podaj kwote kredytu." << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> pom_double;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Nieprawidlowa wartosc, odrzucono wziecie kredytu" << endl;
					break;
				}
				cout << "Podaj liczbe rat, maksymalnie: " << maks_rat << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.clear();
				cin >> pom_int;
				firma->wez_kredyt(pom_double, pom_int);
				break;
			}
			else if (komenda == "kt")
			{
				cout << "Wybrales koniec tury" << endl;
				tick();
				break;
			}
			else
			{
				cout << "Nie wybrales nic, powtorz wybor" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> komenda;
			}
		}
	}
	bool get_wygr()
	{
		if ((firma->wartosc_firmy() - firma->get_zadluzenie()) > wart_docelowa)
			wygrana = false;
		else
			wygrana = true;
		return wygrana;
	}
	bool get_przegr()
	{
		if (firma->get_stan_konta() < 0)
			przegrana = false;
		else
			przegrana = true;
		return przegrana;
	}
private:
	void tick()
	{
		firma->otrzymaj_przychod();
		firma->zaplac_raty();
		firma->zaplac_wynagrodzenie();
		miesiac++;
	}
	const int maks_rat = 36;
	const double wart_docelowa = 200000;
	bool wygrana;
	bool przegrana;
	int miesiac;
	unique_ptr<Firma> firma;
};

int main()
{
	Gra game{};
	while(game.get_przegr() && game.get_wygr())
		game.akcja_gracza();
	if (game.get_przegr() == false)
	{
		cout << "Nie udalo ci sie, firma upadla, a ty straciles wszystko. \n Sprobuj ponownie." << endl;
	}
	else if (game.get_wygr() == false)
	{
		cout << "BRAWO! \n Twoja spolka osiagnela wartosc maksymalna, podbiles swiat, czyli wygrales" << endl;
	}
	else
		cout << "Nie wiemy co sie wydarzylo, ale wystapil blad" << endl;
	return 0;
}