
// Helmet-FCEMDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CHelmetFCEMDlg 对话框



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


// CHelmetFCEMDlg 消息处理程序

BOOL CHelmetFCEMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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
	 SetTimer(1,1000,NULL);  //这里就相当于设定了timer,如果要停掉timer就是KillTimer(TIMERID)
    	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHelmetFCEMDlg::OnPaint()
{
	CPaintDC dc(this);

CDC memdc;
memdc.CreateCompatibleDC(&dc);//创建兼容DC

CBitmap bkg;
bkg.LoadBitmap(IDB_BITMAP4);//载入位图

BITMAP bkginfo;
bkg.GetBitmap(&bkginfo);//获取位图信息

memdc.SelectObject(&bkg);

RECT rect;
GetWindowRect(&rect);//获取对话框信息

dc.StretchBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&memdc,0,0,bkginfo.bmWidth,bkginfo.bmHeight,SRCCOPY);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHelmetFCEMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHelmetFCEMDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 switch (nIDEvent)      
    {      
    case 1:      
        // 如果收到ID为1的定时器的消息则调用func1函数      
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
	// TODO: 在此添加控件通知处理程序代码
}


void CAboutDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	 if(nType == SIZE_MINIMIZED)  

           {  

                  ShowWindow(SW_HIDE); // 当最小化市，隐藏主窗口              

           }  

	// TODO: 在此处添加消息处理程序代码
}


//void CAboutDlg::OnDestroy()
//{
//	CDialogEx::OnDestroy();
//
//	// TODO: 在此处添加消息处理程序代码
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
	// TODO: 在此添加命令处理程序代码
}


BOOL CHelmetFCEMDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message   ==   WM_KEYDOWN)  
{  
    switch(pMsg->wParam)  
    {  
    case   VK_RETURN://屏蔽回车  
          return   TRUE;  
    case   VK_ESCAPE://屏蔽Esc  
          return   TRUE;  
    }  
}    
	return CDialogEx::PreTranslateMessage(pMsg);
}

//jiacuole
void CAboutDlg::OnDelerji()//删除二级节点
{
	// TODO: 在此添加命令处理程序代码
}


void CAboutDlg::OnDelsanji()//删除三级节点
{
	// TODO: 在此添加命令处理程序代码
}


void CAboutDlg::OnRenameerji()//重命名二级节点
{
	// TODO: 在此添加命令处理程序代码
}


void CAboutDlg::OnRenamesanji()//重命名三级节点
{
	// TODO: 在此添加命令处理程序代码
}


void CAboutDlg::OnTree2add()
{
	// TODO: 在此添加命令处理程序代码
}
