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
int getUserLength() {
    int wordlength;
 er:clearScreen();
    cout << "                                                                                                       ";\
    cout << "ENTER YOUR WORD LENGTH:";
    cin >> wordlength;
    if (wordlength <= 0) goto er;
    return wordlength;
}

bool isAllDash(const string& s)
{
    for (unsigned int i = 0; i < s.length(); i++)
        if (s[i] != '_') return false;
    return true;
}

bool isAllNOTDash(const string& s) {
    for (unsigned int i = 0; i < s.length(); i++)
        if (s[i] == '_') return false;
    return true;
}

string getUserAnswer(char guess) {
    if (guess == 'u' || guess == 'i' || guess == 'a' || guess == 'o' || guess == 'e') {
        cout << "                                                                                                       ";
        cout << "Is there an '" << guess << "' in the word?" << endl;
    }
    else {
        cout << "                                                                                                       ";
        cout << "Is there a '" << guess << "' in the word?" << endl;
    }
    cout << "                                                                                                       ";
    cout << "Enter your mask:";
    string answer;
    cin >> answer;
    for (unsigned int i = 0; i < answer.length(); i++) {
        if (65 <= answer[i] && answer[i] <= 90) answer[i] += 32;
    }
    return answer;
}

bool badMask(string s, string secretWord, char guess) {
    if (s.size() != secretWord.size()) return true;
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == '_' || (97 <= s[i] && s[i] <= 122)) continue;
        else return true;
    }
    for (unsigned int i = 0; i < s.size(); i++) {
        if (secretWord[i] != '_' && secretWord[i] != s[i] && s[i] != '_') return true;
        else continue;
    }
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] != '_' && s[i] != guess) return true;
        else continue;
    }
    return false;
}

void update(string& secretWord, const string& ans) {
    for (unsigned int i = 0; i < ans.size(); i++) {
        if (secretWord[i] == '_' && ans[i] != '_') { secretWord[i] = ans[i]; }
    }
}

char getAguess() {
    int max = 0;
    char guess;
    for (int i = 0; i < 26; i++) {
        if (dup[alpp[i]] > max && !visit[alpp[i] - 'a']) {
            max = dup[alpp[i]];
            guess = alpp[i];
        }
    }
    return guess;
}

void getDUP(vector<string> wordList) {
    for (unsigned int i = 0; i < wordList.size(); i++) {
        for (unsigned int j = 0; j < wordList[i].length(); j++) {
            dup[wordList[i][j]]++;
        }
    }
}

bool CONTAINS(string s, char guess) {
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == guess) return true;
    }
    return false;
}

void filter(vector<string>& wordList, char guess, string ans) {
    if (isAllDash(ans)) {
        for (unsigned int i = 0; i < wordList.size(); i++) {
            if (CONTAINS(wordList[i], guess)) {
                for (unsigned int j = 0; j < wordList[i].length(); j++) { dup[wordList[i][j]]--; }
                wordList.erase(wordList.begin() + i);
                i--;
            }
        }
    }
    else {
        for (unsigned int i = 0; i < wordList.size(); i++) {
            if (!CONTAINS(wordList[i], guess)) {
                for (unsigned int j = 0; j < wordList[i].length(); j++) { dup[wordList[i][j]]--; }
                wordList.erase(wordList.begin() + i);
                i--;
            }
            else {
                bool flag = false;
                for (unsigned int j = 0; j < ans.size(); j++) {
                    if ((ans[j] != '_' && ans[j] != wordList[i][j]) || (ans[j] == '_' && guess == wordList[i][j])) {
                        flag = true;
                        break;
                    }
                }
                if (flag) {
                    for (unsigned int j = 0; j < wordList[i].length(); j++) { dup[wordList[i][j]]--; }
                    wordList.erase(wordList.begin() + i);
                    i--;
                }
            }
        }
    }
}

void Option_2() {
    while (true) {
        for (int i = 0; i < 26; i++) { dup[alpp[i]] = 0; }
        for (int i = 0; i < 26; i++) { visit[i] = false; }
        //string back;
        int wordlength = getUserLength();
        vector<string> wordList;
        fstream fs("dictionary.txt");
        string s;
        while (fs >> s) {
            if (s.size() == wordlength) wordList.push_back(s);
        }
        fs.close();
        getDUP(wordList);
        string secretWord = string(wordlength, '_');
        int badGuessCount = 0;
        string guessedAlpha = "";
        renderGame(secretWord, badGuessCount, guessedAlpha);
        while (badGuessCount < 7) {
            char guess;
            guess = getAguess();
            visit[guess - 'a'] = true;
            string ans = getUserAnswer(guess);
            while (badMask(ans, secretWord, guess)) {
                cout << "                                                                                                       ";
                cout << "That is a bad mask !!!! Please try again." << endl;
                Sleep(1000);
                clearScreen();
                renderGame(secretWord, badGuessCount, guessedAlpha);
                ans = getUserAnswer(guess);
            }
            if (isAllDash(ans)) { badGuessCount++; guessedAlpha += " "; guessedAlpha += guess; }
            else { update(secretWord, ans); }
            filter(wordList, guess, ans);
            clearScreen();
            renderGame(secretWord, badGuessCount, guessedAlpha);
            if (isAllNOTDash(secretWord)) break;
            if (wordList.size() == 0) break;
        }
        clearScreen();
        displayFinalResult_2(wordList, badGuessCount);
        Sleep(2000);
    fault: clearScreen();
        cout << endl << "                                                                                                  ";
        cout << "Do you want to play again ? (Y/N) :";
        string ns;
        cin >> ns;
        if (ns == "n" || ns == "N") return;
        else if (ns == "y" || ns == "Y") continue;
        else goto fault;
    }
}