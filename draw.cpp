#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <windows.h>
#include <conio.h>
using namespace std;
extern bool visit[26];
extern bool alo;
extern int th, dif, hi;
extern map <char, int> dup;
extern char alpp[];
const string TOPIC[] = { "ADJECTIVE", "ANIMAL", "JOB", "SPORT", "WEATHER" };
const string FIGURE[] = {
    "                                                                                                          -----------  \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |         O  \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |         O  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |         O  \n"
    "                                                                                                          |        /|  \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |         O  \n"
    "                                                                                                          |        /|\\ \n"
    "                                                                                                          |            \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |         O  \n"
    "                                                                                                          |        /|\\ \n"
    "                                                                                                          |        /   \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |         O  \n"
    "                                                                                                          |        /|\\ \n"
    "                                                                                                          |        / \\ \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
};
const string LOSE[] = {
    "                                                                                                          -----------  \n"
    "                                                                                                          |         /  \n"
    "                                                                                                          |        O  \n"
    "                                                                                                          |       /|\\ \n"
    "                                                                                                          |       / \\ \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |         O  \n"
    "                                                                                                          |        /|\\ \n"
    "                                                                                                          |        / \\ \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         \\  \n"
    "                                                                                                          |          O  \n"
    "                                                                                                          |         /|\\ \n"
    "                                                                                                          |         / \\ \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n",
    "                                                                                                          -----------  \n"
    "                                                                                                          |         |  \n"
    "                                                                                                          |         O  \n"
    "                                                                                                          |        /|\\ \n"
    "                                                                                                          |        / \\ \n"
    "                                                                                                          |            \n"
    "                                                                                                        -----          \n"
};
const string WIN[] = {
    "                                                                                                                       \n"
    "                                                                                                                   O  \n"
    "                                                                                                                  /|\\ \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                  \\O  \n"
    "                                                                                                                   |\\ \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                   O/  \n"
    "                                                                                                                  /|   \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                  \\O/  \n"
    "                                                                                                                   |   \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                   O  \n"
    "                                                                                                                  /|\\ \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                  \\O/  \n"
    "                                                                                                                   |   \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                   O  \n"
    "                                                                                                                  /|\\ \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                  O  \n"
    "                                                                                                                  /|\\ \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                   O  \n"
    "                                                                                                                  /|\\ \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                    O  \n"
    "                                                                                                                  /|\\ \n"
    "                                                                                                                  / \\ \n",
    "                                                                                                                       \n"
    "                                                                                                                   O  \n"
    "                                                                                                                  /|\\ \n"
    "                                                                                                                  / \\ \n",
};
void showIntro() {
    //cout << "                                  ";
    cout << "                                                                                                     -----WELCOME TO HANGMAN-----" << endl;
    cout << "                                                                        ";
    cout << "                                         MENU" << endl;
    cout << "                                                                                                          ";
    cout << "     1.START" << endl;
    cout << "                                                                                                          ";
    cout << "     2.ABOUT" << endl;
    cout << "                                                                                                          ";
    cout << "     3.EXIT" << endl;
}
void showOption() {
    cout << "                                                                                                          ";
    cout << "     1.YOU GUESS" << endl;
    cout << "                                                                                                          ";
    cout << "     2.CP GUESSES" << endl;
    cout << "                                                                                                          ";
    cout << "     3.BACK" << endl;
}
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif // _WIN32
}
void showLevel(int& lev) {
    cout << "                 LEVEL:" << lev << endl;
}
void showTime(int& m, int& s) {
    if (s == 0) { s = 59; m--; }
    else s--;
    if (m < 0) { s = 0; m = 0; }
    cout << "                 TIME:" << m << ":" << (s < 10 ? "0" : "") << s;
    cout << "                                                                                                                                                                          ";
    return;
}
void showScore(int& HighScore, int& Score) {
    cout << "SCORE:" << Score << endl;
    cout << "                                                                                                                                                                                                    ";
    cout << "BEST:" << HighScore << endl;
}
void renderGame(string guessedWord, int badGuessCount, string guessedAlpha)
{
    if (alo) {
        cout << "                                                                                                          ";
        cout << "_____" << TOPIC[th] << "_____" << endl;
        cout << FIGURE[badGuessCount] << endl;
        cout << "                                                                                                          ";
        cout << guessedWord << endl << endl;
        cout << "                                                                                                       ";
        cout << "Number of wrong guesses: " << badGuessCount << endl;
        cout << "                                                                                                       ";
        cout << "Wrong alphabet: " << guessedAlpha << endl;
        cout << "                                                                                          ";
        cout << 1 << ".GUESS IT         " << 2 << ".HINT: " << hi << " left           " << 3 << ".GUESS THE ALPHABET"  << endl;
    }
    else {
        cout << FIGURE[badGuessCount] << endl;
        cout << "                                                                                                          ";
        cout << guessedWord << endl << endl;
        cout << "                                                                                                       ";
        cout << "Number of wrong guesses: " << badGuessCount << endl;
        cout << "                                                                                                       ";
        cout << "Wrong alphabet: " << guessedAlpha << endl;
    }
}
void displayFinalResult(const string& secretWord, const string& guessedWord, int badGuessCount, int HighScore, bool& pass, int lev, int m, int s, int Score) {
    switch (th) {
    case 0: {fstream ff("highscore1.txt"); ff << HighScore; ff.close(); break; }
    case 1: {fstream ff("highscore2.txt"); ff << HighScore; ff.close(); break; }
    case 2: {fstream ff("highscore3.txt"); ff << HighScore; ff.close(); break; }
    case 3: {fstream ff("highscore4.txt"); ff << HighScore; ff.close(); break; }
    case 4: {fstream ff("highscore5.txt"); ff << HighScore; ff.close(); break; }
    default: break;
    }
    if (secretWord == guessedWord && badGuessCount < 7) {
        int win = 0;
        pass = true;
        while (true) {
            if (win == 21) break;
            clearScreen();
            showLevel(lev);
            cout << "                 TIME:" << m << ":" << (s < 10 ? "0" : "") << s;
            cout << "                                                                                                                                                                          ";
            showScore(HighScore, Score);
            cout << WIN[win % 10] << endl;
            cout << "                                                                                                       ";
            cout << "Congrats!!! You are free";
            win++;
            Sleep(500);
        }
    }
    else {
        pass = false;
        int los = 0;
        while (true) {
            if (los == 20) break;
            clearScreen();
            showLevel(lev);
            cout << "                 TIME:" << m << ":" << (s < 10 ? "0" : "") << s;
            cout << "                                                                                                                                                                          ";
            showScore(HighScore, Score);
            cout << LOSE[los % 4] << endl;
            cout << "                                                                                                       ";
            cout << "Game Over!!! You are hanged" << endl;
            cout << "                                                                                                       ";
            cout << "The secret word is: " << secretWord << endl;
            los++;
            Sleep(500);
        }
    }
}
void displayFinalResult_2(vector<string>& wordList, int& badGuessCount) {
    if (wordList.size() == 0 || badGuessCount == 7) {
        int los = 0;
        while (true) {
            if (los == 20) break;
            clearScreen();
            cout << LOSE[los % 4] << endl;
            cout << "                                                                                                ";
            cout << "I GIVE UP! HANG ME PLEASE :((";
            los++;
            Sleep(500);
        }
   redo:clearScreen();
        cout << "                                                                                                   ";
        cout << "WHAT IS YOUR WORD? ";
        string word;
        cin >> word;
        bool inva = false;
        for (unsigned int i = 0; i < word.length(); i++) {
            if (65 <= word[i] && word[i] <= 90) word[i] += 32;
            else if (97 <= word[i] && word[i] <= 122) continue;
            else { inva = true;  break; }
        }
        if (inva) goto redo;
        fstream fs;
        fs.open("dictionary.txt", ios::app);
        int count = 5;
        while (count) {
            fs << endl << word;
            count--;
        }
        fs.close();
        clearScreen();
        cout << "                                                                                                   ";
        cout << "OK! I'LL BEAT YOU NEXT TIME";

    }
    else {
        int win = 0;
        while (true) {
            if (win == 21) break;
            clearScreen();
            cout << WIN[win % 10] << endl;
            cout << "                                                                                                ";
            cout << "HAHA, THAT WAS EASY FOR ME. I WON" << endl;
            cout << "                                                                                                ";
            cout << "YOUR SECRET WORD IS: " << wordList[0];
            win++;
            Sleep(500);
        }
    }
}
void showOuttro() {
    clearScreen();
    cout << "                                                                                                     ";
    cout << "---------THANK YOU---------" << endl;
}