
// Helmet-FCEMDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CHelmetFCEMDlg �Ի���
class CHelmetFCEMDlg : public CDialogEx
{
// ����
public:
	CHelmetFCEMDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HELMETFCEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
//	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
