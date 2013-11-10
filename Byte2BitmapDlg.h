// Byte2BitmapDlg.h : 头文件
//

#pragma once


// CByte2BitmapDlg 对话框
class CByte2BitmapDlg : public CDialog
{
// 构造
public:
	CByte2BitmapDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BYTE2BITMAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
public:
    afx_msg void OnBnClickedCancel();
    void OnClose();

private:
    CString strPathName;
    char* m_pBMPBuffer;
    void OnButtonSelectiamge();
    LONG m_bmW;
    LONG m_bmH;
    HBITMAP m_hBitmap;
    BOOL LoadShowBMPFile(const char *pPathname);
    HBITMAP BufferToHBITMAP();
    void DrawImage(int x, int y, CDC *pDC);
};
