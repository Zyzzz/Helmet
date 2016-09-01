#pragma once
#include "afxcmn.h"
#include "afxext.h"


// Step1dialog 对话框

class Step1dialog : public CDialogEx
{
	DECLARE_DYNAMIC(Step1dialog)

public:
	Step1dialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Step1dialog();

// 对话框数据
	enum { IDD = IDD_Step1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_ctltree;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnRename();
	afx_msg void OnDel();
//	afx_msg void OnAdd();
	afx_msg void OnNMRDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedButton2();
	void deltreeitem();

	void updatatree(void);
	afx_msg void OnRename();
	afx_msg void OnAdd();
	CTreeCtrl m_ctltree1;
	afx_msg void OnNMRClickTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeleditTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree2(NMHDR *pNMHDR, LRESULT *pResult);
	void additem(void);
	void renameitem(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnYijiadderji();
	afx_msg void OnErjiaddsanji();
	afx_msg void OnDelerji();
	afx_msg void OnDelsanji();
	afx_msg void OnRenameerji();
	afx_msg void OnRenamesanji();
	afx_msg void OnTree2add();
	afx_msg void OnTree2del();
	afx_msg void OnTree2rename();
	afx_msg void OnBnClickedButton1();
	CBitmapButton m_save;
	CBitmapButton m_tip;
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton27();
};
