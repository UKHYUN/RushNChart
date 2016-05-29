//Sequence.cpp
/*
	������Ʈ �� : Rush & Chart
	�� �� �� : Sequence.cpp
	�� �� �� : 2014�� 05�� 16��
	��    �� : i5(five)
	��    �� : �ȿ��� ( ���� ), ä����, ������, ����(�۰�), ������ 
*/

#include "Sequence.h"

Sequence::Sequence () 
	: Symbol ( 0, 0, 240, 40, 8, 8, 232, 32, L"" ) {	
		this->upSign = -1 ;
		this->downSign = -1 ;

}

Sequence::Sequence ( Long startPointX, Long startPointY, wstring expression )
	:Symbol ( startPointX, startPointY, startPointX+280, startPointY+40, startPointX+8, startPointY+8, 
				startPointX + 272 , startPointY + 32, expression ){
					this->upSign = -1 ;
					this->downSign = -1 ;


}

Sequence::Sequence( Long startPointX, Long startPointY, Long endPointX, Long endPointY )
	:Symbol ( startPointX, startPointY, startPointY, startPointY ) {
		this->expressionStartPointX = startPointX + 8;
		this->expressionStartPointY = (endPointY-startPointY)/2 - 12 + startPointY;		
		this->expressionEndPointX = endPointX - 8;
		this->expressionEndPointY = (endPointY - startPointY)/2 + 12 + startPointY ;
		this->upSign = -1 ;
		this->downSign = -1 ;


}

Sequence::Sequence( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression )
		:Symbol ( startPointX, startPointY, endPointX, endPointY, expression ){

			this->expressionStartPointX = this->startPointX + 8;
			this->expressionStartPointY = this->startPointY + (this->endPointY-this->startPointY)/2 - 12 ;		
			this->expressionEndPointX = this->endPointX - 8;
			this->expressionEndPointY = this->startPointY + (this->endPointY - this->startPointY)/2 + 12 ;
			this->upSign = -1 ;
			this->downSign = -1 ;

}

Sequence:: Sequence ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, 
			Long expressionStartpointX, Long expressionStartpointY, Long expressionEndPointX, 
			Long expressionEndPointY, wstring expression )
			: Symbol ( startPointX, startPointY, endPointX, endPointY, expressionStartpointX, 
			expressionStartpointY, expressionEndPointX, expressionEndPointY, expression ){
				this->upSign = -1 ;
				this->downSign = -1 ;

}
		

Sequence::~Sequence( )	{
}

Sequence::Sequence ( const Sequence& source )
	:Symbol ( source ) {
		this->upSign = source.upSign ;
		this->downSign = source.downSign ;

}

Sequence& Sequence::operator= ( const Sequence& source ) {
	Symbol::operator = (source);
	this->upSign = source.upSign ;
	this->downSign = source.downSign ;

	return *this;
}