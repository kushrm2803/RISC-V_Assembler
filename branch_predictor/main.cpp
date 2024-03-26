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
    // Loop through command line arguments
    for (int i = 1; i < argc; i++)
    {
        string out1 = outputBranchTargetBuffer(argv[i]); // Output file name
        ifstream fin;
        ofstream fout;
        fin.open(argv[i]);
        fout.open(out1);
        string instruct;
        string next_pc;
        string branch_pc;
        unordered_map<string, string> history_table; // Stores Actual history of branches
        map<string, string> oneBitPredict_table;     // 1-bit branch Predictions
        map<string, string> twoBitPredict_table;     // 2-bit branch Predictions
        map<string, int> oneBitBuffer;               // For 1-bit branch predictor States
        map<string, int> twoBitBuffer;               // For 2-bit branch predictor States
        map<string, string> branchTargetBuffer;      // Branch target buffer
        map<string, int> output;                     // Stores already printed branches
        int correctPrediction = 0;
        int wrongPrediction = 0;
        int correctPrediction1 = 0;
        int wrongPrediction1 = 0;
        cout << "Writing in BTB Output File....." << endl;
        fout << "\n-----------------------BRANCH TARGET BUFFER-----------------------\n\n";
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty() || tokens[0].substr(0, 2) != "0x")
                continue;
            // Process branch instructions obtained in previous line
            if (branch_pc.size() != 0)
            {
                // Update history and counts based on branch outcome
                if (actualBranch(tokens[0], branch_pc))
                {
                    history_table[branch_pc].push_back('1');
                    Taken_count++;
                }
                else
                {
                    history_table[branch_pc].push_back('0');
                    Not_taken_count++;
                }
                // Update predictions and prediction counts
                if (oneBitBranchPredictor(oneBitBuffer, history_table, oneBitPredict_table, branch_pc))
                    correctPrediction++;
                else
                    wrongPrediction++;
                if (twoBitBuffer.find(branch_pc) == twoBitBuffer.end())
                    twoBitBuffer[branch_pc] = 1; // Assuming two bit branch predictor starts from strongly not taken
                if (twoBitBranchPredictor(twoBitBuffer, history_table, twoBitPredict_table, branch_pc))
                    correctPrediction1++;
                else
                    wrongPrediction1++;
                // Print Branch Target Buffer
                string prob;
                //HIT-MISS for taken/not-taken
                if (history_table[branch_pc].back() == '1')
                    prob = "HIT";
                else
                    prob = "MISS";
                fout << "Current PC: " << branch_pc << " Target PC: " << branchTargetBuffer[branch_pc] << " " << prob << endl;
                branch_pc.clear();
            }
            if (tokens[2][0] == 'b')
            {
                branch_pc = tokens[0];
                // To calculate Branch Target Buffer
                bTB(branchTargetBuffer, branch_pc, tokens);
            }
        }
        fout << "\n-------------------------------------------------------------------\n";
        fin.close();
        fout.close();
        cout << "Done Writing in BTB File" << endl;
        string out2 = outputHistoryTable(argv[i]);
        fout.open(out2);
        cout << "Writing in HT Output File..." << endl;
        fout << "\n\n-----------------------HISTORY TABLE-------------------------------\n\n";
        fin.open(argv[i]);
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty() || tokens[0].substr(0, 2) != "0x")
                continue;
            // Check if instruction is a branch and not printed before
            if (output[tokens[0]] == 0 && tokens[2][0] == 'b')
            {
                fout << tokens[0] << endl;
                // Output predictions for one-bit predictor
                fout << "Predictions of One Bit Predictor => ";
                for (auto i : oneBitPredict_table[tokens[0]])
                {
                    if (i == '0')
                        fout << "NT";
                    else
                        fout << "T";
                    fout << "|";
                }
                fout << endl;
                // Output predictions for two-bit predictor
                fout << "Predictions of Two Bit Predictor => ";
                for (auto i : twoBitPredict_table[tokens[0]])
                {
                    if (i == '0')
                        fout << "NT";
                    else
                        fout << "T";
                    fout << "|";
                }
                fout << endl;
                // Output actual results
                fout << "Actual Result => ";
                for (auto i : history_table[tokens[0]])
                {
                    if (i == '0')
                        fout << "NT";
                    else
                        fout << "T";
                    fout << "|";
                }
                fout << "\n-------------------------------------------------------------------\n";
                output[tokens[0]]++;
            }
        }
        cout << "Done Writing in HT Ouput File" << endl;
        fout.close();
        string out3 = outputAccuracy(argv[i]);
        cout << "Writing in Accuracy Output file..." << endl;
        fout.open(out3);
        fout << "\n\n------------------------------ACCURACY-------------------------------------\n\n";
        // Calculate and output accuracy
        float acc_1bit = Accuracy_cal(correctPrediction, wrongPrediction);
        fout << "Total Prediction of 1-bit Branch Predictor -> " << acc_1bit << "%" << endl;
        float acc_2bit = Accuracy_cal(correctPrediction1, wrongPrediction1);
        fout << "Total Prediction of 2-bit Branch Predictor -> " << acc_2bit << "%" << endl;
        float Accuracy = Accuracy_cal(Taken_count, Not_taken_count);
        fout << "Accuracy of branch predictor By Always Taken -> " << Accuracy << "%" << endl;
        float Acc = Accuracy_cal(Not_taken_count, Taken_count);
        fout << "Accuracy of branch predictor By Always Not Taken -> " << Acc << "%" << endl;
        fout << "\n\n-------------------------------------------------------------------\n\n";
        fin.close();
        fout.close();
        cout << "Done Writing in Accuracy Output File" << endl;
    }
    return 0;
}
