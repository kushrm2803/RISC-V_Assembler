#include<map>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

map<string, string> r_func7;
map<string, string> r_func3;
void defineAllOpcodes(){
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

std::string bin_to_hex(std::string binary) { 
    binary = std::string(binary.length() % 4 ? 4 - binary.length() % 4 : 0, '0') + binary; 
    std::map<std::string, char> hex_dict = { 
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, 
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, 
        {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'}, 
        {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'} 
    }; 
    std::string hexadecimal; 
    for (size_t i = 0; i < binary.length(); i += 4) { 
        std::string group = binary.substr(i, 4); 
        hexadecimal += hex_dict[group]; 
    } 
    return hexadecimal; 
}