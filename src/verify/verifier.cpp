/****************************************************************************
   FileName     [ verifier.cpp ]
   PackageName  [ verify ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Verifier class definition. Verify spec and revCkt. ]
   Date         [ 2018/1/13 created ]
****************************************************************************/

#include "verifier.h"

using namespace std;

bool Verifier::verify() {
   Model model(_circuit.nInputs());
   
   vector<size_t> simValues;
   simValues.resize(_spec.size());

   size_t cnt_period = 0; // miner counter for SIZET_SIZE period
   size_t cnt_total  = 0; // total counter
   size_t startIdx   = 0;
   size_t endIdx     = 0;
   size_t i          = 0;
   size_t j          = 0;
   size_t specSize   = _spec.size();

   // Parallel simulation (bitwise pattern)
   while (cnt_total < specSize) {

      // Set startIdx and endIdx
      startIdx   = cnt_total;
      endIdx     = startIdx;
      cnt_period = 0;

      for (cnt_period = 0; cnt_period < SIZET_SIZE; ++cnt_period) {

         // Terminate if no more inputs
         if (cnt_total >= specSize) {
            endIdx = specSize;
            break;
         }

         // Set sim value to model
         model.setConcatenateValue(cnt_period, cnt_total);

         // Update counter
         ++cnt_total;
         ++endIdx;
      }

      // collect sim result
      Model retModel = _circuit.simulate(model);
      for (i = startIdx, j = 0; i < endIdx; ++i, ++j) {
         simValues[i] = retModel.getConcatenateValue(j);
      }
   }

   // Check equivalence
   printHeader(cerr, "Verification");
   bool fCorrect = true;
   for (i = 0; i < specSize; ++i) {
      if (_spec[i] != simValues[i]) {
         if (fCorrect) cerr << "> Error pattern ( i -> o | spec ) : " << endl;
         cerr << "  "
              << bitString(i           , _circuit.nInputs()) << " -> " 
              << bitString(simValues[i], _circuit.nInputs()) << " | "
              << bitString(_spec[i]    , _circuit.nInputs()) << endl;
         fCorrect = false;
      }
   }

   // Show success msg
   if (fCorrect)
      cerr << "> Spec and circuit are matched!!" << endl;
   cerr << endl;

   return fCorrect;
}
