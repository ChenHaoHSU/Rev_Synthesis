/****************************************************************************
   FileName     [ spec.h ]
   PackageName  [ circuit ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Spec class declaration. Store the reversible function ]
   Date         [ 2018/1/5 created ]
****************************************************************************/

#ifndef SPEC_H
#define SPEC_H

#include "global.hpp"

using namespace std;

class Spec {
public:
   Spec() {}
   ~Spec() {}

   // Basic setting functions
   void addOne(size_t x, size_t y);

   // Basic access functions
   size_t size()              const { return _func.size(); }
   size_t nInputs()           const { return _nInputs;     }
   size_t nOutputs()          const { return _nOutputs;    }
   size_t func(size_t i)      const { return _func[i];     }
   size_t revFunc(size_t i)   const { return _revFunc[i];  }

   const size_t operator[] (size_t i) const { return _func[i]; }
   size_t&      operator[] (size_t i)       { return _func[i]; }
   
   bool isValid() const;
   void reverse();
   void summarize();

   // Debugging
   void printSpec() const;

private:
   vector<size_t>  _func;    // f(x)    = y
   vector<size_t>  _revFunc; // f^-1(y) = x
   size_t          _nInputs;
   size_t          _nOutputs;
};

#endif // SPEC_H