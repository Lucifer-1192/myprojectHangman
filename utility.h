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
using namespace std;
string chooseWord(const char* File_name, int lev);
string chooseTopic(int& HighScore, int lev);
bool contains(string secretWord, char guess, string& guessedAlpha);
void update(string& guessedWord, const string& secretWord, char guess);
void hint(const string& secretWord, string& guessedWord, int& hi);
void update_score(int& HighScore, int& Score, bool what, const int m);
void Option_1();