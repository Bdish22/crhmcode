//created by Manishankar Mondal

#include "ClassModule.h"


class ClassGreencrack : public ClassModule {
public:

ClassGreencrack(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
double *infil{ NULL };
double *cuminfil{ NULL };
double *meltrunoff{ NULL };
double *cummeltrunoff{ NULL };
double *runoff{ NULL };
double *cumrunoff{ NULL };
double *snowinfil{ NULL };
double *cumsnowinfil{ NULL };
long  *crackstat{ NULL };
long  *crackon{ NULL };
double *RainOnSnow{ NULL };
double *RainOnSnowA{ NULL };

// local variables
double *k{ NULL };
double *F0{ NULL };
double *f0{ NULL };
double *F1{ NULL };
double *f1{ NULL };
double *dthbot{ NULL };
double *psidthbot{ NULL };
long  *timer{ NULL };

// declared parameters
const double *basin_area{ NULL }; // [BASIN]
const double *hru_area{ NULL };
const double *fallstat{ NULL };
const double *Major{ NULL };      // threshold for major melt event(default is 5 mm/day)
const double *soil_moist_max{ NULL };
const double *soil_moist_init{ NULL };
const long  *soil_type{ NULL };
const long  *PriorInfiltration{ NULL };

// variable inputs
const double *hru_tmax{ NULL };
const double *snowmelt{ NULL };
const double *SWE{ NULL };
const double *net_rain{ NULL };
double *soil_moist{ NULL }; // changed tp PUT

// class allocated
double garain {0.0};      // precipitation/int
double intensity  {0.0};    // precipitation/int converted to mm/h
double pond{ 0.0 };        // mm

// class allocated arrays
double **Xinfil{ NULL }; // [3] [nhru]

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreencrack* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(double F0, double dt);

double calcf1(double F, double psidth);
};