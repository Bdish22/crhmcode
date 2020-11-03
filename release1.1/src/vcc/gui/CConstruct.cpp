// CConstruct.cpp : implementation file
//

#include "stdafx.h"
#include "CConstruct.h"
#include "CConstructCore.h"



// CConstruct dialog

IMPLEMENT_DYNAMIC(CConstruct, CDialog)

CConstruct::CConstruct(CWnd* pParent /*=nullptr*/)
	: CDialog(CONSTRUCT_DLG, pParent)
{

}

CConstruct::~CConstruct()
{
}

void CConstruct::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, listbox_all_modules);
	DDX_Control(pDX, IDC_LIST1, listbox_selected_modules);
	DDX_Control(pDX, IDC_CHECK1, checkbox_basic);
	DDX_Control(pDX, IDC_CHECK2, checkbox_macro);
	DDX_Control(pDX, IDC_CHECK3, checkbox_advanced);
	DDX_Control(pDX, IDC_CHECK4, checkbox_support);
	DDX_Control(pDX, IDC_CHECK5, checkbox_custom);
	DDX_Control(pDX, IDC_CHECK6, checkbox_prototype);
	DDX_Control(pDX, IDC_CHECK7, checkbox_obsolete);
	DDX_Control(pDX, IDC_LIST3, listcontrol);
}


BEGIN_MESSAGE_MAP(CConstruct, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON8, &CConstruct::OnBnClickedButton8)
	ON_LBN_DBLCLK(IDC_LIST2, &CConstruct::OnLbnDblclkList2)
	ON_LBN_DBLCLK(IDC_LIST1, &CConstruct::OnLbnDblclkList1)
	ON_BN_CLICKED(IDCANCEL2, &CConstruct::OnBnClickedCancel2)
	ON_BN_CLICKED(IDC_CHECK1, &CConstruct::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CConstruct::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CConstruct::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CConstruct::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CConstruct::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CConstruct::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CConstruct::OnBnClickedCheck7)
	ON_BN_CLICKED(IDOK, &CConstruct::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CConstruct::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_LIST1, &CConstruct::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CConstruct::OnBnClickedButton1)
END_MESSAGE_MAP()


// CConstruct message handlers



BOOL CConstruct::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	LoadAllModules();
	FormActivate();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CConstruct::LoadAllModules()
{
	listbox_all_modules.ResetContent();
	TStringList* all_modules = CRHMmain::getInstance()->getAllmodules();

	for (int ii = 0; ii <all_modules->Count; ii++) {
		//string s = variables->Strings[ii];
		std::string s = all_modules->Strings[ii];
		CString c_all_modules(s.c_str());
		listbox_all_modules.AddString(c_all_modules);
	}
}



int CConstruct::IsAlreadySelected(CString cstr)
{
	CString cstr1;
	for (int i = 0; i < listbox_selected_modules.GetCount(); i++)
	{
		listbox_selected_modules.GetText(i, cstr1);
		if (cstr == cstr1) { return 1; }
	}

	return 0;
}


void CConstruct::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here

	CString cstr;

	int sel = 0;// = listbox_all_modules.GetCurSel();

	//listbox_all_modules.GetText(index, cstr);
	//listbox_selected_modules.AddString(cstr);

	
	for (int i = 0; i < AllModules->Count; i++)
	{
		sel = listbox_all_modules.GetSel(i);
		if (sel == 1)
		{
			listbox_all_modules.GetText(i, cstr);

			if (IsAlreadySelected(cstr) == 0)
			{
				listbox_selected_modules.AddString(cstr);
				SelectedModules->AddObject(AllModules->Strings[i], AllModules->Objects[i]);				
			}
			listbox_all_modules.SetSel(i, false);
		}
	}
}



void CConstruct::RemoveSelectedModule()
{
	CString cstr;

	int c = SelectedModules->Count;
	for (int i = 0; i < c; i++)
	{
		int sel = listbox_selected_modules.GetSel(i);
		if (sel == 1)
		{
			listbox_selected_modules.GetText(i, cstr);

			listbox_selected_modules.DeleteString(i);
			CT2A s(cstr);
			string str = s;
			int indx = SelectedModules->IndexOf(str);
			SelectedModules->Delete(indx);
		}
	}
}


void CConstruct::AddToAllModules(string str, TObject * obj)
{
	AllModules->AddObject(str, obj);
	CString cstr(str.c_str());
	listbox_all_modules.AddString((LPCTSTR)cstr);
	string S = str;
	//		if (S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
	//			Max_Name_Width1 = S.Length();

}


void CConstruct::AddToSelectedModules(string str, TObject * obj)
{
	SelectedModules->AddObject(str, obj);
	CString cstr(str.c_str());
	listbox_selected_modules.AddString((LPCTSTR)cstr);
	string S = str;
}


//core functionality
void CConstruct::FormActivate()
{
	//StatusBar1->SimpleText = "";
	//StatusBar1->SimplePanel = true;

	listbox_all_modules.ResetContent();

	//for (int ii = 0; ii < CheckListBox1->Count; ++ii)
		//CheckListBox1->Checked[ii] = false;
	checkbox_basic.SetCheck(0);
	checkbox_macro.SetCheck(0);
	checkbox_advanced.SetCheck(0);
	checkbox_custom.SetCheck(0);
	checkbox_obsolete.SetCheck(0);
	checkbox_prototype.SetCheck(0);
	checkbox_support.SetCheck(0);

	//Label3->Caption = "";

	Mapstr2 MapAKACopy;
	MapAKACopy = Global::MapAKA; // save AKA to restore if no rebuild

	AKAselectiveDelete(); // deletes all AKAs but "OBSR" and "OBSF"

	Global::Mapgetvar.clear();
	Global::Mapputvar.clear();
	Global::Mapreadvar.clear();
	Global::Mapdeclvar.clear();
	Global::Mapdeclstat.clear();
	Global::Mapdeclpar.clear();
	Global::Mapdeclobs.clear();

	CRHM::TBuild TempB = Global::BuildFlag;
	Global::BuildFlag = CRHM::BUILD; // default value


	for (int ii = 0; ii < Global::AllModulesList->Count; ++ii) { 

		if (ii == Global::AllModulesList->Count - 1)
		{
			int a = 10;
		}


		ClassModule* thisModule = (ClassModule*)Global::AllModulesList->Objects[ii];
		thisModule->variation_max = 0;

		unsigned short Temp = thisModule->variation;
		unsigned short Temp2 = thisModule->variation_set;
		thisModule->variation_set = 0;
		thisModule->variation = 0;
		thisModule->decl();
		thisModule->variation = Temp;
		thisModule->variation_set = Temp2;

		if (thisModule->variation > 0)
			thisModule->hh = (long) (log(thisModule->variation) / log(2) + 1); // set to current variation
		else
			thisModule->hh = 0;
	}

	Global::OBS_AS_IS = 0; // Quinton module sets it
	Global::WQ_prj = false; // Set for WQ project
	listbox_selected_modules.ResetContent();

	if (Global::OurModulesList->Count)
		ModifyBuild = true;
	else {
		ModifyBuild = false;
		checkbox_basic.SetCheck(1);
	}


	for (int ii = 0; ii < Global::OurModulesList->Count; ++ii) { // fill ListBox2
		//CheckListBox1->Checked[((ClassModule*)Global::OurModulesList->Objects[ii])->Lvl] = true;

		if ( ((ClassModule*)Global::OurModulesList->Objects[ii])->Lvl == CRHM::LMODULE::BASIC ){checkbox_basic.SetCheck(1);}
		if (((ClassModule*)Global::OurModulesList->Objects[ii])->Lvl == CRHM::LMODULE::MACRO) { checkbox_macro.SetCheck(1); }
		if (((ClassModule*)Global::OurModulesList->Objects[ii])->Lvl == CRHM::LMODULE::ADVANCE) { checkbox_advanced.SetCheck(1); }
		if (((ClassModule*)Global::OurModulesList->Objects[ii])->Lvl == CRHM::LMODULE::SUPPORT) { checkbox_support.SetCheck(1); }
		if (((ClassModule*)Global::OurModulesList->Objects[ii])->Lvl == CRHM::LMODULE::CUSTOM) { checkbox_custom.SetCheck(1); }
		if (((ClassModule*)Global::OurModulesList->Objects[ii])->Lvl == CRHM::LMODULE::PROTO) { checkbox_prototype.SetCheck(1); }
		if (((ClassModule*)Global::OurModulesList->Objects[ii])->Lvl == CRHM::LMODULE::OBSOL) { checkbox_obsolete.SetCheck(1); }

		AddToSelectedModules(Global::OurModulesList->Strings[ii], (TObject *)Global::OurModulesList->Objects[ii]);
		//ListBox2->AddObject(Global::OurModulesList->Strings[ii], (TObject *)Global::OurModulesList->Objects[ii]);
		//listbox_selected_modules.AddString((LPCTSTR)Global::OurModulesList->Strings[ii].c_str());
		SetSuffix(ii);
		string S = Global::OurModulesList->Strings[ii];
		//if (S.length() > 33 && S.length() > Max_Name_Width2) // 198 pixels roughly 33 caharacters
	//		Max_Name_Width2 = S.Length();
	}
	//ListBox2->ScrollWidth = Max_Name_Width2 * 6;

	Execute = false;

	UpdateCheckBoxes();
}


void CConstruct::SetSuffix(long Row) {

	//TStringList * ListBox2;

	ClassModule* thisModule = (ClassModule*)SelectedModules->Objects[Row];
	string AA;
	if (thisModule->hh > 0) {
		AA = "#0";
		AA[1] += (char) thisModule->hh;
	}
	int found = SelectedModules->Strings[Row].find("#");
	if (found > -1) // remove earlier suffix
	{
		//SelectedModules->Strings[Row] = SelectedModules->Strings[Row].Delete(SelectedModules->Strings[Row].length() - 1, 2);
		SelectedModules->Strings[Row] = SelectedModules->Strings[Row].substr(0, SelectedModules->Strings[Row].length() - 2);
	}

	SelectedModules->Strings[Row] = SelectedModules->Strings[Row] + AA;
}



void CConstruct::AKAselectiveDelete()
{
	if(!Global::MapAKA.empty()) 
	{ // separate out AKA commands
		Mapstr2::iterator it;

		for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); )
		{
			string Var = (*it).first; // module, type and name

			string::size_type idx = Var.find(' ');
			string type = Var.substr(0, idx);
			TAKA Type = AKAtype(type);

			switch (Type) 
			{
				case OBSR :
				case OBSF :
				++it;
				break;

				default :
				Global::MapAKA.erase(it++);
			} // end switch
		} // for
	}
}


void CConstruct:: AddLinesToMemory(string str)
{
	CListBox * listbox = (CListBox*)GetDlgItem(IDC_LIST4);
	CString cstr(str.c_str());
	listbox->AddString(cstr);
}


void CConstruct::DisplayModule(string S, ClassModule* thisModule, bool LBox1) {
	Mapstr::iterator itMap, pos, pos2, itMap2;

	//int indx; varible is unreferenced commenting out for now - jhs507
	string SS, S1, S2;
	//TGridOptions OurOptions;

	MapVar::iterator itVar;

	long Variation = 0;
	long Vindx = 0;
	int P;

	SS = S;
	if (P = S.find("#"), P > -1) { // remove any suffix
		Vindx = S[P + 1] - char('0');
		Variation = (long) (pow(2, S[P + 1] - char('1')));
		S = S.substr(0, S.length() - 2);
	}
	else
		Variation = 0;

	if (!thisModule->Description.empty()) {
		TStringList* Fred = new TStringList;
		Fred->QuoteChar = '\'';
		Fred->DelimitedText (thisModule->Description);
		if (thisModule->variation_max > 0) // if variation skip overview
			++Vindx;

		if (LBox1) { // write it all out
			for (int ii = 0; ii < Fred->Count; ++ii) {
				S1 = S;
				if (ii == 0)
					S1 += " Function summary";
				else if (ii > 1)
					S1 += "#" + to_string(ii - 1);
				else
					S1 += "  ";

				S1 += " -> " + Fred->Strings[ii];
				//Memo1->Lines->Add(S1);
				AddLinesToMemory(S1);
			}
		}
		else {
			//Memo1->Lines->Add(SS + " -> " + Fred->Strings[Vindx]);
			AddLinesToMemory(SS + " -> " + Fred->Strings[Vindx]);
			if (thisModule->DLLName == "Macro") {
				ClassMacro *thisMacro = dynamic_cast<ClassMacro *> (thisModule);

				if (thisMacro->isGroup) {
					//Memo1->Lines->Add("Group with modules:");
					AddLinesToMemory("Group with modules:");
					string S;
					for (int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
						if (ii == 0)
							S = "  " + thisMacro->GrpStringList->Strings[ii];
						else
							S += ", " + thisMacro->GrpStringList->Strings[ii];
					//Memo1->Lines->Add(S);
					AddLinesToMemory(S);
				}
				else if (thisMacro->isStruct) {
					//Memo1->Lines->Add("Struct with modules:");
					AddLinesToMemory("Struct with modules:");
					string S;
					for (int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
						if (ii == 0)
							S = "  " + thisMacro->GrpStringList->Strings[ii];
						else
							S += ", " + thisMacro->GrpStringList->Strings[ii];
					//Memo1->Lines->Add(S);
					AddLinesToMemory(S);
				}
				else {
					//Memo1->Lines->Add("Macro: ");
					//Memo1->Lines->Add("declarations:");
					AddLinesToMemory("Macro: ");
					AddLinesToMemory("declarations:");
					for (int ii = Global::MacroModulesList->IndexOf(thisMacro->Name.c_str()) + 1; ii < thisMacro->Begin - 1; ++ii)
					{
						//Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);
						AddLinesToMemory(" " + Global::MacroModulesList->Strings[ii]);
					}

					//Memo1->Lines->Add("code:");
					AddLinesToMemory("code:");
					for (int ii = thisMacro->Begin; ii < thisMacro->End; ++ii)
					{
						//Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);
						AddLinesToMemory(" " + Global::MacroModulesList->Strings[ii]);
					}
				}
			}
		}
		//Memo1->Lines->Add(" ");
		AddLinesToMemory(" ");
		delete Fred;
	}

	//stringgrid.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_GRIDLINES);
	
	//stringgrid.insert

	
	//OurOptions << goHorzLine << goVertLine << goFixedVertLine << goColSizing;
	//StringGrid1->Options = OurOptions;



	 
	StringGrid1 = new StringGrid();

	for (int I = 0; I < StringGrid1->ColCount; ++I)
		for (int J = 0; J < StringGrid1->RowCount; ++J)
			StringGrid1->Cells[I][J] = "";

	
	StringGrid1->ColCount = 6;
	StringGrid1->FixedRows = 0;
	StringGrid1->RowCount = 1;

	StringGrid1->Cells[0][0] = "Observations";
	StringGrid1->Cells[1][0] = "Modules";
	StringGrid1->Cells[2][0] = "Inputs";
	StringGrid1->Cells[3][0] = "Outputs";
	StringGrid1->Cells[4][0] = "Parameters";
	StringGrid1->Cells[5][0] = "New Observations";
	

	// insert observations
	pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(S);
	int ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		SS = (itMap->second).first;
		if (StringGrid1->RowCount < ii + 3) StringGrid1->RowCount = ii + 3;
		int Indx = StringGrid1->Cols[0].find(SS);
		if (Indx == -1 && Variation_Decide(Variation, (itMap->second).second)) {
			StringGrid1->Cells[0][ii + 2] = SS;
			++ii;
		}
	} // for

	  // insert put variables used
	range = Global::Mapputvar.equal_range(S);
	ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		SS = itMap->second.first;
		int jj = SS.find(" ");
		S1 = SS.substr(0, jj); // module
		S2 = SS.substr(jj + 1, SS.length() - jj-1); // variable
		if (S1 != S && Variation_Decide(Variation, (itMap->second).second)) {
			if (StringGrid1->RowCount < ii + 3) StringGrid1->RowCount = ii + 3;
			StringGrid1->Cells[1][ii + 2] = S1;
			StringGrid1->Cells[2][ii + 2] = S2;
			++ii;
		}
	} // for

	  // insert get variables used
	range = Global::Mapgetvar.equal_range(S);
	//  ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		SS = itMap->second.first;
		int jj = SS.find(" ");
		S1 = SS.substr(0, jj); // module
		S2 = SS.substr(jj + 1, SS.length() - jj-1); // variable
		if (S1 != S && Variation_Decide(Variation, (itMap->second).second)) {
			int Indx = StringGrid1->Cols[2].find(S2);
			if (Indx == -1) {
				if (StringGrid1->RowCount < ii + 3) StringGrid1->RowCount = ii + 3;
				StringGrid1->Cells[1][ii + 2] = S1;
				StringGrid1->Cells[2][ii + 2] = S2;
				++ii;
			}
		}
	} // for

	  // insert variables declared
	range = Global::Mapdeclvar.equal_range(S);
	ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		SS = itMap->second.first;


		//previous code

		//pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
			//value_equals<KeyType2, KeyType2, Pairstr>(SS));

		//pos2 = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
			//value_equals<KeyType2, KeyType2, Pairstr>(SS));



		for (itMap2 = Global::Mapreadvar.begin(); itMap2 != Global::Mapreadvar.end(); ++itMap2)
		{
			if (itMap2->second.first == SS)
			{
				break;				
			}
		}
		pos = itMap2;

		for (itMap2 = Global::Mapdeclobs.begin(); itMap2 != Global::Mapdeclobs.end(); ++itMap2)
		{
			if (itMap2->second.first == SS)
			{
				break;				
			}
		}
		pos2 = itMap2;


		//new code. need to change.		
		//pos = Global::Mapreadvar.end();
		//pos2 = Global::Mapdeclobs.end();


		if ((pos == Global::Mapreadvar.end() || Not_Obs(S, SS)) && pos2 == Global::Mapdeclobs.end()) {
			int Indx = StringGrid1->Cols[3].find(SS);
			if (Indx == -1 && Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second)) {
				if (StringGrid1->RowCount < ii + 3) StringGrid1->RowCount = ii + 3;
				StringGrid1->Cells[3][ii + 2] = SS;
				++ii;
			}
		}
	} // for

	  // insert parameters declared
	range = Global::Mapdeclpar.equal_range(S);
	ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		if (Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second)) {
			SS = itMap->second.first;
			if (StringGrid1->RowCount < ii + 3)
				StringGrid1->RowCount = ii + 3;
			StringGrid1->Cells[4][ii + 2] = SS;
			++ii;
		}
	} // for

	  // insert observations declared
	range = Global::Mapdeclobs.equal_range(S);
	ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		if (Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second)) {
			SS = itMap->second.first;
			if (StringGrid1->RowCount < ii + 3)
				StringGrid1->RowCount = ii + 3;
			StringGrid1->Cells[5][ii + 2] = SS;
			++ii;
		}
	} // for

	if (StringGrid1->RowCount > 1) StringGrid1->FixedRows = 1;

	while (listcontrol.DeleteColumn(0));

	listcontrol.DeleteAllItems();

	listcontrol.InsertColumn(0, _T("Observations"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(1, _T("Modules"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(2, _T("Inputs"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(3, _T("Outputs"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(4, _T("Parameters"), LVCFMT_LEFT, 95);
	listcontrol.InsertColumn(5, _T("New Observations"), LVCFMT_LEFT, 95);

	for (int i = 1; i < StringGrid1->RowCount; i++)
	{
		CString cstr0(StringGrid1->Cells[0][i].c_str());
		CString cstr1(StringGrid1->Cells[1][i].c_str());
		CString cstr2(StringGrid1->Cells[2][i].c_str());
		CString cstr3(StringGrid1->Cells[3][i].c_str());
		CString cstr4(StringGrid1->Cells[4][i].c_str());
		CString cstr5(StringGrid1->Cells[5][i].c_str());

		int nIndex = listcontrol.InsertItem(i-1, cstr0);
		listcontrol.SetItemText(nIndex, 1, cstr1);
		listcontrol.SetItemText(nIndex, 2, cstr2);
		listcontrol.SetItemText(nIndex, 3, cstr3);
		listcontrol.SetItemText(nIndex, 4, cstr4);
		listcontrol.SetItemText(nIndex, 5, cstr5);
	}
}


bool CConstruct::Variation_Decide(int Variation_set, long Variation) {

	VandP V; V.Set(Variation);

	long variations = V.GetV(); // & 2047;

	if ((variations & 2048) != 0 && Variation_set == 0 || // handles VARIATION_0
		(variations & 4096) != 0 ||                        // handles VARIATION_0
		(variations == 0) ||                               // handles VARIATION_ORG
		(variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
		return true;
	else
		return false;
}

bool CConstruct::Visible_Decide(long Variation) {

	VandP V; V.Set(Variation);
	long Visible = V.GetP();
	return Visible == 1;
}

bool CConstruct::Not_Obs(string Mod, string Var) {

	pair<Mapstr::iterator, Mapstr::iterator> rangeIobs = Global::Mapreadvar.equal_range(Mod);
	for (Mapstr::iterator itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap)
		if (Var == itMap->second.first)
			return false;

	return true;
}


void CConstruct::OnLbnDblclkList2()
{
	// TODO: Add your control notification handler code here
	int selection = listbox_all_modules.GetCurSel();
	CString cstr;
	listbox_all_modules.GetText(selection, cstr);
	CT2A str(cstr);

	int ind = -1;
	for (int i = 0; i < Global::AllModulesList->Count; i++)
	{
		ind = Global::AllModulesList->Strings[i].find(str);
		if (ind > -1) { ind = i;  break; }
	}

	//string S = ListBox1->Strings[selection];
	string S = str;
	ClassModule* thisModule = (ClassModule*)Global::AllModulesList->Objects[ind];
	DisplayModule(S, thisModule, true);
	CRHM::LMODULE Lvl = thisModule->Lvl;
	//Label3->Caption = LVLStrings[Lvl];

}


void CConstruct::OnLbnDblclkList1()
{
	// TODO: Add your control notification handler code here
	int selection = listbox_selected_modules.GetCurSel();
	CString cstr;
	listbox_selected_modules.GetText(selection, cstr);
	CT2A str(cstr);

	int ind = -1;
	for (int i = 0; i < Global::AllModulesList->Count; i++)
	{
		string test = Global::AllModulesList->array[i].Name;
		ind = test.find(str);
		if (ind > -1) 
		{ 
			ind = i;
			break; 
		}
	}

	//string S = ListBox1->Strings[selection];
	string S = str;
	ClassModule* thisModule = (ClassModule*)Global::AllModulesList->Objects[ind];
	DisplayModule(S, thisModule, false);
	CRHM::LMODULE Lvl = thisModule->Lvl;
	//Label3->Caption = LVLStrings[Lvl];
}


void CConstruct::OnBnClickedCancel2()
{
	// TODO: Add your control notification handler code here

	CheckModel();
	//MessageBox(_T("done"));

}

int CConstruct::IndexOf(TStringList *Box, string S) {
	for (int ii = 0; ii < Box->Count; ++ii) {
		if (Box->Strings[ii] == S)
			return ii;
	}
	return -1;
}

string CConstruct::StringOfChar(char c, int n)
{
	string result = "";
	for (int i = 0; i < n; i++)
	{
		result += c;
	}
	return result;
}

long CConstruct::CheckModel() {

	long Showing = SelectedModules->Count;
	if (Showing == 0) return 0;

	Mapstr::iterator itMap, pos, pos2, itMap2;
	pair<Mapstr::iterator, Mapstr::iterator> rangeO;
	pair<Mapstr::iterator, Mapstr::iterator> rangeOobs;
	pair<Mapstr::iterator, Mapstr::iterator> rangeI;
	pair<Mapstr::iterator, Mapstr::iterator> rangeIobs;

	List = new TStringList;
	ListAll = new TStringList;
	ListUsed = new TStringList; // Object SelectedModules pos index, neg -(index+1)
	ListPuts = new TStringList;
	ListStats = new TStringList;

	List->Sorted = false; // allows duplicates
	ListUsed->Sorted = false; // allows duplicates
	ListPuts->Sorted = false; // allows duplicates
	ListStats->Sorted = false; // allows duplicates

	string S, SS, S1, S2;
	int indx, Error = 0, Wild = 0;
	
	MapAKAVar.clear();

	//StatusBar1->SimpleText = "";
	//Memo1->Lines->Clear();
	CListBox * listbox = (CListBox*)GetDlgItem(IDC_LIST4);
	listbox->ResetContent();

	long Variation = 0;
	long Vindx = 0;
	int P;

Again:

	// Add any modules not in SelectedModules but defined as source modules.
	// Wild modules must be explicitly added.
	for (int ii = 0; ii < SelectedModules->Count; ++ii) {
		S = SelectedModules->Strings[ii];

		if (P = S.find("#"), P > -1) { // remove any suffix
			Vindx = S[P + 1] - char('0');
			Variation = (long) pow(2, S[P + 1] - char('1'));
			S = S.replace(S.length() - 2, 2, "");
		}
		else
			Variation = 0;

		rangeI = Global::Mapgetvar.equal_range(S);
		for (itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
			SS = itMap->second.first;
			if (Variation_Decide(Variation, (itMap->second).second)) {
				int jj = SS.find(" ");
				S1 = SS.substr(0, jj);
				S2 = SS.substr(jj + 1, SS.length() - jj-1); // variable
				if (S1[0] != '*') { // handle specified variables
					rangeO = Global::Mapdeclvar.equal_range(S);
					bool Found = false;
					for (pos = rangeO.first; pos != rangeO.second; ++pos) {
						if (S2 == pos->second.first) { // variable
							Found = true;
							break;
						}
					}
					if (!Found) { // not a group!
						indx = IndexOf(SelectedModules, S1); // module in model?
						if (indx == -1) { // module not loaded
							indx = IndexOf(AllModules, S1); // module available?
							if (indx == -1) { // module does not exist
								LogError("module not found: " + S1, TExcept::ERR); // should not return
								//Memo1->Lines->Add("module not found: " + S1);
								AddLinesToMemory("module not found: " + S1);
							}
							else {
								int result = IDYES;

								string temp = "To satisfy module " + S + " input " + SS;
								CString cstr (temp.c_str());
								string temp2 = "Add module " + S1 + " ?";
								CString cstr2(temp2.c_str());
								result = MessageBox(cstr, cstr2, MB_YESNO);
								if (result == IDYES)
								{
									SelectedModules->InsertObject(ii, S1, AllModules->Objects[indx]);
								}
							}
						}
					} // if
				} // if
			} // handle variation
		} // for
	} // for

	for (int ii = 0; ii < SelectedModules->Count; ++ii) {
		S = SelectedModules->Strings[ii];

		if (P = S.find("#"), P > -1) { // remove any suffix
			Vindx = S[P + 1] - char('0');
			Variation = (long) pow(2, S[P + 1] - char('1'));
			S = S.replace(S.length() - 2, 2, "");
		}
		else
			Variation = 0;

		// make stats list
		rangeI = Global::Mapdeclstat.equal_range(S);

		for (itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
			SS = itMap->second.first; // module + variable
			if (Variation_Decide(Variation, (itMap->second).second))
				ListStats->Add(SS);
		} // for

		rangeO = Global::Mapdeclvar.equal_range(S);
		rangeOobs = Global::Mapdeclobs.equal_range(S);
		rangeI = Global::Mapgetvar.equal_range(S);
		rangeIobs = Global::Mapreadvar.equal_range(S);

		// add current modules declared observations to 'list'
		for (itMap = rangeOobs.first; itMap != rangeOobs.second; ++itMap) {
			SS = itMap->second.first; // variable
			if (Variation_Decide(Variation, (itMap->second).second))
				List->AddObject(S + " " + SS, (TObject *)0);
		} // for

		  // add current modules declared variables to 'list'
		for (itMap = rangeO.first; itMap != rangeO.second; ++itMap) {
			SS = itMap->second.first; // variable
			if (Variation_Decide(Variation, (itMap->second).second)) {


				//previous code.
				//pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
					//value_equals<KeyType2, KeyType2, Pairstr>(SS));

				//pos2 = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
					//value_equals<KeyType2, KeyType2, Pairstr>(SS));



				for (itMap2 = Global::Mapreadvar.begin(); itMap2 != Global::Mapreadvar.end(); ++itMap2)
				{
					if (itMap2->second.first == SS)
					{
						break;
					}
				}
				pos = itMap2;

				for (itMap2 = Global::Mapdeclobs.begin(); itMap2 != Global::Mapdeclobs.end(); ++itMap2)
				{
					if (itMap2->second.first == SS)
					{
						break;
					}
				}
				pos2 = itMap2;


				//new code. need to change.		
				//pos = Global::Mapreadvar.end();
				//pos2 = Global::Mapdeclobs.end();


				if ((pos == Global::Mapreadvar.end() || Not_Obs(S, SS)) && pos2 == Global::Mapdeclobs.end()) {
					S2 = SelectedModules->Strings[ii] + " " + SS;
					string S3;
					string M3;
					bool Twice = false;
					int tt;

					for (tt = 0; tt < ListAll->Count; ++tt) {
						int jj = ListAll->Strings[tt].find(" ");
						S3 = ListAll->Strings[tt].substr(jj + 1, ListAll->Strings[tt].length() - jj-1); // variable
						M3 = ListAll->Strings[tt].substr(0, jj); // module
						if (S3 == SS && S != M3 && S != "obs") {
							if (S3[S3.length()-1] != '#') {
								Twice = true;
								break;
							}
						}
					}

					if (Twice) {
						int result = IDYES;

						string temp = string("YES to remove '" + S + "' or NO to remove '" + M3 + "'");
						CString cstr(temp.c_str());
						string temp2 = string("Module output generated twice: '" + S2 + "' defined earlier as '" + ListAll->Strings[tt] + "'");
						CString cstr2(temp2.c_str());

						result = MessageBox(cstr, cstr2, MB_YESNO);

						if (result == IDYES)
							tt = IndexOf(SelectedModules, S); // module in model?
						else if (result == IDNO)
							tt = IndexOf(SelectedModules, M3); // module in model?

						SelectedModules->Delete(tt);

						
						Entries.clear();
						List->Clear();
						ListAll->Clear();
						ListUsed->Clear();
						ListPuts->Clear();
						ListStats->Clear();

						goto Again;
					}

					ListAll->Add(S2);

					int indx = List->IndexOf(S2);
					if (indx == -1)
						List->AddObject(S2, (TObject *)0);
				} // if
			} // handle variation
		} // for

		  // add needed get variables to ListUsed
		for (itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
			SS = itMap->second.first; // module + variable
			if (Variation_Decide(Variation, (itMap->second).second)) {
				int indx = List->IndexOf(SS);
				if (indx == -1 && SS[0] != '*') { // handle groups and ignore wild
					int jj = SS.find(" ");
					S2 = SS.substr(jj + 1, SS.length() - jj-1); // variable
					S1 = S + ' ' + S2; // check if in the same group
					indx = List->IndexOf(S1);
					if (indx == -1 && S1[S1.length() - 2] == '@') // check if available as root variable
						indx = List->IndexOf(SS.substr(0, SS.find("@"))); // check if available as root variable
				}
				if (indx == -1) {
					ListUsed->AddObject(SS, (TObject *)-(ii + 1)); // wild variable or undefined
				}
				else {
					int Cnt = (int)List->Objects[indx]; // increment count of useage
					List->Objects[indx] = (TObject *) ++Cnt;
					ListUsed->AddObject(SS, (TObject *)ii);
				}
			} // neccessary
		} // for

		  // add needed put variables to ListUsed
		rangeI = Global::Mapputvar.equal_range(S);

		for (itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
			SS = itMap->second.first; // module + variable
			if (Variation_Decide(Variation, (itMap->second).second)) {
				int indx = List->IndexOf(SS);
				if (indx == -1) {
					ListPuts->AddObject(SS, (TObject *)ListUsed->Count); // wild variable or undefined
					ListUsed->AddObject(SS, (TObject *)-(ii + 1)); // wild variable or undefined
				}
				else {
					int Cnt = (int)List->Objects[indx]; // increment count of useage
					List->Objects[indx] = (TObject *) ++Cnt;
					ListPuts->AddObject(SS, (TObject *)ListUsed->Count);
					ListUsed->AddObject(SS, (TObject *)ii);
				}
			} // handle variation
		} // for

		  // add needed macro observations to ListUsed
		for (itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap) {
			SS = itMap->second.first; // variable
			if (Variation_Decide(Variation, (itMap->second).second)) {
				
				//previous code.
				//pos = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
					//value_equals<KeyType2, KeyType2, Pairstr>(SS));

				for (itMap2 = Global::Mapdeclobs.begin(); itMap2 != Global::Mapdeclobs.end(); ++itMap2)
				{
					if (itMap2->second.first == SS)
					{
						break;
					}
				}
				pos = itMap2;



				//new code. need to change
				//pos = Global::Mapdeclobs.end();


				if (pos == Global::Mapdeclobs.end())
					continue; // not available or met observation
				indx = IndexOf(SelectedModules, pos->first); // module available?
				if (indx != ii && indx > -1) { // cannot be its self
					S1 = pos->first;
					SS = pos->second.first;
					S2 = S1 + " " + SS;
					indx = List->IndexOf(S2);
					if (indx == -1) { // used but not declared
						ListUsed->AddObject(S2, (TObject *)-(ii + 1));
					}
					else {
						int Cnt = (int)List->Objects[indx]; // increment count of useage
						List->Objects[indx] = (TObject *) ++Cnt;
						ListUsed->AddObject(S2, (TObject *)ii);
					}
				} // if
			} // handle variation
		} // for
	} // for - long loop

	for (int ii = 0; ii < SelectedModules->Count; ++ii) {
		S = SelectedModules->Strings[ii];

		if (P = S.find("#"), P > -1) { // remove any suffix
			Vindx = S[P + 1] - char('0');
			Variation = (long) pow(2, S[P + 1] - char('1'));
			S = S.replace(S.length() - 2, 2, "");
		}
		else {
			Vindx = 0;
			Variation = 0;
		}
		// Add module PeerVar to 'ListUsed' to force module to desired rank.
		ClassModule *Module = (ClassModule*)SelectedModules->Objects[ii];

		TStringList *Choices = new TStringList;
		Choices->CommaText (Module->PeerVar);

		if (Choices->Count > Vindx)
			SS = Choices->Strings[Vindx];
		else if (Choices->Count)
			SS = Choices->Strings[Choices->Count - 1];
		else
			SS = "";

		if (SS != "") {
			for (int jj = 0; jj < List->Count; ++jj) {
				string Entry = List->Strings[jj];
				long kk = Entry.find(' ');
				S1 = Entry.substr(kk + 1, Entry.length());
				if (S1 == SS)
					break;
			} // for

			if (S1 == SS) {
				SS = "* " + SS;
				ListUsed->AddObject(SS, (TObject *)-(ii + 1)); // wild variable
				string SSS = "Ranking module '" + S + "' to '" + SS + "'";
				//Memo1->Lines->Add(SSS);
				AddLinesToMemory(SSS);
			}
			else {
				S2 = "Ranking module '" + S + "' to an inaccessible variable '" + SS + "'";
				//Memo1->Lines->Add(S2);
				AddLinesToMemory(S2);
			}
		} // if
	} // for

	for (int ii = 0; ii < ListUsed->Count; ++ii) {

		// if wild see if exists anywhere
		if (ListUsed->Strings[ii][0] == '*') {
			string Var = ListUsed->Strings[ii];
			Var = Var.substr(2, Var.length());
			int jj = Best_Match(Var, List);
			if (jj > -1) { // match
				++Wild;
				int thisModule = (int)ListUsed->Objects[ii];
				thisModule = -(thisModule + 1);
				string Module = SelectedModules->Strings[thisModule];
				//        LogError("wild variable: '" + Module + " " + ListUsed->Strings[ii] + "' associated with '" + List->Strings[jj] + "'", WARNING);

				//        Memo1->Lines->Add("wild variable: '" + Module + " " + ListUsed->Strings[ii] + "' associated with '" + List->Strings[jj] + "'");

				ListUsed->Strings[ii] = List->Strings[jj];
				ListUsed->Objects[ii] = (TObject *)abs((int)ListUsed->Objects[ii] + 1); // make positive
			} // if
		} // if 'wild'

		else { // declared module source
			int NotFoundIndx = (int)ListUsed->Objects[ii];
			if (NotFoundIndx < 0) { // variable declared after use in current order?
				int indx = List->IndexOf(ListUsed->Strings[ii]);
				if (ListPuts->IndexOf(ListUsed->Strings[ii]) == -1 && indx == -1)
					++Error;
				if (indx > -1) {
					ListUsed->Objects[ii] = (TObject *)abs((int)ListUsed->Objects[ii] + 1); // make positive
					continue;
				}
			}
			else {
				continue; // OK
			}
		} // declared module source

		int NotFoundIndx = (int)ListUsed->Objects[ii];
		if (NotFoundIndx < 0 && ListUsed->Strings[ii][0] == '*') { // not found after wild variable search

																   // make suggestions
			string Message;
			string Message2(" Suggestions: ");
			++Error;
			LogError("wild variable not found: " + ListUsed->Strings[ii], TExcept::WARNING);

			int kk = abs((int)ListUsed->Objects[ii] + 1); // make positive

			string Sroot = ListUsed->Strings[ii];
			if (Sroot.find("@") != -1)
				Sroot = Sroot.substr(0, Sroot.find("@"));
			Message = "wild variable not found: \" " + Sroot + "\" used by " + SelectedModules->Strings[kk] + ".";
			string SW = ListUsed->Strings[ii];
			SW = SW.substr(2, ListUsed->Strings[ii].length());
			bool Once = false;
			bool rootVar = (SW.find("@") == -1); // note !root == group
			if (!rootVar)
				SW = SW.substr(0, SW.find("@"));
			for (itMap = Global::Mapdeclvar.begin(); itMap != Global::Mapdeclvar.end(); ++itMap) {
				SS = itMap->second.first;
				bool rootVar1 = (SS.find("@") == -1); // note !root == group
				if (!rootVar1)
					SS = SS.substr(0, SS.find("@"));
				if (SW == SS) {
					Once = true;
					string S = itMap->first;
					VandP V; V.Set((itMap->second).second);
					long Variation = V.GetV() & 2047;
					if (Variation > 0) {
						long NN = (long) (log(Variation) / log(2) + 1);
						string  AA = "#0";
						AA[1] += (char) NN;
						S += AA;
					}
					Message2 += S + ", ";
				}
			} // for

			if (!Once)
				//Memo1->Lines->Add(Message + " No " + Message2);
				AddLinesToMemory(Message + " No " + Message2);
			else
				//Memo1->Lines->Add(Message + Message2);
				AddLinesToMemory(Message + Message2);

		} // if
	} // for - long loop

	if (Error) {
		string temp = "" + Error;
		S = "Errors: " + temp + ';';
		string Line = StringOfChar('*', 80);;
		//Memo1->Lines->Add(Line);
		AddLinesToMemory(Line);
	}
	else {
		bool Loop = true;
		int Loops = 0;
		TStringList *OrgList = new TStringList; // source module + varName, original SelectedModules index

		for (int ii = 0; ii < SelectedModules->Count; ++ii) {
			OrgList->AddObject(SelectedModules->Strings[ii], (TObject*)ii);
			Entries.push_back(ClassEntry()); // create entries
		}

		while (Loop) {

			Loop = false; ++Loops;

			// set up ClassEntry vector
			for (int ii = 0; ii < SelectedModules->Count; ++ii) {
				Entries[ii].module = (ClassModule*)SelectedModules->Objects[ii];
				Entries[ii].Name = SelectedModules->Strings[ii]; // (Entries[ii].module)->Name.c_str(); //
				Entries[ii].rank = 0; // clear to highest rank
				Entries[ii].used = false; // set to not used

				unsigned long index = OrgList->IndexOf(SelectedModules->Strings[ii]);
				if (index < 0 || index > Entries.size() - 1) {
					LogError("Build error: outside range", TExcept::ERR);  // should not return
				}
				Entries[ii].OrigPos = index;
			} // for

			for (int ii = 0; ii < ListPuts->Count; ++ii) { // handle wild cards in Puts list
				ListPuts->Strings[ii] = ListUsed->Strings[(int)ListPuts->Objects[ii]];
			}

			// assign each module its current rank based upon the modules it uses
			for (int ii = 0; ii < ListUsed->Count; ++ii) {
				unsigned long thisModule = (int)ListUsed->Objects[ii]; // original postion

				for (unsigned long nn = 0; nn < Entries.size(); ++nn) {
					if (Entries[nn].OrigPos == thisModule) {
						thisModule = nn; // current position
						if (thisModule < 0 || thisModule > Entries.size() - 1) {
							LogError("Build error: outside range", TExcept::ERR);  // should not return
						}
						break;
					} // if
				} // for

				string Entry = ListUsed->Strings[ii];
				long kk = Entry.find(' ');
				string UsesModule = Entry.substr(0, kk); // extract module name
				string Var_only = Entry.substr(kk + 1, Entry.length() - kk-1); // extract variable name

				unsigned long index;
				ClassModule* checkModule = NULL;

				for (index = 0; index < Entries.size(); ++index) { // find modules position
					string Root = Entries[index].Name;
					if (Root == UsesModule) {
						checkModule = Entries[index].module;
						break;
					}
				}

				if (checkModule && checkModule->isGroup) { // resides in group
					Entries[index].used = true;
					continue;
				}
				if (index >= Entries.size())
					continue; // ignore

				Entries[index].used = true;

				if (UsesModule == Entries[thisModule].Name) // ignore if self
					continue;

				// assume if put or stat, module does not matter
				int jj = Best_Match(Var_only, ListPuts);
				if (jj > -1 && ii == ((int)ListPuts->Objects[jj]))
					continue; // ignore Puts

				jj = Best_Match(Var_only, ListStats);
				if (jj > -1)
					continue; // ignore Stats

				long B = (long) powl(2, index); // calculate weight
				Entries[thisModule].rank |= B; // OR - done more than once

			} // for

			  // sort by descending rank (ie ascending value)
			for (unsigned long ii = 0; ii < Entries.size() - 1; ++ii) {
				for (unsigned long jj = ii + 1; jj < Entries.size(); ++jj) {

					if (Entries[jj].rank < Entries[ii].rank) {
						MoveDown(Entries, ii, jj);
						Loop = true;
					}
				} // for
			} // for

			  // move entries with equal rank together in alphabetic order or peer rank
			for (long ii = 0; ii < (long)Entries.size() - 1; ++ii) {
				ClassModule * E2 = (ClassModule*)Entries[ii].module;
				if (E2->PeerRank < 0)
					Entries[ii].used = true;
				for (long jj = ii + 1; jj < (long) Entries.size(); ++jj) {
					if (Entries[jj].rank == Entries[ii].rank) {
						ClassModule * E1 = (ClassModule*)Entries[jj].module;

						if (labs(E1->PeerRank) < labs(E2->PeerRank)) {
							MoveDown(Entries, ii, jj);
							Loop = true;
						}
					} // if
				} // for
			} // for

			SelectedModules->Clear();

			// update SelectedModules
			for (unsigned long ii = 0; ii < Entries.size(); ++ii)
				SelectedModules->AddObject(Entries[ii].Name, (TObject*)Entries[ii].module);

			if (Loops > 20) { // too many - something funny
				Loop = false;
				Loops = -Loops;
			}
		} // while

		bool Removed = false;
		for (unsigned long ii = 0; ii < Entries.size() - 1; ++ii) {
			if (!Entries[ii].used && Entries[ii].Name != "basin") {  // never remove basin
				int result = IDYES;

				CString temp(Entries[ii].Name.c_str());
				result = MessageBox(temp, _T("Module not used!  Remove module?"), MB_YESNO);
				if (result != IDYES)
					continue;
				int indx = IndexOf(SelectedModules, Entries[ii].Name);
				SelectedModules->Delete(indx);
				Removed = true;
			}
		}

		Entries.clear();
		List->Clear();
		ListAll->Clear();
		ListUsed->Clear();
		ListPuts->Clear();
		ListStats->Clear();

		if (Removed) goto Again;

		int moves = 0;

		for (unsigned long ii = 0; ii < Entries.size(); ++ii)
			if (Entries[ii].OrigPos != ii) ++moves; // final number of modules moved

		if (Loops) {
			//Memo1->Lines->Add(" ");
			AddLinesToMemory(" ");
			LogError("Number of loops to build: " + to_string(Loops) + " and modules moved: " + to_string(moves), TExcept::WARNING);
			//Memo1->Lines->Add("Number of loops to build: " + to_string(Loops) + " and modules moved: " + to_string(moves));
			AddLinesToMemory("Number of loops to build: " + to_string(Loops) + " and modules moved: " + to_string(moves));
		}
		else {
			LogError("Problem with modules in build. Possibly modules referencing one another!", TExcept::WARNING);
			//Memo1->Lines->Add("Problem with modules in build. Possibly modules referencing one another!");
			AddLinesToMemory("Problem with modules in build. Possibly modules referencing one another!");
			MessageBox(_T("Problem with modules in build."), _T("Possibly modules referencing one another!"), MB_OK);
		}

		Entries.clear();
		delete OrgList;
		S = "";
	} // else


	//need to change
	/*
	if (Global::nlay != UpDownMAXLAY->Position || Global::nhru != UpDownMAXHRU->Position) {
		LogError("# of HRUs changed: *** edit parameters ***", WARNING);
		Memo1->Lines->Add(" ");
		Memo1->Lines->Add("# of HRUs changed: *** edit parameters ***");
	}

	if (Wild) S += "  Wild references: " + string(Wild) + ';';

	StatusBar1->SimpleText = S;
	StatusBar1->Repaint();
	*/

	delete List;
	delete ListAll;
	delete ListUsed;

	return Error;
}

long CConstruct::Best_Match(string Var, TStringList *List) {

	long found = 10;
	long Indx = -1;

	for (int jj = 0; jj < List->Count; ++jj) {
		string Entry = List->Strings[jj];
		long kk = Entry.find(' ');
		string Var1 = Entry.substr(kk + 1, Entry.length()); // root or group

		bool rootVar = (Var.find("@") == -1); // note !root == group
		bool rootVar1 = (Var1.find("@") == -1);

		if (Var1 == Var) { // exact match
			found = 0;
			Indx = jj;
			break;
		}
		else if (rootVar && !rootVar1 && Var == Var1.substr(0, Var1.find("@")) && found > 1) { // root variable to GRP match to root variable
			found = 1;
			Indx = jj;
		}
		else if (!rootVar && rootVar1 && Var.substr(0, Var.find("@")) == Var1 && found > 2) {  // GRP to root variable match to variable
			found = 2;
			Indx = jj;
		}
		else if (!rootVar && !rootVar1 && Var.substr(0, Var.find("@")) == Var1.substr(0, Var1.find("@")) && found > 3) { // GRP variable root to GRP variable root
			found = 3;
			Indx = jj;
		}
	} // for
	return Indx;
}


void CConstruct::UpdateCheckBoxes()
{
	AllModules->Clear();
	listbox_all_modules.ResetContent();
	//Max_Name_Width1 = 0;



	for (int ii = 0; ii < Global::AllModulesList->Count; ++ii) // fill ListBox1 from all levels used
	{
		CRHM::LMODULE str = ((ClassModule*)Global::AllModulesList->Objects[ii])->Lvl;
		if (str == CRHM::LMODULE::MACRO)
		{
			int a = 10;
		}

		if (((ClassModule*)Global::AllModulesList->Objects[ii])->Lvl == CRHM::LMODULE::BASIC)
		{
			if (checkbox_basic.GetCheck() == 1)
			{
				AddToAllModules(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//ListBox1->AddObject(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//listbox_all_modules.AddString((LPCTSTR)StandardConverterUtility::GetCStringFromStandardString(Global::AllModulesList->Strings[ii]));
				//string S = Global::AllModulesList->Strings[ii];
				//		if (S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
				//			Max_Name_Width1 = S.Length();
			}
		}

		if (((ClassModule*)Global::AllModulesList->Objects[ii])->Lvl == CRHM::LMODULE::ADVANCE)
		{
			if (checkbox_advanced.GetCheck() == 1)
			{
				AddToAllModules(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//ListBox1->AddObject(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//listbox_all_modules.AddString((LPCTSTR)StandardConverterUtility::GetCStringFromStandardString(Global::AllModulesList->Strings[ii]));
				//string S = Global::AllModulesList->Strings[ii];
				//		if (S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
				//			Max_Name_Width1 = S.Length();
			}
		}

		if (((ClassModule*)Global::AllModulesList->Objects[ii])->Lvl == CRHM::LMODULE::CUSTOM)
		{
			if (checkbox_custom.GetCheck() == 1)
			{
				AddToAllModules(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//ListBox1->AddObject(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//string S = Global::AllModulesList->Strings[ii];
				//		if (S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
				//			Max_Name_Width1 = S.Length();
			}
		}

		if (str == CRHM::LMODULE::MACRO)
		{
			if (checkbox_macro.GetCheck() == 1)
			{
				AddToAllModules(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//ListBox1->AddObject(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//string S = Global::AllModulesList->Strings[ii];
				//		if (S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
				//			Max_Name_Width1 = S.Length();
			}
		}

		if (((ClassModule*)Global::AllModulesList->Objects[ii])->Lvl == CRHM::LMODULE::OBSOL)
		{
			if (checkbox_obsolete.GetCheck() == 1)
			{
				AddToAllModules(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//ListBox1->AddObject(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//string S = Global::AllModulesList->Strings[ii];
				//		if (S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
				//			Max_Name_Width1 = S.Length();
			}
		}

		if (((ClassModule*)Global::AllModulesList->Objects[ii])->Lvl == CRHM::LMODULE::PROTO)
		{
			if (checkbox_prototype.GetCheck() == 1)
			{
				AddToAllModules(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//ListBox1->AddObject(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//string S = Global::AllModulesList->Strings[ii];
				//		if (S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
				//			Max_Name_Width1 = S.Length();
			}
		}

		if (((ClassModule*)Global::AllModulesList->Objects[ii])->Lvl == CRHM::LMODULE::SUPPORT)
		{
			if (checkbox_support.GetCheck() == 1)
			{
				AddToAllModules(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//ListBox1->AddObject(Global::AllModulesList->Strings[ii], (TObject *)Global::AllModulesList->Objects[ii]);
				//string S = Global::AllModulesList->Strings[ii];
				//		if (S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
				//			Max_Name_Width1 = S.Length();
			}
		}

	}

	//ListBox1->ScrollWidth = Max_Name_Width1 * 6;
}


void CConstruct::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here

	UpdateCheckBoxes();
}


void CConstruct::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here

	UpdateCheckBoxes();
}


void CConstruct::OnBnClickedCheck3()
{
	// TODO: Add your control notification handler code here

	UpdateCheckBoxes();
}


void CConstruct::OnBnClickedCheck4()
{
	// TODO: Add your control notification handler code here

	UpdateCheckBoxes();
}


void CConstruct::OnBnClickedCheck5()
{
	// TODO: Add your control notification handler code here

	UpdateCheckBoxes();
}


void CConstruct::OnBnClickedCheck6()
{
	// TODO: Add your control notification handler code here

	UpdateCheckBoxes();
}


void CConstruct::OnBnClickedCheck7()
{
	// TODO: Add your control notification handler code here

	UpdateCheckBoxes();
}


long CConstruct::BuildClick()
{
	int test = AllModules->Count;
	long Showing = SelectedModules->Count;
	if (Showing == 0) {
		//Global::nlay = UpDownMAXLAY->Position;
		//Global::nhru = UpDownMAXHRU->Position;
		return 1;
	}

	long Errors = CheckModel();

	if (Errors) {
		string str = "Errors: " + to_string(Errors);
		CString cstr(str.c_str());
		MessageBox(L"Model has unsatisfied module inputs or multiple definitions", cstr, MB_OK);
		return Errors;
	}

	if (ModifyBuild) {
		SaveBuildParameters();
		RemoveParameter();
	}

	MapAKACopy = Global::MapAKA; // keep any renamed OUTPUTs

	CRHMmain * crhmmain = CRHMmain::getInstance();
	crhmmain->ClearModules(false); // resets Global::MapAKA

	//Global::nlay = UpDownMAXLAY->Position;
	//Global::nhru = UpDownMAXHRU->Position;

	if (Global::nhru > Global::maxhru) {
		Update_Main_DIM(CRHM::NHRU, Global::nhru);
	}

	for (int ii = 0; ii < SelectedModules->Count; ++ii) { // handle variations
		ClassModule* thisModule = (ClassModule*)SelectedModules->Objects[ii];
		if (FormatMax(thisModule->variation_max) > 0) { // i.e. variation
			thisModule->variation = (unsigned short) pow(2, thisModule->hh - 1); // set variation
			int found = SelectedModules->Strings[ii].find("#");
			if (found > -1) { // remove any suffix
				SelectedModules->Strings[ii] = SelectedModules->Strings[ii].replace(SelectedModules->Strings[ii].length() - 2, 2, "");				
			}
		}
	}

	Global::OurModulesList->Assign(SelectedModules);

	Execute = true;

	Global::BuildFlag = CRHM::BUILD; // model loaded  was DECL

	if (!MapAKAVar.empty()) {
		Mapstr2::iterator it;

		for (it = MapAKAVar.begin(); it != MapAKAVar.end(); ++it)
			MapAKACopy.insert(*it);
	}
	//Close();
	return Errors;
}

void CConstruct::SaveBuildParameters() {

	ClassPar *thisPar;

	if (ModifyBuild) {

		RemoveSharedParams(); // change shared parameters to module parameters

		ParaList = new TStringList;

		// make map: keyed by parameter name holding pointer to parameter
		MapPar::iterator itPar;
		itPar = Global::MapPars.begin();
		while (itPar != Global::MapPars.end()) {
			thisPar = (*itPar).second;
			string S = string(((*itPar).second)->module.c_str()) + " " + ((*itPar).second)->param.c_str();
			if (ParaList->IndexOf(S) == -1) {
				ClassPar* par(new ClassPar(*thisPar));
				ParaList->AddObject(S, (TObject *)par);
			}
			++itPar;
		} // while
	} // if(ModifyBuild)
}


void CConstruct::ReadBuildParameters() {

	MapPar::iterator itPar;
	ClassPar *thisPar;

	if (ModifyBuild) {

		itPar = Global::MapPars.begin();
		while (itPar != Global::MapPars.end()) {
			thisPar = (*itPar).second;

			string S = string(((*itPar).second)->module.c_str()) + " " + ((*itPar).second)->param.c_str();
			int ii = ParaList->IndexOf(S);
			if (ii != -1) {
				ClassPar *OldPar = (ClassPar *)ParaList->Objects[ii];
				thisPar->Change(*OldPar);  // restore old value
			}
			++itPar;
		} // while

		for (int ii = 0; ii < ParaList->Count; ++ii)
			delete (ClassPar *)ParaList->Objects[ii]; // delete Objects

		delete ParaList;
		ParaList = NULL;

		CRHMmain * crhmmain = CRHMmain::getInstance();
		crhmmain->SqueezeParams();  // converts identical parameters to shared parameters
	} // if(ModifyBuild)
}


void CConstruct::RemoveSharedParams() { // pseudo shared parameters

	Global::Mapgetvar.clear();
	Global::Mapputvar.clear();
	Global::Mapreadvar.clear();
	Global::Mapdeclvar.clear();
	Global::Mapdeclstat.clear();
	Global::Mapdeclpar.clear();
	Global::Mapdeclobs.clear();

	Global::DeclRootList->Clear(); // used by AKA to stop looping

	Global::BuildFlag = CRHM::BUILD; // default value

	for (int ii = 0; ii < Global::OurModulesList->Count; ++ii)
		((ClassModule*)Global::OurModulesList->Objects[ii])->decl();


	Global::BuildFlag = CRHM::DECL; // model loaded

	ClassPar *thisPar;
	MapPar::iterator itPar;
	long count;
	// restore original module parameters from pseudo Shared parameters if they do not already exist

	itPar = Global::SharedMapPars.begin();
	while (itPar != Global::SharedMapPars.end()) {
		thisPar = (*itPar).second;
		count = ClassParFindParBld(thisPar);
		Global::MapPars.erase("Shared " + thisPar->param);
		delete thisPar; // parameter no longer needed
		++itPar;
	}
	Global::SharedMapPars.clear();
}

void CConstruct::RemoveParameter() {

	MapPar::iterator itPar;
	ClassPar *thisPar;

	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end();) {
		thisPar = (*itPar).second;

		int kk = IndexOf(SelectedModules, thisPar->module.c_str());

		if (kk == -1 && thisPar->module != "shared") {  // was basin
			Global::MapPars.erase(itPar++);
			delete thisPar;
		}
		else {
			++itPar;
		}
	}

}

long CConstruct::FormatMax(long M)
{
	M = M & 2047;
	if (M == 0) return 0;
	for (int ii = 1; ii < 8; ++ii) {
		M = (M >> 1);
		if (M == 0) return ii;
	}
	return -1; // should never get here
}

void CConstruct::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	long Errors = BuildClick();

	if (!Errors) { CDialog::OnOK(); }

	//CDialog::OnOK();
}


void CConstruct::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	
	CDialog::OnCancel();
}


void CConstruct::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void CConstruct::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here


	RemoveSelectedModule();

}
