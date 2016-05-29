#include "Chart.h"
#include "Paper.h"
#include "Symbol.h"

#include "AfterRepeat.h"
#include "BeforeRepeat.h"
#include "SwitchCase.h"
#include "Selection.h"
#include "Sequence.h"
#include "Arrow.h"

#include "Select.h"
#include "SelectChart.h"
#include "SelectedSymbol.h"

#define MAX 100


Chart::Chart ( )
	: symbols ( MAX ) {
		this->capacity = MAX ;
		this->length = 0 ;
}

Chart::Chart ( Long Capacity )
	: symbols ( capacity ) {
		this->capacity = capacity ;
		this->length = 0 ;
}

Chart::~Chart ( ) {
	for( Long i = 0; i < this->length; i++ )	{
		Symbol *symbol = this->symbols.GetAt( i );
		delete symbol;
	}
}


Chart::Chart ( const Chart& source ) 
	: symbols ( source.capacity ) {
		Symbol	*symbol ;

		for( Long i = 0; i < source.length; i++)	{
			symbol = source.symbols.GetAt(i);

			if( dynamic_cast< Sequence* >(symbol) )	{
				symbol = new Sequence( *(Sequence*) symbol );
			}
			else  if( dynamic_cast< BeforeRepeat* > (symbol) )	{
				symbol = new BeforeRepeat( *(BeforeRepeat*) symbol );
			}
			else if( dynamic_cast< AfterRepeat* > (symbol) )	{
				symbol = new AfterRepeat( *(AfterRepeat*) symbol );
			}
			else if( dynamic_cast< Selection* > (symbol) )	{
				symbol = new Selection( *(Selection*) symbol );
			}
			else if( dynamic_cast< SwitchCase * > (symbol) )	{
				symbol = new SwitchCase( *( SwitchCase *) symbol );
			}
			else if( dynamic_cast< Arrow* >(symbol) )	{
				symbol = new Arrow( *(Arrow*) symbol );
			}
			//*/
			this->symbols.Store( i, symbol );
		}

		this->capacity = source.capacity;
		this->length = source.length;
}

Chart&	Chart::operator= ( const Chart& source ) {
	for ( Long i = 0 ; i < length ; i ++ ) {
		Symbol *deleteSymbol = this->GetAt( i ) ;
		if( deleteSymbol != 0 ){
			delete deleteSymbol ;
			this->symbols.Modify( i , 0 );
		}
	}
	Symbol	*symbol ;
	for( Long i = 0; i < source.length; i++)	{
		symbol = source.symbols.GetAt(i);

		if( dynamic_cast< Sequence * >(symbol) )	{
			symbol = new Sequence( *( Sequence * ) symbol );
		}
		else  if( dynamic_cast< BeforeRepeat * > (symbol) )	{
			symbol = new BeforeRepeat( *( BeforeRepeat * ) symbol );
		}
		else if( dynamic_cast< AfterRepeat * > (symbol) )	{
			symbol = new AfterRepeat( *( AfterRepeat * ) symbol );
		}
		else if( dynamic_cast< Selection * > (symbol) )	{
			symbol = new Selection( *( Selection * ) symbol );
		}
		else if( dynamic_cast< SwitchCase * > (symbol) )	{
			symbol = new SwitchCase( *( SwitchCase * ) symbol );
		}
		else if( dynamic_cast< Arrow* >(symbol) )	{
			symbol = new Arrow( *(Arrow*) symbol );
		}
		//*/
		this->symbols.Store( i, symbol );
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return	*this ;
}

Long Chart::Paste ( Symbol	*symbol ) {
	Long index ;

	if( this->length < this->capacity ) {
		index = this->symbols.Store( this->length, symbol ) ;
	}
	else{
		index = this->symbols.AppendFromRear( symbol ) ;
		(this->capacity)++ ;
	}
	(this->length)++ ;

	return index ;
}

Long Chart::MoveSymbol( Long index, Symbol *movedSymbol ){
	Long ret = this->symbols.Modify( index, movedSymbol );
	
	return ret;
}

Long Chart:: Detach( Long symbolIndex ){
	Long index = this->symbols.Delete( symbolIndex );
	this->length--;
	this->capacity--;

	return index;
}

void Chart::DeleteAllSymbols( ){

	for( Long i = 0 ; i < this->length ; i ++ ){
		this->symbols.DeleteModify( i );
	}


	//this->symbols.Clear( );
	this->length = 0;
	this->capacity = MAX;
}
/*
Long	Chart::TransForm ( Select * select, Long number, Long pointX, Long pointY ) {
	Long	startPointX ;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;
	
	wstring	expression;

	Long	middlePointX;
	Long	middlePointY;
	Long	index;
	Long	i = 0;
	Long	transPointX;	// 변경 X 값
	Long	transPointY;	// 변경 Y 값
	Long	transMiddleY;	// 변경 중간 Y 값
	Long	columnCount;
	bool	isIntegerX;		// X 의 값이 + 인지 - 인지 확인하는 값
	bool	isIntegerY;		// Y 의 값이 + 인지 - 인지 확인하는 값
//	bool	isMiddle;		// 선택 구조의 중간 값이 변경되는지 확인하는 값

	index = select->GetSelectChart()->GetSelectedSymbolIndex();
	index = select->GetSelectChart()->GetAt(index).GetSeletedSymbolIndex();
	middlePointX = static_cast <Selection *>(this->GetAt(index))->GetMiddlePointX();
	middlePointY = static_cast <Selection *>(this->GetAt(index))->GetMiddlePointY();
	
	// 변경 될 구조의 좌표가 얼마나 변경되는지 확인하는 case 구문 9개의 위치중 변경되는 값이 + 인지 - 인지 확인함
	switch ( number ) 
	{
		case 1 : if ( this->GetAt(index)->GetStartPointX() > pointX ) {
					 transPointX = this->GetAt(index)->GetStartPointX() - pointX;
					 isIntegerX = false;
				}
				 if ( this->GetAt(index)->GetStartPointX() < pointX ) {
					transPointX = pointX - this->GetAt(index)->GetStartPointX();
					isIntegerX = true;
				}
				if ( this->GetAt(index)->GetStartPointY() > pointY ) {
					transPointY = this->GetAt(index)->GetStartPointY() - pointY;
					isIntegerY = false;
				}
				if ( this->GetAt(index)->GetStartPointY() < pointY ) {
					transPointY = pointY - this->GetAt(index)->GetStartPointY();
					isIntegerY = true;
				}
				break;

		case 2 : if ( this->GetAt(index)->GetStartPointY() > pointY ) {
					transPointY = this->GetAt(index)->GetStartPointY() - pointY;
					isIntegerY = false;
				}
				if ( this->GetAt(index)->GetStartPointY() < pointY ) {
					transPointY = pointY - this->GetAt(index)->GetStartPointY();
					isIntegerY = true;
				}
				break;

		case 3 : if ( this->GetAt(index)->GetStartPointY() > pointY ) {
					transPointY = this->GetAt(index)->GetStartPointY() - pointY;
					isIntegerY = false;
				}
				if ( this->GetAt(index)->GetStartPointY() < pointY ) {
					transPointY = pointY - this->GetAt(index)->GetStartPointY();
					isIntegerY = true;
				}
				if ( this->GetAt(index)->GetEndPointX() > pointX ) {
					transPointX = this->GetAt(index)->GetEndPointX() - pointX;
					isIntegerX = false;
				}
				if ( this->GetAt(index)->GetEndPointX() < pointX ) {
					transPointX = pointX - this->GetAt(index)->GetEndPointX() ;
					isIntegerX = true;
				}
				break;

		case 4 : if ( this->GetAt(index)->GetEndPointX() > pointX ) {
					transPointX = this->GetAt(index)->GetEndPointX() - pointX;
					isIntegerX = false;
				}
				if ( this->GetAt(index)->GetEndPointX() < pointX ) {
					transPointX = pointX - this->GetAt(index)->GetEndPointX() ;
					isIntegerX = true;
				}
				break;
					 
		case 5 : if ( this->GetAt(index)->GetEndPointX() > pointX ) {
					transPointX = this->GetAt(index)->GetEndPointX() - pointX;
					isIntegerX = false;
				}
				if ( this->GetAt(index)->GetEndPointX() < pointX ) {
					transPointX = pointX - this->GetAt(index)->GetEndPointX() ;
					isIntegerX = true;
				}
				if ( this->GetAt(index)->GetEndPointY() > pointY ) {
					transPointY = this->GetAt(index)->GetEndPointY() - pointY;
					isIntegerY = false;
				}
				if ( this->GetAt(index)->GetEndPointY() < pointY ) {
					transPointY = pointY - this->GetAt(index)->GetEndPointY();
					isIntegerY = true;
				}
				break;

		case 6 : if ( this->GetAt(index)->GetEndPointY() > pointY ) {
					transPointY = this->GetAt(index)->GetEndPointY() - pointY;
					isIntegerY = false;
				}
				if ( this->GetAt(index)->GetEndPointY() < pointY ) {
					transPointY = pointY - this->GetAt(index)->GetEndPointY();
					isIntegerY = true;
				}
				break;

		case 7 : if ( this->GetAt(index)->GetStartPointX() > pointX ) {
					 transPointX = this->GetAt(index)->GetStartPointX() - pointX;
					 isIntegerX = false;
				}
				 if ( this->GetAt(index)->GetStartPointX() < pointX ) {
					transPointX = pointX - this->GetAt(index)->GetStartPointX();
					isIntegerX = true;
				}
				if ( this->GetAt(index)->GetEndPointY() > pointY ) {
					transPointY = this->GetAt(index)->GetEndPointY() - pointY;
					isIntegerY = false;
				}
				if ( this->GetAt(index)->GetEndPointY() < pointY ) {
					transPointY = pointY - this->GetAt(index)->GetEndPointY();
					isIntegerY = true;
				}
				break;

		case 8 : if ( this->GetAt(index)->GetStartPointX() > pointX ) {
					 transPointX = this->GetAt(index)->GetStartPointX() - pointX;
					 isIntegerX = false;
			 	 }
				 if ( this->GetAt(index)->GetStartPointX() < pointX ) {
					transPointX = pointX - this->GetAt(index)->GetStartPointX();
					isIntegerX = true;
				 }
				 break;

		case 9 : if ( middlePointX > pointX ) {
					transPointX = middlePointX - pointX;
					isIntegerX = false;
				}
				if ( middlePointX < pointX ) {
					transPointX = pointX - middlePointX;
					isIntegerX = true;
				}
				break;

		default : break;
	}

	while ( i < select->GetSelectChart()->GetLength() ) 
	{
		index = select->GetSelectChart()->GetAt(i).GetSeletedSymbolIndex();

		startPointX = this->GetAt( index )->GetStartPointX();
		startPointY = this->GetAt( index )->GetStartPointY();
		endPointX = this->GetAt( index )->GetEndPointX();
		endPointY = this->GetAt( index )->GetEndPointY();
		middlePointX = static_cast <Selection *>(this->GetAt(index))->GetMiddlePointX();
		middlePointY = static_cast <Selection *>(this->GetAt(index))->GetMiddlePointY();

		switch ( number ) 
		{
			case 1 : if ( isIntegerX == false ) {
						startPointX = startPointX - transPointX;
					 }
					 if ( isIntegerX == true ) {
						startPointX = startPointX + transPointX;
					 }
					 if ( isIntegerY == false ) {
						 startPointY = startPointY - transPointY;
					 }
					 if ( isIntegerY == true ) {
						 startPointY = startPointY + transPointY;
					 }
					 break;

			case 2 : if ( isIntegerY == false ) {
						 startPointY = startPointY - transPointY;
					 }
					 if ( isIntegerY == true ) {
						 startPointY = startPointY + transPointY;
					 }
					 break;

			case 3 : if ( isIntegerY == false ) {
						 startPointY = startPointY - transPointY;
					 }
					 if ( isIntegerY == true ) {
						 startPointY = startPointY + transPointY;
					 }
					 if ( isIntegerX == false ) {
						 endPointX = endPointX - transPointX;
					 }
					 if ( isIntegerX == true ) {
						 endPointX = endPointX + transPointX;
					 }
					 break;

			case 4 : if ( isIntegerX == false ) {
						 endPointX = endPointX - transPointX;
					 }
					 if ( isIntegerX == true ) {
						 endPointX = endPointX + transPointX;
					 }
					 break;
					 
			case 5 : if ( dynamic_cast < Selection * > ( this->GetAt( index ) ) ) {
						if ( this->GetAt(index)->GetEndPointY() > pointY ) {
							transMiddleY = this->GetAt(index)->GetEndPointY() - pointY;
							middlePointY = middlePointY - transMiddleY;
						}
						if ( this->GetAt(index)->GetEndPointY() < pointY ) {
							transMiddleY = pointY - this->GetAt(index)->GetEndPointY();
							middlePointY = middlePointY + transMiddleY;
						}
					 }
					 if ( isIntegerX == false ) {
						 endPointX = endPointX - transPointX;
					 }
					 else {
						 endPointX = endPointX + transPointX;
					 }
					 if ( isIntegerY == false ) {
						 endPointY = endPointY - transPointY;
					 }
					 else {
						 endPointY = endPointY + transPointY;
					 }
					 break;

			case 6 : if ( dynamic_cast < Selection * > ( this->GetAt( index ) ) ) {
						if ( this->GetAt(index)->GetEndPointY() > pointY ) {
							transMiddleY = this->GetAt(index)->GetEndPointY() - pointY;
							middlePointY = middlePointY - transMiddleY;
						}
						if ( this->GetAt(index)->GetEndPointY() < pointY ) {
							transMiddleY = pointY - this->GetAt(index)->GetEndPointY();
							middlePointY = middlePointY + transMiddleY;
						}
					 }
					 if ( isIntegerY == false ) {
						 endPointY = endPointY - transPointY;
					 }
					 if ( isIntegerY == true ) {
						 endPointY = endPointY + transPointY;
					 }
					 break;

			case 7 : if ( dynamic_cast < Selection * > ( this->GetAt( index ) ) ) {
						if ( this->GetAt(index)->GetEndPointY() > pointY ) {
							transMiddleY = this->GetAt(index)->GetEndPointY() - pointY;
							middlePointY = middlePointY - transMiddleY;
						}
						if ( this->GetAt(index)->GetEndPointY() < pointY ) {
							transMiddleY = pointY - this->GetAt(index)->GetEndPointY();
							middlePointY = middlePointY + transMiddleY;
						}
					 }
					 if ( isIntegerX == false ) {
						startPointX = startPointX - transPointX;
					 }
					 if ( isIntegerX == true ) {
						startPointX = startPointX + transPointX;
					 }
					 if ( isIntegerY == false ) {
						 endPointY = endPointY - transPointY;
					 }
					 if ( isIntegerY == true ) {
						 endPointY = endPointY + transPointY;
					 }
					 break;

			case 8 : if ( isIntegerX == false ) {
						startPointX = startPointX - transPointX;
					 }
					 if ( isIntegerX == true ) {
						startPointX = startPointX + transPointX;
					 }
					 break;

			case 9 : if ( isIntegerX == false ) {
						middlePointX = middlePointX - transPointX;
					 }
					 if ( isIntegerX == true ) {
						 middlePointX = middlePointX + transPointX;
					 }
					 break;

			default : break;
		}
	
		expression = this->GetAt( index )->GetExpression();
		Symbol	*symbol;

		if ( dynamic_cast <Sequence *>(this->GetAt( index ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		if ( dynamic_cast <BeforeRepeat *>( this->GetAt( index ) ) ) {
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		if ( dynamic_cast <AfterRepeat *>( this->GetAt( index ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		if ( dynamic_cast <Selection *>( this->GetAt( index ) ) ) {
				symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, 
										 middlePointX, middlePointY, expression );
		}

		this->symbols.Modify( index, symbol );
		
		i++;
	}

	return index;
}
//*/

void	Chart::MovePoint( Long sPointX, Long sPointY, Long ePointX, Long ePointY, 
						Long *transX, Long *transY, bool *isPointX, bool *isPointY ) {
	if ( sPointX <= ePointX ) {
		*transX = ePointX - sPointX;
		*isPointX = 0;
	}
	else {
		*transX = sPointX - ePointX;
		*isPointX = 1;
	}
	
	if ( sPointY <= ePointY ) {
		*transY = ePointY - sPointY;
		*isPointY = 0;
	}
	else {
		*transY = sPointY - ePointY;
		*isPointY = 1;
	}
}

Long	Chart::Move ( Long sPointX, Long sPointY, Long ePointX, Long ePointY ) {
	Long	transX;
	Long	transY;
	bool	isPointX;
	bool	isPointY;
	Long	startPointX;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;
	Long	middlePointX;
	Long	middlePointY;
	wstring	expression;
	Long	columnCount;

	Long	index;

	Symbol	*symbol;
	Symbol	*oldSymbol;

	this->MovePoint( sPointX, sPointY, ePointX, ePointY, &transX, &transY, &isPointX, &isPointY );

	for ( Long i = 0; i < this->GetLength(); i++ ) {
		startPointX = this->GetAt( i )->GetStartPointX();
		startPointY = this->GetAt( i )->GetStartPointY();
		endPointX = this->GetAt( i )->GetEndPointX();
		endPointY = this->GetAt( i )->GetEndPointY();
		middlePointX = static_cast < Selection * >( this->GetAt( i ) )->GetMiddlePointX();
		middlePointY = static_cast < Selection * >( this->GetAt( i ) )->GetMiddlePointY();
		expression = this->GetAt( i )->GetExpression().c_str();
		columnCount = static_cast < SwitchCase * >( this->GetAt( i ) )->GetColumnCount();

		if ( isPointX == 0 ) {
			startPointX = startPointX + transX;
			endPointX = endPointX + transX;
		}
		else {
			startPointX = startPointX - transX;
			endPointX = endPointX - transX;
		}

		if ( isPointY == 0 ) {
			startPointY = startPointY + transY;
			endPointY = endPointY + transY;
		}
		else {
			startPointY = startPointY - transY;
			endPointY = endPointY - transY;
		}
		if ( dynamic_cast < Sequence * >( this->GetAt( i ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < BeforeRepeat * >( this->GetAt( i ) ) ) {
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < AfterRepeat * >( this->GetAt( i ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < Selection * >( this->GetAt( i ) ) ) {
			if ( isPointX == 0 ) {
				middlePointX = middlePointX + transX;
			}
			else {
				middlePointX = middlePointX - transX;
			}

			if ( isPointY == 0 ) {
				middlePointY = middlePointY + transY;
			}
			else {
				middlePointY = middlePointY - transY;
			}
			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, 
									middlePointX, middlePointY, expression );
		}
		else if ( dynamic_cast < SwitchCase * >( this->GetAt( i ) ) ) {
			Long count = static_cast < SwitchCase * >( this->GetAt( i ) )->GetLength();
			wstring	*cases = new wstring[ columnCount + 1];
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( this->GetAt( i ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		else if ( dynamic_cast < Arrow * >( this->GetAt( i ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}
		
		oldSymbol = this->GetAt( i );

		this->symbols.Modify( i, symbol );

		delete oldSymbol;
	}
	return this->length;
}


Long	Chart::MoveKey ( Select *select, Long direction )	{

	Long	startPointX = 0;
	Long	startPointY = 0;
	Long	endPointX = 0;
	Long	endPointY = 0;
	Long	middlePointX = 0;
	Long	middlePointY = 0;
	wstring	expression;
	Long	columnCount;

	//Long	index;

	Symbol	*symbol;
	Symbol	*oldSymbol;

	for ( Long i = 0; i < this->length; i++ ) {

		switch ( direction )	{
			case 1:
				startPointX = 1;
				startPointY = 0;
				endPointX = 1;
				endPointY = 0;
				middlePointX = 1;
				middlePointY = 0;
				break;

			case 2:
				startPointX = 0;
				startPointY = -1;
				endPointX = 0;
				endPointY = -1;
				middlePointX = 0;
				middlePointY = -1;
				break;

			case 3:
				startPointX = 0;
				startPointY = 1;
				endPointX = 0;
				endPointY = 1;
				middlePointX = 0;
				middlePointY = 1;
				break;

			default:
				startPointX = -1;
				startPointY = 0;
				endPointX = -1;
				endPointY = 0;
				middlePointX = -1;
				middlePointY = 0;
				break;
		}

		startPointX += this->GetAt( i )->GetStartPointX();
		startPointY += this->GetAt( i )->GetStartPointY();
		endPointX += this->GetAt( i )->GetEndPointX();
		endPointY += this->GetAt( i )->GetEndPointY();

		if( dynamic_cast< Selection * > ( this->GetAt( i ) ) )	{
			middlePointX += static_cast < Selection * >( this->GetAt( i ) )->GetMiddlePointX();
			middlePointY += static_cast < Selection * >( this->GetAt( i ) )->GetMiddlePointY();
		}
		else	{
			middlePointX = -1;
			middlePointY = -1;
		}

		expression = this->GetAt( i )->GetExpression().c_str();
		columnCount = static_cast < SwitchCase * >( this->GetAt( i ) )->GetColumnCount();

		if ( dynamic_cast < Sequence * >( this->GetAt( i ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < BeforeRepeat * >( this->GetAt( i ) ) ) {
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < AfterRepeat * >( this->GetAt( i ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < Selection * >( this->GetAt( i ) ) ) {
			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, 
									middlePointX, middlePointY, expression );
		}
		else if ( dynamic_cast < SwitchCase * >( this->GetAt( i ) ) ) {
			Long count = static_cast < SwitchCase * >( this->GetAt( i ) )->GetLength();
			wstring	*cases = new wstring[ columnCount + 1];
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( this->GetAt( i ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		if ( dynamic_cast < Arrow * >( this->GetAt( i ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}
		
		oldSymbol = this->GetAt( i );

		this->symbols.Modify( i, symbol );

		delete oldSymbol;
	}
	return this->length;
}