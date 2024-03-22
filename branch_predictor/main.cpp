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
        while (getline(fin, instruct))
        {
            vector<string> tokens = instructionToToken(instruct);
            string next_pc;
            if (tokens.empty())
                continue;
            for (auto token : tokens)
                cout << "TOKEN:" << token << " ";
            cout << endl;
            
        }
    }
    return 0;
}