#ifndef _SELECTCHART_H
#define _SELECTCHART_H

typedef signed long int Long;

class Chart;

class SelectChart{

public:

	SelectChart( );
	SelectChart( Long fieldStartPointX, Long fieldStartPointY, Long fieldEndPointX, Long fieldEndPointY, Long leftTopStartPointX, Long leftTopStartPointY, Long leftTopEndPointX,
		Long leftTopEndPointY, Long leftMiddleStartPointX, Long leftMiddleStartPointY, Long leftMiddleEndPointX,
		Long leftMiddleEndPointY, Long leftBottomStartPointX,Long leftBottomStartPointY, Long leftBottomEndPointX,
		Long leftBottomEndPointY, Long middleTopStartPointX, Long middleTopStartPointY, Long middleTopEndPointX, 
		Long middleTopEndPointY, Long middleStartPointX, Long middleStartPointY, Long middleEndPointX, Long middleEndPointY,
		Long middleBottomStartPointX, Long middleBottomStartPointY, Long middleBottomEndPointX, Long middleBottomEndPointY,
		Long rightTopStartPointX, Long rightTopStartPointY, Long rightTopEndPointX, Long rightTopEndPointY, Long rightMiddleStartPointX,
		Long rightMiddleStartPointY, Long rightMiddleEndPointX, Long rightMiddleEndPointY, Long rightBottomStartPointX,
		Long rightBottomStartPointY, Long rightBottomEndPointX, Long rightBottomEndPointY ); 
	SelectChart( const SelectChart& source );
	~SelectChart( );
	
	SelectChart& operator= ( const SelectChart& source );	



	void GetFieldPoint( Chart *chart );
	void DrawChartField( );
	bool CheckChart ( Chart *chart, Long pointX, Long pointY );
	bool CheckChart ( Chart *chart, Long startPointX, Long startPointY, Long endPointX, Long endPointY ) ;

	Long GetFieldStartPointX ( ) const;
	Long GetFieldStartPointY ( ) const;
	Long GetFieldEndPointX ( ) const;
	Long GetFieldEndPointY ( ) const;

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
	Long fieldStartPointX;
	Long fieldStartPointY;
	Long fieldEndPointX;
	Long fieldEndPointY;

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
inline Long SelectChart::GetFieldStartPointX( ) const{
	return this->fieldStartPointX;
}
inline Long SelectChart::GetFieldStartPointY ( ) const{
	return this->fieldStartPointY;
}
inline Long SelectChart::GetFieldEndPointX ( ) const{
	return this->fieldEndPointX;
}
inline Long SelectChart::GetFieldEndPointY ( ) const{
	return this->fieldEndPointY;
}

inline Long SelectChart::GetLeftTopStartPointX() const	{
	return this->leftTopStartPointX;
}

inline Long SelectChart::GetLeftTopStartPointY() const	{
	return this->leftTopStartPointY;
}
inline Long SelectChart::GetLeftTopEndPointX() const	{
	return this->leftTopEndPointX;
}

inline Long SelectChart::GetLeftTopEndPointY() const	{
	return this->leftTopEndPointY;
}

		
inline Long SelectChart::GetLeftMiddleStartPointX() const	{
	return this->leftMiddleStartPointX;
}

inline Long SelectChart::GetLeftMiddleStartPointY() const	{
	return this->leftMiddleStartPointY;
}

inline Long SelectChart::GetLeftMiddleEndPointX() const	{
	return this->leftMiddleEndPointX;
}

inline Long SelectChart::GetLeftMiddleEndPointY() const	{
	return this->leftMiddleEndPointY;
}


inline Long SelectChart::GetLeftBottomStartPointX() const	{
	return this->leftBottomStartPointX;
}

inline Long SelectChart::GetLeftBottomStartPointY() const	{
	return this->leftBottomStartPointY;
}

inline Long SelectChart::GetLeftBottomEndPointX() const	{
	return this->leftBottomEndPointX;
}

inline Long SelectChart::GetLeftBottomEndPointY() const	{
	return this->leftBottomEndPointY;
}

inline Long SelectChart::GetMiddleTopStartPointX() const	{
	return this->middleTopStartPointX;
}

inline Long SelectChart::GetMiddleTopStartPointY() const	{
	return this->middleTopStartPointY;
}

inline Long SelectChart::GetMiddleTopEndPointX() const	{
	return this->middleTopEndPointX;
}

inline Long SelectChart::GetMiddleTopEndPointY() const	{
	return this->middleTopEndPointY;
}

inline Long SelectChart::GetMiddleStartPointX() const	{
	return this->middleStartPointX;
}

inline Long SelectChart::GetMiddleStartPointY() const	{
	return this->middleStartPointY;
}

inline Long SelectChart::GetMiddleEndPointX() const	{
	return this->middleEndPointX;
}

inline Long SelectChart::GetMiddleEndPointY() const	{
	return this->middleEndPointY;
}

inline Long SelectChart::GetMiddleBottomStartPointX() const	{
	return this->middleBottomStartPointX;
}

inline Long SelectChart::GetMiddleBottomStartPointY() const	{
	return this->middleBottomStartPointY;
}

inline Long SelectChart::GetMiddleBottomEndPointX() const	{
	return this->middleBottomEndPointX;
}

inline Long SelectChart::GetMiddleBottomEndPointY() const	{
	return this->middleBottomEndPointY;
}

inline Long SelectChart::GetRightTopStartPointX() const	{
	return this->rightTopStartPointX;
}

inline Long SelectChart::GetRightTopStartPointY() const	{
	return this->rightTopStartPointY;
}

inline Long SelectChart::GetRightTopEndPointX() const	{
	return this->rightTopEndPointX;
}

inline Long SelectChart::GetRightTopEndPointY() const	{
	return this->rightTopEndPointY;
}


inline Long SelectChart::GetRightMiddleStartPointX() const	{
	return this->rightMiddleStartPointX;
}

inline Long SelectChart::GetRightMiddleStartPointY() const	{
	return this->rightMiddleStartPointY;
}

inline Long SelectChart::GetRightMiddleEndPointX() const	{
	return this->rightMiddleEndPointX;
}

inline Long SelectChart::GetRightMiddleEndPointY() const	{
	return this->rightMiddleEndPointY;
}


inline Long SelectChart::GetRightBottomStartPointX() const	{
	return this->rightBottomStartPointX;
}

inline Long SelectChart::GetRightBottomStartPointY() const	{
	return this->rightBottomStartPointY;
}

inline Long SelectChart::GetRightBottomEndPointX() const	{
	return this->rightBottomEndPointX;
}

inline Long SelectChart::GetRightBottomEndPointY() const	{
	return this->rightBottomEndPointY;
}

#endif //_SELECTCHART_H
