/****************************************************************************
   FileName     [ gnuplotter.cpp ]
   PackageName  [ gnuplot ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Gnuplotter class definition. Plot revCkt. ]
   Date         [ 2018/1/13 created ]
****************************************************************************/

#include "gnuplotter.h"
#include "gnuplot_i.h"

using namespace std;

void Gnuplotter::liveGnuplot(const Circuit& circuit) {
   printHeader(cout, "Live Gnuplot");

   Gnuplot gnu;
  
   gnu << gnuplotStr(circuit);
   cerr << "Press ENTER to continue ...\n";
   cin.get();
}


void Gnuplotter::outputGnuplot(const string& fileName, const Circuit& circuit) {
   printHeader(cout, "Output Gnuplot format");
   ofstream fout(fileName.c_str(), ios::out);
   if (!fout) {
      cerr << "> Error: Cannot open plt file \"" << fileName << "\".\n";
      return;
   }

   fout << "set title \"" << fileName << "\"\n";
   fout << gnuplotStr(circuit);
   fout.close();

   cout << "> Output circuit in gnuplot format to \"" << fileName << "\".\n";
   cout << endl;
}

string Gnuplotter::gnuplotStr(const Circuit& circuit) {

   #define LINE_SPACE 30
   #define GATE_SPACE 30
   #define BOUNDRY_SPACE 60

   string ret = "";
   
   // ret += "set terminal X11\n"; 
   // init
   // ret << ("set title \"" + string(cirFile) + "\" \n") ;

   size_t width = (GATE_SPACE*circuit.nGateWidth() + BOUNDRY_SPACE);
   size_t height = (LINE_SPACE*circuit.nLines() + BOUNDRY_SPACE - LINE_SPACE);

   ret += "set xrange[-1:" +  to_string(width) + "]\n" ;
   ret += "set yrange[-1:" +  to_string(height) + "]\n" ;
   ret += "unset border\n";
   ret += "unset xtics\n";
   ret += "unset ytics\n";
   ret += "set format x \"\"\n";
   ret += "set format y \"\"\n";
   ret += "set size ratio -1\n";

   // Lines   
   for (size_t i = 0, n = circuit.nLines(); i < n; ++i) {
      stringstream ssi, ssx1, ssx2, ssy, ssl;
      // ssi << cnt;
      ssx1 << (BOUNDRY_SPACE / 2);
      ssx2 << width - (BOUNDRY_SPACE / 2);
      ssy <<  height - (BOUNDRY_SPACE / 2) - i * LINE_SPACE;
      //_plt << ("set arrow " +  ssi.str() + " from "
      ret +=  ("set arrow from " 
               + ssx1.str() + "," + ssy.str() + " to " + ssx2.str() + "," + ssy.str() 
               + " lc rgb \"gray\" nohead back\n");

      ssl << (BOUNDRY_SPACE / 4);
      ret += ("set label \"" + circuit._lineNames[i] + "\""
               + " at " + ssl.str() + "," + ssy.str() + "\n");
   }

   // Gates
   size_t idx = 0;
   Gate* g = 0;
   const list<Gate*>& gates = circuit.gates();
   for (auto iter = gates.begin(); iter != gates.end(); ++iter) {
      g = *iter;
      switch( g->type() ) 
      {
         case CNOT_GATE:
         {
            // not
            size_t this_no = g->lineNo();
            size_t max_no = this_no;
            size_t min_no = this_no;
            
            size_t x = (BOUNDRY_SPACE + GATE_SPACE ) / 2 + idx * GATE_SPACE;
            size_t y = height - (BOUNDRY_SPACE / 2) - this_no * LINE_SPACE;
            for (size_t i = 0; i < 4; ++i) {
               ret += ("set object circle arc [  " + to_string(90*i) + " :  " + to_string(90*(i+1)) + "] at first " 
                       + to_string(x) + "," + to_string(y) + " radius char 1.2 fillstyle empty border lc rgb '#000000' lw 1 front\n");
            }
            // ctrl
            for (size_t i = 0; i < ((CNotGate*)g)->nCtrl(); ++i) {
               this_no = ((CNotGate*)g)->getCtrl(i);
               max_no = max(this_no, max_no);
               min_no = min(this_no, min_no);
               y = height - (BOUNDRY_SPACE / 2) - this_no * LINE_SPACE;
               ret += ("set object circle at first " + to_string(x) + "," + to_string(y)
                       + " radius char 0.8 fs solid 1 front fc rgb '#000000 ' \n");
            }
            // gate line
            ret += ("set arrow from "
                    + to_string(x) + "," + to_string(height - (BOUNDRY_SPACE / 2) - max_no * LINE_SPACE) 
                    + " to "+ to_string(x) + "," + to_string(height - (BOUNDRY_SPACE / 2) - min_no * LINE_SPACE) 
                    + " lc rgb '#000000' nohead  front \n");
            break;
         }
         case FREDKIN_GATE:
         {
            Gate* g1 = g;
            Gate* g2 = *(++iter);
           
            size_t g1_no = g1->lineNo();
            size_t g2_no = g2->lineNo();

            size_t x = (BOUNDRY_SPACE + GATE_SPACE ) / 2 + idx * GATE_SPACE;
            size_t y1 = height - (BOUNDRY_SPACE / 2) - g1_no * LINE_SPACE;
            size_t y2 = height - (BOUNDRY_SPACE / 2) - g2_no * LINE_SPACE;

            // erase line
            ret += ("set arrow from "
                    + to_string(x) + "," + to_string(y1) + " to "+ to_string(x+GATE_SPACE) + "," + to_string(y1) 
                    + " lc rgb '#ffffff' nohead  front \n");

            ret += ("set arrow from "
                    + to_string(x) + "," + to_string(y2) + " to "+ to_string(x+GATE_SPACE) + "," + to_string(y2) 
                    + " lc rgb '#ffffff' nohead  front \n");
            // add X shape swap line
            ret += ("set arrow from "
                    + to_string(x) + "," + to_string(y1) + " to "+ to_string(x+GATE_SPACE) + "," + to_string(y2) 
                    + " lc rgb '#000000' nohead  front \n");

            ret += ("set arrow from "
                    + to_string(x) + "," + to_string(y2) + " to "+ to_string(x+GATE_SPACE) + "," + to_string(y1) 
                    + " lc rgb '#000000' nohead  front \n");
            
            x +=  ( GATE_SPACE/2 );

            if ( ( (FredkinGate*)g )->nCtrl() != 0 ) {
               size_t max_no = 0;
               size_t min_no = circuit.nLines();
               size_t this_no;
             
               for (size_t i = 0; i < ((FredkinGate*)g)->nCtrl(); ++i) {
                  this_no = ((FredkinGate*)g)->getCtrl(i);
                  max_no = max(this_no, max_no);
                  min_no = min(this_no, min_no);
                  size_t y = height - (BOUNDRY_SPACE / 2) - this_no * LINE_SPACE;
                  ret += ("set object circle at first " + to_string(x) + "," + to_string(y)
                          + " radius char 0.8 fs solid 1 front fc rgb '#000000 ' \n");
               }

               ret += ("set arrow from "
                    + to_string(x) + "," 
                    + to_string(min((height - (BOUNDRY_SPACE / 2) - max_no * LINE_SPACE), (y1+y2)/2)) 
                    + " to "+ to_string(x) + "," 
                    + to_string(max((height - (BOUNDRY_SPACE / 2) - min_no * LINE_SPACE), (y1+y2)/2))
                    + " lc rgb '#000000' nohead  front \n"); 
            }
             
            // skip second gate
            ++idx;
            break;
         }
         default:
            break;
      }
      ++idx;
   }
      
   ret += " plot \'-\' using 1:2 t \"\" with line\n";
   ret += " 0 0\n";
   ret += " e\n";
   ret += " pause -1\n";
   
   return ret;
}