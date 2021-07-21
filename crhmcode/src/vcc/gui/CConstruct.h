#include "CRHM_GUI.h"
#include "afxdialogex.h"
#include "TStringList.h"
#include "../../core/CRHMmain/CRHMmain.h"
//#include "GlobalDll.cpp"
//#include "ClassModule/ClassModule.h"
#include "../../core/MacroUnit/MacroUnit.h"

#pragma once

class StringGrid;

// CConstruct dialog

class CConstruct : public CDialog
{
	DECLARE_DYNAMIC(CConstruct)

public:
	CConstruct(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CConstruct();
	
	void AKAselectiveDelete();
	bool ModifyBuild = false;
	void SetSuffix(long Row);
	void DisplayModule(string S, ClassModule* thisModule, bool LBox1);
	bool Variation_Decide(int Variation_set, long Variation);
	bool Visible_Decide(long Variation);
	bool Not_Obs(string Mod, string Var);
	void AddLinesToMemory(string str);
	




// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = CONSTRUCT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	CListBox listbox_all_modules;
	CListBox listbox_selected_modules;
	afx_msg void OnBnClickedButton8();
	void FormActivate();
	void SetSuffix(std::list<std::pair<std::string, ClassModule*>>::iterator pos);
	CButton checkbox_basic;
	CButton checkbox_macro;
	CButton checkbox_advanced;
	CButton checkbox_support;
	CButton checkbox_custom;
	CButton checkbox_prototype;
	CButton checkbox_obsolete;
	std::vector<std::pair<std::string, ClassModule *>> * AllModules = new std::vector<std::pair<std::string, ClassModule*>>(); //manishankar ListBox1 has been renamed as AllModules.
	std::vector<std::pair<std::string, ClassModule *>> * SelectedModules = new std::vector<std::pair<std::string, ClassModule*>>(); //manishankar ListBox2 has been renamed as SelectedModules.
	bool Execute{ FALSE };
	std::vector<std::pair<std::string, int>> * List{ NULL };
	TStringList * ListAll{ NULL };
	TStringList * ListUsed{ NULL };
	std::vector<std::pair<std::string, int>> * ListPuts{ NULL };
	std::vector<std::string> * ListStats{ NULL };
	TStringList * ParaList{ NULL };
	Mapstr2 MapAKACopy;
	Mapstr2 MapAKAVar;

	CEdit Memo1;

	StringGrid * StringGrid1{ NULL };
	afx_msg void OnLbnDblclkList2();
	afx_msg void OnLbnDblclkList1();
	CListCtrl listcontrol;
	afx_msg void OnBnClickedCancel2();
	long CheckModel();
	long Best_Match(string Var, std::vector<std::pair<std::string, int>>* List);
	long Best_Match(string Var, std::vector<std::string>* List);
	int IndexOf(TStringList *Box, string S);
	string StringOfChar(char c, int n);
	void UpdateCheckBoxes();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	long BuildClick();
	void SaveBuildParameters();
	void RemoveSharedParams();
	void RemoveParameter();
	long FormatMax(long M);
	afx_msg void OnBnClickedOk();
	void ReadBuildParameters();
	afx_msg void OnBnClickedCancel();
	void LoadAllModules();
	int IsAlreadySelected(CString cstr);
	afx_msg void OnLbnSelchangeList1();
	void RemoveSelectedModule();
	void AddToAllModules(string str, ClassModule * obj);
	void AddToSelectedModules(string str, ClassModule * obj);
	afx_msg void OnBnClickedButton1();
};

class StringGrid
{
public:
	string Cells[500][500];
	int ColCount = 0;
	int RowCount = 0;
	int FixedRows = 0;
	string Cols[500];
};