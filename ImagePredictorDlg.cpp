

#include "pch.h"
#include "framework.h"
#include "ImagePredictor.h"
#include "ImagePredictorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define B_size 8
#define  nint(x)      ( (x)<0. ? (int)((x)-0.5) : (int)((x)+0.5) )

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
	
END_MESSAGE_MAP()


// CImagePredictorDlg 대화 상자



CImagePredictorDlg::CImagePredictorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGEPREDICTOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImagePredictorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO1, combo);
}

BEGIN_MESSAGE_MAP(CImagePredictorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CImagePredictorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CImagePredictorDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CImagePredictorDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CImagePredictorDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CImagePredictorDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CImagePredictorDlg::OnBnClickedRadio5)
	
	ON_CBN_SELCHANGE(IDC_COMBO1, &CImagePredictorDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CImagePredictorDlg 메시지 처리기

BOOL CImagePredictorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_image.Create(512, 512, 24);
	D_image.Create(512, 512, 24);
	Q_image.Create(512, 512, 24);
	DQ_image.Create(512, 512, 24);
	ID_image.Create(512, 512, 24);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CImagePredictorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CImagePredictorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
			CDialogEx::OnPaint();
		
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CImagePredictorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CImagePredictorDlg::OnBnClickedButton1()
{
	check = 0;
	getImage();
	CClientDC dc(this);
	m_image.Draw(dc, 5,5);
	printImage();
}




void CImagePredictorDlg::OnBnClickedRadio1()
{
	selectRadio = 1;
	if(check) printImage();
}


void CImagePredictorDlg::OnBnClickedRadio2()
{
	selectRadio = 2;
	if(check)printImage();
}

void CImagePredictorDlg::OnBnClickedRadio3()
{
	selectRadio = 3;
	if (check)printImage();

}


void CImagePredictorDlg::OnBnClickedRadio4()
{
	selectRadio = 4;
	if (check)printImage();
}


void CImagePredictorDlg::OnBnClickedRadio5()
{
	selectRadio = 5;
	if (check)printImage();
}



void CImagePredictorDlg::OnCbnSelchangeCombo1()
{
	switch (combo.GetCurSel()) {
	case 0:
		if (stepsize != 10) {
			stepsize = 10;
			if (check) {
				getImage();
				printImage();
			}
		}
		break;
	case 1:
		if (stepsize != 30) {
			stepsize = 30;
			if (check) {
				getImage();
				printImage();
			}
		}
		break;
	case 2:
		if (stepsize != 50){
			stepsize = 50;
			if (check) {
				getImage();
				printImage();
			}
		}
		break;
	}
	
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CImagePredictorDlg::dct(int ix[][8])
{
	static double pi = 3.141592653589793238;
	double x[B_size][B_size], z[B_size][B_size], y[B_size], c[40], s[40],
		ft[4], fxy[4], yy[B_size], zz;
	int i, ii, jj;

	for (i = 0; i < 40; i++) {
		zz = pi * (double)(i + 1) / 64.0;
		c[i] = cos(zz);
		s[i] = sin(zz);
	}

	for (ii = 0; ii < B_size; ii++)
		for (jj = 0; jj < B_size; jj++)
			x[ii][jj] = (float)ix[ii][jj];

	for (ii = 0; ii < B_size; ii++) {
		for (jj = 0; jj < B_size; jj++)
			y[jj] = x[ii][jj];

		for (jj = 0; jj < 4; jj++)
			ft[jj] = y[jj] + y[7 - jj];

		fxy[0] = ft[0] + ft[3];
		fxy[1] = ft[1] + ft[2];
		fxy[2] = ft[1] - ft[2];
		fxy[3] = ft[0] - ft[3];

		ft[0] = c[15] * (fxy[0] + fxy[1]);
		ft[2] = c[15] * (fxy[0] - fxy[1]);
		ft[1] = s[7] * fxy[2] + c[7] * fxy[3];
		ft[3] = -s[23] * fxy[2] + c[23] * fxy[3];

		for (jj = 4; jj < 8; jj++)
			yy[jj] = y[7 - jj] - y[jj];

		y[4] = yy[4];
		y[7] = yy[7];
		y[5] = c[15] * (-yy[5] + yy[6]);
		y[6] = c[15] * (yy[5] + yy[6]);

		yy[4] = y[4] + y[5];
		yy[5] = y[4] - y[5];
		yy[6] = -y[6] + y[7];
		yy[7] = y[6] + y[7];

		y[0] = ft[0];
		y[4] = ft[2];
		y[2] = ft[1];
		y[6] = ft[3];
		y[1] = s[3] * yy[4] + c[3] * yy[7];
		y[5] = s[19] * yy[5] + c[19] * yy[6];
		y[3] = -s[11] * yy[5] + c[11] * yy[6];
		y[7] = -s[27] * yy[4] + c[27] * yy[7];

		for (jj = 0; jj < B_size; jj++)
			z[ii][jj] = y[jj];

	}

	for (ii = 0; ii < B_size; ii++) {
		for (jj = 0; jj < B_size; jj++)
			y[jj] = z[jj][ii];

		for (jj = 0; jj < 4; jj++)
			ft[jj] = y[jj] + y[7 - jj];

		fxy[0] = ft[0] + ft[3];
		fxy[1] = ft[1] + ft[2];
		fxy[2] = ft[1] - ft[2];
		fxy[3] = ft[0] - ft[3];

		ft[0] = c[15] * (fxy[0] + fxy[1]);
		ft[2] = c[15] * (fxy[0] - fxy[1]);
		ft[1] = s[7] * fxy[2] + c[7] * fxy[3];
		ft[3] = -s[23] * fxy[2] + c[23] * fxy[3];

		for (jj = 4; jj < 8; jj++)
			yy[jj] = y[7 - jj] - y[jj];

		y[4] = yy[4];
		y[7] = yy[7];
		y[5] = c[15] * (-yy[5] + yy[6]);
		y[6] = c[15] * (yy[5] + yy[6]);

		yy[4] = y[4] + y[5];
		yy[5] = y[4] - y[5];
		yy[6] = -y[6] + y[7];
		yy[7] = y[6] + y[7];

		y[0] = ft[0];
		y[4] = ft[2];
		y[2] = ft[1];
		y[6] = ft[3];
		y[1] = s[3] * yy[4] + c[3] * yy[7];
		y[5] = s[19] * yy[5] + c[19] * yy[6];
		y[3] = -s[11] * yy[5] + c[11] * yy[6];
		y[7] = -s[27] * yy[4] + c[27] * yy[7];

		for (jj = 0; jj < B_size; jj++)
			y[jj] = y[jj] / 4.0;

		for (jj = 0; jj < B_size; jj++)
			z[jj][ii] = y[jj];
	}

	for (ii = 0; ii < B_size; ii++)
		for (jj = 0; jj < B_size; jj++)
			ix[ii][jj] = nint(z[ii][jj]);

}
void CImagePredictorDlg::idct(int ix[][8])
{
	static double pi = 3.141592653589793238;
	double x[B_size][B_size], z[B_size][B_size], y[B_size], c[40], s[40],
		ait[4], aixy[4], yy[B_size], zz;
	int i, ii, jj;

	for (i = 0; i < 40; i++) {
		zz = pi * (double)(i + 1) / 64.0;
		c[i] = cos(zz);
		s[i] = sin(zz);
	}

	for (ii = 0; ii < B_size; ii++)
		for (jj = 0; jj < B_size; jj++)
			x[ii][jj] = (float)ix[ii][jj];

	for (ii = 0; ii < B_size; ii++) {
		for (jj = 0; jj < B_size; jj++)
			y[jj] = x[jj][ii];

		ait[0] = y[0];
		ait[1] = y[2];
		ait[2] = y[4];
		ait[3] = y[6];

		aixy[0] = c[15] * (ait[0] + ait[2]);
		aixy[1] = c[15] * (ait[0] - ait[2]);
		aixy[2] = s[7] * ait[1] - s[23] * ait[3];
		aixy[3] = c[7] * ait[1] + c[23] * ait[3];

		ait[0] = aixy[0] + aixy[3];
		ait[1] = aixy[1] + aixy[2];
		ait[2] = aixy[1] - aixy[2];
		ait[3] = aixy[0] - aixy[3];

		yy[4] = s[3] * y[1] - s[27] * y[7];
		yy[5] = s[19] * y[5] - s[11] * y[3];
		yy[6] = c[19] * y[5] + c[11] * y[3];
		yy[7] = c[3] * y[1] + c[27] * y[7];

		y[4] = yy[4] + yy[5];
		y[5] = yy[4] - yy[5];
		y[6] = -yy[6] + yy[7];
		y[7] = yy[6] + yy[7];

		yy[4] = y[4];
		yy[7] = y[7];
		yy[5] = c[15] * (-y[5] + y[6]);
		yy[6] = c[15] * (y[5] + y[6]);

		for (jj = 0; jj < 4; jj++)
			y[jj] = ait[jj] + yy[7 - jj];

		for (jj = 4; jj < 8; jj++)
			y[jj] = ait[7 - jj] - yy[jj];

		for (jj = 0; jj < B_size; jj++)
			z[jj][ii] = y[jj];

	}

	for (ii = 0; ii < B_size; ii++) {
		for (jj = 0; jj < B_size; jj++)
			y[jj] = z[ii][jj];

		ait[0] = y[0];
		ait[1] = y[2];
		ait[2] = y[4];
		ait[3] = y[6];

		aixy[0] = c[15] * (ait[0] + ait[2]);
		aixy[1] = c[15] * (ait[0] - ait[2]);
		aixy[2] = s[7] * ait[1] - s[23] * ait[3];
		aixy[3] = c[7] * ait[1] + c[23] * ait[3];

		ait[0] = aixy[0] + aixy[3];
		ait[1] = aixy[1] + aixy[2];
		ait[2] = aixy[1] - aixy[2];
		ait[3] = aixy[0] - aixy[3];

		yy[4] = s[3] * y[1] - s[27] * y[7];
		yy[5] = s[19] * y[5] - s[11] * y[3];
		yy[6] = c[19] * y[5] + c[11] * y[3];
		yy[7] = c[3] * y[1] + c[27] * y[7];

		y[4] = yy[4] + yy[5];
		y[5] = yy[4] - yy[5];
		y[6] = -yy[6] + yy[7];
		y[7] = yy[6] + yy[7];

		yy[4] = y[4];
		yy[7] = y[7];
		yy[5] = c[15] * (-y[5] + y[6]);
		yy[6] = c[15] * (y[5] + y[6]);

		for (jj = 0; jj < 4; jj++)
			y[jj] = ait[jj] + yy[7 - jj];

		for (jj = 4; jj < 8; jj++)
			y[jj] = ait[7 - jj] - yy[jj];

		for (jj = 0; jj < B_size; jj++)
			z[ii][jj] = y[jj] / 4.0;

	}

	for (ii = 0; ii < B_size; ii++)
		for (jj = 0; jj < B_size; jj++)
			ix[ii][jj] = nint(z[ii][jj]);

	
}
void CImagePredictorDlg::qt(int ix[][8],int step)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			if (ix[i][j] > 0)
				ix[i][j] = (ix[i][j] + step/2) / step;
			else
				ix[i][j] = (ix[i][j] - step/2) / step;
		}
	}


}
void CImagePredictorDlg::dq(int ix[][8], int step)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{			
			ix[i][j] = ix[i][j]*step;

		}
	}
}
void CImagePredictorDlg::getImage()
{
	BYTE* p_dest_image = new BYTE[512 * 512 * 3];
	BYTE* p_dest_image2 = new BYTE[512 * 512 * 3];
	BYTE* p_dest_image3 = new BYTE[512 * 512 * 3];
	BYTE* p_dest_image4 = new BYTE[512 * 512 * 3];
	BYTE* p_dest_image5 = new BYTE[512 * 512 * 3];
	BYTE* p_dest_pos = p_dest_image;
	BYTE* p_dest_pos2 = p_dest_image2;
	BYTE* p_dest_pos3 = p_dest_image3;
	BYTE* p_dest_pos4 = p_dest_image4;
	BYTE* p_dest_pos5 = p_dest_image5;
	BYTE* p_src_pos = p_src_image;
	int* p_src_pos2 = p_src_image2;
	int* p_src_pos3 = p_src_image3;
	int* p_src_pos4 = p_src_image4;
	BYTE* p_src_pos5 = p_src_image5;

	if (check != 1) {
		CString str = _T("*.raw|*.raw|"); // 모든 파일 표시
		// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
		CFileDialog dlg(TRUE, _T("*.raw"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
		check = 1;
		if (dlg.DoModal() == IDOK)
		{
			CString strPathName = dlg.GetPathName();
			CFile file;
			int test = 0;//최대값 추적
			int testing = 10;//최솟값 추적
			file.Open(strPathName, CFile::modeRead | CFile::typeBinary);
			file.Read(p_src_image, 512 * 512);
			file.Close();
		}
	}
	int k, l = 0;
	int max = 0, min = 0;
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			for (k = 0; k < 8; k++)
			{
				for (l = 0; l < 8; l++)
				{
					block[i][j][k][l] = ori[l + j * 8 + k * 512 + i * 512 * 8];
				}
			}
			dct(block[i][j]);
			for (k = 0; k < 8; k++) {
				for (l = 0; l < 8; l++) {
					DCT[l + j * 8 + k * 512 + i * 512 * 8] = block[i][j][k][l];
					if (min > block[i][j][k][l])
						min = block[i][j][k][l];
					if (max < block[i][j][k][l])
						max = block[i][j][k][l];
				}
			}
			qt(block[i][j], stepsize);
			for (k = 0; k < 8; k++) {
				for (l = 0; l < 8; l++) {
					QT[l + j * 8 + k * 512 + i * 512 * 8] = block[i][j][k][l];
				}
			}
			dq(block[i][j], stepsize);
			for (k = 0; k < 8; k++) {
				for (l = 0; l < 8; l++) {
					DQ[l + j * 8 + k * 512 + i * 512 * 8] = block[i][j][k][l];
				}
			}
			idct(block[i][j]);
			for (k = 0; k < 8; k++) {
				for (l = 0; l < 8; l++) {
					ID[l + j * 8 + k * 512 + i * 512 * 8] = block[i][j][k][l];
				}
			}
		}
	}

	for (int i = 0; i < 512 * 512; i++)
	{
		*p_dest_pos++ = *p_src_pos;
		*p_dest_pos++ = *p_src_pos;
		*p_dest_pos++ = *p_src_pos++;

		*p_dest_pos2++ = (*p_src_pos2 - min ) * 255 / (max - min);
		*p_dest_pos2++ = (*p_src_pos2 - min) * 255 / (max - min);
		*p_dest_pos2++ = (*p_src_pos2 - min) * 255 / (max - min);
		*p_src_pos2++;

		*p_dest_pos3++ = (*p_src_pos3 - min) * 255 / (max - min);
		*p_dest_pos3++ = (*p_src_pos3 - min) * 255 / (max - min);
		*p_dest_pos3++ = (*p_src_pos3 - min) * 255 / (max - min);
		*p_src_pos3++;

		*p_dest_pos4++ = (*p_src_pos4 - min) * 255 / (max - min);
		*p_dest_pos4++ = (*p_src_pos4 - min) * 255 / (max - min);
		*p_dest_pos4++ = (*p_src_pos4 - min) * 255 / (max - min);
		*p_src_pos4++;

		*p_dest_pos5++ = *p_src_pos5;
		*p_dest_pos5++ = *p_src_pos5;
		*p_dest_pos5++ = *p_src_pos5++;
	}

	::SetBitmapBits(m_image, 512 * 512 * 3, p_dest_image);
	::SetBitmapBits(D_image, 512 * 512 * 3, p_dest_image2);
	::SetBitmapBits(Q_image, 512 * 512 * 3, p_dest_image3);
	::SetBitmapBits(DQ_image, 512 * 512 * 3, p_dest_image4);
	::SetBitmapBits(ID_image, 512 * 512 * 3, p_dest_image5);

	delete[] p_dest_image;
	delete[] p_dest_image2;
	delete[] p_dest_image3;
	delete[] p_dest_image4;
	delete[] p_dest_image5;
	
	m_list.ResetContent();
	strf.Format(_T("%f"), MSE(ori, ID, 512 * 512));
	m_list.AddString(strf);

}
void CImagePredictorDlg::printImage()
{
	CClientDC dc(this);
	switch (selectRadio)
	{
	case 1:
		m_image.Draw(dc, 522, 5); break;
	case 2:
		D_image.Draw(dc, 522, 5); break;
	case 3:
		Q_image.Draw(dc, 522, 5); break;
	case 4:
		DQ_image.Draw(dc, 522, 5); break;
	case 5:
		ID_image.Draw(dc, 522, 5); break;

	}
}
float CImagePredictorDlg::MSE(BYTE a[], BYTE b[], int size)
{
	float sum = 0;
	for (int i = 0; i < size; i++) {
		sum = sum + pow(a[i] - b[i],2);
	}
	sum = sum / (float)size;
	return sum;
}
