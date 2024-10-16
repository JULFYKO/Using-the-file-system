#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

void createSampleFiles() {
    ofstream file1("file1.txt");
    ofstream file2("file2.txt");
    ofstream inputFile("input.txt");

    file1 << "Lorem ipsum dolor sit amet,\n consectetur adipiscing elit. Vivamus est orci,\n iaculis a posuere nec, ullamcorper id orci. Duis varius.";
    file2 << "Lorem ipsum dolor sit amet,\n consectetur adipiscing elit. Integer quis leo sapien.\n Sed rutrum cursus elementum.\n Aenean facilisis tempus efficitur.";
    inputFile << "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n Integer quis leo sapien. Sed rutrum cursus elementum. Aenean facilisis tempus efficitur.\n12345\nAEIOU";

    file1.close();
    file2.close();
    inputFile.close();
}

void compareFiles(const string& file1Name, const string& file2Name) {
    ifstream file1(file1Name);
    ifstream file2(file2Name);
    string line1, line2;
    int lineNum = 0;

    while (getline(file1, line1) && getline(file2, line2)) {
        lineNum++;
        if (line1 != line2) {
            cout << "Difference in line " << lineNum << ":\n";
            cout << "File 1: " << line1 << "\n";
            cout << "File 2: " << line2 << "\n";
            return;
        }
    }

    if (file1.eof() != file2.eof()) {
        cout << "Files have different line counts.\n";
    }
    else {
        cout << "Files are identical.\n";
    }
}

void fileStatistics(const string& inputFileName, const string& outputFileName) {
    ifstream in(inputFileName);
    ofstream out(outputFileName);
    char c;
    int chars = 0, lines = 1, vowels = 0, consonants = 0, digits = 0;

    while (in.get(c)) {
        chars++;
        if (c == '\n') lines++;
        if (strchr("aeiouAEIOU", c)) vowels++;
        else if (isalpha(c)) consonants++;
        else if (isdigit(c)) digits++;
    }

    out << "Characters: " << chars << "\n";
    out << "Lines: " << lines << "\n";
    out << "Vowels: " << vowels << "\n";
    out << "Consonants: " << consonants << "\n";
    out << "Digits: " << digits << "\n";
}

void caesarCipher(const string& inputFileName, const string& outputFileName, int key) {
    ifstream in(inputFileName);
    ofstream out(outputFileName);
    char c;

    while (in.get(c)) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = ((c - base + key) % 26) + base;
        }
        out.put(c);
    }
}

int main() {
    createSampleFiles();

    compareFiles("file1.txt", "file2.txt");

    fileStatistics("input.txt", "statistics.txt");

    caesarCipher("input.txt", "encrypted.txt", 3);

    return 0;
}
