#include "SelectedSymbol.h"
#include "Paper.h"
#include "Chart.h"
#include "Symbol.h"
#include <afxwin.h>

SelectedSymbol::SelectedSymbol( ){
	
	this->selectedSymbolIndex = 0;

	this->leftTopStartPointX = 0;
	this->leftTopStartPointY = 0;
	this->leftTopEndPointX = 0;
	this->leftTopEndPointY = 0;
		
	this->leftMiddleStartPointX = 0;
	this->leftMiddleStartPointY = 0;
	this->leftMiddleEndPointX = 0;
	this->leftMiddleEndPointY = 0;

	this->leftBottomStartPointX = 0;
	this->leftBottomStartPointY = 0;
	this->leftBottomEndPointX = 0;
	this->leftBottomEndPointY = 0;

	this->middleTopStartPointX = 0;
	this->middleTopStartPointY = 0;
	this->middleTopEndPointX = 0;
	this->middleTopEndPointY = 0;
		
	this->middleStartPointX = 0;
	this->middleStartPointY = 0;
	this->middleEndPointX = 0;
	this->middleEndPointY = 0;
		
	this->middleBottomStartPointX = 0;
	this->middleBottomStartPointY = 0;
	this->middleBottomEndPointX = 0;
	this->middleBottomEndPointY = 0;

	this->rightTopStartPointX = 0;
	this->rightTopStartPointY = 0;
	this->rightTopEndPointX = 0;
	this->rightTopEndPointY = 0;

	this->rightMiddleStartPointX = 0;
	this->rightMiddleStartPointY = 0;
	this->rightMiddleEndPointX = 0;
	this->rightMiddleEndPointY = 0;

	this->rightBottomStartPointX = 0;
	this->rightBottomStartPointY = 0;
	this->rightBottomEndPointX = 0;
	this->rightBottomEndPointY = 0;
}

SelectedSymbol::SelectedSymbol( const SelectedSymbol& source ){
	TRACE("SelectedSymbol복사생성자\n");
	this->selectedSymbolIndex = source.selectedSymbolIndex;

	this->leftTopStartPointX = source.leftTopStartPointX;
	this->leftTopStartPointY = source.leftTopStartPointY;
	this->leftTopEndPointX = source.leftTopEndPointX;
	this->leftTopEndPointY = source.leftTopEndPointY;
		
	this->leftMiddleStartPointX = source.leftMiddleStartPointX;
	this->leftMiddleStartPointY = source.leftMiddleStartPointY;
	this->leftMiddleEndPointX = source.leftMiddleEndPointX;
	this->leftMiddleEndPointY = source.leftMiddleEndPointY;

	this->leftBottomStartPointX = source.leftBottomStartPointX;
	this->leftBottomStartPointY = source.leftBottomStartPointY;
	this->leftBottomEndPointX = source.leftBottomEndPointX;
	this->leftBottomEndPointY = source.leftBottomEndPointY;

	this->middleTopStartPointX = source.middleTopStartPointX;
	this->middleTopStartPointY = source.middleTopStartPointY;
	this->middleTopEndPointX = source.middleTopEndPointX;
	this->middleTopEndPointY = source.middleTopEndPointY;
		
	this->middleStartPointX = source.middleStartPointX;
	this->middleStartPointY = source.middleStartPointY;
	this->middleEndPointX = source.middleEndPointX;
	this->middleEndPointY = source.middleEndPointY;
		
	this->middleBottomStartPointX = source.middleBottomStartPointX;
	this->middleBottomStartPointY = source.middleBottomStartPointY;
	this->middleBottomEndPointX = source.middleBottomEndPointX;
	this->middleBottomEndPointY = source.middleBottomEndPointY;

	this->rightTopStartPointX = source.rightTopStartPointX;
	this->rightTopStartPointY = source.rightTopStartPointY;
	this->rightTopEndPointX = source.rightTopEndPointX;
	this->rightTopEndPointY = source.rightTopEndPointY;

	this->rightMiddleStartPointX = source.rightMiddleStartPointX;
	this->rightMiddleStartPointY = source.rightMiddleStartPointY;
	this->rightMiddleEndPointX = source.rightMiddleEndPointX;
	this->rightMiddleEndPointY = source.rightMiddleEndPointY;

	this->rightBottomStartPointX = source.rightBottomStartPointX;
	this->rightBottomStartPointY = source.rightBottomStartPointY;
	this->rightBottomEndPointX = source.rightBottomEndPointX;
	this->rightBottomEndPointY = source.rightBottomEndPointY;
}

SelectedSymbol::SelectedSymbol( Long selectedSymbolIndex, Long leftTopStartPointX, Long leftTopStartPointY, Long leftTopEndPointX,
		Long leftTopEndPointY, Long leftMiddleStartPointX, Long leftMiddleStartPointY, Long leftMiddleEndPointX,
		Long leftMiddleEndPointY, Long leftBottomStartPointX,Long leftBottomStartPointY, Long leftBottomEndPointX,
		Long leftBottomEndPointY, Long middleTopStartPointX, Long middleTopStartPointY, Long middleTopEndPointX, 
		Long middleTopEndPointY, Long middleStartPointX, Long middleStartPointY, Long middleEndPointX, Long middleEndPointY,
		Long middleBottomStartPointX, Long middleBottomStartPointY, Long middleBottomEndPointX, Long middleBottomEndPointY,
		Long rightTopStartPointX, Long rightTopStartPointY, Long rightTopEndPointX, Long rightTopEndPointY, Long rightMiddleStartPointX,
		Long rightMiddleStartPointY, Long rightMiddleEndPointX, Long rightMiddleEndPointY, Long rightBottomStartPointX,
		Long rightBottomStartPointY, Long rightBottomEndPointX, Long rightBottomEndPointY ){

			this->selectedSymbolIndex = selectedSymbolIndex;

			this->leftTopStartPointX = leftTopStartPointX;
			this->leftTopStartPointY = leftTopStartPointY;
			this->leftTopEndPointX = leftTopEndPointX;
			this->leftTopEndPointY = leftTopEndPointY;

			this->leftMiddleStartPointX = leftMiddleStartPointX;
			this->leftMiddleStartPointY = leftMiddleStartPointY;
			this->leftMiddleEndPointX = leftMiddleEndPointX;
			this->leftMiddleEndPointY = leftMiddleEndPointY;

			this->leftBottomStartPointX = leftBottomStartPointX;
			this->leftBottomStartPointY = leftBottomStartPointY;
			this->leftBottomEndPointX = leftBottomEndPointX;
			this->leftBottomEndPointY = leftBottomEndPointY;

			this->middleTopStartPointX = middleTopStartPointX;
			this->middleTopStartPointY = middleTopStartPointY;
			this->middleTopEndPointX = middleTopEndPointX;
			this->middleTopEndPointY = middleTopEndPointY;

			this->middleBottomStartPointX = middleBottomStartPointX;
			this->middleBottomStartPointY = middleBottomStartPointY;
			this->middleBottomEndPointX = middleBottomEndPointX;
			this->middleBottomEndPointY = middleBottomEndPointY;

			this->rightTopStartPointX = rightTopStartPointX;
			this->rightTopStartPointY = rightTopStartPointY;
			this->rightTopEndPointX = rightTopEndPointX;
			this->rightTopEndPointY = rightTopEndPointY;

			this->rightMiddleStartPointX = rightMiddleStartPointX;
			this->rightMiddleStartPointY = rightMiddleStartPointY;
			this->rightMiddleEndPointX = rightMiddleEndPointX;
			this->rightMiddleEndPointY = rightMiddleEndPointY;

			this->rightBottomStartPointX = rightBottomStartPointX;
			this->rightBottomStartPointY = rightBottomStartPointY;
			this->rightBottomEndPointX = rightBottomEndPointX;
			this->rightBottomEndPointY = rightBottomEndPointY;
			
			this->middleStartPointX = middleStartPointX;
			this->middleStartPointY = middleStartPointY;
			this->middleEndPointX = middleEndPointX;
			this->middleEndPointY = middleEndPointY;
}

SelectedSymbol& SelectedSymbol::operator = ( const SelectedSymbol& source ){

	this->selectedSymbolIndex = source.selectedSymbolIndex;
	
	this->leftTopStartPointX = source.leftTopStartPointX;
	this->leftTopStartPointY = source.leftTopStartPointY;
	this->leftTopEndPointX = source.leftTopEndPointX;
	this->leftTopEndPointY = source.leftTopEndPointY;
		
	this->leftMiddleStartPointX = source.leftMiddleStartPointX;
	this->leftMiddleStartPointY = source.leftMiddleStartPointY;
	this->leftMiddleEndPointX = source.leftMiddleEndPointX;
	this->leftMiddleEndPointY = source.leftMiddleEndPointY;

	this->leftBottomStartPointX = source.leftBottomStartPointX;
	this->leftBottomStartPointY = source.leftBottomStartPointY;
	this->leftBottomEndPointX = source.leftBottomEndPointX;
	this->leftBottomEndPointY = source.leftBottomEndPointY;

	this->middleTopStartPointX = source.middleTopStartPointX;
	this->middleTopStartPointY = source.middleTopStartPointY;
	this->middleTopEndPointX = source.middleTopEndPointX;
	this->middleTopEndPointY = source.middleTopEndPointY;
		
	this->middleStartPointX = source.middleStartPointX;
	this->middleStartPointY = source.middleStartPointY;
	this->middleEndPointX = source.middleEndPointX;
	this->middleEndPointY = source.middleEndPointY;
		
	this->middleBottomStartPointX = source.middleBottomStartPointX;
	this->middleBottomStartPointY = source.middleBottomStartPointY;
	this->middleBottomEndPointX = source.middleBottomEndPointX;
	this->middleBottomEndPointY = source.middleBottomEndPointY;

	this->rightTopStartPointX = source.rightTopStartPointX;
	this->rightTopStartPointY = source.rightTopStartPointY;
	this->rightTopEndPointX = source.rightTopEndPointX;
	this->rightTopEndPointY = source.rightTopEndPointY;

	this->rightMiddleStartPointX = source.rightMiddleStartPointX;
	this->rightMiddleStartPointY = source.rightMiddleStartPointY;
	this->rightMiddleEndPointX = source.rightMiddleEndPointX;
	this->rightMiddleEndPointY = source.rightMiddleEndPointY;

	this->rightBottomStartPointX = source.rightBottomStartPointX;
	this->rightBottomStartPointY = source.rightBottomStartPointY;
	this->rightBottomEndPointX = source.rightBottomEndPointX;
	this->rightBottomEndPointY = source.rightBottomEndPointY;

	return *this;
}

SelectedSymbol::~SelectedSymbol(){
}
