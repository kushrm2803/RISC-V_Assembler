#include <bits/stdc++.h>
using namespace std;

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

string dec_to_bin(int num, int n)
{
    string ans = "";
    while (num)
    {
        if (num % 2)
            ans += '1';
        else
            ans += '0';
        num /= 2;
    }
    reverse(ans.begin(), ans.end());
    while (ans.size() < n)
    {
        ans = "0" + ans;
    }
    return ans;
}

string dec_to_hex(int num){
    string ans="";
    map<int,char> hex_dict={
        {0,'0'},{1,'1'},{2,'2'},{3,'3'},{4,'4'},{5,'5'},{6,'6'},{7,'7'},{8,'8'},{9,'9'},{10,'A'},{11,'B'},{12,'C'},{13,'D'},{14,'E'},{15,'F'}
    };
    while(num){
        ans+=hex_dict[num%16];
        num/=16;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

string bin_to_hex(string binary)
{
    binary = string(binary.length() % 4 ? 4 - binary.length() % 4 : 0, '0') + binary;
    map<string, char> hex_dict = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'}, {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};
    string hexadecimal;
    for (size_t i = 0; i < binary.length(); i += 4)
    {
        string group = binary.substr(i, 4);
        hexadecimal += hex_dict[group];
    }
    return hexadecimal;
}

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
    // cout<<num;
    return num;
}

void offset_separate(vector<string> &tokens)
{
    // ld x12 4(x5)->tokens[0]=ld tokens[1]=x12 tokens[2]=x5 tokens[3]=4;
    int i = 0;
    string off = "";
    while (tokens[2][i] != '(')
    {
        off += tokens[2][i];
        i++;
    }
    i++;
    string src2 = "";
    while (tokens[2][i] != ')')
    {
        src2 += tokens[2][i];
        i++;
    }
    tokens[2] = src2;
    tokens.push_back(off);
}