
#include "Scroll.h"

Scroll::Scroll(){
	
}

Scroll::~Scroll(){
	
}

Scroll::Scroll(const Scroll& source){
	
}

Scroll& Scroll::operator =(const Scroll& source){
	return *this;
}

void Scroll::VScroll(UINT nSBCode, UINT nPos, int *yInc, int *yPos, int *yMax){
	
	switch( nSBCode ){
		
	case SB_LINEUP:
		*yInc = -5;
		break;
		
	case SB_LINEDOWN:
		*yInc = 5;
		break;
		
	case SB_PAGEUP:
		*yInc = -10;
		break;
		
	case SB_PAGEDOWN:
		*yInc = 10;
		break;
		
	case SB_THUMBTRACK:
		*yInc = nPos - *yPos;
		
	default:
		break;

	}
	
	if ( *yPos + *yInc < 0 ) {	// 최소값 가드
		*yInc = - *yPos;
	}
	
	if ( *yPos+ *yInc > *yMax ) {	// 최대값 가드
		
		*yInc = *yMax - *yPos;
	}

	*yPos = *yPos + *yInc;		// 현재 스크롤 값
	
}

void Scroll::HScroll(UINT nSBCode, UINT nPos, int *xInc, int *xPos, int *xMax){

	switch( nSBCode ){
		
	case SB_LINELEFT:
		*xInc = -5;
		break;
		
	case SB_LINERIGHT:
		*xInc = 5;
		break;
		
	case SB_PAGELEFT:
		*xInc = -10;
		break;
		
	case SB_PAGERIGHT:
		*xInc = 10;
		break;
		
	case SB_THUMBTRACK:
		*xInc = nPos - *xPos;

	default:
		break;
	}
	
	if ( *xPos + *xInc < 0 ) {
		*xInc = -*xPos;
	}
	
	if ( *xPos + *xInc > *xMax ) {
		
		*xInc = *xMax - *xPos;
	}
	
	*xPos = *xPos + *xInc;
}

void Scroll::KeyDown(UINT nChar, int *xInc, int *xPos, int *xMax, int *yInc, int *yPos, int *yMax){

	switch(nChar){
		
	case VK_LEFT:
		*xInc = -10;
		break;
		
	case VK_RIGHT:
		*xInc = 10;
		break;
		
	case VK_UP:
		*yInc = -10;
		break;
		
	case VK_DOWN:
		*yInc = 10;
		break;
		
	case VK_PRIOR:
		*yInc = -800;
		break;
		
	case VK_NEXT:
		*yInc = 800;
		break;

	default:
		break;

		
	}
	
	if ( *xPos + *xInc < 0 ) {
		*xInc = -*xPos;
	}
	
	if ( *xPos + *xInc > *xMax ) {
		
		*xInc = *xMax - *xPos;
	}
	
	*xPos = *xPos + *xInc;
		
	if ( *yPos + *yInc < 0 ) {	// 최소값 가드
		*yInc = -*yPos;
	}
	
	if ( *yPos+ *yInc > *yMax ) {	// 최대값 가드
		
		*yInc = *yMax - *yPos;
	}

	*yPos = *yPos + *yInc;		// 현재 스크롤 값
	
}

void Scroll::MouseWheel(short zDelta, int *yInc, int *yPos, int *yMax){

	if ( zDelta >0 ) {
		*yInc = -50;
	}
	
	else {
		*yInc = 50;
	}
	
	if ( *yPos + *yInc < 0 ) {	// 최소값 가드
		*yInc = - *yPos;
	}
	
	if ( *yPos + *yInc > *yMax ) {	// 최대값 가드
		
		*yInc = *yMax - *yPos;
	}
	
	*yPos = *yPos + *yInc;		// 현재 스크롤 값
	
}