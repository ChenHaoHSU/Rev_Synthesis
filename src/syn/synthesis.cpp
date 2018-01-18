/****************************************************************************
   FileName     [ synthesis.cpp ]
   PackageName  [ syn ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Synthesis class definition. Synthesis reversible circuit 
                  specified by class spec ]
   Date         [ 2018/1/6 created ]
****************************************************************************/

#include "synthesis.h"

using namespace std;


void Synthesis::synthesis_nct() {
   // Build Hamming Weight Group 
   buildHwGrp();

   // Start transformation-based synthesis
   size_t current = 0;
   size_t target  = 0;
   Model model(_nInputs);

   // Rectify f(0)
   rectifyZero(_circuit, _spec[0]);

   // Rectify all inputs except 0
   // Rectifying order is increasing Hamming weight oreder 
   for (size_t i = 1; i < _hwGrp.size(); ++i) {
      for (size_t j = 0; j < _hwGrp[i].size(); ++j) {

         // Get the transformed value by simulation to current circuit
         model.setConcatenateValue(0, _spec[_hwGrp[i][j]]);
         current = _circuit.simulate(model).getConcatenateValue(0);
         target  = _hwGrp[i][j];

         // Rectify f(x) if it is not matched
         if (current != target) 
            rectify(_circuit, current, target);
      }
   }

   // Merge two circuits
   _circuit.reverse();
}


void Synthesis::synthesis_rev_nct() {
   // Build Hamming Weight Group 
   buildHwGrp();

   // Start transformation-based synthesis
   size_t current = 0;
   size_t target  = 0;
   Model model(_nInputs);

   // Rectify f(0)
   rectifyZero(_circuit, _spec.revFunc(0));

   // Rectify all inputs except 0
   // Rectifying order is increasing Hamming weight oreder 
   for (size_t i = 1; i < _hwGrp.size(); ++i) {
      for (size_t j = 0; j < _hwGrp[i].size(); ++j) {

         // Get the transformed value by simulation to current circuit
         model.setConcatenateValue(0, _spec.revFunc(_hwGrp[i][j]));
         current = _circuit.simulate(model).getConcatenateValue(0);
         target  = _hwGrp[i][j];

         // Rectify f(x) if it is not matched
         if (current != target) 
            rectify(_circuit, current, target);
      }
   }
}


void Synthesis::synthesis_bi_nct() {
   // Build Hamming Weight Group 
   buildHwGrp();

   Circuit iCir(_nInputs, _nOutputs); // i part 
   Circuit oCir(_nInputs, _nOutputs); // o part
   iCir.resetClear();
   oCir.resetClear();

   // Start transformation-based synthesis
   size_t current1 = 0;
   size_t current2 = 0;
   size_t target   = 0;
   size_t hd1      = 0; // i to o, hamming distance 
   size_t hd2      = 0; // o to i, hamming distance 
   size_t tmp      = 0; 
   Model model(_nInputs);

   // Rectify f(0)
   hd1 = hammingDist(0, _spec[0], _nInputs);
   hd2 = hammingDist(_spec.revFunc(0), 0, _nInputs);
   if (hd1 < hd2) 
      rectifyZero(oCir, _spec[0]);
   else 
      rectifyZero(iCir, _spec.revFunc(0));

   // Rectify all inputs except 0
   // Rectifying order is increasing Hamming weight oreder 
   for (size_t i = 1; i < _hwGrp.size(); ++i) {
      for (size_t j = 0; j < _hwGrp[i].size(); ++j) {

         target  = _hwGrp[i][j];

         // First pair i -> o
         model.setConcatenateValue(0, target);
         tmp = iCir.revSimulate(model).getConcatenateValue(0);
         tmp = _spec[tmp];
         model.setConcatenateValue(0, tmp);
         current1 = oCir.simulate(model).getConcatenateValue(0);
         hd1 = hammingDist(target, current1, _nInputs);

         // Continue if the pair is already matched
         if (target == current1) continue;

         // Second pair o -> i
         model.setConcatenateValue(0, target);
         tmp = oCir.revSimulate(model).getConcatenateValue(0);
         tmp = _spec.revFunc(tmp);
         model.setConcatenateValue(0, tmp);
         current2 = iCir.simulate(model).getConcatenateValue(0);
         hd2 = hammingDist(target, current2, _nInputs);

         // Rectify pair from input side or output side
         if (hd1 < hd2) 
            rectify(oCir, current1, target);
         else 
            rectify(iCir, current2, target);
      }
   }

   // Merge two circuits
   oCir.reverse();
   iCir.merge(oCir);
   _circuit.merge(iCir);
}


void Synthesis::synthesis_nctsf() {
   // Build Hamming Weight Group 
   buildHwGrp();

   Circuit iCir(_nInputs, _nOutputs); // i part 
   Circuit oCir(_nInputs, _nOutputs); // o part
   iCir.resetClear();
   oCir.resetClear();

   // Start transformation-based synthesis
   size_t current  = 0;
   size_t target   = 0;
   size_t tmp      = 0;
   Model model(_nInputs);

   // Rectify f(0)
   rectifyZero(oCir, _spec[0]);

   // Rectify all inputs except 0
   // Rectifying order is increasing Hamming weight oreder 
   for (size_t i = 1; i < _hwGrp.size(); ++i) {
      for (size_t j = 0; j < _hwGrp[i].size(); ++j) {

         target  = _hwGrp[i][j];

         // First pair i -> o
         model.setConcatenateValue(0, target);
         tmp = iCir.revSimulate(model).getConcatenateValue(0);
         tmp = _spec[tmp];
         model.setConcatenateValue(0, tmp);
         current = oCir.simulate(model).getConcatenateValue(0);

         rectify_nctsf(oCir, current, target);
      }
   }

   // Merge two circuits
   oCir.reverse();
   iCir.merge(oCir);
   _circuit.merge(iCir);
}


void Synthesis::synthesis_bi_nctsf() {
   // Build Hamming Weight Group 
   buildHwGrp();

   Circuit iCir(_nInputs, _nOutputs); // i part 
   Circuit oCir(_nInputs, _nOutputs); // o part
   iCir.resetClear();
   oCir.resetClear();

   // Start transformation-based synthesis
   size_t current1 = 0;
   size_t current2 = 0;
   size_t target   = 0;
   size_t hd1      = 0; // i to o, hamming distance 
   size_t hd2      = 0; // o to i, hamming distance 
   size_t cost1    = 0; // i to o, rectifying cost
   size_t cost2    = 0; // o to i, rectifying cost 
   size_t tmp      = 0; 
   Model model(_nInputs);

   // Rectify f(0)
   hd1 = hammingDist(0, _spec[0], _nInputs);
   hd2 = hammingDist(_spec.revFunc(0), 0, _nInputs);
   if (hd1 < hd2) 
      rectifyZero(oCir, _spec[0]);
   else 
      rectifyZero(iCir, _spec.revFunc(0));

   // Rectify all inputs except 0
   // Rectifying order is increasing Hamming weight oreder 
   for (size_t i = 1; i < _hwGrp.size(); ++i) {
      for (size_t j = 0; j < _hwGrp[i].size(); ++j) {

         target  = _hwGrp[i][j];

         // First pair i -> o
         model.setConcatenateValue(0, target);
         tmp = iCir.revSimulate(model).getConcatenateValue(0);
         tmp = _spec[tmp];
         model.setConcatenateValue(0, tmp);
         current1 = oCir.simulate(model).getConcatenateValue(0);
         hd1 = hammingDist(target, current1, _nInputs);

         // Continue if the pair is already matched
         if (target == current1) continue;

         // Second pair o -> i
         model.setConcatenateValue(0, target);
         tmp = oCir.revSimulate(model).getConcatenateValue(0);
         tmp = _spec.revFunc(tmp);
         model.setConcatenateValue(0, tmp);
         current2 = iCir.simulate(model).getConcatenateValue(0);
         hd2 = hammingDist(target, current2, _nInputs);

         // Calculate Cost (cost = hd - sw)
         cost1 = hd1 - min(num_10(target, current1, _nInputs), num_01(target, current1, _nInputs));
         cost2 = hd2 - min(num_10(target, current2, _nInputs), num_01(target, current2, _nInputs));

         // Rectify pair from input side or output side
         if (cost1 <= cost2)
            rectify_nctsf(oCir, current1, target);
         else 
            rectify_nctsf(iCir, current2, target);
      }
   }

   // Merge two circuits
   oCir.reverse();
   iCir.merge(oCir);
   _circuit.merge(iCir);
}


void Synthesis::rectify_nctsf(Circuit& circuit, const size_t& current, const size_t& target) {
   static vector<size_t> target_pos1;
   static vector<size_t> diff_pos;
   static vector<size_t> current_pos1;
   static vector<size_t> diff_pos10; // current 1, target 0
   static vector<size_t> diff_pos01; // current 1, target 0
   static size_t         current_copy;

   // No need to rectify
   if (current == target) return;

   current_copy = current;

   positions_1(current_pos1, current_copy, _nInputs);
   positions_10(diff_pos10, current_copy, target, _nInputs);
   positions_01(diff_pos01, current_copy, target, _nInputs);

   // 
   // Fredkin Gates Synthesis
   // 
   if (!diff_pos01.empty() && !diff_pos10.empty()) {
      FredkinGate* newFGate1 = 0;
      FredkinGate* newFGate2 = 0;
      for (size_t i = 0, n = min(diff_pos01.size(), diff_pos10.size()); i < n; ++i) {
         // Get new gates
         newFGate1 = new FredkinGate;
         newFGate2 = new FredkinGate;
         newFGate1->setSwap(diff_pos01[i]);
         newFGate2->setSwap(diff_pos10[i]);
         newFGate1->setLineNo(diff_pos10[i]);
         newFGate2->setLineNo(diff_pos01[i]);
         for (size_t j = 0; j < current_pos1.size(); ++j)
            if (current_pos1[j] != diff_pos01[i] 
               && current_pos1[j] != diff_pos10[i]){
               newFGate1->addControlLine(current_pos1[j]);
               newFGate2->addControlLine(current_pos1[j]);
            }

         // Add new gates to circuit
         circuit.addGate(newFGate1);
         circuit.addGate(newFGate2);

         // Update current
         current_copy = current_copy ^ (CONST1 << diff_pos01[i]);
         current_copy = current_copy ^ (CONST1 << diff_pos10[i]);
         positions_1(current_pos1, current_copy, _nInputs);
      }
   }

   // 
   // Toffoli Gates Synthesis
   // 
   size_t diff = current_copy ^ target;
   positions_1(diff_pos, diff, _nInputs);
   positions_1(target_pos1, target, _nInputs);

   // Rectify 0 to 1
   CNotGate* newGate = 0;
   for (size_t i = 0, n = diff_pos.size(); i < n; ++i) {
      if (target & (CONST1 << diff_pos[i])) {
         // Get new gate
         newGate = new CNotGate(0, 0, ++_level, diff_pos[i]);
         for (size_t j = 0, m = current_pos1.size(); j < m; ++j) 
            newGate->addControlLine(current_pos1[j]);
         circuit.addGate(newGate);
         // Get new one
         current_pos1.push_back(diff_pos[i]);
      }
   }

   // Rectify 1 to 0
   for (size_t i = 0, n = diff_pos.size(); i < n; ++i) {
      if (!(target & (CONST1 << diff_pos[i]))) {
         // Get new gate
         newGate = new CNotGate(0, 0, ++_level, diff_pos[i]);
         for (size_t j = 0, m = target_pos1.size(); j < m; ++j) 
            newGate->addControlLine(target_pos1[j]);
         circuit.addGate(newGate);
      }
   }
}


void Synthesis::buildHwGrp() {
   // Take n = 3 for example,
   //    _hwGrp[0] = [ 000 ]
   //    _hwGrp[1] = [ 001, 010, 001 ]
   //    _hwGrp[2] = [ 011, 101, 110 ]
   //    _hwGrp[3] = [ 111 ]
   //    
   _hwGrp.resize(_nInputs + 1);
   size_t hd = 0;
   for (size_t i = 0, n = _spec.size(); i < n; ++i) {
      hd = hammingWeight(i, _nInputs);
      _hwGrp[hd].push_back(i);
   }
}


void Synthesis::rectifyZero(Circuit& circuit, const size_t& target) {
   // No need to rectify
   if (_spec[0] == CONST0) return;

   // Rectify by adding NOT gates
   vector<size_t> pos1;
   positions_1(pos1, target, _nInputs);
   for (size_t i = 0, n = pos1.size(); i < n; ++i) {
      CNotGate* newGate = new CNotGate(0, 0, ++_level, pos1[i]);
      circuit.addGate(newGate);
   }
}


void Synthesis::rectify(Circuit& circuit, const size_t& current, const size_t& target) {
   static vector<size_t> target_pos1;
   static vector<size_t> diff_pos;
   static vector<size_t> temp_pos1;

   // No need to rectify
   if (current == target) return;

   size_t diff = current ^ target;
   positions_1(diff_pos, diff, _nInputs);
   positions_1(temp_pos1, current, _nInputs);
   positions_1(target_pos1, target, _nInputs);

   // Rectify 0 to 1
   CNotGate* newGate = 0;
   for (size_t i = 0, n = diff_pos.size(); i < n; ++i) {
      if (target & (CONST1 << diff_pos[i])) {
         // Get new gate
         newGate = new CNotGate(0, 0, ++_level, diff_pos[i]);
         for (size_t j = 0, m = temp_pos1.size(); j < m; ++j) 
            newGate->addControlLine(temp_pos1[j]);
         circuit.addGate(newGate);

         // Get new one
         temp_pos1.push_back(diff_pos[i]);
      }
   }

   // Rectify 1 to 0
   for (size_t i = 0, n = diff_pos.size(); i < n; ++i) {
      if (!(target & (CONST1 << diff_pos[i]))) {
         // Get new gate
         newGate = new CNotGate(0, 0, ++_level, diff_pos[i]);
         for (size_t j = 0, m = target_pos1.size(); j < m; ++j) 
            newGate->addControlLine(target_pos1[j]);
         // Add to circuit
         circuit.addGate(newGate);
      }
   }
}


void Synthesis::printHwGrp() const {
   printHeader(cerr, "Hamming Weight Group");
   for (size_t i = 0 ; i < _hwGrp.size(); ++i)
      for (size_t j = 0; j < _hwGrp[i].size(); ++j)
         cerr << "[" << i << "] "  << _hwGrp[i][j] << " "
              << "(" << bitString(_hwGrp[i][j], _nInputs) << ")" 
              << endl;
   cerr << endl;
}


