
// 大富翁银行系统View.h: C大富翁银行系统View 类的接口
//

#pragma once


class C大富翁银行系统View : public CView
{
protected: // 仅从序列化创建
	C大富翁银行系统View() noexcept;
	DECLARE_DYNCREATE(C大富翁银行系统View)

// 特性
public:
	C大富翁银行系统Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C大富翁银行系统View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 大富翁银行系统View.cpp 中的调试版本
inline C大富翁银行系统Doc* C大富翁银行系统View::GetDocument() const
   { return reinterpret_cast<C大富翁银行系统Doc*>(m_pDocument); }
#endif

