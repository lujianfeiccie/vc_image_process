// Byte2BitmapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Byte2Bitmap.h"
#include "Byte2BitmapDlg.h"
#include "conio.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CByte2BitmapDlg 对话框




CByte2BitmapDlg::CByte2BitmapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CByte2BitmapDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CByte2BitmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CByte2BitmapDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &CByte2BitmapDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CByte2BitmapDlg::OnBnClickedCancel)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CByte2BitmapDlg 消息处理程序

BOOL CByte2BitmapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// TODO: 在此添加额外的初始化代码
   
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CByte2BitmapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CByte2BitmapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CByte2BitmapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CByte2BitmapDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
   // OnOK();
         AllocConsole();
    OnButtonSelectiamge();
}

void CByte2BitmapDlg::OnBnClickedCancel()
{
    // TODO: 在此添加控件通知处理程序代码
    //OnCancel();
   
}

void CByte2BitmapDlg::OnButtonSelectiamge() 
{
    char  szFilter[] = "BMP Files (*.bmp)|*.bmp|All Files (*.*)|*.*||";
    CFileDialog dlg( TRUE,"BMP",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter );
    if(dlg.DoModal() == IDOK)
    {
        strPathName = dlg.GetPathName();        
        if(LoadShowBMPFile(strPathName)){    
            m_hBitmap = BufferToHBITMAP();  
            CDC *pDC = GetDC();//函数功能：该函数检索一指定窗口的客户区域或整个屏幕的显示设备上下文环境的句柄，以后可以在GDI函数中使用该句柄来在设备上下文环境中绘图。
            DrawImage(0,0,pDC);
        }
       // Invalidate();
    }
}

//加载BMP文件到内存
BOOL CByte2BitmapDlg::LoadShowBMPFile(const char *pPathname)
{
    CFile file;
    if( !file.Open( pPathname, CFile::modeRead) )
        return FALSE;
    DWORD            m_nFileLen;
    m_nFileLen = file.GetLength();
    m_pBMPBuffer = new char[m_nFileLen + 1];
    if(!m_pBMPBuffer)
        return FALSE;
    if(file.Read(m_pBMPBuffer,m_nFileLen) != m_nFileLen)
        return FALSE;
    return TRUE;
}

//将内存中的BMP文件内容转换成位图句柄
HBITMAP CByte2BitmapDlg::BufferToHBITMAP()
{
    HBITMAP                hShowBMP;//保存结果
    LPSTR                hDIB,lpBuffer = m_pBMPBuffer;//typedef __nullterminated CHAR *LPSTR
    LPVOID                lpDIBBits;//typedef void far
    BITMAPFILEHEADER    bmfHeader;//位图头结构
    DWORD                bmfHeaderLen;//typedef unsigned long DWORD
    
    bmfHeaderLen = sizeof(bmfHeader);
    _cprintf("bmfHeaderLen=%d\n",bmfHeaderLen);
    strncpy((LPSTR)&bmfHeader,(LPSTR)lpBuffer,bmfHeaderLen);//char * strncpy( char *dest, char *src, size_t num );
    //（c/c++）复制src中的内容（字符，数字、汉字....）到dest，复制多少由num的值决定
    if (bmfHeader.bfType != (*(WORD*)"BM")) return NULL;
    _cprintf("bmfHeader.bfType=%d\n",bmfHeader.bfType);
    hDIB = lpBuffer + bmfHeaderLen;
    BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;
    BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
    m_bmW = bmiHeader.biWidth;
    m_bmH = bmiHeader.biHeight;
    _cprintf("bitmap width=%d,height=%d\n",m_bmW,m_bmH);
    lpDIBBits=(lpBuffer)+((BITMAPFILEHEADER *)lpBuffer)->bfOffBits;
    CClientDC dc(this);
    hShowBMP = CreateDIBitmap(dc.m_hDC,
                              &bmiHeader,
                              CBM_INIT,
                              lpDIBBits,
                              &bmInfo,
                              DIB_RGB_COLORS);
    //1.hdc：设备环境句柄。
    //2.lpbmih：指向位图信息头结构的指针，它可以是下列操作系统位图信息头之一：
    //3.如果fdwlnit是CBM_INIT，那么函数使用位图信息头结构来获取位图所需的宽度、高度以及其他信息。
    //4.lpblnit：该指针指向包含初始的位图数据的字节类型数组。数据格式与参数lpbmi指向的BITMAPINFO结构中的成员biBitCount有关。
    //5.lpbmi：指向BITMAPINFO结构的指针。该结构描述了参数lpbmi指向的数组的维数和颜色格式。
    //6.DIB_RGB_COLORS：表示提供一个颜色表，并且表中包含了原义的RGB值。
    return hShowBMP;
}

//在屏幕上显示BMP图像
void CByte2BitmapDlg::DrawImage(int x, int y, CDC *pDC)
{
    HBITMAP OldBitmap;
    CDC MemDC;
    MemDC.CreateCompatibleDC(pDC);//该函数创建一个与指定设备兼容的内存设备上下文环境（DC）
    OldBitmap=(HBITMAP)MemDC.SelectObject(m_hBitmap);//该函数选择一对象到指定的设备上下文环境中,该新对象替换先前的相同类型的对象。
   // CBitmap* pBitmap = CBitmap::FromHandle(m_hBitmap);
    if(m_bmW == 0 || m_bmH == 0)
        return ;
    CRect rect;
    GetClientRect(&rect); //该函数获取窗口客户区的坐标  


    _cprintf("rect w=%d,h=%d\n",rect.Width(),rect.Height());
   

    pDC->BitBlt(x,y,
        rect.Width(),
        rect.Height(),
        &MemDC,
        0,0,
        SRCCOPY);//该函数对指定的源设备环境区域中的像素进行位块（bit_block）转换，以传送到目标设备环境。
    
 
    MemDC.SelectObject(OldBitmap);//恢复内存中原有的位图
    ReleaseDC(pDC); //释放显示DC
}

void CByte2BitmapDlg::OnClose()
{
    delete[] m_pBMPBuffer;
    //delete m_hBitmap;
    FreeConsole();
    EndDialog(IDCANCEL);    //关闭窗口  
    CDialog::OnClose();  
}