#include<map>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

map<string, string> r_func7;
map<string, string> r_func3;
map<string, string> r_opcode;
map<string, string> i_opcode;
map<string, string> i_func3;
void defineAllOpcodes(){
    r_opcode["add"]="0110011";
    r_opcode["and"]="0110011";
    r_opcode["or"]="0110011";
    r_opcode["sll"]="0110011";
    r_opcode["slt"]="0110011";
    r_opcode["sra"]="0110011";
    r_opcode["srl"]="0110011";
    r_opcode["sub"]="0110011";
    r_opcode["xor"]="0110011";
    r_opcode["mul"]="0110011";
    r_opcode["div"]="0110011";
    r_opcode["rem"]="0110011";

   r_func7["add"] = "0000000";
   r_func7["and"] = "0000000";
   r_func7["or"]  = "0000000";
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
   r_func3["or"]  = "000";
   r_func3["sll"] = "001";
   r_func3["slt"] = "010"; 
   r_func3["sra"] = "101";
   r_func3["srl"] = "101";
   r_func3["sub"] = "000";
   r_func3["xor"] = "";
   r_func3["mul"] = "";
   r_func3["div"] = "";
   r_func3["rem"] = "";

   i_opcode["addi"]="0010011";
   i_opcode["andi"]="0010011";
   i_opcode["ori"]="0010011";
   i_opcode["lb"]="0000011";
   i_opcode["ld"]="0000011";
   i_opcode["lh"]="0000011";
   i_opcode["lw"]="0000011";
   i_opcode["jalr"]="1100111";

   i_func3["addi"]="000";
   i_func3["andi"]="111";
   i_func3["ori"]="110";
   i_func3["lb"]="000";
   i_func3["ld"]="011";
   i_func3["lh"]="001";
   i_func3["lw"]="010";
   i_func3["jalr"]="000";
}

string dec_to_bin(int num, int n){
    string ans = "";
    while(num){
        if(num%2) ans+='1';
        else ans+='0';
        num/=2;
    }
    reverse(ans.begin(), ans.end());
    while(ans.size() < n){
        ans = "0" + ans;
    }
    return ans;
}

string bin_to_hex(string binary) { 
    binary = string(binary.length() % 4 ? 4 - binary.length() % 4 : 0, '0') + binary; 
    map<string, char> hex_dict = { 
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, 
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, 
        {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'}, 
        {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'} 
    }; 
    string hexadecimal; 
    for (size_t i = 0; i < binary.length(); i += 4) { 
        string group = binary.substr(i, 4); 
        hexadecimal += hex_dict[group]; 
    } 
    return hexadecimal; 
}

int hex_to_dec(string hex){
    map<char,int> hex_dict={
        {'0',0},{'1',1},{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},{'A',10},{'B',11},{'C',12},{'D',13},{'E',14},{'F',15}
    };
    int num=0;
    int j=1;
    for(int i=hex.size()-1;i>=0;i--){
        num+=hex_dict[hex[i]]*j;
        j*=16;
    }
    // cout<<num;
    return num;
}

void offset_separate(vector<string> &tokens){
    //ld x12 4(x5)->tokens[0]=ld tokens[1]=x12 tokens[2]=x5 tokens[3]=4;
    int i=0;
    string off="";
    while(tokens[2][i]!='('){
        off+=tokens[2][i];
        i++;
    }
    i++;
    string src2="";
    while(tokens[2][i]!=')'){
        src2+=tokens[2][i];
        i++;
    }
    // cout<<off<<" "<<src2<<endl;
    tokens[2]=src2;
    tokens[3]=off;
}