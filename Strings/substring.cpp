#include <iostream>
#include <string>
#include <cstring>

#define R 256

int power(int base, int exponent) {
    int total = 1;
    for (int i = 0; i < exponent; i++) {
        total *= base;
    }
    return total;
}

int rabinkarp(std::string text, std::string pattern) {
    const int BIG_PRIME = 997;
    const int patternLength = pattern.size();
    const int RM = power(R, patternLength - 1);

    int patternHash = pattern[0];
    for (int i = 1; i < patternLength; i++) {
        patternHash = ((R * patternHash) + pattern[i]) % BIG_PRIME;
    }

    int currentHash = text[0];
    for (int i = 1; i < patternLength; i++) {
        currentHash = ((R * currentHash) + text[i]) % BIG_PRIME;
    }

    if (currentHash == patternHash && text.substr(0, patternLength) == pattern) {
        return 0;
    }

    for (int i = 1; i <= text.length() - patternLength; i++) {
        currentHash = (R * (currentHash - (RM * text[i - 1])) + text[i + patternLength - 1]) % BIG_PRIME;
        if (currentHash < 0) {
            currentHash += BIG_PRIME;
        }
        if (currentHash == patternHash && text.substr(i, patternLength) == pattern) {
            return i;
        }
    }

    return -1;
}

int boyermoore(std::string text, std::string pattern) {
    int lastOccurence[R];
    memset(lastOccurence, -1, R * sizeof(int));
    for (int i = 0; i < pattern.size(); i++) {
        lastOccurence[pattern[i]] = i;
    }

    for (int i = 0; i <= text.size() - pattern.size();) {
        for (int j = pattern.size() - 1; j >= 0; j--) {
            if (text[i + j] != pattern[j]) {
                i += std::max(1, j - lastOccurence[text[i + j]]);
                break;
            }
            if (j == 0) {
                return i;
            }
        }
    }

    return -1;
}

int knuthmorrispratt(std::string text, std::string pattern) {
    int patternLength = pattern.length();
    int dfa[patternLength][R];

    // Create initial state
    for (int i = 0; i < patternLength; i++) {
        dfa[i][pattern[i]] = i + 1;
    }
    for (int i = 0; i < R; i++) {
        if (i != pattern[0]) {
            dfa[0][i] = 0;
        }
    }

    int lastState = 0;
    // Create remaining states
    for (int node = 1; node < patternLength; node++) {
        for (int c = 0; c < R; c++) {
            if (c != pattern[node]) {
                dfa[node][c] = dfa[lastState][c];
            }
        }
        lastState = dfa[lastState][pattern[node]];
    }

    int currentState = 0;
    for (int i = 0; i < text.length(); i++) {
        currentState = dfa[currentState][text[i]];
        if (currentState == patternLength) {
            return i - patternLength + 1;
        }
    }

    return -1;
}

int main() {
    std::string text = "fjwpoiefjjpabcqoqo28n";
    std::string pattern = "abc";

    std::cout << rabinkarp(text, pattern) << std::endl;
    std::cout << boyermoore(text, pattern) << std::endl;
    std::cout << knuthmorrispratt(text, pattern) << std::endl;

    return 0;
}