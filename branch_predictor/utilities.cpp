#include<bits/stdc++.h>
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

// Function to convert a hexadecimal string to decimal number
int hex_to_dec(string hex)
{
    map<char, int> hex_dict = {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}};
    int num = 0;
    int j = 1;
    for (int i = hex.size() - 1; i >= 0; i--)
    {
        num += hex_dict[hex[i]] * j;
        j *= 16;
    }
    return num;
}

// Function to convert a decimal number to hexadecimal string representation
string dec_to_hex(int num)
{
    string ans = "";
    map<int, char> hex_dict = {
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}};
    while (num)
    {
        ans += hex_dict[num % 16];
        num /= 16;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

bool actualBranch(string cur_pc,string prev_pc){
    if(hex_to_dec(cur_pc)-hex_to_dec(prev_pc)!=4)return true;
    else return false;
}