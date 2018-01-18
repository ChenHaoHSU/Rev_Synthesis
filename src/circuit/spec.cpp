/****************************************************************************
   FileName     [ spec.cpp ]
   PackageName  [ circuit ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Spec class definition. Store the reversible function ]
   Date         [ 2018/1/5 created ]
****************************************************************************/

#include "spec.h"
#include "util.hpp"

using namespace std;

void Spec::addOne(size_t x, size_t y) {
   if (x >= _func.size()) _func.resize(x+1);
   _func[x] = y;
   if (y >= _revFunc.size()) _revFunc.resize(y+1);
   _revFunc[y] = x;
}


bool Spec::isValid() const {
   if (_func.size() != _revFunc.size()) {
      cerr << "> Error: Not reversible function in spec file." << endl;
      return false;
   }

   // Still more to handle....

   return true;
}


void Spec::summarize() {
   if (!completeLog2(_func.size(), _nInputs)) {
      cout << "> Warning: " << endl;
   }
   completeLog2(_func.size(), _nOutputs);
}


void Spec::reverse() {
   size_t tmp = 0;
   assert(_func.size() == _revFunc.size());
   for (size_t i = 0; i < _func.size(); ++i) {
      tmp = _func[i];
      _func[i] = _revFunc[i];
      _revFunc[i] = tmp;
   }
}

void Spec::printSpec() const
{
   static const size_t PRINT_SPEC_WIDTH = 3;
   printHeader(cout, "Specification");
   size_t y = 0;
   cout << setw(PRINT_SPEC_WIDTH + _nInputs + 2) << left << "X" << "   "
        << setw(PRINT_SPEC_WIDTH + _nInputs + 2) << left << "Y" << endl;
   for (size_t x = 0, n = _func.size(); x < n; ++x) {
      y = _func[x];
      cout << setw(PRINT_SPEC_WIDTH) << right << x << " "
           << "(" << bitString(x, _nInputs) << ") = "
           << setw(PRINT_SPEC_WIDTH) << right << y << " "
           << "(" << bitString(y, _nInputs) << ") \n";
   }
   cout << endl << "I / O = " << _nInputs << " / " << _nOutputs << endl;
   cout << endl;
}
