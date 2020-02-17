#pragma once



// CbankDlg 窗体视图
#define INTEREST_1 1.05 //存款利息
#define INTEREST_2 1.1	//贷款利息


class CbankDlg : public CFormView
{
	DECLARE_DYNCREATE(CbankDlg)

protected:
	CbankDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CbankDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_BANK };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	// 下拉框
	CComboBox m_combo;
	// 欠款num
	int m_Arrears;
	// 存款
	int m_deposit;
	// 消费
	int m_mconsumption;
	// 贷款
	int m_loan;
	// 还款
	int m_repayment;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton6();
private:
	// 额度
	int m_quota;
public:
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
private:
	// 增加
	int m_zj;
public:
	afx_msg void OnBnClickedButton10();
};


