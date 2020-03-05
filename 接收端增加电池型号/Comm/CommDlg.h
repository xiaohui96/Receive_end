
// CommDlg.h : 头文件
//

#pragma once
#include "afxwin.h"



// CCommDlg 对话框
class CCommDlg : public CDialogEx
{
// 构造
public:
	CCommDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CBrush m_brush;  
    COLORREF m_color,m_textcolor; 

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRecvDataHandler(WPARAM wParam, LPARAM lParam);  
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonSend1();
	afx_msg void OnBnClickedButtonSend2();
	afx_msg void OnBnClickedButtonSend3();
	afx_msg void OnBnClickedButtonSend4();
	afx_msg void OnBnClickedButtonSend5();
	afx_msg void OnBnClickedButtonSend6();
	afx_msg void OnBnClickedButtonSend7();
	afx_msg void OnBnClickedButtonSend8();
private:
	void toggleButtonStatus(BOOL isopen=TRUE);
	int GetComList_Reg();
	void printStatus(CString str);
	void printRecvStatus(CString str);
	void  CCommDlg::printRecvVot_Trans_Buck_In_Status(CString str);
	void  CCommDlg::printRecv_Battery_Type_Status(CString str);
	void  CCommDlg::printRecv_BIKE_ID_Status(CString str);
	void  CCommDlg::printRecv_Output_Voltage(CString str);
	void  CCommDlg::printRecv_Output_Current(CString str);
	void  CCommDlg::printRecv_Input_Voltage(CString str);
	void  CCommDlg::printRecv_Duty_Radio(CString str);
	void  CCommDlg::printRecv_Buck_Mode(CString str);
	void  CCommDlg::printRecv_Temperature_Mode(CString str);
	void  CCommDlg::printRecv_Vehicle_code(CString str);
	void  CCommDlg::printRecv_Limit_Voltage(CString str);
	void  CCommDlg::printRecv_Limit_Current(CString str);
	void  CCommDlg::printRecv_Temperature(CString str);
	void  CCommDlg::printRecvjiaoyanStatus(CString str);
	void CCommDlg::OnClickedTimer();
	int CCommDlg::printCString_Int(CString str);
	/*void  CCommDlg::printRecvVot_Recv_Buck_OutStatus(CString str);
	void  CCommDlg::printRecvCur_Rec_BuckStatus(CString str);
	void  CCommDlg::printRecvDuty_Recv_BuckStatus(CString str);
	void  CCommDlg::printRecvDecode_Error_CntStatus(CString str);
	void  CCommDlg::printRecvTemp_Trans_MOStatus(CString str);
	void  CCommDlg::printRecvjiaoyanStatus(CString str);*/
	void OffsetProgress();
private:
	CProgressCtrl *myProCtrl;
public:
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonOpenfile();
	afx_msg void OnBnClickedButtonDatatofile();
	//afx_msg void OnBnClickedCheckHexSend();
	afx_msg void OnBnClickedCheckHexRecv();
	afx_msg void OnCbnSelchangeComboPort();
	afx_msg void OnCbnSelchangeComboBaudrate();
	afx_msg void OnEnChangeEditSend();
	afx_msg void OnCbnSelchangeComboCmd();
	afx_msg void OnEnChangeEditDatafilename();
	afx_msg void OnCbnSelchangeComboAddr();
	afx_msg void OnCbnSelchangeComboEcc();
	afx_msg void OnCbnSelchangeComboData();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedButtonSend1();
	afx_msg void OnClickedButtonSend2();
	afx_msg void OnClickedButtonSend3();
	afx_msg void OnClickedButtonSend4();
	afx_msg void OnClickedButtonSend5();
	afx_msg void OnClickedButtonSend6();
	afx_msg void OnClickedButtonSend7();
	afx_msg void OnClickedButtonSend8();
	afx_msg void OnEnChangeEditUpdateVoltage();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
