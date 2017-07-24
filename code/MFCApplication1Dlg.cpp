
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "BFS.h"
#include "OS.h"
#include "ASTAR.h"
#include "stdio.h"

#include <string>
#include <algorithm>
#include <vector>

using std::vector;
using std::random_shuffle;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int start[3][3] = { 2,8,3,1,6,4,7,0,5 };
int target[3][3] = { 1,2,3,8,0,4,7,6,5 };

int algo;//算法标识
int random=-1;//初始化模式
bool init=false;//初始化标识
int success=0;

BFS bfs;
OS os;
ASTAR astar;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
	ON_STN_CLICKED(IDC_STATIC5, &CMFCApplication1Dlg::OnStnClickedStatic5)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCApplication1Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCApplication1Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMFCApplication1Dlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMFCApplication1Dlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO6, &CMFCApplication1Dlg::OnBnClickedRadio6)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;



		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

int randEx()
{
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);

	return rand();
}

int loadImg(int i)
{
	switch (i)
	{
	case 0:return IDB_BITMAP9;
	case 1:return IDB_BITMAP1;
	case 2:return IDB_BITMAP2;
	case 3:return IDB_BITMAP3;
	case 4:return IDB_BITMAP4;
	case 5:return IDB_BITMAP5;
	case 6:return IDB_BITMAP6;
	case 7:return IDB_BITMAP7;
	case 8:return IDB_BITMAP8;
	}
}

void CMFCApplication1Dlg::OnBnClickedButton1() ///初始化
{
	// TODO: Add your control notification handler code here
	if (random == -1) {
		MessageBox(_T("请选择初始化模式"),_T("warning"), MB_OK);
	}
	else {
		int i, j;
		int k = 0;
		int temp[9];
		vector<int> vi1, vi2;

		init = true;

		for (i = 0; i < 9; i++)
			vi1.push_back(i);
		random_shuffle(vi1.begin(), vi1.end());  //产生随机序列


		if (random == 1) {
			for (i = 0; i < 3; i++) //产生初始状态
				for (j = 0; j < 3; j++)
				{
					start[i][j] = vi1[k++];
				}
		}
		else if (random == 0) {
			start[0][0] = 2; start[0][1] = 8; start[0][2] = 3;
			start[1][0] = 1; start[1][1] = 6; start[1][2] = 4; 
			start[2][0] = 7; start[2][1] = 0; start[2][2] = 5; 
		}


		CBitmap bitmap[9];
		for (i = 0; i < 9; i++)
			bitmap[i].LoadBitmapW(loadImg(i));
		CStatic *p = (CStatic *)GetDlgItem(IDC_STATIC3);
		p->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p->SetBitmap(bitmap[start[0][0]]);

		CStatic *p1 = (CStatic *)GetDlgItem(IDC_STATIC4);
		p1->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p1->SetBitmap(bitmap[start[0][1]]);

		CStatic *p2 = (CStatic *)GetDlgItem(IDC_STATIC5);
		p2->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p2->SetBitmap(bitmap[start[0][2]]);

		CStatic *p3 = (CStatic *)GetDlgItem(IDC_STATIC6);
		p3->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p3->SetBitmap(bitmap[start[1][0]]);

		CStatic *p4 = (CStatic *)GetDlgItem(IDC_STATIC7);
		p4->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p4->SetBitmap(bitmap[start[1][1]]);

		CStatic *p5 = (CStatic *)GetDlgItem(IDC_STATIC8);
		p5->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p5->SetBitmap(bitmap[start[1][2]]);

		CStatic *p6 = (CStatic *)GetDlgItem(IDC_STATIC9);
		p6->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p6->SetBitmap(bitmap[start[2][0]]);

		CStatic *p7 = (CStatic *)GetDlgItem(IDC_STATIC10);
		p7->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p7->SetBitmap(bitmap[start[2][1]]);

		CStatic *p8 = (CStatic *)GetDlgItem(IDC_STATIC11);
		p8->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p8->SetBitmap(bitmap[start[2][2]]);

		CBitmap bitmap2[9];
		for (i = 0; i < 9; i++)
			bitmap2[i].LoadBitmapW(loadImg(i));
		CStatic *p11 = (CStatic *)GetDlgItem(IDC_STATIC30);
		p11->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p11->SetBitmap(bitmap2[target[0][0]]);

		CStatic *p12 = (CStatic *)GetDlgItem(IDC_STATIC12);
		p12->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p12->SetBitmap(bitmap2[target[0][1]]);

		CStatic *p13 = (CStatic *)GetDlgItem(IDC_STATIC13);
		p13->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p13->SetBitmap(bitmap2[target[0][2]]);

		CStatic *p14 = (CStatic *)GetDlgItem(IDC_STATIC14);
		p14->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p14->SetBitmap(bitmap2[target[1][0]]);

		CStatic *p15 = (CStatic *)GetDlgItem(IDC_STATIC15);
		p15->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p15->SetBitmap(bitmap2[target[1][1]]);

		CStatic *p16 = (CStatic *)GetDlgItem(IDC_STATIC16);
		p16->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p16->SetBitmap(bitmap2[target[1][2]]);

		CStatic *p17 = (CStatic *)GetDlgItem(IDC_STATIC17);
		p17->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p17->SetBitmap(bitmap2[target[2][0]]);

		CStatic *p18 = (CStatic *)GetDlgItem(IDC_STATIC18);
		p18->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p18->SetBitmap(bitmap2[target[2][1]]);

		CStatic *p19 = (CStatic *)GetDlgItem(IDC_STATIC19);
		p19->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		p19->SetBitmap(bitmap2[target[2][2]]);

	}
}




void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCApplication1Dlg::OnStnClickedStatic5()
{
	// TODO: Add your control notification handler code here
}


void CMFCApplication1Dlg::OnBnClickedButton2() //开始运行算法
{
	CString str;
	int number;
	char buffer[100];

	if (!init)
	{
		MessageBox(_T("请先进行初始化操作"), _T("warning"), MB_OK);
	}
	else
	{
	switch (algo)
		{
		case 1:
			//str = "计算成功";			
			number = bfs.Algorithm(start, target);

			if (number!=-1)
			{
				sprintf_s(buffer, "计算成功，总节点数为%d", number);
				success = 1;
				str = buffer;
				MessageBox(str,_T(""), MB_OK);
			}
				
			else
			{
				str = "计算失败";
				MessageBox(str, _T(""), MB_OK);
			}
			break;
		case 2:
			number = os.Algorithm(start, target);

			if (number != -1)
			{
				sprintf_s(buffer, "计算成功，总节点数为%d", number);
				success = 1;
				str = buffer;
				MessageBox(str, _T(""), MB_OK);
			}

			else
			{
				str = "计算失败";
				MessageBox(str, _T(""), MB_OK);
			}
			break;
		case 3:
			number = astar.Algorithm(start, target);

			if (number != -1)
			{
				sprintf_s(buffer, "计算成功，总节点数为%d", number);
				success = 1;
				str = buffer;
				MessageBox(str, _T(""), MB_OK);
			}

			else
			{
				str = "计算失败";
				MessageBox(str, _T(""), MB_OK);
			}
			break;
		default:
			MessageBox(_T("请选择算法"),_T("warning"), MB_OK);
			break;
		}
	}
	
}


void CMFCApplication1Dlg::OnBnClickedButton3() //显示结果
{
	BFS::node *display1;
	OS::node *display2;
	ASTAR::node *display3;
	
	CBitmap bitmap[9];
	CStatic *p = (CStatic *)GetDlgItem(IDC_STATIC31);
	CStatic *p1 = (CStatic *)GetDlgItem(IDC_STATIC20);
	CStatic *p2 = (CStatic *)GetDlgItem(IDC_STATIC21);
	CStatic *p3 = (CStatic *)GetDlgItem(IDC_STATIC22);
	CStatic *p4 = (CStatic *)GetDlgItem(IDC_STATIC23);
	CStatic *p5 = (CStatic *)GetDlgItem(IDC_STATIC24);
	CStatic *p6 = (CStatic *)GetDlgItem(IDC_STATIC25);
	CStatic *p7 = (CStatic *)GetDlgItem(IDC_STATIC26);
	CStatic *p8 = (CStatic *)GetDlgItem(IDC_STATIC27);

	p->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	p1->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	p2->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	p3->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	p4->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	p5->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	p6->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	p7->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	p8->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);


	for (int i = 0; i < 9; i++)
		bitmap[i].LoadBitmapW(loadImg(i));

	switch (algo) {
		case 1:display1 = bfs.showResult();
			if (success)
			{
				while (display1 != NULL)
				{
					p->SetBitmap(bitmap[display1->info[0][0]]);
					p1->SetBitmap(bitmap[display1->info[0][1]]);
					p2->SetBitmap(bitmap[display1->info[0][2]]);
					p3->SetBitmap(bitmap[display1->info[1][0]]);
					p4->SetBitmap(bitmap[display1->info[1][1]]);
					p5->SetBitmap(bitmap[display1->info[1][2]]);
					p6->SetBitmap(bitmap[display1->info[2][0]]);
					p7->SetBitmap(bitmap[display1->info[2][1]]);
					p8->SetBitmap(bitmap[display1->info[2][2]]);

					display1 = display1->next;

					for (int time = 0; time < 10000; time++)
						for (int time2 = 0; time2 < 11000; time2++);
				}

			}
			break;
		case 2:display2 = os.showResult();
			if (success){
				while (display2 != NULL){
					p->SetBitmap(bitmap[display2->info[0][0]]);
					p1->SetBitmap(bitmap[display2->info[0][1]]);
					p2->SetBitmap(bitmap[display2->info[0][2]]);
					p3->SetBitmap(bitmap[display2->info[1][0]]);
					p4->SetBitmap(bitmap[display2->info[1][1]]);
					p5->SetBitmap(bitmap[display2->info[1][2]]);
					p6->SetBitmap(bitmap[display2->info[2][0]]);
					p7->SetBitmap(bitmap[display2->info[2][1]]);
					p8->SetBitmap(bitmap[display2->info[2][2]]);

					display2 = display2->next;

					for (int time = 0; time < 10000; time++)
						for (int time2 = 0; time2 < 11000; time2++);
				}

			}
			break;
		case 3:display3 = astar.showResult();
			if (success) {
				while (display3 != NULL) {
					p->SetBitmap(bitmap[display3->info[0][0]]);
					p1->SetBitmap(bitmap[display3->info[0][1]]);
					p2->SetBitmap(bitmap[display3->info[0][2]]);
					p3->SetBitmap(bitmap[display3->info[1][0]]);
					p4->SetBitmap(bitmap[display3->info[1][1]]);
					p5->SetBitmap(bitmap[display3->info[1][2]]);
					p6->SetBitmap(bitmap[display3->info[2][0]]);
					p7->SetBitmap(bitmap[display3->info[2][1]]);
					p8->SetBitmap(bitmap[display3->info[2][2]]);

					display3 = display3->next;

					for (int time = 0; time < 10000; time++)
						for (int time2 = 0; time2 < 11000; time2++);
				}

			}
			break;
	}
	
	// TODO: Add your control notification handler code here
}


void CMFCApplication1Dlg::OnBnClickedRadio1()//宽度优先搜索
{
	algo = 1;
}


void CMFCApplication1Dlg::OnBnClickedRadio2()//有序搜索
{
	algo = 2;
}


void CMFCApplication1Dlg::OnBnClickedRadio3()//A*算法
{
	algo = 3;
}


void CMFCApplication1Dlg::OnBnClickedRadio4()//随机产生初始状态
{
	random = 1;
}




void CMFCApplication1Dlg::OnBnClickedRadio6()//产生固定初始状态
{
	random = 0;
}
