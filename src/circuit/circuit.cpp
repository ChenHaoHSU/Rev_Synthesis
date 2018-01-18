/****************************************************************************
   FileName     [ circuit.cpp ]
   PackageName  [ circuit ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Circuit class definition. Reversible circuit. ]
   Date         [ 2018/1/6 created ]
****************************************************************************/

#include "circuit.h"

using namespace std;

Circuit::Circuit(size_t nInputs, size_t nOutputs) {
   _nInputs  = nInputs;
   _nOutputs = nOutputs;

   // Pi gates
   _pi.resize(nInputs);
   for (size_t i = 0; i < nInputs; ++i) {
      _pi[i] = new PiGate;
      _pi[i]->setLineNo(i);
   }

   // Initialize lineNames
   initLineNames();

   _fClear = true;
}


void Circuit::initLineNames() {
   // Line Names
   // Change whatever name you want
   // Names: l_0, l_1, l_2, ...
   _lineNames.resize(_nInputs);
   for (size_t i = 0; i < _nInputs; ++i)
      _lineNames[i] = "I_" + to_string(i);
}


Model Circuit::simulate(const Model& model) {
   assert(model.size() == _nInputs);

   // Set sim value to PIs
   for (size_t i = 0, n = _pi.size(); i < n; ++i)
      _pi[i]->setValue(model[i]);

   // Initial frontier
   vector<Gate*> frontier;
   frontier.resize(_nInputs);
   for (size_t i = 0; i < _pi.size(); ++i)
      frontier[i] = _pi[i];

   // Forward propagation
   Gate* current    = 0;
   Gate* tmpFredkin = 0;
   for (auto iter = _gates.begin(); iter != _gates.end(); ++iter) {
      current = *iter;
      current->calValue(frontier);
      if (current->type() == FREDKIN_GATE) {
         tmpFredkin = current;
         current = *(++iter);
         current->calValue(frontier);
      }
      frontier[current->lineNo()] = current;
      if (current->type() == FREDKIN_GATE)
         frontier[tmpFredkin->lineNo()] = tmpFredkin;
   }

   // Set return model
   Model retModel(_nInputs);
   for (size_t i = 0, n = frontier.size(); i < n; ++i)
      retModel[i] = frontier[i]->value();

   return retModel;
}


Model Circuit::revSimulate(const Model& model) {
   assert(model.size() == _nInputs);

   // Set sim value to PIs
   for (size_t i = 0, n = _pi.size(); i < n; ++i)
      _pi[i]->setValue(model[i]);

   // Initial frontier
   vector<Gate*> frontier;
   frontier.resize(_nInputs);
   for (size_t i = 0; i < _pi.size(); ++i)
      frontier[i] = _pi[i];

   // Backward propagation
   Gate* current    = 0;
   Gate* tmpFredkin = 0;
   for (auto iter = _gates.rbegin(); iter != _gates.rend(); ++iter) {
      current = *iter;
      current->calValue(frontier);
      if (current->type() == FREDKIN_GATE) {
         tmpFredkin = current;
         current = *(++iter);
         current->calValue(frontier);
      }
      frontier[current->lineNo()] = current;
      if (current->type() == FREDKIN_GATE)
         frontier[tmpFredkin->lineNo()] = tmpFredkin;
   }

   // Set return model
   Model retModel(_nInputs);
   for (size_t i = 0, n = frontier.size(); i < n; ++i)
      retModel[i] = frontier[i]->value();

   return retModel;
}


void Circuit::reverse() {
   // Reverse all gates
   _gates.reverse();
}


void Circuit::outputTfcFile(const string& fileName) const {
   static const string defaultName = "temp.tfc"; 

   printHeader(cout, "Output tfc file");

   // Open output file
   ofstream outf(fileName.c_str(), ios::out);
   if (!outf) {
      outf.open(defaultName.c_str(), ios::out);
      cerr << "> Warning: Cannot open \"" << fileName << "\".\n";
      cerr << "> Warning: Use default filename \"" << defaultName << "\".\n";
   }
   printTfcFile(outf);
   outf.close();

   // Show msg
   cout << "> Output tfc file \"" << fileName << "\".\n";
   cout << endl;
   // printTfcFile(cerr);
}


void Circuit::printTfcFile(ostream& os) const {
   // Variables string (e.g. a,b,c)
   string str = "";
   for (size_t i = 0; i < _nInputs; ++i){
      str = _lineNames[i] + str;
      if (i < _nInputs - 1) str = "," + str; 
   }

   // .v .i .o
   os << ".v " << str << endl;
   os << ".i " << str << endl;
   os << ".o " << str << endl;

   // Gates
   os << "BEGIN" << endl;
   for (auto iter = _gates.begin(); iter != _gates.end(); ++iter) {
      os << (*iter)->tfcGateString(_lineNames) << endl;
      if ((*iter)->type() == FREDKIN_GATE) ++iter;
   }
   os << "END" << endl;
}


void Circuit::printGates() const {
   for (auto iter = _gates.begin(); iter != _gates.end(); ++iter)
      cout << (*iter)->tfcGateString(_lineNames) << endl;
}


void Circuit::printCircuitInfo() const {
   printHeader(cout, "Circuit Infomation");
   cout << "> I / O  = " << _nInputs << " / " << _nOutputs << endl;
   cout << "> #Gates = " << nGates()     << endl;
   cout << "> #Ctrl  = " << nTotalCtrl() << endl;
   cout << endl;
}


size_t Circuit::nTotalCtrl() const {
   size_t total   = 0;
   Gate*  current = 0;
   for (auto iter = _gates.begin(); iter != _gates.end(); ++iter) {
      current = (*iter);
      if (current->type() == CNOT_GATE)
         total += ((CNotGate*)current)->nCtrl();
      else if (current->type() == FREDKIN_GATE) {
         total += ((FredkinGate*)current)->nCtrl();
         ++iter; 
      }
   }
   return total;
}


size_t Circuit::nGates() const {
   size_t total = 0;
   for (auto iter = _gates.begin(); iter != _gates.end(); ++iter) {
      ++total;
      if ((*iter)->type() == FREDKIN_GATE) ++iter;
   }
   return total;
}


size_t Circuit::nGateWidth() const {
   size_t total = 0;
   for (auto iter = _gates.begin(); iter != _gates.end(); ++iter)
      ++total;
   return total;
}


void Circuit::merge(const Circuit& mergedCir) {
   const list<Gate*>& mergedGates = mergedCir.gates();
   for (auto& gate : mergedGates)
      _gates.push_back(gate);
} 


void Circuit::clear() {
   // Clear all gate pointer
   // Clear PIs
   for (size_t i = 0; i < _pi.size(); ++i)
      delete _pi[i];

   // Clear all gates
   if (_fClear) {
      for (auto& gate : _gates)
         delete gate;
      _gates.clear();
   }
}
