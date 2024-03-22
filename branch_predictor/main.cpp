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
    for (int i = 1; i <= argc; i++)
    {
        ifstream fin;
        ofstream fout;
        fin.open(argv[i]);
        string instruct;
        // Generate addresses of instructions
        string prev_pc;
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            if (tokens.empty())
                continue;
            if ((tokens[2][0] == 'b' || tokens[2][0] == 'j') && tokens[2] != "jalr")
            {
                if (prev_pc.size() != 0)
                    if (actualBranch(prev_pc, tokens[0]))
                        cout << tokens[0] << "Taken" << endl;
                    else
                        cout << tokens[0] << "Not Taken" << endl;
                prev_pc = tokens[0];
            }
        }
    }
    return 0;
}