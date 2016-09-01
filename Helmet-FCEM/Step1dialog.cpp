// Step1dialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Helmet-FCEM.h"
#include "Step1dialog.h"
#include "afxdialogex.h"
#include <locale>
#include "zhibiao.h"
CToolTipCtrl  m_ctrlTT11;
//***************************记录树的所有节点，用于分级赋权
int Ftreenum=1;
CString Ftree[200];
int treesave=0;

extern CString zhibiaoxx[57];//57项评价指标（记录勾选的项目） 继承自zhibiao.cpp
//**************************一些标记
extern int cancle;
extern CString delbutton;
int clicktreex=0,delclick=0,addclick=0,renamecheck=0;

HTREEITEM hroot,delitem=NULL,h1,hroot1,delitem1=NULL,h2,reitem=NULL,reitem1=NULL,yijiitem,erjiitem,sanjiitem;
//int  itemchild;
CString itemname,itemnumber,itemoldname;//指标树
CString itemname1,itemnumber1,itemoldname1;//评价树
//****************************************保存用指标树的节点
int position;
 CString  zhibiaoitem[100][2];//第一步指标树的所有节点 [0]编号(用于分三级，并知道谁与谁是一级)  [1]内容
 int zhibiaoitemchilds[100];//第一步指标树的每个节点有多少子节点
 int zhibiaoitempoint=0;//第一步指标树一共有多少节点（指标）
 int  itemchildpoint=0;//
//*******************************************评语树
extern CString  treeitem1[100];//用于存放第一步的评语树的所有节点内容
extern int treepoint1;
//*********************************************8打开文件
extern CString openitem[200];//打开的txt文件的内容
extern int openpoint;//打开文件内容的总个数
extern int openitemnum[200];//每个对应的子项个数
CImageList m_imagelist,m_imagelist1;//定义图像列表
// Step1dialog 对话框

IMPLEMENT_DYNAMIC(Step1dialog, CDialogEx)

Step1dialog::Step1dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(Step1dialog::IDD, pParent)
{

}

Step1dialog::~Step1dialog()
{
}

void Step1dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctltree);

	DDX_Control(pDX, IDC_TREE2, m_ctltree1);
	DDX_Control(pDX, IDC_BUTTON28, m_save);
	DDX_Control(pDX, IDC_BUTTON27, m_tip);
}


BEGIN_MESSAGE_MAP(Step1dialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &Step1dialog::OnBnClickedOk)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &Step1dialog::OnNMClickTree1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &Step1dialog::OnTvnEndlabeleditTree1)
//	ON_COMMAND(ID_rename, &Step1dialog::OnRename)
	ON_COMMAND(ID_del, &Step1dialog::OnDel)
//	ON_COMMAND(ID_add, &Step1dialog::OnAdd)
	ON_NOTIFY(NM_RDBLCLK, IDC_TREE1, &Step1dialog::OnNMRDblclkTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &Step1dialog::OnNMRClickTree1)

	ON_BN_CLICKED(IDC_BUTTON2, &Step1dialog::OnBnClickedButton2)
	ON_COMMAND(ID_rename, &Step1dialog::OnRename)
	ON_COMMAND(ID_add, &Step1dialog::OnAdd)
	ON_NOTIFY(NM_RCLICK, IDC_TREE2, &Step1dialog::OnNMRClickTree2)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE2, &Step1dialog::OnTvnEndlabeleditTree2)
	ON_NOTIFY(NM_CLICK, IDC_TREE2, &Step1dialog::OnNMClickTree2)
	ON_COMMAND(ID_YijiAddErji, &Step1dialog::OnYijiadderji)
	ON_COMMAND(ID_ErjiAddSanji, &Step1dialog::OnErjiaddsanji)
	ON_COMMAND(ID_DelErji, &Step1dialog::OnDelerji)
	ON_COMMAND(ID_DelSanji, &Step1dialog::OnDelsanji)
	ON_COMMAND(ID_RenameErji, &Step1dialog::OnRenameerji)
	ON_COMMAND(ID_RenameSanji, &Step1dialog::OnRenamesanji)
	ON_COMMAND(ID_tree2add, &Step1dialog::OnTree2add)
	ON_COMMAND(ID_tree2del, &Step1dialog::OnTree2del)
	ON_COMMAND(ID_tree2rename, &Step1dialog::OnTree2rename)
	ON_BN_CLICKED(IDC_BUTTON1, &Step1dialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON28, &Step1dialog::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON27, &Step1dialog::OnBnClickedButton27)
END_MESSAGE_MAP()


// Step1dialog 消息处理程序


void Step1dialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

}


BOOL Step1dialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HBITMAP hBitmap=NULL;
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_p1);
    hBitmap =::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP75 ));
	pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);   
    pStatic->SetBitmap(hBitmap);
	m_tip.LoadBitmaps(IDB_BITMAP95,IDB_BITMAP96);
	m_save.LoadBitmaps(IDB_BITMAP97,IDB_BITMAP98);
	 EnableToolTips(TRUE);//enable use it
   m_ctrlTT11.Create(this);
   m_ctrlTT11.Activate(TRUE);
   m_ctrlTT11.SetTipTextColor(RGB(0,0,0));//font color
 
   //IDC_TEST为你想添加提示的控件IDC，"hello为想添加的提示语句"
   m_ctrlTT11.AddTool(GetDlgItem(IDC_BUTTON27),(_bstr_t)"提示");
   m_ctrlTT11.AddTool(GetDlgItem(IDC_BUTTON28),(_bstr_t)"保存模型信息");
	//*********************************8
	//指标树
	//***********************************
	m_imagelist.Create(16,16,ILC_COLOR,2,2);//建立图像列表，分别代表像素，颜色，图片列数，最大图片列数
	CBitmap bm;//位图封装容器
	bm.LoadBitmap(IDB_BITMAP67);//载入Bitmap资源
	m_imagelist.Add(&bm,RGB(0,0,0));//添加到图像列表
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP66);
	m_imagelist.Add(&bm,RGB(0,0,0));
	m_ctltree.SetImageList(&m_imagelist,LVSIL_NORMAL);//为树形控件添加图像列表
	
	//*********************************插入节点
	hroot=m_ctltree.InsertItem((_bstr_t)"评价指标(U)",1,0,TVI_ROOT);
	zhibiaoitem[zhibiaoitempoint][0]="0";zhibiaoitem[zhibiaoitempoint][1]="评价指标(U)";zhibiaoitemchilds[zhibiaoitempoint]=0;zhibiaoitempoint++;
	 h1=m_ctltree.InsertItem((_bstr_t)"指标",1,0,hroot);//添加二级节点
	 //************************************************************************************
	 //找到要插入节点的位置给他的子项目数加一并因此判断此节点的编号应该是多少
	  itemname=m_ctltree.GetItemText(hroot);
	  //遍历数得到位置
	  int check=0;//找到标记
	  int childs=0;//记录子节点数
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//找到
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //插入新节点
	  CString str;
	  str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]="指标";
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
	m_ctltree.SetBkColor(RGB(255,255,255));//设置树形控件的背景色
	m_ctltree.SetTextColor(RGB(0,0,0));//设置文本背景色
	m_ctltree.Select(h1,TVGN_CARET);
	//**************************************8
	//评价树
	m_imagelist1.Create(16,16,ILC_COLOR,2,2);//建立图像列表，分别代表像素，颜色，图片列数，最大图片列数
	CBitmap bm1;//位图封装容器
	bm1.LoadBitmap(IDB_BITMAP67);//载入Bitmap资源
	m_imagelist1.Add(&bm1,RGB(0,0,0));//添加到图像列表
	bm1.DeleteObject();
	bm1.LoadBitmap(IDB_BITMAP66);
	m_imagelist1.Add(&bm1,RGB(0,0,0));
	m_ctltree1.SetImageList(&m_imagelist1,LVSIL_NORMAL);//为树形控件添加图像列表
	hroot1=m_ctltree1.InsertItem((_bstr_t)"评语(V)",1,0,TVI_ROOT);//添加一级节点
	treeitem1[treepoint1]="评语(V)";treepoint1++;
	 h2=m_ctltree1.InsertItem((_bstr_t)"评语",1,0,hroot1);//添加二级节点
	treeitem1[treepoint1]="评语"; treepoint1++;	
	m_ctltree1.SetBkColor(RGB(255,255,255));//设置树形控件的背景色
	m_ctltree1.SetTextColor(RGB(0,0,0));//设置文本背景色
	m_ctltree1.Select(h2,TVGN_CARET);

	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void Step1dialog::OnPaint()
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

void Step1dialog::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)//点击选中的树
{
	// TODO: 在此添加控件通知处理程序代码
	addclick=1;//点击可能要添加节点
	delclick=1;//点击可能要删除节点
	renamecheck=1;//点击可能要重命名节点
	CPoint point;
	GetCursorPos(&point); // 当前鼠标坐标
	CPoint PointInTree = point;
	m_ctltree.ScreenToClient( &PointInTree);
	CMenu menu;
	CMenu *ptrMenu;
	UINT nFlag = TVHT_ONITEM; // 当在 Item 上右击时
	delitem =m_ctltree.HitTest( PointInTree, &nFlag );//
	reitem=m_ctltree.HitTest( PointInTree, &nFlag );
	*pResult = 0;
}


void Step1dialog::OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	CString strText;
	m_ctltree.GetEditControl()->GetWindowText(strText.GetBuffer(200),200);
	int havecheck=0;
	for(position=0;position<zhibiaoitempoint;position++)
	{
		  if(zhibiaoitem[position][1]==strText)
		  {
			  havecheck=1;
			  break;
		  }
	}
	if(havecheck==1)//
	{
		  MessageBox((_bstr_t)"已经有名为"+strText+"的节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}
	m_ctltree.SetItemText(m_ctltree.GetSelectedItem(),strText);//设置编辑后的文本为结点
	for(position=0;position<zhibiaoitempoint;position++)
	{
		if(zhibiaoitem[position][1]==itemoldname)
			  break;
	}
	zhibiaoitem[position][1]=strText;
	*pResult = 0;
}

void Step1dialog::OnDel()
{
	// TODO: 在此添加命令处理程序代码
	UpdateData(true);
	if(clicktreex==1)
	{
	if(hroot==m_ctltree.GetSelectedItem())
	{
		MessageBox((_bstr_t)"根节点无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
		return;
	}
	//找有没有子节点
	CString item;
    CString fatheritem,childitem;
    int len,delitempos,biao=0,biao1=0,childs;
	
	for(position=0;position<zhibiaoitempoint;position++)//找在数组中的位置
	 {
		  if(zhibiaoitem[position][1]== m_ctltree.GetItemText(m_ctltree.GetSelectedItem()))
			 {
				 biao=1;
				 break;
		  }
	 }

	  if(biao==1)//
	  {
		   delitempos=position;
		   childs=zhibiaoitemchilds[position];//子节点个数
		   item=zhibiaoitem[position][0];
		  
	  }
	  if(childs!=0)
	  {
		  MessageBox((_bstr_t)"该指标存在低级指标无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	  }
	   //找到父节点的个数减1
	  len=item.GetLength();  //获取当前行的值的长度；
	  fatheritem=item.Mid(0,len-1);
	    
	  for(position=0;position<zhibiaoitempoint;position++)
	   {
		   if(zhibiaoitem[position][0]== fatheritem)
		   {
			   biao1=1;
			  break;
		   }
	    }
		//	MessageBox((_bstr_t)treeitem[position][1]);
	   if(biao1==1)//
	   {
		   childs=zhibiaoitemchilds[position];//子节点个数
		   zhibiaoitemchilds[position]=childs-1;
	    }
		int pos;
		for(pos=delitempos;pos<zhibiaoitempoint;pos++)
	    {
		    zhibiaoitem[pos][0]= zhibiaoitem[pos+1][0];
			zhibiaoitem[pos][1]= zhibiaoitem[pos+1][1];
			zhibiaoitemchilds[pos]=zhibiaoitemchilds[pos+1];
	    }
		zhibiaoitempoint--;
        m_ctltree.DeleteItem(m_ctltree.GetSelectedItem());//删除活动的结
	}
	//**************************************
	if(clicktreex==2)
	{
	if(hroot1==m_ctltree1.GetSelectedItem())
	{
		MessageBox((_bstr_t)"根节点无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
		return;
	}
	CString item;
    int len,delitempos;	
    for(position=0;position<treepoint1;position++)//找在数组中的位置
	 {
		  if(treeitem1[position]== m_ctltree1.GetItemText(m_ctltree1.GetSelectedItem()))
			 {
				 delitempos=position;
				 break;
		  }
	 }
   
		int pos;
		for(pos=delitempos;pos<treepoint1;pos++)
	    {
		    treeitem1[pos]= treeitem1[pos+1];
		
	    }
		treepoint1--;
        m_ctltree1.DeleteItem(m_ctltree1.GetSelectedItem());//删除活动的结点
	}
}



void Step1dialog::OnNMRDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void Step1dialog::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	clicktreex=1;//单击的树2
	CPoint point;
	GetCursorPos(&point); // 当前鼠标坐标
	CPoint PointInTree = point;
	m_ctltree.ScreenToClient( &PointInTree);
	CMenu menu,menu2;
	CMenu *ptrMenu,*ptrMenu2,*ptrMenu3;
	CBitmap m_bitmap1,m_bitmap2,m_bitmap3;
	m_bitmap1.LoadBitmap(IDB_BITMAP70);
	m_bitmap2.LoadBitmap(IDB_BITMAP71);
	m_bitmap3.LoadBitmap(IDB_BITMAP72);
	HTREEITEM Item;
	UINT nFlag = TVHT_ONITEM; // 当在 Item 上右击时
	Item =m_ctltree.HitTest( PointInTree, &nFlag );
	CString roadname = m_ctltree.GetItemText(Item);
	int nLength = roadname.GetLength(); 
	CString b=roadname.Right(3);
	if ( Item != NULL&&Item==hroot)//总根节点 可以新建一级节点
	{ 
		m_ctltree.SelectItem(Item);	
		menu2.LoadMenu(IDR_MENU2);	
	    ptrMenu2=menu2.GetSubMenu(0);
		ptrMenu2->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bitmap1,&m_bitmap1);
		ptrMenu2->TrackPopupMenu
		(
		TPM_LEFTALIGN|TPM_RIGHTBUTTON,
		point.x,
		point.y,
		this,
		NULL);	

	}
   if( Item != NULL&&m_ctltree.GetParentItem(Item)==hroot)//一级节点 可以新建二级节点
	{
		m_ctltree.SelectItem(Item);	
		menu.LoadMenu(IDR_MENU1);	
	    ptrMenu=menu.GetSubMenu(0);
		ptrMenu->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bitmap1,&m_bitmap1);
		ptrMenu->SetMenuItemBitmaps(1,MF_BYPOSITION,&m_bitmap2,&m_bitmap2);
		ptrMenu->SetMenuItemBitmaps(2,MF_BYPOSITION,&m_bitmap3,&m_bitmap3);
	    ptrMenu->TrackPopupMenu
		(
		TPM_LEFTALIGN|TPM_RIGHTBUTTON,
		point.x,
		point.y,
		this,
		NULL);	
	}
    if( Item != NULL&&m_ctltree.GetParentItem(m_ctltree.GetParentItem(Item))==hroot)//二级节点 可以新建三级节点
	{
		m_ctltree.SelectItem(Item);	
		menu.LoadMenu(IDR_MENU4);	
	    ptrMenu3=menu.GetSubMenu(0);
		ptrMenu3->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bitmap1,&m_bitmap1);
		ptrMenu3->SetMenuItemBitmaps(1,MF_BYPOSITION,&m_bitmap2,&m_bitmap2);
		ptrMenu3->SetMenuItemBitmaps(2,MF_BYPOSITION,&m_bitmap3,&m_bitmap3);
	    ptrMenu3->TrackPopupMenu
		(
		TPM_LEFTALIGN|TPM_RIGHTBUTTON,
		point.x,
		point.y,
		this,
		NULL);	
	}
	 if( Item != NULL&&m_ctltree.GetParentItem(m_ctltree.GetParentItem(m_ctltree.GetParentItem(Item)))==hroot)//三级节点
	{
		m_ctltree.SelectItem(Item);	
		menu.LoadMenu(IDR_MENU5);	
	    ptrMenu3=menu.GetSubMenu(0);
		ptrMenu3->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bitmap2,&m_bitmap2);
		ptrMenu3->SetMenuItemBitmaps(1,MF_BYPOSITION,&m_bitmap3,&m_bitmap3);
	    ptrMenu3->TrackPopupMenu
		(
		TPM_LEFTALIGN|TPM_RIGHTBUTTON,
		point.x,
		point.y,
		this,
		NULL);	
	}
	*pResult = 0;
}

void Step1dialog::OnBnClickedButton2()//保存
{
	// TODO: 在此添加控件通知处理程序代码
	//保存树
	int i,j,k,treenum=1,yiji=0,erji=0,sanji=0,m,n,b;
	CString tree[200],str;
		if(m_ctltree.ItemHasChildren(hroot))//判断结点是否有子结点
			{
				
				tree[0]=m_ctltree.GetItemText(hroot);
				//找此根节点对应有多少一级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==tree[0])
		                        {
									b= zhibiaoitemchilds[position];
			                          break;
		                         }
							}
							str.Format("%d",b);
							tree[0]=tree[0]+"/"+str;
			
				for(i=0;i<b-1;i++)//
	            {
                   if(yiji==0)
				   {
                   yijiitem=m_ctltree.GetChildItem(hroot); //获取第一个子结点
				   tree[treenum]=m_ctltree.GetItemText(yijiitem);
				   //找此一级节点对应有多少二级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==tree[treenum])
		                        {
									n= zhibiaoitemchilds[position];
			                          break;
		                         }
							}
					str.Format("%d",n);
					tree[treenum]=tree[treenum]+"/"+str;treenum++;
				   //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&2ji
				   for(j=0;j<n-1;j++)//第二个子节点
				   {
					   if(erji==0)
					   {
					    erjiitem=m_ctltree.GetChildItem(yijiitem);
					    tree[treenum]=m_ctltree.GetItemText(erjiitem);

						//找此二级节点对应有多少三级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==tree[treenum])
		                        {
									m= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",m);
					     tree[treenum]=tree[treenum]+"/"+str;treenum++;
						//*****************************************************3ji
						  for(k=0;k<m-1;k++)//第三个子节点
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//获取下一个兄弟结点结点
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;//MessageBox((_bstr_t)tree[treenum]+"0");treenum++;
							
							}
				         }
						  sanji=0;
						  
						  erji=1;
						  //******************************************************
					   }
					     if(erji==1)
					   {
					    erjiitem=m_ctltree.GetNextSiblingItem(erjiitem);
					    tree[treenum]=m_ctltree.GetItemText(erjiitem);//MessageBox( tree[treenum]);treenum++;
						//找此二级节点对应有多少三级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==tree[treenum])
		                        {
									m= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",m);
					     tree[treenum]=tree[treenum]+"/"+str;treenum++;
						//*****************************************************3ji
						  for(k=0;k<m-1;k++)//第三个子节点
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//获取下一个兄弟结点结点
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;//MessageBox((_bstr_t)tree[treenum]+"1");treenum++;
						
							}
				         }
						  sanji=0;
						  
						  //******************************************************
					   }
				   }
				   erji=0;
				  
				   yiji=1;
				   //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
				   }
//********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&(((((((((((((((((((((((9
				   if(yiji==1)
				   {
                  yijiitem=m_ctltree.GetNextSiblingItem(yijiitem);
				   tree[treenum]=m_ctltree.GetItemText(yijiitem);
				   //找此一级节点对应有多少二级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==tree[treenum])
		                        {
									n= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",n);
					tree[treenum]=tree[treenum]+"/"+str;treenum++;
				   //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&2ji
				   for(j=0;j<n-1;j++)//第二个子节点
				   {
					   if(erji==0)
					   {
					    erjiitem=m_ctltree.GetChildItem(yijiitem);
					    tree[treenum]=m_ctltree.GetItemText(erjiitem);
						//找此二级节点对应有多少三级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==tree[treenum])
		                        {
									m= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",m);
					     tree[treenum]=tree[treenum]+"/"+str;treenum++;
						//*****************************************************3ji
						  for(k=0;k<m-1;k++)//第三个子节点
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//获取下一个兄弟结点结点
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
							
							}
				         }
						  sanji=0;
					
						  erji=1;
						  //******************************************************
					   }
					     if(erji==1)
					   {
					    erjiitem=m_ctltree.GetNextSiblingItem(erjiitem);
					    tree[treenum]=m_ctltree.GetItemText(erjiitem);
						//找此二级节点对应有多少三级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==tree[treenum])
		                        {
									m= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",m);
					     tree[treenum]=tree[treenum]+"/"+str;treenum++;
						//*****************************************************3ji
						  for(k=0;k<m-1;k++)//第三个子节点
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//获取下一个兄弟结点结点
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
						
							}
				         }
						  sanji=0;
						  
						  //******************************************************
					   }
				   }
				   erji=0;
				   yiji=1;
				   //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
				   }

				}
		}
		
	UpdateData(true);
	// TODO: 在此添加控件通知处理程序代码
	b=treepoint1-1;
	CString szFileFilter=(_bstr_t)"文本(*.txt)|*.txt|";
	CString szFileExt=(_bstr_t)"txt";//扩展名为txt
	CFileDialog dlg(false,szFileExt,NULL,OFN_HIDEREADONLY,szFileFilter);
	if(dlg.DoModal()==IDOK)
	{
		CStdioFile File;		
		File.Open(dlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
		char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
        setlocale( LC_CTYPE, "chs" );//设定
		for(position=0;position<treenum;position++)
	    {
			File.WriteString((_bstr_t)tree[position]+(_bstr_t)"\r\n");//正常写入	
	    }
		File.WriteString((_bstr_t)treeitem1[0]+(_bstr_t)"/"+(_bstr_t)b+(_bstr_t)"\r\n");
		for(position=1;position<treepoint1;position++)
	    {
		  File.WriteString((_bstr_t)treeitem1[position]+(_bstr_t)"\r\n");//正常写入	
	    }

        File.WriteString((_bstr_t)"Finish");
        setlocale( LC_CTYPE, old_locale );
        free( old_locale );//还原区域设定
		File.Close();
	}
}


void Step1dialog::deltreeitem()
{
	//MessageBox((_bstr_t)m_ctltree.GetItemText(delitem));
	//UpdateData(true);
	if(delitem1==NULL&&delitem==NULL)
	{
		MessageBox((_bstr_t)"未选中节点无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}
	if(delclick==1)
	{
	
	if(hroot==delitem)
	{
		MessageBox((_bstr_t)"根节点无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}
//找有没有子节点
	CString item;
    CString fatheritem,childitem;
    int len,delitempos,biao=0,biao1=0,childs;
	
	for(position=0;position<zhibiaoitempoint;position++)//找在数组中的位置
	 {
		  if(zhibiaoitem[position][1]== m_ctltree.GetItemText(m_ctltree.GetSelectedItem()))
			 {
				 biao=1;
				 break;
		  }
	 }

	  if(biao==1)//
	  {
		   delitempos=position;
		   childs=zhibiaoitemchilds[position];//子节点个数
		   item=zhibiaoitem[position][0];
		  
	  }
	  if(childs!=0)
	  {
		  MessageBox((_bstr_t)"该指标存在低级指标无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	  }
	   //找到父节点的个数减1
	  len=item.GetLength();  //获取当前行的值的长度；
	  fatheritem=item.Mid(0,len-1);
	    
	  for(position=0;position<zhibiaoitempoint;position++)
	   {
		   if(zhibiaoitem[position][0]== fatheritem)
		   {
			   biao1=1;
			  break;
		   }
	    }
		//	MessageBox((_bstr_t)treeitem[position][1]);
	   if(biao1==1)//
	   {
		   childs=zhibiaoitemchilds[position];//子节点个数
		   zhibiaoitemchilds[position]=childs-1;
	    }
		int pos;
		for(pos=delitempos;pos<zhibiaoitempoint;pos++)
	    {
		    zhibiaoitem[pos][0]= zhibiaoitem[pos+1][0];
			zhibiaoitem[pos][1]= zhibiaoitem[pos+1][1];
			zhibiaoitemchilds[pos]=zhibiaoitemchilds[pos+1];
	    }
		zhibiaoitempoint--;
        m_ctltree.DeleteItem(m_ctltree.GetSelectedItem());//删除活动的结
    delitem=NULL;
	}

	//*******************************************8
	if(delclick==2)
	{
	
	if(hroot1==delitem1)
	{
		MessageBox((_bstr_t)"根节点无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}

	CString item;
    int len,delitempos;	
    for(position=0;position<treepoint1;position++)//找在数组中的位置
	 {
		  if(treeitem1[position]== m_ctltree1.GetItemText(m_ctltree1.GetSelectedItem()))
			 {
				 delitempos=position;
				 break;
		  }
	 }
   
		int pos;
		//if(delitempos==1)
		for(pos=delitempos;pos<treepoint1;pos++)
	    {

		    treeitem1[pos]= treeitem1[pos+1];
		
	    }
		treepoint1--;
    
	m_ctltree1.DeleteItem(delitem1);//删除活动的结点
    delitem1=NULL;
	}
}



void Step1dialog::updatatree(void)
{
	int i,j,k,m,n,b;
	 CString str,str1,str2;
	 /* for(i=0;i<treepoint;i++)
			{
				MessageBox((_bstr_t)treeitem[i][0]);
				MessageBox((_bstr_t)treeitem[i][1]);
				MessageBox((_bstr_t)itemchilds[i]);
			}
			*/
	
	//删除原树1
	 HTREEITEM   hItem;
	while(m_ctltree.ItemHasChildren(hroot) )
	{
	     hItem=m_ctltree.GetChildItem(hroot); //获取第一个子结点
		 m_ctltree.DeleteItem(hItem);//删除活动的结点
	}
	//根据数组建树
	zhibiaoitempoint=0;
	zhibiaoitem[zhibiaoitempoint][0]="0";zhibiaoitem[zhibiaoitempoint][1]="评价指标(U)";zhibiaoitemchilds[zhibiaoitempoint]=0;zhibiaoitempoint++;
	HTREEITEM hNew,hnew1,hnew2,hnew3;
	int point=1;
	for(i=0;i<openitemnum[0];i++)
	{
		//****************************************
		 //找到要插入节点的位置给他的子项目数加一并因此判断此节点的编号应该是多少
	  itemname=openitem[0];
	  //遍历数得到位置
	  int check=0;//找到标记
	  int childs=0;//记录子节点数
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//找到
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //插入新节点
	 
	  str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]=openitem[point];
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
	    //******************************************
		 hnew1= m_ctltree.InsertItem((_bstr_t)openitem[point],1,0,hroot);//一级节点
		 n=openitemnum[point];str1=openitem[point];point++;
		for(j=0;j<n;j++)
		            {//MessageBox((_bstr_t)"2"+(_bstr_t)openitem[point]+(_bstr_t)n);
							//****************************************
		 //找到要插入节点的位置给他的子项目数加一并因此判断此节点的编号应该是多少
	  itemname=str1;
	  //遍历数得到位置
	  int check=0;//找到标记
	  int childs=0;//记录子节点数
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//找到
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //插入新节点
	  str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]=openitem[point];
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
	    //******************************************
					    hnew2= m_ctltree.InsertItem((_bstr_t)openitem[point],1,0,hnew1);
						m=openitemnum[point];str2=openitem[point];point++;//MessageBox("m"+(_bstr_t)openitem[point]+(_bstr_t)m);	
						for(k=0;k<m;k++)
		                {				//MessageBox("3"+(_bstr_t)openitem[point]+(_bstr_t)m);	
								//****************************************
		 //找到要插入节点的位置给他的子项目数加一并因此判断此节点的编号应该是多少
	  itemname=str2;
	  //遍历数得到位置
	  int check=0;//找到标记
	  int childs=0;//记录子节点数
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//找到
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //插入新节点
	  str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]=openitem[point];
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
	    //******************************************
							  hnew3= m_ctltree.InsertItem((_bstr_t)openitem[point],1,0,hnew2);point++;	
							
						}
		            }
		
	}
	
	//删除原树2
	 HTREEITEM   hItem1;
	while(m_ctltree1.ItemHasChildren(hroot1) )
	{
	     hItem1=m_ctltree1.GetChildItem(hroot1); //获取第一个子结点
		 m_ctltree1.DeleteItem(hItem1);//删除活动的结点
	}
	//根据数组建树
	for(i=1;i<treepoint1;i++)
	{
		HTREEITEM hNew= m_ctltree1.InsertItem((_bstr_t)treeitem1[i],1,0,hroot1);
	}
	
}


void Step1dialog::OnRename()
{
	// TODO: 在此添加命令处理程序代码
	 UpdateData(true);	 
	 if(clicktreex==1)
	 {
       m_ctltree.ModifyStyle(NULL,TVS_EDITLABELS);      //设置编辑风格
	   HTREEITEM hItem=m_ctltree.GetSelectedItem();
	   itemoldname=m_ctltree.GetItemText(hItem);
       m_ctltree.EditLabel(hItem);
	   return;
	 }
	  if(clicktreex==2)
	 {
       m_ctltree1.ModifyStyle(NULL,TVS_EDITLABELS);      //设置编辑风格
	   HTREEITEM hItem=m_ctltree1.GetSelectedItem();
	   itemoldname=m_ctltree1.GetItemText(hItem);
       m_ctltree1.EditLabel(hItem);
	   return;
	 }
}


void Step1dialog::OnAdd()//根节点增加一级节点
{
	// TODO: 在此添加命令处理程序代码
	 UpdateData(true);
	 if(clicktreex==1)//树1
	 {
		 int havecheck=0;
	 for(position=0;position<zhibiaoitempoint;position++)
	 {
		  if(zhibiaoitem[position][1]=="xxxxx")
		  {
			  havecheck=1;
			  break;
		  }
	 }
	 if(havecheck==1)//没找到是=
	 {
		  MessageBox((_bstr_t)"已经有名为xxxxx的节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	 }	
	  //插入新节点	
	 
	   zhibiao a;
	   a.DoModal();
	     if(cancle==1)
	 {
		 cancle=1;
		 return;
	 }
	  //插入新节点	
		   //************************************************************************************
	 //找到要插入节点的位置给他的子项目数加一并因此判断此节点的编号应该是多少
	  itemname=m_ctltree.GetItemText(m_ctltree.GetSelectedItem());
	  //遍历数得到位置
	  int check=0,childs=0;
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
		  {
			  check=1;
			  break;
		  }
	  }
	  if(check==1)//找到
	  {
		    //插入新节点
	  CString str;
	   int i;
	   for(i=1;i<58;i++)
		{   
		//	MessageBox(zhibiaoxx[i]); 
			if(zhibiaoxx[i]!="0")
			{ 
				itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;	
	          str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]=zhibiaoxx[i];
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
			  m_ctltree.InsertItem((_bstr_t)zhibiaoxx[i],1,0,m_ctltree.GetSelectedItem());
	         }
			 
	   }
		 	//MessageBox((_bstr_t)zhibiaoitemchilds[position]); 		 
	  }
	 
	
	 }

	 //**********************************************************************************************
	  if(clicktreex==2)//树2
	 {
		 int havecheck=0;
	 for(position=0;position<treepoint1;position++)
	 {
		  if(treeitem1[position]=="xxxxx")
		  {
			  havecheck=1;
			  break;
		  }
	 }
	 if(havecheck==1)//
	 {
		  MessageBox((_bstr_t)"已经有名为xxxxx的节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	 }	
	  //插入新节点	
	  treeitem1[treepoint1]="xxxxx";
	  treepoint1++;
	//*********************************************************************
	 HTREEITEM hNew=m_ctltree1.InsertItem((_bstr_t)"xxxxx",1,0,m_ctltree1.GetSelectedItem());
	 }
}


void Step1dialog::OnNMRClickTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	clicktreex=2;//单击的树2
	CPoint point;
	GetCursorPos(&point); // 当前鼠标坐标
	CPoint PointInTree = point;
	m_ctltree1.ScreenToClient( &PointInTree);
	CMenu menu,menu2;
	CMenu *ptrMenu,*ptrMenu2;
	CBitmap m_bitmap1,m_bitmap2,m_bitmap3;
	m_bitmap1.LoadBitmap(IDB_BITMAP70);
	m_bitmap2.LoadBitmap(IDB_BITMAP71);
	m_bitmap3.LoadBitmap(IDB_BITMAP72);
	HTREEITEM Item;
	UINT nFlag = TVHT_ONITEM; // 当在 Item 上右击时
	Item =m_ctltree1.HitTest( PointInTree, &nFlag );
	CString roadname = m_ctltree1.GetItemText(Item);
	int nLength = roadname.GetLength(); 
	CString b=roadname.Right(3);
	if ( Item != NULL&&Item==hroot1)
	{ 
		m_ctltree1.SelectItem(Item);	
		menu2.LoadMenu(IDR_MENU6);	
	    ptrMenu2=menu2.GetSubMenu(0);
		ptrMenu2->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bitmap1,&m_bitmap1);
	    ptrMenu2->TrackPopupMenu
		(
		TPM_LEFTALIGN|TPM_RIGHTBUTTON,
		point.x,
		point.y,
		this,
		NULL);	
	}
	else if( Item != NULL)
	{
		m_ctltree1.SelectItem(Item);	
		menu.LoadMenu(IDR_MENU7);	
	    ptrMenu=menu.GetSubMenu(0);
		ptrMenu->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bitmap2,&m_bitmap2);
		ptrMenu->SetMenuItemBitmaps(1,MF_BYPOSITION,&m_bitmap3,&m_bitmap3);
	    ptrMenu->TrackPopupMenu
		(
		TPM_LEFTALIGN|TPM_RIGHTBUTTON,
		point.x,
		point.y,
		this,
		NULL);	
	}
	*pResult = 0;
}


void Step1dialog::OnTvnEndlabeleditTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	CString strText;
	m_ctltree1.GetEditControl()->GetWindowText(strText.GetBuffer(200),200);
	int havecheck=0;
    for(position=0;position<treepoint1;position++)
	{
		  if(treeitem1[position]==strText)
		  {
			  havecheck=1;
			  break;
		  }
	}
	if(havecheck==1)//
	{
		  MessageBox((_bstr_t)"已经有名为"+strText+"的节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}
	m_ctltree1.SetItemText(m_ctltree1.GetSelectedItem(),strText);//设置编辑后的文本为结点
	for(position=0;position<treepoint1;position++)
	{
	    if(treeitem1[position]==itemoldname)
			  break;
	}
	treeitem1[position]=strText;
	/*	for(position=0;position<treepoint;position++)
	  {
		 MessageBox((_bstr_t)treeitem[position][0]);
		  MessageBox((_bstr_t)treeitem[position][1]);
		  MessageBox((_bstr_t)itemchilds[position]);
	  }*/
	*pResult = 0;
}


void Step1dialog::OnNMClickTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	addclick=2;
	delclick=2;
	renamecheck=2;
	CPoint point;
	GetCursorPos(&point); // 当前鼠标坐标
	CPoint PointInTree = point;
	m_ctltree1.ScreenToClient( &PointInTree);
	CMenu menu;
	CMenu *ptrMenu;
	UINT nFlag = TVHT_ONITEM; // 当在 Item 上右击时
	delitem1 =m_ctltree1.HitTest( PointInTree, &nFlag );
	reitem1=m_ctltree1.HitTest( PointInTree, &nFlag );
//	MessageBox((_bstr_t)m_ctltree.GetItemText(delitem));
	*pResult = 0;
}


void Step1dialog::additem(void)
{

	if(addclick==0)
	{
		 MessageBox((_bstr_t)"未选中评价指标(U)或评价等级(V)无法添加节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}
	if(addclick==1)//树1
	 {
		 int havecheck=0;
	     for(position=0;position<zhibiaoitempoint;position++)
	    {
		     if(zhibiaoitem[position][1]=="xxxxx")
		     {
			    havecheck=1;
			    break;
		     }
	     }
	      if(havecheck==1)//没找到是=
	     {
		  MessageBox((_bstr_t)"已经有名为xxxxx的节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	      }	
	  //插入新节点		 
	   zhibiao a;
	   a.DoModal();
	     if(cancle==1)
	    {
		 cancle=1;
		 return;
	     }
	  //插入新节点	
		   //************************************************************************************
	 //找到要插入节点的位置给他的子项目数加一并因此判断此节点的编号应该是多少
	  itemname=m_ctltree.GetItemText(m_ctltree.GetSelectedItem());
	  //遍历数得到位置
	  int check=0,childs;
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
		  {
			  check=1;
			  break;
		  }
	  }
	  if(check==1)//找到
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		 		 
	  }
	 
	  //插入新节点
	  CString str;
	   int i;
	   for(i=1;i<58;i++)
		{   
		//	MessageBox(zhibiaoxx[i]); 
			if(zhibiaoxx[i]!="0")
			{
	          str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]=zhibiaoxx[i];
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
			  m_ctltree.InsertItem((_bstr_t)zhibiaoxx[i],1,0,m_ctltree.GetSelectedItem());
	         }
			 
	   }
	}
	 // addclick=0;
	//*********************************************************************
	
	 //**********************************************************************************************
	  if(addclick==2)//树2
	 {
		  int havecheck=0;
	 for(position=0;position<treepoint1;position++)
	 {
		  if(treeitem1[position]=="xxxxx")
		  {
			   havecheck=1;
			  break;
		  }
	 }
	 if(havecheck==1)//
	 {
		  MessageBox((_bstr_t)"已经有名为xxxxx的节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	 }	
	  //插入新节点	
	  treeitem1[treepoint1]="xxxxx";
	  treepoint1++; 
	  addclick=0;
	//*********************************************************************
	 HTREEITEM hNew=m_ctltree1.InsertItem((_bstr_t)"xxxxx",1,0,hroot1);
	
	 }
}


void Step1dialog::renameitem(void)
{
	if(reitem==NULL&&reitem1==NULL)
	{
		 MessageBox((_bstr_t)"未选中节点无法重命名",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}
	if(reitem==hroot&&reitem1==hroot1)
	{
		 MessageBox((_bstr_t)"根节点无法重命名",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	}
	if(renamecheck==1)
	{
	   m_ctltree.ModifyStyle(NULL,TVS_EDITLABELS);      //设置编辑风格
	   itemoldname=m_ctltree.GetItemText(reitem);
       m_ctltree.EditLabel(reitem);
	   reitem=NULL;
	   return;
	}
	if(renamecheck==2)
	{
	   m_ctltree1.ModifyStyle(NULL,TVS_EDITLABELS);      //设置编辑风格
	   itemoldname=m_ctltree1.GetItemText(reitem1);
       m_ctltree1.EditLabel(reitem1);
	   reitem1=NULL;
	   return;
	}

}


BOOL Step1dialog::PreTranslateMessage(MSG* pMsg)
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
		 m_ctrlTT11.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}


void Step1dialog::OnYijiadderji()//一级节点增加二级节点
{
	// TODO: 在此添加命令处理程序代码
	 UpdateData(true);
	 if(clicktreex==1)//树1
	 {
		 int havecheck=0;
	     for(position=0;position<zhibiaoitempoint;position++)
	    {
		     if(zhibiaoitem[position][1]=="xxxxx")
		     {
			    havecheck=1;
			    break;
		     }
	     }
	      if(havecheck==1)//没找到是=
	     {
		  MessageBox((_bstr_t)"已经有名为xxxxx的节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	      }	
	  //插入新节点		 
	   zhibiao a;
	   a.DoModal();
	     if(cancle==1)
	    {
		 cancle=1;
		 return;
	     }
	  //插入新节点	
		   //************************************************************************************
	 //找到要插入节点的位置给他的子项目数加一并因此判断此节点的编号应该是多少
	  itemname=m_ctltree.GetItemText(m_ctltree.GetSelectedItem());
	  //遍历数得到位置
	  int check=0,childs;
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
		  {
			  check=1;
			  break;
		  }
	  }
	  if(check==1)//找到
	  {
		  		   //插入新节点
	  CString str;
	   int i;
	   for(i=1;i<58;i++)
		{   
		//	MessageBox(zhibiaoxx[i]); 
			if(zhibiaoxx[i]!="0")
			{ itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		
	          str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]=zhibiaoxx[i];
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
			  m_ctltree.InsertItem((_bstr_t)zhibiaoxx[i],1,0,m_ctltree.GetSelectedItem());
	         }
			 
	   }
	  }
	 
	
	 }
	
}


void Step1dialog::OnErjiaddsanji()//二级节点增加三级节点
{
	// TODO: 在此添加命令处理程序代码
	 UpdateData(true);
	 if(clicktreex==1)//树1
	 {
		 int havecheck=0;
	     for(position=0;position<zhibiaoitempoint;position++)
	    {
		     if(zhibiaoitem[position][1]=="xxxxx")
		     {
			    havecheck=1;
			    break;
		     }
	     }
	      if(havecheck==1)//没找到是=
	     {
		  MessageBox((_bstr_t)"已经有名为xxxxx的节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	      }	
	  //插入新节点		 
	   zhibiao a;
	   a.DoModal();
	     if(cancle==1)
	    {
		 cancle=1;
		 return;
	     }
	  //插入新节点	
		   //************************************************************************************
	 //找到要插入节点的位置给他的子项目数加一并因此判断此节点的编号应该是多少
	  itemname=m_ctltree.GetItemText(m_ctltree.GetSelectedItem());
	  //遍历数得到位置
	  int check=0,childs;
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
		  {
			  check=1;
			  break;
		  }
	  }
	  if(check==1)//找到
	  {
		 	  //插入新节点
	  CString str;
	   int i;
	   for(i=1;i<58;i++)
		{   
		//	MessageBox(zhibiaoxx[i]); 
			if(zhibiaoxx[i]!="0")
			{ itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		 	
	          str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]=zhibiaoxx[i];
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
			  m_ctltree.InsertItem((_bstr_t)zhibiaoxx[i],1,0,m_ctltree.GetSelectedItem());
	         }
			 
	   }
	  }
	 
	 
	 }
	
}


void Step1dialog::OnDelerji()//删除二级节点
{
	// TODO: 在此添加命令处理程序代码
	UpdateData(true);
	if(clicktreex==1)
	{
	if(hroot==m_ctltree.GetSelectedItem())
	{
		MessageBox((_bstr_t)"根节点无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
		return;
	}
	//找有没有子节点
	CString item;
    CString fatheritem,childitem;
    int len,delitempos,biao=0,biao1=0,childs;
	
	for(position=0;position<zhibiaoitempoint;position++)//找在数组中的位置
	 {
		  if(zhibiaoitem[position][1]== m_ctltree.GetItemText(m_ctltree.GetSelectedItem()))
			 {
				 biao=1;
				 break;
		  }
	 }

	  if(biao==1)//
	  {
		   delitempos=position;
		   childs=zhibiaoitemchilds[position];//子节点个数
		   item=zhibiaoitem[position][0];
		  
	  }
	  if(childs!=0)
	  {
		  MessageBox((_bstr_t)"该指标存在低级指标无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	  }
	   //找到父节点的个数减1
	  len=item.GetLength();  //获取当前行的值的长度；
	  fatheritem=item.Mid(0,len-1);
	    
	  for(position=0;position<zhibiaoitempoint;position++)
	   {
		   if(zhibiaoitem[position][0]== fatheritem)
		   {
			   biao1=1;
			  break;
		   }
	    }
		//	MessageBox((_bstr_t)treeitem[position][1]);
	   if(biao1==1)//
	   {
		   childs=zhibiaoitemchilds[position];//子节点个数
		   zhibiaoitemchilds[position]=childs-1;
	    }
		int pos;
		for(pos=delitempos;pos<zhibiaoitempoint;pos++)
	    {
		    zhibiaoitem[pos][0]= zhibiaoitem[pos+1][0];
			zhibiaoitem[pos][1]= zhibiaoitem[pos+1][1];
			zhibiaoitemchilds[pos]=zhibiaoitemchilds[pos+1];
	    }
		zhibiaoitempoint--;
        m_ctltree.DeleteItem(m_ctltree.GetSelectedItem());//删除活动的结
	}
}


void Step1dialog::OnDelsanji()//删除三级节点
{
	// TODO: 在此添加命令处理程序代码
	UpdateData(true);
	if(clicktreex==1)
	{
	if(hroot==m_ctltree.GetSelectedItem())
	{
		MessageBox((_bstr_t)"根节点无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
		return;
	}
//找有没有子节点
	CString item;
    CString fatheritem,childitem;
    int len,delitempos,biao=0,biao1=0,childs;
	
	for(position=0;position<zhibiaoitempoint;position++)//找在数组中的位置
	 {
		  if(zhibiaoitem[position][1]== m_ctltree.GetItemText(m_ctltree.GetSelectedItem()))
			 {
				 biao=1;
				 break;
		  }
	 }

	  if(biao==1)//
	  {
		   delitempos=position;
		   childs=zhibiaoitemchilds[position];//子节点个数
		   item=zhibiaoitem[position][0];
		  
	  }
	  if(childs!=0)
	  {
		  MessageBox((_bstr_t)"该指标存在低级指标无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	  }
	   //找到父节点的个数减1
	  len=item.GetLength();  //获取当前行的值的长度；
	  fatheritem=item.Mid(0,len-1);
	    
	  for(position=0;position<zhibiaoitempoint;position++)
	   {
		   if(zhibiaoitem[position][0]== fatheritem)
		   {
			   biao1=1;
			  break;
		   }
	    }
		//	MessageBox((_bstr_t)treeitem[position][1]);
	   if(biao1==1)//
	   {
		   childs=zhibiaoitemchilds[position];//子节点个数
		   zhibiaoitemchilds[position]=childs-1;
	    }
		int pos;
		for(pos=delitempos;pos<zhibiaoitempoint;pos++)
	    {
		    zhibiaoitem[pos][0]= zhibiaoitem[pos+1][0];
			zhibiaoitem[pos][1]= zhibiaoitem[pos+1][1];
			zhibiaoitemchilds[pos]=zhibiaoitemchilds[pos+1];
	    }
		zhibiaoitempoint--;
        m_ctltree.DeleteItem(m_ctltree.GetSelectedItem());//删除活动的结
	}
}


void Step1dialog::OnRenameerji()//重命名二级节点
{
	// TODO: 在此添加命令处理程序代码
	 UpdateData(true);	 
	 if(clicktreex==1)
	 {
       m_ctltree.ModifyStyle(NULL,TVS_EDITLABELS);      //设置编辑风格
	   HTREEITEM hItem=m_ctltree.GetSelectedItem();
	   itemoldname=m_ctltree.GetItemText(hItem);
       m_ctltree.EditLabel(hItem);
	   return;
	 }
}


void Step1dialog::OnRenamesanji()//重命名三级节点
{
	// TODO: 在此添加命令处理程序代码
	 UpdateData(true);	 
	 if(clicktreex==1)
	 {
       m_ctltree.ModifyStyle(NULL,TVS_EDITLABELS);      //设置编辑风格
	   HTREEITEM hItem=m_ctltree.GetSelectedItem();
	   itemoldname=m_ctltree.GetItemText(hItem);
       m_ctltree.EditLabel(hItem);
	   return;
	 }
}


void Step1dialog::OnTree2add()
{
	// TODO: 在此添加命令处理程序代码
	 int havecheck=0;
	 for(position=0;position<treepoint1;position++)
	 {
		  if(treeitem1[position]=="xxxxx")
		  {
			  havecheck=1;
			  break;
		  }
	 }
	 if(havecheck==1)//
	 {
		  MessageBox((_bstr_t)"已经有名为xxxxx的节点",(_bstr_t)"警告", MB_OKCANCEL ); 
			return;
	 }	
	  //插入新节点	
	  treeitem1[treepoint1]="xxxxx";
	  treepoint1++;
	//*********************************************************************
	 HTREEITEM hNew=m_ctltree1.InsertItem((_bstr_t)"xxxxx",1,0,m_ctltree1.GetSelectedItem());
}


void Step1dialog::OnTree2del()
{
	// TODO: 在此添加命令处理程序代码
	if(hroot1==m_ctltree1.GetSelectedItem())
	{
		MessageBox((_bstr_t)"根节点无法删除",(_bstr_t)"警告", MB_OKCANCEL ); 
		return;
	}
	CString item;
    int len,delitempos;	
    for(position=0;position<treepoint1;position++)//找在数组中的位置
	 {
		  if(treeitem1[position]== m_ctltree1.GetItemText(m_ctltree1.GetSelectedItem()))
			 {
				 delitempos=position;
				 break;
		  }
	 }
   
		int pos;
		for(pos=delitempos;pos<treepoint1;pos++)
	    {
		    treeitem1[pos]= treeitem1[pos+1];
		
	    }
		treepoint1--;
        m_ctltree1.DeleteItem(m_ctltree1.GetSelectedItem());//删除活动的结点
	
}


void Step1dialog::OnTree2rename()
{
	// TODO: 在此添加命令处理程序代码
	   m_ctltree1.ModifyStyle(NULL,TVS_EDITLABELS);      //设置编辑风格
	   HTREEITEM hItem=m_ctltree1.GetSelectedItem();
	   itemoldname=m_ctltree1.GetItemText(hItem);
       m_ctltree1.EditLabel(hItem);
	   return;
}


void Step1dialog::OnBnClickedButton1()//已有工程新建工程
{
	// TODO: 在此添加控件通知处理程序代码
	//删除原树1
	 HTREEITEM   hItem;
	 int i;
	while(m_ctltree.ItemHasChildren(hroot) )
	{
	     hItem=m_ctltree.GetChildItem(hroot); //获取第一个子结点
		 m_ctltree.DeleteItem(hItem);//删除活动的结点
	}
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
	//根据数组建树
	zhibiaoitempoint=0;
	zhibiaoitem[zhibiaoitempoint][0]="0";zhibiaoitem[zhibiaoitempoint][1]="评价指标(U)";zhibiaoitemchilds[zhibiaoitempoint]=0;zhibiaoitempoint++;
	 h1=m_ctltree.InsertItem((_bstr_t)"指标",1,0,hroot);//添加二级节点
	 //************************************************************************************
	 //找到要插入节点的位置给他的子项目数加一并因此判断此节点的编号应该是多少
	  itemname=m_ctltree.GetItemText(hroot);
	  //遍历数得到位置
	  int check=0;//找到标记
	  int childs=0;//记录子节点数
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//找到
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //插入新节点
	  CString str;
	  str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]="指标";
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
	//****************************************************************************************8
	//删除原树2
	 HTREEITEM   hItem1;
	while(m_ctltree1.ItemHasChildren(hroot1) )
	{
	     hItem1=m_ctltree1.GetChildItem(hroot1); //获取第一个子结点
		 m_ctltree1.DeleteItem(hItem1);//删除活动的结点
	}
	//删除原数据
	for(i=0;i<treepoint1;i++)
	{
	  treeitem1[i]="0";				
	}
	treepoint1=0;
	treeitem1[treepoint1]="评语(V)";treepoint1++;
	 h2=m_ctltree1.InsertItem((_bstr_t)"评语",1,0,hroot1);//添加二级节点
	treeitem1[treepoint1]="评语"; treepoint1++;	
	
}


void Step1dialog::OnBnClickedButton28()//save
{
	// TODO: 在此添加控件通知处理程序代码
	treesave=1;
		int i,j,k,yiji=0,erji=0,sanji=0,m,n,b;
	    CString str;
		if(m_ctltree.ItemHasChildren(hroot))//判断结点是否有子结点
			{
				
				Ftree[0]=m_ctltree.GetItemText(hroot);
				//找此根节点对应有多少一级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==Ftree[0])
		                        {
									b= zhibiaoitemchilds[position];
			                          break;
		                         }
							}
							str.Format("%d",b);
							Ftree[0]="0"+Ftree[0]+"/"+str;//根
			
				for(i=0;i<b-1;i++)//减1
	            {
                   if(yiji==0)
				   {
                   yijiitem=m_ctltree.GetChildItem(hroot); //获取第一个子结点
				   Ftree[Ftreenum]=m_ctltree.GetItemText(yijiitem);
				   //找此一级节点对应有多少二级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==Ftree[Ftreenum])
		                        {
									n= zhibiaoitemchilds[position];
			                          break;
		                         }
							}
					str.Format("%d",n);
					Ftree[Ftreenum]="1"+Ftree[Ftreenum]+"/"+str;Ftreenum++;//一级
				   //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&2ji
				   for(j=0;j<n-1;j++)//第二个子节点
				   {
					   if(erji==0)
					   {
					    erjiitem=m_ctltree.GetChildItem(yijiitem);
					    Ftree[Ftreenum]=m_ctltree.GetItemText(erjiitem);

						//找此二级节点对应有多少三级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==Ftree[Ftreenum])
		                        {
									m= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",m);
					     Ftree[Ftreenum]="2"+Ftree[Ftreenum]+"/"+str;Ftreenum++;
						//*****************************************************3ji
						  for(k=0;k<m-1;k++)//第三个子节点
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//获取下一个兄弟结点结点
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;//MessageBox((_bstr_t)tree[treenum]+"0");treenum++;
							
							}
				         }
						  sanji=0;
						  
						  erji=1;
						  //******************************************************
					   }
					     if(erji==1)
					   {
					    erjiitem=m_ctltree.GetNextSiblingItem(erjiitem);
					    Ftree[Ftreenum]=m_ctltree.GetItemText(erjiitem);//MessageBox( tree[treenum]);treenum++;
						//找此二级节点对应有多少三级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==Ftree[Ftreenum])
		                        {
									m= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",m);
					     Ftree[Ftreenum]="2"+Ftree[Ftreenum]+"/"+str;Ftreenum++;
						//*****************************************************3ji
						  for(k=0;k<m-1;k++)//第三个子节点
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//获取下一个兄弟结点结点
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;//MessageBox((_bstr_t)tree[treenum]+"1");treenum++;
						
							}
				         }
						  sanji=0;
						  
						  //******************************************************
					   }
				   }
				   erji=0;
				  
				   yiji=1;
				   //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
				   }
//********************************&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&(((((((((((((((((((((((9
				   if(yiji==1)
				   {
                  yijiitem=m_ctltree.GetNextSiblingItem(yijiitem);
				   Ftree[Ftreenum]=m_ctltree.GetItemText(yijiitem);
				   //找此一级节点对应有多少二级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==Ftree[Ftreenum])
		                        {
									n= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",n);
					Ftree[Ftreenum]="1"+Ftree[Ftreenum]+"/"+str;Ftreenum++;
				   //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&2ji
				   for(j=0;j<n-1;j++)//第二个子节点
				   {
					   if(erji==0)
					   {
					    erjiitem=m_ctltree.GetChildItem(yijiitem);
					    Ftree[Ftreenum]=m_ctltree.GetItemText(erjiitem);
						//找此二级节点对应有多少三级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==Ftree[Ftreenum])
		                        {
									m= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",m);
					    Ftree[Ftreenum]="2"+Ftree[Ftreenum]+"/"+str;Ftreenum++;
						//*****************************************************3ji
						  for(k=0;k<m-1;k++)//第三个子节点
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//获取下一个兄弟结点结点
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
							
							}
				         }
						  sanji=0;
					
						  erji=1;
						  //******************************************************
					   }
					     if(erji==1)
					   {
					    erjiitem=m_ctltree.GetNextSiblingItem(erjiitem);
					    Ftree[Ftreenum]=m_ctltree.GetItemText(erjiitem);
						//找此二级节点对应有多少三级
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==Ftree[Ftreenum])
		                        {
									m= zhibiaoitemchilds[position];
			                          break;
		                         }
	                        }
							str.Format("%d",m);
					     Ftree[Ftreenum]="2"+Ftree[Ftreenum]+"/"+str;Ftreenum++;
						//*****************************************************3ji
						  for(k=0;k<m-1;k++)//第三个子节点
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//获取下一个兄弟结点结点
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
						
							}
				         }
						  sanji=0;
						  
						  //******************************************************
					   }
				   }
				   erji=0;
				   yiji=1;
				   //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
				   }

				}
		}
		//测试输出
		CString szFileFilter=(_bstr_t)"文本(*.txt)|*.txt|";
	CString szFileExt=(_bstr_t)"txt";//扩展名为txt
	CFileDialog dlg(false,szFileExt,NULL,OFN_HIDEREADONLY,szFileFilter);
	if(dlg.DoModal()==IDOK)
	{
		CStdioFile File;		
		File.Open(dlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
		char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
        setlocale( LC_CTYPE, "chs" );//设定
		for(position=0;position<Ftreenum;position++)
	    {
			File.WriteString((_bstr_t)Ftree[position]+(_bstr_t)"\r\n");//正常写入	
	    }
		

        File.WriteString((_bstr_t)"Finish");
        setlocale( LC_CTYPE, old_locale );
        free( old_locale );//还原区域设定
		File.Close();
	}
}


void Step1dialog::OnBnClickedButton27()//tip
{
	// TODO: 在此添加控件通知处理程序代码
	 MessageBox((_bstr_t)"1.评价指标(U)与评语(V)建立完成后，请保存",(_bstr_t)"提示", MB_OK ); 
}
