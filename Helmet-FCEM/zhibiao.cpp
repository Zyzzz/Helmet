// zhibiao.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Helmet-FCEM.h"
#include "zhibiao.h"
#include "afxdialogex.h"

extern CString  zhibiaoitem[100][2];//���  ����
extern int zhibiaoitempoint;
int cancle=0;
CString zhibiaoxx[58]={0};
// zhibiao �Ի���

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


// zhibiao ��Ϣ�������


void zhibiao::OnPaint()
{
	 CPaintDC dc(this);
    CDC memdc;
    memdc.CreateCompatibleDC(&dc);//��������DC
    CBitmap bkg;
    bkg.LoadBitmap(IDB_BITMAP65);//����λͼ
    BITMAP bkginfo;
    bkg.GetBitmap(&bkginfo);//��ȡλͼ��Ϣ
    memdc.SelectObject(&bkg);
    RECT rect;
    GetWindowRect(&rect);//��ȡ�Ի�����Ϣ
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
		if(zhibiaoitem[i][1]=="�����������"){((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK1))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="������"){((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK2))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ɶ���"){((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK3))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ɿ���"){((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK4))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�������"){((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK5))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��ȫ��"){((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK6))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��ѧ��"){((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK7))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="������"){((CButton *)GetDlgItem(IDC_CHECK8))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK8))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="����Ч"){((CButton *)GetDlgItem(IDC_CHECK9))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK9))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�龳��ʶ"){((CButton *)GetDlgItem(IDC_CHECK10))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK10))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��������"){((CButton *)GetDlgItem(IDC_CHECK11))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK11))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ַ�����"){((CButton *)GetDlgItem(IDC_CHECK12))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK12))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��ӵ"){((CButton *)GetDlgItem(IDC_CHECK13))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK13))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��Ϣ�ּ�������ʾ"){((CButton *)GetDlgItem(IDC_CHECK14))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK14))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ַ����ȡ��Աȶ�"){((CButton *)GetDlgItem(IDC_CHECK15))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK15))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ַ���ɫ"){((CButton *)GetDlgItem(IDC_CHECK16))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK16))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��ϢƯ����"){((CButton *)GetDlgItem(IDC_CHECK17))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK17))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ַ��߿�"){((CButton *)GetDlgItem(IDC_CHECK18))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK18))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ַ���������˸"){((CButton *)GetDlgItem(IDC_CHECK19))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK19))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ַ�����"){((CButton *)GetDlgItem(IDC_CHECK20))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK20))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ֱ��ʺ��ӳ�"){((CButton *)GetDlgItem(IDC_CHECK21))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK21))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��Ϣ��ʾ�ӳ�ʱ��"){((CButton *)GetDlgItem(IDC_CHECK22))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK22))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�л�ʱ��"){((CButton *)GetDlgItem(IDC_CHECK23))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK23))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="ͷ�����ٽ��ٶ�"){((CButton *)GetDlgItem(IDC_CHECK24))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK24))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="ͷ�����پ���"){((CButton *)GetDlgItem(IDC_CHECK25))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK25))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="������"){((CButton *)GetDlgItem(IDC_CHECK26))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK26))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ַ�λ�þ���"){((CButton *)GetDlgItem(IDC_CHECK27))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK27))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��λ����"){((CButton *)GetDlgItem(IDC_CHECK28))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK28))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��������ʾ��������"){((CButton *)GetDlgItem(IDC_CHECK29))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK29))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�뷴Ӧ����"){((CButton *)GetDlgItem(IDC_CHECK30))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK30))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ַ�λ�ú���"){((CButton *)GetDlgItem(IDC_CHECK31))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK31))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�߼��Ż�"){((CButton *)GetDlgItem(IDC_CHECK32))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK32))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="����ͷ���˶����ַ�����"){((CButton *)GetDlgItem(IDC_CHECK33))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK33))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ַ������ʼ���̬�仯"){((CButton *)GetDlgItem(IDC_CHECK34))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK34))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="����ʵ����׼"){((CButton *)GetDlgItem(IDC_CHECK35))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK35))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="ȡ�����"){((CButton *)GetDlgItem(IDC_CHECK36))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK36))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��������"){((CButton *)GetDlgItem(IDC_CHECK37))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK37))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��ʧ�ܷ���"){((CButton *)GetDlgItem(IDC_CHECK38))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK38))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="ת������"){((CButton *)GetDlgItem(IDC_CHECK39))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK39))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="���ٽ���"){((CButton *)GetDlgItem(IDC_CHECK40))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK40))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��׼��"){((CButton *)GetDlgItem(IDC_CHECK41))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK41))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��ͫ"){((CButton *)GetDlgItem(IDC_CHECK42))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK42))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="ͫ���"){((CButton *)GetDlgItem(IDC_CHECK43))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK43))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="�ƶ�����"){((CButton *)GetDlgItem(IDC_CHECK44))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK44))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="����"){((CButton *)GetDlgItem(IDC_CHECK45))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK45))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="����"){((CButton *)GetDlgItem(IDC_CHECK46))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK46))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="������"){((CButton *)GetDlgItem(IDC_CHECK47))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK47))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="ͷ���������ĸ��Ƿ�Χ"){((CButton *)GetDlgItem(IDC_CHECK48))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK48))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="˫Ŀͬ��"){((CButton *)GetDlgItem(IDC_CHECK49))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK49))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="˫Ŀ�Ӳ�"){((CButton *)GetDlgItem(IDC_CHECK50))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK50))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="˫Ŀ�ӳ�����"){((CButton *)GetDlgItem(IDC_CHECK51))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK51))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="˫Ŀ����"){((CButton *)GetDlgItem(IDC_CHECK52))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK52))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="˫Ŀ���Ȳ�"){((CButton *)GetDlgItem(IDC_CHECK53))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK53))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="ɫ�ʵ�׼ȷ��"){((CButton *)GetDlgItem(IDC_CHECK54))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK54))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��ɫ�Ŀ�ʶ����"){((CButton *)GetDlgItem(IDC_CHECK55))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK55))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="��ɫ��������"){((CButton *)GetDlgItem(IDC_CHECK56))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK56))->EnableWindow(false);}
		if(zhibiaoitem[i][1]=="ɫ�ʴ��������"){((CButton *)GetDlgItem(IDC_CHECK57))->SetCheck(true);((CButton *)GetDlgItem(IDC_CHECK57))->EnableWindow(false);}
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control

}


LRESULT zhibiao::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	 CRect rc;
     GetClientRect(&rc);
     ClientToScreen(&rc);
     return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}


void zhibiao::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���
	cancle=0;
	int i;
	for(i=0;i<58;i++)
		zhibiaoxx[i]="0";
	CButton* pbtn=(CButton*)GetDlgItem(IDC_CHECK1);
	if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[1]="�����������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK2);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[2]="������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK3);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[3]="�ɶ���";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK4);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[4]="�ɿ���";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK5);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[5]="�������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK6);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[6]="��ȫ��";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK7);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[7]="��ѧ��";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK8);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[8]="������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK9);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[9]="����Ч";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK10);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[10]="�龳��ʶ";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK11);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[11]="��������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK12);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[12]="�ַ�����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK13);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[13]="��ӵ";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK14);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[14]="��Ϣ�ּ�������ʾ";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK15);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[15]="�ַ����ȡ��Աȶ�";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK16);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[16]="�ַ���ɫ";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK17);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[17]="��ϢƯ����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK18);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[18]="�ַ��߿�";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK19);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[19]="�ַ���������˸";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK20);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[20]="�ַ�����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK21);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[21]="�ֱ��ʺ��ӳ�";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK22);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[22]="��Ϣ��ʾ�ӳ�ʱ��";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK23);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[23]="�л�ʱ��";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK24);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[24]="ͷ�����ٽ��ٶ�";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK25);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[25]="ͷ�����پ���";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK26);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[26]="������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK27);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[27]="�ַ�λ�þ���";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK28);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[28]="��λ����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK29);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[29]="��������ʾ��������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK30);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[30]="�뷴Ӧ����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK31);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[31]="�ַ�λ�ú���";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK32);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[32]="�߼��Ż�";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK33);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[33]="����ͷ���˶����ַ�����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK34);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[34]="�ַ������ʼ���̬�仯";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK35);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[35]="����ʵ����׼";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK36);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[36]="ȡ�����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK37);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[37]="��������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK38);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[38]="��ʧ�ܷ���";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK39);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[39]="ת������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK40);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[40]="���ٽ���";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK41);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[41]="��׼��";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK42);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[42]="��ͫ";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK43);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[43]="ͫ���";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK44);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[44]="�ƶ�����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK45);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[45]="����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK46);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[46]="����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK47);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[47]="������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK48);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[48]="ͷ���������ĸ��Ƿ�Χ";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK49);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[49]="˫Ŀͬ��";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK50);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[50]="˫Ŀ�Ӳ�";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK51);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[51]="˫Ŀ�ӳ�����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK52);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[52]="˫Ŀ����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK53);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[53]="˫Ŀ���Ȳ�";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK54);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[54]="ɫ�ʵ�׼ȷ��";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK55);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[55]="��ɫ�Ŀ�ʶ����";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK56);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[56]="��ɫ��������";}
	pbtn=(CButton*)GetDlgItem(IDC_CHECK57);if(pbtn->GetCheck()==1&&pbtn->IsWindowEnabled()==true){  zhibiaoxx[57]="ɫ�ʴ��������";}
	 CDialog:OnOK();
}


void zhibiao::OnBnClickedCheck39()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
