
// appDiagoDlg.h: 헤더 파일
//

#pragma once
#include <vector>

class CappDiagoDlg : public CDHtmlDialog
{
// 생성입니다.
protected:
	CMFCShellListCtrl m_wnd_list;
	CTabCtrl m_tabCtrl;
	CMenu menu;
	std::vector<CEdit*> m_vecTabEdits;
	std::vector<CString> m_vecTabTexts;
	std::vector<CString> m_vecPath;
	CStdioFile file;
	CString strFileText;
	CString strLine;
	CString path;
	CFont font;
	int m_nPrevSel;
public:
	CappDiagoDlg(CWnd* pParent = nullptr); // 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPDIAGO_DIALOG, IDH = IDR_HTML_APPDIAGO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// 구현입니다.
protected:
	HICON m_hIcon;
	
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	CString get_path() {
		return path;
	}
	void set_path(CString key) {
		path = key;
	}
	CString get_FolderPath() {
		return path;
	}
	void set_FolderPath(CString key) {
		path = key;
	}
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedlistcontrol(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	void OnContextMenu(CWnd*, CPoint point);
	void OnSaveTab();
	void OnCloseTab();
	BOOL PreTranslateMessage(MSG* pMsg);
	void editFile_save();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CString out_fileName(CString str);
	CString ChangeExtensionToCstr(CString path, CString key);
};
