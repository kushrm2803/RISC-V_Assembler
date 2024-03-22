#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include "utilities.cpp"
using namespace std;

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        ifstream fin;
        ofstream fout;
        fin.open(argv[i]);
        string instruct;
        // Generate addresses of instructions
        string prev_pc;
        map<string,int>history_table; //pc->cur state of instruction
        map<string,int>oneBitBuffer;
        map<string,int>twoBitBuffer;
        int correctPrediction=0;
        int wrongPrediction=0;
        int correctPrediction1=0;
        int wrongPrediction1=0;
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty())
                continue;
            if ((tokens[2][0] == 'b' || tokens[2][0] == 'j') && tokens[2] != "jalr")
            {
                if (prev_pc.size() != 0)
                    if (actualBranch(prev_pc, tokens[0]))
                        history_table[tokens[0]]=1;
                    else history_table[tokens[0]]=0;
                cout<<"Branch Target Buffer of 1-bit:"<<endl;                    
                if(oneBitBranchPredictor(oneBitBuffer,history_table,tokens))correctPrediction++;
                else wrongPrediction++;
                cout<<"Branch Target Buffer of 2-bit:"<<endl;      
                if(twoBitBranchPredictor(twoBitBuffer,history_table,tokens))correctPrediction1++;
                else wrongPrediction1++;
                prev_pc = tokens[0];
            }
        }
        cout<<"Total Prediction of 1-bit Branch Predictor ->" << ((double)correctPrediction/(double)(correctPrediction+wrongPrediction))*100<<"%"<<endl;
        cout<<"Total Prediction of 2-bit Branch Predictor ->" << ((double)correctPrediction1/(double)(correctPrediction1+wrongPrediction1))*100<<"%"<<endl;
    }
    return 0;
}