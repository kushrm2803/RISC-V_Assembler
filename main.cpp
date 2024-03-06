#include<iostream>
#include<vector>
#include<fstream>
#include<map>
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
            if(instruct[j]==':'){   //labeling 
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
    mode = 0;//intial mode is text
    text_address = 0;
    for(int i=1;i<=argc;i++){
        string in = chartostring(argv[i]);
        string out = outputfilename(in);
        
        ifstream fin;
        fin.open(in);
        string instruct;
        while(getline(fin, instruct)){
            if(mode == 0){ // text-mode
                vector<string> tokens = instructionToToken(instruct);
                if(tokens[0]==".data"){
                    mode = 1;
                    continue;
                }
                text_address+=4;
            }
            else{   //data-mode
                // new funciton will be made to tokenize our insturction or edit the same function :(
            }
        }
    }
    return 0;
}