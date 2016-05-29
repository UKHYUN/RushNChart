//Arrow.cpp
/*
	프로젝트 명 : Rush & Chart
	파 일 명 : Arrow.cpp
	작 성 일 : 2014년 07월 22일
	팀    명 : i5(five)
	팀    원 : 안영보 ( 팀장 ), 채형석, 김지수, 고요셉(작가), 곽욱현 
*/

#include "Arrow.h"

Arrow::Arrow () 
	: Symbol ( ) {	

}

Arrow::Arrow ( Long startPointX, Long startPointY )
	:Symbol ( startPointX, startPointY, startPointX, startPointY+40 ){

}

Arrow::Arrow( Long startPointX, Long startPointY, Long endPointX, Long endPointY )
	:Symbol ( startPointX, startPointY, startPointX, endPointY ) {

}

Arrow::~Arrow( )	{
}

Arrow::Arrow ( const Arrow& source )
	:Symbol ( source ) {
		
}

Arrow& Arrow::operator= ( const Arrow& source ) {
	Symbol::operator = (source);

	return *this;
}