
// RGBDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "RGB.h"
#include "RGBDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void chageColor(Mat img, Mat &copy, int i);
Mat show_img;
Mat gray_red;
Mat gray_blue;
Mat gray_green;
Mat open_red;
Mat close_red;
Mat open_green;
Mat close_green;
Mat open_blue;
Mat close_blue;
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRGBDlg ��ȭ ����



CRGBDlg::CRGBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RGB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRGBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_Img, m_pic);
//	DDX_Control(pDX, IDC_Img, m_pic);
}

BEGIN_MESSAGE_MAP(CRGBDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Img_Search, &CRGBDlg::OnBnClickedImgSearch)
	ON_BN_CLICKED(IDC_Img_Save, &CRGBDlg::OnBnClickedImgSave)
END_MESSAGE_MAP()


// CRGBDlg �޽��� ó����

BOOL CRGBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}
int otsu(long int H[]) {

	int sum_h = 0;;

	double n_H[256] = { 0, };
	double m0[256] = { 0, };
	double w0[256] = { 0, };
	double m1[256] = { 0, };
	double w1[256] = { 0, };

	int otsu_i;
	double otsu_max = -1;

	for (int i = 0; i < 256; i++) {
		sum_h += H[i];
	}
	for (int i = 0; i < 256; i++) {
		n_H[i] = (double)H[i] / (double)sum_h;
	}

	for (int i = 0; i < 256; i++) {
		if (i == 0)
			w0[i] = n_H[i];
		else {
			w0[i] = w0[i - 1] + n_H[i];
		}

		double sum_m0 = 0;
		if (i == 0) {
			m0[i] = ((double)i * n_H[i]) / w0[i];
			sum_m0 = sum_m0 + (double)i * n_H[i];
		}
		else {
			sum_m0 = sum_m0 + (double)i * n_H[i];
			m0[i] = sum_m0 / w0[i];
		}

		w1[i] = (double)1 - w0[i];


	}
	double extra_m1_sum = 0;

	for (int i = 255; i >= 0; i--) {

		if (i == 255) {
			m1[i] = 0;
		}
		else {
			extra_m1_sum = extra_m1_sum + (double)(i + 1)*n_H[i + 1];

			m1[i] = extra_m1_sum / w1[i];
		}
	}





	double total_mean = m0[255];

	for (int i = 0; i < 256; i++) {
		double avg = (m0[i] - total_mean)*(m0[i] - total_mean)*w0[i] + (m1[i] - total_mean)*(m1[i] - total_mean)*w1[i];

		if (avg > otsu_max) {
			otsu_max = avg;
			otsu_i = i;
		}

	}

	return otsu_i;
}


void changeGray(Mat &copy) {
	long int H[256] = { 0, };

	for (int y = 0; y < copy.rows; y++) {
		unsigned char* ptr1 = copy.data + 3 * (copy.cols*y);


		for (int x = 0; x < copy.cols; x++) {

			unsigned char tmp = ptr1[3 * x + 0] * 0.114 + ptr1[3 * x + 1] * 0.587 + ptr1[3 * x + 2] * 0.299;
			//unsigned char tmp1 = (ptr1[3 * x + 0] + ptr1[3 * x + 1] + ptr1[3 * x + 2]) /3;
			ptr1[3 * x + 0] = tmp;
			ptr1[3 * x + 1] = tmp;
			ptr1[3 * x + 2] = tmp;

			H[tmp]++;

		}

	}

	int threshold = otsu(H);

	for (int y = 0; y < copy.rows; y++) {
		unsigned char* ptr1 = copy.data + 3 * (copy.cols*y);


		for (int x = 0; x < copy.cols; x++) {

			unsigned char tmp = ptr1[3 * x + 0];

			if (tmp >= threshold) {
				tmp = 0;
			}
			else {
				tmp = 255;
			}

			ptr1[3 * x + 0] = tmp;
			ptr1[3 * x + 1] = tmp;
			ptr1[3 * x + 2] = tmp;


		}

	}

}

void chageColor(Mat img, Mat &copy, int i)
{

	if (i == 1)
	{
		for (int y = 0; y < copy.rows; y++)
		{
			unsigned char* ptr1 = copy.data + 3 * (copy.cols*y);
			unsigned char* resultptr = copy.data + 3 * (copy.cols*y);
			for (int x = 0; x<copy.cols; x++)
			{
				// �̷��� RGB���� �����Ͽ� �� ���� �ȿ� �ִ� Rgb �ȼ����� �ܻ��� �־���.
				//200 -> 160 -> 110
				//�׸���
				//������ �ʷ����� �ص� ����� �ٲ�Ƿ� �Ժη� �մ��� ����
				ptr1[3 * x + 0] = 0;
				ptr1[3 * x + 1] = 0;
				ptr1[3 * x + 2] = ptr1[3 * x + 2];
			}
		}
	}
	else if (i == 2)
	{
		for (int y = 0; y < copy.rows; y++)
		{
			unsigned char* ptr1 = copy.data + 3 * (copy.cols*y);
			unsigned char* resultptr = copy.data + 3 * (copy.cols*y);
			for (int x = 0; x<copy.cols; x++)
			{
				// �̷��� RGB���� �����Ͽ� �� ���� �ȿ� �ִ� Rgb �ȼ����� �ܻ��� �־���.
				//200 -> 160 -> 110
				//�׸���
				//������ �ʷ����� �ص� ����� �ٲ�Ƿ� �Ժη� �մ��� ����
				ptr1[3 * x + 0] = 0;
				ptr1[3 * x + 1] = ptr1[3 * x + 1];
				ptr1[3 * x + 2] = 0;
			}
		}
	}
	else if (i == 3)
	{
		for (int y = 0; y < copy.rows; y++)
		{
			unsigned char* ptr1 = copy.data + 3 * (copy.cols*y);
			unsigned char* resultptr = copy.data + 3 * (copy.cols*y);
			for (int x = 0; x<copy.cols; x++)
			{
				// �̷��� RGB���� �����Ͽ� �� ���� �ȿ� �ִ� Rgb �ȼ����� �ܻ��� �־���.
				//200 -> 160 -> 110
				//�׸���
				//������ �ʷ����� �ص� ����� �ٲ�Ƿ� �Ժη� �մ��� ����
				ptr1[3 * x + 0] = ptr1[3 * x + 0];
				ptr1[3 * x + 1] = 0;
				ptr1[3 * x + 2] = 0;

			}
		}
	}


}


void CRGBDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CRGBDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CRGBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

Mat erosion(Mat input_img, Mat structure_element) {
	
	Mat output_img(input_img.rows, input_img.cols, CV_8UC3, Scalar(0, 0, 0));
	//zero
	uchar *data_input = input_img.data;
	uchar *data_output = output_img.data;

	for (int y = 0; y < input_img.rows; y++)
	{
		
		for (int x = 0; x < input_img.cols; x++) {

			if (y == 0 || x == 0 || y == input_img.rows - 1 || x == input_img.cols - 1) {
				data_input[y*input_img.cols * 3 + x * 3] = 0;
				data_input[y*input_img.cols * 3 + x * 3 + 1]= 0;
				data_input[y*input_img.cols * 3 + x * 3 + 2]= 0;
			}
		}
	}

	int mY[9] = {-1,-1,-1,0,0,0,1,1,1};
	int mX[9] = {-1,0,1,-1,0,1,-1,0,1};


	for (int y = 1; y < input_img.rows-1; y++)
	{
		
		for (int x = 1; x < input_img.cols-1; x++) {

			bool check = 0;
			
			if (data_input[y*input_img.cols * 3 + x * 3]) {
				int tmp_count = 0;
				for (int a = 0; a < 9; a++) {
					int m_x = x + mX[a];
					int m_y = y + mY[a];

					int tmp1 = data_input[m_y*input_img.cols * 3 + m_x * 3];
					int tmp2 = structure_element.at<uchar>(1 + mY[a], 1 + mX[a]);

					if (tmp1 && tmp2) {
						tmp_count++;
					}

				}

				

				if (tmp_count < 9) {	
					int res = 0;

					output_img.at<Vec3b>(y, x)[0] = res;
					output_img.at<Vec3b>(y, x)[1] = res;
					output_img.at<Vec3b>(y, x)[2] = res;
				}
				if (tmp_count >= 9){

					int res = 255;

					output_img.at<Vec3b>(y, x)[0] = res;
					output_img.at<Vec3b>(y, x)[1] = res;
					output_img.at<Vec3b>(y, x)[2] = res;

				}
			}

			
			
		}
	}

	return output_img;
}

Mat dilation(Mat input_img, Mat structure_element) {

	Mat output_img(input_img.rows, input_img.cols, CV_8UC3, Scalar(0,0,0));
	//zero
	uchar *data_input = input_img.data;

	uchar *data_output = output_img.data;
	for (int y = 0; y < input_img.rows; y++)
	{

		for (int x = 0; x < input_img.cols; x++) {

			if (y == 0 || x == 0 || y == input_img.rows - 1 || x == input_img.cols - 1) {
				data_input[y*input_img.cols * 3 + x * 3] = 0;
				data_input[y*input_img.cols * 3 + x * 3 + 1] = 0;
				data_input[y*input_img.cols * 3 + x * 3 + 2] = 0;
			}
		}
	}

	int mY[9] = { -1,-1,-1,0,0,0,1,1,1 };
	int mX[9] = { -1,0,1,-1,0,1,-1,0,1 };


	for (int y = 1; y < input_img.rows - 1; y++)
	{

		for (int x = 1; x < input_img.cols - 1; x++) {

			if (data_input[y*input_img.cols * 3 + x * 3]) {

				int tmp_count = 0;
				for (int a = 0; a < 9; a++) {
					int m_x = x + mX[a];
					int m_y = y + mY[a];

					int tmp1 = data_input[m_y*input_img.cols * 3 + m_x * 3];

					data_output[m_y*input_img.cols * 3 + m_x * 3] = 255;
					data_output[m_y*input_img.cols * 3 + m_x * 3+1] = 255;
					data_output[m_y*input_img.cols * 3 + m_x * 3+2] = 255;


				}

			}
		}


		
	}

	return output_img;
}

Mat opening(Mat input_img, Mat structure_element) {

	Mat erosion_img = erosion(input_img, structure_element);

	Mat ret_img = dilation(erosion_img, structure_element);

	return ret_img;
}

Mat closing(Mat input_img, Mat structure_element) {


	Mat dilation_img = dilation(input_img, structure_element);

	Mat ret_img = erosion(dilation_img, structure_element);

	return ret_img;
}


void CRGBDlg::OnBnClickedImgSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	static TCHAR BASED_CODE szFilter[] = _T("�̹��� ����(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |�������(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		pathName = dlg.GetPathName();
		CT2CA pszConvertedAnsiString_up(pathName);
		std::string up_pathName_str(pszConvertedAnsiString_up);
		img = cv::imread(up_pathName_str);
		//DisplayImage(img, 3);
		
	}


	
//	changeGray(gray_img);
//	namedWindow("gray", WINDOW_NORMAL);
//	imshow("gray", gray_img);

	//RED
	Mat img_copy = img.clone();
	chageColor(img, img_copy, 1);
//	DisplayImage(img_copy, 3);
	show_img = img_copy;
	gray_red = show_img;
	changeGray(gray_red);
//	namedWindow("red_gray", WINDOW_NORMAL);
//	imshow("red_gray", gray_red);
	
	Mat structure_element(3, 3, CV_8U, Scalar(1));

	open_red = opening(gray_red,structure_element);
	namedWindow("open_red", WINDOW_NORMAL);
	imshow("open_red", open_red);

	close_red = closing(gray_red, structure_element);
	namedWindow("close_red", WINDOW_NORMAL);
	imshow("close_red", close_red);

	

	//GREEN
	img_copy = img.clone();
	chageColor(img, img_copy, 2);
//	DisplayImage(img_copy, 3);
	show_img = img_copy;
	gray_green = show_img;
	changeGray(gray_green);
//	namedWindow("green_gray", WINDOW_NORMAL);
//	imshow("green_gray", gray_green);

	open_green = opening(gray_green, structure_element);
	namedWindow("open_green", WINDOW_NORMAL);
	imshow("open_green", open_green);

	close_green = closing(gray_green, structure_element);
	namedWindow("close_green", WINDOW_NORMAL);
	imshow("close_green", close_green);


	//BLUE
	img_copy = img.clone();
	chageColor(img, img_copy, 3);
//	DisplayImage(img_copy, 3);
	show_img = img_copy;
	gray_blue = show_img;
	changeGray(gray_blue);
//	namedWindow("blue_gray", WINDOW_NORMAL);
//	imshow("blue_gray", gray_blue);


	open_blue = opening(gray_blue, structure_element);
	namedWindow("open_blue", WINDOW_NORMAL);
	imshow("open_blue", open_blue);

	close_blue = closing(gray_blue, structure_element);
	namedWindow("close_blue", WINDOW_NORMAL);
	imshow("close_blue", close_blue);

	
}


void CRGBDlg::DisplayImage(Mat targetMat, int channel)
{
	CDC *pDC = nullptr;
	CImage* mfcImg = nullptr;

	pDC = m_pic.GetDC();
//	CStatic *staticSize = (CStatic *)GetDlgItem(IDC_Img);
//	staticSize->GetClientRect(rect);

	cv::Mat tempImage;
	cv::resize(targetMat, tempImage, Size(rect.Width(), rect.Height()));

	BITMAPINFO bitmapInfo;
	bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
	bitmapInfo.bmiHeader.biBitCount = 24;
	bitmapInfo.bmiHeader.biWidth = tempImage.cols;
	bitmapInfo.bmiHeader.biHeight = tempImage.rows;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	bitmapInfo.bmiHeader.biClrImportant = 0;
	bitmapInfo.bmiHeader.biClrUsed = 0;
	bitmapInfo.bmiHeader.biSizeImage = 0;
	bitmapInfo.bmiHeader.biXPelsPerMeter = 0;

	if (targetMat.channels() == 3)
	{
		mfcImg = new CImage();
		mfcImg->Create(tempImage.cols, tempImage.rows, 24);
	}
	else if (targetMat.channels() == 1)
	{
		cvtColor(tempImage, tempImage, CV_GRAY2RGB);
		mfcImg = new CImage();
		mfcImg->Create(tempImage.cols, tempImage.rows, 24);
	}
	else if (targetMat.channels() == 4)
	{
		bitmapInfo.bmiHeader.biBitCount = 32;
		mfcImg = new CImage();
		mfcImg->Create(tempImage.cols, tempImage.rows, 32);
	}
	cv::flip(tempImage, tempImage, 0);
	::StretchDIBits(mfcImg->GetDC(), 0, 0, tempImage.cols, tempImage.rows,
		0, 0, tempImage.cols, tempImage.rows, tempImage.data, &bitmapInfo,
		DIB_RGB_COLORS, SRCCOPY);

	mfcImg->BitBlt(::GetDC(m_pic.m_hWnd), 0, 0);

	if (mfcImg)
	{
		mfcImg->ReleaseDC();
		delete mfcImg;// mfcImg = nullptr;
	}
	tempImage.release();
	ReleaseDC(pDC);
}


void CRGBDlg::OnBnClickedImgSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	imwrite("open_red.jpg", open_red);
	imwrite("open_green.jpg", open_green);
	imwrite("open_blue.jpg", open_blue);
	imwrite("close_red.jpg", close_red);
	imwrite("close_green.jpg", close_green);
	imwrite("close_blue.jpg", close_blue);
	MessageBox(_T("�̹��� ���� �Ϸ�!"), _T(""));
}








