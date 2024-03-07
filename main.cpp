#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include "opcodes.cpp"
using namespace std;

map<string, int> mp;
int text_address;
int data_address;
int mode; // 0 -> .text && 1 -> .data

string chartostring(char *ch)
{
    int i = 0;
    string ans;
    while (ch[i] != '\0')
    {
        ans += ch[i];
        i++;
    }
    return ans;
}
string outputfilename(string in)
{
    in.erase(in.size() - 3);
    in += "mc";
    return in;
}
vector<string> instructionToToken(string instruct)
{
    vector<string> token;
    int len = instruct.size();
    bool flag = false;
    int j = 0;
    while (j < len)
    {
        string word;
        while (j < len && (instruct[j] == ' ' || instruct[j] == ','))
            j++;
        while (j < len && instruct[j] != ' ' && instruct[j] != ',')
        {
            if (instruct[j] == '#')
            { // comments case
                flag = true;
                break;
            }
            if (instruct[j] == ':' && mode == 0)
            { // labeling in case of text-mode
                mp[word] = text_address;
                word.erase();
                j++;
                break;
            }
            word += instruct[j];
            j++;
        }
        if (word.length() > 0)
            token.push_back(word);
        if (flag)
            break; // the next lines are comment
    }
    return token;
}

int main(int argc, char *argv[])
{
    defineAllOpcodes();
    mode = 0; // intial mode is text
    text_address = 0;
    // argv[0] is ./a.exe
    for (int i = 1; i <= argc; i++)
    {
        string in = chartostring(argv[i]);
        string out = outputfilename(in);

        ifstream fin;
        fin.open(in);
        string instruct;
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty())
                continue;
            if (mode == 0)
            { // text-mode
                if (tokens[0] == ".data")
                {
                    mode = 1;
                    continue;
                }
                // 31 instructions code begins

                // R-type
                if (r_func7.find(tokens[0]) != r_func7.end())
                {
                    tokens[1].erase(0, 1);
                    tokens[2].erase(0, 1);
                    tokens[3].erase(0, 1);
                    int idest = stoi(tokens[1]);
                    int ir1 = stoi(tokens[2]);
                    int ir2 = stoi(tokens[3]);
                    // cout<<"h";
                    string dest = dec_to_bin(idest, 5);
                    string r1 = dec_to_bin(ir1, 5);
                    string r2 = dec_to_bin(ir2, 5);
                    string code = r_func7[tokens[0]] + r2 + r1 + r_func3[tokens[0]] + dest + r_opcode[tokens[0]];
                    code = bin_to_hex(code);
                    cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x" << code << endl;
                }

                // I-type
                else if (i_func3.find(tokens[0]) != i_func3.end())
                {
                    if(tokens[0]=="lb" ||tokens[0]=="lw" ||tokens[0]=="ld" ||tokens[0]=="lh")
                        offset_separate(tokens);
                    tokens[1].erase(0, 1);
                    tokens[2].erase(0, 1);
                    // cout<<tokens[1]<<" "<<tokens[2]<<" "<<tokens[3]<<endl;
                    int idest = stoi(tokens[1]);
                    int ir1 = stoi(tokens[2]);
                    // cout<<"Here1";
                    string dest = dec_to_bin(idest, 5);
                    string r1 = dec_to_bin(ir1, 5);
                    int k = 0;
                    bool neg = false;
                    string imd;
                    string upper_lim = "011111111111";
                    string lower_lim = "100000000000";
                    if (tokens[3][k] == '-')
                    {
                        neg = true;
                        k++;
                    }
                    if (tokens[3].substr(k, 2) == "0x")
                    {
                        tokens[3].erase(0, 2 + k);
                        int imm = hex_to_dec(tokens[3]);
                        if (neg)
                            imd = dec_to_bin(pow(2, 12) - abs(imm), 12);
                        else
                            imd = dec_to_bin(hex_to_dec(tokens[3]), 12);
                        // cout<<"Here2";
                    }
                    else if (tokens[3].substr(k, 2) == "0b")
                    {
                        tokens[3].erase(0, 2 + k);
                        while (tokens[3].size() < 12)
                        {
                            tokens[3] = "0" + tokens[3];
                        }
                        imd = tokens[3];
                    }
                    else
                    {
                        int imm = stoi(tokens[3]);
                        // cout<<pow(2,12)-abs(imm)<<endl;
                        if (neg)
                            imd = dec_to_bin(pow(2, 12) - abs(imm), 12);
                        else
                            imd = dec_to_bin(imm, 12);
                        // cout<<imd<<endl;
                    }
                    cout<<imd<<endl;
                    if ((imd > upper_lim && !neg) || (imd < lower_lim && neg) || imd.size() > 12)
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Immediate value out of bounds" << endl;
                    else
                    {
                        string code = imd + r1 + i_func3[tokens[0]] + dest + i_opcode[tokens[0]];
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x" << bin_to_hex(code) << endl;
                    }
                }

                // 31 instructions code ends
                text_address += 4;
            }
            else
            { // data-mode
                if (tokens[0] == ".text")
                {
                    mode = 0;
                    continue;
                }
                // data begins

                // data ends
            }
        }
    }
    return 0;
}