#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <windows.h>
#include <conio.h>

#include "draw.h"
#include "utility.h"
#include "simpleAI.h"

using namespace std;
bool visit[26];
bool alo;
int th, dif, hi;
map <char, int> dup;
char alpp[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',  'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
int main()
{
    srand(time(0));
again:clearScreen();
    showIntro();
    char choice;
    choice = _getch();
    if (choice == '1') {
    mm:clearScreen();
        showOption();
        char ch; ch = _getch();
        if (ch == '1') { alo = true; Option_1(); hi = 3; goto again; }
        else if (ch == '2') { alo = false; Option_2(); goto again; }
        else if (ch == '3') goto again;
        else goto mm;
    }
    else if (choice == '2') {
    ttt: clearScreen();
        cout << "                                                                                                       ";
        cout << "DEV by NO_ONE" << endl; cout << "       B: BACK TO THE MENU";
        char c; c = _getch();
        if (c == 'B' || c == 'b') goto again;
        else goto ttt;
    }
    else if (choice == '3') {
        showOuttro();
        Sleep(3000);
        clearScreen();
        return 0;
    }
    else goto again;
}
