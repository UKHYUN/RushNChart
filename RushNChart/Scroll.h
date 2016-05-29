
// Scroll.h
#ifndef _SCROLL_H
#define _SCROLL_H

#include <afxcoll.h>


class Scroll {
	
public:
	Scroll();
	~ Scroll();
	
	Scroll(const Scroll& source);
	Scroll& operator =(const Scroll& source);
	
	void VScroll(UINT nSBCode, UINT nPos, int *yInc, int *yPos, int *yMax);
	void HScroll(UINT nSBCode, UINT nPos, int *xInc, int *xPos, int *xMax);
	void KeyDown(UINT nChar, int *xInc, int *xPos, int *xMax, int *yInc, int *yPos, int *yMax);
	void MouseWheel(short zDelta, int *yInc, int *yPos, int *yMax);

private:
	
};

#endif // _SCROLL_H







