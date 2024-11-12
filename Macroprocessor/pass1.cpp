#include <bits/stdc++.h>
using namespace std;

int count_pp = 0, count_kp = 0, mdtp = 1, kptp = 1, macro_count = 0;
string mnt = "", pntab = "", kpdt = "", mdt = "", ic = "";

// Helper function to create and write content to a file
void createAndWriteToFile(const string& filename, const string& content) {
    ofstream outfile(filename, ios::out);
    if (outfile.is_open()) {
        outfile << content;
        outfile.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// Helper function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream tokenStream(str);
    string token;
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
        // cout<<token<<" ";
    }
    // cout<<endl;
    return tokens;
}

// Processing function to handle macro processing
void process() {
    bool MACRO_DEF = false, IS_START = false;

    // Open the source file for reading
    ifstream file("source.txt");
    
    if (!file.is_open()) {
        cerr << "Unable to open source.txt file" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // check for start
        if (line.find("START")!=string::npos || IS_START) {
            // if exists add it to the ic.txt
            ic += line + "\n";
            IS_START = true;
        } 
        else {
            stringstream iss(line);
            string word;
            vector<string> words;

            // Process each word in the line, removing '&' characters
            while (iss >> word) {
                // cout<<word<<" : ";
                word.erase(remove(word.begin(), word.end(), '&'), word.end());
                // remove ,
                word.erase(remove(word.begin(), word.end(), ','), word.end());
                // cout<<word<<endl;
                words.push_back(word);
            }


            // Handling the macro definition
            if (MACRO_DEF) {
                // cout<<"--if: ";
                count_kp = 0; // keyword parameter
                count_pp = 0; // positional parameter
                string macro_name = words[0];
                pntab += macro_name + "\t";
                vector<string> parameterList;

                // Process the parameters of the macro
                for (int i = 1; i < words.size(); i++) {
                    // if "=" exists
                    if (words[i].find("=") != string::npos) {
                        // this section is for keyword parameters
                        count_kp++;
                        string parameter_name = words[i].substr(0, words[i].find("="));
                        string default_value = words[i].substr(words[i].find("=") + 1);
                        pntab += parameter_name + "\t";
                        kpdt += parameter_name + "\t" + default_value + "\n";
                        // cout<<parameter_name<<endl;
                        parameterList.push_back(parameter_name);
                    } 
                    else {
                        // positional parameter
                        count_pp++;
                        pntab += words[i] + "\t";
                        // cout<<words[i]<<endl;
                        parameterList.push_back(words[i]);
                    }
                }

                pntab += "\n";
                mnt += macro_name + "\t" + to_string(count_pp) + "\t" + to_string(count_kp) + "\t" + to_string(mdtp) + "\t" + to_string(kptp) + "\n";
                kptp += count_kp;
                MACRO_DEF = false;
            }
            // Start of a new macro definition
            else if (words[0] == "MACRO") {
                cout<<"--elseif: ";
                macro_count++;
                MACRO_DEF = true;
            }
            // Process macro body instructions for the MDT
            else {
                // cout<<"--else: ";
                string mdt_string = words[0] + "\t";
                // cout<<mdt_string<<endl;
                // cout<<pntab<<endl;
                string parameters_str = split(pntab, '\n')[macro_count - 1]; // Extracting the relevant PNTAB for this macro
                // cout<<parameters_str<<endl;
                vector<string> parameters = split(parameters_str, '\t');     // Splitting the string into parameter tokens
                // Replace parameters in the instruction with the proper PNTAB references (P,<index>)
                for (int i = 1; i < words.size(); i++) {
                    // if "=" exists
                    if (words[i].find('=') != string::npos) {
                        // literal : ="3"
                        mdt_string += words[i] + "\t";
                    } 
                    else {
                        cout<<"parameter: "<<words[i]<<endl;
                        cout<<"[ ";
                        for(auto x : parameters){cout<<x<<" | ";}
                        cout<<" ]"<<endl;
                        auto it = find(parameters.begin(), parameters.end(), words[i]);
                        if (it != parameters.end()) {
                            int index = distance(parameters.begin(), it);  // Indexing starts from 1
                            mdt_string += "(P," + to_string(index) + ")\t";
                        } 
                        else {
                            mdt_string += words[i] + "\t";  // If it's not a parameter, leave it unchanged
                        }
                    }
                }

                mdtp++;
                mdt_string += "\n";
                mdt += mdt_string;
            }
            for(auto i : words){cout<<i<<" ";}
            cout<<endl;
        }
    }

    file.close();

    // Write outputs to respective files
    createAndWriteToFile("MNT.txt", mnt);
    createAndWriteToFile("MDT.txt", mdt);
    createAndWriteToFile("KPDT.txt", kpdt);
    createAndWriteToFile("IC.txt", ic);
    createAndWriteToFile("PNTAB.txt", pntab);
    cout << "\nProgram executed successfully!";
}

int main() {
    process();
    return 0;
}