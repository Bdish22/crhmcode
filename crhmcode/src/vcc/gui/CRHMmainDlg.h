#include "CTChart.h"
#include "ClassCRHM.h"

//#include "stdafx.h"
//#include "CRHM_GUI.h"
////#include "CRHMmainDlg.h"
//#include "afxdialogex.h"
#include "../../core/CRHMmain/CRHMmain.h"
#include "CSeries.h"
//#include "CConstruct.h"
//#include "CRHMAboutBox.h"
//#include "StandardConverterUtility.h"


#pragma once


// CRHMmainDlg dialog

class CRHMmainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRHMmainDlg)	

public:
	CRHMmainDlg(CWnd* pParent = nullptr);   // standard constructor
	CRHMmainDlg(string argumentfile);
	virtual ~CRHMmainDlg();
	bool dirty{false};
	long Box1Disply{0};
	long ObsFunct_Toggle = 0; // no display/Final/Trend values
	long TBase{0};
	long water_year_month = 10;

	

	string ProjectFileArgument = ""; //it takes the filename from the command line.
	void ProcessCommandLineArgument();
	


	string defaultprojectname = "currentproject.prj";
	string defaultprojectpath = "currentproject.prj";
	string defaultobservationpath = "obs/Badlake73_76.obs";

	//string FStrings[15] = { "Observation", "VP_saturated", "W_to_MJ/Int", "MJ/Int_to_W", "Average", "Minimum", "Maximum", "Total", "Positive",
	//	"First", "Last", "Count", "Count0", "Delta", "Intvl" };
	//string Sstrings[14] = { "", "_VPsat", "_WtoMJ", "_MJtoW", "_Avg", "_Min", "_Max", "_Tot", "_Pos", "_First", "_Last", "_Cnt", "_Cnt0", "_Dlta" };

	string TBases[5] = { "Daily", "Water_year", "Calendar_year", "Monthly_summary", "Summarize_all" };
	//string Tmonths[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "July", "Aug", "Sept", "Oct", "Nov", "Dec" };
	//string TLogFormats[3] = { "MS_time", "MM/DD/YYYY", "YYYY-MM-DD" };


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = CRHMmainDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	CListBox listbox_varaiables_all;
	CListBox list_box_variables_selected;
	void loadGuiComponents();
	CListBox listbox_observations;
	void FormActivate();
	//afx_msg void OnRun32811();
	CTChart tchart;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	virtual BOOL OnInitDialog();
	CDateTimeCtrl DateTimePicker1;
	CDateTimeCtrl DateTimePicker2;
	afx_msg void OnLbnSelchangeList5();
	afx_msg void OnLbnSelchangeList2();
	CListBox listbox_observations_selected;
	afx_msg void OnBuildConstruct();
	afx_msg void OnRunRunmodel();
	afx_msg void OnFileSaveAs();

	std::list<std::pair<std::string, ClassVar*>> * GetSelectedVariablesFromListBox(int listboxid);
	std::list<std::pair<std::string, TSeries*>> * GetSelectedObservationsFromListBox(int listboxid);
	void SetItemsToListBox(int listboxid, std::vector<std::string> * list);
	afx_msg void OnBnClickedButton9();
	afx_msg void OnFileSave();

	afx_msg void OnFileClose();
	afx_msg void OnLbnDblclkList3();
	afx_msg void OnLbnDblclkList4();
	afx_msg void OnBnClickedButton3();
	void InitModules();
	void GetAllVariables();
	//string DeclObsName(ClassVar *thisVar);
	bool Variation_Decide(int Variation_set, long Variation);
	string DeclObsName(ClassVar *thisVar);
	void RunClickFunction();
	void AddSeriesToTChart();
	void AddSeriesToTChart(TSeries * series);
	afx_msg void OnOpenObservation();

	std::vector<std::pair<std::string, std::vector<std::string>*>> * observationsFiles {NULL};
	//char observationFiles[1000][128];
	int observationsFilesCount = 0;

	afx_msg void OnCloseAllObservations();
	void AddListBox2Click();
	void AddObsPlot(ClassVar *thisVar, TSeries *cdSeries, string S, TFun Funct);
	void SetTime(double startDate, double endDate);
	void SaveProject();
	//afx_msg void OnBnClickedButton2();
	afx_msg void OnBuildMacro();
	afx_msg void OnHelpAbout();
	afx_msg void OnFlowdiagramsShowdiagram();
	void CloseProject();
	void OpenProject(string filepath, string filename);
	void ReopenProject();
	void OpenObservation(string obsfilepath);
	void AddDataToSeries(CSeries series, double xvalue, double yvalue);
	//afx_msg void OnBnClickedOk();
	void AddObservationsOnOpenProject();
	void AddObservation(string obsstr);
	afx_msg void OnReport();
	afx_msg void OnProjectExit32832();
	afx_msg void OnAutoRun();
	afx_msg void OnAutoExit();
	afx_msg void OnClickOnOpenFile(UINT nID);

	void AddOpenObsFile(std::string filepath, std::string filename);
	
	/*View update functions*/
	void updateGui();
	void updateOpenObsFileMenu();
	void updateOpenStateFileMenu();

	/*State Menu Functions*/
	void OnClickOnOpenInitState();
	void CloseOpenInitFile();
	void OnSaveStateAs();
	void OnSaveState();
	void OnSaveStateTo();
private:
	std::map<UINT, std::pair<std::string, std::string>> * openObsFiles; //Map that assocates IDs with open obsfiles.
};
