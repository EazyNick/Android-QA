
// appDiagoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CInputDialog.h"
#include "appDiago.h"
#include "appDiagoDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "comip.h"
#include "framework.h"
#include <afxwin.h> // MFC core and standard components
#include <afxext.h> // MFC extensions
#include <afxdisp.h> // MFC Automation classes
#include <iostream>
#include <windows.h>
#include <cstdlib>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CappDiagoDlg 대화 상자

BEGIN_DHTML_EVENT_MAP(CappDiagoDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()


CappDiagoDlg::CappDiagoDlg(CWnd* pParent /*=nullptr*/)
	: CDHtmlDialog(IDD_APPDIAGO_DIALOG, IDR_HTML_APPDIAGO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CappDiagoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	// IDC_listControl는 쉘 리스트 컨트롤의 ID입니다.
	DDX_Control(pDX, IDC_listControl, m_wnd_list);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}

BEGIN_MESSAGE_MAP(CappDiagoDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON1, &CappDiagoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CappDiagoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CappDiagoDlg::OnBnClickedButton3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_listControl, &CappDiagoDlg::OnLvnItemchangedlistcontrol)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CappDiagoDlg::OnTcnSelchangeTab1)
	ON_COMMAND(ID_POPUP_32771, &CappDiagoDlg::OnSaveTab)
	ON_COMMAND(ID_POPUP_32772, &CappDiagoDlg::OnCloseTab)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_BUTTON4, &CappDiagoDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

// CappDiagoDlg 메시지 처리기

BOOL CappDiagoDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	UpdateData(False);

	// mshellTree 초기화 검증 테스트
	if (m_wnd_list.GetSafeHwnd() == NULL) {
		AfxMessageBox(_T("mshellList 생성안됨"));
		return False;
	}
	
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 컨텍스트 메뉴 생성
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_POPUP_32771, _T("저장"));
	menu.AppendMenu(MF_STRING, ID_POPUP_32772, _T("닫기"));

	font.CreatePointFont(150, _T("Arial"));
	CButton* file_btn = (CButton*)GetDlgItem(IDC_BUTTON1);
	CButton* add_btn = (CButton*)GetDlgItem(IDC_BUTTON2);
	CButton* del_btn = (CButton*)GetDlgItem(IDC_BUTTON3);
	// file_btn->SetFont(&font);
	add_btn->SetFont(&font);
	del_btn->SetFont(&font);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CappDiagoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CappDiagoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CappDiagoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CappDiagoDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CappDiagoDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}

// ListCtrl 아이템 선택시
void CappDiagoDlg::OnLvnItemchangedlistcontrol(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 윈도우 핸들러가 정상적으로 적용되어있는지 확인.
	if (m_wnd_list.GetSafeHwnd() != NULL) {
		int nItem = m_wnd_list.GetNextItem(-1, LVNI_SELECTED);

		if (nItem != -1)
		{
			POSITION pos = m_wnd_list.GetFirstSelectedItemPosition();
			CString strItemText = m_wnd_list.GetItemText(nItem, 0);
			CString strExtension = strItemText.Right(4).MakeLower();
			strFileText = "";
			if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED)) {

				int nIdx = pNMLV->iItem;
				if (strExtension.Find(_T(".")) == -1)
				{
					if (m_wnd_list.GetItemPath(path, nItem)) {
						set_FolderPath(path);
					}
				}
				if (strExtension == _T(".txt") || strExtension == _T(".cpp") || strExtension == _T(".h") || strExtension == _T(".py"))
				{
					// .txt, .cpp, .h, .py 파일을 텍스트로 읽음
					if (m_wnd_list.GetItemPath(path, nItem)) {
						set_path(path);
					}
					// strItemText는 추가하려는 탭의 이름

					bool bExists = false; // 같은 이름의 탭이 이미 존재하는지 여부

					// 모든 탭의 이름을 검사

					for (int i = 0; i < m_tabCtrl.GetItemCount(); ++i)
					{
						TCITEM ti;
						TCHAR szText[100];
						ti.mask = TCIF_TEXT;
						ti.pszText = szText;
						ti.cchTextMax = sizeof(szText) / sizeof(TCHAR);
						m_tabCtrl.GetItem(i, &ti);
						if (strItemText == ti.pszText)
						{
							bExists = true; // 같은 이름의 탭이 이미 존재함
							break;
						}
					}

					// 같은 이름의 탭이 없을 경우에만 새 탭 추가
					if (!bExists)
					{
						if (!file.Open(get_path(), CFile::modeRead | CFile::typeText))
						{
							AfxMessageBox(_T("파일을 열지 못했습니다."));
							*pResult = 0;
							return;
						}
						else {
							m_vecPath.push_back(get_path());
						}
						
						// 파일의 모든 줄을 읽음
						while (file.ReadString(strLine))
						{
							strFileText += strLine;
							strFileText += _T("\r\n"); // 줄바꿈 문자 추가
						}
						AfxMessageBox(strFileText);
						file.Close();

						// 탭 아이템 추가
						int nTab = m_tabCtrl.InsertItem(m_tabCtrl.GetItemCount(), strItemText);

						// 탭 페이지 에디트 컨트롤 생성 및 텍스트 설정
						CRect rect;
						m_tabCtrl.GetClientRect(&rect);
						rect.DeflateRect(5, 25, 5, 5); // 탭 헤더를 고려하여 조정
						CEdit* pEdit = new CEdit;

						pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL, rect, &m_tabCtrl, IDC_EDIT1 + nTab);
						int nSel = m_tabCtrl.GetCurSel();
						m_vecTabEdits.push_back(pEdit);

						// 벡터에 텍스트 저장
						m_vecTabTexts.push_back(strFileText);
						m_vecTabEdits[nSel]->SetWindowText(m_vecTabTexts[nSel]);
						if (m_vecTabTexts.size() != m_vecTabEdits.size())
						{
							AfxMessageBox(_T("m_vecTabTexts 벡터의 크기와 m_tabEdits 컨트롤의 개수가 일치하지 않습니다."));
							exit(0);
						}
						else {
							
						}
					}
				}
			}
		}
	}
	*pResult = 0;
}

// TAB Edit 전환 데이터기억
void CappDiagoDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int nSel = m_tabCtrl.GetCurSel(); // 현재 선택된 탭의 인덱스를 얻음

	// 이전에 선택했던 탭의 에디트 컨트롤을 숨김
	if (m_nPrevSel >= 0 && m_nPrevSel < m_vecTabEdits.size())
	{
		CString strText;
		m_vecTabEdits[m_nPrevSel]->GetWindowText(strText);
		m_vecTabTexts[m_nPrevSel] = strText;
		m_vecTabEdits[m_nPrevSel]->ShowWindow(SW_HIDE);
	}

	// 현재 선택된 탭의 에디트 컨트롤을 표시
	if (nSel >= 0 && nSel < m_vecTabEdits.size())
	{
		m_vecTabEdits[nSel]->SetWindowText(m_vecTabTexts[nSel]);
		m_vecTabEdits[nSel]->ShowWindow(SW_SHOW);
		m_nPrevSel = nSel; // 이전에 선택했던 탭의 인덱스를 업데이트
	}

	m_nPrevSel = nSel; // 이전에 선택했던 탭의 인덱스를 업데이트

	*pResult = 0;
}

// 컨텍스트 메뉴
void CappDiagoDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// 탭 컨트롤의 클라이언트 영역 좌표로 변환
	CPoint clientPoint = point;
	m_tabCtrl.ScreenToClient(&clientPoint);

	// 마우스 위치가 탭 컨트롤 내부인지 확인
	CRect rect;
	m_tabCtrl.GetClientRect(&rect);

	if (rect.PtInRect(clientPoint))
	{
		// 컨텍스트 메뉴 표시
		menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

// 컨텍스트 (TAB_bar)저장
void CappDiagoDlg::OnSaveTab()
{
	editFile_save(); // '저장' 메뉴 아이템 선택 시 처리
}
// 컨텍스트 (TAB_bar)닫기
void CappDiagoDlg::OnCloseTab()
{
	// '닫기' 메뉴 아이템 선택 시 처리

	int nTab = m_tabCtrl.GetCurSel(); // 현재 선택된 탭의 인덱스를 얻음
	if (nTab != -1) // 탭이 선택되어 있는 경우
	{
		// 탭 삭제
		m_tabCtrl.DeleteItem(nTab);

		// 관련 CString 및 CEdit* 삭제
		m_vecTabTexts.erase(m_vecTabTexts.begin() + nTab);
		delete m_vecTabEdits[nTab]; // CEdit 객체 삭제
		m_vecTabEdits.erase(m_vecTabEdits.begin() + nTab);
		m_vecPath.erase(m_vecPath.begin() + nTab);
	}

}

// key 메세지 호출
BOOL CappDiagoDlg::PreTranslateMessage(MSG* pMsg)
{
	// Edit (Ctrl + s)저장기능
	if (pMsg->message == WM_KEYDOWN &&
		GetKeyState(VK_CONTROL) < 0 &&
		pMsg->wParam == 'S') // Ctrl + S를 눌렀을 때
	{
		editFile_save();
	}

	// 키보드 입력 확인
	if (pMsg->message == WM_KEYDOWN)
	{
		// Tab 들여쓰기
		if (pMsg->wParam == VK_TAB)
		{
			CEdit* pEdit = (CEdit*)GetFocus(); // 현재 포커스를 가지고 있는 Edit 컨트롤을 가져옵니다.
			if (pEdit != NULL)
			{
				int nStartChar, nEndChar;
				pEdit->GetSel(nStartChar, nEndChar); // 현재 선택된 텍스트의 범위를 가져옵니다.
				pEdit->ReplaceSel(_T("\t")); // 선택된 텍스트를 탭 문자로 대체합니다.

				return TRUE; // 메시지 처리를 여기서 종료합니다.
			}
		}

		// Enter 키가 눌렸을 경우
		if (pMsg->wParam == VK_RETURN)
		{
			// Edit 컨트롤이 포커스를 가지고 있는지 확인
			CWnd* pFocusWnd = GetFocus();

			if (pFocusWnd != nullptr && pFocusWnd->IsKindOf(RUNTIME_CLASS(CEdit)))
			{
				// 현재 텍스트를 가져옴
				CString strText;
				((CEdit*)pFocusWnd)->GetWindowText(strText);

				// 현재 커서 위치를 가져옴
				int startChar, endChar;
				((CEdit*)pFocusWnd)->GetSel(startChar, endChar);

				// 현재 커서 위치에 줄바꿈 문자 삽입
				strText.Insert(startChar, _T("\r\n"));

				// 텍스트를 다시 설정
				((CEdit*)pFocusWnd)->SetWindowText(strText);

				// 커서를 줄바꿈 문자 뒤로 이동
				((CEdit*)pFocusWnd)->SetSel(startChar + 2, startChar + 2);

				return TRUE; // 메시지 처리 완료
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CappDiagoDlg::editFile_save() {
	CEdit* pEdit = (CEdit*)GetFocus(); // 현재 포커스를 가지고 있는 Edit 컨트롤을 가져옵니다.

	if (pEdit != NULL)
	{
		if (MessageBox(_T("저장하시겠습니까?"), _T("저장"), MB_YESNO) == IDYES)
		{
			// 사용자가 '예'를 선택했을 때의 처리
			int nSel = m_tabCtrl.GetCurSel();

			CEdit* pEdit = m_vecTabEdits[nSel];
			CString path = m_vecPath[nSel];
			CString strText;

			if (file.Open(path, CFile::modeCreate | CFile::modeWrite))
			{
				pEdit->GetWindowText(strText); // 에디트 컨트롤의 텍스트를 얻음
				m_vecTabTexts[nSel] = strText;
				m_vecTabEdits[nSel]->SetWindowText(m_vecTabTexts[nSel]);
				file.WriteString(strText); // 파일에 텍스트 쓰기
				file.Close();
			}
			else
			{
				MessageBox(_T("파일을 저장할 수 없습니다."), _T("오류"), MB_OK);
			}
		}
	}
}


// 파일선택 버튼
void CappDiagoDlg::OnBnClickedButton1()
{
	// 폴더 선택 대화 상자를 엽니다.
	BROWSEINFO bi;
	TCHAR szPath[MAX_PATH] = { 0 };
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = this->GetSafeHwnd();
	bi.lpszTitle = _T("폴더를 선택하세요:");

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		// 선택된 폴더의 경로를 가져옵니다.
		TCHAR path[MAX_PATH];

		if (SHGetPathFromIDList(pidl, path))
		{
			// path 변수에 선택된 폴더의 경로가 저장됩니다.

			// IMalloc 인터페이스 포인터를 얻습니다.

			LPMALLOC pMalloc = NULL;

			if (SUCCEEDED(SHGetMalloc(&pMalloc)))

			{

				// pidl 메모리를 해제합니다.

				pMalloc->Free(pidl);

				pMalloc->Release();
			}

			//테스트 코드
			// m_ShellTree에 경로를 적용합니다.
			if (!PathFileExists(path)) // 경로 확인
			{
				AfxMessageBox(_T("유효하지 않은 경로입니다."));
				return;
			}

			if (m_wnd_list.GetSafeHwnd() == NULL) // 쉘 트리 컨트롤 초기화 확인
			{
				AfxMessageBox(_T("쉘 트리 컨트롤이 초기화되지 않았습니다."));
				return;
			}

			// m_ShellTree에 경로를 적용합니다.
			MessageBox(path);
			set_FolderPath(path);
			m_wnd_list.DisplayFolder(path);
		}
	}
}

// 스크립트 추가 버튼
void CappDiagoDlg::OnBnClickedButton2()
{
	// 1. 사용자에게 .cpp 파일의 이름을 입력받습니다.
	CInputDialog dlgInput;

	if (dlgInput.DoModal() != IDOK)
		return;

	// 3. Shell List Control을 갱신합니다.
	m_wnd_list.Refresh();
}

void CappDiagoDlg::OnBnClickedButton3()
{
	// 1. 파일 탐색기를 열어서 사용자가 파일을 선택하도록 합니다.
	CFileDialog dlg(TRUE, NULL, get_FolderPath() + _T("\\"), OFN_ALLOWMULTISELECT);
	if (dlg.DoModal() == IDOK)
	{
		// 2. 선택한 파일을 삭제합니다.
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			CString strFilePath = dlg.GetNextPathName(pos); // 사용자가 선택한 파일의 경로를 얻습니다.
			if (!DeleteFile(strFilePath))
			{
				AfxMessageBox(_T("파일을 삭제할 수 없습니다.") + strFilePath);
			}
		}
		// 3. Shell List Control을 갱신합니다.
		m_wnd_list.Refresh();
	}
}

BOOL IsPathValid(const CString& strPath)
{
	DWORD dwAttrib = GetFileAttributes(strPath);
	if (dwAttrib == INVALID_FILE_ATTRIBUTES)
	{
		// 파일이나 디렉토리가 존재하지 않으면
		return FALSE;
	}
	// 파일이나 디렉토리가 존재하면
	return TRUE;
}

void CappDiagoDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString exePath;
	CString m_strCppFilePath = get_path();
	CString m_strExeFilePath = _T("C:\\Windows\\System32\\cmd.exe");
	CString command_path;
	CString adb_zip;
	command_path.Format(_T("cl %s /c"), m_strCppFilePath);
	// wchar_t 배열을 선언하고 충분한 크기를 할당합니다.
	wchar_t commandLine[1024];
	DWORD bufferSize = MAX_PATH;
	wchar_t currentDirectory[MAX_PATH];

	if (GetCurrentDirectory(bufferSize, currentDirectory)) {
		adb_zip.Format(_T("cl /I C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared %s\\adb_shell_input.cpp /c"), currentDirectory);
		AfxMessageBox(adb_zip);
	}
	exePath.Format(_T("link %s adb_shell_input.obj"), ChangeExtensionToCstr(out_fileName(get_path()),_T("obj")));
	// Visual C++ 컴파일러를 사용한 컴파일 예제
   // "yourProgram.cpp"를 현재 디렉토리에 컴파일합니다.
	CStringA target_objPath(command_path);
	CStringA adb_objPath(adb_zip);
	CStringA target_exePath(exePath);
	CStringA profile_play(ChangeExtensionToCstr(out_fileName(get_path()), _T("exe")));
	int objResult = system(target_objPath);
	int objAdb = system(adb_objPath);
	if (objResult != 0 || objAdb != 0) {
		AfxMessageBox(_T("컴파일 실패"));
	}
	system(target_exePath);
	// 컴파일된 프로그램 실행
	system(profile_play);
}

CString CappDiagoDlg::out_fileName(CString str) {

	// '\\' 문자를 뒤에서부터 찾는다
	int pos = str.ReverseFind('\\');

	if (pos != -1) {
		// 찾은 위치 다음부터 문자열 끝까지가 파일 이름이다
		CString fileName = str.Mid(pos + 1);
		std::wcout << _T("File Name: ") << (LPCTSTR)fileName << std::endl;
		return fileName;
	}
	else {
		// '\\' 문자가 없는 경우, 전체 경로가 파일 이름이다
		std::wcout << _T("File Name: ") << (LPCTSTR)str << std::endl;
		return str;
	}
}

CString CappDiagoDlg::ChangeExtensionToCstr(CString path, CString key) {

	// 마지막 '.'의 위치를 찾습니다.
	int dotIndex = path.ReverseFind('.');

	if (dotIndex != -1) { // '.'이 발견되면
		path = path.Left(dotIndex) + key; // 확장자를 .obj로 변경
	}
	else {
		// 확장자가 없는 경우, .obj를 추가
		path += key;
	}
	return path;
}