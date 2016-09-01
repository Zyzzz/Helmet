
// Helmet-FCEMDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CHelmetFCEMDlg 对话框
class CHelmetFCEMDlg : public CDialogEx
{
// 构造
public:
	CHelmetFCEMDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HELMETFCEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
//	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	CStatic m_picture;
	afx_msg void OnStnClickedStaticPicture();
	HICON m_hIcon;
//	CProgressCtrl m_ctrlProgress;
	afx_msg void OnIdok();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
