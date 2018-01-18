/**CPPFile**************************************************************

  FileName    [main.cpp]

  SystemName  [NTUdr: Academic Detailed Router.]

  PackageName [misc: Useful utils.]

  Synopsis    [util functions definition]

  Author      [Hao Chen]
  
  Affiliation [NTU]

  Date        [26, Dec., 2017.]

***********************************************************************/

#include <sys/stat.h>

#include "util.hpp"
#include "global.hpp"

using namespace std;


// Msg Header
void printHeader(ostream& os, const string& title) {
  const int totalLen = 69;
  int rest = max(0, totalLen - (int)title.length() - 3); // 3 = len("= ") + len(" ")
  os << endl;
  // Top line
  for (int i = 0; i < totalLen; ++i) os << "=";
  os << endl;
  // Middle Line
  os << "= " << title << " ";
  for (int i = 0; i < rest - 1; ++i) os << " ";
  os << "=" << endl;
  // Bottom Line
  for (int i = 0; i < totalLen; ++i) os << "=";
  os << endl;
}


// filename
bool existFile (const string& filename) {
  struct stat buffer;   
  return stat(filename.c_str(), &buffer) == 0; 
}

string getFileDirName(const string& filePathName) {
  string retStr = filePathName;
  string::size_type pos = retStr.rfind("/");
  if (pos != string::npos)
    retStr = retStr.substr(0, pos);
  return retStr;
}

string getFileName(const string& filePathName) {
  string retStr = filePathName;
  string::size_type pos = retStr.rfind("/");
  if (pos != string::npos)
    retStr = retStr.substr(pos + 1);
  return retStr;
}

// memory
double getPeakMemoryUsage() {
#ifdef __linux__
  FILE* fmem = fopen("/proc/self/status", "r");
  char membuf[128];
  double vmPeak = 0;
  while (fgets(membuf, 128, fmem)) {
    char* ch;
    if ((ch = strstr(membuf, "VmPeak:"))) {
      vmPeak = atol(ch + 7);
      continue;
    }
  }
  fclose(fmem);
  return vmPeak;
#else
  return -1;
#endif
}

double getCurrMemoryUsage() {
#ifdef __linux__
  FILE* fmem = fopen("/proc/self/status", "r");
  char membuf[128];
  double vmSize = 0;
  while (fgets(membuf, 128, fmem)) {
    char* ch;
    if ((ch = strstr(membuf, "VmSize:"))) {
      vmSize = atol(ch + 7);
      break;
    }
  }
  fclose(fmem);
  return vmSize;
#else
  return -1;
#endif
}

void showMemoryUsage(bool flag) {
  if (flag)
    fprintf(stderr, "Peak Memory Usage: %f MB\n", getPeakMemoryUsage() / MEMORY_SCALE);
  else
    fprintf(stderr, "Curr Memory Usage: %f MB\n", getCurrMemoryUsage() / MEMORY_SCALE);
}

// string
bool myStr2Int(const string& str, int& num)
{
   num = 0;
   size_t i = 0;
   int sign = 1;
   if (str[0] == '-') { sign = -1; i = 1; }
   bool valid = false;
   for (; i < str.size(); ++i) {
      if (isdigit(str[i])) {
         num *= 10;
         num += int(str[i] - '0');
         valid = true;
      }
      else return false;
   }
   num *= sign;
   return valid;
}

size_t myStrGetTok(const string& str, string& tok, size_t pos = 0,
                   const char del = ' ')
{
   size_t begin = str.find_first_not_of(del, pos);
   if (begin == string::npos) { tok = ""; return begin; }
   size_t end = str.find_first_of(del, begin);
   tok = str.substr(begin, end - begin);
   return end;
}


// bitwise operation
string bitString(const size_t& num, const size_t length) {
  string str = "";
  size_t num_copy = num;
  for (size_t i = 0; i < length; ++i) {
    if (num_copy & CONST1) str = "1" + str; 
    else str = "0" + str; 
    num_copy >>= 1;
  }
  return str;
}


bool completeLog2(size_t n, size_t& log2_n) {
  // Return true if n is 2^k. (k is int)
  // Return false, otherwise.
  assert(n >= 1);
  double l = log2((double)n);
  double floor_l = floor(l);
  log2_n = (size_t)floor_l;
  return (floor_l == l);
}


size_t hammingWeight(size_t n, const size_t len) {
  size_t weight = 0;
  for (size_t i = 0; i < len; ++i) {
    if (n & CONST1) ++weight;
    n >>= 1;
  }
  return weight;
}


void positions_1(vector<size_t>& v, size_t number, size_t len) {
  v.resize(0);
  for (size_t i = 0; i < len; ++i) {
    if (number & CONST1)
      v.push_back(i);
    number >>= 1;
  }
}


void positions_0(vector<size_t>& v, size_t number, size_t len) {
  v.resize(0);
  for (size_t i = 0; i < len; ++i) {
    if (!(number & CONST1))
      v.push_back(i);
    number >>= 1;
  }
}


void positions_diff(vector<size_t>& v, size_t n1, size_t n2, size_t len) {
  // Return positions where n1[p] != n2[p]
  v.resize(0);
  size_t diff = n1 ^ n2;
  for (size_t i = 0; i < len; ++i) {
    if (diff & CONST1)
      v.push_back(i);
    diff >>= 1;
  }
}


void positions_10(vector<size_t>& v, size_t n1, size_t n2, size_t len) {
  // Return positions where n1[p] = 1 and n2[p] = 0
  v.resize(0);
  size_t diff = (n1 ^ n2) & n1;
  for (size_t i = 0; i < len; ++i) {
    if (diff & CONST1)
      v.push_back(i);
    diff >>= 1;
  }
}


void positions_01(vector<size_t>& v, size_t n1, size_t n2, size_t len) {
  // Return positions where n1[p] = 0 and n2[p] = 1
  v.resize(0);
  size_t diff = (n1 ^ n2) & n2;
  for (size_t i = 0; i < len; ++i) {
    if (diff & CONST1)
      v.push_back(i);
    diff >>= 1;
  }
}


size_t num_10(size_t n1, size_t n2, size_t len) {
  // Return #positions where n1[p] = 1 and n2[p] = 1
  size_t total = 0;
  size_t diff = (n1 ^ n2) & n1;
  for (size_t i = 0; i < len; ++i) {
    if (diff & CONST1)
      ++total;
    diff >>= 1;
  }
  return total;
}

size_t num_01(size_t n1, size_t n2, size_t len) {
  // Return positions where n1[p] = 0 and n2[p] = 1
  size_t total = 0;
  size_t diff = (n1 ^ n2) & n2;
  for (size_t i = 0; i < len; ++i) {
    if (diff & CONST1)
      ++total;
    diff >>= 1;
  }
  return total;
}


size_t hammingDist(const size_t num1, const size_t num2, const size_t len) {
  size_t diff = num1 ^ num2;
  size_t cnt = 0;
  for (size_t i = 0; i < len; ++i) {
    if (CONST1 & diff) ++cnt;
    diff >>= 1;
  }
  return cnt;
}