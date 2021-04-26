#include "DefCRHM.h"

Defdeclparam::Defdeclparam(ClassMacro* Macro_) : DefCRHM(Macro_) {

	if (DefStringList->Strings[0] == "decldiagparam")
		visibility = TVISIBLE::DIAGNOSTIC;
	else
		visibility = TVISIBLE::USUAL;

	name = DefStringList->Strings[1];
	Dim = getTDim(DefStringList->Strings[2]);
	Default = DefStringList->Strings[3];
	Min = DefStringList->Strings[4];
	Max = DefStringList->Strings[5];
	Description = DefStringList->Strings[6];
	Units = DefStringList->Strings[7];

	if (DefCRHM::DefStringList->Count > 8 && DefStringList->Strings[8] == "Int")
		Int = true;
	else
		Int = false;

	if (DefCRHM::DefStringList->Count > 9)
		nlay = Strtolong(DefStringList->Strings[9]);
}


void Defdeclparam::CallDecl() {

	if (Int)
		Macro->declparam(name, Dim, Default, Min, Max, Description, Units, &fix_long_const, &fix2_long_const, nlay, visibility);
	else
		Macro->declparam(name, Dim, Default, Min, Max, Description, Units, &fix_const, &fix2_const, Macro->nhru, visibility);

	if (Global::BuildFlag == TBuild::INIT) {
		FP = Macro->vars.find(name);
		if (FP == Macro->vars.end()) {
			Macro->vars.insert(make_pair(name, VarCHRM()));
			FP = Macro->vars.find(name);
		}

		FP->second.name = name;
		FP->second.Ihh = 0;
		FP->second.IndexMax = Macro->nhru - 1;
		FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
		FP->second.Me = Macro;

		if (Int) {
			if (Dim == TDim::NDEF || Dim == TDim::NDEFN) {
				FP->second.kind = TV::CRHMint2;
				FP->second.ivalue2 = const_cast<long**> (fix2_long_const);
			}
			else {
				FP->second.kind = TV::CRHMint;
				FP->second.ivalue = const_cast<long*> (fix_long_const);
			}
		}
		else {
			if (Dim == TDim::NDEF || Dim == TDim::NDEFN) {
				FP->second.kind = TV::CRHM2;
				FP->second.value2 = const_cast<double**> (fix2_const);
			}
			else {
				FP->second.kind = TV::CRHM;
				FP->second.value = const_cast<double*> (fix_const);
			}
		}
	}
}

void Defdeclparam::CallInit(long nhru, long nlay) {
}