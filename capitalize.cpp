#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <cctype>
#include <iostream>

using namespace std;

const char UsageHelp[] =  "Usage: \n (1) capitalize <inputFile.srt> \n (2) capitalize <inputFile.srt> <dictionaryFile.txt>";

set <string> toCapitalize;

int main (int argc, char* argv[]) {
    string inFile, dictFile;

    if (argc == 2) {
        string file = argv[1];
        auto found = file.find (".srt");
        if (found == string::npos) {
            cerr << "Not a .srt file!" << '\n';
            cerr <<UsageHelp << '\n';
            return 1;
        }

        dictFile = "MattS_dictionary.txt";
        inFile = file;
    }
    else {
        if (argc < 2) {
            cerr << UsageHelp << '\n';
            return 1;
        }
        else {
            inFile = argv[1];
            dictFile = argv[2];
            auto found = inFile.find (".srt");
            if (found == string::npos) {
                cerr << "Not a .srt file!" << '\n';
                cerr << UsageHelp << '\n';
                return 1;
            }
            found = dictFile.find (".txt");
            if (found == string::npos) {
                cerr << "Not a .txt file!" << '\n';
                cerr << UsageHelp << '\n';
                return 1;
            }
        }
    }

    ifstream fdict (dictFile);
    if ( !fdict.is_open()) {
        cerr << "Could not open " << dictFile << " file! \n";
    }
    ifstream fin (inFile);
    if ( !fin.is_open()) {
        cerr << "Could not open " << inFile << " file! \n";
    }
    ofstream fout ("Cap_" + inFile);

    //insert all words in the map
    string word;
    while (fdict >> word){
        toCapitalize.insert (word);
    }

    string inWord;
    char c;
    bool pctFlag = true;

    while (fin >> noskipws >> c && !isalpha (c)) {
        fout << c;
    }
    inWord.push_back (c);

    while (fin >> c) {
        if (isalpha (c)) {
            inWord.push_back (c);
        }
        else {
            transform (inWord.begin(), inWord.end(), inWord.begin(), ::tolower);
            inWord[0] = toupper (inWord[0]);

            if (pctFlag == false && toCapitalize.find (inWord) == toCapitalize.end() ) {
               inWord[0] = tolower (inWord[0]);
            }

            fout << inWord;

            if (isalpha (inWord[0])) {
                pctFlag = false;
            }

            inWord.erase ();

            fout << c;

            if (c == '.' || c == '?' || c == '!') {
                pctFlag = true;
            }
        }
    }

    return 0;
}
