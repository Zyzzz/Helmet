// Step4dialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Helmet-FCEM.h"
#include "Step4dialog.h"
#include "afxdialogex.h"
#include  "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
extern CString  treeitem[100],treeitem1[100];
extern int treepoint,treepoint1;
extern float quanzhong[70];
extern float Two_wight[70];
extern float Three_wight[70];
extern int Two_wightNum ;
extern int Three_wightNum ;
extern int quanzhongnum;
extern float R[100][100];
extern int Rsave;
extern int Qsave;
extern int av,ov,aj,oj;
extern int zhibiaoitempoint;
// Step4dialog 对话框

IMPLEMENT_DYNAMIC(Step4dialog, CDialogEx)

Step4dialog::Step4dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(Step4dialog::IDD, pParent)
	, m_suanzi(_T(""))
{

}

Step4dialog::~Step4dialog()
{
}

void Step4dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON27, m_tip);
	DDX_Text(pDX, IDC_EDIT1, m_suanzi);
}


BEGIN_MESSAGE_MAP(Step4dialog, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &Step4dialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON27, &Step4dialog::OnBnClickedButton27)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Step4dialog 消息处理程序


void Step4dialog::OnPaint()
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


BOOL Step4dialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HBITMAP hBitmap=NULL;
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_p4);
    hBitmap =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP109 ));
	pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStatic->SetBitmap(hBitmap);  
	m_tip.LoadBitmaps(IDB_BITMAP95,IDB_BITMAP96);
	int i;
	for(i=0;i<treepoint1;i++)
	{
		m_list.InsertColumn(i, (_bstr_t)treeitem1[i], LVCFMT_LEFT,140);
	}
    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
     m_list.InsertItem(0, (_bstr_t)"");
	m_list.SetItemText(0,0,(_bstr_t)"B");
	if(av==1)//M(∧,∨)
	{
      
	   m_suanzi="主因素突出型M(∧,∨)";
	  
	}
	if(ov==1)//M(.,∨)
	{
		
		 m_suanzi="主因素突出型M(·,∨)";
		
	}
	if(aj==1)//M(∧,⊙)
	{
		 m_suanzi="加权平均型M(∧,+)";
		
	}
	if(oj==1)//M(.,⊙)
	{
		 m_suanzi="加权平均型M(·,+)";
		
	}
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control

}


void Step4dialog::OnBnClickedButton1()//jisuan
{
	// TODO: 在此添加控件通知处理程序代码
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
	for(i=0;i<treepoint1;i++)
	{
		m_list.InsertColumn(i, (_bstr_t)treeitem1[i], LVCFMT_LEFT,140);
	}
    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
     m_list.InsertItem(0, (_bstr_t)"");
	m_list.SetItemText(0,0,(_bstr_t)"B");
	if(Rsave==0)
	{
		MessageBox((_bstr_t)"未保存R，请返回第三步保存",(_bstr_t)"警告", MB_OK ); 
		return;
	}
	if(Qsave==0)
	{
		MessageBox((_bstr_t)"未保存权重，请返回第二步保存",(_bstr_t)"警告", MB_OK ); 
		return;
	}
	
	if(av==1)//M(∧,∨)
	{ 
		m_suanzi="主因素突出型M(∧,∨)";
	  UpdateData(false);
       AV();
	 
	}
	if(ov==1)//M(.,∨)
	{ 
		m_suanzi="主因素突出型M(·,∨)";
		 UpdateData(false);
		OV();
		
	}
	if(aj==1)//M(∧,⊙)
	{
		m_suanzi="加权平均型M(∧,+)";
		 UpdateData(false);
		AJ();
		
	}
	if(oj==1)//M(.,⊙)
	{ 
		m_suanzi="加权平均型M(·,+)";
		 UpdateData(false);
		OJ();
		
	}

}


void Step4dialog::AV(void)//
{
	int row = 0;
	float leve3; 
	float smallnum[100],bignum[100];
	int wightpos = 0;
	float **lever3arry;	
	int lever3resultpos = 0;
	float **lever3result = new float*[30];
	for (int j = 0; j < 30; j++)
	{
		lever3result[j] = new float[treepoint1 + 1];
	}
	for (int i = 0; i < zhibiaoitempoint; i++)
	{
		int lever1, lever2, lever3;
	
		lever1 = Ftree[i].Find((_bstr_t)"1");
		lever2 = Ftree[i].Find((_bstr_t)"2");
		lever3 = Ftree[i].Find((_bstr_t)"3");
		if (lever1 == 0)
		{
			char a = Ftree[i].GetAt(Ftree[i].GetLength() - 1);
			if (int(a) - 48 == 0)
			{
				row++;
			}
		}
		else if (lever2 == 0)
		{
			char a = Ftree[i].GetAt(Ftree[i].GetLength() - 1);
			if (int(a) - 48 == 0)
			{
				row++;
			}
		}
		else if (lever3 == 0)
		{
			int rowsum;
			char a = Ftree[i-1].GetAt(Ftree[i-1].GetLength() - 1);
			rowsum = a - 48;
			float **lever3arry;
			lever3arry = new float*[rowsum];
			for (int j = 0; j < rowsum; j++)
			{
				lever3arry[j] = new float[treepoint1+1];
			}
			for (int j = 0; j < rowsum; j++)
			{
				for (int k = 1; k < treepoint1; k++)
				{
					lever3arry[j][k] = R[pj+row][k];
				}
			}
			for (int j = 0; j < rowsum ; j++)
			{
				wightpos++;
				for (int k = 1; k < treepoint1; k++)
				{
					lever3arry[j][k] = min(Three_wight[wightpos], lever3arry[j][k]);
				}
			}               

			for (int j = 1; j < treepoint1; j++)
			{
				//wightpos++;
				float max = -10000000;
				for (int k = 0; k <rowsum ; k++)
				{
					if (max<lever3arry[k][j])
						max = lever3arry[k][j];
				}
				lever3result[lever3resultpos][j] = max;
			}
			lever3resultpos++;
			i =i+ rowsum-1;
			row = row + rowsum;
			for (int i = 0; i<rowsum; i++)
			{
				delete[] lever3arry[i]; //先撤销指针元素所指向的数组
			}
			delete[] lever3arry;
		}
	}
 //    //权重A是和treepoint一样 是行
	////R 要用列 【j】
	//for(j=1;j<treepoint1;j++)//lie
 //   {
	//	
	//for(i=0;i<treepoint-1;i++)//hang
	//{
	//	
	//
	//  if( quanzhong[i]<R[i][j])
	//  {
	//	  smallnum[i]=quanzhong[i];
	//  
	//  }
	//  else
	//  {
	//	   smallnum[i]=R[i][j];
	//  }
	//	//MessageBox((_bstr_t)quanzhong[i]+"权重",(_bstr_t)"警告", MB_OKCANCEL ); 
	//  
	//  // MessageBox((_bstr_t)R[i][j],(_bstr_t)"警告", MB_OKCANCEL );
	//}
	//bignum[j]=smallnum[0];
	//for(i=1;i<treepoint-1;i++)//hang
	//{
	//	if( bignum[j]<smallnum[i])
	//  {
	//	 bignum[j]=smallnum[i];
	//  }
	//}
	//if(0<bignum[j]<1)
	//m_list.SetItemText(0,j,(_bstr_t)"0"+(_bstr_t)bignum[j]);
	//else
	//	m_list.SetItemText(0,j,(_bstr_t)bignum[j]);
	//}
}


void Step4dialog::OV(void)//M(.,∨)
{
	int i,j,k;
	float smallnum[100],bignum[100];
     //权重A是和treepoint一样 是行
	//R 要用列 【j】

	for(j=1;j<treepoint1;j++)//lie
    {
		
	for(i=0;i<treepoint-1;i++)//hang
	{
		  smallnum[i]=quanzhong[i]*R[i][j];	
            smallnum[i]=((int)( smallnum[i] * 1000000.0 + 0.5)) / 1000000.0;// smallnum[i]= ((float)((int)(smallnum[i]*1000.0+5)/10))/100.0;
	}
	bignum[j]=smallnum[0];
	for(i=1;i<treepoint-1;i++)//hang
	{
		if( bignum[j]<smallnum[i])
	  {
		 bignum[j]=smallnum[i];
	  }
	}
	if(0<bignum[j]<1)
	m_list.SetItemText(0,j,(_bstr_t)"0"+(_bstr_t)bignum[j]);
	else
		m_list.SetItemText(0,j,(_bstr_t)bignum[j]);
	}
}


void Step4dialog::AJ(void)
{
		int i,j,k;
	float smallnum[100],bignum[100];
     //权重A是和treepoint一样 是行
	//R 要用列 【j】
	for(j=1;j<treepoint1;j++)//lie
    {
		
	for(i=0;i<treepoint-1;i++)//hang
	{
		
	
	  if( quanzhong[i]<R[i][j])
	  {
		  smallnum[i]=quanzhong[i];
	  
	  }
	  else
	  {
		   smallnum[i]=R[i][j];
	  }
	}
	bignum[j]=0;
	for(i=0;i<treepoint-1;i++)//hang
	{
	
		 bignum[j]+=smallnum[i];
		// bignum[i]=((int)( bignum[i] * 1000000.0 + 0.5)) / 1000000.0;MessageBox((_bstr_t)bignum[j]+"big"+(_bstr_t)smallnum[i],(_bstr_t)"警告", MB_OKCANCEL ); 
	}
		if(0<bignum[j]<1)
	m_list.SetItemText(0,j,(_bstr_t)"0"+(_bstr_t)bignum[j]);
	else
		m_list.SetItemText(0,j,(_bstr_t)bignum[j]);
	}
}


void Step4dialog::OJ(void)
{
		int i,j,k;
	float smallnum[100],bignum[100];
     //权重A是和treepoint一样 是行
	//R 要用列 【j】
	for(j=1;j<treepoint1;j++)//lie
    {
		
	for(i=0;i<treepoint-1;i++)//hang
	{
		
	
	  smallnum[i]=quanzhong[i]*R[i][j];	
        //    smallnum[i]=((int)( smallnum[i] * 1000000.0 + 0.5)) / 1000000.0;
	}
	bignum[j]=0;
	for(i=0;i<treepoint-1;i++)//hang
	{
			 bignum[j]+=smallnum[i];//bignum[i]=((int)( bignum[i] * 1000000.0 + 0.5)) / 1000000.0;MessageBox((_bstr_t)bignum[j]+"big"+(_bstr_t)smallnum[i],(_bstr_t)"警告", MB_OKCANCEL );	
	}
		if(0<bignum[j]<1)
	m_list.SetItemText(0,j,(_bstr_t)"0"+(_bstr_t)bignum[j]);
	else
		m_list.SetItemText(0,j,(_bstr_t)bignum[j]);
	}
}


void Step4dialog::Lin_ExportListToExcel(CListCtrl &m_List)
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
		
		MessageBox((_bstr_t)"没有安装Excel无法导出Excel",(_bstr_t)"警告", MB_OKCANCEL ); 
		return;
	}
	books=app.get_Workbooks();
	book=books.Add(covOptional);
	sheets=book.get_Sheets();
	sheet=sheets.get_Item(COleVariant((short)1));
	//写入表头//
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
	//获取单元格的位置//
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


CString Step4dialog::Lin_GetEnglishCharacter(int Num)
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


void Step4dialog::excel(void)
{
		Lin_ExportListToExcel(m_list);
}


void Step4dialog::OnBnClickedButton27()//提示
{
	// TODO: 在此添加控件通知处理程序代码
	 MessageBox((_bstr_t)"1.点击“刷新”刷新列表;\r2.点击“导出Excel”导出列表\r3.精度为小数点后5位",(_bstr_t)"提示", MB_OK ); 
}


HBRUSH Step4dialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	   if (pWnd->GetDlgCtrlID() == IDC_STATIC)
        {
             pDC->SetTextColor(RGB(0,0,0)); //设置字体颜色
             pDC->SetBkMode(TRANSPARENT);
             return CreateSolidBrush(RGB(255,255,255));
}
	    if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
        {
             pDC->SetTextColor(RGB(0,0,0)); //设置字体颜色
             pDC->SetBkMode(TRANSPARENT);
             return CreateSolidBrush(RGB(255,255,255));
}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void Step4dialog::shuaxin(void)
{
	OnBnClickedButton1();
}
