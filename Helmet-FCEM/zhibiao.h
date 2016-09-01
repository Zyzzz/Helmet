#pragma once
#include "afxext.h"


// zhibiao 对话框

class zhibiao : public CDialogEx
{
	DECLARE_DYNAMIC(zhibiao)

public:
	zhibiao(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~zhibiao();

// 对话框数据
	enum { IDD = IDD_ZHIBIAO_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedButton2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCheck39();
	CBitmapButton m_quanxuanbtn;
	CBitmapButton m_nochoosebtn;
	CBitmapButton m_cancle;
	CBitmapButton m_ok;
};
