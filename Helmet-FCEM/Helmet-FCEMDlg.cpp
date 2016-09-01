
// Helmet-FCEMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Helmet-FCEM.h"
#include "Helmet-FCEMDlg.h"
#include "afxdialogex.h"
#include "Vfw.h"
#include "windows.h"
#include "Main.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int background=0;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnDestroy();
//	afx_msg void OnPaint();
//	virtual BOOL OnInitDialog();
	afx_msg void OnDelerji();
	afx_msg void OnDelsanji();
	afx_msg void OnRenameerji();
	afx_msg void OnRenamesanji();
	afx_msg void OnTree2add();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_SIZE()
//	ON_WM_DESTROY()
//ON_WM_PAINT()
ON_COMMAND(ID_DelErji, &CAboutDlg::OnDelerji)
ON_COMMAND(ID_DelSanji, &CAboutDlg::OnDelsanji)
ON_COMMAND(ID_RenameErji, &CAboutDlg::OnRenameerji)
ON_COMMAND(ID_RenameSanji, &CAboutDlg::OnRenamesanji)
ON_COMMAND(ID_tree2add, &CAboutDlg::OnTree2add)
END_MESSAGE_MAP()


// CHelmetFCEMDlg �Ի���



CHelmetFCEMDlg::CHelmetFCEMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelmetFCEMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHelmetFCEMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	
}

BEGIN_MESSAGE_MAP(CHelmetFCEMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHelmetFCEMDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_STATIC_PICTURE, &CHelmetFCEMDlg::OnStnClickedStaticPicture)
	ON_COMMAND(IDOK, &CHelmetFCEMDlg::OnIdok)
END_MESSAGE_MAP()


// CHelmetFCEMDlg ��Ϣ�������

BOOL CHelmetFCEMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	 HBITMAP hBitmap2=NULL;
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_PICTURE);
    hBitmap2 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1 ));
	pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStatic->SetBitmap(hBitmap2);
	 HBITMAP hBitmap3=NULL;
	CStatic *pStatic3 = (CStatic *)GetDlgItem(IDC_STATIC_picture3);
    hBitmap3 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP14 ));
	pStatic3->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStatic3->SetBitmap(hBitmap3);
      HBITMAP   hBitmap;  
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP5));   
	 ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap); 
	  HBITMAP hBitmap1=NULL;
	  CStatic *pStatic1 = (CStatic *)GetDlgItem(IDC_STATIC_picture2);
      hBitmap1 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP6 ));
	  pStatic1->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
      pStatic1->SetBitmap(hBitmap1);
	 SetTimer(1,1000,NULL);  //������൱���趨��timer,���Ҫͣ��timer����KillTimer(TIMERID)
    	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHelmetFCEMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHelmetFCEMDlg::OnPaint()
{
	CPaintDC dc(this);

CDC memdc;
memdc.CreateCompatibleDC(&dc);//��������DC

CBitmap bkg;
bkg.LoadBitmap(IDB_BITMAP4);//����λͼ

BITMAP bkginfo;
bkg.GetBitmap(&bkginfo);//��ȡλͼ��Ϣ

memdc.SelectObject(&bkg);

RECT rect;
GetWindowRect(&rect);//��ȡ�Ի�����Ϣ

dc.StretchBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&memdc,0,0,bkginfo.bmWidth,bkginfo.bmHeight,SRCCOPY);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHelmetFCEMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHelmetFCEMDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	  KillTimer(1); 
	 Sleep(1000);
	  HBITMAP hBitmap1=NULL;
	  CStatic *pStatic1 = (CStatic *)GetDlgItem(IDC_STATIC_picture2);
      hBitmap1 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP7 ));
	  pStatic1->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
      pStatic1->SetBitmap(hBitmap1);
	  Sleep(500);

      hBitmap1 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP8 ));
	  pStatic1->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
      pStatic1->SetBitmap(hBitmap1);

	    HBITMAP hBitmap=NULL;
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_PICTURE);
    hBitmap =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP3 ));
	pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStatic->SetBitmap(hBitmap);

	  Sleep(500);

      hBitmap1 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP9 ));
	  pStatic1->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
      pStatic1->SetBitmap(hBitmap1);
     
	   Sleep(500);
      hBitmap1 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP10 ));
	  pStatic1->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
      pStatic1->SetBitmap(hBitmap1);

	  hBitmap =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP2 ));
      pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
      pStatic->SetBitmap(hBitmap);
	 
	   Sleep(500);
      hBitmap1 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP11 ));
	  pStatic1->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
      pStatic1->SetBitmap(hBitmap1);
	   Sleep(500);
      hBitmap1 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP12 ));
	  pStatic1->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
      pStatic1->SetBitmap(hBitmap1);
	   Sleep(500);


      hBitmap1 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP13 ));
	  pStatic1->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
      pStatic1->SetBitmap(hBitmap1);
	
	Sleep(500);
    

	CDialog::OnOK();
    Main a;
	a.DoModal();
		//return;
	
     

}


void CHelmetFCEMDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	 switch (nIDEvent)      
    {      
    case 1:      
        // ����յ�IDΪ1�Ķ�ʱ������Ϣ�����func1����      
        OnBnClickedButton1();
		 KillTimer(1);   
        break;      
   

    default:      
        break;      
    }      

	CDialogEx::OnTimer(nIDEvent);

}


void CHelmetFCEMDlg::OnStnClickedStaticPicture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CAboutDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	 if(nType == SIZE_MINIMIZED)  

           {  

                  ShowWindow(SW_HIDE); // ����С���У�����������              

           }  

	// TODO: �ڴ˴������Ϣ����������
}


//void CAboutDlg::OnDestroy()
//{
//	CDialogEx::OnDestroy();
//
//	// TODO: �ڴ˴������Ϣ����������
//}


//void CAboutDlg::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	
//}


//BOOL CAboutDlg::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//   
//	return TRUE;  // return TRUE unless you set the focus to a control
//
//}


void CHelmetFCEMDlg::OnIdok()
{
	// TODO: �ڴ���������������
}


BOOL CHelmetFCEMDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message   ==   WM_KEYDOWN)  
{  
    switch(pMsg->wParam)  
    {  
    case   VK_RETURN://���λس�  
          return   TRUE;  
    case   VK_ESCAPE://����Esc  
          return   TRUE;  
    }  
}    
	return CDialogEx::PreTranslateMessage(pMsg);
}

//jiacuole
void CAboutDlg::OnDelerji()//ɾ�������ڵ�
{
	// TODO: �ڴ���������������
}


void CAboutDlg::OnDelsanji()//ɾ�������ڵ�
{
	// TODO: �ڴ���������������
}


void CAboutDlg::OnRenameerji()//�����������ڵ�
{
	// TODO: �ڴ���������������
}


void CAboutDlg::OnRenamesanji()//�����������ڵ�
{
	// TODO: �ڴ���������������
}


void CAboutDlg::OnTree2add()
{
	// TODO: �ڴ���������������
}
