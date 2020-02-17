// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "大富翁银行系统.h"
#include "CSelectView.h"
#include "MainFrm.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_treeCtrl = &GetTreeCtrl();

	//创建图标

	//准备资源
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON2);

	//加载图片进入框架
	m_imageList.Create(30, 30, ILC_COLOR32, 1, 1);
	m_imageList.Add(icon);

	//安装图标
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//添加节点
	m_treeCtrl->InsertItem(_T("首页"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("银行"), 0, 0, NULL);
	



}


void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM item=m_treeCtrl->GetSelectedItem();
	CString str=m_treeCtrl->GetItemText(item);

	if (str == TEXT("首页"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	}
	if (str == TEXT("银行"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}

	*pResult = 0;
}
