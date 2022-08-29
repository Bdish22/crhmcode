/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassNOP.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassNOP* ClassNOP::klone(string name) const{
  return new ClassNOP(name);
}

void ClassNOP::decl(void) {

  Description = "'NO operation module. Use only in macro declstruct as filler.'";

}

void ClassNOP::init(void) {

}

void ClassNOP::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessage(hh, string("'" + Name + " (NOP)'").c_str(), TExtra::BLANK);
  }
  LogDebug(" ");
}
