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
extern bool visit[26];
extern bool alo;
extern int th, dif, hi;
extern map <char, int> dup;
extern char alpp[];
string chooseWord(const char* File_name, int lev)
{
    vector<string>WordList;
    ifstream ifs(File_name);
    string word;
    if (ifs.is_open()) {

        while (ifs >> word) {
            WordList.push_back(word);
        }
        ifs.close();
    }

    if (WordList.size() > 0) {
    pp:int randomIndex = rand() % WordList.size();
        string sss = WordList[randomIndex];
        if (1 <= lev && lev <= 2 && sss.size() <= 4) return sss;
        else if (3 <= lev && lev <= 4 && 5 <= sss.size() && sss.size() <= 7) return sss;
        else if (lev >= 5 && 8 <= sss.size()) return sss;
        else goto pp;
    }
    else return "";
}

string chooseTopic(int& HighScore, int lev) {
    hi = 3;
pp: clearScreen();
    string secretWord;
    int hs;
    cout << "                                                                                                       ";
    cout << "---------TOPIC---------" << endl;
    cout << "                                                                                                            ";
    cout << 1 << ".Adjective" << endl;
    cout << "                                                                                                            ";
    cout << 2 << ".Animal" << endl;
    cout << "                                                                                                            ";
    cout << 3 << ".Job" << endl;
    cout << "                                                                                                            ";
    cout << 4 << ".Sport" << endl;
    cout << "                                                                                                            ";
    cout << 5 << ".Weather" << endl;
    cout << "                                                                                                            ";
    cout << 6 << ".Back" << endl;
    char n;
    n = _getch();
    if (n == '6') return "";
    th = n - '0' - 1;
    switch (n) {
    case '1': { fstream ff("highscore1.txt"); ff >> hs; HighScore = hs; ff.close(); secretWord = chooseWord("adjective.txt", lev); break; }
    case '2': { fstream ff("highscore2.txt"); ff >> hs; HighScore = hs; ff.close(); secretWord = chooseWord("animal.txt", lev); break; }
    case '3': { fstream ff("highscore3.txt"); ff >> hs; HighScore = hs; ff.close(); secretWord = chooseWord("job.txt", lev); break; }
    case '4': { fstream ff("highscore4.txt"); ff >> hs; HighScore = hs; ff.close(); secretWord = chooseWord("sport.txt", lev); break; }
    case '5': { fstream ff("highscore5.txt"); ff >> hs; HighScore = hs; ff.close(); secretWord = chooseWord("weather.txt", lev); break; }
    default: goto pp;;
    }
    return secretWord;

}

bool contains(string secretWord, char guess, string& guessedAlpha)
{
    for (unsigned int i = 0; i < secretWord.length(); i++) {
        if (secretWord[i] == guess) return true;
    }
    if (!visit[guess - 'a']) {
        guessedAlpha += guess;
        guessedAlpha += ' ';
        visit[guess - 'a'] = true;
    }
    return false;
}

void update(string& guessedWord, const string& secretWord, char guess)
{
    for (unsigned int i = 0; i < secretWord.length(); i++) {
        if (secretWord[i] == guess) guessedWord[i] = guess;
    }
}

void hint(const string& secretWord, string& guessedWord, int& hi) {
    int n = secretWord.size();
    char c;
    if (hi > 0) {
        hi--;
        for (int i = 0; i < n; i++) {
            if (guessedWord[i] == '_') {
                c = secretWord[i];
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (secretWord[i] == c) {
                guessedWord[i] = c;
            }
        }
        cout << endl << "                                                                                                       ";
        cout << "OK!!";
    }
    else {
        cout << endl << "                                                                                                       ";
        cout << "Sorry!! No more hints left";
    }
}

void update_score(int& HighScore, int& Score, bool what, const int m) {
    if (what) {
        if (m >= 1) { Score += 100 * dif; Score += 500; }
        else { Score += 50 * dif; Score += 250; }
    }
    else {
        if (m >= 1) Score += 100;
        else Score += 50;
    }
    if (Score > HighScore) HighScore = Score;
}

void Option_1() {
re:clearScreen();
    int lev = 1;
    int HighScore, Score = 0;
    string secretWord = chooseTopic(HighScore, lev);
    while (true) {
        if (lev == 6) break;
        dif = 0;
        if (secretWord.size() == 0) return;
        clearScreen();
        string guessedWord = string(secretWord.length(), '_');
        string guessedAlpha = "";
        string guessIT = ""; // for GUESS IT
        char guess, c;
        const int  MAX_BAD_GUESSES = 7;
        int badGuessCount = 0;
        for (int i = 0; i < 26; i++) { visit[i] = false; }
        int m = 2, s = 1;
        bool what = false, pass;
        while (badGuessCount < MAX_BAD_GUESSES && secretWord != guessedWord) {
        tt: Sleep(1200);
            clearScreen();
            showLevel(lev);
            showTime(m, s);
            showScore(HighScore, Score);
            renderGame(guessedWord, badGuessCount, guessedAlpha);
            if ((s == 0 && m == 0) || (m < 0)) break;
            if (_kbhit()) {
                guess = _getch();
                if (guess == '1') {
                    while (true) {
                        if ((s == 0 && m == 0) || (m < 0)) { clearScreen();  showLevel(lev); showTime(m, s); showScore(HighScore, Score); renderGame(guessedWord, badGuessCount, guessedAlpha); cout << "Guess the word: " << guessIT; break; }
                        Sleep(1200);
                        clearScreen();
                        showLevel(lev);
                        showTime(m, s);
                        showScore(HighScore, Score);
                        renderGame(guessedWord, badGuessCount, guessedAlpha);
                        cout << "Guess the word: " << guessIT;
                        if (_kbhit()) {
                            c = _getche();
                            if (c == 8) guessIT.erase(guessIT.begin() + guessIT.size() - 1);
                            else guessIT.push_back(c);
                        }
                        else continue;
                        if (guessIT.size() == secretWord.size()) break;
                    }
                    for (unsigned int i = 0; i < guessIT.size(); i++) {
                        if (guessIT[i] != guessedWord[i]) dif++;
                    }
                    guessedWord = guessIT;
                    if (guessedWord == secretWord) {
                        what = true;
                        update_score(HighScore, Score, what, m);
                    }
                    break;
                }
                else if (guess == '2') {
                    //bool flag = hint(secretWord, guessedWord, hi);
                    char c;
                    while (true) {
                        Sleep(1200);
                        clearScreen();
                        showLevel(lev);
                        showTime(m, s);
                        showScore(HighScore, Score);
                        renderGame(guessedWord, badGuessCount, guessedAlpha);
                        cout << "                                                                                                       ";
                        cout << "Are you sure? (Y/N):";
                        //if (!flag) {
                          //  goto tt;
                        //}
                        //else continue;
                            if (_kbhit()) {
                                c = _getche();
                                if (c == 'N' || c == 'n') break;
                                else if (c == 'y' || c == 'Y') {
                                    hint(secretWord, guessedWord, hi);
                                    break;
                                }
                                else continue;
                            }
                    }
                    goto tt;
                }
                else if (guess == '3') {
                    char c;
                    while (true) {
                        if (s == 0 && m == 0) { clearScreen();  showLevel(lev); showTime(m, s); showScore(HighScore, Score); renderGame(guessedWord, badGuessCount, guessedAlpha); cout << "Guess the alphabet: "; break; }
                    ttp:Sleep(1200);
                        clearScreen();
                        showLevel(lev);
                        showTime(m, s);
                        showScore(HighScore, Score);
                        renderGame(guessedWord, badGuessCount, guessedAlpha);
                        cout << "                                                                                                       ";
                        cout << "Guess the alphabet: ";
                        if (_kbhit()) {
                            c = _getche();
                            if (65 <= c && c <= 90) c += 32;
                            if (visit[c - 'a']) goto ttp;
                            if (contains(secretWord, c, guessedAlpha)) {
                                update(guessedWord, secretWord, c);
                                update_score(HighScore, Score, what, m);
                            }
                            else { badGuessCount++; }
                            break;
                        }
                    }
                }
                else goto tt;
            }
        }
        Sleep(500);
        displayFinalResult(secretWord, guessedWord, badGuessCount, HighScore, pass, lev, m, s, Score);
        Sleep(500);
        if (pass) {
            int lucky = rand() % 5;
            if (lucky == 3) {
                clearScreen();
                cout << "                                                                                                          ";
                cout << "CONGRATULATION!!! YOU RECEIVE 1 HINT";
                hi++;
                Sleep(1200);
            }
            lev++;
            switch (th) {
            case 0: { secretWord = chooseWord("adjective.txt", lev); break; }
            case 1: { secretWord = chooseWord("animal.txt", lev); break; }
            case 2: { secretWord = chooseWord("job.txt", lev); break; }
            case 3: { secretWord = chooseWord("sport.txt", lev); break; }
            case 4: { secretWord = chooseWord("weather.txt", lev); break; }
            }
        }
        else break;
    }
fault: clearScreen();
    cout << endl << "                                                                                                  ";
    cout << "Do you want to play again ? (Y/N) :";
    string ans;
    cin >> ans;
    if (ans == "n" || ans == "N") return;
    else if (ans == "y" || ans == "Y") { clearScreen(); goto re; }
    else goto fault;
}