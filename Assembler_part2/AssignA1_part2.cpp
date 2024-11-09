#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ifstream sin("symbol_table.txt");
    ifstream lin("littab.txt");
    ifstream fin("ic.txt");
    ofstream fout("machineCode.txt");

    string line, word;
    vector<pair<string, int>> symtab;
    vector<pair<string, int>> littab;

    // Read Symbol Table
    while (getline(sin, line)) {
        stringstream st(line);
        st >> word;
        string label = word;
        st >> word;
        symtab.push_back({label, stoi(word)});
    }
    sin.close();

    // Read Literal Table
    while (getline(lin, line)) {
        stringstream st(line);
        st >> word;
        string label = word;
        st >> word;
        littab.push_back({label, stoi(word)});
    }
    lin.close();

    int lc = -1;

    // Process Intermediate Code
    while (getline(fin, line)) {
        stringstream st(line);
        st >> word;
        string cls = word.substr(1, 2); // Class code
        string mnemonic = word.substr(4, 2); // Mnemonic code

        if (cls == "AD") {
            fout << "No Machine Code" << endl;
            if (mnemonic == "01") { // START
                st >> word;
                lc = stoi(word.substr(3, word.length() - 4));
            } else if (mnemonic == "03") { // ORIGIN
                st >> word;
                int index = stoi(word.substr(4, 1)) - 1;
                lc = symtab[index].second;

                // Check for additional offset, e.g., +2 in (S,02)+2
                size_t plus_pos = word.find('+');
                if (plus_pos != string::npos) {
                    int offset = stoi(word.substr(plus_pos + 1));
                    lc += offset;
                }
            }
            // Skip increment for "No Machine Code" lines
            continue;
        }

        if (cls == "IS") {
            fout << lc << " " << mnemonic << " ";
            lc++;

            if (mnemonic == "00") { // STOP
                fout << "0 000" << endl;
                continue;
            }

            // Operand 1
            st >> word;
            if (word[1] != 'S' && word[1] != 'L') {
                fout << word.substr(1, 1) << " ";
                st >> word;
            } else {
                fout << "0 ";
            }

            // Operand 2
            int num = stoi(word.substr(3, 2)) - 1;
            if (word[1] == 'S') {
                fout << symtab[num].second << endl;
            } else if (word[1] == 'L') {
                fout << littab[num].second << endl;
            }
        } else if (cls == "DL") {
            fout << lc << " ";
            lc++;

            if (mnemonic == "01") { // DC
                fout << "00 0 ";
                st >> word;
                fout << "00" << word.substr(3, 1) << endl;
            } else if (mnemonic == "02") { // DS
                fout << "No Machine Code" << endl;
            }
        }
    }

    fout.close();
    fin.close();
    cout << "\nProgram for Pass-2 is executed successfully!\n";

    return 0;
}