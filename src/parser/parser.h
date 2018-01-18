/****************************************************************************
   FileName     [ parser.h ]
   PackageName  [ parser ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Parser class declaration. Parse spec file and store it to 
                  Class Spec ]
   Date         [ 2018/1/5 created ]
****************************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include "global.hpp"
#include "paramHandler.hpp"
#include "spec.h"
#include "circuit.h"

using namespace std;

class Parser {
public:
   Parser() {}
   ~Parser() {}

   // Spec file parser
   bool parseSpecFile(const string&, Spec&);
   bool parseSpecSeq(const string&, Spec&);

   // Tfc file parser
   bool parseTfcFile(const string&, Circuit&);

private:
};

#endif // PARSER_H