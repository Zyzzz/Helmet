// Step1dialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Helmet-FCEM.h"
#include "Step1dialog.h"
#include "afxdialogex.h"
#include <locale>
#include "zhibiao.h"
CToolTipCtrl  m_ctrlTT11;
//***************************��¼�������нڵ㣬���ڷּ���Ȩ
int Ftreenum=1;
CString Ftree[200];
int treesave=0;

extern CString zhibiaoxx[57];//57������ָ�꣨��¼��ѡ����Ŀ�� �̳���zhibiao.cpp
//**************************һЩ���
extern int cancle;
extern CString delbutton;
int clicktreex=0,delclick=0,addclick=0,renamecheck=0;

HTREEITEM hroot,delitem=NULL,h1,hroot1,delitem1=NULL,h2,reitem=NULL,reitem1=NULL,yijiitem,erjiitem,sanjiitem;
//int  itemchild;
CString itemname,itemnumber,itemoldname;//ָ����
CString itemname1,itemnumber1,itemoldname1;//������
//****************************************������ָ�����Ľڵ�
int position;
 CString  zhibiaoitem[100][2];//��һ��ָ���������нڵ� [0]���(���ڷ���������֪��˭��˭��һ��)  [1]����
 int zhibiaoitemchilds[100];//��һ��ָ������ÿ���ڵ��ж����ӽڵ�
 int zhibiaoitempoint=0;//��һ��ָ����һ���ж��ٽڵ㣨ָ�꣩
 int  itemchildpoint=0;//
//*******************************************������
extern CString  treeitem1[100];//���ڴ�ŵ�һ���������������нڵ�����
extern int treepoint1;
//*********************************************8���ļ�
extern CString openitem[200];//�򿪵�txt�ļ�������
extern int openpoint;//���ļ����ݵ��ܸ���
extern int openitemnum[200];//ÿ����Ӧ���������
CImageList m_imagelist,m_imagelist1;//����ͼ���б�
// Step1dialog �Ի���

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


// Step1dialog ��Ϣ�������


void Step1dialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
 
   //IDC_TESTΪ���������ʾ�Ŀؼ�IDC��"helloΪ����ӵ���ʾ���"
   m_ctrlTT11.AddTool(GetDlgItem(IDC_BUTTON27),(_bstr_t)"��ʾ");
   m_ctrlTT11.AddTool(GetDlgItem(IDC_BUTTON28),(_bstr_t)"����ģ����Ϣ");
	//*********************************8
	//ָ����
	//***********************************
	m_imagelist.Create(16,16,ILC_COLOR,2,2);//����ͼ���б��ֱ�������أ���ɫ��ͼƬ���������ͼƬ����
	CBitmap bm;//λͼ��װ����
	bm.LoadBitmap(IDB_BITMAP67);//����Bitmap��Դ
	m_imagelist.Add(&bm,RGB(0,0,0));//��ӵ�ͼ���б�
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP66);
	m_imagelist.Add(&bm,RGB(0,0,0));
	m_ctltree.SetImageList(&m_imagelist,LVSIL_NORMAL);//Ϊ���οؼ����ͼ���б�
	
	//*********************************����ڵ�
	hroot=m_ctltree.InsertItem((_bstr_t)"����ָ��(U)",1,0,TVI_ROOT);
	zhibiaoitem[zhibiaoitempoint][0]="0";zhibiaoitem[zhibiaoitempoint][1]="����ָ��(U)";zhibiaoitemchilds[zhibiaoitempoint]=0;zhibiaoitempoint++;
	 h1=m_ctltree.InsertItem((_bstr_t)"ָ��",1,0,hroot);//��Ӷ����ڵ�
	 //************************************************************************************
	 //�ҵ�Ҫ����ڵ��λ�ø���������Ŀ����һ������жϴ˽ڵ�ı��Ӧ���Ƕ���
	  itemname=m_ctltree.GetItemText(hroot);
	  //�������õ�λ��
	  int check=0;//�ҵ����
	  int childs=0;//��¼�ӽڵ���
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//�ҵ�
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //�����½ڵ�
	  CString str;
	  str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]="ָ��";
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
	m_ctltree.SetBkColor(RGB(255,255,255));//�������οؼ��ı���ɫ
	m_ctltree.SetTextColor(RGB(0,0,0));//�����ı�����ɫ
	m_ctltree.Select(h1,TVGN_CARET);
	//**************************************8
	//������
	m_imagelist1.Create(16,16,ILC_COLOR,2,2);//����ͼ���б��ֱ�������أ���ɫ��ͼƬ���������ͼƬ����
	CBitmap bm1;//λͼ��װ����
	bm1.LoadBitmap(IDB_BITMAP67);//����Bitmap��Դ
	m_imagelist1.Add(&bm1,RGB(0,0,0));//��ӵ�ͼ���б�
	bm1.DeleteObject();
	bm1.LoadBitmap(IDB_BITMAP66);
	m_imagelist1.Add(&bm1,RGB(0,0,0));
	m_ctltree1.SetImageList(&m_imagelist1,LVSIL_NORMAL);//Ϊ���οؼ����ͼ���б�
	hroot1=m_ctltree1.InsertItem((_bstr_t)"����(V)",1,0,TVI_ROOT);//���һ���ڵ�
	treeitem1[treepoint1]="����(V)";treepoint1++;
	 h2=m_ctltree1.InsertItem((_bstr_t)"����",1,0,hroot1);//��Ӷ����ڵ�
	treeitem1[treepoint1]="����"; treepoint1++;	
	m_ctltree1.SetBkColor(RGB(255,255,255));//�������οؼ��ı���ɫ
	m_ctltree1.SetTextColor(RGB(0,0,0));//�����ı�����ɫ
	m_ctltree1.Select(h2,TVGN_CARET);

	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void Step1dialog::OnPaint()
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

void Step1dialog::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)//���ѡ�е���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	addclick=1;//�������Ҫ��ӽڵ�
	delclick=1;//�������Ҫɾ���ڵ�
	renamecheck=1;//�������Ҫ�������ڵ�
	CPoint point;
	GetCursorPos(&point); // ��ǰ�������
	CPoint PointInTree = point;
	m_ctltree.ScreenToClient( &PointInTree);
	CMenu menu;
	CMenu *ptrMenu;
	UINT nFlag = TVHT_ONITEM; // ���� Item ���һ�ʱ
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
		  MessageBox((_bstr_t)"�Ѿ�����Ϊ"+strText+"�Ľڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	}
	m_ctltree.SetItemText(m_ctltree.GetSelectedItem(),strText);//���ñ༭����ı�Ϊ���
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
	// TODO: �ڴ���������������
	UpdateData(true);
	if(clicktreex==1)
	{
	if(hroot==m_ctltree.GetSelectedItem())
	{
		MessageBox((_bstr_t)"���ڵ��޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
		return;
	}
	//����û���ӽڵ�
	CString item;
    CString fatheritem,childitem;
    int len,delitempos,biao=0,biao1=0,childs;
	
	for(position=0;position<zhibiaoitempoint;position++)//���������е�λ��
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
		   childs=zhibiaoitemchilds[position];//�ӽڵ����
		   item=zhibiaoitem[position][0];
		  
	  }
	  if(childs!=0)
	  {
		  MessageBox((_bstr_t)"��ָ����ڵͼ�ָ���޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	  }
	   //�ҵ����ڵ�ĸ�����1
	  len=item.GetLength();  //��ȡ��ǰ�е�ֵ�ĳ��ȣ�
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
		   childs=zhibiaoitemchilds[position];//�ӽڵ����
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
        m_ctltree.DeleteItem(m_ctltree.GetSelectedItem());//ɾ����Ľ�
	}
	//**************************************
	if(clicktreex==2)
	{
	if(hroot1==m_ctltree1.GetSelectedItem())
	{
		MessageBox((_bstr_t)"���ڵ��޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
		return;
	}
	CString item;
    int len,delitempos;	
    for(position=0;position<treepoint1;position++)//���������е�λ��
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
        m_ctltree1.DeleteItem(m_ctltree1.GetSelectedItem());//ɾ����Ľ��
	}
}



void Step1dialog::OnNMRDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void Step1dialog::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	clicktreex=1;//��������2
	CPoint point;
	GetCursorPos(&point); // ��ǰ�������
	CPoint PointInTree = point;
	m_ctltree.ScreenToClient( &PointInTree);
	CMenu menu,menu2;
	CMenu *ptrMenu,*ptrMenu2,*ptrMenu3;
	CBitmap m_bitmap1,m_bitmap2,m_bitmap3;
	m_bitmap1.LoadBitmap(IDB_BITMAP70);
	m_bitmap2.LoadBitmap(IDB_BITMAP71);
	m_bitmap3.LoadBitmap(IDB_BITMAP72);
	HTREEITEM Item;
	UINT nFlag = TVHT_ONITEM; // ���� Item ���һ�ʱ
	Item =m_ctltree.HitTest( PointInTree, &nFlag );
	CString roadname = m_ctltree.GetItemText(Item);
	int nLength = roadname.GetLength(); 
	CString b=roadname.Right(3);
	if ( Item != NULL&&Item==hroot)//�ܸ��ڵ� �����½�һ���ڵ�
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
   if( Item != NULL&&m_ctltree.GetParentItem(Item)==hroot)//һ���ڵ� �����½������ڵ�
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
    if( Item != NULL&&m_ctltree.GetParentItem(m_ctltree.GetParentItem(Item))==hroot)//�����ڵ� �����½������ڵ�
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
	 if( Item != NULL&&m_ctltree.GetParentItem(m_ctltree.GetParentItem(m_ctltree.GetParentItem(Item)))==hroot)//�����ڵ�
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

void Step1dialog::OnBnClickedButton2()//����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//������
	int i,j,k,treenum=1,yiji=0,erji=0,sanji=0,m,n,b;
	CString tree[200],str;
		if(m_ctltree.ItemHasChildren(hroot))//�жϽ���Ƿ����ӽ��
			{
				
				tree[0]=m_ctltree.GetItemText(hroot);
				//�Ҵ˸��ڵ��Ӧ�ж���һ��
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
                   yijiitem=m_ctltree.GetChildItem(hroot); //��ȡ��һ���ӽ��
				   tree[treenum]=m_ctltree.GetItemText(yijiitem);
				   //�Ҵ�һ���ڵ��Ӧ�ж��ٶ���
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
				   for(j=0;j<n-1;j++)//�ڶ����ӽڵ�
				   {
					   if(erji==0)
					   {
					    erjiitem=m_ctltree.GetChildItem(yijiitem);
					    tree[treenum]=m_ctltree.GetItemText(erjiitem);

						//�Ҵ˶����ڵ��Ӧ�ж�������
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
						  for(k=0;k<m-1;k++)//�������ӽڵ�
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//��ȡ��һ���ֵܽ����
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
						//�Ҵ˶����ڵ��Ӧ�ж�������
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
						  for(k=0;k<m-1;k++)//�������ӽڵ�
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//��ȡ��һ���ֵܽ����
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
				   //�Ҵ�һ���ڵ��Ӧ�ж��ٶ���
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
				   for(j=0;j<n-1;j++)//�ڶ����ӽڵ�
				   {
					   if(erji==0)
					   {
					    erjiitem=m_ctltree.GetChildItem(yijiitem);
					    tree[treenum]=m_ctltree.GetItemText(erjiitem);
						//�Ҵ˶����ڵ��Ӧ�ж�������
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
						  for(k=0;k<m-1;k++)//�������ӽڵ�
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//��ȡ��һ���ֵܽ����
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
						//�Ҵ˶����ڵ��Ӧ�ж�������
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
						  for(k=0;k<m-1;k++)//�������ӽڵ�
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							tree[treenum]=m_ctltree.GetItemText(sanjiitem)+"/";treenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//��ȡ��һ���ֵܽ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	b=treepoint1-1;
	CString szFileFilter=(_bstr_t)"�ı�(*.txt)|*.txt|";
	CString szFileExt=(_bstr_t)"txt";//��չ��Ϊtxt
	CFileDialog dlg(false,szFileExt,NULL,OFN_HIDEREADONLY,szFileFilter);
	if(dlg.DoModal()==IDOK)
	{
		CStdioFile File;		
		File.Open(dlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
		char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
        setlocale( LC_CTYPE, "chs" );//�趨
		for(position=0;position<treenum;position++)
	    {
			File.WriteString((_bstr_t)tree[position]+(_bstr_t)"\r\n");//����д��	
	    }
		File.WriteString((_bstr_t)treeitem1[0]+(_bstr_t)"/"+(_bstr_t)b+(_bstr_t)"\r\n");
		for(position=1;position<treepoint1;position++)
	    {
		  File.WriteString((_bstr_t)treeitem1[position]+(_bstr_t)"\r\n");//����д��	
	    }

        File.WriteString((_bstr_t)"Finish");
        setlocale( LC_CTYPE, old_locale );
        free( old_locale );//��ԭ�����趨
		File.Close();
	}
}


void Step1dialog::deltreeitem()
{
	//MessageBox((_bstr_t)m_ctltree.GetItemText(delitem));
	//UpdateData(true);
	if(delitem1==NULL&&delitem==NULL)
	{
		MessageBox((_bstr_t)"δѡ�нڵ��޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	}
	if(delclick==1)
	{
	
	if(hroot==delitem)
	{
		MessageBox((_bstr_t)"���ڵ��޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	}
//����û���ӽڵ�
	CString item;
    CString fatheritem,childitem;
    int len,delitempos,biao=0,biao1=0,childs;
	
	for(position=0;position<zhibiaoitempoint;position++)//���������е�λ��
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
		   childs=zhibiaoitemchilds[position];//�ӽڵ����
		   item=zhibiaoitem[position][0];
		  
	  }
	  if(childs!=0)
	  {
		  MessageBox((_bstr_t)"��ָ����ڵͼ�ָ���޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	  }
	   //�ҵ����ڵ�ĸ�����1
	  len=item.GetLength();  //��ȡ��ǰ�е�ֵ�ĳ��ȣ�
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
		   childs=zhibiaoitemchilds[position];//�ӽڵ����
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
        m_ctltree.DeleteItem(m_ctltree.GetSelectedItem());//ɾ����Ľ�
    delitem=NULL;
	}

	//*******************************************8
	if(delclick==2)
	{
	
	if(hroot1==delitem1)
	{
		MessageBox((_bstr_t)"���ڵ��޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	}

	CString item;
    int len,delitempos;	
    for(position=0;position<treepoint1;position++)//���������е�λ��
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
    
	m_ctltree1.DeleteItem(delitem1);//ɾ����Ľ��
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
	
	//ɾ��ԭ��1
	 HTREEITEM   hItem;
	while(m_ctltree.ItemHasChildren(hroot) )
	{
	     hItem=m_ctltree.GetChildItem(hroot); //��ȡ��һ���ӽ��
		 m_ctltree.DeleteItem(hItem);//ɾ����Ľ��
	}
	//�������齨��
	zhibiaoitempoint=0;
	zhibiaoitem[zhibiaoitempoint][0]="0";zhibiaoitem[zhibiaoitempoint][1]="����ָ��(U)";zhibiaoitemchilds[zhibiaoitempoint]=0;zhibiaoitempoint++;
	HTREEITEM hNew,hnew1,hnew2,hnew3;
	int point=1;
	for(i=0;i<openitemnum[0];i++)
	{
		//****************************************
		 //�ҵ�Ҫ����ڵ��λ�ø���������Ŀ����һ������жϴ˽ڵ�ı��Ӧ���Ƕ���
	  itemname=openitem[0];
	  //�������õ�λ��
	  int check=0;//�ҵ����
	  int childs=0;//��¼�ӽڵ���
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//�ҵ�
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //�����½ڵ�
	 
	  str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]=openitem[point];
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
	    //******************************************
		 hnew1= m_ctltree.InsertItem((_bstr_t)openitem[point],1,0,hroot);//һ���ڵ�
		 n=openitemnum[point];str1=openitem[point];point++;
		for(j=0;j<n;j++)
		            {//MessageBox((_bstr_t)"2"+(_bstr_t)openitem[point]+(_bstr_t)n);
							//****************************************
		 //�ҵ�Ҫ����ڵ��λ�ø���������Ŀ����һ������жϴ˽ڵ�ı��Ӧ���Ƕ���
	  itemname=str1;
	  //�������õ�λ��
	  int check=0;//�ҵ����
	  int childs=0;//��¼�ӽڵ���
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//�ҵ�
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //�����½ڵ�
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
		 //�ҵ�Ҫ����ڵ��λ�ø���������Ŀ����һ������жϴ˽ڵ�ı��Ӧ���Ƕ���
	  itemname=str2;
	  //�������õ�λ��
	  int check=0;//�ҵ����
	  int childs=0;//��¼�ӽڵ���
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//�ҵ�
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //�����½ڵ�
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
	
	//ɾ��ԭ��2
	 HTREEITEM   hItem1;
	while(m_ctltree1.ItemHasChildren(hroot1) )
	{
	     hItem1=m_ctltree1.GetChildItem(hroot1); //��ȡ��һ���ӽ��
		 m_ctltree1.DeleteItem(hItem1);//ɾ����Ľ��
	}
	//�������齨��
	for(i=1;i<treepoint1;i++)
	{
		HTREEITEM hNew= m_ctltree1.InsertItem((_bstr_t)treeitem1[i],1,0,hroot1);
	}
	
}


void Step1dialog::OnRename()
{
	// TODO: �ڴ���������������
	 UpdateData(true);	 
	 if(clicktreex==1)
	 {
       m_ctltree.ModifyStyle(NULL,TVS_EDITLABELS);      //���ñ༭���
	   HTREEITEM hItem=m_ctltree.GetSelectedItem();
	   itemoldname=m_ctltree.GetItemText(hItem);
       m_ctltree.EditLabel(hItem);
	   return;
	 }
	  if(clicktreex==2)
	 {
       m_ctltree1.ModifyStyle(NULL,TVS_EDITLABELS);      //���ñ༭���
	   HTREEITEM hItem=m_ctltree1.GetSelectedItem();
	   itemoldname=m_ctltree1.GetItemText(hItem);
       m_ctltree1.EditLabel(hItem);
	   return;
	 }
}


void Step1dialog::OnAdd()//���ڵ�����һ���ڵ�
{
	// TODO: �ڴ���������������
	 UpdateData(true);
	 if(clicktreex==1)//��1
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
	 if(havecheck==1)//û�ҵ���=
	 {
		  MessageBox((_bstr_t)"�Ѿ�����Ϊxxxxx�Ľڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	 }	
	  //�����½ڵ�	
	 
	   zhibiao a;
	   a.DoModal();
	     if(cancle==1)
	 {
		 cancle=1;
		 return;
	 }
	  //�����½ڵ�	
		   //************************************************************************************
	 //�ҵ�Ҫ����ڵ��λ�ø���������Ŀ����һ������жϴ˽ڵ�ı��Ӧ���Ƕ���
	  itemname=m_ctltree.GetItemText(m_ctltree.GetSelectedItem());
	  //�������õ�λ��
	  int check=0,childs=0;
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
		  {
			  check=1;
			  break;
		  }
	  }
	  if(check==1)//�ҵ�
	  {
		    //�����½ڵ�
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
	  if(clicktreex==2)//��2
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
		  MessageBox((_bstr_t)"�Ѿ�����Ϊxxxxx�Ľڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	 }	
	  //�����½ڵ�	
	  treeitem1[treepoint1]="xxxxx";
	  treepoint1++;
	//*********************************************************************
	 HTREEITEM hNew=m_ctltree1.InsertItem((_bstr_t)"xxxxx",1,0,m_ctltree1.GetSelectedItem());
	 }
}


void Step1dialog::OnNMRClickTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	clicktreex=2;//��������2
	CPoint point;
	GetCursorPos(&point); // ��ǰ�������
	CPoint PointInTree = point;
	m_ctltree1.ScreenToClient( &PointInTree);
	CMenu menu,menu2;
	CMenu *ptrMenu,*ptrMenu2;
	CBitmap m_bitmap1,m_bitmap2,m_bitmap3;
	m_bitmap1.LoadBitmap(IDB_BITMAP70);
	m_bitmap2.LoadBitmap(IDB_BITMAP71);
	m_bitmap3.LoadBitmap(IDB_BITMAP72);
	HTREEITEM Item;
	UINT nFlag = TVHT_ONITEM; // ���� Item ���һ�ʱ
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
		  MessageBox((_bstr_t)"�Ѿ�����Ϊ"+strText+"�Ľڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	}
	m_ctltree1.SetItemText(m_ctltree1.GetSelectedItem(),strText);//���ñ༭����ı�Ϊ���
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
	GetCursorPos(&point); // ��ǰ�������
	CPoint PointInTree = point;
	m_ctltree1.ScreenToClient( &PointInTree);
	CMenu menu;
	CMenu *ptrMenu;
	UINT nFlag = TVHT_ONITEM; // ���� Item ���һ�ʱ
	delitem1 =m_ctltree1.HitTest( PointInTree, &nFlag );
	reitem1=m_ctltree1.HitTest( PointInTree, &nFlag );
//	MessageBox((_bstr_t)m_ctltree.GetItemText(delitem));
	*pResult = 0;
}


void Step1dialog::additem(void)
{

	if(addclick==0)
	{
		 MessageBox((_bstr_t)"δѡ������ָ��(U)�����۵ȼ�(V)�޷���ӽڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	}
	if(addclick==1)//��1
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
	      if(havecheck==1)//û�ҵ���=
	     {
		  MessageBox((_bstr_t)"�Ѿ�����Ϊxxxxx�Ľڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	      }	
	  //�����½ڵ�		 
	   zhibiao a;
	   a.DoModal();
	     if(cancle==1)
	    {
		 cancle=1;
		 return;
	     }
	  //�����½ڵ�	
		   //************************************************************************************
	 //�ҵ�Ҫ����ڵ��λ�ø���������Ŀ����һ������жϴ˽ڵ�ı��Ӧ���Ƕ���
	  itemname=m_ctltree.GetItemText(m_ctltree.GetSelectedItem());
	  //�������õ�λ��
	  int check=0,childs;
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
		  {
			  check=1;
			  break;
		  }
	  }
	  if(check==1)//�ҵ�
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		 		 
	  }
	 
	  //�����½ڵ�
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
	  if(addclick==2)//��2
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
		  MessageBox((_bstr_t)"�Ѿ�����Ϊxxxxx�Ľڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	 }	
	  //�����½ڵ�	
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
		 MessageBox((_bstr_t)"δѡ�нڵ��޷�������",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	}
	if(reitem==hroot&&reitem1==hroot1)
	{
		 MessageBox((_bstr_t)"���ڵ��޷�������",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	}
	if(renamecheck==1)
	{
	   m_ctltree.ModifyStyle(NULL,TVS_EDITLABELS);      //���ñ༭���
	   itemoldname=m_ctltree.GetItemText(reitem);
       m_ctltree.EditLabel(reitem);
	   reitem=NULL;
	   return;
	}
	if(renamecheck==2)
	{
	   m_ctltree1.ModifyStyle(NULL,TVS_EDITLABELS);      //���ñ༭���
	   itemoldname=m_ctltree1.GetItemText(reitem1);
       m_ctltree1.EditLabel(reitem1);
	   reitem1=NULL;
	   return;
	}

}


BOOL Step1dialog::PreTranslateMessage(MSG* pMsg)
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
		 m_ctrlTT11.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}


void Step1dialog::OnYijiadderji()//һ���ڵ����Ӷ����ڵ�
{
	// TODO: �ڴ���������������
	 UpdateData(true);
	 if(clicktreex==1)//��1
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
	      if(havecheck==1)//û�ҵ���=
	     {
		  MessageBox((_bstr_t)"�Ѿ�����Ϊxxxxx�Ľڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	      }	
	  //�����½ڵ�		 
	   zhibiao a;
	   a.DoModal();
	     if(cancle==1)
	    {
		 cancle=1;
		 return;
	     }
	  //�����½ڵ�	
		   //************************************************************************************
	 //�ҵ�Ҫ����ڵ��λ�ø���������Ŀ����һ������жϴ˽ڵ�ı��Ӧ���Ƕ���
	  itemname=m_ctltree.GetItemText(m_ctltree.GetSelectedItem());
	  //�������õ�λ��
	  int check=0,childs;
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
		  {
			  check=1;
			  break;
		  }
	  }
	  if(check==1)//�ҵ�
	  {
		  		   //�����½ڵ�
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


void Step1dialog::OnErjiaddsanji()//�����ڵ����������ڵ�
{
	// TODO: �ڴ���������������
	 UpdateData(true);
	 if(clicktreex==1)//��1
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
	      if(havecheck==1)//û�ҵ���=
	     {
		  MessageBox((_bstr_t)"�Ѿ�����Ϊxxxxx�Ľڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	      }	
	  //�����½ڵ�		 
	   zhibiao a;
	   a.DoModal();
	     if(cancle==1)
	    {
		 cancle=1;
		 return;
	     }
	  //�����½ڵ�	
		   //************************************************************************************
	 //�ҵ�Ҫ����ڵ��λ�ø���������Ŀ����һ������жϴ˽ڵ�ı��Ӧ���Ƕ���
	  itemname=m_ctltree.GetItemText(m_ctltree.GetSelectedItem());
	  //�������õ�λ��
	  int check=0,childs;
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
		  {
			  check=1;
			  break;
		  }
	  }
	  if(check==1)//�ҵ�
	  {
		 	  //�����½ڵ�
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


void Step1dialog::OnDelerji()//ɾ�������ڵ�
{
	// TODO: �ڴ���������������
	UpdateData(true);
	if(clicktreex==1)
	{
	if(hroot==m_ctltree.GetSelectedItem())
	{
		MessageBox((_bstr_t)"���ڵ��޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
		return;
	}
	//����û���ӽڵ�
	CString item;
    CString fatheritem,childitem;
    int len,delitempos,biao=0,biao1=0,childs;
	
	for(position=0;position<zhibiaoitempoint;position++)//���������е�λ��
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
		   childs=zhibiaoitemchilds[position];//�ӽڵ����
		   item=zhibiaoitem[position][0];
		  
	  }
	  if(childs!=0)
	  {
		  MessageBox((_bstr_t)"��ָ����ڵͼ�ָ���޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	  }
	   //�ҵ����ڵ�ĸ�����1
	  len=item.GetLength();  //��ȡ��ǰ�е�ֵ�ĳ��ȣ�
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
		   childs=zhibiaoitemchilds[position];//�ӽڵ����
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
        m_ctltree.DeleteItem(m_ctltree.GetSelectedItem());//ɾ����Ľ�
	}
}


void Step1dialog::OnDelsanji()//ɾ�������ڵ�
{
	// TODO: �ڴ���������������
	UpdateData(true);
	if(clicktreex==1)
	{
	if(hroot==m_ctltree.GetSelectedItem())
	{
		MessageBox((_bstr_t)"���ڵ��޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
		return;
	}
//����û���ӽڵ�
	CString item;
    CString fatheritem,childitem;
    int len,delitempos,biao=0,biao1=0,childs;
	
	for(position=0;position<zhibiaoitempoint;position++)//���������е�λ��
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
		   childs=zhibiaoitemchilds[position];//�ӽڵ����
		   item=zhibiaoitem[position][0];
		  
	  }
	  if(childs!=0)
	  {
		  MessageBox((_bstr_t)"��ָ����ڵͼ�ָ���޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	  }
	   //�ҵ����ڵ�ĸ�����1
	  len=item.GetLength();  //��ȡ��ǰ�е�ֵ�ĳ��ȣ�
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
		   childs=zhibiaoitemchilds[position];//�ӽڵ����
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
        m_ctltree.DeleteItem(m_ctltree.GetSelectedItem());//ɾ����Ľ�
	}
}


void Step1dialog::OnRenameerji()//�����������ڵ�
{
	// TODO: �ڴ���������������
	 UpdateData(true);	 
	 if(clicktreex==1)
	 {
       m_ctltree.ModifyStyle(NULL,TVS_EDITLABELS);      //���ñ༭���
	   HTREEITEM hItem=m_ctltree.GetSelectedItem();
	   itemoldname=m_ctltree.GetItemText(hItem);
       m_ctltree.EditLabel(hItem);
	   return;
	 }
}


void Step1dialog::OnRenamesanji()//�����������ڵ�
{
	// TODO: �ڴ���������������
	 UpdateData(true);	 
	 if(clicktreex==1)
	 {
       m_ctltree.ModifyStyle(NULL,TVS_EDITLABELS);      //���ñ༭���
	   HTREEITEM hItem=m_ctltree.GetSelectedItem();
	   itemoldname=m_ctltree.GetItemText(hItem);
       m_ctltree.EditLabel(hItem);
	   return;
	 }
}


void Step1dialog::OnTree2add()
{
	// TODO: �ڴ���������������
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
		  MessageBox((_bstr_t)"�Ѿ�����Ϊxxxxx�Ľڵ�",(_bstr_t)"����", MB_OKCANCEL ); 
			return;
	 }	
	  //�����½ڵ�	
	  treeitem1[treepoint1]="xxxxx";
	  treepoint1++;
	//*********************************************************************
	 HTREEITEM hNew=m_ctltree1.InsertItem((_bstr_t)"xxxxx",1,0,m_ctltree1.GetSelectedItem());
}


void Step1dialog::OnTree2del()
{
	// TODO: �ڴ���������������
	if(hroot1==m_ctltree1.GetSelectedItem())
	{
		MessageBox((_bstr_t)"���ڵ��޷�ɾ��",(_bstr_t)"����", MB_OKCANCEL ); 
		return;
	}
	CString item;
    int len,delitempos;	
    for(position=0;position<treepoint1;position++)//���������е�λ��
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
        m_ctltree1.DeleteItem(m_ctltree1.GetSelectedItem());//ɾ����Ľ��
	
}


void Step1dialog::OnTree2rename()
{
	// TODO: �ڴ���������������
	   m_ctltree1.ModifyStyle(NULL,TVS_EDITLABELS);      //���ñ༭���
	   HTREEITEM hItem=m_ctltree1.GetSelectedItem();
	   itemoldname=m_ctltree1.GetItemText(hItem);
       m_ctltree1.EditLabel(hItem);
	   return;
}


void Step1dialog::OnBnClickedButton1()//���й����½�����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ɾ��ԭ��1
	 HTREEITEM   hItem;
	 int i;
	while(m_ctltree.ItemHasChildren(hroot) )
	{
	     hItem=m_ctltree.GetChildItem(hroot); //��ȡ��һ���ӽ��
		 m_ctltree.DeleteItem(hItem);//ɾ����Ľ��
	}
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
	//�������齨��
	zhibiaoitempoint=0;
	zhibiaoitem[zhibiaoitempoint][0]="0";zhibiaoitem[zhibiaoitempoint][1]="����ָ��(U)";zhibiaoitemchilds[zhibiaoitempoint]=0;zhibiaoitempoint++;
	 h1=m_ctltree.InsertItem((_bstr_t)"ָ��",1,0,hroot);//��Ӷ����ڵ�
	 //************************************************************************************
	 //�ҵ�Ҫ����ڵ��λ�ø���������Ŀ����һ������жϴ˽ڵ�ı��Ӧ���Ƕ���
	  itemname=m_ctltree.GetItemText(hroot);
	  //�������õ�λ��
	  int check=0;//�ҵ����
	  int childs=0;//��¼�ӽڵ���
	  for(position=0;position<zhibiaoitempoint;position++)
	  {
		  if(zhibiaoitem[position][1]==itemname)
			{ 
				check=1;
				break;
		  }
	  }
	  if(check==1)//�ҵ�
	  {
		  itemnumber=zhibiaoitem[position][0];
		  childs=zhibiaoitemchilds[position];
		  zhibiaoitemchilds[position]=childs+1;		  		
	  }
	  //�����½ڵ�
	  CString str;
	  str.Format(_T("%d"),childs++);
	  zhibiaoitem[zhibiaoitempoint][0]=itemnumber+str;
	  zhibiaoitem[zhibiaoitempoint][1]="ָ��";
	  zhibiaoitemchilds[zhibiaoitempoint]=0;
	  zhibiaoitempoint++;
	//****************************************************************************************8
	//ɾ��ԭ��2
	 HTREEITEM   hItem1;
	while(m_ctltree1.ItemHasChildren(hroot1) )
	{
	     hItem1=m_ctltree1.GetChildItem(hroot1); //��ȡ��һ���ӽ��
		 m_ctltree1.DeleteItem(hItem1);//ɾ����Ľ��
	}
	//ɾ��ԭ����
	for(i=0;i<treepoint1;i++)
	{
	  treeitem1[i]="0";				
	}
	treepoint1=0;
	treeitem1[treepoint1]="����(V)";treepoint1++;
	 h2=m_ctltree1.InsertItem((_bstr_t)"����",1,0,hroot1);//��Ӷ����ڵ�
	treeitem1[treepoint1]="����"; treepoint1++;	
	
}


void Step1dialog::OnBnClickedButton28()//save
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	treesave=1;
		int i,j,k,yiji=0,erji=0,sanji=0,m,n,b;
	    CString str;
		if(m_ctltree.ItemHasChildren(hroot))//�жϽ���Ƿ����ӽ��
			{
				
				Ftree[0]=m_ctltree.GetItemText(hroot);
				//�Ҵ˸��ڵ��Ӧ�ж���һ��
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==Ftree[0])
		                        {
									b= zhibiaoitemchilds[position];
			                          break;
		                         }
							}
							str.Format("%d",b);
							Ftree[0]="0"+Ftree[0]+"/"+str;//��
			
				for(i=0;i<b-1;i++)//��1
	            {
                   if(yiji==0)
				   {
                   yijiitem=m_ctltree.GetChildItem(hroot); //��ȡ��һ���ӽ��
				   Ftree[Ftreenum]=m_ctltree.GetItemText(yijiitem);
				   //�Ҵ�һ���ڵ��Ӧ�ж��ٶ���
							for(position=0;position<zhibiaoitempoint;position++)
	                        {
								if(zhibiaoitem[position][1]==Ftree[Ftreenum])
		                        {
									n= zhibiaoitemchilds[position];
			                          break;
		                         }
							}
					str.Format("%d",n);
					Ftree[Ftreenum]="1"+Ftree[Ftreenum]+"/"+str;Ftreenum++;//һ��
				   //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&2ji
				   for(j=0;j<n-1;j++)//�ڶ����ӽڵ�
				   {
					   if(erji==0)
					   {
					    erjiitem=m_ctltree.GetChildItem(yijiitem);
					    Ftree[Ftreenum]=m_ctltree.GetItemText(erjiitem);

						//�Ҵ˶����ڵ��Ӧ�ж�������
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
						  for(k=0;k<m-1;k++)//�������ӽڵ�
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//��ȡ��һ���ֵܽ����
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
						//�Ҵ˶����ڵ��Ӧ�ж�������
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
						  for(k=0;k<m-1;k++)//�������ӽڵ�
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//��ȡ��һ���ֵܽ����
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
				   //�Ҵ�һ���ڵ��Ӧ�ж��ٶ���
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
				   for(j=0;j<n-1;j++)//�ڶ����ӽڵ�
				   {
					   if(erji==0)
					   {
					    erjiitem=m_ctltree.GetChildItem(yijiitem);
					    Ftree[Ftreenum]=m_ctltree.GetItemText(erjiitem);
						//�Ҵ˶����ڵ��Ӧ�ж�������
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
						  for(k=0;k<m-1;k++)//�������ӽڵ�
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//��ȡ��һ���ֵܽ����
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
						//�Ҵ˶����ڵ��Ӧ�ж�������
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
						  for(k=0;k<m-1;k++)//�������ӽڵ�
				         {
							if(sanji==0)
							{
							sanjiitem=m_ctltree.GetChildItem(erjiitem);
							Ftree[Ftreenum]="3"+m_ctltree.GetItemText(sanjiitem);Ftreenum++;
							sanji=1;
							}
							if(sanji==1)
							{
							sanjiitem=m_ctltree.GetNextSiblingItem(sanjiitem);//��ȡ��һ���ֵܽ����
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
		//�������
		CString szFileFilter=(_bstr_t)"�ı�(*.txt)|*.txt|";
	CString szFileExt=(_bstr_t)"txt";//��չ��Ϊtxt
	CFileDialog dlg(false,szFileExt,NULL,OFN_HIDEREADONLY,szFileFilter);
	if(dlg.DoModal()==IDOK)
	{
		CStdioFile File;		
		File.Open(dlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
		char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
        setlocale( LC_CTYPE, "chs" );//�趨
		for(position=0;position<Ftreenum;position++)
	    {
			File.WriteString((_bstr_t)Ftree[position]+(_bstr_t)"\r\n");//����д��	
	    }
		

        File.WriteString((_bstr_t)"Finish");
        setlocale( LC_CTYPE, old_locale );
        free( old_locale );//��ԭ�����趨
		File.Close();
	}
}


void Step1dialog::OnBnClickedButton27()//tip
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 MessageBox((_bstr_t)"1.����ָ��(U)������(V)������ɺ��뱣��",(_bstr_t)"��ʾ", MB_OK ); 
}
