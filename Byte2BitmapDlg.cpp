// Byte2BitmapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Byte2Bitmap.h"
#include "Byte2BitmapDlg.h"
#include "conio.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// CByte2BitmapDlg �Ի���




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


// CByte2BitmapDlg ��Ϣ�������

BOOL CByte2BitmapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
   
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CByte2BitmapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);

        
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CByte2BitmapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CByte2BitmapDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
   // OnOK();
         AllocConsole();
    OnButtonSelectiamge();
}

void CByte2BitmapDlg::OnBnClickedCancel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
            CDC *pDC = GetDC();//�������ܣ��ú�������һָ�����ڵĿͻ������������Ļ����ʾ�豸�����Ļ����ľ�����Ժ������GDI������ʹ�øþ�������豸�����Ļ����л�ͼ��
            DrawImage(0,0,pDC);
        }
       // Invalidate();
    }
}

//����BMP�ļ����ڴ�
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

//���ڴ��е�BMP�ļ�����ת����λͼ���
HBITMAP CByte2BitmapDlg::BufferToHBITMAP()
{
    HBITMAP                hShowBMP;//������
    LPSTR                hDIB,lpBuffer = m_pBMPBuffer;//typedef __nullterminated CHAR *LPSTR
    LPVOID                lpDIBBits;//typedef void far
    BITMAPFILEHEADER    bmfHeader;//λͼͷ�ṹ
    DWORD                bmfHeaderLen;//typedef unsigned long DWORD
    
    bmfHeaderLen = sizeof(bmfHeader);
    _cprintf("bmfHeaderLen=%d\n",bmfHeaderLen);
    strncpy((LPSTR)&bmfHeader,(LPSTR)lpBuffer,bmfHeaderLen);//char * strncpy( char *dest, char *src, size_t num );
    //��c/c++������src�е����ݣ��ַ������֡�����....����dest�����ƶ�����num��ֵ����
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
    //1.hdc���豸���������
    //2.lpbmih��ָ��λͼ��Ϣͷ�ṹ��ָ�룬�����������в���ϵͳλͼ��Ϣͷ֮һ��
    //3.���fdwlnit��CBM_INIT����ô����ʹ��λͼ��Ϣͷ�ṹ����ȡλͼ����Ŀ�ȡ��߶��Լ�������Ϣ��
    //4.lpblnit����ָ��ָ�������ʼ��λͼ���ݵ��ֽ��������顣���ݸ�ʽ�����lpbmiָ���BITMAPINFO�ṹ�еĳ�ԱbiBitCount�йء�
    //5.lpbmi��ָ��BITMAPINFO�ṹ��ָ�롣�ýṹ�����˲���lpbmiָ��������ά������ɫ��ʽ��
    //6.DIB_RGB_COLORS����ʾ�ṩһ����ɫ�����ұ��а�����ԭ���RGBֵ��
    return hShowBMP;
}

//����Ļ����ʾBMPͼ��
void CByte2BitmapDlg::DrawImage(int x, int y, CDC *pDC)
{
    HBITMAP OldBitmap;
    CDC MemDC;
    MemDC.CreateCompatibleDC(pDC);//�ú�������һ����ָ���豸���ݵ��ڴ��豸�����Ļ�����DC��
    OldBitmap=(HBITMAP)MemDC.SelectObject(m_hBitmap);//�ú���ѡ��һ����ָ�����豸�����Ļ�����,���¶����滻��ǰ����ͬ���͵Ķ���
   // CBitmap* pBitmap = CBitmap::FromHandle(m_hBitmap);
    if(m_bmW == 0 || m_bmH == 0)
        return ;
    CRect rect;
    GetClientRect(&rect); //�ú�����ȡ���ڿͻ���������  


    _cprintf("rect w=%d,h=%d\n",rect.Width(),rect.Height());
   

    pDC->BitBlt(x,y,
        rect.Width(),
        rect.Height(),
        &MemDC,
        0,0,
        SRCCOPY);//�ú�����ָ����Դ�豸���������е����ؽ���λ�飨bit_block��ת�����Դ��͵�Ŀ���豸������
    
 
    MemDC.SelectObject(OldBitmap);//�ָ��ڴ���ԭ�е�λͼ
    ReleaseDC(pDC); //�ͷ���ʾDC
}

void CByte2BitmapDlg::OnClose()
{
    delete[] m_pBMPBuffer;
    //delete m_hBitmap;
    FreeConsole();
    EndDialog(IDCANCEL);    //�رմ���  
    CDialog::OnClose();  
}