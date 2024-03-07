#include<iostream>
#include<vector>
#include<fstream>
#include<map>
#include<algorithm>
#include "opcodes.cpp"
using namespace std;

map<string, int> mp;
int text_address;
int data_address;
int mode; //0 -> .text && 1 -> .data

string chartostring(char* ch){
    int i = 0;
    string ans;
    while(ch[i]!='\0'){
        ans+=ch[i];
        i++;
    }
    return ans;
}
string outputfilename(string in){
    in.erase(in.size() - 3);
    in += "mc";
    return in;
}
vector<string> instructionToToken(string instruct){
    vector<string> token;
    int len = instruct.size();
    bool flag = false;
    int j  = 0;
    while(j<len){
        string word;
        while(j<len && (instruct[j] == ' ' || instruct[j]== ',')) j++;
        while(j<len && instruct[j] != ' ' && instruct[j] != ','){
            if(instruct[j]=='#'){   //comments case
                flag = true;
                break;
            }
            if(instruct[j]==':' && mode == 0){   //labeling in case of text-mode
                mp[word] = text_address;
                word.erase();
                j++;
                break;
            }
            word += instruct[j];
            j++;
        }
        if(word.length()>0) token.push_back(word);
        if(flag) break; // the next lines are comment 
    }
    return token;
}

int main(int argc, char* argv[]){
    defineAllOpcodes();
    mode = 0;//intial mode is text
    text_address = 0;
    for(int i=1;i<=argc;i++){
        string in = chartostring(argv[i]);
        string out = outputfilename(in);
        
        ifstream fin;
        fin.open(in);
        string instruct;
        while(getline(fin, instruct)){
            vector<string> tokens = instructionToToken(instruct);
            if(tokens.empty())continue;
            if(mode == 0){ // text-mode
                if(tokens[0]==".data"){
                    mode = 1;
                    continue;
                }
                //31 instructions code begins

                    //R-type
                    if(r_func7.find(tokens[0]) != r_func7.end()){
                        tokens[1].erase(0, 1);
                        tokens[2].erase(0, 1);
                        tokens[3].erase(0, 1);
                        int idest = stoi(tokens[1]);
                        int ir1 = stoi(tokens[2]);
                        int ir2 = stoi(tokens[3]);
                        //cout<<"h";
                        string dest = dec_to_bin(idest, 5);
                        string r1 = dec_to_bin(ir1, 5);
                        string r2 = dec_to_bin(ir2, 5);
                        string code = r_func7[tokens[0]] + r2 + r1 + r_func3[tokens[0]] + dest + "0110011";
                        code = bin_to_hex(code);
                        cout<<"0x"<<bin_to_hex(dec_to_bin(text_address, 32))<<" 0x"<<code<<endl;
                    }
                    // I-type
                    
                    
                //31 instructions code ends
                text_address+=4;
            }
            else{   //data-mode
                if(tokens[0] == ".text"){
                    mode = 0;
                    continue;
                }
                //data begins

                //data ends
            }
        }
    }
    return 0;
}