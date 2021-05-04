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
int getUserLength();
bool isAllDash(const string& s);
bool isAllNOTDash(const string& s);
string getUserAnswer(char guess);
bool badMask(string s, string secretWord, char guess);
void updateWord(string& secretWord, const string& ans);
char getAguess();
void getDUP(vector<string> wordList);
bool CONTAINS(string s, char guess);
void filter(vector<string>& wordList, char guess, string ans, bool pass);
void Option_2();