/****************************************************************************
   FileName     [ verifier.h ]
   PackageName  [ verify ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Verifier class declaration. Verify spec and revCkt. ]
   Date         [ 2018/1/13 created ]
****************************************************************************/

#ifndef VERIFIER_H
#define VERIFIER_H

#include "global.hpp"
#include "util.hpp"
#include "circuit.h"
#include "synthesis.h"

using namespace std;

class Verifier {
public:
   Verifier(Circuit& c, Spec& s) : _circuit(c), _spec(s) {}
   ~Verifier() {}

   bool verify();

private:
   Circuit& _circuit;
   Spec&    _spec;
};

#endif // VERIFIER_H