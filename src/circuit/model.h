/****************************************************************************
   FileName     [ model.h ]
   PackageName  [ circuit ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Model class declaration. Simulation model. ]
   Date         [ 2018/1/12 created ]
****************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include "global.hpp"
#include "util.hpp"

using namespace std;

class Model {
public:
   Model(size_t s = 0) {
      _values.resize(s, 0);
   }
   ~Model() {}

   const size_t operator[] (size_t i) const { return _values[i]; }
   size_t& operator[] (size_t i) { return _values[i]; }

   size_t getConcatenateValue(size_t) const;
   void   setConcatenateValue(size_t, size_t);

   size_t size()     const { return _values.size(); }
   void   resize(size_t s) { _values.resize(s);     }

private:
   vector<size_t> _values;
};

#endif // MODEL_H



