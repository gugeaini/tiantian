// CbankDlg.cpp: 实现文件
//

#include "pch.h"
#include "大富翁银行系统.h"
#include "CbankDlg.h"
#include "InfoFile.h"


// CbankDlg

IMPLEMENT_DYNCREATE(CbankDlg, CFormView)

CbankDlg::CbankDlg()
	: CFormView(DIALOG_BANK)
	, m_Arrears(0)
	, m_deposit(0)
	, m_mconsumption(0)
	, m_loan(0)
	, m_repayment(0)
	, m_quota(0)
	, m_zj(0)
{

}

CbankDlg::~CbankDlg()
{
}

void CbankDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT5, m_Arrears);
	DDX_Text(pDX, IDC_EDIT1, m_deposit);
	DDX_Text(pDX, IDC_EDIT2, m_mconsumption);
	DDX_Text(pDX, IDC_EDIT3, m_loan);
	DDX_Text(pDX, IDC_EDIT4, m_repayment);
	DDX_Text(pDX, IDC_EDIT6, m_quota);
	DDX_Text(pDX, IDC_EDIT7, m_zj);
}

BEGIN_MESSAGE_MAP(CbankDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CbankDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CbankDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CbankDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &CbankDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CbankDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &CbankDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CbankDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON10, &CbankDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CbankDlg 诊断

#ifdef _DEBUG
void CbankDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CbankDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CbankDlg 消息处理程序


void CbankDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name.c_str()));
	}
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

}


void CbankDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString str;
	m_combo.GetLBText(index, str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == str)
		{
			m_Arrears =it->num;
			m_deposit = it->price;
			m_quota = it->quota;
			break;
		}
	}
	UpdateData(FALSE);
}


void CbankDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_mconsumption <= 0)
	{
		MessageBox(_T("消费不可以小于0"));
		return;
	}

	int index = m_combo.GetCurSel();
	CString str;
	m_combo.GetLBText(index, str);

	CInfoFile file;
	file.ReadDocline();

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == str)
		{
			if (m_mconsumption > it->price)
			{
				MessageBox(_T("消费不可以大于存款,请申请贷款"));
				return;
			}
		
			it->price -= m_mconsumption;
			break;
		}
	}

	file.WriteDocline();
	m_mconsumption = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CbankDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_mconsumption = 0;
	UpdateData(FALSE);
}


void CbankDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if ((m_Arrears + m_loan) > m_quota || m_loan <= 0)
	{
		MessageBox(_T("输入内容不合法"));
		return;
	}

	int index = m_combo.GetCurSel();
	CString str;
	m_combo.GetLBText(index, str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == str)
		{
			it->num += m_loan;
			m_Arrears += m_loan;
			break;
		}
	}
	file.WriteDocline();
	m_loan = 0;
	m_repayment = 0;
	UpdateData(FALSE);
}


void CbankDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_Arrears == 0)
	{
		MessageBox(_T("无欠款，不需要还"));
		return;
	}

	if (m_repayment <= 0)
	{
		MessageBox(_T("输入内容不合法"));
		return;
	}
	if (m_repayment > m_Arrears)
	{
		MessageBox(_T("自动调整最大还款金额"));
		m_repayment = m_Arrears;
	}
	int index = m_combo.GetCurSel();
	CString str;
	m_combo.GetLBText(index, str);


	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (str == (CString)it->name.c_str())
		{
			m_Arrears -= m_repayment;
			it->num -= m_repayment;
			break;
		}
	}

	file.WriteDocline();
	m_repayment = 0;
	m_loan = 0;
	UpdateData(FALSE);

}


void CbankDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString str;
	m_combo.GetLBText(index, str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (str == (CString)it->name.c_str())
		{
			it->price += 1000;
			it->num *= (INTEREST_2 + 0.01 * (rand() % 5));
			it->price *= (INTEREST_1 + 0.01 * (rand() % 5));
			it->quota *= (INTEREST_2 + 0.01 * (rand() % 5));
			m_Arrears = it->num;
			m_deposit = it->price;
			m_quota = it->quota;
			break;
		}
	}

	file.WriteDocline();
	UpdateData(FALSE);

}


void CbankDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString str;
	m_combo.GetLBText(index, str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (str == (CString)it->name.c_str())
		{
			it->price += 2000;
			it->num *= (INTEREST_2 + 0.01 * (rand() % 5));
			it->price *= (INTEREST_1 + 0.01 * (rand() % 5));
			it->quota *= (INTEREST_2 + 0.01 * (rand() % 5));
			m_Arrears = it->num;
			m_deposit = it->price;
			m_quota = it->quota;
			break;
		}
	}

	file.WriteDocline();
	UpdateData(FALSE);
}


void CbankDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_zj <= 0)
	{
		MessageBox(_T("小于0不行"));
		return;
	}

	int index = m_combo.GetCurSel();
	CString str;
	m_combo.GetLBText(index, str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (str == (CString)it->name.c_str())
		{
			it->price += m_zj;
			m_zj = 0;
			m_deposit = it->price;
			break;
		}
	}

	file.WriteDocline();
	UpdateData(FALSE);
}
