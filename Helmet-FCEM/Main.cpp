// Main.cpp : ʵ���ļ�
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

int av=1,ov=0,aj=0,oj=0;//ȫ�ֱ��� ѡ���㷨�ֱ���M(��,��)M(.,��)M(��,+)M(.,+)
extern int treesave;  //��һ��������ָ�������������Ƿ񱣴�ı�־
extern float quanzhong[70];//�ڶ����������һ��ָ���Ȩ��
extern int quanzhongnum;//һ���ж���һ��ָ��Ȩ��
//*****************************���±����̳���Step1dialog
extern  CString  zhibiaoitem[100][2];//��һ��ָ���������нڵ� [0]���(���ڷ���������֪��˭��˭��һ��)  [1]����
extern  int zhibiaoitemchilds[100];//��һ��ָ������ÿ���ڵ��ж����ӽڵ�
extern int zhibiaoitempoint;///��һ��ָ����һ���ж��ٽڵ㣨ָ�꣩
extern int  itemchildpoint;//
//______________________________________________________
CString openitem[200];//�򿪵�txt�ļ�������
int openpoint=0;//���ļ����ݵ��ܸ���
int openitemnum[200];//ÿ����Ӧ���������

CToolTipCtrl  m_ctrlTT;
Step1dialog step1dhk;int step1dhkcishu=0,step1dhkxianshi=0;
Step2dialog step2dhk;int step2dhkcishu=0,step2dhkxianshi=0;
Step3dialog step3dhk;int step3dhkcishu=0,step3dhkxianshi=0;
Step4dialog step4dhk;int step4dhkcishu=0,step4dhkxianshi=0;
 #define WM_SHOWTASK (WM_USER +1)
CString delbutton=0;
  NOTIFYICONDATA m_nid;
// Main �Ի���
  CString  treeitem[100]={0},treeitem1[100]={0};//treeitem1���ڴ�ŵ�һ���������������нڵ�����
  int treepoint=0,treepoint1=0;//treepoint1���ڼ�¼��һ�����������ж��ٽڵ�
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
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)//�˴�Ϊ��Ӳ���
	 ON_MESSAGE(WM_SHOWTASK,OnShowTask)

     ON_WM_SIZE()//Ϊ��������С������������ͼ�����ӵ���Ϣ��Ӧ�������������ϵͳ�Դ�ֱ�����

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


// Main ��Ϣ�������


void Main::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//---------------------------������ʾ---------------------------------//
     m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

     m_nid.hWnd = this->m_hWnd;

     m_nid.uID = IDR_MAINFRAME;

     m_nid.uFlags = NIF_ICON|NIF_MESSAGE |NIF_TIP;

     m_nid.uCallbackMessage = WM_SHOWTASK;

     m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));

	 // strcpy_s(m_nid.szTip,strlen("�Ի���")+1,"�Ի���");

     Shell_NotifyIcon(NIM_ADD,&m_nid); // �����������ͼ��

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
	 m_av.LoadBitmaps(IDB_BITMAP34,IDB_BITMAP36);//ѡ��
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
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP34));  //36Ϊѡ�� 34
	 ((CButton *)GetDlgItem(IDC_BUTTON10))->SetBitmap(hBitmap);
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP38));  //38Ϊѡ�� 37
	 ((CButton *)GetDlgItem(IDC_BUTTON11))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP39));  //40Ϊѡ�� 39
	 ((CButton *)GetDlgItem(IDC_BUTTON12))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP41));  //41Ϊѡ�� 42
	 ((CButton *)GetDlgItem(IDC_BUTTON13))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP45));  
	 ((CButton *)GetDlgItem(IDC_BUTTON14))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP47));  //48Ϊѡ�� 47
	 ((CButton *)GetDlgItem(IDC_BUTTON15))->SetBitmap(hBitmap);
	 hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP49));  //50Ϊѡ�� 49
	 ((CButton *)GetDlgItem(IDC_BUTTON16))->SetBitmap(hBitmap);
	  hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP52));  //52Ϊѡ�� 51
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
	 	//***********************************��ť��ʾ
   EnableToolTips(TRUE);//enable use it
   m_ctrlTT.Create(this);
   m_ctrlTT.Activate(TRUE);
   m_ctrlTT.SetTipTextColor(RGB(0,0,0));//font color
 
   //IDC_TESTΪ���������ʾ�Ŀؼ�IDC��"helloΪ����ӵ���ʾ���"
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON5),(_bstr_t)"�½�");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON6),(_bstr_t)"����Ŀ");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON7),(_bstr_t)"���湤��");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON24),(_bstr_t)"��ӽڵ�");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON25),(_bstr_t)"�������ڵ�");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON8),(_bstr_t)"ɾ���ڵ�");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON26),(_bstr_t)"ˢ��");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON9),(_bstr_t)"����Excel");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON14),(_bstr_t)"����ģ��");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON10),(_bstr_t)"������ͻ����M(�ġ�)");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON11),(_bstr_t)"������ͻ����M(����)");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON12),(_bstr_t)"��Ȩƽ����M(�� +)");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON13),(_bstr_t)"��Ȩƽ����M(�� +)");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON15),(_bstr_t)"����ͼ");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON16),(_bstr_t)"��״ͼ");
   m_ctrlTT.AddTool(GetDlgItem(IDC_BUTTON17),(_bstr_t)"��״ͼ");

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
     case WM_LBUTTONDBLCLK:                            // ˫������Ĵ���
         this->ShowWindow(SW_SHOWNORMAL);         // ��ʾ������  
         break;
     }
     return 0;
}


void Main::OnPaint()
{
	CPaintDC dc(this);

CDC memdc;
memdc.CreateCompatibleDC(&dc);//��������DC

CBitmap bkg;
bkg.LoadBitmap(IDB_BITMAP16);//����λͼ

BITMAP bkginfo;
bkg.GetBitmap(&bkginfo);//��ȡλͼ��Ϣ

memdc.SelectObject(&bkg);

RECT rect;
GetWindowRect(&rect);//��ȡ�Ի�����Ϣ

dc.StretchBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&memdc,0,0,bkginfo.bmWidth,bkginfo.bmHeight,SRCCOPY);
}


BOOL Main::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	   // ��乤�����ı���ɫ  
   
	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH Main::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
       
		   if (pWnd->GetDlgCtrlID() == IDC_STATIC)
        {
             pDC->SetTextColor(RGB(0,0,0)); //����������ɫ
             pDC->SetBkMode(TRANSPARENT);
             return CreateSolidBrush(RGB(255,255,255));
}
		
	return hbr;
}


void Main::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Main::OnBnSetfocusButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Main::OnBnSetfocusOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void Main::OnBnClickedSmall()//��С��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	ShowWindow(SW_HIDE);

}


void Main::OnBnSetfocusSmall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}




BOOL Main::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	Shell_NotifyIcon(NIM_DELETE, &m_nid);             
	CDialog::OnOK();
	return CDialogEx::DestroyWindow();
}


LRESULT Main::OnNcHitTest(CPoint point)//�Ի�����ƶ�
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	 CRect rc;
     GetClientRect(&rc);
     ClientToScreen(&rc);
     return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
	
}

void Main::OnBnClickedButton10()//ѡ���㷨M(��,��)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    HBITMAP choose =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP102 ));
	CStatic *pStaticT6 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose);
	pStaticT6->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT6->SetBitmap(choose);
	av=1,ov=0,aj=0,oj=0;

}


void Main::OnBnClickedButton11()//ѡ���㷨M(.,��)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 HBITMAP choose =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP103 ));
	CStatic *pStaticT6 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose);
	pStaticT6->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT6->SetBitmap(choose);
	 av=0,ov=1,aj=0,oj=0;
}


void Main::OnBnClickedButton12()//ѡ���㷨M(��,+)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	  HBITMAP choose =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP104 ));
	CStatic *pStaticT6 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose);
	pStaticT6->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT6->SetBitmap(choose);
	av=0,ov=0,aj=1,oj=0;
}


void Main::OnBnClickedButton13()//ѡ���㷨M(.,+)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 HBITMAP choose =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP105 ));
	CStatic *pStaticT6 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose);
	pStaticT6->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT6->SetBitmap(choose);
	av=0,ov=0,aj=0,oj=1;
	
	
}
void Main::OnBnSetfocusButton14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Main::OnBnClickedButton15()//ѡ������ʾ-����ͼ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HBITMAP choose2 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP106 ));
	CStatic *pStaticT7 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose2);
	pStaticT7->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT7->SetBitmap(choose2);
}


void Main::OnBnClickedButton16()//ѡ������ʾ-��״ͼ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 HBITMAP choose2 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP107 ));
	CStatic *pStaticT7 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose2);
	pStaticT7->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT7->SetBitmap(choose2);
}


void Main::OnBnClickedButton17()//ѡ������ʾ-��״ͼ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 HBITMAP choose2 =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP108 ));
	CStatic *pStaticT7 = (CStatic *)GetDlgItem(IDC_STATIC_linechoose2);
	pStaticT7->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT7->SetBitmap(choose2);
}


void Main::OnBnClickedButton18()//��һ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_STATIC_ROLL)->ShowWindow(SW_SHOW);//�ɼ�
	   CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)//δ��ʼ��
	   {
	  step1dhk.Create(IDD_Step1_DIALOG, this);  
	   step1dhk.MoveWindow(rect);
	   //****************��������ӶԻ�����ʾ��������
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
	     if(step1dhkcishu==1)//�Ѿ���ʼ��
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


void Main::OnBnClickedButton19()//�ڶ���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//�ɼ�
	   
	   if(step1dhkcishu==0)
	   {
		    MessageBox((_bstr_t)"����ִ�е�һ������ģ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	   }
	   if(treesave==0)
	   {
		   MessageBox((_bstr_t)"���ȱ����һ��������ģ��",(_bstr_t)"����", MB_OKCANCEL ); 
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


void Main::OnBnClickedButton20()//������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(step1dhkcishu==0||step2dhkcishu==0)
	{
		  MessageBox((_bstr_t)"�������ǰ����",(_bstr_t)"����", MB_OKCANCEL ); 
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
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//�ɼ�
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


void Main::OnBnClickedButton21()//���Ĳ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(step1dhkcishu==0||step2dhkcishu==0||step3dhkcishu==0)
	{
		  MessageBox((_bstr_t)"�������ǰ����",(_bstr_t)"����", MB_OKCANCEL ); 
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
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//�ɼ�
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


void Main::OnBnClickedButton22()//���岽
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//�ɼ�
}


void Main::OnBnClickedButton23()//������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	   GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW);//�ɼ�
	   GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW);//�ɼ�
}


void Main::OnBnClickedButton5()//�½�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON18)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON19)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON20)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON21)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON22)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BUTTON23)->ShowWindow(SW_SHOW); 
	 if(step1dhkcishu==0)
	   {	        
		 OnBnClickedButton18();//δ���������̣�δִ�й���һ����ֱ�ӵ��õ�һ������
	   }
	 else if(MessageBox((_bstr_t)"�Ѿ���������,δ����Ĺ��̽���ɾ��,�Ƿ�����½�",(_bstr_t)"����",MB_YESNO)==IDYES)
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
	   step1dhk.OnBnClickedButton1();//���öԻ���step1dialog�ĺ���,�����½�
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhkxianshi=1;
	 }
	
}


void Main::OnBnClickedButton8()//ɾ�������Ľڵ㣩
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		
	 CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)//��һ��δ�����޷�ɾ�����ڵ�
	   {
	        
		  MessageBox((_bstr_t)"û�н�ģ����ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	  
	   }
	   if(step1dhkxianshi==0)//��һ��δ��ʾ�ڽ����У��޷�ɾ�����ڵ�
	   {
		     MessageBox((_bstr_t)"�޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
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
	   step1dhk.deltreeitem();//����step1dialog��ɾ�����ڵ�ĺ���
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhkxianshi=1;
	   }
	
}


void Main::OnBnClickedButton7()//����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	 CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)
	   {
	        
		  MessageBox((_bstr_t)"û�н�ģ���ܱ��湤��",(_bstr_t)"����", MB_OKCANCEL ); 
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
	   step1dhk.OnBnClickedButton2();//����step1dialog�ı��溯��
	    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	   step1dhkxianshi=1;
	   }
	
}


void Main::OnBnClickedButton6()//���ļ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i,j,k,m;
	int len,len1,len2,len3,len4;
	int point;
	int line,line1,line2,line3,line4;
	openpoint=0;
		if(zhibiaoitempoint==0)
	{
		 OnBnClickedButton18();//�ȳ�ʼ������
		 //���Ȳ�����ʼ���Ѿ�д�õ����ڵ������			
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

		  CString szFileFilter=(_bstr_t)"�ı�(*.txt)|*.txt|";
	          CString szFileExt=(_bstr_t)"txt";//��չ��Ϊtxt
	          CFileDialog dlg(true,szFileExt,NULL,OFN_HIDEREADONLY,szFileFilter);
	          if(dlg.DoModal()==IDOK)
	          {
	            	CStdioFile File;
		            CString strLine,strText;//һ���洢�ı�һ������һ���洢���е�
		            File.Open(dlg.GetPathName(),CFile::modeRead);
		            char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		            setlocale( LC_CTYPE, "chs" );//�趨
					File.ReadString(strLine);//��ȡ��ͷ��һ��
					int len=strLine.GetLength();
					int line= strLine.Find((_bstr_t)"/");
					openitem[0]= strLine.Mid(0,len-(len-line));		
					int Vpoint=_ttoi(strLine.Mid(line+1,len));//�ܵ��м���	
					openitemnum[0]=Vpoint;openpoint++;
					for(i=0;i<Vpoint;i++)
		            {
					    File.ReadString(strLine);//��ȡһ���ڵ�	һ���ڵ���ʽ�������������/3
						int len1=strLine.GetLength();//��ȡ�䳤��
					    int line1= strLine.Find((_bstr_t)"/");//�ҵ�/��λ��
					    openitem[openpoint]= strLine.Mid(0,len1-(len1-line1));//��¼�ڵ����� �磺�����������	
					    int Vpoint1=_ttoi(strLine.Mid(line1+1,len1));//��ȡ/�������� ��֪�ýڵ��м����ӽڵ�	
					    openitemnum[openpoint]=Vpoint1;openpoint++;	//��¼���ӽڵ����
						for(j=0;j<Vpoint1;j++)
		                {						
							File.ReadString(strLine);//��ȡ�����ڵ�		
						    int len2=strLine.GetLength();
					        int line2= strLine.Find((_bstr_t)"/");
					        openitem[openpoint]= strLine.Mid(0,len2-(len2-line2));
					        int Vpoint2=_ttoi(strLine.Mid(line2+1,len2));//�ܵ��м���	
					        openitemnum[openpoint]=Vpoint2;openpoint++;		
							for(k=0;k<Vpoint2;k++)
		                    {
								File.ReadString(strLine);//��ȡ�����ڵ�								        
					           int len3=strLine.GetLength();
					           int line3= strLine.Find((_bstr_t)"/");
					           openitem[openpoint]= strLine.Mid(0,len3-(len3-line3));
					            openitemnum[openpoint]=0;openpoint++;	
							}
						}
		            }
					//��ȡ����
					for(i=0;i<treepoint1;i++)
			        {
				       treeitem1[i]="0";
				
					}treepoint1=0;
				    File.ReadString(strLine);//��ȡ��ͷ��һ��
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
            //�������
			/*  for(i=0;i<openpoint;i++)
		      {
				  MessageBox((_bstr_t)openitem[i]+(_bstr_t)openitemnum[i]);
			  }*/
			  //*********��ť����
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
			  //*******************************************���ú����ؽ���
			
			  step1dhk.updatatree();
			
	}
	else
	{
		if(MessageBox((_bstr_t)"�Ѿ���������ָ���Ƿ�ɾ�����������ļ�",(_bstr_t)"����",MB_YESNO)==IDYES)
		{
			 //���Ȳ�����ʼ���Ѿ�д�õ�����
			
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

		  CString szFileFilter=(_bstr_t)"�ı�(*.txt)|*.txt|";
	          CString szFileExt=(_bstr_t)"txt";//��չ��Ϊtxt
	          CFileDialog dlg(true,szFileExt,NULL,OFN_HIDEREADONLY,szFileFilter);
	          if(dlg.DoModal()==IDOK)
	          {
	            	CStdioFile File;
		            CString strLine,strText;//һ���洢�ı�һ������һ���洢���е�
		            File.Open(dlg.GetPathName(),CFile::modeRead);
		            char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		            setlocale( LC_CTYPE, "chs" );//�趨
					File.ReadString(strLine);//��ȡ��ͷ��һ��
					int len=strLine.GetLength();
					int line= strLine.Find((_bstr_t)"/");
					openitem[0]= strLine.Mid(0,len-(len-line));		
					int Vpoint=_ttoi(strLine.Mid(line+1,len));//�ܵ��м���	
					openitemnum[0]=Vpoint;openpoint++;
					for(i=0;i<Vpoint;i++)
		            {
					    File.ReadString(strLine);//��ȡһ���ڵ�	
						int len1=strLine.GetLength();
					    int line1= strLine.Find((_bstr_t)"/");
					    openitem[openpoint]= strLine.Mid(0,len1-(len1-line1));	
					    int Vpoint1=_ttoi(strLine.Mid(line1+1,len1));//�ܵ��м���	
					    openitemnum[openpoint]=Vpoint1;openpoint++;	
						for(j=0;j<Vpoint1;j++)
		                {						
							File.ReadString(strLine);//��ȡ�����ڵ�		
						    int len2=strLine.GetLength();
					        int line2= strLine.Find((_bstr_t)"/");
					        openitem[openpoint]= strLine.Mid(0,len2-(len2-line2));
					        int Vpoint2=_ttoi(strLine.Mid(line2+1,len2));//�ܵ��м���	
					        openitemnum[openpoint]=Vpoint2;openpoint++;		
							for(k=0;k<Vpoint2;k++)
		                    {
						       File.ReadString(strLine);//��ȡ�����ڵ�								        
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
					//��ȡ����
					for(i=0;i<treepoint1;i++)
			        {
				       treeitem1[i]="0";
				
					}treepoint1=0;
				    File.ReadString(strLine);//��ȡ��ͷ��һ��
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
			 //***********��ť����
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
			 //*******************************************���ú����ؽ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Main::OnBnClickedButton24()//������ڵ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)
	   {
	        
		  MessageBox((_bstr_t)"û�н�ģ������ӽڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	  
	   }
	      if(step1dhkxianshi==0)//��߸ĳ�excel
	   {
		     MessageBox((_bstr_t)"�޷���ӽڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
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


void Main::OnBnClickedButton25()//�������ڵ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 CRect rect;  
       GetDlgItem(IDC_STATIC_dialog)-> GetWindowRect(&rect); 
       ScreenToClient(&rect); 
	   if(step1dhkcishu==0)
	   {
	        
		  MessageBox((_bstr_t)"û�н�ģ����������",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	  
	   }
	      if(step1dhkxianshi==0)//��߸ĳ�excel
	   {
		     MessageBox((_bstr_t)"�޷�������",(_bstr_t)"����", MB_OKCANCEL ); 
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
	 m_ctrlTT.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}


void Main::OnBnClickedButton26()//ˢ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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


void Main::OnBnClickedButton9()//����excel
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 if(step2dhkcishu==0&&step3dhkcishu==0&&step2dhkxianshi==0&&step3dhkxianshi==0)
	   {
	        
		  MessageBox((_bstr_t)"û���б��ܵ���Excel",(_bstr_t)"����", MB_OKCANCEL ); 
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
