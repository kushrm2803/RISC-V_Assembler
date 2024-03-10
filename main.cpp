#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include "codes.cpp"
#include "utilities.cpp"
using namespace std;
#define all(a) a.begin(), a.end() //

map<string, int> mp;
int text_address;
int data_address;
int mode; // 0 -> .text && 1 -> .data

// Function to tokenize the instruction string
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
            {
                // Handle comments
                flag = true;
                break;
            }
            else if (instruct[j] == ':' && mode == 0)
            {
                // Handle labeling in text-mode
                mp[word] = text_address;
                word.erase();
                j++;
                break;
            }
            else if(instruct[j] == ':' && mode == 1){
                if(word.length()>0){
                    token.push_back(word); 
                    word = "";
                }
                token.push_back(":");
                j++;
                continue;
            }
            word += instruct[j];
            j++;
        }
        if (word.length() > 0)
            token.push_back(word);
        if (flag)
            break; // Ignore comments
    }
    return token;
}

int main(int argc, char *argv[])
{
    defineAllCodes(); // Define all instruction opcodes
    mode = 0;         // Initial mode is text
    text_address = 0;
    // Loop through command line arguments
    for (int i = 1; i <= argc; i++)
    {
        string in = chartostring(argv[i]); // Input file name
        string out = outputfilename(in);   // Output file name
        string datadata;
        ifstream fin;
        ofstream fout;
        fin.open(in);
        fout.open(out);
        string instruct;
        // Generate addresses of instructions
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty())
                continue;
            if (mode == 0)
            {
                // Text-mode
                if (tokens[0] == ".data")
                {
                    mode = 1;
                    continue;
                }
                if (tokens[0] == ".text")
                    continue;
                text_address += 4;
            }
            else
            {
                // Data-mode
                if (tokens[0] == ".text")
                {
                    mode = 0;
                    continue;
                }
                if (tokens[0] == ".data")
                    continue;
            }
        }
        fin.close();
        // Reset addresses
        fin.open(in);
        text_address = 0;
        data_address = 268435456;
        // Generate machine code
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty())
                continue;
            if (mode == 0)
            {
                // Text-mode
                if (tokens[0] == ".data")
                {
                    mode = 1;
                    continue;
                }
                if (tokens[0] == ".text")
                    continue;
                // 31 Instructions code begins
                // R-type instructions
                if (r_func7.find(tokens[0]) != r_func7.end())
                {
                    // Instruction check according to pattern of R instruction
                    if (tokens.size() > 4 || tokens[1].substr(0, 1) != "x" || tokens[2].substr(0, 1) != "x" || tokens[3].substr(0, 1) != "x")
                    {
                        fout << "Error" << endl;
                    }
                    else
                    {
                        // Extract register and immediate values
                        tokens[1].erase(0, 1);
                        tokens[2].erase(0, 1);
                        tokens[3].erase(0, 1);
                        int idest = stoi(tokens[1]);
                        int ir1 = stoi(tokens[2]);
                        int ir2 = stoi(tokens[3]);
                        string dest = dec_to_bin(idest, 5);
                        string r1 = dec_to_bin(ir1, 5);
                        string r2 = dec_to_bin(ir2, 5);
                        string code = r_func7[tokens[0]] + r2 + r1 + r_func3[tokens[0]] + dest + r_opcode[tokens[0]];
                        code = bin_to_hex(code);
                        fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x" << code << endl;
                    }
                }
                // I-type instructions
                else if (i_func3.find(tokens[0]) != i_func3.end())
                {
                    if (tokens[0] == "lb" || tokens[0] == "lw" || tokens[0] == "ld" || tokens[0] == "lh")
                        offset_separate(tokens); // Separate offset from base register
                    // Instruction check according to pattern of I instruction
                    if (tokens.size() > 4 || tokens[1].substr(0, 1) != "x" || tokens[2].substr(0, 1) != "x" || tokens[3].substr(0, 1) == "x")
                    {
                        fout << "Error" << endl;
                    }
                    else
                    {
                        // Extract register and immediate values
                        tokens[1].erase(0, 1);
                        tokens[2].erase(0, 1);
                        int idest = stoi(tokens[1]);
                        int ir1 = stoi(tokens[2]);
                        string dest = dec_to_bin(idest, 5);
                        string r1 = dec_to_bin(ir1, 5);
                        int k = 0;
                        bool neg = false;
                        bool error = false;
                        // Extract immediate value
                        string imd;
                        string upper_lim = "011111111111";
                        string lower_lim = "100000000000";
                        if (tokens[3][k] == '-')
                        {
                            neg = true;
                            k++;
                        }
                        // Handle Hexadecimal format of immediate values
                        if (tokens[3].substr(k, 2) == "0x")
                        {
                            tokens[3].erase(0, 2 + k);
                            error = valid_check(tokens[3], 16);
                            int imm = hex_to_dec(tokens[3]);
                            if (neg)
                                imd = dec_to_bin(pow(2, 12) - abs(imm), 12);
                            else
                                imd = dec_to_bin(hex_to_dec(tokens[3]), 12);
                        }
                        // Handle Binary format of immediate values
                        else if (tokens[3].substr(k, 2) == "0b")
                        {
                            tokens[3].erase(0, 2 + k);
                            while (tokens[3].size() < 12)
                            {
                                tokens[3] = "0" + tokens[3];
                            }
                            imd = tokens[3];
                            error = valid_check(imd, 2);
                        }
                        // Handle Decimal format of immediate values
                        else
                        {
                            error = valid_check(tokens[3], 10);
                            int imm = stoi(tokens[3]);
                            if (neg)
                                imd = dec_to_bin(pow(2, 12) - abs(imm), 12);
                            else
                                imd = dec_to_bin(imm, 12);
                        }
                        if (((imd > upper_lim && !neg) || (imd < lower_lim && neg) || imd.size() > 12) && !error)
                            fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Immediate value out of bounds" << endl;
                        else if (error)
                            fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Wrong inputs" << endl;
                        else
                        {
                            string code = imd + r1 + i_func3[tokens[0]] + dest + i_opcode[tokens[0]];
                            fout << "0x" << bin_to_hex(dec_to_bin(text_address, 0)) << " 0x" << bin_to_hex(code) << endl;
                        }
                    }
                }
                // S-type instructions
                else if (s_func3.find(tokens[0]) != s_func3.end())
                {
                    offset_separate(tokens); // Separate offset from base register
                    // Instruction check according to pattern of S instruction
                    if (tokens.size() > 4 || tokens[1].substr(0, 1) != "x" || tokens[2].substr(0, 1) != "x" || tokens[3].substr(0, 1) == "x")
                    {
                        fout << "Error" << endl;
                    }
                    else
                    {
                        // Extract register and offset values
                        tokens[1].erase(0, 1);
                        tokens[2].erase(0, 1);
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
                        if (tokens[3][k] == '-')
                        {
                            neg = true;
                            k++;
                        }
                        // Handle Hexadecimal format of offset values
                        if (tokens[3].substr(k, 2) == "0x")
                        {
                            tokens[3].erase(0, 2 + k);
                            error = valid_check(tokens[3], 16);
                            int imm = hex_to_dec(tokens[3]);
                            if (neg)
                                imd = dec_to_bin(pow(2, 12) - abs(imm), 12);
                            else
                                imd = dec_to_bin(hex_to_dec(tokens[3]), 12);
                        }
                        // Handle Binary format of offset values
                        else if (tokens[3].substr(k, 2) == "0b")
                        {
                            tokens[3].erase(0, 2 + k);
                            while (tokens[3].size() < 12)
                            {
                                tokens[3] = "0" + tokens[3];
                            }
                            imd = tokens[3];
                            error = valid_check(imd, 2);
                        }
                        // Handle Decimal format of offset values
                        else
                        {
                            error = valid_check(tokens[3], 10);
                            int imm = stoi(tokens[3]);
                            if (neg)
                                imd = dec_to_bin(pow(2, 12) - abs(imm), 12);
                            else
                                imd = dec_to_bin(imm, 12);
                        }
                        string i1 = imd.substr(0, 7);
                        string i2 = imd.substr(7, 5);
                        if ((imd > upper_lim && !neg) || (imd < lower_lim && neg) || imd.size() > 12)
                            fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Immediate value out of bounds" << endl;
                        else if (error)
                            fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Wrong inputs" << endl;
                        else
                        {
                            string code = i1 + fr2 + fr1 + s_func3[tokens[0]] + i2 + s_opcode[tokens[0]];
                            fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x" << bin_to_hex(code) << endl;
                        }
                    }
                }

                // U-type instructions
                else if (u_opcode.find(tokens[0]) != u_opcode.end())
                {
                    // Instruction check according to pattern of U instruction
                    if (tokens.size() > 3 || tokens[1].substr(0, 1) != "x" || tokens[2].substr(0, 1) == "x")
                    {
                        fout << "Error" << endl;
                    }
                    else
                    {
                        tokens[1].erase(0, 1);
                        int idest = stoi(tokens[1]);
                        string dest = dec_to_bin(idest, 5);
                        string imd;
                        string upper_lim = "11111111111111111111";
                        string lower_lim = "00000000000000000000";
                        bool neg = false;
                        bool error = false;
                        if (tokens[2][0] == '-')
                        {
                            neg = true;
                            tokens[2].erase(0, 1);
                        }
                        // Handle Hexadecimal format of immediate values
                        if (tokens[2].substr(0, 2) == "0x")
                        {
                            tokens[2].erase(0, 2);
                            error = valid_check(tokens[2], 16);
                            int imm = hex_to_dec(tokens[2]);
                            imd = dec_to_bin(hex_to_dec(tokens[2]), 20);
                        }
                        // Handle Binary format of immediate values
                        else if (tokens[2].substr(0, 2) == "0b")
                        {
                            tokens[2].erase(0, 2);
                            while (tokens[2].size() < 12)
                            {
                                tokens[2] = "0" + tokens[2];
                            }
                            imd = tokens[2];
                            error = valid_check(imd, 2);
                        }
                        // Handle Decimal format of immediate values
                        else
                        {
                            error = valid_check(tokens[2], 10);
                            int imm = stoi(tokens[2]);
                            imd = dec_to_bin(imm, 20);
                        }
                        if ((imd > upper_lim || imd < lower_lim || imd.size() > 20 || neg) && !error)
                            fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Immediate value out of bounds" << endl;
                        else if (error)
                            fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " Wrong inputs" << endl;
                        else
                        {
                            string code = imd + dest + u_opcode[tokens[0]];
                            fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x" << bin_to_hex(code) << endl;
                        }
                    }
                }

                // UJ-type instructions
                else if (tokens[0] == "jal")
                {
                    // Instruction check according to pattern of UJ instruction
                    if (tokens.size() > 3 || tokens[1].substr(0, 1) != "x")
                    {
                        fout << "Error" << endl;
                    }
                    else
                    {
                        // Calculate the immediate value for jumping
                        int imm = (mp[tokens[2]] - text_address);
                        tokens[1].erase(0, 1);
                        int dest = stoi(tokens[1]);
                        // Convert immediate value and destination register to binary
                        string imm1 = dec_to_bin(imm, 21);
                        string temp = imm1.substr(10, 10);
                        string temp2 = imm1.substr(1, 8);
                        imm1 = imm1[0] + temp + imm1[9] + temp2;
                        string code = bin_to_hex(imm1 + dec_to_bin(dest, 5) + "1101111");
                        fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x";
                        fout << code << endl;
                    }
                }
                // SB-type instructions
                else if (sb_func3.find(tokens[0]) != sb_func3.end())
                {
                    // Instruction check according to pattern of SB instruction
                    if (tokens.size() > 4 || tokens[1].substr(0, 1) != "x" || tokens[2].substr(0, 1) != "x")
                    {
                        fout << "Error" << endl;
                    }
                    else
                    {
                        // Extract register values
                        tokens[1].erase(0, 1);
                        tokens[2].erase(0, 1);
                        int ir1 = stoi(tokens[1]);
                        int ir2 = stoi(tokens[2]);
                        string r1 = dec_to_bin(ir1, 5);
                        string r2 = dec_to_bin(ir2, 5);
                        // Calculate the immediate value for branching
                        int imm = (mp[tokens[3]] - text_address);
                        string imm1 = dec_to_bin(imm, 13);
                        string code = imm1[0] + imm1.substr(2, 6) + r2 + r1 + sb_func3[tokens[0]] + imm1.substr(8, 4) + imm1[1] + "1100011";
                        code = bin_to_hex(code);
                        fout << "0x" << bin_to_hex(dec_to_bin(text_address, 1)) << " 0x";
                        fout << code << endl;
                    }
                }
                else
                {
                    fout << "command not recognized" << endl;
                    return 0;
                }

                // 31 Instructions code ends
                text_address += 4; // Increment text address
            }
            else
            {
                // Data-mode
                if (tokens[0] == ".text")
                {
                    mode = 0;
                    continue;
                }
                else if (tokens[0] == ".data")
                    continue;
                // data begins
                if (tokens[2] == ".word" || tokens[2] == ".half" || tokens[2] == ".dword" || tokens[2] == ".byte")
                {
                    // Loop through each data value
                    int i = 3;
                    while (i<tokens.size())
                    {

                        int k = 0;
                        bool neg = false;
                        bool error = false;
                        map<string, int> data_size = {{".dword", 16}, {".byte", 2}, {".word", 8}, {".half", 4}};
                        // Initialize an empty vector to hold memory blocks
                        vector<string> memory_block;
                        if (tokens[i][k] == '-')
                        {
                            neg = true;
                            k++;
                        }
                        string data = "";
                        // Determine the format of the input data and convert it to hexadecimal
                        if (tokens[i].substr(k, 2) == "0x")
                        {
                            tokens[i].erase(0, 2 + k);

                            error = valid_check(tokens[i], 16);
                            data = tokens[i];
                            if (data.size() > data_size[tokens[2]])
                                error = true;
                            while (data.size() < data_size[tokens[2]])
                                data = "0" + data;
                        }
                        else if (tokens[i].substr(k, 2) == "0b")
                        {
                            tokens[i].erase(0, 2 + k);
                            error = valid_check(tokens[i], 2);
                            data = tokens[i];
                            data = bin_to_hex(data);
                            if (data.size() > data_size[tokens[2]])
                                error = true;
                            while (data.size() < data_size[tokens[2]])
                                data = "0" + data;
                        }
                        else
                        {
                            error = valid_check(tokens[i], 10);
                            data = dec_to_hex(stoi(tokens[i]));
                            if (data.size() > data_size[tokens[2]])
                                error = true;
                            while (data.size() < data_size[tokens[2]])
                                data = "0" + data;
                        }
                        if (error)
                        {
                            datadata += "0x" + bin_to_hex(dec_to_bin(data_address, 8)) + " Wrong inputs\n";
                        }
                        else
                        {
                            // Write memory values in hexadecimal format
                            int j = data_size[tokens[2]] - 2;
                            while (j >= 0)
                            {
                                datadata += "0x" + bin_to_hex(dec_to_bin(data_address, 8)) + " " + data.substr(j, 2) + "\n";
                                j -= 2;
                                data_address++;
                            }
                        }
                        i++;
                    }
                }
                // Processing null-terminated ASCII strings
                else if (tokens[2] == ".asciiz")
                {
                    int i = 3;
                    string data = "";
                    int asciiz_len = 0;
                    // Concatenate each character into a string
                    while (i < tokens.size())
                    {
                        data += tokens[i];
                        data += " ";
                        i++;
                    }
                    // Remove leading and trailing quotes from the string
                    data.erase(0, 1);
                    data.pop_back();
                    data.pop_back();
                    asciiz_len = data.size();
                    // Convert each character to hexadecimal and write to the output file
                    for (char c : data)
                    {
                        datadata += "0x" + bin_to_hex(dec_to_bin(data_address, 8)) + " " + bin_to_hex(dec_to_bin((int)c, 0)) + "\n";
                        data_address += 1;
                    }
                    datadata += "0x" + bin_to_hex(dec_to_bin(data_address, 8)) + " " + "00" + "\n";
                    data_address += 1; // for terminating zero
                }
                // Data ends
            }
        }
        fout << "\n\n------------------------DATA--------------------------\n"
             << datadata;
        fin.close();
        fout.close();
    }
    return 0;
}