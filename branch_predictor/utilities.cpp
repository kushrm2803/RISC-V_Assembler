#include <bits/stdc++.h>
using namespace std;

// Function to tokenize instruction
vector<string> instructionToToken(string &instruction)
{
    vector<string> tokens;
    istringstream iss(instruction);
    string token;
    bool ignoreNext = false; // Flag to ignore the next token

    // Read and tokenize each part of the instruction
    while (iss >> token)
    {
        if (token == "core")
        {
            // Process core number
            string core;
            iss >> core;
        }
        else if (token.find("0x") != string::npos)
        {
            // Process hexadecimal values
            tokens.push_back(token);
        }
        else if (token == "(")
        {
            // Process hexadecimal value within brackets
            string hexValue;
            iss >> hexValue;
            tokens.push_back("(" + hexValue + ")");
        }
        else if (token == ")")
        {
            // End of hexadecimal value within brackets, ignore
            continue;
        }
        else if (token.find(",") != string::npos)
        {
            // Process comma-separated arguments
            istringstream arg_iss(token);
            string arg;
            while (getline(arg_iss, arg, ','))
            {
                tokens.push_back(arg);
            }
        }
        else if (token == "pc")
        {
            // Process program counter
            tokens.push_back(token);
            iss >> token;
            tokens.push_back(token);
        }
        else if (token.find("(") != string::npos)
        {
            // Process register and offset within brackets
            size_t open_paren_pos = token.find("(");
            string offset = token.substr(0, open_paren_pos);
            string reg = token.substr(open_paren_pos + 1, token.length() - open_paren_pos - 2);
            tokens.push_back(offset);
            tokens.push_back(reg);
        }
        else
        {
            // Process other instructions
            if (!ignoreNext)
            {
                tokens.push_back(token);
            }
            else
            {
                ignoreNext = false;
            }
        }
        if (token == "pc")
        {
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
string dec_to_hex(long long num)
{
    string ans = "";
    map<int, char> hex_dict = {
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'a'}, {11, 'b'}, {12, 'c'}, {13, 'd'}, {14, 'e'}, {15, 'f'}};
    while (num)
    {
        ans += hex_dict[num % 16];
        num /= 16;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// Function to generate output file name for branch target buffer
string outputBranchTargetBuffer(string in)
{
    // Erase the last 3 characters (assumed to be the extension)
    in.erase(in.size() - 4);
    in += "_OutputBTB.txt";
    cout << "Created BTB Output File" << endl;
    return in;
}

// Function to generate output file name for history table
string outputHistoryTable(string in)
{
    // Erase the last 3 characters (assumed to be the extension)
    in.erase(in.size() - 4);
    in += "_OutputHT.txt";
    cout << "Created HT Output File" << endl;
    return in;
}

// Function to generate output file name for accuracy
string outputAccuracy(string in)
{
    // Erase the last 3 characters (assumed to be the extension)
    in.erase(in.size() - 4);
    in += "_OutputAccuracy.txt";
    cout << "Created Accuracy Output File" << endl;
    return in;
}

// Function to determine if the branch is actually taken or not taken
bool actualBranch(string cur_pc, string prev_pc)
{
    cur_pc.erase(0, 2);
    prev_pc.erase(0, 2);
    if (hex_to_dec(cur_pc) - hex_to_dec(prev_pc) != 4)
        return true;
    else
        return false;
}

// Function to calculate the branch target address
void bTB(map<string, string> &branchTargetBuffer, string branch_pc, vector<string> &tokens)
{
    if (tokens[tokens.size() - 2] == "+")
    {
        string cur_pc = branch_pc;
        cur_pc.erase(0, 2);
        long long int_cur_pc = hex_to_dec(cur_pc);
        long long result = int_cur_pc + stoll(tokens[tokens.size() - 1]);
        if (result < 0) // For the case of 2's complement
            result = 4294967296 + result;
        string target_pc = "0x" + dec_to_hex(result);
        branchTargetBuffer[branch_pc] = target_pc;
    }
    if (tokens[tokens.size() - 2] == "-")
    {
        string cur_pc = branch_pc;
        cur_pc.erase(0, 2);
        long long int_cur_pc = hex_to_dec(cur_pc);
        long long result = int_cur_pc - stoll(tokens[tokens.size() - 1]);
        if (result < 0) // For the case of 2's complement
            result = 4294967296 + result;
        string target_pc = "0x" + dec_to_hex(result);
        branchTargetBuffer[branch_pc] = target_pc;
    }
}

// Function to calculate accuracy and handle ZERO case
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

// Function for one-bit branch predictor
int oneBitBranchPredictor(map<string, int> &oneBitBuffer, unordered_map<string, string> &history_table, map<string, string> &oneBitPredict_table, string &branch_pc)
{
    // 0 => not taken, 1 => taken
    int prev_state = oneBitBuffer[branch_pc];
    oneBitPredict_table[branch_pc].push_back(prev_state + '0');
    int history_state = history_table[branch_pc].back() - '0';
    if (history_state == oneBitBuffer[branch_pc])
        return 1; // Correct prediction
    else
    {
        oneBitBuffer[branch_pc] = history_state;
        return 0; // Wrong prediction
    }
}

// Function for two-bit branch predictor
int twoBitBranchPredictor(map<string, int> &twoBitBuffer, unordered_map<string, string> &history_table, map<string, string> &twoBitPredict_table, string &branch_pc)
{
    // 0=>strongly not taken 1=>not taken 2=>taken 3=>strongly taken
    int prev_state = twoBitBuffer[branch_pc];
    if (prev_state == 0)
        twoBitPredict_table[branch_pc].push_back(prev_state + '0');
    else if (prev_state == 1 || prev_state == 2)
        twoBitPredict_table[branch_pc].push_back(prev_state - 1 + '0');
    else if (prev_state == 3)
        twoBitPredict_table[branch_pc].push_back(prev_state - 2 + '0');
    int history_state = history_table[branch_pc].back() - '0';
    if (twoBitBuffer[branch_pc] == 0)
    {
        if (history_state)
            twoBitBuffer[branch_pc] = 1;
    }
    else if (twoBitBuffer[branch_pc] == 1)
    {
        if (history_state)
            twoBitBuffer[branch_pc] = 2;
        else
            twoBitBuffer[branch_pc] = 0;
    }
    else if (twoBitBuffer[branch_pc] == 2)
    {
        if (history_state)
            twoBitBuffer[branch_pc] = 3;
        else
            twoBitBuffer[branch_pc] = 1;
    }
    else
    {
        if (!history_state)
            twoBitBuffer[branch_pc] = 2;
    }
    if ((prev_state == twoBitBuffer[branch_pc]) || (prev_state == 1 && twoBitBuffer[branch_pc] == 0) || (prev_state == 2 && twoBitBuffer[branch_pc] == 3))
        return 1; // Correct prediction
    else
        return 0; // Wrong prediction
}
