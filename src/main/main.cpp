/****************************************************************************
   FileName     [ main.cpp ]
   PackageName  [ main ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Main function ]
   Date         [ 2018/1/5 created ]
****************************************************************************/

#include <iostream>

#include "paramHandler.hpp"
#include "argHandler.hpp"
#include "global.hpp"
#include "parser.h"
#include "spec.h"
#include "util.hpp"
#include "circuit.h"
#include "synthesis.h"
#include "verifier.h"
#include "gnuplotter.h"

using namespace std;

ParamHandler gParam;

int main(int argc, char** argv)
{
   ArgHandler(argc, argv, gParam);

   gParam.printParamInfo();

   // Parse
   Spec spec;
   Parser parser;
   parser.parseSpecFile(gParam.specName, spec);
   // spec.printSpec();

   // Synthesis
   Circuit circuit(spec.nInputs(), spec.nOutputs());
   Synthesis syn(spec, circuit);
   syn.synthesis_bi_nctsf();

   // Output tfc file
   circuit.outputTfcFile(gParam.outName);

   // Show circuit info
   circuit.printCircuitInfo();

   // Verify
   Verifier verifier(circuit, spec);
   verifier.verify();

   // Plot 
   if (gParam.fPlot) {
      Gnuplotter gnuplotter;
      if (gParam.pltName == "")
         gnuplotter.liveGnuplot(circuit);
      else
         gnuplotter.outputGnuplot(gParam.pltName, circuit);
   }

   // // Output to size.log
   // fstream fout("size.log", ios::app);
   // if (fout) {
   //    fout << circuit.nGates() << endl;
   //    fout.close();
   // }
   // fout.open("ctrl.log", ios::app);
   // if (fout) {
   //    fout << circuit.nTotalCtrl() << endl;
   //    fout.close();
   // }

   return 0;
}

