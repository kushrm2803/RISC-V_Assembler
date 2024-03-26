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

    int Taken_count = 0;
    int Not_taken_count = 0;
    for (int i = 1; i < argc; i++)
    {
        ifstream fin;
        ofstream fout;
        fin.open(argv[i]);
        string instruct;
        // Generate addresses of instructions
        string next_pc;
        string branch_pc;
        map<string, int> history_table; // pc->cur state of instruction
        map<string, int> oneBitBuffer;
        map<string, int> twoBitBuffer;
        int correctPrediction = 0;
        int wrongPrediction = 0;
        int correctPrediction1 = 0;
        int wrongPrediction1 = 0;
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty() || tokens[0].substr(0,2)!="0x")
                continue;
            if (branch_pc.size() != 0)
            {
                if (actualBranch(tokens[0], branch_pc)){
                    // cout<<branch_pc<<" "<<"Taken"<<endl;
                    history_table[branch_pc] = 1;
                    branch_pc.clear();
                    Taken_count++;
                }
                else{
                    // cout<<branch_pc<<" "<<"NOTTaken"<<endl;
                    history_table[branch_pc] = 0;
                    branch_pc.clear();
                    Not_taken_count++;

                }
            }
            if (tokens[2][0] == 'b')
            {
                branch_pc = tokens[0];
                // continue;
                // cout<<tokens[2]<<endl;
                // if (prev_pc.size() != 0)
                //     if (actualBranch(prev_pc, tokens[0]))
                //         history_table[tokens[0]] = 1;
                //     else
                //         history_table[tokens[0]] = 0;
                // cout << "Branch Target Buffer of 1-bit:" << endl;
                if (oneBitBranchPredictor(oneBitBuffer, history_table, tokens))
                    correctPrediction++;
                else
                    wrongPrediction++;
                if (twoBitBuffer.find(tokens[0]) == twoBitBuffer.end())
                    twoBitBuffer[tokens[0]] = 1; // two bit branch predictor should start from not taken
                // // cout << "Branch Target Buffer of 2-bit:" << endl;
                if (twoBitBranchPredictor(twoBitBuffer, history_table, tokens))
                    correctPrediction1++;
                else
                    wrongPrediction1++;
                // if (actualBranch(prev_pc, tokens[0]))
                // {
                //     // cout << tokens[0] << "  Taken" << endl;
                //     Taken_count++;
                // }
                // else
                // {
                //     // cout << tokens[0] << "  Not Taken" << endl;
                //     Not_taken_count++;
                // }
            }
            // prev_pc = tokens[0];
        }
        float acc_1bit = Accuracy_cal(correctPrediction, wrongPrediction);
        cout << "Total Prediction of 1-bit Branch Predictor -> " << acc_1bit << "%" << endl;
        float acc_2bit = Accuracy_cal (correctPrediction1, wrongPrediction1);
        cout << "Total Prediction of 2-bit Branch Predictor -> " << acc_2bit << "%" << endl;
        float Accuracy = Accuracy_cal(Taken_count, Not_taken_count);
        cout << "accuracy of branch predictor By Always Taken -> " << Accuracy << "%" << endl;
        float Acc = Accuracy_cal(Not_taken_count,Taken_count);
        cout << "accuracy of branch predictor By Always Not Taken -> " << Acc << "%" << endl;
    }

    return 0;
}