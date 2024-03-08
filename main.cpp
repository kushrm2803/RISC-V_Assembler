#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include "opcodes.cpp"
#include "utilities.cpp"
using namespace std;
#define all(a) a.begin(), a.end()

map<string, int> mp;
int text_address;
int data_address;
int mode; // 0 -> .text && 1 -> .data

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
        //for generating all address of instructions
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty()) continue;
            if (mode == 0)
            { // text-mode
                if (tokens[0] == ".data")
                {
                    mode = 1;
                    continue;
                }
                if(tokens[0] == ".text") continue;
                text_address += 4;
            }
            else
            {
                if (tokens[0] == ".text")
                {
                    mode = 0;
                    continue;
                }
                if(tokens[0] == ".data") continue;
            }
        }
        fin.close();
        fin.open(in);
        text_address=0;

        //main code starts here
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
                if(tokens[0] == ".text") continue;
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
                    if (tokens[0] == "lb" || tokens[0] == "lw" || tokens[0] == "ld" || tokens[0] == "lh")
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
                    bool error = false;
                    string imd;
                    string upper_lim = "011111111111";
                    string lower_lim = "100000000000";
                    set<char> valid_hex = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '-'};
                    set<char> valid_dig = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
                    set<char> valid_bin = {'0', '1'};
                    if (tokens[3][k] == '-')
                    {
                        neg = true;
                        k++;
                    }
                    if (tokens[3].substr(k, 2) == "0x")
                    {
                        tokens[3].erase(0, 2 + k);
                        for (auto i : tokens[3])
                            if (valid_hex.find(i) == valid_hex.end())
                                error = true;
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
                        for (auto i : imd)
                            if (valid_bin.find(i) == valid_bin.end())
                                error = true;
                    }
                    else
                    {
                        for (auto i : tokens[3])
                            if (valid_dig.find(i) == valid_dig.end())
                                error = true;
                        int imm = stoi(tokens[3]);
                        // cout<<pow(2,12)-abs(imm)<<endl;
                        if (neg)
                            imd = dec_to_bin(pow(2, 12) - abs(imm), 12);
                        else
                            imd = dec_to_bin(imm, 12);
                        // cout<<imd<<endl;
                    }
                    // cout << imd << endl;
                    if (((imd > upper_lim && !neg) || (imd < lower_lim && neg) || imd.size() > 12) && !error)
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Immediate value out of bounds" << endl;
                    else if (error)
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Wrong inputs" << endl;
                    else
                    {
                        string code = imd + r1 + i_func3[tokens[0]] + dest + i_opcode[tokens[0]];
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 0)) << " 0x" << bin_to_hex(code) << endl;
                    }
                }
                //S-type
                else if(s_func3.find(tokens[0]) != s_func3.end()){
                    offset_separate(tokens);
                    tokens[1].erase(0, 1);
                    tokens[2].erase(0, 1);

                   // cout<<tokens[1]<<" "<<tokens[2]<<" "<<tokens[3]<<endl;
                    
                    int rs2 = stoi(tokens[1]);
                    int rs1 = stoi(tokens[2]);

                    string fr2 = dec_to_bin(rs2, 5);
                    string fr1 = dec_to_bin(rs1, 5);
                    
                    int k = 0;
                    bool neg = false;
                    bool error = false;
                    string imd;
                    string upper_lim = "011111111111";
                    string lower_lim = "100000000000";

                    set<char> valid_hex = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '-'};
                    set<char> valid_dig = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
                    set<char> valid_bin = {'0', '1'};

                    if (tokens[3][k] == '-')
                    {
                        neg = true;
                        k++;
                    }
                    if (tokens[3].substr(k, 2) == "0x")
                    {
                        tokens[3].erase(0, 2 + k);

                        for (auto i : tokens[3])
                            if (valid_hex.find(i) == valid_hex.end())
                                error = true;

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

                        for (auto i : imd)
                            if (valid_bin.find(i) == valid_bin.end())
                                error = true;

                    }
                    else
                    {   
                        for (auto i : tokens[3])
                            if (valid_dig.find(i) == valid_dig.end())
                                error = true;

                        int imm = stoi(tokens[3]);
                        // cout<<pow(2,12)-abs(imm)<<endl;
                        if (neg)
                            imd = dec_to_bin(pow(2, 12) - abs(imm), 12);
                        else
                            imd = dec_to_bin(imm, 12);
                        // cout<<imd<<endl;
                    }
                    //cout << imd << endl;

                    string i1 = imd.substr(0,7);
                    string i2 = imd.substr(7,5);

                    //cout<< i1 << endl;
                    //cout<< i2 << endl;

                    if ((imd > upper_lim && !neg) || (imd < lower_lim && neg) || imd.size() > 12)
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Immediate value out of bounds" << endl;
                    else if (error)
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Wrong inputs" << endl;
                    else
                    {
                        string code = i1 + fr2 + fr1 + s_func3[tokens[0]] + i2 + s_opcode[tokens[0]];
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x" << bin_to_hex(code) << endl;
                    }
                }

                // U-type
                else if (u_opcode.find(tokens[0]) != u_opcode.end())
                {
                    tokens[1].erase(0, 1);
                    int idest = stoi(tokens[1]);
                    string dest = dec_to_bin(idest, 5);
                    string imd;
                    string upper_lim = "11111111111111111111";
                    string lower_lim = "00000000000000000000";
                    bool neg = false;
                    bool error = false;
                    set<char> valid_hex = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '-'};
                    set<char> valid_dig = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
                    set<char> valid_bin = {'0', '1'};
                    if (tokens[2][0] == '-'){
                        neg = true;
                        tokens[2].erase(0,1);
                    }
                    if (tokens[2].substr(0, 2) == "0x")
                    {
                        tokens[2].erase(0, 2);
                        for (auto i : tokens[2])
                            if (valid_hex.find(i) == valid_hex.end())
                                error = true;
                        int imm = hex_to_dec(tokens[2]);
                        imd = dec_to_bin(hex_to_dec(tokens[2]), 20);
                    }
                    else if (tokens[2].substr(0, 2) == "0b")
                    {
                        tokens[2].erase(0, 2);
                        while (tokens[2].size() < 12)
                        {
                            tokens[2] = "0" + tokens[2];
                        }
                        imd = tokens[2];
                        for (auto i : imd)
                            if (valid_bin.find(i) == valid_bin.end())
                                error = true;
                    }
                    else
                    {
                        for (auto i : tokens[2])
                            if (valid_dig.find(i) == valid_dig.end())
                                error = true;
                        int imm = stoi(tokens[2]);
                        imd = dec_to_bin(imm, 20);
                    }
                    if ((imd > upper_lim || imd < lower_lim || imd.size() > 20 || neg) && !error)
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Immediate value out of bounds" << endl;
                    else if (error)
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Wrong inputs" << endl;
                    else
                    {
                        string code = imd + dest + u_opcode[tokens[0]];
                        cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x" << bin_to_hex(code) << endl;
                    }
                }
                
                //UJ-format // jal
                else if(tokens[0] == "jal"){
                    int imm = (mp[tokens[2]] - text_address);
                    // cout<<imm<<" ";
                    tokens[1].erase(0, 1);
                    int dest = stoi(tokens[1]); 
                    string imm1 = dec_to_bin(imm, 21);
                    string temp = imm1.substr(10, 10);
                    string temp2 = imm1.substr(1, 8);
                    // reverse(all(temp));
                    // reverse(all(temp2));
                    imm1 = imm1[0] + temp + imm1[9] + temp2;
                    // reverse(all(imm1));
                    string code = bin_to_hex(imm1 + dec_to_bin(dest, 5) + "1101111");
                    cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x";
                    cout<<code<<endl;
                }
                // SB format
                else if(sb_func3.find(tokens[0]) != sb_func3.end()){
                    tokens[1].erase(0, 1);
                    tokens[2].erase(0, 1);
                    int ir1 = stoi(tokens[1]);
                    int ir2 = stoi(tokens[2]);
                    string r1 = dec_to_bin(ir1, 5);
                    string r2 = dec_to_bin(ir2, 5);
                    int imm = (mp[tokens[3]] - text_address);
                    string imm1 = dec_to_bin(imm, 13);
                    string code = imm1[0] + imm1.substr(2,  6) + r2 + r1 + sb_func3[tokens[0]] + imm1.substr(8, 4) + imm1[1] + "1100011";
                    code = bin_to_hex(code);
                    cout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x";
                    cout<<code<<endl;
                }
                else{
                    cout<<"command not recognized"<<endl;
                    return 0;
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
                else if(tokens[0] == ".data") continue;
                // data begins
                cout<<tokens[0]<<" "<<tokens[1]<<" "<<tokens[2]<<" "<<tokens[4]<<endl;
                if(tokens[2]==".word" || tokens[2]==".half" || tokens[2]==".dword" || tokens[2]==".byte" || tokens[2]==".asciiz"){
                    
                }
                // data ends
            }
        }
    }
    return 0;
}