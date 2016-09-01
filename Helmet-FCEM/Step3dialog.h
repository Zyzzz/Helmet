#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxext.h"


// Step3dialog �Ի���

class Step3dialog : public CDialogEx
{
	DECLARE_DYNAMIC(Step3dialog)

public:
	Step3dialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Step3dialog();

// �Ի�������
	enum { IDD = IDD_Step3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	void shuaxinlist(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_edit;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
//	CBitmapButton m_chushihua;
	CBitmapButton m_tip;
	afx_msg void OnBnClickedButton27();
	void Lin_ExportListToExcel(CListCtrl &m_List);
	CString Lin_GetEnglishCharacter(int Num);
	void excel(void);
	CBitmapButton m_rsave;
	afx_msg void OnBnClickedButton28();
};
