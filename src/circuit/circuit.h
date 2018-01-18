/****************************************************************************
   FileName     [ circuit.h ]
   PackageName  [ circuit ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Circuit class declaration. Reversible circuit. ]
   Date         [ 2018/1/6 created ]
****************************************************************************/

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "global.hpp"
#include "util.hpp"
#include "gate.h"
#include "model.h"

using namespace std;

class Circuit {
   friend class Synthesis;
   friend class Gnuplotter;

public:
   Circuit(size_t nInputs, size_t nOutputs);
   ~Circuit() { clear(); }

   void initLineNames();

   Gate*   pi(size_t i)   const { return _pi[i];        }
   size_t  nInputs()      const { return _nInputs;      }
   size_t  nOutputs()     const { return _nOutputs;     }
   size_t  nLines()       const { return _nInputs;      }
   bool    fClear()       const { return _fClear;       }
   size_t  nGates()       const;
   size_t  nGateWidth()   const;
   size_t  nTotalCtrl()   const;

   Model simulate(const Model&);
   Model revSimulate(const Model&);

   void reverse(); 
   void outputTfcFile(const string&) const;
   void printTfcFile(ostream& os)    const;
   void printGates()                 const;

   void printCircuitInfo() const;

   void setClear()              { _fClear = true;      }
   void resetClear()            { _fClear = false;     }
   void addGate(Gate* g)        { _gates.push_back(g); }
   void merge(const Circuit&);

   const list<Gate*>& gates() const { return _gates; }

   void clear();

private:
   size_t                  _nInputs;
   size_t                  _nOutputs;
   vector<Gate*>           _pi;
   list<Gate*>             _gates;
   vector<string>          _lineNames; // line names
   bool                    _fClear;
};

#endif // CIRCUIT_H