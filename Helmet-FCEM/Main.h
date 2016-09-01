#pragma once
#include "afxext.h"
#include "afxwin.h"


// Main 对话框

class Main : public CDialogEx
{
	DECLARE_DYNAMIC(Main)

public:
	Main(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Main();

// 对话框数据
	enum { IDD = IDD_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	CBitmapButton m_button;
	afx_msg void OnBnSetfocusButton1();
	afx_msg void OnBnSetfocusOk();
	CBitmapButton m_okbutton;
	afx_msg void OnBnClickedSmall();
	CBitmapButton m_smallbutton;
	afx_msg void OnBnSetfocusSmall();
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
//	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL DestroyWindow();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	CBitmapButton m_newbuttom;
//	afx_msg void OnBnSetfocusButton5();
	CBitmapButton m_openbuttton;
//	afx_msg void OnBnSetfocusButton6();
	CBitmapButton m_savebutton;
//	afx_msg void OnBnSetfocusButton7();
	CBitmapButton m_delbutton;
//	afx_msg void OnBnSetfocusButton8();

	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	CBitmapButton m_excelbutton;
//	afx_msg void OnBnSetfocusButton9();
	afx_msg void OnBnSetfocusButton14();
	CBitmapButton m_jsbutton;
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	CBitmapButton m_addbtn;
	afx_msg void OnBnSetfocusButton24();
	afx_msg void OnBnClickedButton24();
	CBitmapButton m_rnamebtn;
	afx_msg void OnBnClickedButton25();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CBitmapButton m_sxbtn;
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton9();
	CBitmapButton m_setting;
	CBitmapButton m_tools;
//	CButton m_help;
	CBitmapButton m_help;
	CBitmapButton m_av;
	CBitmapButton m_ov;
	CBitmapButton m_aj;
	CBitmapButton m_oj;
	CBitmapButton m_zhexian;
	CBitmapButton m_zhuzt;
	CBitmapButton m_bingzt;
};
