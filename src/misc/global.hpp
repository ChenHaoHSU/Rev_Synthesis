/**HeaderFile**********************************************************

  FileName    [global.hpp]

  SystemName  [NTUdr: Academic Detailed Router.]

  PackageName [misc: Useful utils.]

  Synopsis    [global]

  Author      [Hao Chen]
  
  Affiliation [NTU]

  Date        [3, Jan., 2018.]

***********************************************************************/

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <cstdarg>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <limits>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <list>
#include <algorithm>
#include <map>

////////////////////////////////////////////////////////////////////////
///                          PLATFORMS                               ///
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
///                          CONSTANT                                 ///
////////////////////////////////////////////////////////////////////////

constexpr double    TIME_SCALE   = 1000000.0;
constexpr double    MEMORY_SCALE = 1024.0;
constexpr size_t    CONST0       = 0x0;
constexpr size_t    CONST1       = 0x1;
constexpr size_t    ALL1         = ~(0x0);
constexpr size_t    BYTE_SIZE    = 8;
constexpr size_t    SIZET_SIZE   = sizeof(size_t) * BYTE_SIZE;

////////////////////////////////////////////////////////////////////////
///                          TYPEDEF                                 ///
////////////////////////////////////////////////////////////////////////


#endif // GLOBAL_HPP

