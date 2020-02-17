
// 大富翁银行系统View.cpp: C大富翁银行系统View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "大富翁银行系统.h"
#endif

#include "大富翁银行系统Doc.h"
#include "大富翁银行系统View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C大富翁银行系统View

IMPLEMENT_DYNCREATE(C大富翁银行系统View, CView)

BEGIN_MESSAGE_MAP(C大富翁银行系统View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// C大富翁银行系统View 构造/析构

C大富翁银行系统View::C大富翁银行系统View() noexcept
{
	// TODO: 在此处添加构造代码

}

C大富翁银行系统View::~C大富翁银行系统View()
{
}

BOOL C大富翁银行系统View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C大富翁银行系统View 绘图

void C大富翁银行系统View::OnDraw(CDC* /*pDC*/)
{
	C大富翁银行系统Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// C大富翁银行系统View 打印

BOOL C大富翁银行系统View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C大富翁银行系统View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void C大富翁银行系统View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// C大富翁银行系统View 诊断

#ifdef _DEBUG
void C大富翁银行系统View::AssertValid() const
{
	CView::AssertValid();
}

void C大富翁银行系统View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C大富翁银行系统Doc* C大富翁银行系统View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C大富翁银行系统Doc)));
	return (C大富翁银行系统Doc*)m_pDocument;
}
#endif //_DEBUG


// C大富翁银行系统View 消息处理程序
