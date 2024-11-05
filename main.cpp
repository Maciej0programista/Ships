#include <iostream>
#include <vector>
#include <ncurses.h>

using namespace std;

// Funkcja do rysowania planszy
void rysuj_plansze(const vector<vector<int>>& plansza, int wybrany_x, int wybrany_y) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == wybrany_x && j == wybrany_y) {
                attron(COLOR_PAIR(1)); // Niebieski dla zaznaczenia
                printw("[");
                if (plansza[i][j] == 0) printw(".");
                else if (plansza[i][j] == 1) printw("#"); // Statek (dla testu)
                else if (plansza[i][j] == 2) printw("*");
                else if (plansza[i][j] == 3) printw("x");
                printw("]");
                attroff(COLOR_PAIR(1));
            } else {
                printw("[");
                if (plansza[i][j] == 0) printw(".");
                else if (plansza[i][j] == 1) printw("#");  // Statek (dla testu)
                else if (plansza[i][j] == 2) printw("*");
                else if (plansza[i][j] == 3) printw("x");

                printw("]");
            }
        }
        printw("\n");
    }
}


int main() {
    // Inicjalizacja ncurses
    initscr();
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK); // Para kolorów dla zaznaczenia
    noecho(); // Nie wyświetlaj wpisywanych znaków
    keypad(stdscr, TRUE); // Włącz obsługę strzałek
    curs_set(0); // Ukryj kursor

    // Reprezentacja planszy
    vector<vector<int>> plansza(10, vector<int>(10, 0));

    // Przykładowy statek dla testu
    plansza[5][3] = 1;
    plansza[5][4] = 1;


    int wybrany_x = 0;
    int wybrany_y = 0;
    int ch;

    while ((ch = getch()) != 'q') {
        erase(); // Wyczyść ekran

        switch (ch) {
            case KEY_UP:
                wybrany_x = max(0, wybrany_x - 1);
                break;
            case KEY_DOWN:
                wybrany_x = min(9, wybrany_x + 1);
                break;
            case KEY_LEFT:
                wybrany_y = max(0, wybrany_y - 1);
                break;
            case KEY_RIGHT:
                wybrany_y = min(9, wybrany_y + 1);
                break;
             case 's':
                if (plansza[wybrany_x][wybrany_y] == 1) {
                    plansza[wybrany_x][wybrany_y] = 2; // Trafiony
                } else {
                    plansza[wybrany_x][wybrany_y] = 3; // Pudło
                }
                break;
        }


        rysuj_plansze(plansza, wybrany_x, wybrany_y);
        refresh(); // Odśwież ekran
    }


    // Zakończenie ncurses
    endwin();

    return 0;
}
