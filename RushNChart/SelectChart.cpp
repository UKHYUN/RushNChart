#include "SelectChart.h"
#include "SelectedSymbol.h"

#include "Paper.h"

#include "Sequence.h"
#include "BeforeRepeat.h"
#include "AfterRepeat.h"
#include "Selection.h"
#include "SwitchCase.h"
#include "Arrow.h"

SelectChart::SelectChart( ) {

	this->fieldStartPointX = 0;
	this->fieldStartPointY = 0;
	this->fieldEndPointX = 0;
	this->fieldEndPointY = 0;

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

SelectChart::SelectChart( const SelectChart& source ) {
	
	this->fieldStartPointX = source.fieldStartPointX;
	this->fieldStartPointY = source.fieldStartPointY;
	this->fieldEndPointX = source.fieldEndPointX;
	this->fieldEndPointY = source.fieldEndPointY;

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

SelectChart::~SelectChart( ){
}

SelectChart& SelectChart::operator= (const SelectChart& source ){
	
	this->fieldStartPointX = source.fieldStartPointX;
	this->fieldStartPointY = source.fieldStartPointY;
	this->fieldEndPointX = source.fieldEndPointX ;
	this->fieldEndPointY = source.fieldEndPointY ;
	
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

SelectChart::SelectChart( Long fieldStartPointX, Long fieldStartPointY, Long fieldEndPointX, Long fieldEndPointY, Long leftTopStartPointX, Long leftTopStartPointY, Long leftTopEndPointX,
		Long leftTopEndPointY, Long leftMiddleStartPointX, Long leftMiddleStartPointY, Long leftMiddleEndPointX,
		Long leftMiddleEndPointY, Long leftBottomStartPointX,Long leftBottomStartPointY, Long leftBottomEndPointX,
		Long leftBottomEndPointY, Long middleTopStartPointX, Long middleTopStartPointY, Long middleTopEndPointX, 
		Long middleTopEndPointY, Long middleStartPointX, Long middleStartPointY, Long middleEndPointX, Long middleEndPointY,
		Long middleBottomStartPointX, Long middleBottomStartPointY, Long middleBottomEndPointX, Long middleBottomEndPointY,
		Long rightTopStartPointX, Long rightTopStartPointY, Long rightTopEndPointX, Long rightTopEndPointY, Long rightMiddleStartPointX,
		Long rightMiddleStartPointY, Long rightMiddleEndPointX, Long rightMiddleEndPointY, Long rightBottomStartPointX,
		Long rightBottomStartPointY, Long rightBottomEndPointX, Long rightBottomEndPointY ){

			this->fieldStartPointX = fieldStartPointX;
			this->fieldStartPointY = fieldStartPointY;
			this->fieldEndPointX = fieldEndPointX;
			this->fieldEndPointY = fieldEndPointY;

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


void SelectChart::GetFieldPoint( Chart *chart ){
	Long startPointX = chart->GetAt( 0 )->GetStartPointX( );
	Long startPointY = chart->GetAt( 0 )->GetStartPointY( );
	Long endPointX = chart->GetAt( 0 )->GetEndPointX( );
	Long endPointY = chart->GetAt( 0 )->GetEndPointY( );

	for( Long i = 0 ; i < chart->GetLength( ) ; i ++ ){
		if( startPointX > chart->GetAt( i )->GetStartPointX( ) ){
			startPointX = chart->GetAt( i )->GetStartPointX( ) ;
		}
	}
	
	for( Long i = 0 ; i < chart->GetLength( ) ; i ++ ){
		if( startPointY > chart->GetAt( i )->GetStartPointY( ) ){
			startPointY = chart->GetAt( i )->GetStartPointY( ) ;
		}
	}
	
	for( Long i = 0 ; i < chart->GetLength( ) ; i ++ ){
		if( endPointX < chart->GetAt( i )->GetEndPointX( ) ){
			endPointX = chart->GetAt( i )->GetEndPointX( ) ;
		}
	}
	
	for( Long i = 0 ; i < chart->GetLength( ) ; i ++ ){
		if( endPointY < chart->GetAt( i )->GetEndPointY( ) ){
			endPointY = chart->GetAt( i )->GetEndPointY( ) ;
		}
	}

	this->fieldStartPointX = startPointX - 5;
	this->fieldStartPointY = startPointY - 5;
	this->fieldEndPointX = endPointX + 5;
	this->fieldEndPointY = endPointY + 5;
}

void SelectChart::DrawChartField( ) {
	this->leftTopStartPointX = this->fieldStartPointX - 4;
	this->leftTopStartPointY = this->fieldStartPointY - 4;
	this->leftTopEndPointX = this->fieldStartPointX + 4;
	this->leftTopEndPointY = this->fieldStartPointY + 4;

	this->leftMiddleStartPointX = this->fieldStartPointX - 4;
	this->leftMiddleStartPointY = ( ( this->fieldStartPointY + this->fieldEndPointY ) / 2 ) - 4;
	this->leftMiddleEndPointX = this->fieldStartPointX + 4;
	this->leftMiddleEndPointY = ( ( this->fieldStartPointY + this->fieldEndPointY ) / 2 ) + 4;

	this->leftBottomStartPointX = this->fieldStartPointX - 4;
	this->leftBottomStartPointY = this->fieldEndPointY - 4;
	this->leftBottomEndPointX = this->fieldStartPointX + 4;
	this->leftBottomEndPointY = this->fieldEndPointY + 4;

	this->middleTopStartPointX = ( ( this->fieldStartPointX + this->fieldEndPointX ) / 2 ) - 4;
	this->middleTopStartPointY = this->fieldStartPointY - 4;
	this->middleTopEndPointX = ( ( this->fieldStartPointX + this->fieldEndPointX ) / 2 ) + 4;
	this->middleTopEndPointY = this->fieldStartPointY + 4;

	this->middleBottomStartPointX = ( ( this->fieldStartPointX + this->fieldEndPointX ) / 2 ) - 4;
	this->middleBottomStartPointY = this->fieldEndPointY - 4;
	this->middleBottomEndPointX = ( ( this->fieldStartPointX + this->fieldEndPointX ) / 2 ) + 4;
	this->middleBottomEndPointY = this->fieldEndPointY + 4;

	this->rightTopStartPointX = this->fieldEndPointX - 4;
	this->rightTopStartPointY = this->fieldStartPointY - 4;
	this->rightTopEndPointX = this->fieldEndPointX + 4;
	this->rightTopEndPointY = this->fieldStartPointY + 4;

	this->rightMiddleStartPointX = this->fieldEndPointX - 4;
	this->rightMiddleStartPointY = ( this->fieldStartPointY + this->fieldEndPointY ) / 2 - 4;
	this->rightMiddleEndPointX = this->fieldEndPointX + 4;
	this->rightMiddleEndPointY = ( this->fieldStartPointY + this->fieldEndPointY ) / 2 + 4;

	this->rightBottomStartPointX = this->fieldEndPointX - 4;
	this->rightBottomStartPointY = this->fieldEndPointY - 4;
	this->rightBottomEndPointX = this->fieldEndPointX + 4;
	this->rightBottomEndPointY = this->fieldEndPointY + 4;

}

bool SelectChart::CheckChart( Chart *chart, Long pointX, Long pointY ){
	
	Symbol *symbol;

	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;

	bool isSymbolChecked = false;
	
	Long i = 0;
	
	while ( i < chart->GetLength() && isSymbolChecked != true )	{
		symbol = chart->GetAt( i );

		startPointX = symbol->GetStartPointX();
		startPointY = symbol->GetStartPointY();

		endPointX = symbol->GetEndPointX();
		endPointY = symbol->GetEndPointY();
		
		if ( dynamic_cast < Sequence * > ( symbol ) ){
			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < endPointY )	{
					isSymbolChecked = true;
			}
		}
		else if ( dynamic_cast < Arrow * > ( symbol ) ){
			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < endPointY )	{
					isSymbolChecked = true;
			}
		}
		else if ( dynamic_cast < BeforeRepeat * > ( symbol ) )	{
			middlePointX = static_cast < BeforeRepeat * > ( symbol )->GetMiddlePointX();
			middlePointY = static_cast < BeforeRepeat * > ( symbol )->GetMiddlePointY();

			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < middlePointY ||
				pointX > startPointX && pointX < middlePointX && pointY > middlePointY && pointY < endPointY )	{
					isSymbolChecked = true;
			}
		}
		else if ( dynamic_cast < AfterRepeat * > ( symbol ) )	{
			middlePointX = static_cast < AfterRepeat * > ( symbol )->GetMiddlePointX();
			middlePointY = static_cast < AfterRepeat * > ( symbol )->GetMiddlePointY();

			if ( pointX > startPointX && pointX < middlePointX && pointY > startPointY && pointY < endPointY ||
				pointX > middlePointX && pointX < endPointX && pointY > middlePointY && pointY < endPointY )	{
					isSymbolChecked = true;
			}
		}
		else if( dynamic_cast < Selection * > ( symbol ) )	{
			middlePointX = static_cast < Selection * > ( symbol )->GetMiddlePointX( );
			middlePointY = static_cast < Selection * > ( symbol )->GetMiddlePointY( );
			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < endPointY )	{
					isSymbolChecked = true;
			}
		}

		else if( dynamic_cast < SwitchCase * > ( symbol ) ){
			Selection *switchCaseSelection = static_cast<SwitchCase * >( symbol )->GetSelection( ) ;
			middlePointX = switchCaseSelection -> GetMiddlePointX( );
			middlePointY = switchCaseSelection ->GetMiddlePointY( );
			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < middlePointY ||
				pointX > startPointX && pointX < middlePointX && pointY > middlePointY && pointY < endPointY )	{
					
					isSymbolChecked = true;
			}
		}
		i++;
	}
	bool ret;
	if ( isSymbolChecked == true ) {
		ret = true;
	}
	else{
		ret = false;
	}
	return ret;
}

bool SelectChart::CheckChart( Chart *chart , Long startPointX, Long startPointY, Long endPointX, Long endPointY ){
	bool ret = false;
	return ret;

}