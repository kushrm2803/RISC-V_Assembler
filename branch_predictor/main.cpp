#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

// Function to tokenize instruction
vector<string> instructionToToken(string &instruction)
{
    vector<string> tokens;
    istringstream iss(instruction);
    string token;
    bool ignoreNext = false; // Flag to ignore the next token

    // Read and tokenize each part of the instruction
    while (iss >> token) {
        if (token == "core") {
            // Process core number
            string core;
            iss >> core;
        } else if (token.find("0x") != string::npos) {
            // Process hexadecimal values
            tokens.push_back(token);
        } else if (token == "(") {
            // Process hexadecimal value within brackets
            string hexValue;
            iss >> hexValue;
            tokens.push_back("(" + hexValue + ")");
        } else if (token == ")") {
            // End of hexadecimal value within brackets, ignore
            continue;
        } else if (token.find(",") != string::npos) {
            // Process comma-separated arguments
            istringstream arg_iss(token);
            string arg;
            while (getline(arg_iss, arg, ',')) {
                tokens.push_back(arg);
            }
        } else if (token == "pc") {
            // Process program counter
            tokens.push_back(token);
            iss >> token;
            tokens.push_back(token);
        } else if (token.find("(") != string::npos) {
            // Process register and offset within brackets
            size_t open_paren_pos = token.find("(");
            string offset = token.substr(0, open_paren_pos);
            string reg = token.substr(open_paren_pos + 1, token.length() - open_paren_pos - 2);
            tokens.push_back(offset);
            tokens.push_back(reg);
        } else {
            // Process other instructions
            if (!ignoreNext) {
                tokens.push_back(token);
            } else {
                ignoreNext = false;
            }
        }
        if (token == "pc") {
            ignoreNext = true;
        }
    }

    return tokens;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i <= argc; i++)
    {
        ifstream fin;
        ofstream fout;
        fin.open(argv[i]);
        string instruct;
        // Generate addresses of instructions
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty())
                continue;
            for (auto token : tokens)
                cout << "TOKEN:" << token << " ";
            cout << endl;
        }
    }
}