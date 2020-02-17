// CDelDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC_销售管理系统.h"
#include "CDelDlg.h"
#include "InfoFile.h"


// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(DIALOG_DEL)
	, m_num(0)
	, m_ku(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_num);
	DDX_Text(pDX, IDC_EDIT2, m_ku);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDelDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON8, &CDelDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON3, &CDelDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDelDlg 诊断

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//加载商品
	//初始化下拉框
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name.c_str()));//放入名字
		m_combo2.AddString(CString(it->name.c_str()));
	}
	m_combo.SetCurSel(0);//默认显示第一个
	m_combo2.SetCurSel(0);//默认显示第一个
	OnCbnSelchangeCombo1();//手动调用

}


void CDelDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString str;
	m_combo.GetLBText(index, str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (str == (CString)it->name.c_str())//找到当前商品
		{
			//更新库存单价库存
			m_ku = it->num;
			UpdateData(FALSE);
		}
	}
}


void CDelDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_num <= 0)
	{
		MessageBox(_T("必须填写个数大于0"));
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
			if (m_num > it->num)
			{
				MessageBox(TEXT("减少量必须小于库存量"));
				return;
			}
			it->num -= m_num;
		}
	}
	//清空输入栏
	m_num = 0;
	file.WriteDocline();//写入新信息
	OnCbnSelchangeCombo1();//手动调用
}


void CDelDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_num = 0;
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();//手动调用
}


void CDelDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index = m_combo2.GetCurSel();
	CString str;
	m_combo2.GetLBText(index,str);
	CInfoFile file;
	file.ReadDocline();//读取
	file.Dleline(str);//删除
	file.WriteDocline();//写入

	m_combo2.DeleteString(index);
	m_combo.DeleteString(index);
	m_combo2.SetCurSel(0);
	m_combo.SetCurSel(0);
	UpdateData(FALSE);
	OnCbnSelchangeCombo1();
	MessageBox(TEXT("商品下架成功"));
	
}


void CDelDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_combo2.SetCurSel(0);
	OnCbnSelchangeCombo1();
}
