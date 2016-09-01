// Main.cpp : 实现文件
//

#include "stdafx.h"
#include "Helmet-FCEM.h"
#include "Main.h"
#include "afxdialogex.h"
#include "string.h"
#include "Step1dialog.h"
#include "Step2dialog.h"
#include "Step3dialog.h"
#include "Step4dialog.h"
#include <locale>
#include "zhibiao.h"

int av=1,ov=0,aj=0,oj=0;//全局变量 选择算法分别是M(∧,∨)M(.,∨)M(∧,+)M(.,+)
extern int treesave;  //第一步建立的指标树和评语树是否保存的标志
extern float quanzhong[70];//第二步所输入的一级指标的权重
extern int quanzhongnum;//一共有多少一级指标权重
//*****************************以下变量继承自Step1dialog
extern  CString  zhibiaoitem[100][2];//第一步指标树的所有节点 [0]编号(用于分三级，并知道谁与谁是一级)  [1]内容
extern  int zhibiaoitemchilds[100];//第一步指标树的每个节点有多少子节点
extern int zhibiaoitempoint;///第一步指标树一共有多少节点（指标）
extern int  itemchildpoint;//
//______________________________________________________
CString openitem[200];//打开的txt文件的内容
int openpoint=0;//打开文件内容的总个数
int openitemnum[200];//每个对应的子项个数

CToolTipCtrl  m_ctrlTT;
Step1dialog step1dhk;int step1dhkcishu=0,step1dhkxianshi=0;
Step2dialog step2dhk;int step2dhkcishu=0,step2dhkxianshi=0;
Step3dialog step3dhk;int step3dhkcishu=0,step3dhkxianshi=0;
Step4dialog step4dhk;int step4dhkcishu=0,step4dhkxianshi=0;
 #define WM_SHOWTASK (WM_USER +1)
CString delbutton=0;
  NOTIFYICONDATA m_nid;
// Main 对话框
  CString  treeitem[100]={0},treeitem1[100]={0};//treeitem1用于存放第一步的评语树的所有节点内容
  int treepoint=0,treepoint1=0;//treepoint1用于记录第一步的评语树有多少节点
IMPLEMENT_DYNAMIC(Main, CDialogEx)

Main::Main(CWnd* pParent /*=NULL*/)
	: CDialogEx(Main::IDD, pParent)
{

}

Main::~Main()
{
}

void Main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_button);
	DDX_Control(pDX, IDOK, m_okbutton);
	DDX_Control(pDX, IDSmall, m_smallbutton);
	DDX_Control(pDX, IDC_BUTTON5, m_newbuttom);
	DDX_Control(pDX, IDC_BUTTON6, m_openbuttton);
	DDX_Control(pDX, IDC_BUTTON7, m_savebutton);
	DDX_Control(pDX, IDC_BUTTON8, m_delbutton);
	;
	DDX_Control(pDX, IDC_BUTTON9, m_excelbutton);
	DDX_Control(pDX, IDC_BUTTON14, m_jsbutton);
	DDX_Control(pDX, IDC_BUTTON24, m_addbtn);
	DDX_Control(pDX, IDC_BUTTON25, m_rnamebtn);
	DDX_Control(pDX, IDC_BUTTON26, m_sxbtn);
	DDX_Control(pDX, IDC_BUTTON2, m_setting);
	DDX_Control(pDX, IDC_BUTTON3, m_tools);
	//  DDX_Control(pDX, IDC_BUTTON4, m_help);
	DDX_Control(pDX, IDC_BUTTON4, m_help);
	DDX_Control(pDX, IDC_BUTTON10, m_av);
	DDX_Control(pDX, IDC_BUTTON11, m_ov);
	DDX_Control(pDX, IDC_BUTTON12, m_aj);
	DDX_Control(pDX, IDC_BUTTON13, m_oj);
	DDX_Control(pDX, IDC_BUTTON15, m_zhexian);
	DDX_Control(pDX, IDC_BUTTON16, m_zhuzt);
	DDX_Control(pDX, IDC_BUTTON17, m_bingzt);
}


BEGIN_MESSAGE_MAP(Main, CDialogEx)
	ON_BN_CLICKED(IDOK, &Main::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &Main::OnBnClickedButton1)
	ON_BN_SETFOCUS(IDC_BUTTON1, &Main::OnBnSetfocusButton1)
	ON_BN_SETFOCUS(IDOK, &Main::OnBnSetfocusOk)
	ON_BN_CLICKED(IDSmall, &Main::OnBnClickedSmall)
	ON_BN_SETFOCUS(IDSmall, &Main::OnBnSetfocusSmall)
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)//此处为添加部分
	 ON_MESSAGE(WM_SHOWTASK,OnShowTask)

     ON_WM_SIZE()//为了隐藏最小化到任务栏的图标而添加的消息响应函数，这个函数系统自带直接添加

//	ON_WM_QUERYDRAGICON()
ON_WM_NCHITTEST()

ON_BN_CLICKED(IDC_BUTTON10, &Main::OnBnClickedButton10)
ON_BN_CLICKED(IDC_BUTTON11, &Main::OnBnClickedButton11)
ON_BN_CLICKED(IDC_BUTTON12, &Main::OnBnClickedButton12)
ON_BN_CLICKED(IDC_BUTTON13, &Main::OnBnClickedButton13)
ON_BN_SETFOCUS(IDC_BUTTON14, &Main::OnBnSetfocusButton14)
ON_BN_CLICKED(IDC_BUTTON15, &Main::OnBnClickedButton15)
ON_BN_CLICKED(IDC_BUTTON16, &Main::OnBnClickedButton16)
ON_BN_CLICKED(IDC_BUTTON17, &Main::OnBnClickedButton17)
ON_BN_CLICKED(IDC_BUTTON18, &Main::OnBnClickedButton18)
ON_BN_CLICKED(IDC_BUTTON19, &Main::OnBnClickedButton19)
ON_BN_CLICKED(IDC_BUTTON20, &Main::OnBnClickedButton20)
ON_BN_CLICKED(IDC_BUTTON21, &Main::OnBnClickedButton21)
ON_BN_CLICKED(IDC_BUTTON22, &Main::OnBnClickedButton22)
ON_BN_CLICKED(IDC_BUTTON23, &Main::OnBnClickedButton23)
ON_BN_CLICKED(IDC_BUTTON5, &Main::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON8, &Main::OnBnClickedButton8)
ON_BN_CLICKED(IDC_BUTTON7, &Main::OnBnClickedButton7)
ON_BN_CLICKED(IDC_BUTTON6, &Main::OnBnClickedButton6)
ON_BN_SETFOCUS(IDC_BUTTON24, &Main::OnBnSetfocusButton24)
ON_BN_CLICKED(IDC_BUTTON24, &Main::OnBnClickedButton24)
ON_BN_CLICKED(IDC_BUTTON25, &Main::OnBnClickedButton25)
ON_BN_CLICKED(IDC_BUTTON26, &Main::OnBnClickedButton26)
ON_BN_CLICKED(IDC_BUTTON9, &Main::OnBnClickedButton9)
END_MESSAGE_MAP()


// Main 消息处理程序


void Main::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL Main::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HBITMAP hBitmapTITLE=NULL;
	CStatic *pStaticT = (CStatic *)GetDlgItem(IDC_STATIC_TITLE);
    hBitmapTITLE =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP82 ));
	pStaticT->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT->SetBitmap(hBitmapTITLE);
	HBITMAP hBitmapTITLE2=NULL;
	CStatic *pStaticT2 = (CStatic *)GetDlgItem(IDC_STATIC_FG1);
    hBitmapTITLE2 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP84 ));
	pStaticT2->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT2->SetBitmap(hBitmapTITLE2);
	CStatic *pStaticT3 = (CStatic *)GetDlgItem(IDC_STATIC_FG2);
	pStaticT3->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT3->SetBitmap(hBitmapTITLE2);
	CStatic *pStaticT4 = (CStatic *)GetDlgItem(IDC_STATIC_FG3);
	pStaticT4->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT4->SetBitmap(hBitmapTITLE2);
	CStatic *pStaticT5 = (CStatic *)GetDlgItem(IDC_STATIC_FG4);
	pStaticT5->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT5->SetBitmap(hBitmapTITLE2);
	 HBITMAP choose =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP102 ));
	CStatic *pStaticT6 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose);
	pStaticT6->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT6->SetBitmap(choose);
	 HBITMAP choose2 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP106 ));
	CStatic *pStaticT7 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose2);
	pStaticT7->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT7->SetBitmap(choose2);
	//---------------------------托盘显示---------------------------------//
     m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

     m_nid.hWnd = this->m_hWnd;

     m_nid.uID = IDR_MAINFRAME;

     m_nid.uFlags = NIF_ICON|NIF_MESSAGE |NIF_TIP;

     m_nid.uCallbackMessage = WM_SHOWTASK;

     m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));

	 // strcpy_s(m_nid.szTip,strlen("对话框")+1,"对话框");

     Shell_NotifyIcon(NIM_ADD,&m_nid); // 在托盘区添加图标

	 m_button.LoadBitmaps(IDB_BITMAP17,IDB_BITMAP21); 
	 m_setting.LoadBitmaps(IDB_BITMAP18,IDB_BITMAP99); 
	 m_tools.LoadBitmaps(IDB_BITMAP19,IDB_BITMAP100); 
	 m_help.LoadBitmaps(IDB_BITMAP20,IDB_BITMAP101); 
	 m_okbutton.LoadBitmaps(IDB_BITMAP22,IDB_BITMAP23);
	 m_smallbutton.LoadBitmaps(IDB_BITMAP24,IDB_BITMAP25);
	 m_newbuttom.LoadBitmaps(IDB_BITMAP26,IDB_BITMAP27);
	 m_openbuttton.LoadBitmaps(IDB_BITMAP28,IDB_BITMAP29);
	 m_savebutton.LoadBitmaps(IDB_BITMAP30,IDB_BITMAP31);
	 m_delbutton.LoadBitmaps(IDB_BITMAP32,IDB_BITMAP33);
	 m_excelbutton.LoadBitmaps(IDB_BITMAP43,IDB_BITMAP44);
	 m_jsbutton.LoadBitmaps(IDB_BITMAP45,IDB_BITMAP46);
	 m_addbtn.LoadBitmaps(IDB_BITMAP68,IDB_BITMAP69);
	 m_rnamebtn.LoadBitmaps(IDB_BITMAP73,IDB_BITMAP74);
	 m_sxbtn.LoadBitmaps(IDB_BITMAP78,IDB_BITMAP79);
	 m_av.LoadBitmaps(IDB_BITMAP34,IDB_BITMAP36);//选中
	 m_ov.LoadBitmaps(IDB_BITMAP37,IDB_BITMAP38);
	 m_aj.LoadBitmaps(IDB_BITMAP39,IDB_BITMAP40);
	 m_oj.LoadBitmaps(IDB_BITMAP41,IDB_BITMAP42);
	 m_zhexian.LoadBitmaps(IDB_BITMAP47,IDB_BITMAP48);
	m_zhuzt.LoadBitmaps(IDB_BITMAP49,IDB_BITMAP50);
	m_bingzt.LoadBitmaps(IDB_BITMAP51,IDB_BITMAP52);
	 HBITMAP   hBitmap;  
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP17));   
	 ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap); 
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP18));   
	 ((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap); 
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP19));   
	 ((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap); 
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP20));   
	 ((CButton *)GetDlgItem(IDC_BUTTON4))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP26));   
	 ((CButton *)GetDlgItem(IDC_BUTTON5))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP28));   
	 ((CButton *)GetDlgItem(IDC_BUTTON6))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP30));   
	 ((CButton *)GetDlgItem(IDC_BUTTON7))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP32));   
	 ((CButton *)GetDlgItem(IDC_BUTTON8))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP43));   
	 ((CButton *)GetDlgItem(IDC_BUTTON9))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP34));  //36为选中 34
	 ((CButton *)GetDlgItem(IDC_BUTTON10))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP38));  //38为选中 37
	 ((CButton *)GetDlgItem(IDC_BUTTON11))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP39));  //40为选中 39
	 ((CButton *)GetDlgItem(IDC_BUTTON12))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP41));  //41为选中 42
	 ((CButton *)GetDlgItem(IDC_BUTTON13))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP45));  
	 ((CButton *)GetDlgItem(IDC_BUTTON14))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP47));  //48为选中 47
	 ((CButton *)GetDlgItem(IDC_BUTTON15))->SetBitmap(hBitmap);
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP49));  //50为选中 49
	 ((CButton *)GetDlgItem(IDC_BUTTON16))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP52));  //52为选中 51
	 ((CButton *)GetDlgItem(IDC_BUTTON17))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP53)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP22));   
	 ((CButton *)GetDlgItem(IDOK))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP24));   
	 ((CButton *)GetDlgItem(IDSmall))->SetBitmap(hBitmap); 
	 	//***********************************按钮提示
   EnableToolTips(TRUE);//enable use it
   m_ctrlTT.Create(this);
   m_ctrlTT.Activate(TRUE);
   m_ctrlTT.SetTipTextColor(RGB(0,0,0));//font color
 
   //IDC_TEST为你想添加提示的控件IDC，"hello为想添加的提示语句"
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON5),(_bstr_t)"新建");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON6),(_bstr_t)"打开项目");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON7),(_bstr_t)"保存工程");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON24),(_bstr_t)"添加节点");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON25),(_bstr_t)"重命名节点");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON8),(_bstr_t)"删除节点");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON26),(_bstr_t)"刷新");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON9),(_bstr_t)"导出Excel");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON14),(_bstr_t)"计算模型");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON10),(_bstr_t)"主因素突出型M(∧∨)");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON11),(_bstr_t)"主因素突出型M(·∨)");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON12),(_bstr_t)"加权平均型M(∧ +)");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON13),(_bstr_t)"加权平均型M(· +)");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON15),(_bstr_t)"折线图");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON16),(_bstr_t)"柱状图");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON17),(_bstr_t)"饼状图");

		 //******************LINE
	
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_ROLL);
    hBitmap =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP77 ));
	pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStatic->SetBitmap(hBitmap);
	return TRUE;  // return TRUE unless you set the focus to a control

}

LRESULT Main::OnShowTask(WPARAM wParam, LPARAM lParam)

{
     if(wParam != IDR_MAINFRAME) return 1;
     switch(lParam)
     {    
     case WM_LBUTTONDBLCLK:                            // 双击左键的处理
         this->ShowWindow(SW_SHOWNORMAL);         // 显示主窗口  
         break;
     }
     return 0;
}


void Main::OnPaint()
{
	CPaintDC dc(this);

CDC memdc;
memdc.CreateCompatibleDC(&dc);//创建兼容DC

CBitmap bkg;
bkg.LoadBitmap(IDB_BITMAP16);//载入位图

BITMAP bkginfo;
bkg.GetBitmap(&bkginfo);//获取位图信息

memdc.SelectObject(&bkg);

RECT rect;
GetWindowRect(&rect);//获取对话框信息

dc.StretchBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&memdc,0,0,bkginfo.bmWidth,bkginfo.bmHeight,SRCCOPY);
}


BOOL Main::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	   // 填充工具栏的背景色  
   
	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH Main::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
       
		   if (pWnd->GetDlgCtrlID() == IDC_STATIC)
        {
             pDC->SetTextColor(RGB(0,0,0)); //设置字体颜色
             pDC->SetBkMode(TRANSPARENT);
             return CreateSolidBrush(RGB(255,255,255));
}
		
	return hbr;
}


void Main::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Main::OnBnSetfocusButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Main::OnBnSetfocusOk()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Main::OnBnClickedSmall()//最小化
{
	// TODO: 在此添加控件通知处理程序代码
	
	ShowWindow(SW_HIDE);

}


void Main::OnBnSetfocusSmall()
{
	// TODO: 在此添加控件通知处理程序代码
}




BOOL Main::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	Shell_NotifyIcon(NIM_DELETE, &m_nid);             
	CDialog::OnOK();
	return CDialogEx::DestroyWindow();
}


LRESULT Main::OnNcHitTest(CPoint point)//对话框可移动
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 CRect rc;
     GetClientRect(&rc);
     ClientToScreen(&rc);
     return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
	
}

void Main::OnBnClickedButton10()//选择算法M(∧,∨)
{
	// TODO: 在此添加控件通知处理程序代码
    HBITMAP choose =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP102 ));
	CStatic *pStaticT6 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose);
	pStaticT6->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT6->SetBitmap(choose);
	av=1,ov=0,aj=0,oj=0;

}


void Main::OnBnClickedButton11()//选择算法M(.,∨)
{
	// TODO: 在此添加控件通知处理程序代码
	 HBITMAP choose =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP103 ));
	CStatic *pStaticT6 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose);
	pStaticT6->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT6->SetBitmap(choose);
	 av=0,ov=1,aj=0,oj=0;
}


void Main::OnBnClickedButton12()//选择算法M(∧,+)
{
	// TODO: 在此添加控件通知处理程序代码
	  HBITMAP choose =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP104 ));
	CStatic *pStaticT6 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose);
	pStaticT6->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT6->SetBitmap(choose);
	av=0,ov=0,aj=1,oj=0;
}


void Main::OnBnClickedButton13()//选择算法M(.,+)
{
	// TODO: 在此添加控件通知处理程序代码
	 HBITMAP choose =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP105 ));
	CStatic *pStaticT6 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose);
	pStaticT6->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT6->SetBitmap(choose);
	av=0,ov=0,aj=0,oj=1;
	
	
}
void Main::OnBnSetfocusButton14()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Main::OnBnClickedButton15()//选择结果显示-折线图
{
	// TODO: 在此添加控件通知处理程序代码
	HBITMAP choose2 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP106 ));
	CStatic *pStaticT7 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose2);
	pStaticT7->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT7->SetBitmap(choose2);
}


void Main::OnBnClickedButton16()//选择结果显示-柱状图
{
	// TODO: 在此添加控件通知处理程序代码
	 HBITMAP choose2 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP107 ));
	CStatic *pStaticT7 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose2);
	pStaticT7->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT7->SetBitmap(choose2);
}


void Main::OnBnClickedButton17()//选择结果显示-饼状图
{
	// TODO: 在此添加控件通知处理程序代码
	 HBITMAP choose2 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP108 ));
	CStatic *pStaticT7 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose2);
	pStaticT7->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT7->SetBitmap(choose2);
}


void Main::OnBnClickedButton18()//第一步
{
	// TODO: 在此添加控件通知处理程序代码
	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP53)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_STATIC_ROLL)->ShowWindow(SW_SHOW);//可见
	   CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)//未初始化
	   {
	  step1dhk.Create(IDD_Step1_DIALOG, this);  
	   step1dhk.MoveWindow(rect);
	   //****************如果其他子对话框显示让其隐藏
	       if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		     if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
			  if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
	   //****************
       step1dhk.ShowWindow( SW_SHOW ); step1dhkcishu=1;step1dhkxianshi=1;
	   }
	     if(step1dhkcishu==1)//已经初始化
	   {
	   step1dhk.GetDlgItem(IDD_Step1_DIALOG);  
	   step1dhk.MoveWindow(rect);
	   //*******8
	     if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		   if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
		    if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
		 //********
       step1dhk.ShowWindow( SW_SHOW ); step1dhkxianshi=1;
	   }
}


void Main::OnBnClickedButton19()//第二步
{
	// TODO: 在此添加控件通知处理程序代码
	
	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP59)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP54));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//可见
	   
	   if(step1dhkcishu==0)
	   {
		    MessageBox((_bstr_t)"请先执行第一步建立模型",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	   }
	   if(treesave==0)
	   {
		   MessageBox((_bstr_t)"请先保存第一步建立的模型",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	   }
	    CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step2dhkcishu==0)
	   {
	  step2dhk.Create(IDD_Step2_DIALOG, this);  
	   step2dhk.MoveWindow(rect);
	   //****************
	       if(step1dhkxianshi==1)
		   {
			   step1dhk.ShowWindow( SW_HIDE ); 
			   step1dhkxianshi=0;
	       }
		      if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
			   if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
	   //****************
       step2dhk.ShowWindow( SW_SHOW ); step2dhkcishu=1;step2dhkxianshi=1;
	   }
	     if(step2dhkcishu==1)
	   {
	   step2dhk.GetDlgItem(IDD_Step2_DIALOG);  
	   step2dhk.MoveWindow(rect);
	   //*******8
	     if(step1dhkxianshi==1)
		   {
			   step1dhk.ShowWindow( SW_HIDE ); 
			   step1dhkxianshi=0;
	       }
		   if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
		    if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
		 //********
       step2dhk.ShowWindow( SW_SHOW ); step2dhkxianshi=1;
	   }
}


void Main::OnBnClickedButton20()//第三步
{
	// TODO: 在此添加控件通知处理程序代码
	if(step1dhkcishu==0||step2dhkcishu==0)
	{
		  MessageBox((_bstr_t)"请先完成前两步",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}
	
	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP59)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP55)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//可见
	   CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step3dhkcishu==0)
	   {
	  step3dhk.Create(IDD_Step3_DIALOG, this);  
	   step3dhk.MoveWindow(rect);
	   //****************
	      if(step1dhkxianshi==1)
		   {
			   step1dhk.ShowWindow( SW_HIDE ); 
			   step1dhkxianshi=0;
	       }
	       if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		    if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
	   //****************
       step3dhk.ShowWindow( SW_SHOW ); step3dhkcishu=1;step3dhkxianshi=1;
	   }
	     if(step3dhkcishu==1)
	   {
	   step3dhk.GetDlgItem(IDD_Step1_DIALOG);  
	   step3dhk.MoveWindow(rect);
	   //*******8
	      if(step1dhkxianshi==1)
		   {
			   step1dhk.ShowWindow( SW_HIDE ); 
			   step1dhkxianshi=0;
	       }
	     if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		  if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
		 //********
       step3dhk.ShowWindow( SW_SHOW ); step3dhkxianshi=1;
	   }
}


void Main::OnBnClickedButton21()//第四步
{
	// TODO: 在此添加控件通知处理程序代码
	if(step1dhkcishu==0||step2dhkcishu==0||step3dhkcishu==0)
	{
		  MessageBox((_bstr_t)"请先完成前三步",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}
	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP59)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP56)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//可见
	     CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step4dhkcishu==0)
	   {
	  step4dhk.Create(IDD_Step4_DIALOG, this);  
	   step4dhk.MoveWindow(rect);
	   //****************
	    if(step1dhkxianshi==1)
		   {
			   step1dhk.ShowWindow( SW_HIDE ); 
			   step1dhkxianshi=0;
	       }
	       if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		     if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
	   //****************
       step4dhk.ShowWindow( SW_SHOW );
	   step4dhk.OnBnClickedButton1();step4dhkcishu=1;step4dhkxianshi=1;
	   }
	     if(step4dhkcishu==1)
	   {
	   step4dhk.GetDlgItem(IDD_Step4_DIALOG);  
	   step4dhk.MoveWindow(rect);
	   //*******8
	    if(step1dhkxianshi==1)
		   {
			   step1dhk.ShowWindow( SW_HIDE ); 
			   step1dhkxianshi=0;
	       }
	     if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		   if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
		 //********
       step4dhk.ShowWindow( SW_SHOW );  step4dhk.OnBnClickedButton1();step4dhkxianshi=1;
	   }
}


void Main::OnBnClickedButton22()//第五步
{
	// TODO: 在此添加控件通知处理程序代码
	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP59)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP57)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//可见
}


void Main::OnBnClickedButton23()//第六步
{
	// TODO: 在此添加控件通知处理程序代码
   HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP59)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP58)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//可见
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//可见
}


void Main::OnBnClickedButton5()//新建
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW); 
	 if(step1dhkcishu==0)
	   {	        
		 OnBnClickedButton18();//未创建过工程（未执行过第一步）直接调用第一步创建
	   }
	 else if(MessageBox((_bstr_t)"已经创建工程,未保存的工程将被删除,是否继续新建",(_bstr_t)"警告",MB_YESNO)==IDYES)
	 {
		  CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
		  step1dhk.GetDlgItem(IDD_Step1_DIALOG);  
	   step1dhk.MoveWindow(rect);
	   //*******8
	     if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		   if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
		    if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
		 //********
		 	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP53)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
		 //**********8
       step1dhk.ShowWindow( SW_SHOW ); 
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhk.OnBnClickedButton1();//调用对话框step1dialog的函数,进行新建
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhkxianshi=1;
	 }
	
}


void Main::OnBnClickedButton8()//删除（树的节点）
{
	// TODO: 在此添加控件通知处理程序代码
		
	 CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)//第一步未建立无法删除树节点
	   {
	        
		  MessageBox((_bstr_t)"没有建模不能删除",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	  
	   }
	   if(step1dhkxianshi==0)//第一步未显示在界面中，无法删除树节点
	   {
		     MessageBox((_bstr_t)"无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	   }
	     if(step1dhkcishu==1)
	   {
	   step1dhk.GetDlgItem(IDD_Step1_DIALOG);  
	   step1dhk.MoveWindow(rect);
	   //*******8
	     if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		   if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
		    if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
		 //********

		 	HBITMAP   hBitmap;  
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP53)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
		 //**********
       step1dhk.ShowWindow( SW_SHOW ); 
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhk.deltreeitem();//调用step1dialog的删除树节点的函数
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhkxianshi=1;
	   }
	
}


void Main::OnBnClickedButton7()//保存
{
	// TODO: 在此添加控件通知处理程序代码
	
	 CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)
	   {
	        
		  MessageBox((_bstr_t)"没有建模不能保存工程",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	  
	   }
	     if(step1dhkcishu==1)
	   {
	   step1dhk.GetDlgItem(IDD_Step1_DIALOG);  
	   step1dhk.MoveWindow(rect);
	   //*******8
	     if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		   if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
		    if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
		 //********
		 	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP53)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
		 //**********8
       step1dhk.ShowWindow( SW_SHOW ); 
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhk.OnBnClickedButton2();//调用step1dialog的保存函数
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhkxianshi=1;
	   }
	
}


void Main::OnBnClickedButton6()//打开文件
{
	// TODO: 在此添加控件通知处理程序代码
	int i,j,k,m;
	int len,len1,len2,len3,len4;
	int point;
	int line,line1,line2,line3,line4;
	openpoint=0;
		if(zhibiaoitempoint==0)
	{
		 OnBnClickedButton18();//先初始化界面
		 //首先擦除初始化已经写好的树节点的数据			
		 for(i=0;i<zhibiaoitempoint;i++)
			{
				zhibiaoitem[i][0]="0";
				zhibiaoitem[i][1]="0";
				
			}
			zhibiaoitempoint=0;
			for(i=0;i<itemchildpoint;i++)
			{
				zhibiaoitemchilds[i]=0;
				
			}
			itemchildpoint=0;

		  CString szFileFilter=(_bstr_t)"文本(*.txt)|*.txt|";
	          CString szFileExt=(_bstr_t)"txt";//扩展名为txt
	          CFileDialog dlg(true,szFileExt,NULL,OFN_HIDEREADONLY,szFileFilter);
	          if(dlg.DoModal()==IDOK)
	          {
	            	CStdioFile File;
		            CString strLine,strText;//一个存储文本一行内容一个存储所有的
		            File.Open(dlg.GetPathName(),CFile::modeRead);
		            char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		            setlocale( LC_CTYPE, "chs" );//设定
					File.ReadString(strLine);//读取开头第一行
					int len=strLine.GetLength();
					int line= strLine.Find((_bstr_t)"/");
					openitem[0]= strLine.Mid(0,len-(len-line));		
					int Vpoint=_ttoi(strLine.Mid(line+1,len));//总的有几个	
					openitemnum[0]=Vpoint;openpoint++;
					for(i=0;i<Vpoint;i++)
		            {
					    File.ReadString(strLine);//读取一级节点	一级节点形式：完成任务能力/3
						int len1=strLine.GetLength();//读取其长度
					    int line1= strLine.Find((_bstr_t)"/");//找到/的位置
					    openitem[openpoint]= strLine.Mid(0,len1-(len1-line1));//记录节点内容 如：完成任务能力	
					    int Vpoint1=_ttoi(strLine.Mid(line1+1,len1));//读取/后面数字 得知该节点有几个子节点	
					    openitemnum[openpoint]=Vpoint1;openpoint++;	//记录其子节点个数
						for(j=0;j<Vpoint1;j++)
		                {						
							File.ReadString(strLine);//读取二级节点		
						    int len2=strLine.GetLength();
					        int line2= strLine.Find((_bstr_t)"/");
					        openitem[openpoint]= strLine.Mid(0,len2-(len2-line2));
					        int Vpoint2=_ttoi(strLine.Mid(line2+1,len2));//总的有几个	
					        openitemnum[openpoint]=Vpoint2;openpoint++;		
							for(k=0;k<Vpoint2;k++)
		                    {
								File.ReadString(strLine);//读取三级节点								        
					           int len3=strLine.GetLength();
					           int line3= strLine.Find((_bstr_t)"/");
					           openitem[openpoint]= strLine.Mid(0,len3-(len3-line3));
					            openitemnum[openpoint]=0;openpoint++;	
							}
						}
		            }
					//读取评语
					for(i=0;i<treepoint1;i++)
			        {
				       treeitem1[i]="0";
				
					}treepoint1=0;
				    File.ReadString(strLine);//读取开头第一行
					 len=strLine.GetLength();
					 line= strLine.Find((_bstr_t)"/");
					treeitem1[0]= strLine.Mid(0,len-(len-line));treepoint1++;
					 while(File.ReadString(strLine))
		            {
					if(strLine=="Finish")
							break;						
					treeitem1[treepoint1]= strLine;
						treepoint1++;
		            }
		            setlocale( LC_CTYPE, old_locale );
                    free( old_locale );     
		            File.Close();
	          }
            //测试输出
			/*  for(i=0;i<openpoint;i++)
		      {
				  MessageBox((_bstr_t)openitem[i]+(_bstr_t)openitemnum[i]);
			  }*/
			  //*********按钮回显
			  	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP53)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
			  //*******************************************调用函数重建树
			
			  step1dhk.updatatree();
			
	}
	else
	{
		if(MessageBox((_bstr_t)"已经创建评价指标是否删除继续打开新文件",(_bstr_t)"警告",MB_YESNO)==IDYES)
		{
			 //首先擦除初始化已经写好的数据
			
		 for(i=0;i<zhibiaoitempoint;i++)
			{
				zhibiaoitem[i][0]="0";
				zhibiaoitem[i][1]="0";
				
			}
			zhibiaoitempoint=0;
			for(i=0;i<itemchildpoint;i++)
			{
				zhibiaoitemchilds[i]=0;
				
			}
			itemchildpoint=0;

		  CString szFileFilter=(_bstr_t)"文本(*.txt)|*.txt|";
	          CString szFileExt=(_bstr_t)"txt";//扩展名为txt
	          CFileDialog dlg(true,szFileExt,NULL,OFN_HIDEREADONLY,szFileFilter);
	          if(dlg.DoModal()==IDOK)
	          {
	            	CStdioFile File;
		            CString strLine,strText;//一个存储文本一行内容一个存储所有的
		            File.Open(dlg.GetPathName(),CFile::modeRead);
		            char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		            setlocale( LC_CTYPE, "chs" );//设定
					File.ReadString(strLine);//读取开头第一行
					int len=strLine.GetLength();
					int line= strLine.Find((_bstr_t)"/");
					openitem[0]= strLine.Mid(0,len-(len-line));		
					int Vpoint=_ttoi(strLine.Mid(line+1,len));//总的有几个	
					openitemnum[0]=Vpoint;openpoint++;
					for(i=0;i<Vpoint;i++)
		            {
					    File.ReadString(strLine);//读取一级节点	
						int len1=strLine.GetLength();
					    int line1= strLine.Find((_bstr_t)"/");
					    openitem[openpoint]= strLine.Mid(0,len1-(len1-line1));	
					    int Vpoint1=_ttoi(strLine.Mid(line1+1,len1));//总的有几个	
					    openitemnum[openpoint]=Vpoint1;openpoint++;	
						for(j=0;j<Vpoint1;j++)
		                {						
							File.ReadString(strLine);//读取二级节点		
						    int len2=strLine.GetLength();
					        int line2= strLine.Find((_bstr_t)"/");
					        openitem[openpoint]= strLine.Mid(0,len2-(len2-line2));
					        int Vpoint2=_ttoi(strLine.Mid(line2+1,len2));//总的有几个	
					        openitemnum[openpoint]=Vpoint2;openpoint++;		
							for(k=0;k<Vpoint2;k++)
		                    {
						       File.ReadString(strLine);//读取三级节点								        
					            int len3=strLine.GetLength();
					           int line3= strLine.Find((_bstr_t)"/");
					           openitem[openpoint]= strLine.Mid(0,len3-(len3-line3));
					            openitemnum[openpoint]=0;openpoint++;	
							}
						}
		            } 
			/*		for(i=0;i<openpoint;i++)
		      {
				  MessageBox((_bstr_t)openitem[i]+(_bstr_t)openitemnum[i]);
			  }*/
					//读取评语
					for(i=0;i<treepoint1;i++)
			        {
				       treeitem1[i]="0";
				
					}treepoint1=0;
				    File.ReadString(strLine);//读取开头第一行
					 len=strLine.GetLength();
					 line= strLine.Find((_bstr_t)"/");
					treeitem1[0]= strLine.Mid(0,len-(len-line));treepoint1++;
					 while(File.ReadString(strLine))
		            {
					if(strLine=="Finish")
							break;						
					treeitem1[treepoint1]= strLine;
						treepoint1++;
		            }
		            setlocale( LC_CTYPE, old_locale );
                    free( old_locale );     
		            File.Close();
	          }
			 //***********按钮回显
			  	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP53)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
			 //*******************************************调用函数重建树
			  OnBnClickedButton18();
			  step1dhk.updatatree();
		}
		else
		{
			return;
		}
	}

}


void Main::OnBnSetfocusButton24()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Main::OnBnClickedButton24()//添加树节点
{
	// TODO: 在此添加控件通知处理程序代码
	 CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)
	   {
	        
		  MessageBox((_bstr_t)"没有建模不能添加节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	  
	   }
	      if(step1dhkxianshi==0)//后边改成excel
	   {
		     MessageBox((_bstr_t)"无法添加节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	   }
	     if(step1dhkcishu==1)
	   {
	   step1dhk.GetDlgItem(IDD_Step1_DIALOG);  
	   step1dhk.MoveWindow(rect);
	   //*******8
	     if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		   if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
		    if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
		 //********
		 	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP53)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
		 //********
       step1dhk.ShowWindow( SW_SHOW ); 
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  
	   step1dhk.additem();
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhkxianshi=1;
	   }
}


void Main::OnBnClickedButton25()//重命名节点
{
	// TODO: 在此添加控件通知处理程序代码
	 CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)
	   {
	        
		  MessageBox((_bstr_t)"没有建模不能重命名",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	  
	   }
	      if(step1dhkxianshi==0)//后边改成excel
	   {
		     MessageBox((_bstr_t)"无法重命名",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	   }
	     if(step1dhkcishu==1)
	   {
	   step1dhk.GetDlgItem(IDD_Step1_DIALOG);  
	   step1dhk.MoveWindow(rect);
	   //*******8
	     if(step2dhkxianshi==1)
		   {
			   step2dhk.ShowWindow( SW_HIDE ); 
			   step2dhkxianshi=0;
	       }
		   if(step3dhkxianshi==1)
		   {
			   step3dhk.ShowWindow( SW_HIDE ); 
			   step3dhkxianshi=0;
	       }
		    if(step4dhkxianshi==1)
		   {
			   step4dhk.ShowWindow( SW_HIDE ); 
			   step4dhkxianshi=0;
	       }
		 //********
		 	HBITMAP   hBitmap;  
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP53)); //11
	  ((CButton *)GetDlgItem(IDC_BUTTON18))->SetBitmap(hBitmap);
	    hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP60));//2 
	  ((CButton *)GetDlgItem(IDC_BUTTON19))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP61)); //3
	  ((CButton *)GetDlgItem(IDC_BUTTON20))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP62)); ///4
	  ((CButton *)GetDlgItem(IDC_BUTTON21))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP63)); //5
	  ((CButton *)GetDlgItem(IDC_BUTTON22))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP64)); //6
	  ((CButton *)GetDlgItem(IDC_BUTTON23))->SetBitmap(hBitmap);
       step1dhk.ShowWindow( SW_SHOW ); 
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhk.renameitem();
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhkxianshi=1;
	   }
}


BOOL Main::PreTranslateMessage(MSG* pMsg)
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
	 m_ctrlTT.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}


void Main::OnBnClickedButton26()//刷新
{
	// TODO: 在此添加控件通知处理程序代码
	
	   if(step2dhkcishu!=0&&step2dhkxianshi==1)
	   {
	        
	    step2dhk.shuaxinlist();
	  
	   }
	    if(step3dhkcishu!=0&&step3dhkxianshi==1)
	   {
	        
	    step3dhk.shuaxinlist();
	  
	   }
		    if(step4dhkcishu!=0&&step4dhkxianshi==1)
	   {
	        
	    step4dhk.shuaxin();
	  
	   }
	 

}


void Main::OnBnClickedButton9()//导出excel
{
	// TODO: 在此添加控件通知处理程序代码
	 if(step2dhkcishu==0&&step3dhkcishu==0&&step2dhkxianshi==0&&step3dhkxianshi==0)
	   {
	        
		  MessageBox((_bstr_t)"没有列表不能导出Excel",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	  
	   }
	    if(step2dhkcishu!=0&&step2dhkxianshi==1)
	   {
	        
	    step2dhk.excel();
	  
	   }
	    if(step3dhkcishu!=0&&step3dhkxianshi==1)
	   {
	        
	    step3dhk.excel();
	  
	   }
		    if(step4dhkcishu!=0&&step4dhkxianshi==1)
	   {
	        
	    step4dhk.excel();
	  
	   }
}
