//Arrow.cpp
/*
	������Ʈ �� : Rush & Chart
	�� �� �� : Arrow.cpp
	�� �� �� : 2014�� 07�� 22��
	��    �� : i5(five)
	��    �� : �ȿ��� ( ���� ), ä����, ������, ����(�۰�), ������ 
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