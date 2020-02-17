// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC_销售管理系统.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include"InfoFile.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwg(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwg);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//控件值导入变量
	if (m_user.IsEmpty() || m_pwg.IsEmpty())
	{
		MessageBox(TEXT("用户名或密码不能为空"));
		return;
	}
	CString user;
	CString pwg;

	CInfoFile file;
	file.ReadLogin(user, pwg);//读取登录信息
	if (m_user == user)
	{
		if (m_pwg == pwg)
		{
			CDialog::OnOK();//账号密码正常 关闭登录窗口
		}
		else
		{
			MessageBox(TEXT("密码错误"));
		}
	}
	else
	{
		MessageBox(TEXT("用户名错误"));
	}


}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//默认添加账户名
	CString user;
	CString pwg;
	CInfoFile file;
	file.ReadLogin(user, pwg);
	m_user = user;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}
