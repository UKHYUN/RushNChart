//BeforeRepeat.cpp
/*
	������Ʈ�� : Rush & Chart
	��  ��  �� : BeforeRepeat.cpp
	��  ��  �� : 2014�� 05�� 16��
	��      �� : i5(five)
	��      �� : �ȿ��� ( ���� ), ä����, ������, ����(�۰�), ������ 
*/
#include "BeforeRepeat.h"

BeforeRepeat::BeforeRepeat () 
	: Symbol ( 0, 0, 240, 120, 20, 8, 232, 112, L"" ) {
	this->middlePointX = 40;
	this->middlePointY = 40;
	this->upSign = -1 ;
	this->inSign = -1 ;
	this->downSign = -1 ;
}


BeforeRepeat::BeforeRepeat ( Long startPointX, Long startPointY, wstring expression )
	: Symbol (  startPointX, startPointY, startPointX + 280, startPointY + 120, 
				startPointX + 20, startPointY + 8, startPointX+272,startPointY+32,expression ) {
	this->middlePointX = this->startPointX + 40;
	this->middlePointY = this->startPointY + 40;
	this->upSign = -1 ;
	this->inSign = -1 ;
	this->downSign = -1 ;
}


BeforeRepeat::BeforeRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY )
	: Symbol ( startPointX, startPointY, endPointX, endPointY ){
		if( ( endPointX-startPointX ) <= 80 ){
			this->middlePointX = ( endPointX-startPointX )/2;
		}
		else{
			this->middlePointX = startPointX + 40;
		}
		if( ( endPointY - startPointY ) <= 80 ){
			this->middlePointY = (endPointY - startPointY )/2;
		}
		else{
			this->middlePointY = startPointY + 40;
		}
		this->expressionStartPointX = startPointX + 20;
		this->expressionStartPointY = ( this->middlePointY - startPointY )/2 -12 + startPointY;
		this->expressionEndPointX = endPointX - 8;
		this->expressionEndPointY = ( this->middlePointY - startPointY )/2 + 12 + startPointY;
		this->upSign = -1 ;
		this->inSign = -1 ;
		this->downSign = -1 ;
}

BeforeRepeat::BeforeRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression )
	: Symbol ( startPointX, startPointY, endPointX, endPointY, expression ){

		if( ( this->endPointX-this->startPointX ) <= 80 ){
			this->middlePointX = this->startPointX+( this->endPointX - this->startPointX )/2;
		}
		else{ 
			this->middlePointX = this->startPointX + 40;
		}
		if( ( this->endPointY - this->startPointY ) <= 80 ){
			this->middlePointY = this->startPointY+( this->endPointY - this->startPointY )/2;
		}
		else{
			this->middlePointY = this->startPointY + 40;
		}
		this->expressionStartPointX = this->startPointX + 20;
		this->expressionStartPointY = this->startPointY + ( this->middlePointY - this->startPointY )/2 -12 ;
		this->expressionEndPointX = this->endPointX - 8;
		this->expressionEndPointY = this->startPointY + ( this->middlePointY - this->startPointY )/2 + 12 ;
		this->upSign = -1 ;
		this->inSign = -1 ;
		this->downSign = -1 ;
}


BeforeRepeat::BeforeRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, Long middlePointX,
			Long middlePointY)
			:Symbol( startPointX, startPointY, endPointX, endPointY ){
				this->middlePointX = middlePointX;
				this->middlePointY = middlePointY;
				this->expressionStartPointX = startPointX + 20;
				this->expressionStartPointY = ( this->middlePointY - startPointY )/2 -12 + startPointY;
				this->expressionEndPointX = endPointX - 8;
				this->expressionEndPointY = ( this->middlePointY - startPointY )/2 + 12 + startPointY;
				this->upSign = -1 ;
				this->inSign = -1 ;
				this->downSign = -1 ;	
}


BeforeRepeat::BeforeRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, Long middlePointX,
			Long middlePointY, wstring expression )
			:Symbol( startPointX, startPointY, endPointX, endPointY, expression ){
				this->middlePointX = middlePointX;
				this->middlePointY = middlePointY;
				this->expressionStartPointX = startPointX + 20;
				this->expressionStartPointY = ( this->middlePointY - startPointY )/2 -12 + startPointY;
				this->expressionEndPointX = endPointX - 8;
				this->expressionEndPointY = ( this->middlePointY - startPointY )/2 + 12 + startPointY;
				this->upSign = -1 ;
				this->inSign = -1 ;
				this->downSign = -1 ;
}


BeforeRepeat:: BeforeRepeat (Long startPointX,
                             Long startPointY,
                             Long endPointX,
                             Long endPointY,
                             Long expressionStartPointX,
                             Long expressionStartPointY,
                             Long expressionEndPointX,
                             Long expressionEndPointY,                             
                             wstring expression )
: Symbol ( startPointX, startPointY, endPointX, endPointY, expressionStartPointX, expressionStartPointY, 
expressionEndPointX, expressionEndPointY, expression )	{
    if( ( endPointX-startPointX ) <= 80 ){
        this->middlePointX = ( endPointX-startPointX )/2;
    }
    else{
        this->middlePointX = startPointX + 40;
    }
    if( ( endPointY - startPointY ) <= 80 ){
        this->middlePointY = (endPointY - startPointY )/2;
    }
    else{
        this->middlePointY = startPointY + 40;
    }
	this->upSign = -1 ;
	this->inSign = -1 ;
	this->downSign = -1 ;

}


BeforeRepeat::BeforeRepeat (Long startPointX,
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
						  expressionStartPointY, expressionEndPointX, expressionEndPointY, expression )	{

						  this->middlePointX = middlePointX;
						  this->middlePointY = middlePointY;
						  this->upSign = -1 ;
						  this->inSign = -1 ;
						  this->downSign = -1 ;
}
	

BeforeRepeat::BeforeRepeat ( const BeforeRepeat& source )
	:Symbol ( source.startPointX, source.startPointY, source.endPointX, source.endPointY, source.expressionStartPointX,
	source.expressionStartPointY, source.expressionEndPointX, source.expressionEndPointY, source.expression ){
	this->middlePointX = source.middlePointX;
	this->middlePointY = source.middlePointY;
	this->upSign = source.upSign ;
	this->inSign = source.inSign ;
	this->downSign =source.downSign ;
}


BeforeRepeat&	BeforeRepeat::operator = ( const BeforeRepeat& source ) {
	Symbol::operator= ( source );
	this->middlePointX = source.middlePointX;
	this->middlePointY = source.middlePointY;
	this->upSign = source.upSign ;
	this->inSign = source.inSign ;
	this->downSign =source.downSign ;

	return *this;
}


BeforeRepeat::~BeforeRepeat () {

}