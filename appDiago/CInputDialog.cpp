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
    // TODO: ���⿡ ������ �ڵ带 �߰��մϴ�.
}


// CInputDialog.cpp ����
void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// TODO: ���⿡ DDX/DDV ȣ���� �߰��մϴ�.
	DDX_Control(pDX, IDC_EDIT1, edit_scriptName);
}

void CInputDialog::OnBnClickedOk()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    CappDiagoDlg* dl = (CappDiagoDlg*)AfxGetMainWnd();
    if (dl == nullptr) {
        return;
    }
    CString strText;
    edit_scriptName.GetWindowText(strText); // ����Ʈ ��Ʈ���� �ؽ�Ʈ�� ������
    AfxMessageBox(dl->get_FolderPath());
    CString strPath = dl->get_FolderPath() + _T("\\") + strText + _T(".cpp"); // ���� ���丮 ��η� �����ϼ���
    CFile file;

    if (file.Open(strPath, CFile::modeCreate | CFile::modeWrite))
    {
        file.Write(strText, strText.GetLength()); // ���Ͽ� �ؽ�Ʈ�� ��
        file.Close(); // ������ ����
    }
    else
    {
        AfxMessageBox(_T("������ ������ �� �����ϴ�."));
        return;
    }
    CDialogEx::OnOK();
}



void CInputDialog::OnBnClickedCancel()                          
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    CDialogEx::OnCancel(); // ��ȭ���ڸ� ����
}

