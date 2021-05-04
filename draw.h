#include<iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include<fstream>
using namespace std;
void showIntro();
void showOption();
void clearScreen();
void showLevel(int& lev);
void showTime(int& m, int& s);
void showScore(int& HighScore, int& Score);
void renderGame(string guessedWord, int badGuessCount, string guessedAlpha);
void displayFinalResult(const string& secretWord, const string& guessedWord, int badGuessCount, int HighScore, bool& pass, int lev, int m, int s, int Score);
void displayFinalResult_2(vector<string>& wordList, int& badGuessCount);
void showOuttro();
