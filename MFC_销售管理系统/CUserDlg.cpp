// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC_销售管理系统.h"
#include "CUserDlg.h"
#include"InfoFile.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwg(_T(""))
	, m_surePwg(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwg);
	DDX_Text(pDX, IDC_EDIT4, m_surePwg);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserDlg::OnBnClickedButton4)
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


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	
	//初始化 身份 用户名显示
	CString name;
	CString pwd;
	m_user = TEXT("销售部经理");
	CInfoFile file;
	file.ReadLogin(name, pwd);
	m_name = name;
	UpdateData(FALSE);

}


void CUserDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_newPwg.IsEmpty() || m_surePwg.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空！"));
		return;
	}

	if (m_newPwg != m_surePwg)
	{
		MessageBox(TEXT("两次密码必须一致！"));
		return;
	}
	CString name;
	CString pwd;
	CInfoFile file;
	file.ReadLogin(name, pwd);

	if (m_newPwg == pwd)
	{
		MessageBox(TEXT("新密码与旧密码一样，无法修改！"));
		return;
	}
	//修改密码
	CStringA temName;
	CStringA temPwd;
	temPwd = m_newPwg;
	temName = name;
	file.WritePwd(temName.GetBuffer(), temPwd.GetBuffer());
	MessageBox(TEXT("密码修改成功"));
	//清空输入内容
	m_newPwg.Empty();
	m_surePwg.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	//清空输入内容
	m_newPwg.Empty();
	m_surePwg.Empty();
	UpdateData(FALSE);
}
