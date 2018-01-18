/****************************************************************************
   FileName     [ argHandler.cpp ]
   PackageName  [ misc ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Handle argc argv. Store the info to gParam ]
   Date         [ 2018/1/5 created ]
****************************************************************************/

#include "util.hpp"
#include "argHandler.hpp"

using namespace std;

extern ParamHandler gParam;


inline void printUsage() {
  printHeader(cout, "Usage");
  cerr << "Usage: ./revSyn -spec <spec_file_name> -output <tfc_file_name> [-plt]" << endl;
  cerr << "Example: ./revSyn -spec case1.spec -output case1.tfc -plt            " << endl;
  cerr << "Options:                                                             " << endl;
  cerr << "  -h, --help : show help messege                                     " << endl;
  cerr << "  -spec      : function specification file                           " << endl;
  cerr << "  -output    : output tfc file                                       " << endl;
  cerr << "  -plt       : output Gnuplot format file                            " << endl;
  cerr << endl;
  exit(0);
}


ArgHandler::ArgHandler(int argc, char** argv, ParamHandler& gParam) {
  int i = 0;
  if (argc == 1) printUsage();
  while(++i < argc) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printUsage();
    }
    else if (strcmp(argv[i], "-spec") == 0) {
      if (++i >= argc) printUsage();
      gParam.specName = argv[i];
    }
    else if (strcmp(argv[i], "-output") == 0) {
      if (++i >= argc) printUsage();
      gParam.outName = argv[i];
    }
    else if (strcmp(argv[i], "-plt") == 0) {
      gParam.fPlot = true;
      if (++i < argc)
        gParam.pltName = argv[i];
      else 
        --i;
    }
    else printUsage();
  }

  if (!existFile(gParam.specName)) {
    cerr << "Error: spec file \"" << gParam.specName << "\" does not exist." << endl;
    printUsage();
  }
}

