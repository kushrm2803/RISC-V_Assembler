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
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}};
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
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'a'}, {11, 'b'}, {12, 'b'}, {13, 'd'}, {14, 'e'}, {15, 'f'}};
    while (num)
    {
        ans += hex_dict[num % 16];
        num /= 16;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

bool actualBranch(string cur_pc,string prev_pc){
    // cout<<cur_pc<<" "<<prev_pc<<endl;
    cur_pc.erase(0,2);
    prev_pc.erase(0,2);
    // cout<<cur_pc<<" "<<prev_pc<<endl;
    // cout<<hex_to_dec(cur_pc)<<" "<<hex_to_dec(prev_pc)<<endl;
    if(hex_to_dec(cur_pc)-hex_to_dec(prev_pc)!=4)return true;
    else return false;
}

float Accuracy_cal(int a, int b)
{
    if (a + b == 0)
    {
        // Handling division by zero
        return 0.0;
    }
    else
    {
        float acc = (double)a / (double)(a + b);
        return acc * 100;
    }
}

int oneBitBranchPredictor(map<string, int> &oneBitBuffer, map<string, string> &history_table, string &branch_pc) {
    // 0 => not taken, 1 => taken
    int prev_state = oneBitBuffer[branch_pc];
    // cout<<"history_table of "<<branch_pc<<" is "<<history_table[branch_pc]<<endl;
    int history_state = history_table[branch_pc].back() - '0';
    if (history_state == oneBitBuffer[branch_pc]) {
        // cout << "State of " << branch_pc << " changed from " << oneBitBuffer[branch_pc] << " to " << history_state << endl;
        return 1;
    } else {
        // cout << "State of " << branch_pc << " changed from " << oneBitBuffer[branch_pc] << " to " << history_state << endl;
        oneBitBuffer[branch_pc] = history_state;
        return 0;
    }
}


int twoBitBranchPredictor(map<string,int> &twoBitBuffer,map<string,string> &history_table,string&branch_pc){
    // 0=>strongly not taken 1=>not taken 2=>taken 3=>strongly taken
    int prev_state=twoBitBuffer[branch_pc];
    // cout<<"history_table of "<<branch_pc<<" is "<<history_table[branch_pc]<<endl;
    int history_state = history_table[branch_pc].back() - '0';
    if(twoBitBuffer[branch_pc]==0){
        if(history_state)twoBitBuffer[branch_pc]=1;
        // cout<<"State of "<<branch_pc<<" changed from "<<prev_state<<" to "<<twoBitBuffer[branch_pc]<<endl;
    }
    else if(twoBitBuffer[branch_pc]==1){
        if(history_state)twoBitBuffer[branch_pc]=2;
        else twoBitBuffer[branch_pc]=0;
        // cout<<"State of "<<branch_pc<<" changed from "<<prev_state<<" to "<<twoBitBuffer[branch_pc]<<endl;
    }
    else if(twoBitBuffer[branch_pc]==2){
        if(history_state)twoBitBuffer[branch_pc]=3;
        else twoBitBuffer[branch_pc]=1;
        // cout<<"State of "<<branch_pc<<" changed from "<<prev_state<<" to "<<twoBitBuffer[branch_pc]<<endl;
    }
    else{
        if(!history_state){
            twoBitBuffer[branch_pc]=2;
            // cout<<"State of "<<branch_pc<<" changed from "<<prev_state<<" to "<<twoBitBuffer[branch_pc]<<endl;
        }
    }
    if((prev_state==twoBitBuffer[branch_pc]) || (prev_state==1 && twoBitBuffer[branch_pc]==0) ||(prev_state==2 && twoBitBuffer[branch_pc]==3))return 1;
    else return 0;
}