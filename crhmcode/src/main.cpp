//#include "stdafx.h"
#include "core/CRHMArguments.h"

int main(int argc, char *argv[])
{
    //Declare the object for arguments.
    CRHMArguments * arguments = new CRHMArguments();

    arguments->readCommandLine(argc, argv);
    arguments->validate();

    //Create main object with the given arguments.
    CRHMmain* m = new CRHMmain(arguments);

    std::string projectArgument = arguments->get_project_name();
    m->OpenNamePrj = projectArgument;

    if (m->DoPrjOpen(projectArgument, ""))
    {
      m->RunClick();
    }
    else
    {
      std::cout << "Error encountered while loading the project. Check log file for more detail.";
    }

}