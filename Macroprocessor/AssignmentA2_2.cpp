#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<int>> mnt;       // Macro Name Table
unordered_map<string, vector<string>> pntab;  // Parameter Name Table
unordered_map<string, string> kpdt;           // Keyword Parameter Default Table
unordered_map<int, string> aptab;             // Actual Parameter Table
string output = "";

// Function to read the MNT from the file
void readMNT() {
    ifstream file("MNT.txt");
    if (!file.is_open()) {
        cerr << "Unable to open MNT file" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string macro_name;
        int pp, kp, mdtp, kptp;
        ss >> macro_name >> pp >> kp >> mdtp >> kptp;
        mnt[macro_name] = {pp, kp, mdtp, kptp};
    }
    file.close();
}

// Function to read the PNTAB from the file
void readPNTAB() {
    ifstream file("PNTAB.txt");
    if (!file.is_open()) {
        cerr << "Unable to open PNTAB file" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string macro_name, param;
        vector<string> params;
        ss >> macro_name; // First token is the macro name
        while (ss >> param) {
            params.push_back(param); // Store parameters
        }
        pntab[macro_name] = params; // Associate macro with its parameters
    }
    file.close();
}

// Function to read the KPDT from the file
void readKPDT() {
    ifstream file("KPDT.txt");
    if (!file.is_open()) {
        cerr << "Unable to open KPDT file" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string key, value;
        ss >> key >> value; // Read keyword and its default value
        kpdt[key] = value; // Store in map
    }
    file.close();
}

// Function to read the IC and process the macros
void processIC() {
    ifstream icFile("IC.txt");
    ifstream mdtFile("MDT.txt");
    // Check if both files opened successfully
    if (!icFile.is_open() || !mdtFile.is_open()) {
        cerr << "Error: Unable to open IC.txt or MDT.txt" << endl;
        return;
    }
    string line;
    while (getline(icFile, line)) {
        stringstream ss(line);
        vector<string> words;
        string word;
        
        // Split the line into words
        while (ss >> word) {
            words.push_back(word);
        }

        if (words.empty()) {
            continue;  // Skip empty lines
        }

        // Check if the first word is a macro
        if (mnt.find(words[0]) == mnt.end()) {
            output += line + "\n";  // Not a macro, add to output
            continue;
        } 

        // Get MNT values for the macro
        int pp = mnt[words[0]][0];
        int kp = mnt[words[0]][1];
        int mdtp = mnt[words[0]][2];
        aptab.clear();  // Clear previous APTAB entries

        // Handling positional parameters
        if (words.size() < pp + 1) {
            cerr << "Error: Not enough positional parameters for macro " << words[0] << endl;
            return;
        }
        for (int i = 1; i <= pp; ++i) {
            aptab[i] = words[i];
        }

        // Handling keyword parameters
        for (int i = pp + 1; i < words.size(); ++i) {
            size_t equals_pos = words[i].find('=');
            if (equals_pos != string::npos) {
                string key = words[i].substr(0, equals_pos);
                string value = words[i].substr(equals_pos + 1);               
                if (value.empty()) {
                    aptab[i] = kpdt[key];  // Use default if value is empty
                } else {
                    aptab[i] = value;
                }
            }
        }

        // Move MDT pointer to the appropriate macro definition
        mdtFile.clear();  // Reset file state
        mdtFile.seekg(0, ios::beg);  // Move to beginning of the MDT file

        string mdt_line;
        int mdt_counter = 0;  // Track the current line in MDT
        bool macro_found = false;

        while (getline(mdtFile, mdt_line)) {
            if (++mdt_counter == mdtp) {  // Find the correct MDT index
                macro_found = true;
                break;
            }
        }

        if (!macro_found) {
            cerr << "Error: Could not find MDT entry for macro " << words[0] << endl;
            return;
        }

        // Process the macro's MDT
        while (getline(mdtFile, mdt_line)) {
            if (mdt_line == "MEND") {
                break;  // Stop processing on MEND, do not add to output
            }

            stringstream mdt_ss(mdt_line);
            vector<string> mdt_words;
            while (mdt_ss >> word) {
                mdt_words.push_back(word);
            }

            output += mdt_words[0] + "\t";  // First word in MDT

            // Process the remaining words (parameters)
            for (size_t i = 1; i < mdt_words.size(); ++i) {
                if (mdt_words[i].find('=') == string::npos && mdt_words[i].find("(P,") != string::npos) {
                    // Extract the parameter index (P,<index>)
                    int param_index = stoi(mdt_words[i].substr(3, 1));
                    if (aptab.find(param_index) != aptab.end()) {
                        output += aptab[param_index] + "\t";  // Substitute the parameter
                    } else {
                        cerr << "Error: Parameter " << param_index << " not found in APTAB" << endl;
                    }
                } else {
                    output += mdt_words[i] + "\t";  // Regular parameter or literal
                }
            }

            output += "\n";  // Move to the next line in the MDT
        }
    }

    icFile.close();
    mdtFile.close();
}

int main() {
    readMNT();   // Read MNT
    readPNTAB(); // Read PNTAB
    readKPDT();  // Read KPDT
    processIC(); // Process IC

    // Write the final output to a file or print it
    ofstream outfile("ExpandedOutput.txt", ios::out);
    if (outfile.is_open()) {
        outfile << output; // Write output to file
        outfile.close();
        cout << "Pass 2 processing complete. Output written to ExpandedOutput.txt." << endl;
    } else {
        cerr << "Unable to write the output to file" << endl;
    }

    return 0;
}
