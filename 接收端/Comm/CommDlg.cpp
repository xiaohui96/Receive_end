
// CommDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Comm.h"
#include "CommDlg.h"
#include "afxdialogex.h"

#include "serialport.h"
#include "xmodem.h"
#include "myAlgorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SERIAL_RXBUFF_MAX  0x100000ul

BYTE TxBuff[4096];
WORD TxLen;
BYTE RxBuff[65536];
DWORD RxLen;
DWORD RxLenTotal;
CString rstr;

// 用于应用程序“关于”菜单项的 CAboRxByteArrayutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCommDlg 对话框




CCommDlg::CCommDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCommDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ON_COM_RECV, &CCommDlg::OnRecvDataHandler)
	ON_BN_CLICKED(IDC_BUTTON_Open, &CCommDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_Send, &CCommDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CCommDlg::OnBnClickedButtonClear)
	//ON_BN_CLICKED(IDC_CHECK_HexSend, &CCommDlg::OnBnClickedCheckHexSend)
	//ON_BN_CLICKED(IDC_CHECK_HexRecv, &CCommDlg::OnBnClickedCheckHexRecv)
	//ON_BN_CLICKED(IDC_BUTTON_Clear, &CCommDlg::OnBnClickedButtonClear)
	ON_CBN_SELCHANGE(IDC_COMBO_Port, &CCommDlg::OnCbnSelchangeComboPort)
	ON_CBN_SELCHANGE(IDC_COMBO_Baudrate, &CCommDlg::OnCbnSelchangeComboBaudrate)
	ON_BN_CLICKED(IDC_BUTTON_Send1, &CCommDlg::OnClickedButtonSend1)
	ON_BN_CLICKED(IDC_BUTTON_Send2, &CCommDlg::OnClickedButtonSend2)
	ON_BN_CLICKED(IDC_BUTTON_Send3, &CCommDlg::OnClickedButtonSend3)
	ON_BN_CLICKED(IDC_BUTTON_Send4, &CCommDlg::OnClickedButtonSend4)
	ON_BN_CLICKED(IDC_BUTTON_Send5, &CCommDlg::OnClickedButtonSend5)
	ON_BN_CLICKED(IDC_BUTTON_Send6, &CCommDlg::OnClickedButtonSend6)
	ON_BN_CLICKED(IDC_BUTTON_Send7, &CCommDlg::OnClickedButtonSend7)
	ON_BN_CLICKED(IDC_BUTTON_Send8, &CCommDlg::OnClickedButtonSend8)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void UserInit()
{

}

void CCommDlg::OnBnClickedButtonClear()
{
	GetDlgItem(IDC_EDIT_Status)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_RecvLen)->SetWindowText(_T("0"));
	//RxLenTotal = 0;
	//RxLen = 0;
}
// CCommDlg 消息处理程序


void  CCommDlg::printRecv_Output_Voltage(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	//stu=stu&(0x0F);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Output_Voltage);
	//CEdit* pEdit = (CEdit*)a.GetDlgItem(IDC_EDIT_Status);
	//把IDC_EDIT_Status的窗口指针赋给pEdit
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Output_Voltage)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}

void  CCommDlg::printRecv_Output_Current(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Output_Current);
	//CEdit* pEdit = (CEdit*)b.GetDlgItem(IDC_EDIT_Recv);
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Output_Current)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}

void  CCommDlg::printRecv_Input_Voltage(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	//CCommDlg b;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Input_Voltage);
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
	GetDlgItem(IDC_EDIT_Input_Voltage)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}
void  CCommDlg::printRecv_Duty_Radio(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Duty_Radio);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Duty_Radio)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}

void  CCommDlg::printRecv_Buck_Mode(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	buck1 = stu2.Mid(2,2);
	//buck2 = stu2.Mid(0,2);
	if (buck1 =="")
	{
		buck1 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Buck_Mode);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Buck_Mode)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck1); 
}
void  CCommDlg::printRecv_Temperature_Mode(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	CString stu2;
	CString buck1;
	CString buck2;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	while(stu!=0){
		if(stu%2==0)
		{stu2 = _T("0") + stu2;}
		else
		{stu2 = _T("1") + stu2;}
		stu = stu/2;
	}
	//buck1 = stu2.Mid(2,2);
	buck2 = stu2.Mid(0,2);
	if (buck2 =="")
	{
		buck2 =_T("00");}
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Temperature_Mode);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Temperature_Mode)->SetWindowText(_T(""));
    pEdit->ReplaceSel(buck2); 
}

void  CCommDlg::printRecv_Vehicle_code(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Vehicle_code);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Vehicle_code)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}

void  CCommDlg::printRecv_Limit_Voltage(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Limit_Voltage);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Limit_Voltage)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}

void  CCommDlg::printRecv_Limit_Current(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Limit_Current);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Limit_Current)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}

void  CCommDlg::printRecv_Temperature(CString str)
{
	CString strn=str;
    char temp[10];
	CString stu1;
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	stu1.Format(_T("%ld"),stu);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Temperature);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	GetDlgItem(IDC_EDIT_Temperature)->SetWindowText(_T(""));
    pEdit->ReplaceSel(stu1); 
}


void  CCommDlg::printRecvjiaoyanStatus(CString str)
{
	CString stu1;
	long stu;
	long zongshu=0;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Status);
    int nLength = pEdit->GetWindowTextLength();
    pEdit->SetSel(nLength, nLength);
	for(int i=2;i<=30;i+=2)
	{
	CString strn=rstr.Mid(i,2);
    char temp[10];
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	zongshu+=stu;
	}
	stu1.Format(_T("%lx"),zongshu);
	/*if(stu1.Right(2)==rstr.Mid(32,2))
	{
	pEdit->ReplaceSel(_T("\n数据校验成功\n"));
	pEdit->ReplaceSel(_T("\n"));
	}
	else
	{
	pEdit->ReplaceSel(_T("    数据校验失败"));
	pEdit->ReplaceSel(_T("\n"));
	}*/
}

void CCommDlg::printStatus(CString str)
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Status);
    int nLength = pEdit->GetWindowTextLength();
 
    //选定当前文本的末端
    pEdit->SetSel(nLength, nLength);
    //追加文本
    pEdit->ReplaceSel(str); 
}

// CString 转int
int CCommDlg::printCString_Int(CString str)
{
CString strn3=str;
    char temp[10];
	long stu;
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn3);
    const char *str1=temp;
	stu=strtol(str1,0,10);
	return stu;
}

BOOL CCommDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_textcolor=RGB(0,0,0);                 // 文本颜色设置为红色  
	// TODO: 在此添加额外的初始化代码
	//自定义控件初始化
	GetComList_Reg();
	myProCtrl = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS_Status);

	CComboBox* comboBaudrate = (CComboBox*)GetDlgItem(IDC_COMBO_Baudrate);
	((CButton *)GetDlgItem(IDC_CHECK_HexRecv))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CHECK_HexSend))->SetCheck(TRUE);
	
	
	((CButton *)GetDlgItem(IDC_CHECK_SEND))->SetCheck(FALSE);

	comboBaudrate->AddString(_T("9600"));
	comboBaudrate->AddString(_T("19200"));
	comboBaudrate->AddString(_T("115200"));
	SetDlgItemText(IDC_COMBO_Baudrate, _T("9600"));  //

	SetDlgItemText(IDC_COMBO_Port, _T("COM3"));
	//指令初始化
	SetDlgItemText(IDC_COMBO_Order1, _T("接收端反馈所有电路状态"));
	SetDlgItemText(IDC_COMBO_Order2, _T("更改接收端存储的电压限值、电流限值"));
	SetDlgItemText(IDC_COMBO_Order3, _T("接收端BUCK完全开启，且不做控制"));
	SetDlgItemText(IDC_COMBO_Order4, _T("接收端BUCK完全关断，且不做控制"));
	SetDlgItemText(IDC_COMBO_Order5, _T("接收端BUCK恢复正常的PI控制"));
	SetDlgItemText(IDC_COMBO_Order6, _T("更改车载设备编码信息"));
	SetDlgItemText(IDC_COMBO_Order7, _T("失能接收端温度控制"));
	SetDlgItemText(IDC_COMBO_Order8, _T("使能接收端温度控制"));
	TCHAR path[255];
	SHGetSpecialFolderPath(0,path,CSIDL_DESKTOPDIRECTORY,0);

	CString binFileName = path;
	binFileName += _T("\\data");
	SYSTEMTIME st; 
	CString strDate,strTime; 
	
	GetLocalTime(&st); 
	binFileName.AppendFormat(_T("_%4d-%2d-%2d"),st.wYear,st.wMonth,st.wDay); 
	binFileName.AppendFormat(_T("_%2d-%2d"),st.wHour,st.wMinute) ; 
	binFileName += strDate + strTime ;

	binFileName += _T(".hex");
	//GetDlgItem(IDC_EDIT_DataFileName)->SetWindowText(binFileName);

	//CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Recv);
	//pEdit->SetLimitText(1000000);

	//用户代码初始化
	//::UserInit();




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCommDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CCommDlg::OnRecvDataHandler(WPARAM wParam, LPARAM lParam)
{   
	CString strSend1;
	CString strnum;
	CString str1;
	CString str2;
	CString str;
	
	//GetDlgItem(IDC_COMBO_Addr)->GetWindowText(strSend1);
	
	BYTE* buffer = (BYTE*)wParam; //缓冲区指针
	WORD total = (WORD)lParam; //缓冲区接收到的字节数
	if(RxLen+total > SERIAL_RXBUFF_MAX)
	{
		MessageBox(_T("The Rx Buffer is full!"));
	}
	else
	{
		memcpy(RxBuff+RxLen, buffer, total);
		RxLen += total;
		RxLenTotal += total;
	}
	
	if(IsDlgButtonChecked(IDC_CHECK_HexRecv)) //Hex接收
	{
		for(WORD cur = 0; cur<total; ++cur)
		{
			str.AppendFormat(_T("%02x"), buffer[cur]);
		}
		rstr += str;
	}
	else
	{
		buffer[total] = '\0';
		str = buffer;

	}
	strnum.Format(_T("%d"), RxLenTotal);
	GetDlgItem(IDC_STATIC_RecvLen)->SetWindowText(strnum);
	//GetDlgItem(IDC_STATIC_RecvLen)->SetWindowText('\0');
	if(rstr.Mid(0,2)=="aa")
	{
		//if((RxLenTotal%18==0))
		if((RxLenTotal==18))
			{
				printStatus(rstr);
				printStatus(_T("\n"));
				printRecv_Output_Voltage(rstr.Mid(6,1)+rstr.Mid(2,2));
				printRecv_Output_Current(rstr.Mid(7,1)+rstr.Mid(4,2));
				printRecv_Input_Voltage(rstr.Mid(12,1)+rstr.Mid(8,2));
				printRecv_Duty_Radio(rstr.Mid(13,1)+rstr.Mid(10,2));
				printRecv_Buck_Mode(rstr.Mid(17,1));
				printRecv_Temperature_Mode(rstr.Mid(17,1));
				printRecv_Vehicle_code(rstr.Mid(30,2)+rstr.Mid(28,2)+rstr.Mid(26,2)+rstr.Mid(24,2));
				printRecv_Limit_Voltage(rstr.Mid(22,1)+rstr.Mid(18,2));
				printRecv_Limit_Current(rstr.Mid(23,1)+rstr.Mid(20,2));
				printRecv_Temperature(rstr.Mid(16,1)+rstr.Mid(14,2));
				printRecvjiaoyanStatus(str.Mid(0,32));
				//if(RxLenTotal =18){
					RxLenTotal =0;
					rstr ="";
				//}
				printStatus(_T("\n数据帧正常"));
				printStatus(_T("\n"));//断点
				}
		else
		{
		printStatus(_T("数据帧不正常，请重新发送指令"));
		printStatus(_T("\n"));
		// 清除错误数据
		RxLenTotal =0;
		rstr ="";
		}
	    }
	else{
		printStatus(_T("数据帧不正常，请重新发送指令"));
		printStatus(_T("\n"));
		// 清除错误数据
		RxLenTotal =0;
		rstr ="";
	}
	return 0;
}

void CCommDlg::toggleButtonStatus(BOOL isopen)
{
	GetDlgItem(IDC_BUTTON_Send)->EnableWindow(isopen);
	//GetDlgItem(IDC_BUTTON_Start)->EnableWindow(isopen);
	//GetDlgItem(IDC_BUTTON_Stop)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON_Start2)->EnableWindow(isopen);
	//GetDlgItem(IDC_BUTTON_Stop)->EnableWindow(FALSE);
}

//***********************
// 枚举所有的串口，以及名称
//***********************
int CCommDlg::GetComList_Reg()
{
    HKEY hkey;  
    int result;
    int count = 0;

	CComboBox * CCombox  = (CComboBox*)GetDlgItem(IDC_COMBO_Port);

    CString strComName;//串口名称
	CString strDrName;//串口详细名称

	result = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
							_T( "Hardware\\DeviceMap\\SerialComm" ),
							NULL,
							KEY_READ,
							&hkey );

	if(result == ERROR_SUCCESS)   //   打开串口注册表   
	{   
		TCHAR portName[ 0x100 ], commName[ 0x100 ];
		DWORD dwLong, dwSize;

		CCombox->ResetContent();
		do
		{   
			dwSize = sizeof( portName ) / sizeof( TCHAR );
			dwLong = dwSize;
			result = RegEnumValue( hkey, count, portName, &dwLong, NULL, NULL, ( LPBYTE )commName, &dwSize );
			if( ERROR_NO_MORE_ITEMS == result )
			{
				//   枚举串口
				break;   //   commName就是串口名字"COM2"
			}
			strComName=commName;
			strDrName = portName;

			// 从右往左边开始查找第一个'\\'，获取左边字符串的长度
			int len = strDrName.ReverseFind( '\\');
			// 获取'\\'左边的字符串
			CString strFilePath = strDrName.Left( len+1 );
			// 获取'\\'右边的字符串
			CString fileName = strDrName.Right(strDrName.GetLength() - len-1);
			fileName = strComName + _T(": ")+fileName;

			CCombox->AddString(strComName);
			count++;   
		} while ( 1 );

		RegCloseKey( hkey );   
	}

	CCombox->SetCurSel(0);
    return count;
}




void CCommDlg::OffsetProgress()
{
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_Progress);
	CString str;
	myProCtrl->OffsetPos(1);
	int pos = myProCtrl->GetPos();
	int lower,upper;
	myProCtrl->GetRange(lower, upper);
	
	str.Format(_T("%2d%%"), pos*100/upper);
	pStatic->SetWindowText(str);
}

/**
  * @brief: 串口打开函数
  */
void CCommDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPort;
	GetDlgItem(IDC_COMBO_Port)->GetWindowText(strPort);
	CString strBaudrate;
	GetDlgItem(IDC_COMBO_Baudrate)->GetWindowText(strBaudrate);
	CString strButtonOpen;
	GetDlgItem(IDC_BUTTON_Open)->GetWindowText(strButtonOpen);
	if(!strButtonOpen.CompareNoCase(_T("Close")))
	{
		GetDlgItem(IDC_BUTTON_Open)->SetWindowText(_T("Open"));
		toggleButtonStatus(FALSE);
		if(CloseSerialPort())
			printStatus(_T("关闭") + strPort + _T("成功\n"));  
		else
			MessageBox(_T("关闭") + strPort + _T("失败\n"));  
		return;
	}
	
	if(!SerialOpen(this->GetSafeHwnd(), strPort, _ttoi(strBaudrate)))
	{
		MessageBox(strPort +"打开失败");
		return;
	}
	GetDlgItem(IDC_BUTTON_Open)->SetWindowText(_T("Close"));
	printStatus(strPort + _T("打开成功\n")); 
	toggleButtonStatus();
	
	
}



void CCommDlg::OnBnClickedButtonSend()
{
	CString strSend;
	GetDlgItem(IDC_EDIT_Send)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
}

void CCommDlg::OnClickedButtonSend1()
{
	if(IsDlgButtonChecked(IDC_CHECK_SEND))//按钮被按下
	{
		SetTimer(1,1000,NULL);
	}
	else
	{
		KillTimer(1);
	}
	CString strSend;
	strSend="55 0F 00 00 00 00 00";
	//GetDlgItem(IDC_EDIT_Send)->GetWindowText(strSend);
	//GetDlgItem(IDC_COMBO_Order1)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
	
}



void CCommDlg::OnClickedButtonSend2()
{
	CString strSend;
	CString updVoltage_Int16;
	CString updCurrent_Int16;
	CString updVoltage;
	INT updVoltage_Int;
	INT updCurrent_Int;
	CString updCurrent;
	CString buffer;
	CString sum;
	//strSend="55 1E 00 00 00 00 00";
	strSend="55 1E ";
	GetDlgItemText(IDC_EDIT_Update_Voltage,updVoltage);
	GetDlgItemText(IDC_EDIT_Update_Current,updCurrent);
	updVoltage_Int = printCString_Int(updVoltage);
	updVoltage_Int16.Format(_T("%3x"),updVoltage_Int);
	updCurrent_Int = printCString_Int(updCurrent);
	updCurrent_Int16.Format(_T("%3x"),updCurrent_Int);
	buffer =updVoltage_Int16.Mid(0,1)+updCurrent_Int16.Mid(0,1);
	sum=updVoltage_Int16.Mid(1,2)+updCurrent_Int16.Mid(1,2)+buffer;
	CString stu1;
	long stu;
	long zongshu=0;
	for(int i=0;i<=4;i+=2)
	{
	CString strn=sum.Mid(i,2);
    char temp[10];
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	zongshu+=stu;
	}
	stu1.Format(_T("%lx"),zongshu);
	strSend = strSend+updVoltage_Int16.Mid(1,2);
	strSend = strSend+" "+updCurrent_Int16.Mid(1,2)+" "+buffer+" "+"00 "+stu1.Right(2);
	//char test1[10];
	//char test2[10];
	//::wsprintfA(test1, "%ls",(LPCTSTR)updVoltage);
	//::wsprintfA(test2, "%ls",(LPCTSTR)updCurrent);
	//const char *voltage=test1;
	//const char *current=test2;
	//long n1 =strtol(voltage,0,10);
	//long n2 =strtol(current,0,10);
	//long n3 =n1+n2;
	//char buffer1[3];
	//char buffer2[3];
	//char buffer3[2];
	//itoa(n1,buffer1,16);
	//itoa(n2,buffer2,16);
	//itoa(n3,buffer3,16);
	//if (n3>255)
	//{
	//int i=0;
	//for(i=0;i<=1;i++)
	//{buffer3[i]=buffer3[i+1];
	//}
	//}
	///*if(n1>255)
	//{
	//	strcpy(buffer3,a);
	//	strcat(buffer3,b);
	//}*/
	//strSend += buffer1;
	//strSend +=" ";
	//strSend +=buffer2;
	//strSend +=" 00 00 ";
	//strSend +=buffer3;
	//strSend=strSend.Mid(0,20);
	//GetDlgItem(IDC_COMBO_Order2)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnClickedButtonSend3()
{
	CString strSend;
	strSend="55 2D 00 00 00 00 00";
	//GetDlgItem(IDC_COMBO_Order3)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnClickedButtonSend4()
{
	CString strSend;
	strSend="55 3C 00 00 00 00 00";
	//GetDlgItem(IDC_COMBO_Order4)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnClickedButtonSend5()
{
	CString strSend;
	strSend="55 4B 00 00 00 00 00";
	//GetDlgItem(IDC_COMBO_Order4)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnClickedButtonSend6()
{
	CString strSend;
	CString Num3;
	int Num3_Int;
	CString Num6;
	int Num6_Int;
	CString Num9;
	int Num9_Int;
	CString Cnum;
	int Num_Sum;
	CString CNum_Sum;
	CString CNum_Sum16;
	strSend="55 5A ";
	GetDlgItemText(IDC_EDIT_Car_Num3,Num3);
	GetDlgItemText(IDC_EDIT_Car_Num6,Num6);
	GetDlgItemText(IDC_EDIT_Car_Num9,Num9);
	 Num3_Int = printCString_Int(Num3);
	 Num6_Int = printCString_Int(Num6) * 1000;
	 Num9_Int = printCString_Int(Num9) * 1000000;
	Num_Sum = Num3_Int + Num6_Int + Num9_Int;
	CNum_Sum.Format(_T("%ld"),Num_Sum);
	// 输入错误弹框提示
	if((Num3.GetLength()>3 )||(Num6.GetLength()>3) ||(Num9.GetLength()>3)) 
	{
		MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
		return;
		}
	// 转换成16进制
	CNum_Sum16.Format(_T("%x"),Num_Sum);
	int j = CNum_Sum16.GetLength();
	/*for(int i=0; i<=8-CNum_Sum16.GetLength(); i++)
	{
		CNum_Sum16 = _T("0") + CNum_Sum16;
	}*/
	// 解决无法补全的问题
	if (j==1){
		CNum_Sum16 = _T("0000000") + CNum_Sum16;
	}
	else if(j==2){
		CNum_Sum16 = _T("000000") + CNum_Sum16;
	}
	else if(j==3){
		CNum_Sum16 = _T("00000") + CNum_Sum16;
	}
	else if(j==4){
		CNum_Sum16 = _T("0000") + CNum_Sum16;
	}
	else if(j==5){
		CNum_Sum16 = _T("000") + CNum_Sum16;
	}
	else if(j==6){
		CNum_Sum16 = _T("00") + CNum_Sum16;
	}
	else if(j==7){
		CNum_Sum16 = _T("0") + CNum_Sum16;
	}


	// test
	/*CString test;
	test = Cnum.Mid(2,2);*/
	CString stu1;
	long stu;
	long zongshu=0;
	for(int i=0;i<=7;i+=2)
	{
	CString strn=CNum_Sum16.Mid(i,2);
    char temp[10];
    ::wsprintfA(temp, "%ls",(LPCTSTR)strn);
    const char *str1=temp;
	stu=strtol(str1,0,16);
	zongshu+=stu;
	}
	stu1.Format(_T("%lx"),zongshu);
	if((stu1.GetLength()>2))
	{
		stu1 = stu1.Mid(1,2);
	}

	strSend = strSend + CNum_Sum16.Mid(6,2) + " " + CNum_Sum16.Mid(4,2) + " " + CNum_Sum16.Mid(2,2) + " " + CNum_Sum16.Mid(0,2) + " " + stu1;

	//GetDlgItem(IDC_COMBO_Order4)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnClickedButtonSend7()
{
	CString strSend;
	strSend="55 69 00 00 00 00 00";
	//GetDlgItem(IDC_COMBO_Order4)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnClickedButtonSend8()
{
	CString strSend;
	strSend="55 78 00 00 00 00 00";
	//GetDlgItem(IDC_COMBO_Order4)->GetWindowText(strSend);
	int bytelen = strSend.GetLength();
	WORD count = 0;
	if(bytelen <= 0)
	{
		MessageBox(_T("请输入要发送的内容"));
		return;
	}
	//if(IsDlgButtonChecked(IDC_CHECK_HexSend)) //Hex发送
	if(1) //Hex发送
	{
		for(WORD i=0; i < bytelen; )//bytelen不要超过1024
		{
			if(strSend.Mid(i,1) == _T(' '))
			{
				i++; continue;
			}
			CString bit = strSend.Mid(i,2); //从i开始取2个字符
			if(bit.Mid(1,1)==_T(' ')|| i==bytelen-1) //如果第2个字符是空字符,或者已经到了最后一个字节了
			{
				TxBuff[count++] = (BYTE)(_ttol(bit.Mid(0,1)));
				i += 1;//去掉空字符
			}
			else
			{
				bit.MakeUpper();
				int num=0;

				char buffer[3];
				My_CStringToChar(buffer, bit);				
				if(isalpha(buffer[0]))
					num += (buffer[0]-'A'+10);
				else
					num = buffer[0]-'0';
				num *= 16;
				if(isalpha(buffer[1]))
					num += (buffer[1]-'A'+10);
				else
					num += buffer[1]-'0';
				TxBuff[count++] = (BYTE)num;
				i += 2; //去掉空字符
				if(strSend.Mid(i,1)!=_T(' ') && i<bytelen && strSend.Mid(i,1)!='\n') //确定是否相连
				{
					MessageBox(_T("输入的信息中存在不符合规格的字节，请重新输入"));
					return;
				}
			}
		}
	}
	else //字符串发送
	{
		count = My_CStringToChar((char*)TxBuff,strSend);
	}
	printStatus(strSend + _T("已发送"));
	printStatus(_T("\n"));
	TxLen = count;
	SerialSend(TxBuff, TxLen);
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnCbnSelchangeComboPort()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCommDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 在此添加控件通知处理程序代码
}




void CCommDlg::OnEnChangeEditSend()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	//#1015

	// TODO:  在此添加控件通知处理程序代码
}



HBRUSH CCommDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString strr;
	GetDlgItemText(IDC_STATIC_RecvLen,strr);//判断Flag_Infrary值
	if(strr!="18")
	{
	m_textcolor=RGB(255,0,0);;//红色
	}
switch (nCtlColor) //对所有同一类型的控件进行判断  
	{  
case CTLCOLOR_EDIT:  
//case CTLCOLOR_MSGBOX://假设控件是文本框或者消息框，则进入下一个switch  
	switch (pWnd->GetDlgCtrlID())//对某一个特定控件进行判断  
   {      
   case IDC_EDIT_Output_Voltage:         // 第一个文本框  
    //pDC->SetBkColor(m_color);    // change the background  

    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;    
	case IDC_EDIT_Output_Current:         // 第二个文本框   
   //pDC->SetBkColor(m_color);   // make background   
    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;     // apply the red brush  
    break; 
	case IDC_EDIT_Input_Voltage :         // 第一个文本框  
    //pDC->SetBkColor(m_color);    // change the background  
    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;
	case IDC_EDIT_Duty_Radio :         // 第一个文本框  
    //pDC->SetBkColor(m_color);    // change the background   
    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;
	case IDC_EDIT_Buck_Mode :         // 第一个文本框  
    //pDC->SetBkColor(m_color);    // change the background   
    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;case IDC_EDIT_Temperature_Mode :         // 第一个文本框  
    //pDC->SetBkColor(m_color);    // change the background   
    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;
	case IDC_EDIT_Vehicle_code :         // 第一个文本框  
    //pDC->SetBkColor(m_color);    // change the background   
    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;
	case IDC_EDIT_Limit_Voltage :         // 第一个文本框  
    //pDC->SetBkColor(m_color);    // change the background   
    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;
	case IDC_EDIT_Limit_Current :         // 第一个文本框  
    //pDC->SetBkColor(m_color);    // change the background   
    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;
	case IDC_EDIT_Temperature :         // 第一个文本框  
    //pDC->SetBkColor(m_color);    // change the background   
    pDC->SetTextColor(m_textcolor); // change the text color  
    hbr = (HBRUSH) m_brush;    // apply the blue brush  
    break;
   default:  
    hbr=CDialogEx::OnCtlColor(pDC,pWnd,nCtlColor);  
    break;  
   }  
   break;  
}  
// TODO: Return a different brush if the default is not desired  
return hbr;
}



void CCommDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	OnClickedButtonSend1();
}
