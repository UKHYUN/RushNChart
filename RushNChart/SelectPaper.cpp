#include "SelectPaper.h"
#include "SelectedSymbol.h"
#include "Paper.h"
#include "Sequence.h"
#include "BeforeRepeat.h"
#include "AfterRepeat.h"
#include "Selection.h"
#include "SwitchCase.h"
#include "Arrow.h"

#define MAX 100

SelectPaper::SelectPaper( )
	:selectedSymbols( MAX ){
		this->capacity = MAX ;
		this->length = 0;
		this->selectedSymbolIndex = 0;
}

SelectPaper::SelectPaper( const SelectPaper& source )
	:selectedSymbols( source.selectedSymbols ){
		this->capacity = source.capacity;
		this->length = source.length;
		this->selectedSymbolIndex = source.selectedSymbolIndex;
}

SelectPaper::~SelectPaper( ){
}

SelectPaper& SelectPaper::operator= (const SelectPaper& source ){
	this->selectedSymbols = source.selectedSymbols;
	this->capacity = source.capacity;
	this->length = source.length;
	this->selectedSymbolIndex = source.selectedSymbolIndex;

	return *this;
}

Long SelectPaper::CheckSymbol( Paper *paper, Long pointX, Long pointY ){

	Symbol *symbol;

	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;

	bool isSymbolChecked = false;

	Long i = 0;
	Long count = 0 ;

	while ( i < paper->GetLength() && isSymbolChecked != true )	{
		symbol = paper->GetAt( i );

		startPointX = symbol->GetStartPointX();
		startPointY = symbol->GetStartPointY();

		endPointX = symbol->GetEndPointX();
		endPointY = symbol->GetEndPointY();

		if ( dynamic_cast < Arrow * > ( symbol ) ){
			if ( pointX > startPointX-10 && pointX < startPointX+10 && pointY > startPointY && pointY < endPointY )	{
					isSymbolChecked = true;
					count = i;
			}
		}
		i++;
	}
	i = 0;

	while ( i < paper->GetLength() && isSymbolChecked != true )	{
		symbol = paper->GetAt( i );

		startPointX = symbol->GetStartPointX();
		startPointY = symbol->GetStartPointY();

		endPointX = symbol->GetEndPointX();
		endPointY = symbol->GetEndPointY();

		if ( dynamic_cast < Sequence * > ( symbol ) ){
			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < endPointY )	{
					isSymbolChecked = true;
					count = i;
			}
		}
		else if ( dynamic_cast < BeforeRepeat * > ( symbol ) )	{
			middlePointX = static_cast < BeforeRepeat * > ( symbol )->GetMiddlePointX();
			middlePointY = static_cast < BeforeRepeat * > ( symbol )->GetMiddlePointY();

			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < middlePointY ||
				pointX > startPointX && pointX < middlePointX && pointY > middlePointY && pointY < endPointY )	{
					isSymbolChecked = true;
					count = i;
			}
		}
		else if ( dynamic_cast < AfterRepeat * > ( symbol ) )	{
			middlePointX = static_cast < AfterRepeat * > ( symbol )->GetMiddlePointX();
			middlePointY = static_cast < AfterRepeat * > ( symbol )->GetMiddlePointY();

			if ( pointX > startPointX && pointX < middlePointX && pointY > startPointY && pointY < endPointY ||
				pointX > middlePointX && pointX < endPointX && pointY > middlePointY && pointY < endPointY )	{
					isSymbolChecked = true;
					count = i;
			}
		}
		else if( dynamic_cast < Selection * > ( symbol ) )	{
			middlePointX = static_cast < Selection * > ( symbol )->GetMiddlePointX( );
			middlePointY = static_cast < Selection * > ( symbol )->GetMiddlePointY( );
			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < endPointY )	{
					isSymbolChecked = true;
					count = i;
			}
		}
		
		else if( dynamic_cast < SwitchCase * > ( symbol ) ){
			Selection *switchCaseSelection = static_cast<SwitchCase * >( symbol )->GetSelection( ) ;
			middlePointX = switchCaseSelection -> GetMiddlePointX( );
			middlePointY = switchCaseSelection ->GetMiddlePointY( );
			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < middlePointY ||
				pointX > startPointX && pointX < middlePointX && pointY > middlePointY && pointY < endPointY )	{
					
					isSymbolChecked = true;
					count = i;
			}
		}
		i++;
	}
	if ( isSymbolChecked == true ) {
		this->selectedSymbolIndex = count;
	}
	else{
		this->selectedSymbolIndex = -1;
	}

	return this->selectedSymbolIndex;
}

Long SelectPaper::CheckDuplication( Long selectedSymbolIndex ){
	
	SelectedSymbol selectedSymbol;
	bool isSymbolCheck = false;
	Long i = 0;
	Long ret;
	while( i< length && isSymbolCheck != true ){

		selectedSymbol = this->GetAt( i );
		if( selectedSymbol.GetSeletedSymbolIndex( ) == selectedSymbolIndex ){
			isSymbolCheck = true;
		}

		i++;
	}
	//중복이면
	if( isSymbolCheck == true ){
		ret = i - 1;
	}
	//중복이아니면
	else{
		ret = -1;
	}

	return ret;
}

Long SelectPaper::StoreSelectedSymbol( Paper *paper, Long selectedSymbolIndex ){

	Symbol *symbol;
	
	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;

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


	symbol = paper->GetAt( selectedSymbolIndex );

	startPointX = symbol->GetStartPointX();
	startPointY = symbol->GetStartPointY();

	endPointX = symbol->GetEndPointX();
	endPointY = symbol->GetEndPointY();

		
	if ( dynamic_cast < Sequence * > ( symbol ) ){

		middleStartPointX = -1;
		middleStartPointY = -1;
		middleEndPointX = -1;
		middleEndPointY = -1;

	}
	else if ( dynamic_cast < BeforeRepeat * > ( symbol ) )	{
		middlePointX = static_cast < BeforeRepeat * > ( symbol )->GetMiddlePointX();
		middlePointY = static_cast < BeforeRepeat * > ( symbol )->GetMiddlePointY();

		middleStartPointX = middlePointX - 4;
		middleStartPointY = middlePointY - 4;
		middleEndPointX = middlePointX + 4;
		middleEndPointY = middlePointY + 4;
	}
	else if ( dynamic_cast < AfterRepeat * > ( symbol ) )	{
		middlePointX = static_cast < AfterRepeat * > ( symbol )->GetMiddlePointX();
		middlePointY = static_cast < AfterRepeat * > ( symbol )->GetMiddlePointY();

		middleStartPointX = middlePointX - 4;
		middleStartPointY = middlePointY - 4;
		middleEndPointX = middlePointX + 4;
		middleEndPointY = middlePointY + 4;
	}

	else if( dynamic_cast < Selection * > ( symbol ) )	{
		middlePointX = static_cast < Selection * > ( symbol )->GetMiddlePointX( );
		middlePointY = static_cast < Selection * > ( symbol )->GetMiddlePointY( );

		middleStartPointX = middlePointX - 4;
		middleStartPointY = middlePointY - 4;
		middleEndPointX = middlePointX + 4;
		middleEndPointY = middlePointY + 4;
	}
	
			
	else if( dynamic_cast < SwitchCase * > ( symbol ) ){
		Selection *switchCaseSelection = static_cast<SwitchCase * >( symbol )->GetSelection( ) ;
		middlePointX = switchCaseSelection -> GetMiddlePointX( );
		middlePointY = switchCaseSelection ->GetMiddlePointY( );
		
		middleStartPointX = middlePointX - 4;
		middleStartPointY = middlePointY - 4;
		middleEndPointX = middlePointX + 4;
		middleEndPointY = middlePointY + 4;
	}
	//*/
	//왼쪽 위 중간 아래 수정점
	leftTopStartPointX = startPointX - 4;
	leftTopStartPointY = startPointY - 4;
	leftTopEndPointX = startPointX + 4;
	leftTopEndPointY = startPointY + 4;
		
	leftMiddleStartPointX = startPointX - 4;
	leftMiddleStartPointY = ( ( startPointY + endPointY ) / 2 ) - 4;
	leftMiddleEndPointX = startPointX + 4;
	leftMiddleEndPointY = ( ( startPointY + endPointY ) / 2 ) + 4;

	leftBottomStartPointX = startPointX - 4;
	leftBottomStartPointY = endPointY - 4;
	leftBottomEndPointX = startPointX + 4;
	leftBottomEndPointY = endPointY + 4;


	//중간 위 수정점
	middleTopStartPointX = ((( endPointX - startPointX ) / 2 ) + startPointX ) - 4;
	middleTopStartPointY = startPointY - 4;
	middleTopEndPointX = ((( endPointX - startPointX ) / 2 ) + startPointX ) + 4;
	middleTopEndPointY = startPointY + 4;

	if( dynamic_cast < Selection * > ( symbol ) )	{
		middleBottomStartPointX = -1;
		middleBottomStartPointY = -1;
		middleBottomEndPointX = -1;
		middleBottomEndPointY = -1;
	}
	else {
		middleBottomStartPointX = ((( endPointX - startPointX ) / 2 ) + startPointX ) - 4;
		middleBottomStartPointY = symbol->GetEndPointY() - 4;
		middleBottomEndPointX = ((( endPointX - startPointX ) / 2 ) + startPointX )+ 4;
		middleBottomEndPointY = symbol->GetEndPointY() + 4;
	}


	//오른쪽 위 중간 아래 수정점
	rightTopStartPointX = endPointX - 4;
	rightTopStartPointY = startPointY - 4;
	rightTopEndPointX = endPointX + 4;
	rightTopEndPointY = startPointY + 4;

	rightMiddleStartPointX = endPointX - 4;
	rightMiddleStartPointY = ( ( startPointY + endPointY ) / 2 ) - 4;
	rightMiddleEndPointX = endPointX + 4;
	rightMiddleEndPointY = ( ( startPointY + endPointY ) / 2 ) + 4;

	rightBottomStartPointX = endPointX - 4;
	rightBottomStartPointY = endPointY - 4;
	rightBottomEndPointX = endPointX + 4;
	rightBottomEndPointY = endPointY + 4;
	Long index;

	if ( dynamic_cast < Arrow * > ( symbol ) ){
		middleStartPointX = -1;
		middleStartPointY = -1;
		middleEndPointX = -1;
		middleEndPointY = -1;

		leftMiddleStartPointX = -1 ;
		leftMiddleStartPointY = -1 ;
		leftMiddleEndPointX = -1 ;
		leftMiddleEndPointY = -1 ;

		rightMiddleStartPointX = -1 ;
		rightMiddleStartPointY = -1 ;
		rightMiddleEndPointX = -1 ;
		rightMiddleEndPointY = -1 ;
	}

	SelectedSymbol selectedSymbol( selectedSymbolIndex, leftTopStartPointX, leftTopStartPointY, leftTopEndPointX,
		leftTopEndPointY,  leftMiddleStartPointX,  leftMiddleStartPointY,  leftMiddleEndPointX,
		leftMiddleEndPointY,  leftBottomStartPointX, leftBottomStartPointY,  leftBottomEndPointX,
		leftBottomEndPointY,  middleTopStartPointX,  middleTopStartPointY,  middleTopEndPointX, 
		middleTopEndPointY,  middleStartPointX,  middleStartPointY,  middleEndPointX,  middleEndPointY,
		middleBottomStartPointX,  middleBottomStartPointY,  middleBottomEndPointX,  middleBottomEndPointY,
		rightTopStartPointX,  rightTopStartPointY,  rightTopEndPointX,  rightTopEndPointY,  rightMiddleStartPointX,
		rightMiddleStartPointY,  rightMiddleEndPointX,  rightMiddleEndPointY,  rightBottomStartPointX,
		rightBottomStartPointY,  rightBottomEndPointX,  rightBottomEndPointY ); 	
		
	if( this->length < this->capacity ){
		
		index = this->selectedSymbols.Store( length, selectedSymbol );
	
	}
	else{
	
		index = this->selectedSymbols.AppendFromRear( selectedSymbol );
		this->capacity++;
	}
	
	
	this->length++;
	return index;
}	

Long SelectPaper::StoreSelectedSymbol( Paper *paper ) {

	Symbol *symbol;
	
	Long startPointX;
	Long startPointY;
	Long endPointX;
	Long endPointY;
	Long middlePointX;
	Long middlePointY;

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
	
	Long index = -1;

	for ( Long i = 0; i < paper->GetLength(); i ++ ) {
		symbol = paper->GetAt( i );

		startPointX = symbol->GetStartPointX();
		startPointY = symbol->GetStartPointY();

		endPointX = symbol->GetEndPointX();
		endPointY = symbol->GetEndPointY();

		
		if ( dynamic_cast < Sequence * > ( symbol ) ){

			middleStartPointX = -1;
			middleStartPointY = -1;
			middleEndPointX = -1;
			middleEndPointY = -1;

		}
		else if ( dynamic_cast < BeforeRepeat * > ( symbol ) )	{
			middlePointX = static_cast < BeforeRepeat * > ( symbol )->GetMiddlePointX();
			middlePointY = static_cast < BeforeRepeat * > ( symbol )->GetMiddlePointY();

			middleStartPointX = middlePointX - 4;
			middleStartPointY = middlePointY - 4;
			middleEndPointX = middlePointX + 4;
			middleEndPointY = middlePointY + 4;
		}
		else if ( dynamic_cast < AfterRepeat * > ( symbol ) )	{
			middlePointX = static_cast < AfterRepeat * > ( symbol )->GetMiddlePointX();
			middlePointY = static_cast < AfterRepeat * > ( symbol )->GetMiddlePointY();

			middleStartPointX = middlePointX - 4;
			middleStartPointY = middlePointY - 4;
			middleEndPointX = middlePointX + 4;
			middleEndPointY = middlePointY + 4;
		}

		else if( dynamic_cast < Selection * > ( symbol ) )	{
			middlePointX = static_cast < Selection * > ( symbol )->GetMiddlePointX( );
			middlePointY = static_cast < Selection * > ( symbol )->GetMiddlePointY( );

			middleStartPointX = middlePointX - 4;
			middleStartPointY = middlePointY - 4;
			middleEndPointX = middlePointX + 4;
			middleEndPointY = middlePointY + 4;
		}
	
			
		else if( dynamic_cast < SwitchCase * > ( symbol ) ){
			Selection *switchCaseSelection = static_cast<SwitchCase * >( symbol )->GetSelection( ) ;
			middlePointX = switchCaseSelection -> GetMiddlePointX( );
			middlePointY = switchCaseSelection ->GetMiddlePointY( );
		
			middleStartPointX = middlePointX - 4;
			middleStartPointY = middlePointY - 4;
			middleEndPointX = middlePointX + 4;
			middleEndPointY = middlePointY + 4;
		}
		//*/
		//왼쪽 위 중간 아래 수정점
		leftTopStartPointX = startPointX - 4;
		leftTopStartPointY = startPointY - 4;
		leftTopEndPointX = startPointX + 4;
		leftTopEndPointY = startPointY + 4;
		
		leftMiddleStartPointX = startPointX - 4;
		leftMiddleStartPointY = ( ( startPointY + endPointY ) / 2 ) - 4;
		leftMiddleEndPointX = startPointX + 4;
		leftMiddleEndPointY = ( ( startPointY + endPointY ) / 2 ) + 4;

		leftBottomStartPointX = startPointX - 4;
		leftBottomStartPointY = endPointY - 4;
		leftBottomEndPointX = startPointX + 4;
		leftBottomEndPointY = endPointY + 4;


		//중간 위 수정점
		middleTopStartPointX = ((( endPointX - startPointX ) / 2 ) + startPointX ) - 4;
		middleTopStartPointY = startPointY - 4;
		middleTopEndPointX = ((( endPointX - startPointX ) / 2 ) + startPointX ) + 4;
		middleTopEndPointY = startPointY + 4;


		//중간 아래 수정점
		if ( dynamic_cast <Selection *>( symbol ) ){
			middleBottomStartPointX = -1;
			middleBottomStartPointY = -1;
			middleBottomEndPointX = -1;
			middleBottomEndPointY = -1;
		}
		else {
			middleBottomStartPointX = ((( endPointX - startPointX ) / 2 ) + startPointX ) - 4;
			middleBottomStartPointY = symbol->GetEndPointY() - 4;
			middleBottomEndPointX = ((( endPointX - startPointX ) / 2 ) + startPointX )+ 4;
			middleBottomEndPointY = symbol->GetEndPointY() + 4;
		}


		//오른쪽 위 중간 아래 수정점
		rightTopStartPointX = endPointX - 4;
		rightTopStartPointY = startPointY - 4;
		rightTopEndPointX = endPointX + 4;
		rightTopEndPointY = startPointY + 4;

		rightMiddleStartPointX = endPointX - 4;
		rightMiddleStartPointY = ( ( startPointY + endPointY ) / 2 ) - 4;
		rightMiddleEndPointX = endPointX + 4;
		rightMiddleEndPointY = ( ( startPointY + endPointY ) / 2 ) + 4;

		rightBottomStartPointX = endPointX - 4;
		rightBottomStartPointY = endPointY - 4;
		rightBottomEndPointX = endPointX + 4;
		rightBottomEndPointY = endPointY + 4;

		if ( dynamic_cast < Arrow * > ( symbol ) ){
			middleStartPointX = -1;
			middleStartPointY = -1;
			middleEndPointX = -1;
			middleEndPointY = -1;

			leftMiddleStartPointX = -1 ;
			leftMiddleStartPointY = -1 ;
			leftMiddleEndPointX = -1 ;
			leftMiddleEndPointY = -1 ;

			rightMiddleStartPointX = -1 ;
			rightMiddleStartPointY = -1 ;
			rightMiddleEndPointX = -1 ;
			rightMiddleEndPointY = -1 ;
		}

		SelectedSymbol selectedSymbol( i, leftTopStartPointX, leftTopStartPointY, leftTopEndPointX,
				leftTopEndPointY,  leftMiddleStartPointX,  leftMiddleStartPointY,  leftMiddleEndPointX,
				leftMiddleEndPointY,  leftBottomStartPointX, leftBottomStartPointY,  leftBottomEndPointX,
				leftBottomEndPointY,  middleTopStartPointX,  middleTopStartPointY,  middleTopEndPointX, 
				middleTopEndPointY,  middleStartPointX,  middleStartPointY,  middleEndPointX,  middleEndPointY,
				middleBottomStartPointX,  middleBottomStartPointY,  middleBottomEndPointX,  middleBottomEndPointY,
				rightTopStartPointX,  rightTopStartPointY,  rightTopEndPointX,  rightTopEndPointY,  rightMiddleStartPointX,
				rightMiddleStartPointY,  rightMiddleEndPointX,  rightMiddleEndPointY,  rightBottomStartPointX,
				rightBottomStartPointY,  rightBottomEndPointX,  rightBottomEndPointY ); 	

		if( this->length < this->capacity ){
		
			index = this->selectedSymbols.Store( length, selectedSymbol );
	
		}
		else{
	
			index = this->selectedSymbols.AppendFromRear( selectedSymbol );
			this->capacity++;
		}
	
		this->length++;
	}
	return index;
}


Long SelectPaper::Release( Long selectedSymbolIndex ){

	Long ret = this->selectedSymbols.Delete( selectedSymbolIndex ) ; 

	this->length--;
	this->capacity --;

	return ret;
}

void SelectPaper::ReleaseAllSymbols( )	{
	
	if( this->length > 0 )	{
		this->selectedSymbols.Clear();

		this->length = 0;
		this->capacity = 0;
	}
}

Long	SelectPaper::CheckSymbols( Paper *paper, Long sPointX, Long sPointY, Long ePointX, 
							Long ePointY ) {
//	Symbol *symbol;
	
	Long	startPointX;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;
	Long	middlePointX;
	Long	middlePointY;
//	Long	symbolIndex;

	//왼쪽 위
	Long	leftTopStartPointX;
	Long	leftTopStartPointY;
	Long	leftTopEndPointX;
	Long	leftTopEndPointY;

	//중간 위 점
	Long	middleTopStartPointX;
	Long	middleTopStartPointY;
	Long	middleTopEndPointX;
	Long	middleTopEndPointY;
	
	//오른쪽 위 점
	Long	rightTopStartPointX;
	Long	rightTopStartPointY;
	Long	rightTopEndPointX;
	Long	rightTopEndPointY;

	//오른쪽 중간 점
	Long	rightMiddleStartPointX;
	Long	rightMiddleStartPointY;
	Long	rightMiddleEndPointX;
	Long	rightMiddleEndPointY;

	//오른쪽 아래 점
	Long	rightBottomStartPointX;
	Long	rightBottomStartPointY;
	Long	rightBottomEndPointX;
	Long	rightBottomEndPointY;

	//중간 아래 점
	Long	middleBottomStartPointX;
	Long	middleBottomStartPointY;
	Long	middleBottomEndPointX;
	Long	middleBottomEndPointY;

	//왼쪽 아래 점
 	Long	leftBottomStartPointX;
	Long	leftBottomStartPointY;
	Long	leftBottomEndPointX;
	Long	leftBottomEndPointY;
		
	//왼쪽 중간 점
	Long	leftMiddleStartPointX;
	Long	leftMiddleStartPointY;
	Long	leftMiddleEndPointX;
	Long	leftMiddleEndPointY;

	//중간 점// 셀렉션 중간 점
	Long	middleStartPointX;
	Long	middleStartPointY;
	Long	middleEndPointX;
	Long	middleEndPointY;
	Long	index = - 1;
	Long	i = 0;

	if ( this->length != 0 ) {
		this->selectedSymbols.Clear();
		this->length = 0;
		this->capacity = 0;
	}
	while ( i < paper->GetLength() ) {
		startPointX = paper->GetAt( i )->GetStartPointX();
		startPointY = paper->GetAt( i )->GetStartPointY();
		endPointX = paper->GetAt( i )->GetEndPointX();
		endPointY = paper->GetAt( i )->GetEndPointY();

		if ( sPointX < startPointX && ePointX > endPointX && sPointY < startPointY && ePointY > endPointY ) {
			leftTopStartPointX = startPointX - 4;
			leftTopStartPointY = startPointY - 4;
			leftTopEndPointX = startPointX + 4;
			leftTopEndPointY = startPointY + 4;

			middleTopStartPointX = ( ( startPointX + endPointX ) / 2 ) - 4;
			middleTopStartPointY = startPointY - 4;
			middleTopEndPointX = ( ( startPointX + endPointX ) / 2 ) + 4;
			middleTopEndPointY = startPointY + 4;

			rightTopStartPointX = endPointX - 4;
			rightTopStartPointY = startPointY - 4;
			rightTopEndPointX = endPointX + 4;
			rightTopEndPointY = startPointY + 4;

			rightMiddleStartPointX = endPointX - 4;
			rightMiddleStartPointY = ( ( startPointY + endPointY ) / 2 ) - 4;
			rightMiddleEndPointX = endPointX + 4;
			rightMiddleEndPointY = ( ( startPointY + endPointY ) / 2 ) + 4;

			rightBottomStartPointX = endPointX - 4;
			rightBottomStartPointY = endPointY - 4;
			rightBottomEndPointX = endPointX + 4;
			rightBottomEndPointY = endPointY + 4;

			if ( dynamic_cast < Selection * >( paper->GetAt( i ) ) ) {
				middleBottomStartPointX = -1;
				middleBottomStartPointY = -1;
				middleBottomEndPointX = -1;
				middleBottomEndPointY = -1;
				
				middlePointX = static_cast < Selection * >( paper->GetAt( i ) )->GetMiddlePointX();
				middlePointY = static_cast < Selection * >( paper->GetAt( i ) )->GetMiddlePointY();
				middleStartPointX = middlePointX - 4;
				middleStartPointY = middlePointY - 4;
				middleEndPointX =  middlePointX + 4;
				middleEndPointY = middlePointY + 4;
			}
			else {
				middleBottomStartPointX = ( ( startPointX + endPointX ) / 2 ) - 4;
				middleBottomStartPointY = endPointY - 4;
				middleBottomEndPointX =  ( ( startPointX + endPointX ) / 2 ) + 4;
				middleBottomEndPointY = endPointY + 4;
			}

			leftBottomStartPointX = startPointX - 4;
			leftBottomStartPointY = endPointY - 4;;
			leftBottomEndPointX = startPointX + 4;
			leftBottomEndPointY = endPointY + 4;

			leftMiddleStartPointX = startPointX - 4;
			leftMiddleStartPointY = ( ( startPointY + endPointY ) / 2 ) - 4;
			leftMiddleEndPointX = startPointX + 4;
			leftMiddleEndPointY = ( ( startPointY + endPointY ) / 2 ) + 4;

			if ( dynamic_cast <Sequence *>( paper->GetAt( i ) ) ) {
				middleStartPointX =  - 1;
				middleStartPointY = - 1;
				middleEndPointX =  - 1;
				middleEndPointY = - 1;
			}
			else if ( dynamic_cast <Arrow *>( paper->GetAt( i ) ) ) {
				middleStartPointX =  - 1;
				middleStartPointY = - 1;
				middleEndPointX =  - 1;
				middleEndPointY = - 1;

				leftMiddleStartPointX = -1 ;
				leftMiddleStartPointY = -1 ;
				leftMiddleEndPointX = -1 ;
				leftMiddleEndPointY = -1 ;

				rightMiddleStartPointX = -1 ;
				rightMiddleStartPointY = -1 ;
				rightMiddleEndPointX = -1 ;
				rightMiddleEndPointY = -1 ;

			}

			else if ( dynamic_cast <BeforeRepeat *>( paper->GetAt( i ) ) ){ 
				middlePointX = static_cast < BeforeRepeat * >( paper->GetAt( i ) )->GetMiddlePointX();
				middlePointY = static_cast < BeforeRepeat * >( paper->GetAt( i ) )->GetMiddlePointY();
				middleStartPointX = middlePointX - 4;
				middleStartPointY = middlePointY - 4;
				middleEndPointX =  middlePointX + 4;
				middleEndPointY = middlePointY + 4;
			}
			else if ( dynamic_cast <AfterRepeat *>( paper->GetAt( i ) ) ) {
				middlePointX = static_cast < AfterRepeat * >( paper->GetAt( i ) )->GetMiddlePointX();
				middlePointY = static_cast < AfterRepeat * >( paper->GetAt( i ) )->GetMiddlePointY();
				middleStartPointX = middlePointX - 4;
				middleStartPointY = middlePointY - 4;
				middleEndPointX =  middlePointX + 4;
				middleEndPointY = middlePointY + 4;
			}
			
			else if( dynamic_cast < SwitchCase * > ( paper->GetAt( i ) ) ){

			Selection *switchCaseSelection = static_cast<SwitchCase * >(  paper->GetAt( i )  )->GetSelection( ) ;
			middlePointX = switchCaseSelection -> GetMiddlePointX( );
			middlePointY = switchCaseSelection ->GetMiddlePointY( );

			middleStartPointX = middlePointX - 4;
			middleStartPointY = middlePointY - 4;
			middleEndPointX =  middlePointX + 4;
			middleEndPointY = middlePointY + 4;
			}
			//*/
			SelectedSymbol select( i, leftTopStartPointX, leftTopStartPointY, leftTopEndPointX,
			 leftTopEndPointY,  leftMiddleStartPointX,  leftMiddleStartPointY,  leftMiddleEndPointX,
			 leftMiddleEndPointY,  leftBottomStartPointX, leftBottomStartPointY,  leftBottomEndPointX,
			 leftBottomEndPointY,  middleTopStartPointX,  middleTopStartPointY,  middleTopEndPointX, 
			 middleTopEndPointY,  middleStartPointX,  middleStartPointY,  middleEndPointX,  middleEndPointY,
			 middleBottomStartPointX,  middleBottomStartPointY,  middleBottomEndPointX,  middleBottomEndPointY,
			 rightTopStartPointX,  rightTopStartPointY,  rightTopEndPointX,  rightTopEndPointY,  rightMiddleStartPointX,
			 rightMiddleStartPointY,  rightMiddleEndPointX,  rightMiddleEndPointY,  rightBottomStartPointX,
			 rightBottomStartPointY,  rightBottomEndPointX,  rightBottomEndPointY ); 
			
			if ( this->length < this->capacity ) {
				index = this->selectedSymbols.Store( this->length, select );
			}
			else {
				index = this->selectedSymbols.AppendFromRear ( select );
				this->capacity++;
			}
			this->length++;
		}
		i++;
	}
	return index;
}


/*
	함수이름 : TransNumber
	설    명 : 변경될 위치를 구한다.
	입    력 : paper, pointX, pointY
	출    력 : index
	만 든 이 : 채형석
*/
Long	SelectPaper::TransNumber( Paper *paper, Long pointX, Long pointY ){
	Long	number = 0;
	Long	i = 0;
	Symbol	*symbol;
	while ( i < this->GetLength() && number == 0 ) {
		symbol = paper->GetAt(this->GetAt(i).GetSeletedSymbolIndex());

		if ( this->GetAt(i).GetLeftTopStartPointX() <= pointX && this->GetAt(i).GetLeftTopEndPointX() >= pointX &&
			 this->GetAt(i).GetLeftTopStartPointY() <= pointY && this->GetAt(i).GetLeftTopEndPointY() >= pointY ) {
				number = 1;
				this->selectedSymbolIndex = i;
		}
		else if ( this->GetAt(i).GetMiddleTopStartPointX() <= pointX && this->GetAt(i).GetMiddleTopEndPointX() >= pointX &&
				  this->GetAt(i).GetMiddleTopStartPointY() <= pointY && this->GetAt(i).GetMiddleTopEndPointY() >= pointY ) {
				number = 2;
				this->selectedSymbolIndex = i;
		}
		else if ( this->GetAt(i).GetRightTopStartPointX() <= pointX && this->GetAt(i).GetRightTopEndPointX()  >= pointX &&
				  this->GetAt(i).GetRightTopStartPointY() <= pointY && this->GetAt(i).GetRightTopEndPointY()  >= pointY ) {
				number = 3;
				this->selectedSymbolIndex = i;
		} 
		else if ( this->GetAt(i).GetRightMiddleStartPointX() <= pointX && this->GetAt(i).GetRightMiddleEndPointX() >= pointX &&
				  this->GetAt(i).GetRightMiddleStartPointY() <= pointY && this->GetAt(i).GetRightMiddleEndPointY() >= pointY ) {
				number = 4;
				this->selectedSymbolIndex = i;
		}
		else if ( this->GetAt(i).GetRightBottomStartPointX() <= pointX && this->GetAt(i).GetRightBottomEndPointX() >= pointX &&
				  this->GetAt(i).GetRightBottomStartPointY() <= pointY && this->GetAt(i).GetRightBottomEndPointY() >= pointY ) {
				number = 5;
				this->selectedSymbolIndex = i;
		}
		
		else if ( this->GetAt(i).GetLeftBottomStartPointX() <= pointX && this->GetAt(i).GetLeftBottomEndPointX() >= pointX &&
				  this->GetAt(i).GetLeftBottomStartPointY() <= pointY && this->GetAt(i).GetLeftBottomEndPointY() >= pointY ) {
				number = 7;
				this->selectedSymbolIndex = i;
		}
		else if ( this->GetAt(i).GetLeftMiddleStartPointX() <= pointX && this->GetAt(i).GetLeftMiddleEndPointX() >= pointX &&
				  this->GetAt(i).GetLeftMiddleStartPointY() <= pointY && this->GetAt(i).GetLeftMiddleEndPointY() >= pointY ) {
				number = 8;
				this->selectedSymbolIndex = i;
		}
		else if ( dynamic_cast < Selection * > ( symbol )  &&
				  this->GetAt(i).GetMiddleStartPointX() <= pointX && this->GetAt(i).GetMiddleEndPointX() >= pointX &&
				  this->GetAt(i).GetMiddleStartPointY() <= pointY && this->GetAt(i).GetMiddleEndPointY() >= pointY ) {
				number = 6;
				this->selectedSymbolIndex = i;	
		}
		else {
			if ( this->GetAt(i).GetMiddleBottomStartPointX() <= pointX && this->GetAt(i).GetMiddleBottomEndPointX() >= pointX &&
				  this->GetAt(i).GetMiddleBottomStartPointY() <= pointY && this->GetAt(i).GetMiddleBottomEndPointY() >= pointY ) {
				number = 6;
				this->selectedSymbolIndex = i;
			}
		}
		
		i++;
	}

	return	number;
}

/*
	함수이름 : ReNewSelected
	설    명 : 변경될 위치를 구한다.
	입    력 : paper, pointX, pointY
	출    력 : index
	만 든 이 : 채형석
*/
Long	SelectPaper::ReNewSelected( Paper *paper ){

	//왼쪽 위
	Long	leftTopStartPointX;
	Long	leftTopStartPointY;
	Long	leftTopEndPointX;
	Long	leftTopEndPointY;

	//중간 위 점
	Long	middleTopStartPointX;
	Long	middleTopStartPointY;
	Long	middleTopEndPointX;
	Long	middleTopEndPointY;
	
	//오른쪽 위 점
	Long	rightTopStartPointX;
	Long	rightTopStartPointY;
	Long	rightTopEndPointX;
	Long	rightTopEndPointY;

	//오른쪽 중간 점
	Long	rightMiddleStartPointX;
	Long	rightMiddleStartPointY;
	Long	rightMiddleEndPointX;
	Long	rightMiddleEndPointY;

	//오른쪽 아래 점
	Long	rightBottomStartPointX;
	Long	rightBottomStartPointY;
	Long	rightBottomEndPointX;
	Long	rightBottomEndPointY;

	//중간 아래 점
	Long	middleBottomStartPointX;
	Long	middleBottomStartPointY;
	Long	middleBottomEndPointX;
	Long	middleBottomEndPointY;

	//왼쪽 아래 점
 	Long	leftBottomStartPointX;
	Long	leftBottomStartPointY;
	Long	leftBottomEndPointX;
	Long	leftBottomEndPointY;
		
	//왼쪽 중간 점
	Long	leftMiddleStartPointX;
	Long	leftMiddleStartPointY;
	Long	leftMiddleEndPointX;
	Long	leftMiddleEndPointY;

	//중간 점// 셀렉션 중간 점
	Long	middleStartPointX;
	Long	middleStartPointY;
	Long	middleEndPointX;
	Long	middleEndPointY;

	Long	startPointX;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;
	Long	middlePointX;
	Long	middlePointY;
	Long	i = 0; 

	while ( i < this->GetLength() ) {
		Long	index = this->GetAt( i ).GetSeletedSymbolIndex();

		startPointX = paper->GetAt( index )->GetStartPointX();
		startPointY = paper->GetAt( index )->GetStartPointY();
		endPointX = paper->GetAt( index )->GetEndPointX();
		endPointY = paper->GetAt( index )->GetEndPointY();

		leftTopStartPointX = startPointX - 4;
		leftTopStartPointY = startPointY - 4;
		leftTopEndPointX = startPointX + 4;
		leftTopEndPointY = startPointY + 4;

		middleTopStartPointX = ( ( startPointX + endPointX ) / 2 ) - 4;
		middleTopStartPointY = startPointY - 4;
		middleTopEndPointX = ( ( startPointX + endPointX ) / 2 ) + 4;
		middleTopEndPointY = startPointY + 4;

		rightTopStartPointX = endPointX - 4;
		rightTopStartPointY = startPointY - 4;
		rightTopEndPointX = endPointX + 4;
		rightTopEndPointY = startPointY + 4;

		rightMiddleStartPointX = endPointX - 4;
		rightMiddleStartPointY = ( ( startPointY + endPointY ) / 2 ) - 4;
		rightMiddleEndPointX = endPointX + 4;
		rightMiddleEndPointY = ( ( startPointY + endPointY ) / 2 ) + 4;

		rightBottomStartPointX = endPointX - 4;
		rightBottomStartPointY = endPointY - 4;
		rightBottomEndPointX = endPointX + 4;
		rightBottomEndPointY = endPointY + 4;

		if ( dynamic_cast < Selection * >( paper->GetAt( index ) ) ) {
			middleBottomStartPointX = -1;
			middleBottomStartPointY = -1;
			middleBottomEndPointX = -1;
			middleBottomEndPointY = -1;
				
			middlePointX = static_cast < Selection * >( paper->GetAt( index ) )->GetMiddlePointX();
			middlePointY = static_cast < Selection * >( paper->GetAt( index ) )->GetMiddlePointY();
			middleStartPointX = middlePointX - 4;
			middleStartPointY = middlePointY - 4;
			middleEndPointX =  middlePointX + 4;
			middleEndPointY = middlePointY + 4;
		}
		else {
			middleBottomStartPointX = ( ( startPointX + endPointX ) / 2 ) - 4;
			middleBottomStartPointY = endPointY - 4;
			middleBottomEndPointX =  ( ( startPointX + endPointX ) / 2 ) + 4;
			middleBottomEndPointY = endPointY + 4;
		}

		leftBottomStartPointX = startPointX - 4;
		leftBottomStartPointY = endPointY - 4;;
		leftBottomEndPointX = startPointX + 4;
		leftBottomEndPointY = endPointY + 4;

		leftMiddleStartPointX = startPointX - 4;
		leftMiddleStartPointY = ( ( startPointY + endPointY ) / 2 ) - 4;
		leftMiddleEndPointX = startPointX + 4;
		leftMiddleEndPointY = ( ( startPointY + endPointY ) / 2 ) + 4;

		if ( dynamic_cast <Sequence *>( paper->GetAt( index ) ) ) {
			middleStartPointX =  - 1;
			middleStartPointY = - 1;
			middleEndPointX =  - 1;
			middleEndPointY = - 1;
		}
		else if ( dynamic_cast <Arrow *>( paper->GetAt( index ) ) ) {
			middleStartPointX =  - 1;
			middleStartPointY = - 1;
			middleEndPointX =  - 1;
			middleEndPointY = - 1;

			leftMiddleStartPointX = -1 ;
			leftMiddleStartPointY = -1 ;
			leftMiddleEndPointX = -1 ;
			leftMiddleEndPointY = -1 ;

			rightMiddleStartPointX = -1 ;
			rightMiddleStartPointY = -1 ;
			rightMiddleEndPointX = -1 ;
			rightMiddleEndPointY = -1 ;

		}
		else if ( dynamic_cast <BeforeRepeat *>( paper->GetAt( index ) ) ){ 
			middlePointX = static_cast < BeforeRepeat * >( paper->GetAt( index ) )->GetMiddlePointX();
			middlePointY = static_cast < BeforeRepeat * >( paper->GetAt( index ) )->GetMiddlePointY();
			middleStartPointX = middlePointX - 4;
			middleStartPointY = middlePointY - 4;
			middleEndPointX =  middlePointX + 4;
			middleEndPointY = middlePointY + 4;
		}
		else if ( dynamic_cast <AfterRepeat *>( paper->GetAt( index ) ) ) {
			middlePointX = static_cast < AfterRepeat * >( paper->GetAt( index ) )->GetMiddlePointX();
			middlePointY = static_cast < AfterRepeat * >( paper->GetAt( index ) )->GetMiddlePointY();
			middleStartPointX = middlePointX - 4;
			middleStartPointY = middlePointY - 4;
			middleEndPointX =  middlePointX + 4;
			middleEndPointY = middlePointY + 4;
		}
		else if( dynamic_cast < SwitchCase * > ( paper->GetAt( index ) ) ) {

			Selection *switchCaseSelection = static_cast<SwitchCase * >(  paper->GetAt( index )  )->GetSelection( ) ;
			middlePointX = switchCaseSelection -> GetMiddlePointX( );
			middlePointY = switchCaseSelection ->GetMiddlePointY( );

			middleStartPointX = middlePointX - 4;
			middleStartPointY = middlePointY - 4;
			middleEndPointX =  middlePointX + 4;
			middleEndPointY = middlePointY + 4;
		}
		
		SelectedSymbol select( index, leftTopStartPointX, leftTopStartPointY, leftTopEndPointX, leftTopEndPointY,  
			 leftMiddleStartPointX,  leftMiddleStartPointY,  leftMiddleEndPointX, leftMiddleEndPointY,  
			 leftBottomStartPointX, leftBottomStartPointY,  leftBottomEndPointX, leftBottomEndPointY,  
			 middleTopStartPointX,  middleTopStartPointY,  middleTopEndPointX, middleTopEndPointY,  
			 middleStartPointX,  middleStartPointY,  middleEndPointX,  middleEndPointY, 
			 middleBottomStartPointX,  middleBottomStartPointY,  middleBottomEndPointX,  middleBottomEndPointY,
			 rightTopStartPointX,  rightTopStartPointY,  rightTopEndPointX,  rightTopEndPointY,  
			 rightMiddleStartPointX, rightMiddleStartPointY,  rightMiddleEndPointX,  rightMiddleEndPointY,  
			 rightBottomStartPointX, rightBottomStartPointY,  rightBottomEndPointX,  rightBottomEndPointY ); 

		index = this->selectedSymbols.Modify( i, select );

		i++;
	}

	return this->GetLength();
}


Long	SelectPaper::StringCheck( Paper *paper, Long pointX, Long pointY ) {
	Symbol	*symbol;

	Long	startPointX;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;
	//Long	middlePointX;
	//Long	middlePointY;

	bool	isSymbolChecked = false;
	Long	count;
	Long	index = 0;

	index = this->GetAt(0).GetSeletedSymbolIndex();
	symbol = paper->GetAt( index );
	Long	columnCount = static_cast < SwitchCase * >( symbol )->GetColumnCount();

	Long i = 0;

	while ( i < columnCount + 1 && isSymbolChecked != true ) {

		if ( i == 0 ) {
			Symbol	*tempSymbol = static_cast < SwitchCase *>(symbol)->GetSelection();

			if ( dynamic_cast < Selection * >( tempSymbol ) ) {
				startPointX = static_cast < Selection *>(tempSymbol)->GetStartPointX();
				startPointY = static_cast < Selection *>(tempSymbol)->GetStartPointY();

				endPointX = static_cast < Selection *>(tempSymbol)->GetEndPointX();
				endPointY = static_cast < Selection *>(tempSymbol)->GetEndPointY();

				if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < endPointY )	{
					isSymbolChecked = true;
					count = 0;
				}
			}
			if ( isSymbolChecked != true ) {
				startPointX = static_cast < SwitchCase *>(symbol)->GetCases( i )->GetStartPointX();
				startPointY = static_cast < SwitchCase *>(symbol)->GetCases( i )->GetStartPointY();

				endPointX = static_cast < SwitchCase *>(symbol)->GetCases( i )->GetEndPointX();
				endPointY = static_cast < SwitchCase *>(symbol)->GetCases( i )->GetEndPointY();

				if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < endPointY )	{
					isSymbolChecked = true;
					count = i + 1;
				}
			}

		}
		else {
			startPointX = static_cast < SwitchCase *>(symbol)->GetCases( i )->GetStartPointX();
			startPointY = static_cast < SwitchCase *>(symbol)->GetCases( i )->GetStartPointY();

			endPointX = static_cast < SwitchCase *>(symbol)->GetCases( i )->GetEndPointX();
			endPointY = static_cast < SwitchCase *>(symbol)->GetCases( i )->GetEndPointY();

			if ( pointX > startPointX && pointX < endPointX && pointY > startPointY && pointY < endPointY )	{
				isSymbolChecked = true;
				count = i + 1;
			}
		}
		i++;
	}

	return count;
}