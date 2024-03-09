#include <map>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

map<string, string> r_func7;
map<string, string> r_func3;
map<string, string> r_opcode;
map<string, string> i_opcode;
map<string, string> i_func3;
map<string, string> s_opcode;
map<string, string> s_func3;
map<string, string> sb_func3;
map<string, string> u_opcode;
map<string, string> uj_opcode;

// Function to define all necessary codes
void defineAllCodes()
{
    r_opcode["add"] = "0110011";
    r_opcode["and"] = "0110011";
    r_opcode["or"] = "0110011";
    r_opcode["sll"] = "0110011";
    r_opcode["slt"] = "0110011";
    r_opcode["sra"] = "0110011";
    r_opcode["srl"] = "0110011";
    r_opcode["sub"] = "0110011";
    r_opcode["xor"] = "0110011";
    r_opcode["mul"] = "0110011";
    r_opcode["div"] = "0110011";
    r_opcode["rem"] = "0110011";

    r_func7["add"] = "0000000";
    r_func7["and"] = "0000000";
    r_func7["or"] = "0000000";
    r_func7["sll"] = "0000000";
    r_func7["slt"] = "0000000";
    r_func7["sra"] = "0100000";
    r_func7["srl"] = "0000000";
    r_func7["sub"] = "0100000";
    r_func7["xor"] = "";
    r_func7["mul"] = "";
    r_func7["div"] = "";
    r_func7["rem"] = "";

    r_func3["add"] = "000";
    r_func3["and"] = "111";
    r_func3["or"] = "000";
    r_func3["sll"] = "001";
    r_func3["slt"] = "010";
    r_func3["sra"] = "101";
    r_func3["srl"] = "101";
    r_func3["sub"] = "000";
    r_func3["xor"] = "";
    r_func3["mul"] = "";
    r_func3["div"] = "";
    r_func3["rem"] = "";

    i_opcode["addi"] = "0010011";
    i_opcode["andi"] = "0010011";
    i_opcode["ori"] = "0010011";
    i_opcode["lb"] = "0000011";
    i_opcode["ld"] = "0000011";
    i_opcode["lh"] = "0000011";
    i_opcode["lw"] = "0000011";
    i_opcode["jalr"] = "1100111";

    i_func3["addi"] = "000";
    i_func3["andi"] = "111";
    i_func3["ori"] = "110";
    i_func3["lb"] = "000";
    i_func3["ld"] = "011";
    i_func3["lh"] = "001";
    i_func3["lw"] = "010";
    i_func3["jalr"] = "000";

    s_opcode["sb"] = "0100011";
    s_opcode["sh"] = "0100011";
    s_opcode["sw"] = "0100011";
    s_opcode["sd"] = "0100011";

    s_func3["sb"] = "000";
    s_func3["sh"] = "001";
    s_func3["sw"] = "010";
    s_func3["sd"] = "011";


    sb_func3["beq"] = "000";
    sb_func3["bne"] = "001";
    sb_func3["blt"] = "100";
    sb_func3["bge"] = "101";

    u_opcode["auipc"] = "0010111";
    u_opcode["lui"] = "0110111";

    uj_opcode["jal"] = "1101111";
}