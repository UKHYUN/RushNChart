//Selection.cpp
/*
	프로젝트명 : Rush & Chart
	파  일  명 : BeforeRepeat.cpp
	작  성  일 : 2014년 05월 16일
	팀      명 : i5(five)
	팀      원 : 안영보 ( 팀장 ), 채형석, 김지수, 고요셉(작가), 곽욱현 
*/
#include "Selection.h"
Selection::Selection () 
	: Symbol ( 0, 0, 240, 80, 60, 8, 180, 32, L"" ) {
	this->middlePointX = 120;
	this->middlePointY = 80;
	this->upSign = -1 ;
	this->trueSign = -1 ;
	this->falseSign = -1 ;
}

Selection::Selection ( Long startPointX, Long startPointY, wstring expression )
	: Symbol (  startPointX, startPointY, startPointX + 280, startPointY+40 ,
				startPointX + 70 , startPointY -2 , startPointX + 210 , startPointY + 22 , expression ) {

		this->middlePointX = this->startPointX + 140 ;
		this->middlePointY = this->endPointY ;
		this->upSign = -1 ;
		this->trueSign = -1 ;
		this->falseSign = -1 ;
}

Selection::Selection ( Long startPointX, Long startPointY, Long endPointX, Long endPointY )
	:Symbol ( startPointX, startPointY, endPointX, endPointY )	{
		this->middlePointX = this->startPointX + ( this->endPointX - this->startPointX )/2 ;
		this->middlePointY = this->endPointY;
		this->expressionStartPointX = ( this->middlePointX - this->startPointX )/2 + this->startPointX;
		this->expressionStartPointY = ( ( this->endPointY - this->startPointY )/4 -12 ) + this->startPointY;
		this->expressionEndPointX = ( this->endPointX - this->middlePointX )/2 + this->middlePointX;
		this->expressionEndPointY = ( this->endPointY - this->startPointY )/4 +12 + this->startPointY;
		this->upSign = -1 ;
		this->trueSign = -1 ;
		this->falseSign = -1 ;	
}

Selection::Selection ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression )
	:Symbol ( startPointX, startPointY, endPointX, endPointY, expression ){
		this->middlePointX = ( this->endPointX - this->startPointX )/2 + this->startPointX;
		this->middlePointY = this->endPointY;
		this->expressionStartPointX = ( this->middlePointX - this->startPointX )/2 + this->startPointX;
		this->expressionStartPointY = ( ( this->endPointY - this->startPointY )/4 -12 ) + this->startPointY;
		this->expressionEndPointX = ( this->endPointX - this->middlePointX )/2 + this->middlePointX;
		this->expressionEndPointY = ( this->endPointY - this->startPointY )/4 +12 + this->startPointY;
		this->upSign = -1 ;
		this->trueSign = -1 ;
		this->falseSign = -1 ;
}


Selection:: Selection ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, 
			Long expressionStartpointX, Long expressionStartpointY, Long expressionEndPointX,
			Long expressionEndPointY, wstring expression )
			: Symbol ( startPointX, startPointY, endPointX, endPointY, expressionStartpointX, 
			expressionStartpointY, expressionEndPointX, expressionEndPointY, expression )

{
    this->middlePointX = ( this->endPointX - this->startPointX )/2 + this->startPointX;
    this->middlePointY = this->endPointY;
	this->upSign = -1 ;
	this->trueSign = -1 ;
	this->falseSign = -1 ;
}


Selection::Selection ( Long startPointX, Long startPointY, Long endPointX, Long endPointY,
			Long middlePointX, Long middlePointY )
			:Symbol( startPointX, startPointY, endPointX, endPointY ){
				this->middlePointX = middlePointX;
				this->middlePointY = middlePointY;
				this->expressionStartPointX = ( this->middlePointX - this->startPointX )/2 + this->startPointX;
				this->expressionStartPointY = ( ( this->endPointY - this->startPointY )/4 -12 ) + this->startPointY;
				this->expressionEndPointX = ( this->endPointX - this->middlePointX )/2 + this->middlePointX;
			    this->expressionEndPointY = ( this->endPointY - this->startPointY )/4 +12 + this->startPointY;
				this->upSign = -1 ;
				this->trueSign = -1 ;
				this->falseSign = -1 ;	
}

Selection::Selection ( Long startPointX, Long startPointY, Long endPointX, Long endPointY,
			Long middlePointX, Long middlePointY, wstring expression )
			:Symbol( startPointX, startPointY, endPointX, endPointY, expression ){
				this->middlePointX = middlePointX ;
				this->middlePointY = middlePointY ;
				this->expressionStartPointX = ( this->middlePointX - this->startPointX )/2 + this->startPointX;
				this->expressionStartPointY = ( ( this->endPointY - this->startPointY )/4 -12 ) + this->startPointY;
				this->expressionEndPointX = ( this->endPointX - this->middlePointX )/2 + this->middlePointX;
				this->expressionEndPointY = ( this->endPointY - this->startPointY )/4 +12 + this->startPointY;
				this->upSign = -1 ;
				this->trueSign = -1 ;
				this->falseSign = -1 ;
}

Selection::Selection (
                   Long startPointX,
                   Long startPointY,
                   Long endPointX,
                   Long endPointY,
			
                   Long expressionStartPointX,
                   Long expressionStartPointY,
                   Long expressionEndPointX,
                   Long expressionEndPointY,
                   
				   Long middlePointX,
				   Long middlePointY,

                   wstring expression )
				   :Symbol( startPointX, startPointY, endPointX, endPointY, expressionStartPointX, 
				   expressionStartPointY, expressionEndPointX, expressionEndPointY, expression ){
					    this->middlePointX = middlePointX;
					    this->middlePointY = middlePointY;
						this->upSign = -1 ;
						this->trueSign = -1 ;
						this->falseSign = -1 ;
}


Selection::Selection ( const Selection& source )
	: Symbol ( source.startPointX, source.startPointY, source.endPointX, source.endPointY, 
	source.expressionStartPointX, source.expressionStartPointY, source.expressionEndPointX, 
	source.expressionEndPointY, source.expression )	{
	this->middlePointX = source.middlePointX;
	this->middlePointY = source.middlePointY;
	this->upSign = source.upSign ;
	this->trueSign = source.trueSign ;
	this->falseSign = source.falseSign	;
}

Selection&	Selection::operator = ( const Selection& source ) {
	Symbol::operator= ( source );
	this->middlePointX = source.middlePointX;
	this->middlePointY = source.middlePointY;
	this->upSign = source.upSign ;
	this->trueSign = source.trueSign ;
	this->falseSign = source.falseSign	;

	return *this;
}

Selection::~Selection () {

} 