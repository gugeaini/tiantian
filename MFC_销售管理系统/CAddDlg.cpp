// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC_销售管理系统.h"
#include "CAddDlg.h"
#include"InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(DIALOG_ADD)
	, m_ku(0)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
	, m_id2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Text(pDX, IDC_EDIT1, m_ku);
	DDX_Text(pDX, IDC_EDIT2, m_price1);
	DDX_Text(pDX, IDC_EDIT3, m_num1);
	DDX_Text(pDX, IDC_EDIT4, m_name2);
	DDX_Text(pDX, IDC_EDIT5, m_price2);
	DDX_Text(pDX, IDC_EDIT6, m_num2);
	DDX_Text(pDX, IDC_EDIT8, m_id2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAddDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAddDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAddDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//加载商品
	//初始化下拉框
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo1.AddString(CString(it->name.c_str()));//放入名字
	}
	m_combo1.SetCurSel(0);//默认显示第一个
	OnCbnSelchangeCombo1();//手动调用

}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo1.GetCurSel();
	CString str;
	m_combo1.GetLBText(index,str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (str == (CString)it->name.c_str())//找到当前商品
		{
			//更新库存单价库存
			m_ku = it->num;
			m_price1 = it->price;
			UpdateData(FALSE);
		}
	}
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	//添加商品
	UpdateData(TRUE);
	
	if (m_num1 <= 0)
	{
		MessageBox(_T("添加库存必须大于0"));
		m_num1 = 0;//清空
		return;
	}
	int index = m_combo1.GetCurSel();
	CString str;
	m_combo1.GetLBText(index, str);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (str == (CString)it->name.c_str())//找到当前商品
		{//进行添加商品
			it->num += m_num1;
			file.WriteDocline();
			m_num1 = 0;
			UpdateData(FALSE);
			OnCbnSelchangeCombo1();
		}
	}
	MessageBox(_T("添加成功！"));

}


void CAddDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_num1 = 0;
	UpdateData(FALSE);
	m_combo1.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_name2.IsEmpty() || m_num2 == 0 || m_price2 == 0 || m_id2 < 0)
	{
		MessageBox(TEXT("输入格式有误,请检查再输入"));
		return;
	}
	
	CInfoFile file;
	file.ReadDocline();//先读取文件商品
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)//判断是否已经存在商品
	{
		if (m_name2 == (CString)it->name.c_str())//找到当前商品
		{
			MessageBox(_T("商品已经存在，无需重新添加"));
			return;
		}
		if (m_id2 == it->id)
		{
			MessageBox(_T("商品ID号已经存在，请换一个ID编号"));
			return;
		}
	}
	//检测通过
	//开始添加
	file.Addline(m_id2,m_name2, m_num2, m_price2);
	file.WriteDocline();//新数据写入文件
	MessageBox(_T("添加新商品成功"));
	//把新商品添加到下拉框中
	m_combo1.InsertString(0, m_name2);
	m_combo1.SetCurSel(0);
	OnCbnSelchangeCombo1();//手动更新

	//清空新商品栏
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	m_id2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空新商品栏
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}
