/****************************************************************************
   FileName     [ main.cpp ]
   PackageName  [ revSpenGen ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Randomly generate spec file for reversible circuit ]
   Date         [ 2018/1/12 created ]
****************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

#define SHUFFLE_TIME 1000

int usage();
bool myStr2Int(const string&, int&);
void shuffle(vector<size_t>&);

int main(int argc, char** argv) {
   if (argc != 3) return usage();
   
   // File name
   string fileName = argv[1];

   // #Inputs
   string numStr = argv[2];
   int nInputs = 0;
   if (!myStr2Int(numStr, nInputs)) {
      cerr << "Error: Invalid number of inputs (" << numStr << ")" << endl;
      exit(0);
   }

   // 2 ^ #Inputs
   size_t nCombination = (1 << nInputs);

   vector<size_t> list;
   for (size_t i = 0; i < nCombination; ++i)
      list.push_back(i);
   shuffle(list);

   // Output to file
   ofstream outf(fileName.c_str(), ios::out);
   if (!outf) {
      cerr << "Error: Cannot open file \"" << fileName << "\"\n";
      return -1; 
   }

   for (size_t i = 0; i < list.size(); ++i) {
      if (i > 0) outf << ",";
      outf << list[i];
   }
   outf << endl;
   outf.close();

   return 0;   
}


void shuffle(vector<size_t>& v) {
   srand((unsigned)time(NULL));
   size_t size = v.size();
   size_t pos1, pos2,temp;
   for (size_t i = 0, n = v.size() * 2; i < n; ++i) {
      pos1 = rand() % size;
      pos2 = rand() % size;
      if (pos1 == pos2) continue;
      temp = v[pos1];
      v[pos1] = v[pos2];
      v[pos2] = temp;
   }
}


int usage() {
   cerr << "Usage: ./specGen <outFileName> <#Inputs> \n";
   cerr << "e.g. ./specGen example.spec 4 \n";
   return -1;
}


bool myStr2Int(const string& str, int& num)
{
   num = 0;
   size_t i = 0;
   int sign = 1;
   if (str[0] == '-') { sign = -1; i = 1; }
   bool valid = false;
   for (; i < str.size(); ++i) {
      if (isdigit(str[i])) {
         num *= 10;
         num += int(str[i] - '0');
         valid = true;
      }
      else return false;
   }
   num *= sign;
   return valid;
}