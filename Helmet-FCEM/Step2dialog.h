#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxext.h"


// Step2dialog 对话框

class Step2dialog : public CDialogEx
{
	DECLARE_DYNAMIC(Step2dialog)

public:
	Step2dialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Step2dialog();

// 对话框数据
	enum { IDD = IDD_Step2_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CListCtrl m_list;

	CEdit m_edit;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	void shuaxinlist(void);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBitmapButton m_guiyihuabtn;
	afx_msg void OnBnClickedButton1();
	CBitmapButton m_tip;
	afx_msg void OnBnClickedButton27();
//	void excel(void);
	void Lin_ExportListToExcel(CListCtrl &m_List);
	CString Lin_GetEnglishCharacter(int Num);
	void excel(void);
	CBitmapButton m_save;
	afx_msg void OnBnClickedButton28();
//	float m_result;
};
