//created by Manishankar Mondal

#include "ClassModule.h"

class ClassMeltRunoff_Lag : public ClassModule {
public:

ClassMeltRunoff_Lag(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module{ NULL }; // used to call preser for simple projects

// declared variables
double *In_Lagstorage{ NULL };
long *Tf{ NULL };

// get variables:
const double *snowmelt_int{ NULL };

// put variables
double *runLag{ NULL };

// declared parameters
const double *hru_area{ NULL };
const long  *inhibit_MeltRunoff_Lag{ NULL };

void decl(void);
void init(void);
void run(void);

ClassMeltRunoff_Lag* klone(string name) const;
};