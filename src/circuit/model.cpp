/****************************************************************************
   FileName     [ model.cpp ]
   PackageName  [ circuit ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Model class definition. Simulation model. ]
   Date         [ 2018/1/12 created ]
****************************************************************************/

#include "model.h"

using namespace std;


size_t Model::getConcatenateValue(size_t idx) const {
   // Given idx = 0
   // Save it as 
   // _values[0] = xx..xx0
   // _values[1] = xx..xx1
   // _values[2] = xx..xx1
   //                    ^
   //                   idx (position)
   // return 0x110
   size_t ret = CONST0;
   size_t shift = CONST1 << idx;
   for (size_t i = 0, n = _values.size(); i < n; ++i) {
      if (shift & _values[i])
         ret |= (CONST1 << i);
      else 
         ret &= ~(CONST1 << i);
   }
   return ret;
}


void Model::setConcatenateValue(size_t idx, size_t v) {
   // Given idx = 0, v = 110
   // Save it as 
   // _values[0] = xx..xx0
   // _values[1] = xx..xx1
   // _values[2] = xx..xx1
   //                    ^
   //                   idx (position)
   // 
   for (size_t i = 0, n = _values.size(); i < n; ++i) {
      if (v & CONST1)
         _values[i] |= CONST1 << idx; // | 000...0001
      else
         _values[i] &= ~(CONST1 << idx); // & 111..1110
      v >>= 1;
   }
}

