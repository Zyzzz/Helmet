// Step2dialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Helmet-FCEM.h"
#include "Step2dialog.h"
#include "afxdialogex.h"
#include  "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"

//***************************������ָ����������
//extern int Ftreenum;
//extern CString Ftree[200];

//**************************
float quanzhong[70]={0.0};//һ��ָ���Ȩ��
float Two_wight[70] = { 0.0 };
float Three_wight[70] = { 0.0 };
int Two_wightNum=0;
int Three_wightNum = 0;
int falg = 1;
int One_Node = 1;
int Qsave=0;
int Two_listnum = 1;
int Three_listnum = 1;
int Two_Pos[70];
int Three_Pos[70];
int quanzhongnum=0;
CToolTipCtrl  m_ctrlTT1;
CString shuru;int hang,lie,lieshu11=0;
extern CString  treeitem1[100];//������������
extern int treepoint1;
extern  CString  zhibiaoitem[100][2];//��һ��ָ���������нڵ� [0]���(���ڷ���������֪��˭��˭��һ��)  [1]����
extern int zhibiaoitempoint;
extern int zhibiaoitemchilds[100];
// Step2dialog �Ի���

IMPLEMENT_DYNAMIC(Step2dialog, CDialogEx)

Step2dialog::Step2dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(Step2dialog::IDD, pParent)
	
{

}

Step2dialog::~Step2dialog()
{
}

void Step2dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_BUTTON1, m_guiyihuabtn);
	DDX_Control(pDX, IDC_BUTTON27, m_tip);
	DDX_Control(pDX, IDC_BUTTON28, m_save);
	DDX_Control(pDX, IDC_LIST2, Two_lists);
	DDX_Control(pDX, IDC_LIST3, Three_lists);
}


BEGIN_MESSAGE_MAP(Step2dialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &Step2dialog::OnBnClickedOk)
	ON_WM_PAINT()

	ON_EN_KILLFOCUS(IDC_EDIT1, &Step2dialog::OnEnKillfocusEdit1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &Step2dialog::OnNMDblclkList1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &Step2dialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON27, &Step2dialog::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &Step2dialog::OnBnClickedButton28)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &Step2dialog::OnDblclkList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &Step2dialog::OnDblclkList3)
END_MESSAGE_MAP()


// Step2dialog ��Ϣ�������


void Step2dialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


BOOL Step2dialog::PreTranslateMessage(MSG* pMsg)
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
	 m_ctrlTT1.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL Step2dialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HBITMAP hBitmap=NULL;
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_p2);
    hBitmap =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP76 ));
	pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStatic->SetBitmap(hBitmap);
	m_guiyihuabtn.LoadBitmaps(IDB_BITMAP80,IDB_BITMAP81);
	m_tip.LoadBitmaps(IDB_BITMAP95,IDB_BITMAP96);
	m_save.LoadBitmaps(IDB_BITMAP97,IDB_BITMAP98);
	//*****************************************
	 EnableToolTips(TRUE);//enable use it
   m_ctrlTT1.Create(this);
   m_ctrlTT1.Activate(TRUE);
   m_ctrlTT1.SetTipTextColor(RGB(0,0,0));//font color
 
   //IDC_TESTΪ���������ʾ�Ŀؼ�IDC��"helloΪ����ӵ���ʾ���"
   m_ctrlTT1.AddTool(GetDlgItem(IDC_BUTTON1),(_bstr_t)"��һ��");
   m_ctrlTT1.AddTool(GetDlgItem(IDC_BUTTON27),(_bstr_t)"��ʾ");
   m_ctrlTT1.AddTool(GetDlgItem(IDC_BUTTON28),(_bstr_t)"����Ȩ����Ϣ");
	//********************************��ʼ����
   //Ftree[]�������Ŀ�������¸�ʽ�� 1�����������/3   2��ѧ��/0  3�龳��ʶ
	int i,k,yiji,xie;
	int pos2=0;
	int pos3 = 0;
	int len=Ftree[0].GetLength();
	int line= Ftree[0].Find((_bstr_t)"/");
	int Vpoint=_ttoi(Ftree[0].Mid(line+1,len));//һ���ܵ��м���	
	m_list.InsertColumn(0, (_bstr_t)Ftree[0].Mid(1,line-1), LVCFMT_LEFT, 140);
	Two_lists.InsertColumn(0, (_bstr_t)"��������", LVCFMT_LEFT, 140);
	Three_lists.InsertColumn(0, (_bstr_t)"����������", LVCFMT_LEFT, 140);
	for (k = 0, i = 1; k < Ftreenum; k++)
	{
		yiji = Ftree[k].Find((_bstr_t)"1");
		xie = Ftree[k].Find((_bstr_t)"/");
		if (yiji == 0)
		{
			One_Node++;
			char s = Ftree[k].GetAt(Ftree[k].GetLength() - 1);
			int a = s - 48;
			m_list.InsertColumn(i, (_bstr_t)Ftree[k].Mid(1, xie - 1), LVCFMT_LEFT, 140);
			i++;
			Two_Pos[k] = a;
		}
		else
		{
			yiji = Ftree[k].Find((_bstr_t)"2");
			if (yiji == 0)
			{
				char s = Ftree[k].GetAt(Ftree[k].GetLength() - 1);
				int a = s - 48;
				Two_lists.InsertColumn(Two_listnum, (_bstr_t)Ftree[k].Mid(1, xie - 1), LVCFMT_LEFT, 140);
				Two_listnum++;
				//Two_wightNum++;
				Three_Pos[k] = a;
			}
			else
			{
				yiji = Ftree[k].Find((_bstr_t)"3");
				if (yiji == 0)
				{
					Three_lists.InsertColumn(Three_listnum, (_bstr_t)Ftree[k].Mid(1,Ftree[k].GetLength()-1), LVCFMT_LEFT, 140);
					Three_listnum++;
					//Two_wightNum++;
				}
			}
		}
	}
    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    m_list.InsertItem(0, (_bstr_t)"");
	m_list.SetItemText(0,0,(_bstr_t)"Ȩ��");
	//Two_lists.
	Two_lists.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Two_lists.InsertItem(0, (_bstr_t)"");
	Two_lists.SetItemText(0, 0, (_bstr_t)"Ȩ��");
	Three_lists.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	Three_lists.InsertItem(0, (_bstr_t)"");
	Three_lists.SetItemText(0, 0, (_bstr_t)"Ȩ��");
	int j;
	for(j=1;j<=Vpoint;j++)
		m_list.SetItemText(0,j,(_bstr_t)"˫������");

	for (j = 1; j <= Two_listnum; j++)
		Two_lists.SetItemText(0, j, (_bstr_t)"˫������");


	for (j = 1; j <= Three_listnum; j++)
		Three_lists.SetItemText(0, j, (_bstr_t)"˫������");


	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control

}


void Step2dialog::OnPaint()
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




void Step2dialog::OnEnKillfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 m_edit.GetWindowText(shuru);    //�õ��û�������µ����� 
	 for (int i = 0 ; i <shuru.GetLength();i++)    
    {    
       int unicode = (int)shuru.GetAt(i);    
	   if (unicode != '9'&&unicode !='0'&&unicode !='1'&&unicode !='2'&&unicode !='3'&&unicode !='4'&&unicode !='5'&&unicode !='6'&&unicode !='7'&&unicode !='8'&&unicode != '.')    
	   {
		   MessageBox((_bstr_t)"�����к��������Ƿ��ַ�����������ȷ��������Ϣ",(_bstr_t)"��ʾ", MB_OK); 
			return;
	   }
    }   
	 if (falg == 1)
	 {
		 m_list.SetItemText(hang, lie, shuru);   //���ñ༭���������  
		 m_edit.ShowWindow(SW_HIDE);                //Ӧ�ر༭��  
	 }
	 else if (falg ==2 )
	 {
		 Two_lists.SetItemText(hang, lie, shuru);   //���ñ༭���������  
		 m_edit.ShowWindow(SW_HIDE);                //Ӧ�ر༭��  
	 }
	 else
	 {
		 Three_lists.SetItemText(hang, lie, shuru);   //���ñ༭���������  
		 m_edit.ShowWindow(SW_HIDE);
	 }
}


void Step2dialog::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR; 
	 CRect rc;  
	 falg = 1;
    hang = pNMListView->iItem;//���ѡ�е���  
    lie = pNMListView->iSubItem;//���ѡ����  
	if(m_list.GetItemText(hang,lie)=="˫������")
		m_list.SetItemText(hang,lie,(_bstr_t)"0");
    if   (pNMListView->iSubItem != 0) //���ѡ���������;  
    {  
        m_list.GetSubItemRect(hang,lie,LVIR_LABEL,rc);//��������RECT��  
        m_edit.SetParent(&m_list);//ת������Ϊ�б���е�����  
        m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;  
        m_edit.SetWindowText(m_list.GetItemText(hang,lie));//���������е�ֵ����Edit�ؼ��У�  
        m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���  
        m_edit.SetFocus();//����Edit����  
        m_edit.ShowCaret();//��ʾ���  
        m_edit.SetSel(-1);//������ƶ������  
		
    }  
	*pResult = 0;
}


void Step2dialog::shuaxinlist(void)//ˢ��
{
	m_list.DeleteAllItems();
	CHeaderCtrl* pHeaderCtrl = m_list.GetHeaderCtrl();

if (pHeaderCtrl != NULL)
{
   int  nColumnCount = pHeaderCtrl->GetItemCount();
   for (int i=0; i<nColumnCount; i++)
   {
      m_list.DeleteColumn(0);
   }
}

	int i, k, yiji, xie;
	
	int len = Ftree[0].GetLength();
	int line = Ftree[0].Find((_bstr_t)"/");
	int Vpoint = _ttoi(Ftree[0].Mid(line + 1, len));//һ���ܵ��м���	
	m_list.InsertColumn(0, (_bstr_t)Ftree[0].Mid(1, line - 1), LVCFMT_LEFT, 140);
	Two_lists.InsertColumn(0, (_bstr_t)"��������", LVCFMT_LEFT, 140);
	Three_lists.InsertColumn(0, (_bstr_t)"����������", LVCFMT_LEFT, 140);
	for (k = 0, i = 1; k < Ftreenum; k++)
	{
		yiji = Ftree[k].Find((_bstr_t)"1");
		xie = Ftree[k].Find((_bstr_t)"/");
		if (yiji == 0)
		{
			m_list.InsertColumn(i, (_bstr_t)Ftree[k].Mid(1, xie - 1), LVCFMT_LEFT, 140);
			i++;
		}
		else
		{
			yiji = Ftree[k].Find((_bstr_t)"2");
			if (yiji == 0)
			{
				Two_lists.InsertColumn(Two_listnum, (_bstr_t)Ftree[k].Mid(1, xie - 1), LVCFMT_LEFT, 140);
				Two_listnum++;
			}
			else
			{
				yiji = Ftree[k].Find((_bstr_t)"3");
				if (yiji == 0)
				{
					Three_lists.InsertColumn(Three_listnum, (_bstr_t)Ftree[k].Mid(1, Ftree[k].GetLength() - 1), LVCFMT_LEFT, 140);
					Three_listnum++;
				}
			}
	}
}
m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
m_list.InsertItem(0, (_bstr_t)"");
m_list.SetItemText(0, 0, (_bstr_t)"Ȩ��");
//Two_lists.
Two_lists.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
Two_lists.InsertItem(0, (_bstr_t)"");
Two_lists.SetItemText(0, 0, (_bstr_t)"Ȩ��");
Three_lists.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
Three_lists.InsertItem(0, (_bstr_t)"");
Three_lists.SetItemText(0, 0, (_bstr_t)"Ȩ��");
int j;
for (j = 1; j <= Vpoint; j++)
m_list.SetItemText(0, j, (_bstr_t)"˫������");

for (j = 1; j <= Two_listnum; j++)
Two_lists.SetItemText(0, j, (_bstr_t)"˫������");


for (j = 1; j <= Three_listnum; j++)
Three_lists.SetItemText(0, j, (_bstr_t)"˫������");


}


HBRUSH Step2dialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
  if (pWnd->GetDlgCtrlID() == IDC_STATIC)
        {
             pDC->SetTextColor(RGB(0,0,0)); //����������ɫ
             pDC->SetBkMode(TRANSPARENT);
             return CreateSolidBrush(RGB(255,255,255));
        }
	return hbr;
}


void Step2dialog::OnBnClickedButton1()//��һ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
/*	int i,j,zs,xs,z=10;float xss,chu;
	float num[100],sumnum=0;num[0]=0; 
	CString input,zhengshu,xiaoshu;
	
	for(i=1;i<treepoint;i++)
    {
	  if( m_list.GetItemText(0,i)==""||m_list.GetItemText(0,i)=="˫������")
	 {
		   MessageBox((_bstr_t)"Ȩ�ز���Ϊ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	 }
	input=m_list.GetItemText(0,i);	
	chu=atof(input);//MessageBox((_bstr_t)chu,(_bstr_t)"����", MB_OKCANCEL );
	num[i]=chu;
    sumnum+=num[i];
	}
	for(i=1;i<treepoint;i++)
    {
		xss=(float)num[i]/sumnum;MessageBox((_bstr_t)xss,(_bstr_t)"����", MB_OKCANCEL );
	}
	*/
}


void Step2dialog::OnBnClickedButton27()//��ʾ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 MessageBox((_bstr_t)"1.�����ˢ�¡�ˢ���б�;\r2.���������Excel�������б�\r3.��дȨ��ֵ�����ȱ�����ִ����һ��\r4.����д��һ���������\r5.����ΪС�����7λ",(_bstr_t)"��ʾ", MB_OK ); 
}




void Step2dialog::Lin_ExportListToExcel(CListCtrl &m_List)//����excel
{
	CApplication app;
	CWorkbooks books;
	CWorkbook book;
	CWorksheets sheets;
	CWorksheet sheet;
	CRange range;
	CRange cols;
	int i = 3;
	CString str1, str2;
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if( !app.CreateDispatch(_T("Excel.Application")))
	{
		
		MessageBox((_bstr_t)"û�а�װExcel�޷�����Excel",(_bstr_t)"����", MB_OKCANCEL ); 
		return;
	}
	books=app.get_Workbooks();
	book=books.Add(covOptional);
	sheets=book.get_Sheets();
	sheet=sheets.get_Item(COleVariant((short)1));
	//д���ͷ//
	for (int ColumNum=1;ColumNum<m_List.GetHeaderCtrl()->GetItemCount();ColumNum++)
	{
		str2 = Lin_GetEnglishCharacter(ColumNum);
		str2 = str2 + _T("1");
		LVCOLUMN   lvColumn;   
		TCHAR strChar[256];
		lvColumn.pszText=strChar;   
		lvColumn.cchTextMax=256 ;
		lvColumn.mask   = LVCF_TEXT;
		m_List.GetColumn(ColumNum,&lvColumn);
		CString str=lvColumn.pszText;
		range=sheet.get_Range(COleVariant(str2),COleVariant(str2));
		range.put_Value2(COleVariant(str));

	}
	//��ȡ��Ԫ���λ��//
	for (int ColumNum =1;ColumNum<m_List.GetHeaderCtrl()->GetItemCount();ColumNum++)
	{
		
		for (int ItemNum = 0;ItemNum<m_List.GetItemCount();ItemNum++)
		{
			str2 = Lin_GetEnglishCharacter(ColumNum);
			str1.Format(_T("%d"),ItemNum+2);
			str2 = str2+str1;
			CString str = m_List.GetItemText(ItemNum,ColumNum);
			range=sheet.get_Range(COleVariant(str2),COleVariant(str2));
			range.put_Value2(COleVariant(str));
		}
	}
	cols=range.get_EntireColumn();
	cols.AutoFit();

	app.put_Visible(TRUE);
	app.put_UserControl(TRUE);
}


CString Step2dialog::Lin_GetEnglishCharacter(int Num)
{
	CString str2;
	switch(Num){
	case 1:
		str2.Format(_T("A"));
		break;
	case 2:
		str2.Format(_T("B"));
		break;
	case 3:
		str2.Format(_T("C"));
		break;
	case 4:
		str2.Format(_T("D"));
		break;
	case 5:
		str2.Format(_T("E"));
		break;
	case 6:
		str2.Format(_T("F"));
		break;
	case 7:
		str2.Format(_T("G"));
		break;
	case 8:
		str2.Format(_T("H"));
		break;
	case 9:
		str2.Format(_T("I"));
		break;
	case 10:
		str2.Format(_T("J"));
		break;
	case 11:
		str2.Format(_T("K"));
		break;
	case 12:
		str2.Format(_T("L"));
		break;
	case 13:
		str2.Format(_T("M"));
		break;
	case 14:
		str2.Format(_T("N"));
		break;
	case 15:
		str2.Format(_T("O"));
		break;
	case 16:
		str2.Format(_T("P"));
		break;
	case 17:
		str2.Format(_T("Q"));
		break;
	case 18:
		str2.Format(_T("R"));
		break;
	case 19:
		str2.Format(_T("S"));
		break;
	case 20:
		str2.Format(_T("T"));
		break;
	case 21:
		str2.Format(_T("U"));
		break;
	case 22:
		str2.Format(_T("V"));
		break;
	case 23:
		str2.Format(_T("W"));
		break;
	case 24:
		str2.Format(_T("X"));
		break;
	case 25:
		str2.Format(_T("Y"));
		break;
	case 26:
		str2.Format(_T("Z"));
		break;
		case 27:
		str2.Format(_T("AA"));
		break;
		case 28:
		str2.Format(_T("AB"));
		break;
		case 29:
		str2.Format(_T("AC"));
		break;
		case 30:
		str2.Format(_T("AD"));
		break;
		case 31:
		str2.Format(_T("AE"));
		break;
		case 32:
		str2.Format(_T("AF"));
		break;
		case 33:
		str2.Format(_T("AG"));
		break;
		case 34:
		str2.Format(_T("AH"));
		break;
		case 35:
		str2.Format(_T("AI"));
		break;
		case 36:
		str2.Format(_T("AJ"));
		break;
		case 37:
		str2.Format(_T("AK"));
		break;
		case 38:
		str2.Format(_T("AL"));
		break;
		case 39:
		str2.Format(_T("AM"));
		break;
		case 40:
		str2.Format(_T("AN"));
		break;
		case 41:
		str2.Format(_T("AO"));
		break;
		case 42:
		str2.Format(_T("AP"));
		break;
		case 43:
		str2.Format(_T("AQ"));
		break;
		case 44:
		str2.Format(_T("AR"));
		break;
		case 45:
		str2.Format(_T("AS"));
		break;
		case 46:
		str2.Format(_T("AT"));
		break;
		case 47:
		str2.Format(_T("AU"));
		break;
		case 48:
		str2.Format(_T("AV"));
		break;
		case 49:
		str2.Format(_T("AW"));
		break;
		case 50:
		str2.Format(_T("AX"));
		break;
		case 51:
		str2.Format(_T("AY"));
		break;
		case 52:
		str2.Format(_T("AZ"));
		break;
		case 53:
		str2.Format(_T("BA"));
		break;
		case 54:
		str2.Format(_T("BB"));
		break;
		case 55:
		str2.Format(_T("BC"));
		break;
		case 56:
		str2.Format(_T("BD"));
		break;
		case 57:
		str2.Format(_T("BE"));
		break;
		case 58:
		str2.Format(_T("BF"));
		break;
		case 59:
		str2.Format(_T("BG"));
		break;
		case 60:
		str2.Format(_T("BH"));
		break;
		
	default:
		str2.Format(_T("Z"));
		break;
	}
	return str2;
}



void Step2dialog::excel(void)
{
	Lin_ExportListToExcel(m_list);
	Lin_ExportListToExcel(Two_lists);
	Lin_ExportListToExcel(Three_lists);
}


void Step2dialog::OnBnClickedButton28()//����Ȩ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i,j,zs,xs,z=10;float xss,chu;
	float num[100],sumnum=0;num[0]=0; 
	CString input,zhengshu,xiaoshu;
	
	for (i = 1; i<One_Node; i++)
    {
	  if( m_list.GetItemText(0,i)==""||m_list.GetItemText(0,i)=="˫������")
	 {
		   MessageBox((_bstr_t)"Ȩ�ز���Ϊ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	 }
		input=m_list.GetItemText(0,i);	
		chu=atof(input);//MessageBox((_bstr_t)chu,(_bstr_t)"����", MB_OKCANCEL );
		num[i]=chu;
		sumnum+=num[i];
	}
	if(int(sumnum)!=1)
	{
		MessageBox((_bstr_t)"һ��Ȩ��δ��һ�������ȹ�һ��",(_bstr_t)"����", MB_OK); 
			return;
	}
	if (int(sumnum + 0.9) != 1)
	{
		MessageBox((_bstr_t)"һ��Ȩ��δ��һ�������ȹ�һ��", (_bstr_t)"����", MB_OK);
		return;
	}
	for(i=1;i<zhibiaoitempoint;i++)
    {
		quanzhong[quanzhongnum]=num[i];
		quanzhongnum++;
	}
	

	int pos = 1;
	int Sum = 0;
	int pos2 = 1;
	for (i = 1; i<zhibiaoitempoint; i++)
	{
		sumnum = 0;
		if (Two_Pos[i] != 0)
		{

			Sum = Sum + Two_Pos[i];
			for (; pos <= Sum; pos++)
			{
				if (Two_lists.GetItemText(0, pos) == "" || Two_lists.GetItemText(0, pos) == "˫������")
				{
					MessageBox((_bstr_t)"����Ȩ�ز���Ϊ��", (_bstr_t)"����", MB_OKCANCEL);
					return;
				}
				input = Two_lists.GetItemText(0, pos);
				chu = atof(input);//MessageBox((_bstr_t)chu,(_bstr_t)"����", MB_OKCANCEL );
				num[pos] = chu;
				sumnum += num[pos];
			}
			if (int(sumnum) != 1)
			{
				MessageBox((_bstr_t)"����Ȩ��δ��һ�������ȹ�һ��", (_bstr_t)"����", MB_OK);
				return;
			}
			if (int(sumnum+0.9) != 1)
			{
				MessageBox((_bstr_t)"����Ȩ��δ��һ�������ȹ�һ��", (_bstr_t)"����", MB_OK);
				return;
			}
			for (; pos2 <= Sum; pos2++)
			{
				Two_wight[pos2] = num[pos2];
				Two_wightNum++;
			}
		}	
	}
		

	pos = 1;
	Sum = 0;
	pos2 = 1;
	for (i = 1; i<zhibiaoitempoint; i++)
	{
		sumnum = 0;
		if (Three_Pos[i] != 0)
		{
			Sum = Sum + Three_Pos[i];
			for (; pos <= Sum; pos++)
			{
				if (Three_lists.GetItemText(0, pos) == "" || Three_lists.GetItemText(0, pos) == "˫������")
				{
					MessageBox((_bstr_t)"����Ȩ�ز���Ϊ��", (_bstr_t)"����", MB_OKCANCEL);
					return;
				}
				input = Three_lists.GetItemText(0, pos);
				chu = atof(input);//MessageBox((_bstr_t)chu,(_bstr_t)"����", MB_OKCANCEL );
				num[pos] = chu;
				sumnum += num[pos];
			}
			if (int(sumnum) != 1)
			{
				MessageBox((_bstr_t)"����Ȩ��δ��һ�������ȹ�һ��", (_bstr_t)"����", MB_OK);
				return;
			}
			if (int(sumnum + 0.9) != 1)
			{
				MessageBox((_bstr_t)"����Ȩ��δ��һ�������ȹ�һ��", (_bstr_t)"����", MB_OK);
				return;
			}
			for (; pos2 <= Sum; pos2++)
			{
				Three_wight[pos2] = num[pos2];
				Three_wightNum++;
			}
		}
	}





	Qsave=1;
	MessageBox((_bstr_t)"�ѱ���",(_bstr_t)"��ʾ", MB_OK ); 
	/*for(i=0;i<quanzhongnum;i++)
    {
		
		MessageBox((_bstr_t)quanzhong[i]+"Ȩ��",(_bstr_t)"����", MB_OKCANCEL ); 
	}*/
}


void Step2dialog::OnDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	falg = 2;
	hang = pNMListView->iItem;//���ѡ�е���  
	lie = pNMListView->iSubItem;//���ѡ����  
	if (Two_lists.GetItemText(hang, lie) == "˫������")
		Two_lists.SetItemText(hang, lie, (_bstr_t)"0");
	if (pNMListView->iSubItem != 0) //���ѡ���������;  
	{
		Two_lists.GetSubItemRect(hang, lie, LVIR_LABEL, rc);//��������RECT��  
		m_edit.SetParent(&Two_lists);//ת������Ϊ�б���е�����  
		m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;  
		m_edit.SetWindowText(Two_lists.GetItemText(hang, lie));//���������е�ֵ����Edit�ؼ��У�  
		m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���  
		m_edit.SetFocus();//����Edit����  
		m_edit.ShowCaret();//��ʾ���  
		m_edit.SetSel(-1);//������ƶ������  

	}
	*pResult = 0;
}


void Step2dialog::OnDblclkList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	falg = 3;
	hang = pNMListView->iItem;//���ѡ�е���  
	lie = pNMListView->iSubItem;//���ѡ����  
	if (Three_lists.GetItemText(hang, lie) == "˫������")
		Three_lists.SetItemText(hang, lie, (_bstr_t)"0");
	if (pNMListView->iSubItem != 0) //���ѡ���������;  
	{
		Three_lists.GetSubItemRect(hang, lie, LVIR_LABEL, rc);//��������RECT��  
		m_edit.SetParent(&Three_lists);//ת������Ϊ�б���е�����  
		m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;  
		m_edit.SetWindowText(Three_lists.GetItemText(hang, lie));//���������е�ֵ����Edit�ؼ��У�  
		m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���  
		m_edit.SetFocus();//����Edit����  
		m_edit.ShowCaret();//��ʾ���  
		m_edit.SetSel(-1);//������ƶ������  

	}
	*pResult = 0;
}
