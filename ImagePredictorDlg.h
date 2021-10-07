
// ImagePredictorDlg.h: 헤더 파일
//

#pragma once


// CImagePredictorDlg 대화 상자
class CImagePredictorDlg : public CDialogEx
{
// 생성입니다.
public:
	CImagePredictorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEPREDICTOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	

public:
	afx_msg void OnBnClickedButton1();
	CImage m_image;
	CImage D_image;
	CImage Q_image;
	CImage DQ_image;
	CImage ID_image;
	BOOL ready=0;
	BYTE ori[512 * 512] = { 0 ,};
	int DCT[512 * 512] = { 0, };
	int QT[512 * 512] = { 0, };
	int DQ[512 * 512] = { 0, };
	BYTE ID[512 * 512] = { 0, };
	int block[64][64][8][8];


	int selectRadio = 1;
	BOOL check = 0;
	int stepsize = 10;


	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	CListBox m_list;
	CString strf;

	afx_msg void OnCbnSelchangeCombo1();
	void dct(int ix[][8]);
	void idct(int ix[][8]);
	void qt(int ix[][8],int stepsize);
	void dq(int ix[][8], int stepsize);
	void getImage();
	void printImage();
	float MSE(BYTE a[], BYTE b[], int size);

	CComboBox combo;
	BYTE* p_src_image = ori;
	int* p_src_image2 = DCT;
	int* p_src_image3 = QT;
	int* p_src_image4 = DQ;
	BYTE* p_src_image5 = ID;
};
