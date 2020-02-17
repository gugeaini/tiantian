// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC_销售管理系统.h"
#include "CInfoDlg.h"

#include"InfoFile.h"


// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(DIALOG_INFO)
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg 消息处理程序


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//设置风格 整行选中 加入网格线
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//插入表头
	CString str[] = { TEXT("商品ID"), TEXT("商品名称"), TEXT("商品价格"),TEXT("库存数量")};
	for (int i = 0; i < sizeof(str)/sizeof(str[0]); i++)
	{
		m_list.InsertColumn(i, str[i], LVCFMT_CENTER, 80);
	}
	CInfoFile file;
	file.ReadDocline();
	int i = 0;
	int contt = 1;
	CString strtem;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		contt = 1;

		strtem.Format(_T("%d"),it->id);
		m_list.InsertItem(i, strtem);//输入ID
		
		m_list.SetItemText(i, contt++, (CString)it->name.c_str());//输入名称
		strtem.Format(_T("%d"),it->price);
		m_list.SetItemText(i, contt++,strtem);//输入价格
		strtem.Format(_T("%d"),it->num);
		m_list.SetItemText(i, contt, strtem);//输入库存
		i++;
	}

}
