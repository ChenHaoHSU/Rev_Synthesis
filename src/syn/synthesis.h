/****************************************************************************
   FileName     [ synthesis.h ]
   PackageName  [ syn ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Synthesis class declaration. Synthesis reversible circuit 
                  specified by class spec ]
   Date         [ 2018/1/6 created ]
****************************************************************************/

#ifndef SYNTHESIS_H
#define SYNTHESIS_H

#include "global.hpp"
#include "util.hpp"
#include "circuit.h"
#include "spec.h"

using namespace std;


class Synthesis {
public:
   Synthesis(Spec& s, Circuit& c) : _spec(s), _circuit(c) {
      _nInputs  = _spec.nInputs();
      _nOutputs = _spec.nOutputs();
      _level = 0;
   }
   ~Synthesis() {}
   
   void buildHwGrp();

   // Reversible Gate Library
   //    N : Not gate
   //    C : Controlled Not gate
   //    T : Toffoli gate (multiple controlled Not gate)
   //    S : Swap gate
   //    F : Fredkin gate (multiple controlled Swap gate)
   void synthesis_nct();      // one-way syn (NCT)
   void synthesis_rev_nct();  // reverse spec syn (NCT)
   void synthesis_bi_nct();   // bi-directional alogorithm (NCT)
   void synthesis_nctsf();    // one-way syn (NCTSF)
   void synthesis_bi_nctsf(); // bi-directional alogorithm (NCTSF)

   void rectifyZero(Circuit&, const size_t&);
   void rectify(Circuit&, const size_t&, const size_t&);
   void rectify_nctsf(Circuit&, const size_t&, const size_t&);

   void printHwGrp() const;

private:
   Spec&          _spec;
   Circuit&       _circuit;
   size_t         _nInputs;
   size_t         _nOutputs;
   size_t         _level;

   vector<vector<size_t> > _hwGrp;    // hamming weight group 
};

#endif // SYNTHESIS_H