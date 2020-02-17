// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "大富翁银行系统.h"
#include "CUserDlg.h"
#include <string>
#include "InfoFile.h"
#include "MainFrm.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_newName(_T(""))
	, m_gold(0)
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_newName);
	DDX_Text(pDX, IDC_EDIT2, m_gold);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CUserDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &CUserDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnBnClickedButton1()
{
	srand((unsigned int)time(NULL));
	// TODO: 在此添加控件通知处理程序代码
	std::string name[3] = { "小米普陀","超级火鸡","爱丽丝" };
	int i = rand() % 3;
	m_newName = name[i].c_str();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	srand((unsigned int)time(NULL));
	int i = (rand() % 5) * 1000 + 10000;
	m_gold = i;
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_newName.IsEmpty() || m_gold <= 0)
	{
		MessageBox(TEXT("没有输入正确"));
		return;
	}
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (m_newName == (CString)it->name.c_str())
		{
			MessageBox(_T("用户已经存在，请更换一个ID"));
			return;
		}
	}
	
	file.Addline(m_newName, 1, m_gold);
	file.WriteDocline();
	
	MessageBox(TEXT("创建成功"));
	m_newName.Empty();
	m_gold = 0;
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_newName.Empty();
	m_gold = 0;
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CInfoFile file;
	file.WriteDocline();
	MessageBox(_T("新游戏开启成功"));
}


void CUserDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
}
