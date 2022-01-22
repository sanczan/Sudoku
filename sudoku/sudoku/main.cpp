#include<iostream>
#include <stdlib.h>

using namespace std;

bool czy_ta_sama(int tab[9]) { // pomocna pêtla sprawdzaj¹ca czy w kwadracie 3x3 cyfra siê powtarza
	for (int i = 0; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (tab[i] != 0 && i != j) {
				if (tab[i] == tab[j]) {
					return true;
				}
			}
		}
	}
	return false;
}


bool czy_ta_sama_2(int tab[9], int pozycja) { // bardziej 'wyspecjalizowana' wersja poprzedniej funkcji
	for (int i = 0; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (tab[i] != 0 && i != j) {
				if (tab[i] == tab[j] && tab[i] == pozycja) {
					return true;
				}
			}
		}
	}
	return false;
}


//funkcje 'pion', 'poziom' oraz 'kwadrat' opieraj¹ siê na niemal¿e tej samej zasadzie co funkcja 'czyPoprawnie'
//jednak musia³em je rozdzieliæ aby mo¿liwe by³o sprawdzenie warunku zakoñczenia programu (poprawnoœc uzupe³nionej tablicy)

//w domysle czy sie powtarza (komentarz dla mnie)
bool poziom(int plansza[9][9], int q, int r, int pozycja) {
	for (int i = 0; i < 9; i++) {
		if (pozycja == plansza[q][i]  && i != r) {
			return true;
		}
	}
	return false;
}

bool pion(int plansza[9][9], int q, int r, int pozycja) {
	for (int i = 0; i < 9; i++) {
		if (pozycja == plansza[i][r] && i != q) {
			return true;
		}
	}
	return false;
}

bool kwadrat(int plansza[9][9], int q, int r, int pozycja) {
	int pomoc[9]{};
	int licznik{}, kwadrat_poziom{}, kwadrat_pion{};
	kwadrat_poziom = r / 3;
	kwadrat_pion = q / 3;
	for (int i = 3*kwadrat_pion; i < (3 * kwadrat_pion) + 3; i += 3) {
		for (int j = 3*kwadrat_poziom; j < (3 * kwadrat_poziom) + 3; j += 3) {
			for (int k = i; k < (3 * kwadrat_pion) + 3; k++) {
				for (int l = j; l < (3 * kwadrat_poziom) + 3; l++) {
					pomoc[licznik] = plansza[k][l];
					licznik++;
				}
			}
			if (czy_ta_sama_2(pomoc, pozycja) == true && pozycja == plansza[q][r]) {
				return true;
			}
			licznik = 0;
		}
	}
	return false;
}


bool czyPoprawnie(int plansza[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (plansza[i][j] == 0) {
				continue;
			}
			else {
				for (int k = 0; k < 9; k++) {
					if (j != k && plansza[i][k] != 0) {
						if ((plansza[i][j] == plansza[i][k]) && plansza[i][j] != 0) {
							return false;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (plansza[j][i] == 0) {
				continue;
			}
			else {
				for (int k = 0; k < 9; k++) {
					if (j != k && plansza[k][i] != 0) {
						if ((plansza[j][i] == plansza[k][i]) && plansza[j][i] != 0) {
							return false;
						}
					}
				}
			}
		}
	}

	int pomoc[9]{};
	int licznik{};
	for (int i = 0; i < 9; i += 3) {
		for (int j = 0; j < 9; j += 3) {
			for (int k = i; k < 3; k++) {
				for (int l = j; l < 3; l++) {
					pomoc[licznik] = plansza[k][l];
					licznik++;
				}
			}
			if (czy_ta_sama(pomoc) == true) {
				return false;
			}
			licznik = 0;
		}
	}
	return true;
}

//sprawdzamy czy na planszy s¹ jakieœ zera i czy jest ona poprawnie uzupe³niona,
//je¿eli tak to zwracamy wartoœæ true
bool czy_wygrana(int tab[9][9]) { 
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (tab[i][j] == 0) {
				return false;
			}
		}
	}
	if (czyPoprawnie(tab) == true) {
		return true;
	}
	else {
		return false;
	}
}


//sprawdzenie czy wprowadzona cyfra jest w zakresie <0,9>
bool poprawnosc(int x) {
	if (x >= 0 && x <= 9) {
		return true;
	}
	else {
		return false;
	}
}


int main() {
	srand(time(NULL));

	int poziom_trudnosci{}, pola_do_podmiany{};
	string podpowiedz{};
	
	//poziom trudnosci
	do {
		cout << "Wybierz poziom trudnosci:" << endl;
		cout << "1. Latwy" << endl;
		cout << "2. Sredni" << endl;
		cout << "3. Trudny" << endl;
		cin >> poziom_trudnosci;
		if (!cin) {//ignoruje bledne znaki
			cin.clear();
			cin.ignore(40, '\n');
		}
		system("CLS");//czysci konsole po wprowadzeniu blednych znakow
	} while (poziom_trudnosci < 1 || poziom_trudnosci > 3);

	//wybor opcji pomocy
	do {
		cout << "Czy chcesz skorzystac z podpowiedzi? (tak/nie)" << endl;
		cin >> podpowiedz;
	} while (podpowiedz != "tak" && podpowiedz != "nie" && podpowiedz != "TAK");

	//ilosc pol do podmiany na danej tablicy w zale¿noœci od poziomu trudnoœci
	switch (poziom_trudnosci){
		case 1:
			pola_do_podmiany = 40;
			break;
		case 2:
			pola_do_podmiany = 50;
			break;
		case 3:
			pola_do_podmiany = 60;
			break;
		default:
			break;
	}

	int tab[9][9]{};

	//tablice 'losowe'
	int tab_1[9][9] = { 
		{5, 3, 4, 6, 7, 8, 9, 1, 2}, 
		{6, 7, 2, 1, 9, 5, 3, 4, 8}, 
		{1, 9, 8, 3, 4, 2, 5, 6, 7},
		{8, 5, 9, 7, 6, 1, 4, 2, 3}, 
		{4, 2, 6, 8, 5, 3, 7, 9, 1}, 
		{7, 1, 3, 9, 2, 4, 8, 5, 6},
		{9, 6, 1, 5, 3, 7, 2, 8, 4}, 
		{2, 8, 7, 4, 1, 9, 6, 3, 5}, 
		{3, 4, 5, 2, 8, 6, 1, 7, 9} 
	};

	int tab_2[9][9] = {
		{2, 4, 7, 9, 1, 3, 8, 6, 5},
		{1, 9, 5, 6, 8, 7, 2, 4, 3},
		{8, 6, 3, 2, 5, 4, 7, 9, 1},
		{3, 1, 2, 4, 7, 9, 5, 8, 6},
		{9, 5, 8, 1, 6, 2, 4, 3, 7},
		{6, 7, 4, 5, 3, 8, 9, 1, 2},
		{7, 8, 1, 3, 4, 5, 6, 2, 9},
		{4, 3, 9, 7, 2, 6, 1, 5, 8},
		{5, 2, 6, 8, 9, 1, 3, 7, 4}
	};

	int tab_3[9][9] = {
		{1, 6, 8, 2, 5, 4, 7, 9, 3},
		{3, 7, 5, 9, 8, 6, 1, 2, 4},
		{9, 4, 2, 3, 7, 1, 8, 6, 5},
		{6, 2, 1, 5, 3, 8, 9, 4, 7},
		{4, 5, 9, 7, 1, 2, 3, 8, 6},
		{8, 3, 7, 4, 6, 9, 5, 1, 2},
		{5, 9, 4, 8, 2, 3, 6, 7, 1},
		{2, 1, 3, 6, 9, 7, 4, 5, 8},
		{7, 8, 6, 1, 4, 5, 2, 3, 9}
	};

	int tab_4[9][9] = {
		{4, 9, 6, 1, 7, 5, 8, 3, 2},
		{2, 1, 8, 3, 6, 9, 7, 4, 5},
		{7, 5, 3, 2, 4, 8, 1, 9, 6},
		{5, 3, 1, 6, 2, 7, 9, 8, 4},
		{6, 4, 9, 8, 1, 3, 2, 5, 7},
		{8, 2, 7, 5, 9, 4, 6, 1, 3},
		{1, 8, 5, 7, 3, 6, 4, 2, 9},
		{9, 6, 2, 4, 5, 1, 3, 7, 8},
		{3, 7, 4, 9, 8, 2, 5, 6, 1}
	};

	int losuj_tab = rand() % 4 + 1;

	//automatyzacja wyboru tablicy
	switch (losuj_tab){
		case 1:
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					tab[i][j] = tab_1[i][j];
				}
			}
			break;
		case 2:
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					tab[i][j] = tab_2[i][j];
				}
			}
			break;
		case 3:
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					tab[i][j] = tab_3[i][j];
				}
			}
			break;
		case 4:
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					tab[i][j] = tab_4[i][j];
				}
			}
			break;
		default:
			break;
	}

	system("CLS");

	//podmiana losowych pol na '0'
	for (int i = 0; i < pola_do_podmiany; i++) {
		int a{}, b{};
		a = rand() % 9;
		b = rand() % 9;
		if (tab[a][b] == 0) {
			i--;
		}
		else {
			tab[a][b] = 0;
		}
	}


	//glowna petla programu
	do {
		int rzad{}, kolumna{}, wartosc{}, pozycja{};

		switch (poziom_trudnosci) {
		case 1:
			cout << "Poziom: Latwy" << endl;
			break;
		case 2:
			cout << "Poziom: Sredni" << endl;
			break;
		case 3:
			cout << "Poziom: Trudny" << endl;
			break;
		default:
			break;
		}

		//zabawa w kolory i formatowanie
		printf("\033[1;32m");
		cout << "   " << "#  ";
		printf("\033[1;37m");
		cout << "1" << " " << "2" << " " << "3" << "   " << "4" << " " << "5" << " " << "6" << "   " << "7" << " " << "8" << " " << "9" << endl;
		printf("\033[1;32m");
		cout << " # # # # # # # # # # # # # #";
		printf("\033[1;37m");

		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) {		//co 3 daje odstep
				cout << endl;
			}
			cout << " " << i + 1;
			printf("\033[1;32m");
			cout << " #";
			printf("\033[1;37m");
			for (int j = 0; j < 9; j++) {
				pozycja = tab[i][j];
				if (j % 3 == 0) {		//i tu tez daje odstep
					cout << "  ";
				}
				if (tab[i][j] == 0) {		//zaznaczenie '0', zeby ulatwic odczyt uzytkownikowi
					printf("\033[1;34m");
					cout << "0";
					printf("\033[1;37m");
					cout << " ";
				}
				else if ((poziom(tab, i, j, pozycja) == true || pion(tab, i, j, pozycja) == true || kwadrat(tab, i, j, pozycja) == true) && (podpowiedz == "tak" || podpowiedz == "TAK")) {		//zaznacza bledne dane
					printf("\033[1;31m");
					cout << tab[i][j] << " ";
					printf("\033[1;37m");
				}
				else {
					cout << tab[i][j] << " ";
				}
			}
			cout << endl;
		}
		printf("\033[1;32m");
		cout << "   #" << endl;
		printf("\033[1;37m");

		//wprowadzenie danych 
		cout << "Podaj kolumne, rzad i wartosc:" << endl;
		cin >> kolumna;
		cin >> rzad;
		cin >> wartosc;

		if (!cin) {		//sprawdzenie czy liczba
			cin.clear();
			cin.ignore(40, '\n');
		}

		else if (poprawnosc(kolumna) == true && poprawnosc(rzad) == true && poprawnosc(wartosc) == true) {	//sprawdzenie czy w przedziale
			tab[rzad - 1][kolumna - 1] = wartosc;	//podmiana cyfry podanej przez u¿ytkownika
		}

		system("CLS");

	} while (czy_wygrana(tab) != true);		//koniec petli
	

	//wyczyszczenie konsoli i poinformowanie o wygranej
	system("CLS");
	cout << "Gratululacje wygranej" << endl;


	system("pause");
}