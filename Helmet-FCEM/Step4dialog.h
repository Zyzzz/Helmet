#pragma once
#include "afxcmn.h"
#include "afxext.h"


// Step4dialog �Ի���

class Step4dialog : public CDialogEx
{
	DECLARE_DYNAMIC(Step4dialog)

public:
	Step4dialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Step4dialog();

// �Ի�������
	enum { IDD = IDD_Step4_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton1();
	void AV(void);
	void OV(void);
	void AJ(void);
	void OJ(void);
	void Lin_ExportListToExcel(CListCtrl &m_List);
	CString Lin_GetEnglishCharacter(int Num);
	void excel(void);
	CBitmapButton m_tip;
	afx_msg void OnBnClickedButton27();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void shuaxin(void);
	CString m_suanzi;
};
