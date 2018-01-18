/**HeaderFile**********************************************************

  FileName    [util.hpp]

  SystemName  [NTUdr: Academic Detailed Router.]

  PackageName [misc: Useful utils.]

  Synopsis    [util functions declaration]

  Author      [Hao Chen]
  
  Affiliation [NTU]

  Date        [26, Dec., 2017.]

***********************************************************************/

#ifndef UTIL_HPP
#define UTIL_HPP

#include "global.hpp"

using namespace std;

// show sys info
// extern void          showSysInfo();

// Msg Header
extern void          printHeader(ostream&, const string&);

// filename
extern bool          existFile (const std::string& filename);
extern std::string   getFileDirName(const std::string& filePathName);
extern std::string   getFileName(const std::string& filePathName);

// memory
extern double        getPeakMemoryUsage();
extern double        getCurrMemoryUsage();
extern void          showMemoryUsage(bool flag);

// string
extern bool          myStr2Int(const string&, int&);
extern size_t        myStrGetTok(const string&, string&, size_t pos, const char del);

// bitwise operation
extern string        bitString(const size_t&, const size_t);
extern bool          completeLog2(size_t, size_t&);
extern void          positions_1(vector<size_t>&, size_t, size_t);
extern void          positions_0(vector<size_t>&, size_t, size_t);
extern void          positions_diff(vector<size_t>&, size_t, size_t, size_t);
extern void          positions_10(vector<size_t>&, size_t, size_t, size_t);
extern void          positions_01(vector<size_t>&, size_t, size_t, size_t);
extern size_t        num_10(size_t, size_t, size_t);
extern size_t        num_01(size_t, size_t, size_t);
extern size_t        hammingDist(const size_t, const size_t, const size_t);
extern size_t        hammingWeight(size_t, const size_t);

#endif // UTIL_HPP