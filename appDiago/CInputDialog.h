#pragma once
class CInputDialog : public CDialogEx
{
public:
	CInputDialog();
	CString GetInput() { return m_strInput; } // 이 함수를 사용해 입력 값을 가져올 수 있습니다.
	CEdit edit_scriptName;
	CButton input_ok;
	CButton input_cancel;
protected:
	CInputDialog(CWnd* pParent);
	void DoDataExchange(CDataExchange* pDX);
	void OnBnClickedOk();
	void OnBnClickedCancel();
	DECLARE_MESSAGE_MAP()
	CString m_strInput; // 이 멤버 변수에 사용자의 입력을 저장합니다.
	//... 나머지 코드 ...
};