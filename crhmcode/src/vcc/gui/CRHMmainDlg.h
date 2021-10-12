// Library includes
#include "stdafx.h"
#include "afxdialogex.h"
#include "CSeries.h"
#include "CTChart.h"
// Source includes
#include "../../core/CRHMmain/CRHMmain.h"
#include "ClassCRHM.h"
#include "CRHM_GUI.h"
#include "CRHMAboutBox.h"
#include "MacroEntryDlg.h"
#include "FlowDiagramDlg.h"
#include "CReport.h"
#include "CConstruct.h"
#include "RightClickListBox.h"
// Defines
#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)

#pragma once
 
/**
* The main CRHM dialog window class
* CRHMmainDlg defines the main dialog window for the application. 
* This dialog handles the main menu and supports loading, saving, and running projects.
* It is a descendant of the CDialogEx class.  
*/
class CRHMmainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRHMmainDlg)	

public:

	CRHMmainDlg(CWnd* pParent = nullptr); /**< Standard constructor */
	virtual ~CRHMmainDlg(); /**< Standard destructor */

	/**
	* Constructor that takes in a project file name and runs that
	*	project after opening
	*
	* @param argumentfile std::string path to a project file.
	*/
	CRHMmainDlg(std::string argumentfile);

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = CRHMmainDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	long Box1Disply{ 0 };
	long ObsFunct_Toggle = 0; /**< no display/Final/Trend values */
	long TBase{ 0 };
	long water_year_month = 10; /**< Specifies the month to signal end of water year. Default is October.*/

	std::string ProjectFileArgument = ""; /**< it takes the filename from the command line. */
	std::string defaultprojectname = "currentproject.prj";
	std::string defaultprojectpath = "currentproject.prj";
	std::string defaultobservationpath = "obs/Badlake73_76.obs";
	std::string TBases[5] = { "Daily", "Water_year", "Calendar_year", "Monthly_summary", "Summarize_all" };

	/**
	* List box for all variables in the loaded project
	* List box that contains a string for each variable available
	*	for output in the currently loaded project.
	* 
	* The control ID is ID_ALL_VAR_LIST_BOX
	* The list box is defined in the resource file CRHMGUI.rc
	*/
	CListBox listbox_all_variables;

	/**
	* List box for all variables that have been selected for output.
	* List box that contains a string for each variable to be output.
	*
	* The control ID is ID_SEL_VAR_LIST_BOX
	* The list box is defined in the resource file CRHMGUI.rc
	*/
	CListBox listbox_sel_variables;

	/**
	* Listbox for all available observations.
	* List box that contains a string for each observation currently loaded.
	*
	* The control ID is ID_ALL_OBS_LIST_BOX
	* The list box is defined in the resource file "CRHMGUI.rc"
	*/
	RightClickListBox listbox_all_observations;

	/**
	* List box for selected observations.
	* List box that contains a string for each observation that is currently selected
	*	for output and display.
	*
	* The control ID is ID_SEL_OBS_LIST_BOX
	* The list box is defined in the resource file "CRHMGUI.rc"
	*/
	RightClickListBox listbox_sel_observations;

	/**
	* CTChart that controls the tchart plot.
	*/
	CTChart tchart;

	/**
	* Date picker for the start date of the simulation. 
	* 
	* Control ID is ID_START_DATE_PICKER
	* The control is defined in the resource file "CRhMGUI.rc"
	*/
	CDateTimeCtrl StartDatePicker;

	/**
	* Date picker for the end date of the simulation.
	*
	* Control ID is ID_END_DATE_PICKER
	* The control is defined in the resource file "CRhMGUI.rc"
	*/
	CDateTimeCtrl EndDatePicker;

	/** 
	* The number of open observation files.
	*/
	int observationsFilesCount = 0; 

	/**
	* Vector that stores observation file names paired with a vector of strings of the names of the observations within.
	*/
	std::vector<std::pair<std::string, std::vector<std::string>*>>* observationsFiles{ NULL };

	/**
	* Map that assocates a control ID for a menu item with each open observation file.
	*/
	std::map<UINT, std::pair<std::string, std::string>>* openObsFiles; 

	/**
	* Initalizes the dialog elements after creating the dialog.
	*/
	virtual BOOL OnInitDialog();

	/**
	* Processes the command line arguments if the GUI version of CRHM is used as a command line program.
	* 
	* This feature is not reccomended as the gcc CLI is much more robust. 
	* Reccomend depricating this feature. 
	*/
	void ProcessCommandLineArgument();

	/**
	* Initalzies GUI components after loading a project. 
	* 
	* Also determines of auto run is enabled and runs the project if so.
	*/
	void loadGuiComponents();


	/**
	* Calls the declaration function on each selected module after a model is built.
	*/
	void InitModules();

	/**
	* Called at end of initModules. Purpose currently unknown. 
	*/
	void GetAllVariables();

	/**
	* Returns true if the variable and module use a variation.
	* 
	* @param Variation_set int value of variation_set member of a ClassVar
	* @param Variation long value of variation member of a ClassModule 
	*/
	bool Variation_Decide(int Variation_set, long Variation);

	/**
	* Returns name of the passed in variable with the group suffix appended. 
	* 
	* @param thisVar ClassVar* the variable to return the group suffix appened name of.
	*/
	std::string DeclObsName(ClassVar* thisVar);

	/**
	* Runs the simulation that has been set up.
	* The simulation is run in stages and after 
	*	each stage the GUI updates the plot as it runs
	*/
	void RunClickFunction();


	/**
	* Adds a series to the TChart plot.
	* 
	* @param series TSeries* a pointer to the series to add to the plot.
	*/
	void AddSeriesToTChart(TSeries* series);


	/**
	* 
	* @param thisVar ClassVar* pointer to the observation variable being added to the plot.
	* @param cdSeries TSeries* pointer to the series being added to the plot.
	* @param S 
	*/
	void AddObsPlot(ClassVar* thisVar, TSeries* cdSeries, std::string S, TFun Funct);

	/**
	* Sets the time on the date pickers.
	* 
	* @param startDate double windows OLE timestamp
	* @param endDate double windows OLE timestamp
	*/
	void SetTime(double startDate, double endDate);

	/**
	* Opens a project in the model.
	* 
	* @param filepath std::string path to the project file to open.
	* @param filename std::string name of the project file to open.
	*/
	void OpenProject(std::string filepath, std::string filename);

	/**
	* Saves, closes, and reopens the currently open project. 
	*/
	void ReopenProject();

	/**
	* Saves the currently open project.
	*/
	void SaveProject();

	/**
	* Closes the currently open project.
	*/
	void CloseProject();

	/**
	* Adds a plot point to a CSeries
	* 
	* @param series CSeries the seriese to add the plot point to.
	* @param xvalue double x value of the plot point to add.
	* @param yvalue double y value of the plot point to add. 
	*/
	void AddDataToSeries(CSeries series, double xvalue, double yvalue);

	/**
	* Opens an observation file.
	* 
	* @param obsfilepath std::string filepath to the observation file to open.
	*/
	void OpenObservation(std::string obsfilepath);


	/**
	* Adds an observation file to the list of open observation files and makes a menu item for it.
	* Creates a menu item for the given observation file and adds it to the menu. 
	*
	* @param filepath std::string path to the project file to open.
	* @param filename std::string name of the project file to open.
	*/
	void AddOpenObsFile(std::string filepath, std::string filename);

	// Start GUI update functions

	/**
	* Calls the updateOpenObsFileMenu and updateOpenStateFileMenu funcitons.
	*/
	void updateGuiMenuItems();

	/**
	* Updates the observation submenu based on the model.
	* Helper function that removes all submenu items from the OpenObsFileMenu and
	* resets it so that it contains the correct submenu items based on the state
	* in the model.
	*
	* Also resets the observations listbox and its selected items.
	*/
	void updateOpenObsFileMenu();

	/**
	* Updates the state file submenu items based on the model.
	*/
	void updateOpenStateFileMenu();

	/**
	* Updates the selected observation list box contents based on the state of the model.
	*/
	void updateSelectedObservationListBox();

	// End GUI update functions

	//Message handlers

	/**
	* Handler for clicking on project->Open
	* Uses a file open dialog to select a project file 
	*	and then opens the selected project file.
	*/
	afx_msg void OnFileOpen();

	/**
	* Handler for clicking on project->Save
	* 
	* Saves the currently loaded project. 
	*/
	afx_msg void OnFileSave();

	/**
	* Handler for clicking on project->Save As
	* 
	* Opens a file dialog allowing the user to choose a file location.
	*	Upon completion of the dialog saves the currently open project in that location.
	*/
	afx_msg void OnFileSaveAs();

	/**
	* Handler for clicking on project->Close
	* 
	* Closes the currently open project.
	*	This saves the project and closes the whole dialog and opens a new one.
	*/
	afx_msg void OnFileClose();

	/**
	* Handler for clicking on project->Extract Group
	* 
	* Opens the extract group modal window.
	*/
	afx_msg void OnReport();

	/**
	* Handler for clicking on project->Auto Run
	* 
	* Toggles the auto run status of the currently loaded project.
	*/
	afx_msg void OnAutoRun();

	/**
	* Handler for clicking on project->Auto Exit
	* 
	* Toggles the auto exit status of the currently loaded project. 
	*/
	afx_msg void OnAutoExit();

	/**
	* Handler for clicking on project->Exit
	*
	* this has been added by Manishankar for exiting the CRHM program.
	* All the functionalities while closing the project should be integrated
	*	(for example saving an unsaved project) and additionally the program 
	*	should exit at last.
	* 
	* Currently does not check if project needs to be saved.
	*/
	afx_msg void OnExit();

	/**
	* Handler for clicking on Observations->Open Observation
	* 
	* Opens a file selection dialog. 
	* Once complete the user selected observation file is opened. 
	* A menu item for the open file is also created. 
	*/
	afx_msg void OnOpenObservation();

	/**
	* Handler for clicking on an open observation file menu item.
	* 
	* Closes the clicked on observation file and removes the menu item.
	*/
	afx_msg void OnClickOnOpenFile(UINT nID);

	/**
	* Handler for clicking on Observations->Close All
	* 
	* Closes all of the open observation files. 
	*/
	afx_msg void OnCloseAllObservations();

	/**
	* Handler for clicking on Build->Construct
	* 
	* Opens the project construction dialog.
	*/
	afx_msg void OnBuildConstruct();

	/**
	* Handler for clicking on Build->Macro
	* 
	* Opens the macro construction dialog.
	*/
	afx_msg void OnBuildMacro();

	/**
	* Handler for clicking on States->Open Inital State
	* 
	* Opens a file dialog to select an inital state file.
	* Upon completion loads the inital state file and creates an menu item for it.
	*/
	afx_msg void OnClickOnOpenInitState();

	/**
	* Handler for clicking on an open 
	*/
	afx_msg void CloseOpenInitFile();

	afx_msg void OnSaveState();

	afx_msg void OnSaveStateTo();

	afx_msg void OnSaveStateAs();

	afx_msg void OnRunRunmodel();

	afx_msg void OnFlowdiagramsShowdiagram();

	afx_msg void OnHelpAbout();

	afx_msg void DecreaseHRUDimension();

	afx_msg void IncreaseHRUDimension();

	afx_msg void DecreaseObsDimension();

	afx_msg void IncreaseObsDimension();

	afx_msg void OnLbnSelchangeList5();
	
	afx_msg void OnLbnDblclkList3();

	afx_msg void OnDblClkAllObsListBox();

	afx_msg void OnDblClkSelObsListBox();

	afx_msg void OnObservationSelectChange();

	afx_msg LRESULT OpenAllObsCtxMenu(WPARAM, LPARAM);

	afx_msg LRESULT OpenSelObsCtxMenu(WPARAM, LPARAM);

	afx_msg void OnBnClickedButton3();

	void addObservationsToSelected();

	void addObservationsArrayToSelected();
	
	void removeObservationsFromSelected();
	
	bool observationIsSelected(std::string seriesTitle);

	void SetItemsToListBox(int listboxid, std::vector<std::string>* list);

	std::list<std::pair<std::string, ClassVar*>> * GetSelectedVariablesFromListBox(int listboxid);

	std::list<std::pair<std::string, TSeries*>> * GetSelectedObservationsFromListBox(int listboxid);
	
};
