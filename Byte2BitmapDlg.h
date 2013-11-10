// Byte2BitmapDlg.h : ͷ�ļ�
//

#pragma once


// CByte2BitmapDlg �Ի���
class CByte2BitmapDlg : public CDialog
{
// ����
public:
	CByte2BitmapDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BYTE2BITMAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
