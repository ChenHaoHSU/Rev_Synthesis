/**HeaderFile**********************************************************

  FileName    [paramHandler.hpp]

  SystemName  [NTUdr: Academic Detailed Router.]

  PackageName [misc: Useful utils.]

  Synopsis    [global parameters]

  Author      [Hao Chen]
  
  Affiliation [NTU]

  Date        [26, Dec., 2017.]

***********************************************************************/

#ifndef PARAMHANDLER_HPP
#define PARAMHANDLER_HPP

#include "global.hpp"
#include "paramHandler.hpp"
#include "util.hpp"

using namespace std;

class ParamHandler {
public:
   ParamHandler() : specName(""), outName(""), pltName(""), fPlot(false) {}
   ~ParamHandler() {}

   // Data mamber
   // string mode;
   string specName;
   string outName;
   string pltName;
   bool   fPlot;

   // Public methods
   void printParamInfo() const
   {
      printHeader(cout, "Parameter");
      cout << "> Specification file : " << specName               << endl;
      cout << "> Output file        : " << outName                << endl;
      cout << "> Plot               : " << (fPlot ? "ON" : "OFF") << endl;
      cout << endl;
   }

};


#endif // PARAMHANDLER_HPP