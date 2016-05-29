#ifndef _SELECTEDSYMBOL_
#define _SELECTEDSYMBOL_
typedef signed long int Long;

class Paper;
class Symbol;

class SelectedSymbol{
public:
	SelectedSymbol( );
	~SelectedSymbol( );
	SelectedSymbol( const SelectedSymbol& source );
	SelectedSymbol( Long selectedSymbolIndex, Long leftTopStartPointX, Long leftTopStartPointY, Long leftTopEndPointX,
		Long leftTopEndPointY, Long leftMiddleStartPointX, Long leftMiddleStartPointY, Long leftMiddleEndPointX,
		Long leftMiddleEndPointY, Long leftBottomStartPointX,Long leftBottomStartPointY, Long leftBottomEndPointX,
		Long leftBottomEndPointY, Long middleTopStartPointX, Long middleTopStartPointY, Long middleTopEndPointX, 
		Long middleTopEndPointY, Long middleStartPointX, Long middleStartPointY, Long middleEndPointX, Long middleEndPointY,
		Long middleBottomStartPointX, Long middleBottomStartPointY, Long middleBottomEndPointX, Long middleBottomEndPointY,
		Long rightTopStartPointX, Long rightTopStartPointY, Long rightTopEndPointX, Long rightTopEndPointY, Long rightMiddleStartPointX,
		Long rightMiddleStartPointY, Long rightMiddleEndPointX, Long rightMiddleEndPointY, Long rightBottomStartPointX,
		Long rightBottomStartPointY, Long rightBottomEndPointX, Long rightBottomEndPointY ); 
		
		
	SelectedSymbol& operator = ( const SelectedSymbol& source );
	
	Long GetSeletedSymbolIndex() const;

	Long GetLeftTopStartPointX() const;
	Long GetLeftTopStartPointY() const;
	Long GetLeftTopEndPointX() const;
	Long GetLeftTopEndPointY() const;
		
	Long GetLeftMiddleStartPointX() const;
	Long GetLeftMiddleStartPointY() const;
	Long GetLeftMiddleEndPointX() const;
	Long GetLeftMiddleEndPointY() const;
	
	Long GetLeftBottomStartPointX() const;
	Long GetLeftBottomStartPointY() const;
	Long GetLeftBottomEndPointX() const;
	Long GetLeftBottomEndPointY() const;

	Long GetMiddleTopStartPointX() const;
	Long GetMiddleTopStartPointY() const;
	Long GetMiddleTopEndPointX() const;
	Long GetMiddleTopEndPointY() const;
		
	Long GetMiddleStartPointX() const;
	Long GetMiddleStartPointY() const;
	Long GetMiddleEndPointX() const;
	Long GetMiddleEndPointY() const;
		
	Long GetMiddleBottomStartPointX() const;
	Long GetMiddleBottomStartPointY() const;
	Long GetMiddleBottomEndPointX() const;
	Long GetMiddleBottomEndPointY() const;

	Long GetRightTopStartPointX() const;
	Long GetRightTopStartPointY() const;
	Long GetRightTopEndPointX() const;
	Long GetRightTopEndPointY() const;

	Long GetRightMiddleStartPointX() const;
	Long GetRightMiddleStartPointY() const;
	Long GetRightMiddleEndPointX() const;
	Long GetRightMiddleEndPointY() const;

	Long GetRightBottomStartPointX() const;
	Long GetRightBottomStartPointY() const;
	Long GetRightBottomEndPointX() const;
	Long GetRightBottomEndPointY() const;

	private :
		Long selectedSymbolIndex; // '수정점을 만들어야 하는 기호'의 주소가 저장된 '배열의 첨자'

		//왼쪽 위 점
		Long leftTopStartPointX;
		Long leftTopStartPointY;
		Long leftTopEndPointX;
		Long leftTopEndPointY;
		
		//왼쪽 중간 점
		Long leftMiddleStartPointX;
		Long leftMiddleStartPointY;
		Long leftMiddleEndPointX;
		Long leftMiddleEndPointY;

		//왼쪽 바닥 점
 		Long leftBottomStartPointX;
		Long leftBottomStartPointY;
		Long leftBottomEndPointX;
		Long leftBottomEndPointY;

		//중간 위 점
		Long middleTopStartPointX;
		Long middleTopStartPointY;
		Long middleTopEndPointX;
		Long middleTopEndPointY;
		
		//중간 중간 점// 셀렉션 중간 점
		Long middleStartPointX;
		Long middleStartPointY;
		Long middleEndPointX;
		Long middleEndPointY;
		
		//중간 바닥 점
		Long middleBottomStartPointX;
		Long middleBottomStartPointY;
		Long middleBottomEndPointX;
		Long middleBottomEndPointY;

		//오른쪽 위 점
		Long rightTopStartPointX;
		Long rightTopStartPointY;
		Long rightTopEndPointX;
		Long rightTopEndPointY;

		//오른쪽 중간 점
		Long rightMiddleStartPointX;
		Long rightMiddleStartPointY;
		Long rightMiddleEndPointX;
		Long rightMiddleEndPointY;

		//오른쪽 아래 점
		Long rightBottomStartPointX;
		Long rightBottomStartPointY;
		Long rightBottomEndPointX;
		Long rightBottomEndPointY;

};

inline Long SelectedSymbol::GetSeletedSymbolIndex() const	{
	return this->selectedSymbolIndex;
}


inline Long SelectedSymbol::GetLeftTopStartPointX() const	{
	return this->leftTopStartPointX;
}

inline Long SelectedSymbol::GetLeftTopStartPointY() const	{
	return this->leftTopStartPointY;
}
inline Long SelectedSymbol::GetLeftTopEndPointX() const	{
	return this->leftTopEndPointX;
}

inline Long SelectedSymbol::GetLeftTopEndPointY() const	{
	return this->leftTopEndPointY;
}

		
inline Long SelectedSymbol::GetLeftMiddleStartPointX() const	{
	return this->leftMiddleStartPointX;
}

inline Long SelectedSymbol::GetLeftMiddleStartPointY() const	{
	return this->leftMiddleStartPointY;
}

inline Long SelectedSymbol::GetLeftMiddleEndPointX() const	{
	return this->leftMiddleEndPointX;
}

inline Long SelectedSymbol::GetLeftMiddleEndPointY() const	{
	return this->leftMiddleEndPointY;
}


inline Long SelectedSymbol::GetLeftBottomStartPointX() const	{
	return this->leftBottomStartPointX;
}

inline Long SelectedSymbol::GetLeftBottomStartPointY() const	{
	return this->leftBottomStartPointY;
}

inline Long SelectedSymbol::GetLeftBottomEndPointX() const	{
	return this->leftBottomEndPointX;
}

inline Long SelectedSymbol::GetLeftBottomEndPointY() const	{
	return this->leftBottomEndPointY;
}


inline Long SelectedSymbol::GetMiddleTopStartPointX() const	{
	return this->middleTopStartPointX;
}

inline Long SelectedSymbol::GetMiddleTopStartPointY() const	{
	return this->middleTopStartPointY;
}

inline Long SelectedSymbol::GetMiddleTopEndPointX() const	{
	return this->middleTopEndPointX;
}

inline Long SelectedSymbol::GetMiddleTopEndPointY() const	{
	return this->middleTopEndPointY;
}

		
inline Long SelectedSymbol::GetMiddleStartPointX() const	{
	return this->middleStartPointX;
}

inline Long SelectedSymbol::GetMiddleStartPointY() const	{
	return this->middleStartPointY;
}

inline Long SelectedSymbol::GetMiddleEndPointX() const	{
	return this->middleEndPointX;
}

inline Long SelectedSymbol::GetMiddleEndPointY() const	{
	return this->middleEndPointY;
}

		
inline Long SelectedSymbol::GetMiddleBottomStartPointX() const	{
	return this->middleBottomStartPointX;
}

inline Long SelectedSymbol::GetMiddleBottomStartPointY() const	{
	return this->middleBottomStartPointY;
}

inline Long SelectedSymbol::GetMiddleBottomEndPointX() const	{
	return this->middleBottomEndPointX;
}

inline Long SelectedSymbol::GetMiddleBottomEndPointY() const	{
	return this->middleBottomEndPointY;
}


inline Long SelectedSymbol::GetRightTopStartPointX() const	{
	return this->rightTopStartPointX;
}

inline Long SelectedSymbol::GetRightTopStartPointY() const	{
	return this->rightTopStartPointY;
}

inline Long SelectedSymbol::GetRightTopEndPointX() const	{
	return this->rightTopEndPointX;
}

inline Long SelectedSymbol::GetRightTopEndPointY() const	{
	return this->rightTopEndPointY;
}


inline Long SelectedSymbol::GetRightMiddleStartPointX() const	{
	return this->rightMiddleStartPointX;
}

inline Long SelectedSymbol::GetRightMiddleStartPointY() const	{
	return this->rightMiddleStartPointY;
}

inline Long SelectedSymbol::GetRightMiddleEndPointX() const	{
	return this->rightMiddleEndPointX;
}

inline Long SelectedSymbol::GetRightMiddleEndPointY() const	{
	return this->rightMiddleEndPointY;
}


inline Long SelectedSymbol::GetRightBottomStartPointX() const	{
	return this->rightBottomStartPointX;
}

inline Long SelectedSymbol::GetRightBottomStartPointY() const	{
	return this->rightBottomStartPointY;
}

inline Long SelectedSymbol::GetRightBottomEndPointX() const	{
	return this->rightBottomEndPointX;
}

inline Long SelectedSymbol::GetRightBottomEndPointY() const	{
	return this->rightBottomEndPointY;
}

#endif	