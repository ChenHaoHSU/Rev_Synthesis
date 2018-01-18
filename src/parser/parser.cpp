/****************************************************************************
   FileName     [ parser.cpp ]
   PackageName  [ parser ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Parser class definition. Parse spec file and store it to 
                  Class Spec ]
   Date         [ 2018/1/5 created ]
****************************************************************************/

#include "parser.h"
#include "util.hpp"

using namespace std;

bool Parser::parseSpecFile(const string& fileName, Spec& spec) {
   // Open file
   ifstream inf(fileName.c_str(), ios::in);
   if (!inf) {
      cerr << "Error: Cannot open spec file \"" << fileName << "\"." << endl;
      return false;
   }

   // Parse context
   int lineNo = 0;
   string buffer = "";
   while (getline(inf, buffer, '\n')) {
      ++lineNo;
      
      // Only one line is allowed
      if (lineNo > 1) {
         cerr << "Error: Extra lines in spec file \"" << fileName << "\"." << endl;
         return false;
      }

      // Parse the first line
      if (lineNo == 1){
         if (!parseSpecSeq(buffer, spec)) return false;
      }
   }

   return true;
}


bool Parser::parseSpecSeq(const string& buffer, Spec& spec) {
   string tok    = "";
   int    tmpInt = 0;
   size_t pos    = 0;
   size_t x      = 0;
   size_t y      = 0;
   while (true) {
      pos = myStrGetTok(buffer, tok, pos, ',');
      if (!myStr2Int(tok, tmpInt)) {
         cerr << "Error: Invalid integer \"" << tok << "\" in spec file." << endl;
         return false; 
      }
      if (tmpInt < 0) {
         cerr << "Error: Negative integer \"" << tok << "\" in spec file." << endl;
         return false; 
      }

      // add to spec
      y = tmpInt;
      spec.addOne(x, y);
      x++;

      if (pos == string::npos) break;
   }
   spec.summarize();
   // spec.printSpec();
   return spec.isValid();
}


bool Parser::parseTfcFile(const string& fileName, Circuit& circuit) {
   // TODO
   return true;
}
