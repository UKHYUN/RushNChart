//Symbol.cpp
/*
	프로젝트명 : Rush & Chart
	파  일  명 : Symbol.cpp
	작  성  일 : 2014년 05월 16일
	팀      명 : i5(five)
	팀      원 : 안영보 ( 팀장 ), 채형석, 김지수, 고요셉(작가), 곽욱현 
*/

#include "Symbol.h"


Symbol::Symbol () 
	: expression ( L"" ) {
	this->startPointX = 0;
	this->startPointY = 0;
	this->endPointX = 0;
	this->endPointY = 0;
	this->expressionStartPointX = 0;
	this->expressionStartPointY = 0;
	this->expressionEndPointX = 0;
	this->expressionEndPointY = 0;
}


Symbol::Symbol ( Long startPointX, Long startPointY, wstring expression ) 
	: expression ( expression ) {

	this->startPointX = startPointX;
	this->startPointY = startPointY;
	this->endPointX = 0;
	this->endPointY = 0;
	this->expressionStartPointX = 0;
	this->expressionStartPointY = 0;
	this->expressionEndPointX = 0;
	this->expressionEndPointY = 0;
}


Symbol::Symbol ( Long startPointX, Long startPointY, Long endPointX, Long endPointY )
	:expression( L"" ){
		this->startPointX = startPointX;
		this->startPointY = startPointY;
		this->endPointX = endPointX;
		this->endPointY = endPointY;
		this->expressionStartPointX = 0;
		this->expressionStartPointY = 0;
		this->expressionEndPointX = 0;
		this->expressionEndPointY = 0;
}


Symbol::Symbol ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression )
	:expression( expression ) {
		this->startPointX = startPointX;
		this->startPointY = startPointY;
		this->endPointX = endPointX;
		this->endPointY = endPointY;
		this->expressionStartPointX = 0;
		this->expressionStartPointY = 0;
		this->expressionEndPointX = 0;
		this->expressionEndPointY = 0;
}


Symbol::Symbol ( Long startPointX, 
				 Long startPointY, 
				 Long endPointX, 
				 Long endPointY,
				 Long expressionStartPointX, 
				 Long expressionStartPointY, 
				 Long expressionEndPointX, 
				 Long expressionEndPointY)	{

	this->startPointX = startPointX;
	this->startPointY = startPointY;
	this->endPointX = endPointX;
	this->endPointY = endPointY;

	this->expressionStartPointX = expressionStartPointX;
	this->expressionStartPointY = expressionStartPointY;
	this->expressionEndPointX = expressionEndPointX;
	this->expressionEndPointY = expressionEndPointY;

	this->expression = L"" ;
}


Symbol::Symbol (Long startPointX,
                Long startPointY,
                Long endPointX,
                Long endPointY,
                Long expressionStartPointX,
                Long expressionStartPointY,
                Long expressionEndPointX,
                Long expressionEndPointY,                
                wstring expression )
: expression ( expression ) {
    
	this->startPointX = startPointX;
	this->startPointY = startPointY;
	this->endPointX = endPointX;
	this->endPointY = endPointY;
    
	this->expressionStartPointX = expressionStartPointX;
	this->expressionStartPointY = expressionStartPointY;
	this->expressionEndPointX = expressionEndPointX;
	this->expressionEndPointY = expressionEndPointY;
}


Symbol::Symbol( const Symbol& source )
	:expression( source.expression ){
	this->startPointX = source.startPointX;
	this->startPointY = source.startPointY;
	this->endPointX = source.endPointX;
	this->endPointY = source.endPointY;
	this->expressionStartPointX = source.expressionStartPointX;
	this->expressionStartPointY = source.expressionStartPointY;
	this->expressionEndPointX = source.expressionEndPointX;
	this->expressionEndPointY = source.expressionEndPointY;
}


Symbol&	Symbol::operator= ( const Symbol& source ) {
	this->startPointX = source.startPointX;
	this->startPointY = source.startPointY;
	this->endPointX = source.endPointX;
	this->endPointY = source.endPointY;
	this->expressionStartPointX = source.expressionStartPointX;
	this->expressionStartPointY = source.expressionStartPointY;
	this->expressionEndPointX = source.expressionEndPointX;
	this->expressionEndPointY = source.expressionEndPointY;
	this->expression = source.expression;

	return *this;
}


Symbol::~Symbol( ){
}