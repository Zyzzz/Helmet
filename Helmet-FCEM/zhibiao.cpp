// zhibiao.cpp : 实现文件
//

#include "stdafx.h"
#include "Helmet-FCEM.h"
#include "zhibiao.h"
#include "afxdialogex.h"

extern CString  zhibiaoitem[100][2];//编号  内容
extern int zhibiaoitempoint;
int cancle=0;
CString zhibiaoxx[58]={0};
// zhibiao 对话框

IMPLEMENT_DYNAMIC(zhibiao, CDialogEx)

zhibiao::zhibiao(CWnd* pParent /*=NULL*/)
	: CDialogEx(zhibiao::IDD, pParent)
{

}

zhibiao::~zhibiao()
{
}

void zhibiao::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON4, m_quanxuanbtn);
	DDX_Control(pDX, IDC_BUTTON5, m_nochoosebtn);
	DDX_Control(pDX, IDC_BUTTON2, m_cancle);
	DDX_Control(pDX, IDC_BUTTON3, m_ok);
}


BEGIN_MESSAGE_MAP(zhibiao, CDialogEx)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BUTTON2, &zhibiao::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON4, &zhibiao::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &zhibiao::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &zhibiao::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK39, &zhibiao::OnBnClickedCheck39)
END_MESSAGE_MAP()


// zhibiao 消息处理程序


void zhibiao::OnPaint()
{
	 CPaintDC dc(this);
    CDC memdc;
    memdc.CreateCompatibleDC(&dc);//创建兼容DC
    CBitmap bkg;
    bkg.LoadBitmap(IDB_BITMAP65);//载入位图
    BITMAP bkginfo;
    bkg.GetBitmap(&bkginfo);//获取位图信息
    memdc.SelectObject(&bkg);
    RECT rect;
    GetWindowRect(&rect);//获取对话框信息
    dc.StretchBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&memdc,0,0,bkginfo.bmWidth,bkginfo.bmHeight,SRCCOPY);
}


BOOL zhibiao::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HBITMAP hBitmapTITLE=NULL;
	CStatic *pStaticT = (CStatic *)GetDlgItem(IDC_STATIC_zhibiao);
    hBitmapTITLE =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP85 ));
	pStaticT->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStaticT->SetBitmap(hBitmapTITLE);
	m_quanxuanbtn.LoadBitmaps(IDB_BITMAP87,IDB_BITMAP88);
	m_nochoosebtn.LoadBitmaps(IDB_BITMAP89,IDB_BITMAP90);
	m_cancle.LoadBitmaps(IDB_BITMAP91,IDB_BITMAP92);
	m_ok.LoadBitmaps(IDB_BITMAP93,IDB_BITMAP94);
	//*************************************8
	int i;
	for(i=0;i<zhibiaoitempoint;i++)
	{
		if(zhibiaoitem[i][1]=="完成任务能力"){((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK1))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="可视性"){((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK2))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="可读性"){((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK3))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="可控性"){((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK4))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="可理解性"){((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK5))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="安全性"){((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK6))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="易学性"){((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK7))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="舒适性"){((CButton *)GetDlgItem(IDC_CHECK8))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK8))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="任务绩效"){((CButton *)GetDlgItem(IDC_CHECK9))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK9))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="情境意识"){((CButton *)GetDlgItem(IDC_CHECK10))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK10))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="工作负荷"){((CButton *)GetDlgItem(IDC_CHECK11))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK11))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="字符功能"){((CButton *)GetDlgItem(IDC_CHECK12))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK12))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="防拥"){((CButton *)GetDlgItem(IDC_CHECK13))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK13))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="信息分级合理显示"){((CButton *)GetDlgItem(IDC_CHECK14))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK14))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="字符亮度、对比度"){((CButton *)GetDlgItem(IDC_CHECK15))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK15))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="字符颜色"){((CButton *)GetDlgItem(IDC_CHECK16))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK16))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="信息漂移量"){((CButton *)GetDlgItem(IDC_CHECK17))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK17))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="字符线宽"){((CButton *)GetDlgItem(IDC_CHECK18))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK18))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="字符抖动和闪烁"){((CButton *)GetDlgItem(IDC_CHECK19))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK19))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="字符质量"){((CButton *)GetDlgItem(IDC_CHECK20))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK20))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="分辨率和视场"){((CButton *)GetDlgItem(IDC_CHECK21))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK21))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="信息显示延迟时间"){((CButton *)GetDlgItem(IDC_CHECK22))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK22))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="切换时间"){((CButton *)GetDlgItem(IDC_CHECK23))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK23))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="头部跟踪角速度"){((CButton *)GetDlgItem(IDC_CHECK24))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK24))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="头部跟踪精度"){((CButton *)GetDlgItem(IDC_CHECK25))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK25))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="更新率"){((CButton *)GetDlgItem(IDC_CHECK26))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK26))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="字符位置精度"){((CButton *)GetDlgItem(IDC_CHECK27))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK27))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="定位精度"){((CButton *)GetDlgItem(IDC_CHECK28))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK28))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="与其他显示器兼容性"){((CButton *)GetDlgItem(IDC_CHECK29))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK29))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="与反应兼容"){((CButton *)GetDlgItem(IDC_CHECK30))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK30))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="字符位置合理"){((CButton *)GetDlgItem(IDC_CHECK31))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK31))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="逻辑优化"){((CButton *)GetDlgItem(IDC_CHECK32))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK32))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="满足头部运动对字符需求"){((CButton *)GetDlgItem(IDC_CHECK33))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK33))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="字符驱动率及动态变化"){((CButton *)GetDlgItem(IDC_CHECK34))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK34))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="与真实外界对准"){((CButton *)GetDlgItem(IDC_CHECK35))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK35))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="取样间隔"){((CButton *)GetDlgItem(IDC_CHECK36))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK36))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="坐标问题"){((CButton *)GetDlgItem(IDC_CHECK37))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK37))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="对失败反馈"){((CButton *)GetDlgItem(IDC_CHECK38))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK38))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="转动自如"){((CButton *)GetDlgItem(IDC_CHECK39))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK39))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="快速解脱"){((CButton *)GetDlgItem(IDC_CHECK40))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK40))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="标准化"){((CButton *)GetDlgItem(IDC_CHECK41))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK41))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="出瞳"){((CButton *)GetDlgItem(IDC_CHECK42))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK42))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="瞳间距"){((CButton *)GetDlgItem(IDC_CHECK43))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK43))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="移动自如"){((CButton *)GetDlgItem(IDC_CHECK44))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK44))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="重量"){((CButton *)GetDlgItem(IDC_CHECK45))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK45))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="重心"){((CButton *)GetDlgItem(IDC_CHECK46))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK46))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="适体性"){((CButton *)GetDlgItem(IDC_CHECK47))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK47))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="头部跟踪器的覆盖范围"){((CButton *)GetDlgItem(IDC_CHECK48))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK48))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="双目同步"){((CButton *)GetDlgItem(IDC_CHECK49))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK49))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="双目视差"){((CButton *)GetDlgItem(IDC_CHECK50))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK50))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="双目视场叠加"){((CButton *)GetDlgItem(IDC_CHECK51))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK51))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="双目竞争"){((CButton *)GetDlgItem(IDC_CHECK52))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK52))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="双目亮度差"){((CButton *)GetDlgItem(IDC_CHECK53))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK53))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="色彩的准确性"){((CButton *)GetDlgItem(IDC_CHECK54))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK54))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="颜色的可识别性"){((CButton *)GetDlgItem(IDC_CHECK55))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK55))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="颜色语义特征"){((CButton *)GetDlgItem(IDC_CHECK56))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK56))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="色彩搭配可用性"){((CButton *)GetDlgItem(IDC_CHECK57))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK57))->EnableWindow(false);}
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control

}


LRESULT zhibiao::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 CRect rc;
     GetClientRect(&rc);
     ClientToScreen(&rc);
     return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}


void zhibiao::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	cancle=1;
    CDialog:OnOK();
}


HBRUSH zhibiao::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
  if (pWnd->GetDlgCtrlID() == IDC_CHECK1)
        { pDC->SetTextColor(RGB(0,0,0));  pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK2)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255));}
  if (pWnd->GetDlgCtrlID() == IDC_CHECK3)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK4)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK5)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK6)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK7)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK8)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK9)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK10)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
   if (pWnd->GetDlgCtrlID() == IDC_CHECK11)
        { pDC->SetTextColor(RGB(0,0,0));  pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK12)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255));}
  if (pWnd->GetDlgCtrlID() == IDC_CHECK13)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK14)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK15)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK16)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK17)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK18)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK19)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK20)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
   if (pWnd->GetDlgCtrlID() == IDC_CHECK21)
        { pDC->SetTextColor(RGB(0,0,0));  pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK22)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255));}
  if (pWnd->GetDlgCtrlID() == IDC_CHECK23)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK24)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK25)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK26)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK27)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK28)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK29)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK30)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
   if (pWnd->GetDlgCtrlID() == IDC_CHECK31)
        { pDC->SetTextColor(RGB(0,0,0));  pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK32)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255));}
  if (pWnd->GetDlgCtrlID() == IDC_CHECK33)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK34)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK35)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK36)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK37)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK38)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK39)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK40)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
   if (pWnd->GetDlgCtrlID() == IDC_CHECK41)
        { pDC->SetTextColor(RGB(0,0,0));  pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK42)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255));}
  if (pWnd->GetDlgCtrlID() == IDC_CHECK43)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK44)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK45)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK46)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK47)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK48)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK49)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK50)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
   if (pWnd->GetDlgCtrlID() == IDC_CHECK51)
        { pDC->SetTextColor(RGB(0,0,0));  pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK52)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT); return CreateSolidBrush(RGB(255,255,255));}
  if (pWnd->GetDlgCtrlID() == IDC_CHECK53)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK54)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK55)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK56)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }
  if (pWnd->GetDlgCtrlID() == IDC_CHECK57)
        { pDC->SetTextColor(RGB(0,0,0)); pDC->SetBkMode(TRANSPARENT);return CreateSolidBrush(RGB(255,255,255)); }

  return hbr;
}


void zhibiao::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(((CButton *)GetDlgItem(IDC_CHECK1))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK2))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK3))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK4))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK5))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK6))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK7))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK8))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK8))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK9))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK9))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK10))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK10))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK11))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK11))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK12))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK12))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK13))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK13))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK14))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK14))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK15))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK15))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK16))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK16))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK17))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK17))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK18))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK18))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK19))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK19))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK20))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK20))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK21))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK21))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK22))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK22))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK23))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK23))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK24))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK24))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK25))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK25))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK26))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK26))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK27))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK27))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK28))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK28))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK29))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK29))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK30))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK30))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK31))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK31))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK32))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK32))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK33))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK33))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK34))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK34))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK35))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK35))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK36))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK36))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK37))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK37))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK38))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK38))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK39))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK39))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK40))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK40))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK41))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK41))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK42))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK42))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK43))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK43))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK44))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK44))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK45))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK45))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK46))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK46))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK47))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK47))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK48))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK48))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK49))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK49))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK50))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK50))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK51))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK51))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK52))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK52))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK53))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK53))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK54))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK54))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK55))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK55))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK56))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK56))->SetCheck(true);
	if(((CButton *)GetDlgItem(IDC_CHECK57))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK57))->SetCheck(true);

	
}


void zhibiao::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if(((CButton *)GetDlgItem(IDC_CHECK1))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK2))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK3))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK4))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK5))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK6))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK7))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK8))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK8))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK9))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK9))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK10))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK10))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK11))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK11))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK12))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK12))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK13))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK13))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK14))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK14))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK15))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK15))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK16))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK16))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK17))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK17))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK18))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK18))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK19))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK19))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK20))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK20))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK21))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK21))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK22))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK22))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK23))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK23))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK24))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK24))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK25))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK25))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK26))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK26))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK27))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK27))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK28))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK28))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK29))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK29))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK30))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK30))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK31))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK31))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK32))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK32))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK33))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK33))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK34))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK34))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK35))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK35))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK36))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK36))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK37))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK37))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK38))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK38))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK39))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK39))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK40))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK40))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK41))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK41))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK42))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK42))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK43))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK43))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK44))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK44))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK45))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK45))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK46))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK46))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK47))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK47))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK48))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK48))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK49))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK49))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK50))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK50))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK51))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK51))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK52))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK52))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK53))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK53))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK54))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK54))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK55))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK55))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK56))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK56))->SetCheck(false);
	if(((CButton *)GetDlgItem(IDC_CHECK57))->IsWindowEnabled()==true)	((CButton *)GetDlgItem(IDC_CHECK57))->SetCheck(false);
}


void zhibiao::OnBnClickedButton3()//queding
{
	// TODO: 在此添加控件通知处理程序代码
	//清空
	cancle=0;
	int i;
	for(i=0;i<58;i++)
		zhibiaoxx[i]="0";
	CButton* pbtn=(CButton*)GetDlgItem(IDC_CHECK1);
	if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[1]="完成任务能力";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK2);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[2]="可视性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK3);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[3]="可读性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK4);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[4]="可控性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK5);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[5]="可理解性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK6);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[6]="安全性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK7);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[7]="易学性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK8);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[8]="舒适性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK9);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[9]="任务绩效";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK10);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[10]="情境意识";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK11);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[11]="工作负荷";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK12);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[12]="字符功能";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK13);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[13]="防拥";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK14);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[14]="信息分级合理显示";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK15);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[15]="字符亮度、对比度";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK16);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[16]="字符颜色";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK17);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[17]="信息漂移量";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK18);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[18]="字符线宽";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK19);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[19]="字符抖动和闪烁";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK20);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[20]="字符质量";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK21);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[21]="分辨率和视场";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK22);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[22]="信息显示延迟时间";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK23);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[23]="切换时间";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK24);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[24]="头部跟踪角速度";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK25);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[25]="头部跟踪精度";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK26);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[26]="更新率";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK27);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[27]="字符位置精度";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK28);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[28]="定位精度";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK29);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[29]="与其他显示器兼容性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK30);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[30]="与反应兼容";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK31);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[31]="字符位置合理";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK32);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[32]="逻辑优化";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK33);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[33]="满足头部运动对字符需求";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK34);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[34]="字符驱动率及动态变化";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK35);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[35]="与真实外界对准";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK36);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[36]="取样间隔";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK37);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[37]="坐标问题";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK38);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[38]="对失败反馈";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK39);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[39]="转动自如";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK40);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[40]="快速解脱";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK41);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[41]="标准化";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK42);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[42]="出瞳";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK43);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[43]="瞳间距";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK44);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[44]="移动自如";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK45);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[45]="重量";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK46);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[46]="重心";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK47);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[47]="适体性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK48);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[48]="头部跟踪器的覆盖范围";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK49);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[49]="双目同步";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK50);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[50]="双目视差";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK51);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[51]="双目视场叠加";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK52);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[52]="双目竞争";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK53);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[53]="双目亮度差";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK54);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[54]="色彩的准确性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK55);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[55]="颜色的可识别性";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK56);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[56]="颜色语义特征";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK57);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[57]="色彩搭配可用性";}
	 CDialog:OnOK();
}


void zhibiao::OnBnClickedCheck39()
{
	// TODO: 在此添加控件通知处理程序代码
}
