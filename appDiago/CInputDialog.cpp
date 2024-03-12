#include "pch.h"
#include "CInputDialog.h"
#include "appDiagoDlg.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(CInputDialog, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_BN_CLICKED(IDC_INPUT_BUTTON1, &CInputDialog::OnBnClickedOk)
    ON_BN_CLICKED(IDC_INPUT_BUTTON2, &CInputDialog::OnBnClickedCancel)
END_MESSAGE_MAP()
// CInputDialog.cpp

CInputDialog::CInputDialog()
    : CDialogEx(IDRETRY), m_strInput(_T(""))
{
    // TODO: 여기에 생성자 코드를 추가합니다.
}


// CInputDialog.cpp 파일
void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// TODO: 여기에 DDX/DDV 호출을 추가합니다.
	DDX_Control(pDX, IDC_EDIT1, edit_scriptName);
}

void CInputDialog::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CappDiagoDlg* dl = (CappDiagoDlg*)AfxGetMainWnd();
    if (dl == nullptr) {
        return;
    }
    CString strText;
    edit_scriptName.GetWindowText(strText); // 에디트 컨트롤의 텍스트를 가져옴
    AfxMessageBox(dl->get_FolderPath());
    CString strPath = dl->get_FolderPath() + _T("\\") + strText + _T(".cpp"); // 실제 디렉토리 경로로 변경하세요
    CFile file;

    if (file.Open(strPath, CFile::modeCreate | CFile::modeWrite))
    {
        file.Write(strText, strText.GetLength()); // 파일에 텍스트를 씀
        file.Close(); // 파일을 닫음
    }
    else
    {
        AfxMessageBox(_T("파일을 저장할 수 없습니다."));
        return;
    }
    CDialogEx::OnOK();
}



void CInputDialog::OnBnClickedCancel()                          
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CDialogEx::OnCancel(); // 대화상자를 닫음
}

