// Step3dialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Helmet-FCEM.h"
#include "Step3dialog.h"
#include "afxdialogex.h"
#include  "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
CToolTipCtrl  m_ctrlTT2;
extern CString  treeitem[100],treeitem1[100];
extern int treepoint,treepoint1;
int Rsave=0;
float R[100][100]={0.0};
int NodeNum = 0;
extern int zhibiaoitempoint;
CString shuru3;int hang3,lie3,lieshu3=0;
// Step3dialog �Ի���

IMPLEMENT_DYNAMIC(Step3dialog, CDialogEx)

Step3dialog::Step3dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(Step3dialog::IDD, pParent)
{

}

Step3dialog::~Step3dialog()
{
}

void Step3dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_BUTTON27, m_tip);
	DDX_Control(pDX, IDC_BUTTON28, m_rsave);
}


BEGIN_MESSAGE_MAP(Step3dialog, CDialogEx)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_EDIT1, &Step3dialog::OnEnKillfocusEdit1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &Step3dialog::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON27, &Step3dialog::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &Step3dialog::OnBnClickedButton28)
END_MESSAGE_MAP()


// Step3dialog ��Ϣ�������


void Step3dialog::OnPaint()
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


BOOL Step3dialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HBITMAP hBitmap=NULL;
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_p3);
    hBitmap =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP86 ));
	pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStatic->SetBitmap(hBitmap);
	m_tip.LoadBitmaps(IDB_BITMAP95,IDB_BITMAP96);
		m_rsave.LoadBitmaps(IDB_BITMAP97,IDB_BITMAP98);
	//************************************
	 EnableToolTips(TRUE);//enable use it
   m_ctrlTT2.Create(this);
   m_ctrlTT2.Activate(TRUE);
   m_ctrlTT2.SetTipTextColor(RGB(0,0,0));//font color
 
   //IDC_TESTΪ���������ʾ�Ŀؼ�IDC��"helloΪ����ӵ���ʾ���"
   m_ctrlTT2.AddTool(GetDlgItem(IDC_BUTTON27),(_bstr_t)"��ʾ");
    m_ctrlTT2.AddTool(GetDlgItem(IDC_BUTTON28),(_bstr_t)"����Ȩ����Ϣ");


	int i;
	m_list.InsertColumn(0, (_bstr_t)"ָ��/�ȼ�", LVCFMT_LEFT, 140);
	for(i=1;i<treepoint1;i++)
	{
		//MessageBox((_bstr_t)treeitem[i]);
		m_list.InsertColumn(i, (_bstr_t)treeitem1[i], LVCFMT_LEFT,140);
		//m_list.Insert
	}
    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	NodeNum = 0;
	for (i = 0; i<zhibiaoitempoint; i++)
	{
	//	MessageBox((_bstr_t)treeitem1[i]);
		int lever1,lever2,lever3;
		int downlever;
		 
		lever1 = Ftree[i].Find((_bstr_t)"1");
		lever2 = Ftree[i].Find((_bstr_t)"2");
		lever3 = Ftree[i].Find((_bstr_t)"3");
		if (lever1 == 0)
		{
			char a = Ftree[i].GetAt(Ftree[i].GetLength() - 1);
			if (int(a) - 48 == 0)
			{
				CString s =Ftree[i].Mid(1, Ftree[i].GetLength() - 2);
				m_list.InsertItem(NodeNum, (_bstr_t)Ftree[i].Mid(1, Ftree[i].GetLength() - 3));
				NodeNum++;
			}
		}
		else if (lever2 == 0)
		{
			char a = Ftree[i].GetAt(Ftree[i].GetLength() - 1);
			if (int(a) - 48 == 0)
			{
				m_list.InsertItem(NodeNum, (_bstr_t)Ftree[i].Mid(1, Ftree[i].GetLength() - 3));
				NodeNum++;
			}
		}
		else if (lever3 == 0)
		{
			m_list.InsertItem(NodeNum, (_bstr_t)Ftree[i].Mid(1, Ftree[i].GetLength() - 1));
			NodeNum++;
		}
		//downlever = Ftree[i].Find((_bstr_t)"/");
		
		//m_list.InsertItem(0, (_bstr_t)treeitem[i]);
	}
	int j;
	
for (i = 0; i<NodeNum; i++)
	for (j = 1; j<treepoint1; j++)
		m_list.SetItemText(i,j,(_bstr_t)"˫������");
		UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control

}


void Step3dialog::shuaxinlist(void)
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


int i;
m_list.InsertColumn(0, (_bstr_t)"ָ��/�ȼ�", LVCFMT_LEFT, 140);
for (i = 1; i<treepoint1; i++)
{
	//MessageBox((_bstr_t)treeitem[i]);
	m_list.InsertColumn(i, (_bstr_t)treeitem1[i], LVCFMT_LEFT, 140);
	//m_list.Insert
}
m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
NodeNum = 0;
for (i = 0; i<zhibiaoitempoint; i++)
{
	//	MessageBox((_bstr_t)treeitem1[i]);
	int lever1, lever2, lever3;
	int downlever;

	lever1 = Ftree[i].Find((_bstr_t)"1");
	lever2 = Ftree[i].Find((_bstr_t)"2");
	lever3 = Ftree[i].Find((_bstr_t)"3");
	if (lever1 == 0)
	{
		char a = Ftree[i].GetAt(Ftree[i].GetLength() - 1);
		if (int(a) - 48 == 0)
		{
			CString s = Ftree[i].Mid(1, Ftree[i].GetLength() - 2);
			m_list.InsertItem(NodeNum, (_bstr_t)Ftree[i].Mid(1, Ftree[i].GetLength() - 3));
			NodeNum++;
		}
	}
	else if (lever2 == 0)
	{
		char a = Ftree[i].GetAt(Ftree[i].GetLength() - 1);
		if (int(a) - 48 == 0)
		{
			m_list.InsertItem(NodeNum, (_bstr_t)Ftree[i].Mid(1, Ftree[i].GetLength() - 3));
			NodeNum++;
		}
	}
	else if (lever3 == 0)
	{
		m_list.InsertItem(NodeNum, (_bstr_t)Ftree[i].Mid(1, Ftree[i].GetLength() - 1));
		NodeNum++;
	}
	//downlever = Ftree[i].Find((_bstr_t)"/");

	//m_list.InsertItem(0, (_bstr_t)treeitem[i]);
}
int j;

for (i = 0; i<NodeNum; i++)
	for (j = 1; j<treepoint1; j++)
		m_list.SetItemText(i, j, (_bstr_t)"˫������");
	// return TRUE unless you set the focus to a control


}


BOOL Step3dialog::PreTranslateMessage(MSG* pMsg)
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
	 m_ctrlTT2.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}


void Step3dialog::OnEnKillfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit.GetWindowText(shuru3);    //�õ��û�������µ����� 
	 for (int i = 0 ; i <shuru3.GetLength();i++)    
    {    
       int unicode = (int)shuru3.GetAt(i);    
	   if (unicode != '9'&&unicode !='0'&&unicode !='1'&&unicode !='2'&&unicode !='3'&&unicode !='4'&&unicode !='5'&&unicode !='6'&&unicode !='7'&&unicode !='8'&&unicode != '.')    
	   {
		   MessageBox((_bstr_t)"�����к��������Ƿ��ַ�����������ȷ��������Ϣ",(_bstr_t)"��ʾ", MB_OK ); 
			return;
	   }
    }   
    m_list.SetItemText(hang3,lie3,shuru3);   //���ñ༭���������  
    m_edit.ShowWindow(SW_HIDE);                //Ӧ�ر༭��  
}


void Step3dialog::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR; 
	 CRect rc;  
    hang3 = pNMListView->iItem;//���ѡ�е���  
    lie3 = pNMListView->iSubItem;//���ѡ����  
	if(m_list.GetItemText(hang3,lie3)=="˫������")
	m_list.SetItemText(hang3,lie3,(_bstr_t)"0");
    if   (pNMListView->iSubItem != 0) //���ѡ���������;  
    {  
        m_list.GetSubItemRect(hang3,lie3,LVIR_LABEL,rc);//��������RECT��  
        m_edit.SetParent(&m_list);//ת������Ϊ�б���е�����  
        m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;  
        m_edit.SetWindowText(m_list.GetItemText(hang3,lie3));//���������е�ֵ����Edit�ؼ��У�  
        m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���  
        m_edit.SetFocus();//����Edit����  
        m_edit.ShowCaret();//��ʾ���  
        m_edit.SetSel(-1);//������ƶ������  
		
    }  
	*pResult = 0;
}


void Step3dialog::OnBnClickedButton27()//tip
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 MessageBox((_bstr_t)"1.�����ˢ�¡�ˢ���б�;\r2.���������Excel�������б�\r3.��д�����ȱ�����ִ����һ��\r4.����д��һ���������\r5.����ΪС�����7λ",(_bstr_t)"��ʾ", MB_OK ); 
}


void Step3dialog::Lin_ExportListToExcel(CListCtrl &m_List)
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


CString Step3dialog::Lin_GetEnglishCharacter(int Num)
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


void Step3dialog::excel(void)
{
	Lin_ExportListToExcel(m_list);
}


void Step3dialog::OnBnClickedButton28()//save
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i,j,zs,xs,z=10;float xss,chu;
	float num[100],sumnum=0;num[0]=0; 
	CString input,zhengshu,xiaoshu;
	//MessageBox((_bstr_t)treepoint+(_bstr_t)"tree"+(_bstr_t)treepoint1,(_bstr_t)"����", MB_OKCANCEL ); 
	for (i = 0; i <NodeNum ; i++)
	{
		sumnum = 0;
		for (j = 1; j < treepoint1; j++)
		{	
			CString s = m_list.GetItemText(i, j);
			if (m_list.GetItemText(i, j) == "" || m_list.GetItemText(i, j) == "˫������")
			{
				MessageBox((_bstr_t)i + (_bstr_t)"Ȩ�ز���Ϊ��" + (_bstr_t)j, (_bstr_t)"����", MB_OKCANCEL);
				return;
			}
			input = m_list.GetItemText(i, j);//	MessageBox((_bstr_t)i+(_bstr_t)"input"+(_bstr_t)j,(_bstr_t)"����", MB_OKCANCEL ); 
			chu = atof(input);
			num[j] = chu;
			R[i][j] = num[j];//MessageBox((_bstr_t)input,(_bstr_t)"����", MB_OKCANCEL );
			/* sumnum+=num[j];
			 }
			 if(sumnum!=1)
			 {
			 MessageBox((_bstr_t)i+(_bstr_t)"��δ��һ�������ȹ�һ��",(_bstr_t)"����", MB_OK);
			 return;
			 }*/
		}
	}
	 Rsave=1;
	MessageBox((_bstr_t)"�ѱ���",(_bstr_t)"��ʾ", MB_OK ); 
}
