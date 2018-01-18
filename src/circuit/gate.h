/****************************************************************************
   FileName     [ gate.h ]
   PackageName  [ circuit ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Gate class definition. Reversible gates including CmNOT, CNOT, NOT ]
   Date         [ 2018/1/6 created ]
****************************************************************************/

#include "global.hpp"
#include "util.hpp"

using namespace std;

class Gate;
class CNotGate;
class FredkinGate;
class PiGate;
class PoGate;


enum GateType {
   CNOT_GATE    = 0,
   FREDKIN_GATE = 1,
   PI_GATE      = 2,
   PO_GATE      = 3,
   // dummy
   TOT_GATE     = 4
};


class Gate {
public:
   Gate(Gate* g = 0, Gate* x = 0, size_t l = 0, size_t n = 0, size_t v = 0, GateType t = TOT_GATE) 
      : _prev(g), _next(x), _level(l), _lineNo(n), _value(v), _type(t) {}
   virtual ~Gate() {}

   // Basic setting functions
   void setType(GateType t)  { _type = t;   }
   void setValue(size_t v)   { _value = v;  }
   void setLevel(size_t l)   { _level = l;  }
   void setLineNo(size_t n)  { _lineNo = n; }
   void setPrev(Gate* g)     { _prev = g;   }
   void setNext(Gate* g)     { _next = g;   }

   // Basic access functions
   GateType type()   const { return _type;   }
   size_t   value()  const { return _value;  }
   size_t   level()  const { return _level;  }
   size_t   lineNo() const { return _lineNo; }
   Gate*    prev()   const { return _prev;   }
   Gate*    next()   const { return _next;   }

   void insertPrev(Gate* g) {
      if (_prev != 0)
         _prev->setNext(g);
      g->setPrev(_prev);
      _prev = g;
      g->setNext(this);
   }

   void insertNext(Gate* g) {
      if (_next != 0)
         _next->setPrev(g);
      g->setNext(_next);
      _next = g;
      g->setPrev(this);
   }

   void reverse() {
      Gate* tmp = _prev;
      _prev = _next;
      _next = tmp;
   }
   // Pure virtual functions
   virtual void   calValue(const vector<Gate*>&)       = 0;
   virtual string tfcGateString(const vector<string>&) = 0;

protected:
   Gate*    _prev;
   Gate*    _next;
   size_t   _level;
   size_t   _lineNo;
   size_t   _value;
   GateType _type;
};


class CNotGate: public Gate {

public:
   CNotGate(Gate* g = 0, Gate* x = 0, size_t l = 0, size_t n = 0, size_t v = 0, GateType t = CNOT_GATE) 
      : Gate(g,x,l,n,v,t) {}
   ~CNotGate() {}

   void   clearControlLine()       { _controls.resize(0);     }
   void   addControlLine(size_t g) { _controls.push_back(g);  }
   size_t nCtrl()            const { return _controls.size(); }
   size_t getCtrl(size_t i)  const { return _controls[i];     }
   

   virtual void calValue(const vector<Gate*>& frontier) {
      size_t control = ALL1;
      for (size_t i = 0, n = _controls.size(); i < n; ++i)
         control &= (frontier[_controls[i]]->value());
      _value = control ^ (frontier[_lineNo]->value());
   }

   virtual string tfcGateString(const vector<string>& lineNames) {   
      string str = "";
      str += "t" + to_string(_controls.size() + 1) + " ";
      for (size_t i = 0, n = _controls.size(); i < n; ++i)
         str += lineNames[_controls[i]] + ",";
      str += lineNames[_lineNo];
      return str;
   }

private:
   vector<size_t> _controls;
};


class FredkinGate: public Gate {
public:
   FredkinGate(Gate* g = 0, Gate* x = 0, size_t l = 0, size_t n = 0, size_t v = 0, GateType t = FREDKIN_GATE) 
      : Gate(g,x,l,n,v,t) {}
   ~FredkinGate() {}

   void   clearControlLine()       { _controls.resize(0);     }
   void   addControlLine(size_t g) { _controls.push_back(g);  }
   size_t nCtrl()           const  { return _controls.size(); }
   size_t getCtrl(size_t i) const  { return _controls[i];     }
   void   setSwap(size_t s)        { _swap = s;               }
   
   virtual void calValue(const vector<Gate*>& frontier) {
      size_t control = ALL1;
      for (size_t i = 0, n = _controls.size(); i < n; ++i)
         control &= (frontier[_controls[i]]->value());
      _value = (control & (frontier[_swap]->value())) | (~control & (frontier[_lineNo]->value()));
   }

   virtual string tfcGateString(const vector<string>& lineNames) {
      string str = "";
      str += "f" + to_string(_controls.size() + 2) + " ";
      for (size_t i = 0, n = _controls.size(); i < n; ++i)
         str += lineNames[_controls[i]] + ",";
      str += lineNames[_lineNo] + "," + lineNames[_swap];
      return str;
   }

private:
   size_t         _swap;
   vector<size_t> _controls;
};


class PiGate: public Gate {
public:
   PiGate() {}
   ~PiGate() {}

   virtual void calValue(const vector<Gate*>& frontier) {}

   virtual string tfcGateString(const vector<string>& lineNames) {   
      return "";
   }

private:

};


class PoGate: public Gate {
public:
   PoGate() {}
   ~PoGate() {}

   virtual void calValue(const vector<Gate*>& frontier) {}
   virtual string tfcGateString(const vector<string>& lineNames) {   
      return "";
   }

private:

};

