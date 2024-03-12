#pragma once
class CInputDialog : public CDialogEx
{
public:
	CInputDialog();
	CString GetInput() { return m_strInput; } // �� �Լ��� ����� �Է� ���� ������ �� �ֽ��ϴ�.
	CEdit edit_scriptName;
	CButton input_ok;
	CButton input_cancel;
protected:
	CInputDialog(CWnd* pParent);
	void DoDataExchange(CDataExchange* pDX);
	void OnBnClickedOk();
	void OnBnClickedCancel();
	DECLARE_MESSAGE_MAP()
	CString m_strInput; // �� ��� ������ ������� �Է��� �����մϴ�.
	//... ������ �ڵ� ...
};