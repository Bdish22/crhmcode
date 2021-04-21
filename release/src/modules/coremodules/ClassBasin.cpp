//created by Manishankar Mondal

#include "ClassBasin.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM/ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

Classbasin* Classbasin::klone(string name) const{
  return new Classbasin(name);
}

void Classbasin::decl(void) {

  Description = "'Holds commonly used physical and control parameters.'";

  decldiagparam("RUN_ID", TDim::BASIN, "1", "-1E8", "+1E8", "run identification. If RUN_ID > 0 then the log file default name 'CRHM_output' with extensions .sum, .log OR .txt is expanded to 'CRHM_output_ID'.", "()", &RUN_ID);

  decldiagparam("RUN_START", TDim::BASIN, "0", "0", "+1E5", "run start time (Automation)", "(d)", &RUN_START);

  decldiagparam("RUN_END", TDim::BASIN, "0", "0", "+1E5", "run end time (Automation)", "(d)", &RUN_END);

  INIT_STATE = decldiagparam("INIT_STATE", TDim::BASIN, "", "Initial state file (Automation)", INIT_STATE);


  declvar("run_ID", TDim::BASIN, "run identification", "()", &run_ID);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("hru_lat", TDim::NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(" + string(DEGREE) + ")", &hru_lat);

  declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  declparam("hru_GSL", TDim::NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string(DEGREE) + ")", &hru_GSL);

  declparam("hru_ASL", TDim::NHRU, "0.0", "0.0", "360.0", "aspect, 0/90/180/270 - north/east/south/west facing for positive GSL.", "(" + string(DEGREE) + ")", &hru_ASL);


  hru_names = declparam("hru_names", TDim::NHRU, "'HRU'", "HRU names", hru_names);

  basin_name = declparam("basin_name", TDim::BASIN, "Basin", "Basin name", basin_name);

  RapidAdvance_to = decldiagparam("RapidAdvance_to", TDim::ONE, "' ', ' ', ' '", "Rapid advance to this date formatted as 'mm/dd/yyyy'", RapidAdvance_to);

  Loop_to = decldiagparam("Loop_to", TDim::TWO, "' ', ' '", "loop to this date formatted as 'mm/dd/yyyy', 0 - # loops", Loop_to);

  StateVars_to_Update = decldiagparam("StateVars_to_Update", TDim::TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "run up these state variables.",  StateVars_to_Update);

  TraceVars = decldiagparam("TraceVars", TDim::TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "Trace these variables at end of loop during run up.",  TraceVars);
}

void Classbasin::init(void) {

  run_ID[0] = RUN_ID[0];  // transfer run identification

  double totarea = 0;
  nhru = getdim(TDim::NHRU);

  for(hh = 0; hh < nhru; ++hh)
    totarea += hru_area[hh];

  if(fabs((totarea-basin_area[0])/basin_area[0]) > 1e-3){
    const_cast<double *>  (basin_area)[0] = totarea;
    CRHMException TExcept(string(string("Sum of HRU's area <> Basin area, Basin area made = ") + FloatToStrF(totarea, TFloatFormat::ffGeneral, 3, 0)).c_str(), TExcept::WARNING);
    LogError(TExcept);
  }

  Global::RapidAdvanceTo = 0;
  Global::LoopTo = 0;
  Global::LoopCnt = 0;

  try{
	  if (RapidAdvance_to->Count > 0)
	  {
		  RapidAdvance_to->Strings[0] = Common::trim(RapidAdvance_to->Strings[0]);

		  if (RapidAdvance_to->Strings[0].length() > 0) 
		  {
			  
			  if (RapidAdvance_to->Strings[0].length() > 0)
			  {
				  Global::RapidAdvanceTo = StrToDate(RapidAdvance_to->Strings[0]);
			  }
				  
		  }
	  }
	  if (Loop_to->Count > 1)
	  {
		  Loop_to->Strings[0] = Common::trim(Loop_to->Strings[0]);
		  Loop_to->Strings[1] = Common::trim(Loop_to->Strings[1]);

		  if (Loop_to->Strings[0].length() > 0) 
		  {
			  
			  if (Loop_to->Strings[0].length() > 0)
			  {
				  Global::LoopTo = StrToDate(Loop_to->Strings[0]);
			  }  
			  if (Loop_to->Strings[1].length() > 0)
			  {
				  Global::LoopCnt = Strtolong(Loop_to->Strings[1]);
			  }
				  
		  }
	  }
  }

  catch (...){
    CRHMException TExcept("Error in 'RapidAdvance_to' or 'Loop_to' parameters", TExcept::TERMINATE);
    LogError(TExcept);
    Global::RapidAdvanceTo = 0;
    Global::LoopTo = 0;
    Global::LoopCnt = 0;
  }
}