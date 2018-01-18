/****************************************************************************
   FileName     [ argHandler.cpp ]
   PackageName  [ misc ]
   Author       [ Chen-Hao Hsu, Yi-Ting Lin ]
   System       [ Reverisble Circuit Synthesis ]
   Synopsis     [ Handle argc argv. Store the info to gParam ]
   Date         [ 2018/1/5 created ]
****************************************************************************/

#ifndef ARGHANDLER_HPP
#define ARGHANDLER_HPP

#include <cstdlib>
#include <iostream>
#include <string>

#include "global.hpp"
#include "paramHandler.hpp"

class ArgHandler {
public:
  ArgHandler(int argc, char** argv, ParamHandler& gParam);
  ~ArgHandler() {}
};

#endif // ARGHANDLER_HPP