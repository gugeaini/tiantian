// CSellDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC_销售管理系统.h"
#include "CSellDlg.h"
#include"InfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(DIALOG_SELL)
	, m_left(0)
	, m_price(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT2, m_left);
	DDX_Text(pDX, IDC_EDIT3, m_price);
	DDX_Text(pDX, IDC_EDIT4, m_num);
	DDX_Text(pDX, IDC_EDIT7, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSellDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSellDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//初始化下拉框
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name.c_str()));//放入名字
	}
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();//获取当前行

	CString str;
	m_combo.GetLBText(index, str);//获取商品名称
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (str == CString(it->name.c_str()))
		{
			m_left = it->num;
			m_price = it->price;
			UpdateData(FALSE);
		}
	}

}


void CSellDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_num <= 0)
	{
		MessageBox(TEXT("购买个数必须大于0"));
		return;
	}
	if (m_num > m_left)
	{
		MessageBox(TEXT("购买个数小于库存量"));
		return;
	}

	int index = m_combo.GetCurSel();//获取当前行
	CString str;
	m_combo.GetLBText(index, str);//获取商品名称
	CInfoFile file;
	file.ReadDocline();

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (str == CString(it->name.c_str()))//到当前信息位置
		{
			CString info;
			m_left -= m_num;
			it->num = m_left;
			MessageBox(_T("购买成功!"));
			if (m_left == 0)
			{
				info.Format(TEXT("商品：%s 库存不足，请及时添加"), str);
				MessageBox(info);
			}
			info.Format(TEXT("---购买信息---\r\n 商品：%s \r\n 单价：%d \r\n 总价：%d \r\n"),str,m_price,m_price*m_num);
			m_sellInfo = info;

			m_num = 0;
		}
	}
	file.WriteDocline();
	UpdateData(FALSE);

}


void CSellDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_num = 0;
	m_combo.SetCurSel(0);
	m_sellInfo.Empty();
	UpdateData(FALSE);
	OnCbnSelchangeCombo1();
}
