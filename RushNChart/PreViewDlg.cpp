// PreViewDlg.cpp
#include "PreViewDlg.h"
#include "RushNChart.h"


BEGIN_MESSAGE_MAP(PreViewDlg,CDialog)

	ON_WM_KEYDOWN()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_CLOSE()
	
	ON_COMMAND(ID_PREVIEW_CLOSE,OnEnd)
	ON_COMMAND(ID_PREVIEW_PRINT,OnPrint)

	ON_COMMAND(ID_UPSIZE, OnUpSize)
	ON_COMMAND(ID_DOWNSIZE, OnDownSize)
	ON_COMMAND(ID_PER200,OnPreView200)
	ON_COMMAND(ID_PER150,OnPreView150)
	ON_COMMAND(ID_PER100,OnPreView100)
	ON_COMMAND(ID_PER75,OnPreView75)
	ON_COMMAND(ID_PER50,OnPreView50)
	ON_COMMAND(ID_PER25,OnPreView25)

END_MESSAGE_MAP()

PreViewDlg::PreViewDlg(CWnd *parent)
	:CDialog(PreViewDlg::IDD, parent){

	this->preViewWidth = PREVIEW_WIDTH;
	this->preViewHeight = PREVIEW_HEIGHT;

	this->xPos = 0;
	this->yPos = 0;
	this->xMax = 0;
	this->yMax = 0;

}

PreViewDlg::~PreViewDlg(){
}

//미리보기
void PreViewDlg::DisplayPreView(CDC *memDc){
	CClientDC pDC(this);

	pDC.SetWindowOrg(this->xPos, this->yPos);	// 스크롤 이동 위치 자동보정

	RushNChart *rushNChart = (RushNChart*)this->GetParent();
	CRect paperRect = rushNChart->GetPaperRect();	//종이 영역 크기를 구한다
	int paperRectWidth = paperRect.Width();
	int paperRectHeight = paperRect.Height();
	
	CDC bufferDC;
	CBitmap bitMap;
	bufferDC.CreateCompatibleDC(&pDC);
	bitMap.CreateCompatibleBitmap(&pDC, paperRectWidth, paperRectHeight);
	bufferDC.SelectObject(&bitMap);
	bufferDC.PatBlt(0,0, paperRectWidth, paperRectHeight, BLACKNESS);
	
	this->GetClientRect(this->preViewWindow);//클라이언트 영역
	
	// 메모리DC에 그려진 내용을 현재 DC에 복사 595 X 842
	int x = this->preViewWindow.Width()/2 - this->preViewWidth / 2;
	bufferDC.StretchBlt( x, 0, this->preViewWidth, this->preViewHeight,
						memDc, 0, 0, paperRectWidth, paperRectHeight, SRCCOPY);

	pDC.BitBlt( 0, 0, paperRectWidth, paperRectHeight, &bufferDC, 0, 0, SRCCOPY);

}
///////////////////////////////////////////////////////////////////////////////////////////////

// 키보드 방향키 스크롤
void PreViewDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){

	switch(nChar) {
		case VK_ADD:
			this->preViewWidth += this->preViewWidth /100 * 10;
			this->preViewHeight += this->preViewHeight /100 * 10;

			if ( this->preViewWindow.Height() < this->preViewHeight ) {
				this->yMax = this->preViewHeight - this->preViewWindow.Height() ;
				ShowScrollBar(SB_VERT, TRUE);
				SetScrollRange(SB_VERT,0,this->yMax,TRUE);
			}
			if ( this->preViewWindow.Width() < this->preViewWidth ) {
				this->xMax = this->preViewWidth - this->preViewWindow.Width();
				ShowScrollBar(SB_HORZ, TRUE);
				SetScrollRange(SB_HORZ,0,this->xMax,TRUE);
			}
			break;

		case VK_SUBTRACT:
			this->preViewWidth -= this->preViewWidth /100 * 10;
			this->preViewHeight -= this->preViewHeight /100 * 10;
			
			if ( this->preViewWindow.Height() >= this->preViewHeight ) {
				this->yPos = 0;
				this->yMax = 0;
				ShowScrollBar(SB_VERT, FALSE);
			}
			if ( this->preViewWindow.Width() >= this->preViewWidth ) {
				this->xPos = 0;
				this->xMax = 0;
				ShowScrollBar(SB_HORZ, FALSE);
			}
			break;

		default:
			break;
	}
	InvalidateRect(NULL,FALSE);
}

// 세로 스크롤
void PreViewDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){

	int yInc = 0 ;	// 세로 스크롤 이동한 값

	switch( nSBCode ){
		
	case SB_LINEUP:
		yInc = -5;
		break;
		
	case SB_LINEDOWN:
		yInc = 5;
		break;
		
	case SB_PAGEUP:
		yInc = -10;
		break;
		
	case SB_PAGEDOWN:
		yInc = 10;
		break;
		
	case SB_THUMBTRACK:
		yInc = nPos - this->yPos;
		
	default:
		break;

	}
	
	if ( this->yPos + yInc < 0 ) {	// 최소값 가드
		yInc = -this->yPos;
	}
	
	if ( this->yPos+ yInc > this->yMax ) {	// 최대값 가드
		
		yInc = this->yMax - this->yPos;
	}

	this->yPos = this->yPos + yInc;		// 현재 스크롤 값

	SetScrollPos(SB_VERT, this->yPos, TRUE);	// 스크롤바 위치 설정

}

// 가로 스크롤
void PreViewDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){

	int xInc = 0 ;

	switch( nSBCode ){
		
	case SB_LINELEFT:
		xInc = -5;
		break;
		
	case SB_LINERIGHT:
		xInc = 5;
		break;
		
	case SB_PAGELEFT:
		xInc = -10;
		break;
		
	case SB_PAGERIGHT:
		xInc = 10;
		break;
		
	case SB_THUMBTRACK:
		xInc = nPos - this->xPos;

	default:
		break;
	}
	
	if ( this->xPos + xInc < 0 ) {
		xInc = -this->xPos;
	}
	
	if ( this->xPos + xInc > this->xMax ) {
		
		xInc = this->xMax - this->xPos;
	}
	
	this->xPos = this->xPos + xInc;

	SetScrollPos(SB_HORZ, this->xPos, TRUE);

}

BOOL PreViewDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt){

	int yInc=0;	

	if ( zDelta >0 ) {
		yInc = -50;
	}
	
	else {
		yInc = 50;
	}
	
	if ( this->yPos + yInc < 0 ) {	// 최소값 가드
		yInc = - this->yPos;
	}
	
	if ( this->yPos + yInc > this->yMax ) {	// 최대값 가드
		
		yInc = this->yMax - this->yPos;
	}
	
	this->yPos = this->yPos + yInc;		// 현재 스크롤 값
	
	SetScrollPos(SB_VERT,this->yPos,TRUE);	// 스크롤바 위치 설정

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
void PreViewDlg::OnPrint(){
	RushNChart *rushNChart = (RushNChart*)this->GetParent();

	rushNChart->OnPrintMenuClicked() ;
}


void PreViewDlg::OnClose(){
	RushNChart *rushNChart = (RushNChart*)this->GetParent();
	CDialog::OnOK();

	rushNChart->ClosePreView();
}

void PreViewDlg::OnEnd(){
	RushNChart *rushNChart = (RushNChart*)this->GetParent();
	CDialog::OnOK();

	rushNChart->ClosePreView();
}
//////////////////////////////////////////////////////////////////////////////////
void PreViewDlg::OnUpSize(){
	this->preViewWidth += this->preViewWidth /100 * 10;
	this->preViewHeight += this->preViewHeight /100 * 10;

	if ( this->preViewWindow.Height() < this->preViewHeight ) {
		this->yMax = this->preViewHeight - this->preViewWindow.Height() ;
		ShowScrollBar(SB_VERT, TRUE);
		SetScrollRange(SB_VERT,0,this->yMax,TRUE);
	}
	if ( this->preViewWindow.Width() < this->preViewWidth ) {
		this->xMax = this->preViewWidth - this->preViewWindow.Width();
		ShowScrollBar(SB_HORZ, TRUE);
		SetScrollRange(SB_HORZ,0,this->xMax,TRUE);
	}
}

void PreViewDlg::OnDownSize(){
	this->preViewWidth -= this->preViewWidth /100 * 10;
	this->preViewHeight -= this->preViewHeight /100 * 10;

	if ( this->preViewWindow.Height() >= this->preViewHeight ) {
		this->yPos = 0;
		this->yMax = 0;
		ShowScrollBar(SB_VERT, FALSE);
	}
	if ( this->preViewWindow.Width() >= this->preViewWidth ) {
		this->xPos = 0;
		this->xMax = 0;
		ShowScrollBar(SB_HORZ, FALSE);
	}
}

void PreViewDlg::OnPreView200(){
	this->preViewWidth = PREVIEW_WIDTH * 2;
	this->preViewHeight = PREVIEW_HEIGHT * 2;

	if ( this->preViewWindow.Height() < this->preViewHeight ) {
		this->yMax = this->preViewHeight - this->preViewWindow.Height() ;
		ShowScrollBar(SB_VERT, TRUE);
		SetScrollRange(SB_VERT,0,this->yMax,TRUE);
	}
	if ( this->preViewWindow.Width() < this->preViewWidth ) {
		this->xMax = this->preViewWidth - this->preViewWindow.Width();
		ShowScrollBar(SB_HORZ, TRUE);
		SetScrollRange(SB_HORZ,0,this->xMax,TRUE);
	}
}
void PreViewDlg::OnPreView150(){
	this->preViewWidth = PREVIEW_WIDTH / 100 * 150;
	this->preViewHeight = PREVIEW_HEIGHT / 100 * 150;
	
	if ( this->preViewWindow.Height() < this->preViewHeight ) {
		this->yMax = this->preViewHeight - this->preViewWindow.Height() ;
		ShowScrollBar(SB_VERT, TRUE);
		SetScrollRange(SB_VERT,0,this->yMax,TRUE);
	}
	if ( this->preViewWindow.Width() < this->preViewWidth ) {
		this->xMax = this->preViewWidth - this->preViewWindow.Width();
		ShowScrollBar(SB_HORZ, TRUE);
		SetScrollRange(SB_HORZ,0,this->xMax,TRUE);
	}
}
void PreViewDlg::OnPreView100(){
	this->preViewWidth = PREVIEW_WIDTH;
	this->preViewHeight = PREVIEW_HEIGHT;

	if ( this->preViewWindow.Height() >= this->preViewHeight ) {
		this->yPos = 0;
		this->yMax = 0;
		ShowScrollBar(SB_VERT, FALSE);
	}
	if ( this->preViewWindow.Width() >= this->preViewWidth ) {
		this->xPos = 0;
		this->xMax = 0;
		ShowScrollBar(SB_HORZ, FALSE);
	}

}
void PreViewDlg::OnPreView75(){
	this->preViewWidth = PREVIEW_WIDTH / 100 * 75;
	this->preViewHeight = PREVIEW_HEIGHT / 100 * 75;
	
	if ( this->preViewWindow.Height() >= this->preViewHeight ) {
		this->yPos = 0;
		this->yMax = 0;
		ShowScrollBar(SB_VERT, FALSE);
	}
	if ( this->preViewWindow.Width() >= this->preViewWidth ) {
		this->xPos = 0;
		this->xMax = 0;
		ShowScrollBar(SB_HORZ, FALSE);
	}
}
void PreViewDlg::OnPreView50(){
	this->preViewWidth = PREVIEW_WIDTH / 100 * 50;
	this->preViewHeight = PREVIEW_HEIGHT / 100 * 50;
	if ( this->preViewWindow.Height() >= this->preViewHeight ) {
		this->yPos = 0;
		this->yMax = 0;
		ShowScrollBar(SB_VERT, FALSE);
	}
	if ( this->preViewWindow.Width() >= this->preViewWidth ) {
		this->xPos = 0;
		this->xMax = 0;
		ShowScrollBar(SB_HORZ, FALSE);
	}
}
void PreViewDlg::OnPreView25(){
	this->preViewWidth = PREVIEW_WIDTH / 100 * 25;
	this->preViewHeight = PREVIEW_HEIGHT / 100 * 25;
	if ( this->preViewWindow.Height() >= this->preViewHeight ) {
		this->yPos = 0;
		this->yMax = 0;
		ShowScrollBar(SB_VERT, FALSE);
	}
	if ( this->preViewWindow.Width() >= this->preViewWidth ) {
		this->xPos = 0;
		this->xMax = 0;
		ShowScrollBar(SB_HORZ, FALSE);
	}
}
	
