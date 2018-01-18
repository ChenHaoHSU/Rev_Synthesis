/****************************************************************************
   FileName     [ gnuplotter.h ]
   PackageName  [ gnuplot ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Gnuplotter class declaration. Plot revCkt. ]
   Date         [ 2018/1/13 created ]
****************************************************************************/

#ifndef GNUPLOTTER_H
#define GNUPLOTTER_H

#include "circuit.h"
#include "global.hpp"
#include "util.hpp"

using namespace std;

class Gnuplotter {
public:
   Gnuplotter() {}
   ~Gnuplotter() {}

   void liveGnuplot(const Circuit&);
   void outputGnuplot(const string&, const Circuit&);
   string gnuplotStr(const Circuit&);

private:
   
};

#endif // GNUPLOTTER_H
