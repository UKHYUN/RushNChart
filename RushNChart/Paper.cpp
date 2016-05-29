
/*
	프로젝트명 : Rush & Chart
	파  일  명 : Paper.cpp
	작  성  일 : 2014년 06월 18일
	팀      명 : i5(five)
	팀      원 : 안영보 ( 팀장 ), 채형석, 김지수, 고요셉(작가), 곽욱현 
*/

#include "Paper.h"
#include "Chart.h"
#include "Symbol.h"

#include "Selection.h"
#include "Sequence.h"
#include "AfterRepeat.h"
#include "BeforeRepeat.h"
#include "Arrow.h"

#include "Select.h"
#include "SelectChart.h"
#include "SelectPaper.h"
#include "SelectedSymbol.h"
#include "SwitchCase.h"

#include <stdio.h>
#include <wchar.h>
using namespace std;

#define MAX 100

Paper ::Paper ( ) 
	: symbols ( MAX ) {
		this->startPointX = 0 ;
		this->startPointY = 0 ;
		this->endPointX = 1280 ;
		this->endPointY = 768 ;
		this->chart = new Chart ;
		this->capacity = MAX ;
		this->length = 0 ;
}

Paper::~Paper( )	{
	for( Long i = 0; i < this->length; i++ )	{
		Symbol *symbol = this->symbols.GetAt( i );
		delete symbol;
	}
}

Paper ::Paper ( Long startPointX , Long startPointY , Long endPointX , Long endPointY , Long capacity )
	: symbols ( capacity ) {
		this->startPointX = startPointX ;
		this->startPointY = startPointY ;
		this->endPointX = endPointX ;
		this->endPointY = endPointY ;
		this->chart = 0 ;
		this->capacity = capacity ;
		this->length = 0 ;

}//*/

Paper::Paper( const Paper& source )
	:symbols(source.capacity)	{
		if( source.chart != 0 )	{
			this->chart = new Chart( *(source.chart) );
		}
		else	{
			this->chart = 0;
		}
		Symbol *symbol;
		Symbol *temp;

		for( Long i = 0; i < source.length; i++)	{
			temp = source.symbols.GetAt(i);

			if( dynamic_cast< Sequence * >( temp ) )	{
				symbol = new Sequence( *( Sequence * ) temp );
			}
			else  if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
				symbol = new BeforeRepeat( *( BeforeRepeat * ) temp );
			}
			else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
				symbol = new AfterRepeat( *( AfterRepeat * ) temp );
			}
			else if( dynamic_cast< Selection * > ( temp ) )	{
				symbol = new Selection( *( Selection * ) temp );
			}
			else if( dynamic_cast< SwitchCase * > ( temp ) )	{
				symbol = new SwitchCase( *( SwitchCase * ) temp );
			}
			else if ( dynamic_cast< Arrow * > ( temp ) )	{
				symbol = new Arrow( *( Arrow * ) temp );
			}
			
			this->symbols.Store( i, symbol );
		}

		this->capacity = source.capacity;
		this->length = source.length;
		this->startPointX = source.startPointX ;
		this->startPointY = source.startPointY ;
		this->endPointX = source.endPointX ;
		this->endPointY = source.endPointY ;

}

Paper& Paper::operator= ( const Paper& source )	{

	for ( Long i = 0 ; i < length ; i ++ ) {
		Symbol *deleteSymbol = this->GetAt( i ) ;
		if( deleteSymbol != 0 ){
			delete deleteSymbol ;
			this->symbols.Modify( i , 0 );
		}
	}

	if ( this->chart != 0 ) {
		delete	this->chart ;
	}
	this->chart = source.chart ;
	Symbol *symbol;
	Symbol *temp;

	for( Long i = 0; i < source.length; i++)	{
		temp = source.symbols.GetAt(i);

		if( dynamic_cast< Sequence * >( temp ) )	{
			symbol = new Sequence( *( Sequence * ) temp );
		}
		else  if( dynamic_cast< BeforeRepeat * > ( temp ) )	{
			symbol = new BeforeRepeat( *( BeforeRepeat * ) temp );
		}
		else if( dynamic_cast< AfterRepeat * > ( temp ) )	{
			symbol = new AfterRepeat( *( AfterRepeat * ) temp );
		}
		else if( dynamic_cast< Selection * > ( temp ) )	{
			symbol = new Selection( *( Selection * ) temp );
		}
		else if( dynamic_cast< SwitchCase * > ( temp ) )	{
			symbol = new SwitchCase( *( SwitchCase * ) temp );
		}
		else if ( dynamic_cast< Arrow * > ( temp ) )	{
				symbol = new Arrow( *( Arrow * ) temp );
			}
		this->symbols.Store( i, symbol );
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->startPointX = source.startPointX ;
	this->startPointY = source.startPointY ;
	this->endPointX = source.endPointX ;
	this->endPointY = source.endPointY ;
	return	*this ;
}

Symbol* Paper::GetAt( Long index ) const{

	return const_cast< Symbol* >(this->symbols.GetAt( index ) );
}

Long Paper ::Draw ( Long startPointX , Long startPointY , wstring expression , string type ) {
	Symbol	*symbol ;
	Long	index = 0 ;


	if ( type.compare("Sequence") == 0 ) {
		symbol = new Sequence ( startPointX , startPointY , expression ) ;
	}
	else if ( type.compare("BeforeRepeat") == 0 ) {
		symbol = new BeforeRepeat ( startPointX , startPointY , expression ) ;
	}
	else if ( type.compare("AfterRepeat") == 0 ) {
		symbol = new AfterRepeat ( startPointX , startPointY , expression ) ;
	}
	else if ( type.compare("Selection") == 0 ) {
		symbol = new Selection ( startPointX , startPointY , expression ) ;
	}
	else if ( type.compare("SwitchCase") == 0 ) {
		symbol = new SwitchCase ( 4, startPointX , startPointY , expression ) ;
		//symbol = new SwitchCase ( columnCount, startPointX , startPointY , endPointX, endPointY , expression) ;
	}
	else if ( type.compare("Arrow") == 0 ) {
		symbol = new Arrow ( startPointX , startPointY ) ;
	}
	if ( this->capacity > this->length ) {
		index = this->symbols.Store ( this->length , symbol ) ;
	}
	else {
		index = this->symbols.AppendFromRear ( symbol ) ;
		this->capacity++ ;
	}
	this->length++ ;

	return index ;

}
//*/
//*
Long Paper::Draw ( Long startPointX , Long startPointY , Long endPointX, Long endPointY, wstring expression , 
	string type, Long columnCount ){
	Symbol	*symbol ;
	Long	index = 0 ;

	if ( startPointX > endPointX ) {
		Long	tempPointX ;
		tempPointX = startPointX ;
		startPointX = endPointX ;
		endPointX = tempPointX ;
	}

	if ( startPointY > endPointY ) {
		Long	tempPointY ;
		tempPointY = startPointY ;
		startPointY = endPointY ;
		endPointY = tempPointY ;
	}

	if ( endPointX - startPointX <= 10 || endPointY - startPointY <=10 ) {
		if ( type.compare("SwitchCase") == 0 ) {
			symbol = new SwitchCase ( columnCount, startPointX , startPointY , expression) ;
		}

	}
	else {
		if ( type.compare("SwitchCase") == 0 ) {
			symbol = new SwitchCase ( columnCount, startPointX, startPointY , endPointX, endPointY, expression) ;
		}
	}

	if ( this->capacity > this->length ) {
		index = this->symbols.Store ( this->length , symbol ) ;
	}
	else {
		index = this->symbols.AppendFromRear ( symbol ) ;
		this->capacity++ ;
	}
	this->length++ ;


	return index ;
}
//*/


Long Paper ::Draw ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression, 
	string type ) {
	Symbol	*symbol ;
	Long	index = 0 ;
	
	if ( startPointX > endPointX ) {
		Long	tempPointX ;
		tempPointX = startPointX ;
		startPointX = endPointX ;
		endPointX = tempPointX ;
	}
	if ( startPointY > endPointY ) {
		Long	tempPointY ;
		tempPointY = startPointY ;
		startPointY = endPointY ;
		endPointY = tempPointY ;
	}

	if ( endPointX - startPointX <= 10 || endPointY - startPointY <=10 ) {
		if ( type.compare("Sequence") == 0 ) {
			symbol = new Sequence ( startPointX, startPointY, expression ) ;
		}
		else if ( type.compare("BeforeRepeat") == 0 ) {
			symbol = new BeforeRepeat ( startPointX, startPointY, expression ) ;
		}
		else if ( type.compare("AfterRepeat") == 0 ) {
			symbol = new AfterRepeat ( startPointX, startPointY, expression ) ;
		}
		else if ( type.compare("Selection") == 0 ) {
			symbol = new Selection ( startPointX, startPointY, expression ) ;
		}
		else if ( type.compare("Arrow") == 0 ) {
			symbol = new Arrow ( startPointX, startPointY ) ;
		}
	}
	else {
		if ( type.compare("Sequence") == 0 ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression ) ;
		}
		else if ( type.compare("BeforeRepeat") == 0 ) {
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression ) ;
		}
		else if ( type.compare("AfterRepeat") == 0 ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression ) ;
		}
		else if ( type.compare("Selection") == 0 ) {
			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, expression ) ;
		}
		else if ( type.compare("Arrow") == 0 ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY ) ;
		}

	}
	if ( this->capacity > this->length ) {
		index = this->symbols.Store ( this->length, symbol ) ;
	}
	else {
		index = this->symbols.AppendFromRear ( symbol ) ;
		this->capacity++ ;
	}
	this->length++ ;

	//return this->symbols.GetAt(index);
	return index ;

}


Long Paper::Write( Long index, wstring expression ) {
	Symbol *newSymbol ;
	Symbol *oldSymbol ;

	oldSymbol = this-> symbols.GetAt(index) ;

	if( dynamic_cast< Sequence * >( oldSymbol ) )	{
			newSymbol = new Sequence( 
				oldSymbol->GetStartPointX(), 
				oldSymbol->GetStartPointY(), 
				oldSymbol->GetEndPointX(), 
				oldSymbol->GetEndPointY(),

				oldSymbol->GetExpressionStartPointX(), 
				oldSymbol->GetExpressionStartPointY(), 
				oldSymbol->GetExpressionEndPointX(), 
				oldSymbol->GetExpressionEndPointY(),
				( oldSymbol->GetExpression() + expression ) ) ;
		}
		else  if( dynamic_cast< BeforeRepeat * > ( oldSymbol ) )	{
			BeforeRepeat *beforeRepeat = static_cast< BeforeRepeat * > ( oldSymbol );
			newSymbol = new BeforeRepeat( 
				oldSymbol->GetStartPointX(), 
				oldSymbol->GetStartPointY(), 
				oldSymbol->GetEndPointX(), 
				oldSymbol->GetEndPointY(),

				oldSymbol->GetExpressionStartPointX(), 
				oldSymbol->GetExpressionStartPointY(), 
				oldSymbol->GetExpressionEndPointX(), 
				oldSymbol->GetExpressionEndPointY(),
				beforeRepeat->GetMiddlePointX(),
				beforeRepeat->GetMiddlePointY(),
				( oldSymbol->GetExpression() + expression ) ) ;
		}
		else if( dynamic_cast< AfterRepeat * > ( oldSymbol ) )	{
			AfterRepeat *afterRepeat = static_cast< AfterRepeat * > ( oldSymbol );
			newSymbol = new AfterRepeat(
				oldSymbol->GetStartPointX(), 
				oldSymbol->GetStartPointY(), 
				oldSymbol->GetEndPointX(), 
				oldSymbol->GetEndPointY(),

				oldSymbol->GetExpressionStartPointX(),
				oldSymbol->GetExpressionStartPointY(),
				oldSymbol->GetExpressionEndPointX(),
				oldSymbol->GetExpressionEndPointY(),
                afterRepeat->GetMiddlePointX(),
				afterRepeat->GetMiddlePointY(),
				( oldSymbol->GetExpression() + expression ) ) ;
		}
		else if( dynamic_cast< Selection * > ( oldSymbol ) )	{
			Selection *selection = static_cast< Selection * > ( oldSymbol );
			newSymbol = new Selection( 
				oldSymbol->GetStartPointX(), 
				oldSymbol->GetStartPointY(), 
				oldSymbol->GetEndPointX(), 
				oldSymbol->GetEndPointY(),

				oldSymbol->GetExpressionStartPointX(), 
				oldSymbol->GetExpressionStartPointY(), 
				oldSymbol->GetExpressionEndPointX(), 
				oldSymbol->GetExpressionEndPointY(),
				selection->GetMiddlePointX(),
				selection->GetMiddlePointY(),
				( oldSymbol->GetExpression() + expression ) ) ;
				
		}
		else if( dynamic_cast< SwitchCase * > ( oldSymbol ) )	{
			 SwitchCase *temp = static_cast< SwitchCase * >( oldSymbol ) ;
			 Selection *tempSelection = temp->GetSelection();

			 Selection *selection = new Selection ( tempSelection->GetStartPointX(), tempSelection->GetStartPointY(), 
				 tempSelection->GetEndPointX(), tempSelection->GetEndPointY(), tempSelection->GetMiddlePointX(), tempSelection->GetMiddlePointY(),
				 ( oldSymbol->GetExpression() + expression ) );
			 
			 Sequence* *( tempArray ) = new Sequence* [ temp->GetCapacity() ];
			 for ( Long i = 0; i < temp->GetLength(); i++ )	{
				 Sequence *tempCase = new Sequence ( *( temp->GetCases( i ) ) );
				 tempArray [ i ] = tempCase;
			 }

			 newSymbol =
				 new SwitchCase( temp->GetColumnCount(), temp->GetStartPointX(), temp->GetStartPointY(), 
				 temp->GetEndPointX(), temp->GetEndPointY(), selection->GetExpression() ,
				 selection, tempArray ) ;
		}
		
		delete oldSymbol ;
		index = this->symbols.Modify( index, newSymbol ) ;

		return index ;

}


Long Paper::WriteCase( Long symbolIndex, Long caseNumber, Long expressionIndex, wstring expression ) {
	Symbol *newSymbol ;
	Symbol *oldSymbol ;

	oldSymbol = this-> symbols.GetAt( symbolIndex ) ;

	if( dynamic_cast< SwitchCase * > ( oldSymbol ) )	{
		SwitchCase *temp = static_cast< SwitchCase * >( oldSymbol ) ;
		Selection *tempSelection = temp->GetSelection();

		Selection *selection = new Selection ( tempSelection->GetStartPointX(), tempSelection->GetStartPointY(), 
			tempSelection->GetEndPointX(), tempSelection->GetEndPointY(), tempSelection->GetMiddlePointX(), tempSelection->GetMiddlePointY(),
			temp->GetExpression() );

		Sequence* *( tempArray ) = new Sequence* [ temp->GetCapacity() ];
		wstring insertString;
		for ( Long i = 0; i < temp->GetLength(); i++ )	{
			insertString.clear();
			if ( i == ( caseNumber - 1 ) )	{
				wstring tempString = temp->GetCases( i )->GetExpression();
				if( expressionIndex > 0 && expressionIndex < temp->GetCases( i )->GetExpression().size() )	{
					wstring strHead = tempString.substr( 0, expressionIndex );
					wstring strTail = tempString.substr( expressionIndex, tempString.size() );
		
					insertString.append ( strHead );
					insertString.append ( expression );
					insertString.append ( strTail );
				}
				else if( expressionIndex <= 0 )	{
					wstring strTail = tempString.substr( expressionIndex, tempString.size() );

					insertString.append ( expression );
					insertString.append ( strTail );
				}
				else	{
					wstring strHead = tempString.substr( 0, expressionIndex );

					insertString.append ( strHead );
					insertString.append ( expression );
				}
			}
			else	{
				insertString = temp->GetCases( i )->GetExpression();
			}

			Sequence *tempCase = new Sequence ( temp->GetCases( i )->GetStartPointX(), temp->GetCases( i )->GetStartPointY(),
				temp->GetCases( i )->GetEndPointX(), temp->GetCases( i )->GetEndPointY(), insertString );
			tempArray [ i ] = tempCase;
		}

		newSymbol =
			new SwitchCase( temp->GetColumnCount(), temp->GetStartPointX(), temp->GetStartPointY(), 
			temp->GetEndPointX(), temp->GetEndPointY(), selection->GetExpression() ,
			selection, tempArray ) ;
	}
		
	delete oldSymbol ;
	symbolIndex = this->symbols.Modify( symbolIndex, newSymbol ) ;

	return symbolIndex ;

}


Long Paper::Correct( Long symbolIndex, Long correctIndex, wstring expression )	{
	Symbol *symbol = this->GetAt( symbolIndex );
	Symbol *newSymbol;

	wstring tempString = symbol->GetExpression();
	wstring insertString;

	if( correctIndex > 0 && correctIndex < symbol->GetExpression().size() )	{
		wstring strHead = tempString.substr( 0, correctIndex );
		wstring strTail = tempString.substr( correctIndex, tempString.size() );
		
		insertString.append ( strHead );
		insertString.append ( expression );
		insertString.append ( strTail );
	}
	else if( correctIndex <= 0 )	{
		wstring strTail = tempString.substr( correctIndex, tempString.size() );

		insertString.append ( expression );
		insertString.append ( strTail );
	}
	else	{
		wstring strHead = tempString.substr( 0, correctIndex );

		insertString.append ( strHead );
		insertString.append ( expression );
	}


	if( dynamic_cast < Sequence * > ( symbol ) )	{

		newSymbol = new Sequence ( symbol->GetStartPointX(), symbol->GetStartPointY(), symbol->GetEndPointX(),
			symbol->GetEndPointY(), symbol->GetExpressionStartPointX(), symbol->GetExpressionStartPointY(),
			symbol->GetExpressionEndPointX(), symbol->GetExpressionEndPointY(), insertString );
	}
	else if( dynamic_cast < BeforeRepeat * > ( symbol ) )	{
		BeforeRepeat *beforeRepeat = static_cast < BeforeRepeat * > ( symbol ) ;
		newSymbol = new BeforeRepeat ( symbol->GetStartPointX(), symbol->GetStartPointY(), symbol->GetEndPointX(),
			symbol->GetEndPointY(), symbol->GetExpressionStartPointX(), symbol->GetExpressionStartPointY(),
			symbol->GetExpressionEndPointX(), symbol->GetExpressionEndPointY(), beforeRepeat->GetMiddlePointX(),
			beforeRepeat->GetMiddlePointY(), insertString );
	}
	else if( dynamic_cast < AfterRepeat * > ( symbol ) )	{
		AfterRepeat *afterRepeat = static_cast < AfterRepeat * > ( symbol ) ;
		newSymbol = new AfterRepeat ( symbol->GetStartPointX(), symbol->GetStartPointY(), symbol->GetEndPointX(),
			symbol->GetEndPointY(), symbol->GetExpressionStartPointX(), symbol->GetExpressionStartPointY(),
			symbol->GetExpressionEndPointX(), symbol->GetExpressionEndPointY(), afterRepeat->GetMiddlePointX(),
			afterRepeat->GetMiddlePointY(), insertString );
	}
	else if( dynamic_cast < Selection * > ( symbol ) )	{
		Selection *selection = static_cast < Selection * > ( symbol ) ;
		newSymbol = new Selection ( symbol->GetStartPointX(), symbol->GetStartPointY(), symbol->GetEndPointX(),
			symbol->GetEndPointY(), symbol->GetExpressionStartPointX(), symbol->GetExpressionStartPointY(),
			symbol->GetExpressionEndPointX(), symbol->GetExpressionEndPointY(), selection->GetMiddlePointX(),
			selection->GetMiddlePointY(), insertString );
	}
	else if( dynamic_cast < SwitchCase * > ( symbol ) )	{
		SwitchCase *temp = static_cast< SwitchCase * >( symbol ) ;
		Selection *tempSelection = temp->GetSelection();

		Selection *selection = new Selection ( tempSelection->GetStartPointX(), tempSelection->GetStartPointY(), 
			tempSelection->GetEndPointX(), tempSelection->GetEndPointY(), tempSelection->GetMiddlePointX(), tempSelection->GetMiddlePointY(),
			insertString );
			 
		Sequence* *( tempArray ) = new Sequence* [ temp->GetCapacity() ];
		for ( Long i = 0; i < temp->GetLength(); i++ )	{
			Sequence *tempCase = new Sequence ( *( temp->GetCases( i ) ) );
			tempArray [ i ] = tempCase;
		}

		newSymbol =
			new SwitchCase( temp->GetColumnCount(), temp->GetStartPointX(), temp->GetStartPointY(), 
				 temp->GetEndPointX(), temp->GetEndPointY(), selection->GetExpression() ,
				 selection, tempArray ) ;
	}

	delete symbol;
	Long ret = this->symbols.Modify( symbolIndex, newSymbol );

	return ret;
}

Long Paper::Erase ( Long symbolIndex, Long eraseIndex )	{
	Long ret = -2;

	Symbol *symbol = this->symbols.GetAt( symbolIndex );
	Symbol *newSymbol;

	Long startPointX = symbol->GetStartPointX();
	Long startPointY = symbol->GetStartPointY();
	Long endPointX = symbol->GetEndPointX();
	Long endPointY = symbol->GetEndPointY();

	Long expressionStartPointX = symbol->GetExpressionStartPointX();
	Long expressionStartPointY = symbol->GetExpressionStartPointY();
	Long expressionEndPointX = symbol->GetExpressionEndPointX();
	Long expressionEndPointY = symbol->GetExpressionEndPointY();

	wstring tempString = symbol->GetExpression();
	wstring expression;

	if( eraseIndex < tempString.size() )	{
		//expression.erase ( eraseIndex );
		if( eraseIndex > 0 && eraseIndex < symbol->GetExpression().size() )	{
			wstring strHead = tempString.substr( 0, eraseIndex );
			wstring strTail = tempString.substr( eraseIndex + 1, tempString.size() );
		
			expression.append ( strHead );
			expression.append ( strTail );
		}
		else if( eraseIndex <= 0 )	{
			wstring strTail = tempString.substr( eraseIndex + 1, tempString.size() );

			expression.append ( strTail );
		}
		else	{
			wstring strHead = tempString.substr( 0, eraseIndex );

			expression.append ( strHead );
		}


		if( dynamic_cast < Sequence * > ( symbol ) )	{

			newSymbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, 
				expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY, expression );
		}
		else if( dynamic_cast < BeforeRepeat * > ( symbol ) )	{
			BeforeRepeat *beforeRepeat = static_cast < BeforeRepeat * > ( symbol ) ;
			newSymbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, 
				expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY,
				beforeRepeat->GetMiddlePointX(), beforeRepeat->GetMiddlePointY(), expression );
		}
		else if( dynamic_cast < AfterRepeat * > ( symbol ) )	{
			AfterRepeat *afterRepeat = static_cast < AfterRepeat * > ( symbol ) ;
			newSymbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, 
				expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY,
				afterRepeat->GetMiddlePointX(), afterRepeat->GetMiddlePointY(), expression );
		}
		else if( dynamic_cast < Selection * > ( symbol ) )	{
			Selection *selection = static_cast < Selection * > ( symbol ) ;
			newSymbol = new Selection ( startPointX, startPointY, endPointX, endPointY, 
				expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY,
				selection->GetMiddlePointX(), selection->GetMiddlePointY(), expression );
		}
		else if( dynamic_cast < SwitchCase * > ( symbol ) )	{
			SwitchCase *temp = static_cast< SwitchCase * >( symbol ) ;
			Selection *tempSelection = temp->GetSelection();

			Long columnCount = static_cast < SwitchCase * >( symbol )->GetColumnCount() ;
			Long count = static_cast < SwitchCase * >( symbol )->GetLength();
			wstring	*cases = new wstring[ columnCount + 1];
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( symbol )->GetCases( j )->GetExpression();
			}
			newSymbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, 
				tempSelection->GetMiddlePointX(), tempSelection->GetMiddlePointY(), cases );
		}

		delete symbol;

		ret = this->symbols.Modify( symbolIndex, newSymbol );
	}
	return ret;
}


Long Paper::EraseCase ( Long symbolIndex, Long caseNumber, Long eraseIndex )	{
	Long ret = -2;

	Symbol *symbol = this->symbols.GetAt( symbolIndex );
	Symbol *newSymbol;

	Long startPointX = symbol->GetStartPointX();
	Long startPointY = symbol->GetStartPointY();
	Long endPointX = symbol->GetEndPointX();
	Long endPointY = symbol->GetEndPointY();

	Long expressionStartPointX = symbol->GetExpressionStartPointX();
	Long expressionStartPointY = symbol->GetExpressionStartPointY();
	Long expressionEndPointX = symbol->GetExpressionEndPointX();
	Long expressionEndPointY = symbol->GetExpressionEndPointY();

	wstring expression;

	if( dynamic_cast < SwitchCase * > ( symbol ) )	{
		SwitchCase *temp = static_cast< SwitchCase * >( symbol ) ;
		Selection *tempSelection = temp->GetSelection();

		wstring tempString = temp->GetCases( caseNumber - 1 )->GetExpression();
		
		if( eraseIndex < tempString.size() )	{

			Selection *selection = new Selection ( tempSelection->GetStartPointX(), tempSelection->GetStartPointY(), 
				tempSelection->GetEndPointX(), tempSelection->GetEndPointY(), tempSelection->GetMiddlePointX(), tempSelection->GetMiddlePointY(),
				temp->GetExpression() );

			Sequence* *( tempArray ) = new Sequence* [ temp->GetCapacity() ];
			for ( Long i = 0; i < temp->GetLength(); i++ )	{
				expression.clear();
				if ( i == ( caseNumber - 1 ) )	{
					if( eraseIndex > 0 && eraseIndex < temp->GetCases( i )->GetExpression().size() )	{
							wstring strHead = tempString.substr( 0, eraseIndex );
							wstring strTail = tempString.substr( eraseIndex + 1, tempString.size() );
		
							expression.append ( strHead );
							expression.append ( strTail );
						}
						else if( eraseIndex <= 0 )	{
							wstring strTail = tempString.substr( eraseIndex + 1, tempString.size() );

							expression.append ( strTail );
						}
						else	{
							wstring strHead = tempString.substr( 0, eraseIndex );

							expression.append ( strHead );
						}
				}
				else	{
					expression = temp->GetCases( i )->GetExpression();
				}

				Sequence *tempCase = new Sequence ( temp->GetCases( i )->GetStartPointX(), temp->GetCases( i )->GetStartPointY(),
					temp->GetCases( i )->GetEndPointX(), temp->GetCases( i )->GetEndPointY(), expression );
				tempArray [ i ] = tempCase;
			}

			newSymbol =
			new SwitchCase( temp->GetColumnCount(), temp->GetStartPointX(), temp->GetStartPointY(), 
			temp->GetEndPointX(), temp->GetEndPointY(), selection->GetExpression() ,
			selection, tempArray ) ;
			
			delete symbol ;
			ret = this->symbols.Modify( symbolIndex, newSymbol );
		}
	}
	return ret;
}


/*
	함수이름 : Load
	설    명 : 저장된 데이터를 불러온다
	입    력 : loadName
	출    력 : index
	만 든 이 : 채형석
*/
Long Paper::Load ( wchar_t *loadName )	{
	Long	startPointX;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;

	Long	expressionStartPointX;
	Long	expressionStartPointY;
	Long	expressionEndPointX;
	Long	expressionEndPointY;
	
	Long	middlePointX;
	Long	middlePointY;

	wstring	expression;

	Long	columnCount;

	wchar_t	line[1024] = {0, };
	wchar_t	cases[256] = { 0, };
	wchar_t	temp[256] = { 0, };
	
	wstring	type;

	Long	count;
	Long	i = 0;
	Long	j;
	Long	k = 0;
	
	FILE	*symbols;
	//Long	flag;
	bool	loadDate = 0;			// 종이인지 차트인지 확인하기 위한 Flag
	wstring	division;				// 종이 문자가 나오면 다음부터 차트이기 떄문에 구분하기 위한 변수

	symbols = _wfopen ( loadName, L"rb" );
	
	if ( symbols != 0 )
	{
		fgetws ( line, 1024, symbols );

		while ( !feof ( symbols ) ) 
		{
			
			count = 1;
			
			if ( loadDate == 0 ) 
			{
				i = 0;
				while ( count <= 14 && loadDate == 0 ) 
				{
					j = 0;
					//strcpy ( temp, "" );
					memset ( temp, 0x00, sizeof( wchar_t ) * 256 );
				
					while ( line[i] == 0 && i < 256)	
					{
						i++;
					}

					while ( line[i] != '\t' && line[i] != '\n' )
					{
						temp[j] = line[i];
						j++;
						i++;
					}
				
					//temp[j] = '\n';
					i++;
					division = wstring ( temp );
					if ( count == 1 && division.compare ( L"Paper" ) == 0 )		// 종이 데이터의 끝인지 파악한다. 
					{
						loadDate = 1;
					}
					if ( loadDate != 1 )						// 종이 데이터가 끝이 아니면 종이에 저장한다.
					{ 
						switch ( count ) 
						{
							case 1 : startPointX = _wtoi ( temp );				break;
							case 2 : startPointY = _wtoi ( temp );				break;
							case 3 : endPointX = _wtoi ( temp );				break;
							case 4 : endPointY = _wtoi ( temp );				break;
							case 5 : expressionStartPointX = _wtoi ( temp );	break;
							case 6 : expressionStartPointY = _wtoi ( temp );	break;
							case 7 : expressionEndPointX = _wtoi ( temp );		break;
							case 8 : expressionEndPointY = _wtoi ( temp );		break;
							case 9 : expression = wstring ( temp );				break;
							case 10 : middlePointX = _wtoi ( temp );			break;
							case 11 : middlePointY = _wtoi ( temp );			break;
							case 12 : columnCount = _wtoi ( temp );				break;
							case 13 : wcscpy ( cases, temp );					break;
							case 14 : type = wstring ( temp );					break;
							default :											break;
						}
						count++;
					}
					
				}	

				if ( loadDate != 1 ) {
					Symbol	*symbol;
					Long	index;

					if ( type.compare ( L"Sequence" ) == 0 ) {
						symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY,
							expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY, expression );
					}
					else if ( type.compare ( L"BeforeRepeat" ) == 0 ) {
						symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY,
							expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY, 
							middlePointX, middlePointY, expression );
					}
					else if ( type.compare ( L"AfterRepeat" ) == 0 ) {
						symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY,
							expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY, expression );
					}
					else if ( type.compare ( L"Selection" ) == 0 ) {
						symbol = new Selection ( startPointX, startPointY, endPointX, endPointY,
							expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY, middlePointX, middlePointY, expression );
					}
					else if ( type.compare ( L"Arrow" ) == 0 ) {
						symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
					}


					else if ( type.compare ( L"SwitchCase" ) == 0 ) {
						i = 0;
						k = 0 ;

						wstring	*text = new wstring[columnCount+1] ;

						while ( i <= columnCount ) {
							j = 0;
					
							wchar_t	tempCase[256] = { 0, };
							//memset ( tempCase, 0x00, sizeof( wchar_t ) * 256 );

							while ( cases[k] != ',' )//&& cases[k] != '\n') 
							{
								tempCase[j] = cases[k];
								j++;
								k++;
							}
							k++;
							text[i] = wstring ( tempCase );
							i++;
						}
						symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY,
												 expression, middlePointX, middlePointY, text );
					}
					if ( this->capacity > this->length ) {
						index = this->symbols.Store ( this->length, symbol );
					}
					else {
						index = this->symbols.AppendFromRear ( symbol );
						this->capacity++;
					}
					this->length++;
				}
				fgetws ( line, 1024, symbols ) ;
			}

			// 차트를 로드한다.
			else						 
			{
				i = 0;
				while ( count <= 14 )
				{
				
					j = 0;
					memset ( temp, 0x00, sizeof( wchar_t ) * 256 );
				
					while ( line[i] == 0 && i < 256)	{
						i++;
					}

					while ( line[i] != '\t' && line[i] != '\n' ) 
					{
						temp[j] = line[i];
						j++;
						i++;
					}
				
					i++;
				
					switch ( count ) {
						case 1 : startPointX = _wtoi ( temp );				break;
						case 2 : startPointY = _wtoi ( temp );				break;
						case 3 : endPointX = _wtoi ( temp );					break;
						case 4 : endPointY = _wtoi ( temp );					break;
						case 5 : expressionStartPointX = _wtoi ( temp );		break;
						case 6 : expressionStartPointY = _wtoi ( temp );		break;
						case 7 : expressionEndPointX = _wtoi ( temp );		break;
						case 8 : expressionEndPointY = _wtoi ( temp );		break;
						case 9 : expression = wstring ( temp );				break;
						case 10 : middlePointX = _wtoi ( temp );				break;
						case 11 : middlePointY = _wtoi ( temp );				break;
						case 12 : columnCount = _wtoi ( temp );				break;
						case 13 : wcscpy ( cases, temp );					break;
						case 14 : type = wstring ( temp );					break;
						default :											break;
					}
					count++;
				}

				i = 0;

				Symbol	*symbol;
				//Long	index;

				if ( type.compare ( L"Sequence" ) == 0 ) {
					symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY,
						expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY, expression );
				}
				else if ( type.compare ( L"BeforeRepeat" ) == 0 ) {
					symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY,
						expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY, expression );
				}
				else if ( type.compare ( L"AfterRepeat" ) == 0 ) {
					symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY,
						expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY, expression );
				}
				else if ( type.compare ( L"Selection" ) == 0 ) {
					symbol = new Selection ( startPointX, startPointY, endPointX, endPointY,
						expressionStartPointX, expressionStartPointY, expressionEndPointX, expressionEndPointY, expression );
				}
				else if ( type.compare ( L"Arrow" ) == 0 ) {
					symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
				}
				
				else if ( type.compare ( L"SwitchCase" ) == 0 ) {
					i = 0;
					k = 0 ;

					wstring	*text = new wstring[columnCount+1] ;

					while ( i <= columnCount ) {
						j = 0;
					
						wchar_t	tempCase[256] = { 0, };

						while ( cases[k] != ',' )//&& cases[k] != '\n') 
						{
							tempCase[j] = cases[k];
							j++;
							k++;
						}
						k++;
						text[i] = wstring ( tempCase );
						i++;
					}
					symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY,
											expression, middlePointX, middlePointY, text );
				}
				//*/
				this->chart->Paste( symbol ) ;
			
				fgetws ( line, 1024, symbols ) ;
			}
		}
		fclose ( symbols );
	}

	return this->length;
}



/*
	함수이름 : Save
	설    명 : 저장된 데이터를 불러온다
	입    력 : savePaper
	출    력 : index
	만 든 이 : 채형석
*/
Long Paper::Save ( wchar_t *savePaper )	{
	FILE *file;
	file = _wfopen ( savePaper, L"wb" );// 파일 열기

	if( file != 0 )	{ // 파일의 끝이 아닌 동안 반복?..

		wchar_t charSymbol [ 256 ] ;
		wchar_t charTemp [ 256 ] = { 0, };

		for( Long i = 0; i < this->length; i++ )	{
			memset( charSymbol, 0x00, sizeof( wchar_t ) * 256 );
			memset( charTemp, 0x00, sizeof( wchar_t ) * 256 );

			//charSymbol에 symbols의 각 요소를 저장한다
			_swprintf( charSymbol, L"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t",
				this->symbols[ i ]->GetStartPointX(),
				this->symbols[ i ]->GetStartPointY(),
				this->symbols[ i ]->GetEndPointX(),
				this->symbols[ i ]->GetEndPointY(),
				this->symbols[ i ]->GetExpressionStartPointX(),
				this->symbols[ i ]->GetExpressionStartPointY(),
				this->symbols[ i ]->GetExpressionEndPointX(),
				this->symbols[ i ]->GetExpressionEndPointY(),
				this->symbols[ i ]->GetExpression().c_str() );

			if ( dynamic_cast< Sequence * > ( this->symbols[ i ] ) )	{
				wchar_t *charType = L"\t\t\t\tSequence";
				wcscat( charTemp, charType );
			}
			else if ( dynamic_cast< Arrow * > ( this->symbols[ i ] ) )	{
				wchar_t *charType = L"\t\t\t\tArrow";
				wcscat( charTemp, charType );
			}
			else if( dynamic_cast< BeforeRepeat * > ( this->symbols[ i ] ) )	{
				BeforeRepeat *beforeRepeat = static_cast< BeforeRepeat * > ( this->symbols[ i ] );
				_swprintf( charTemp, L"%d\t%d\t\t\tBeforeRepeat", 
					beforeRepeat->GetMiddlePointX(),
					beforeRepeat->GetMiddlePointY() );
			}
			else if( dynamic_cast < AfterRepeat * > ( this->symbols[ i ] ) )	{
				AfterRepeat *afterRepeat = static_cast< AfterRepeat * > ( this->symbols[ i ] );
				_swprintf( charTemp, L"%d\t%d\t\t\tAfterRepeat", 
					afterRepeat->GetMiddlePointX(),
					afterRepeat->GetMiddlePointY() );
			}
			else if( dynamic_cast < Selection * > ( this->symbols[ i ] ) )	{
				Selection *selection = static_cast< Selection * > ( this->symbols[ i ] );
				_swprintf( charTemp, L"%d\t%d\t\t\tSelection", 
					selection->GetMiddlePointX(),
					selection->GetMiddlePointY() );
			}

			else if( dynamic_cast < SwitchCase * > (this->symbols[ i ] ) )	{
				SwitchCase *switchCase = static_cast< SwitchCase * > ( this->symbols[ i ]  );

				_swprintf( charTemp, L"%d\t%d\t%d\t", switchCase->GetSelection()->GetMiddlePointX(),
													  switchCase->GetSelection()->GetMiddlePointY(),
													  switchCase->GetColumnCount() );
				
				for( Long j = 0; j < switchCase->GetColumnCount() + 1; j++ )	{
					wchar_t charCases[ 256 ] = { 0, } ;
					_swprintf( charCases, L"%s,", switchCase->GetCases( j )->GetExpression().c_str() );

					wcscat ( charTemp, charCases );
				}

				wchar_t *charType = L"\tSwitchCase";
				wcscat ( charTemp, charType );
			}

			wchar_t *charLine = L"\n";
			wcscat( charTemp, charLine );
			wcscat( charSymbol, charTemp );
			
			fwrite( charSymbol, sizeof( charSymbol ), 1, file );
		}
		// Paper 저장이 끝나면 차트과 구분하기 위해 하나를 넣다.
		memset( charSymbol, 0x00, sizeof( wchar_t ) * 256 );
		//memset( charTemp, 0x00, sizeof( wchar_t ) * 256 );
		wchar_t *charLine = L"Paper\n";
		wcscat( charSymbol, charLine );
			
		fwrite( charSymbol, sizeof( charSymbol ), 1, file );

		for( Long i = 0; i < this->chart->GetLength() ; i++ )	{
			memset( charSymbol, 0x00, sizeof( wchar_t ) * 256 );
			memset( charTemp, 0x00, sizeof( wchar_t ) * 256 );

			//charSymbol에 symbols의 각 요소를 저장한다
			_swprintf( charSymbol, L"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t",
				this->chart->GetAt( i )->GetStartPointX(),
				this->chart->GetAt( i )->GetStartPointY(),
				this->chart->GetAt( i )->GetEndPointX(),
				this->chart->GetAt( i )->GetEndPointY(),
				this->chart->GetAt( i )->GetExpressionStartPointX(),
				this->chart->GetAt( i )->GetExpressionStartPointY(),
				this->chart->GetAt( i )->GetExpressionEndPointX(),
				this->chart->GetAt( i )->GetExpressionEndPointY(),
				this->chart->GetAt( i )->GetExpression().c_str() );

			if( dynamic_cast< Sequence * > ( this->chart->GetAt( i ) ) )	{
				wchar_t *charType = L"\t\t\t\tSequence";
				wcscat ( charTemp, charType );
			}
			else if( dynamic_cast< Arrow * > ( this->chart->GetAt( i ) ) )	{
				wchar_t *charType = L"\t\t\t\tArrow";
				wcscat ( charTemp, charType );
			}

			else if( dynamic_cast< BeforeRepeat * > ( this->chart->GetAt( i ) ) )	{
				BeforeRepeat *beforeRepeat = static_cast< BeforeRepeat * > ( this->chart->GetAt( i ) );
				_swprintf( charTemp, L"%d\t%d\t\t\tBeforeRepeat", 
					beforeRepeat->GetMiddlePointX(),
					beforeRepeat->GetMiddlePointY() );
			}
			else if( dynamic_cast < AfterRepeat * > ( this->chart->GetAt( i ) ) )	{
				AfterRepeat *afterRepeat = static_cast< AfterRepeat * > ( this->chart->GetAt( i ) );
				_swprintf( charTemp, L"%d\t%d\t\t\tAfterRepeat", 
					afterRepeat->GetMiddlePointX(),
					afterRepeat->GetMiddlePointY() );
			}
			else if( dynamic_cast < Selection * > ( this->chart->GetAt( i ) ) )	{
				Selection *selection = static_cast< Selection * > ( this->chart->GetAt( i ) );
				_swprintf( charTemp, L"%d\t%d\t\t\tSelection", 
					selection->GetMiddlePointX(),
					selection->GetMiddlePointY() );
			}

			else if( dynamic_cast < SwitchCase * > (this->chart->GetAt( i ) ) )	{
				SwitchCase *switchCase = static_cast< SwitchCase * > ( this->chart->GetAt( i )  );
				_swprintf( charTemp, L"%d\t%d\t%d\t", switchCase->GetSelection()->GetMiddlePointX(),
													  switchCase->GetSelection()->GetMiddlePointY(),
													  switchCase->GetColumnCount() );
				
				for( Long j = 0; j < switchCase->GetColumnCount() + 1; j++ )	{
					wchar_t charCases[ 256 ] = { 0, } ;
					_swprintf( charCases, L"%s,", switchCase->GetCases( j )->GetExpression().c_str() );

					wcscat ( charTemp, charCases );
				}

				wchar_t *charType = L"\tSwitchCase";
				wcscat ( charTemp, charType );
			}
			//*/
			wchar_t *charLine = L"\n";
			wcscat ( charTemp, charLine );
			wcscat ( charSymbol, charTemp );

			fwrite( charSymbol, sizeof( charSymbol ), 1, file );
		}

		fclose( file );
	}

	return this->length;
}

/*
	함수이름 : TransForm
	설    명 : 다중고치다
	입    력 : select, number, pointX, pointY
	출    력 : index
	만 든 이 : 채형석
*/
//다중선택에 따른 다중 구조 변환
Long	Paper::TransForm ( Select * select, Long number, Long pointX, Long pointY ) {
	Long	startPointX ;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;
	
	wstring	expression;

	Long	middlePointX;
	Long	middlePointY;
	Long	index;
	Long	i = 0;
	Long	transX;	// 변경 X 값
	Long	transY;	// 변경 Y 값
	Long	transMiddleX = 0;	// 변경 중간 X 값
	Long	columnCount;

	index = select->GetSelectPaper()->GetSelectedSymbolIndex();
	index = select->GetSelectPaper()->GetAt(index).GetSeletedSymbolIndex();
	startPointX = this->GetAt( index )->GetStartPointX();
	startPointY = this->GetAt( index )->GetStartPointY();
	endPointX = this->GetAt( index )->GetEndPointX();
	endPointY = this->GetAt( index )->GetEndPointY();
	middlePointX = static_cast <Selection *>(this->GetAt(index))->GetMiddlePointX();
	middlePointY = static_cast <Selection *>(this->GetAt(index))->GetMiddlePointY();

	switch ( number ) {

		case 1 :
			transX = pointX - startPointX ;
			transY = pointY - startPointY ;
			break;

		case 2 :
			transY = pointY - startPointY ;
			break;

		case 3 : 
			transX = endPointX - pointX ; 
			transY = pointY - startPointY ;
			break;

		case 4 : 
			transX = endPointX - pointX ; 
			break;
					 
		case 5 : 
			transX = endPointX - pointX ; 
			transY = endPointY - pointY ;;
			break;

		case 6 : 
			if ( dynamic_cast < Selection * >(this->GetAt(index)) ) {
				transY = middlePointY - pointY ;
				transMiddleX = pointX - middlePointX ;
			}
			else {
				transY = endPointY - pointY ;
			}
			break;

		case 7 : 
			transX = pointX - startPointX ;
			transY = endPointY - pointY ;
			break;


		case 8 : 
			transX = pointX - startPointX ;
			break;

		default : break;
	}

	while ( i < select->GetSelectPaper()->GetLength() ) 
	{
		index = select->GetSelectPaper()->GetAt(i).GetSeletedSymbolIndex();

		startPointX = this->GetAt( index )->GetStartPointX();
		startPointY = this->GetAt( index )->GetStartPointY();
		endPointX = this->GetAt( index )->GetEndPointX();
		endPointY = this->GetAt( index )->GetEndPointY();
		middlePointX = static_cast <Selection *>( this->GetAt(index) )->GetMiddlePointX();
		middlePointY = static_cast <Selection *>( this->GetAt(index) )->GetMiddlePointY();
		columnCount = static_cast <SwitchCase *>( this->GetAt(index) )->GetColumnCount();
		Long minimum = ( static_cast <SwitchCase *>(this->GetAt(index))->GetColumnCount() + 2 ) * 25 ;

		switch ( number ) 
		{
			case 1 :
				if ( dynamic_cast <SwitchCase *>(this->GetAt(index)) ) {
					startPointX = startPointX + transX ;
					if ( endPointX -startPointX < minimum ) {
						startPointX = endPointX - minimum ;
					}

					startPointY = startPointY + transY ;
					if ( endPointY - startPointY < 80 ) {
						startPointY = endPointY - 80 ;
					}
				}
				else if ( dynamic_cast <Arrow *>(this->GetAt(index)) ) {
					startPointY = startPointY + transY ;
					if ( endPointY - startPointY < 20 ) {
						startPointY = endPointY - 20 ;
					}
				}
				else {
					startPointX = startPointX + transX ;
					if ( endPointX - startPointX < 40 ) {
						startPointX = endPointX - 40 ;
					}
					startPointY = startPointY + transY ;
					if ( endPointY - startPointY < 40 ) {
						startPointY = endPointY - 40 ;
					}
					if ( dynamic_cast <Selection *>(this->GetAt(index)) ) {
						if ( middlePointX - startPointX <= 20 ) {
							middlePointX = startPointX + 20 ;
						}
						if ( endPointX - middlePointX <= 20 ) {
							middlePointX = endPointX - 20 ;
						}
					}
				}
				break;

			case 2 : 
				if ( dynamic_cast <SwitchCase *>(this->GetAt(index)) ) {
					startPointY = startPointY + transY ;
					if ( endPointY - startPointY < 80 ) {
						startPointY = endPointY - 80 ;
					}
				}
				else if ( dynamic_cast <Arrow *>(this->GetAt(index)) ) {
					startPointY = startPointY + transY ;
					if ( endPointY - startPointY < 20 ) {
						startPointY = endPointY - 20 ;
					}
				}
				else {
					startPointY = startPointY + transY ;
					if ( endPointY - startPointY < 40 ) {
						startPointY = endPointY - 40 ;
					}
				}
				break;

			case 3 : 
				if ( dynamic_cast <SwitchCase *>(this->GetAt(index)) ) {
				
					endPointX = endPointX - transX ;
					if ( endPointX - startPointX < minimum ) {
						endPointX = startPointX + minimum ;
					}
					startPointY = startPointY + transY ;
					if ( endPointY - startPointY < 80 ) {
						startPointY = endPointY - 80 ;
					}
				}
				else if ( dynamic_cast <Arrow *>(this->GetAt(index)) ) {
					startPointY = startPointY + transY ;
					if ( endPointY - startPointY < 20 ) {
						startPointY = endPointY - 20 ;
					}
				}
				else { 
					endPointX = endPointX - transX ;
					if ( endPointX - startPointX < 40 ) {
						endPointX = startPointX + 40 ;
					}
					startPointY = startPointY + transY ;
					if ( endPointY - startPointY < 40 ) {
						startPointY = endPointY - 40 ;
					}
					if ( dynamic_cast <Selection *>(this->GetAt(index)) ) {
						if ( middlePointX - startPointX <= 20 ) {
							middlePointX = startPointX + 20 ;
						}
						if ( endPointX - middlePointX <= 20 ) {
							middlePointX = endPointX - 20 ;
						}
					}
				}
				break;

			case 4 : 
				if ( dynamic_cast <SwitchCase *>(this->GetAt(index)) ) {
					endPointX = endPointX - transX ;
					if ( endPointX -startPointX < minimum ) {
						endPointX = startPointX + minimum ;
					}
				}
				else { 
					endPointX = endPointX - transX ;
					if ( endPointX - startPointX < 40 ) {
						endPointX = startPointX + 40 ;
					}
					if ( dynamic_cast <Selection *>(this->GetAt(index)) ) {
						if ( middlePointX - startPointX <= 20 ) {
							middlePointX = startPointX + 20 ;
						}
						if ( endPointX - middlePointX <= 20 ) {
							middlePointX = endPointX - 20 ;
						}
					}
				}
				break;
					 
			case 5 :
				if ( dynamic_cast <SwitchCase *>(this->GetAt(index)) ) {

					endPointX = endPointX - transX ;
					if ( endPointX -startPointX < minimum ) {
						endPointX = startPointX + minimum ;
					}
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 80 ) {
						endPointY = startPointY + 80 ;
					}
				}
				else if ( dynamic_cast <Arrow *>(this->GetAt(index)) ) {
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 20 ) {
						endPointY = startPointY + 20 ;
					}
				}
				else { 
					endPointX = endPointX - transX ;
					if ( endPointX - startPointX < 40 ) {
						endPointX = startPointX + 40 ;
					}
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 40 ) {
						endPointY = startPointY + 40 ;
					}
					if ( dynamic_cast <Selection *>(this->GetAt(index)) ) {
						if ( middlePointX - startPointX <= 20 ) {
							middlePointX = startPointX + 20 ;
						}
						if ( endPointX - middlePointX <= 20 ) {
							middlePointX = endPointX - 20 ;
						}
						middlePointY = endPointY ;
					}
				}
				break;

			case 6 : 
				if ( dynamic_cast <SwitchCase *>(this->GetAt(index)) ) {
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 80 ) {
						endPointY = startPointY + 80 ;
					}
				}
				else if ( dynamic_cast <Arrow *>(this->GetAt(index)) ) {
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 20 ) {
						endPointY = startPointY + 20 ;
					}
				}
				else if ( dynamic_cast < Selection * >(this->GetAt(index)) ) {
					middlePointX = middlePointX + transMiddleX ;
					if ( middlePointX - startPointX < 20 ) {
						middlePointX = startPointX + 20 ;
					}
					if ( endPointX - middlePointX < 20 ) {
						middlePointX = endPointX - 20 ;
					}
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 40 ) {
						endPointY = startPointY + 40 ;
					}
					middlePointY = endPointY ;
				}
				else {
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 40 ) {
						endPointY = startPointY + 40 ;
					}
					middlePointY = endPointY ;
				}
				break;


			case 7 : 
				if ( dynamic_cast <SwitchCase *>(this->GetAt(index)) ) {
					startPointX = startPointX + transX ;
					if ( endPointX -startPointX < minimum ) {
						startPointX = endPointX - minimum ;
					}
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 80 ) {
						endPointY = startPointY + 80 ;
					}
				}
				else if ( dynamic_cast <Arrow *>(this->GetAt(index)) ) {
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 20 ) {
						endPointY = startPointY + 20 ;
					}
				}
				else {
					startPointX = startPointX + transX ;
					if ( endPointX - startPointX < 40 ) {
						startPointX = endPointX - 40 ;
					}
					endPointY = endPointY - transY ;
					if ( endPointY - startPointY < 40 ) {
						endPointY = startPointY + 40 ;
					}
					if ( dynamic_cast <Selection *>(this->GetAt(index)) ) {
						if ( middlePointX - startPointX <= 20 ) {
							middlePointX = startPointX + 20 ;
						}
						if ( endPointX - middlePointX <= 20 ) {
							middlePointX = endPointX - 20 ;
						}
						middlePointY = endPointY ;
					}
				}
				break;


			case 8 :
				if ( dynamic_cast <SwitchCase *>(this->GetAt(index)) ) {
					startPointX = startPointX + transX ;
					if ( endPointX -startPointX < minimum ) {
						startPointX = endPointX - minimum ;
					}
				}
				else {
					startPointX = startPointX + transX ;
					if ( endPointX - startPointX < 40 ) {
						startPointX = endPointX - 40 ;
					}
					if ( dynamic_cast <Selection *>(this->GetAt(index)) ) {
						if ( middlePointX - startPointX <= 20 ) {
							middlePointX = startPointX + 20 ;
						}
						if ( endPointX - middlePointX <= 20 ) {
							middlePointX = endPointX - 20 ;
						}
					}
				}
				break;

			default : break;
		}
	
		expression = this->GetAt( index )->GetExpression();
		Symbol	*symbol;

		if ( dynamic_cast <Sequence *>(this->GetAt( index ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}

		else if ( dynamic_cast <BeforeRepeat *>( this->GetAt( index ) ) ) {
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}

		else if ( dynamic_cast <AfterRepeat *>( this->GetAt( index ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}

		else if ( dynamic_cast <Selection *>( this->GetAt( index ) ) ) {
			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, 
									 middlePointX, middlePointY, expression );
		}

		else if ( dynamic_cast <SwitchCase *>( this->GetAt( index ) ) ) {
			Long columnCount = static_cast < SwitchCase * >( this->GetAt( index ) )->GetColumnCount() ;
			Long count = static_cast < SwitchCase * >( this->GetAt( index ) )->GetLength();
			wstring	*cases = new wstring[ columnCount + 1];
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( this->GetAt( index ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		else if ( dynamic_cast <Arrow *>(this->GetAt( index ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}


		if ( this->symbols[i] != 0 ) {
			delete[] this->symbols[index] ;	
		}

		this->symbols.Modify( index, symbol );
		i++;
	}

	return index;
}

Long Paper::MoveSymbol( Long symbolIndex, Symbol *movedSymbol ){
	Long index = this->symbols.Modify( symbolIndex, movedSymbol );

	return index;
}

void Paper::DeleteSymbols ( SelectPaper *selectPaper ){
	
	Long	selectedSymbolIndex;
	//Symbol	*symbol;
	Symbol	*deleteSymbol;
	Long	deleteCount = 0;
	Long	j = 0;

	for( Long i = 0; i < selectPaper->GetLength( ); i++ ){

		selectedSymbolIndex = selectPaper->GetAt( i ).GetSeletedSymbolIndex( );
		deleteSymbol = this->symbols.GetAt( selectedSymbolIndex );

		if( deleteSymbol != 0 ){
			delete deleteSymbol;
			this->symbols.Modify( selectedSymbolIndex, 0 );
		}
	}

	while( j < this->length ) {
		
		if( this->GetAt( j - deleteCount ) == 0 ) {

			this->symbols.Delete( j - deleteCount ) ;
			deleteCount++ ;
		}
		j++ ;
	}

	this->capacity = this->capacity - deleteCount ;
	this->length = this->length - deleteCount ;

	selectPaper->ReleaseAllSymbols( );
}



Long Paper::Draw( Long index , Symbol *symbol ){

	Long ret ;

	if( this->length < this->capacity ) {
		ret = this->symbols.Store( index , symbol ) ;
	}
	else{
		ret = this->symbols.AppendFromRear( symbol ) ;
		(this->capacity)++ ;
	}
	(this->length)++ ;

	return ret ;
}

void	Paper::ModifyTo( Symbol *symbol, Long index ) {
	this->symbols.Modify( index, symbol );
}

Long	Paper::MoveTo(Long index, Long upDownSign, Long gap){
	Symbol *symbol = this->symbols.GetAt(index);

	if (upDownSign == 0)
	{

		//아래에 끼는 경우
			//아래에 있는 기호들을 아래로 내린다
		if (dynamic_cast<Sequence*>(symbol))
		{
			Sequence *sequence = static_cast<Sequence*>(symbol);
			Sequence *moveSymbol = new Sequence(
				sequence->GetStartPointX(),
				sequence->GetStartPointY() + gap,
				sequence->GetEndPointX(),
				sequence->GetEndPointY() + gap,

				sequence->GetExpressionStartPointX(),
				sequence->GetExpressionStartPointY() + gap,
				sequence->GetExpressionEndPointX(),
				sequence->GetExpressionEndPointY() + gap,
				sequence->GetExpression()
				);
			delete symbol;
			this->symbols.Modify(index, moveSymbol);
		}
		else if (dynamic_cast<Selection*>(symbol))
		{

			Selection *selection = static_cast<Selection*>(symbol);
			Selection *moveSymbol = new Selection(
				selection->GetStartPointX(),
				selection->GetStartPointY() + gap,
				selection->GetEndPointX(),
				selection->GetEndPointY() + gap,

				selection->GetExpressionStartPointX(),
				selection->GetExpressionStartPointY() + gap,
				selection->GetExpressionEndPointX(),
				selection->GetExpressionEndPointY() + gap,

				selection->GetMiddlePointX(),
				selection->GetMiddlePointY() + gap,

				selection->GetExpression()
			);
			delete symbol;
			this->symbols.Modify(index, moveSymbol);
		}
		else if (dynamic_cast<BeforeRepeat*>(symbol))
		{

			BeforeRepeat *beforeRepeat = static_cast<BeforeRepeat*>(symbol);
			BeforeRepeat *moveSymbol = new BeforeRepeat(
				beforeRepeat->GetStartPointX(),
				beforeRepeat->GetStartPointY() + gap,
				beforeRepeat->GetEndPointX(),
				beforeRepeat->GetEndPointY() + gap,

				beforeRepeat->GetExpressionStartPointX(),
				beforeRepeat->GetExpressionStartPointY() + gap,
				beforeRepeat->GetExpressionEndPointX(),
				beforeRepeat->GetExpressionEndPointY() + gap,

				beforeRepeat->GetMiddlePointX(),
				beforeRepeat->GetMiddlePointY() + gap,

				beforeRepeat->GetExpression()
				);
			delete symbol;
			this->symbols.Modify(index, moveSymbol);
		}
		else if (dynamic_cast<AfterRepeat*>(symbol))
		{

			AfterRepeat *afterRepeat = static_cast<AfterRepeat*>(symbol);
			AfterRepeat *moveSymbol = new AfterRepeat(
				afterRepeat->GetStartPointX(),
				afterRepeat->GetStartPointY() + gap,
				afterRepeat->GetEndPointX(),
				afterRepeat->GetEndPointY() + gap,

				afterRepeat->GetExpressionStartPointX(),
				afterRepeat->GetExpressionStartPointY() + gap,
				afterRepeat->GetExpressionEndPointX(),
				afterRepeat->GetExpressionEndPointY() + gap,

				afterRepeat->GetMiddlePointX(),
				afterRepeat->GetMiddlePointY() + gap,

				afterRepeat->GetExpression()
				);
			delete symbol;
			this->symbols.Modify(index, moveSymbol);
		}
	}

	// 위로 끼우는 경우
		// 위에 있는 기호들을 위로 올린다
	else
	{
		if (dynamic_cast<Sequence*>(symbol))
		{
			Sequence *sequence = static_cast<Sequence*>(symbol);
			Sequence *moveSymbol = new Sequence(
				sequence->GetStartPointX(),
				sequence->GetStartPointY() - gap,
				sequence->GetEndPointX(),
				sequence->GetEndPointY() - gap,

				sequence->GetExpressionStartPointX(),
				sequence->GetExpressionStartPointY() - gap,
				sequence->GetExpressionEndPointX(),
				sequence->GetExpressionEndPointY() - gap,
				sequence->GetExpression()
				);
			delete symbol;
			this->symbols.Modify(index, moveSymbol);
		}
		else if (dynamic_cast<Selection*>(symbol))
		{

			Selection *selection = static_cast<Selection*>(symbol);
			Selection *moveSymbol = new Selection(
				selection->GetStartPointX(),
				selection->GetStartPointY() - gap,
				selection->GetEndPointX(),
				selection->GetEndPointY() - gap,

				selection->GetExpressionStartPointX(),
				selection->GetExpressionStartPointY() - gap,
				selection->GetExpressionEndPointX(),
				selection->GetExpressionEndPointY() - gap,

				selection->GetMiddlePointX(),
				selection->GetMiddlePointY() - gap,

				selection->GetExpression()
				);
			delete symbol;
			this->symbols.Modify(index, moveSymbol);
		}
		else if (dynamic_cast<BeforeRepeat*>(symbol))
		{

			BeforeRepeat *beforeRepeat = static_cast<BeforeRepeat*>(symbol);
			BeforeRepeat *moveSymbol = new BeforeRepeat(
				beforeRepeat->GetStartPointX(),
				beforeRepeat->GetStartPointY() - gap,
				beforeRepeat->GetEndPointX(),
				beforeRepeat->GetEndPointY() - gap,

				beforeRepeat->GetExpressionStartPointX(),
				beforeRepeat->GetExpressionStartPointY() - gap,
				beforeRepeat->GetExpressionEndPointX(),
				beforeRepeat->GetExpressionEndPointY() - gap,

				beforeRepeat->GetMiddlePointX(),
				beforeRepeat->GetMiddlePointY() - gap,

				beforeRepeat->GetExpression()
				);
			delete symbol;
			this->symbols.Modify(index, moveSymbol);
		}
		else if (dynamic_cast<AfterRepeat*>(symbol))
		{

			AfterRepeat *afterRepeat = static_cast<AfterRepeat*>(symbol);
			AfterRepeat *moveSymbol = new AfterRepeat(
				afterRepeat->GetStartPointX(),
				afterRepeat->GetStartPointY() - gap,
				afterRepeat->GetEndPointX(),
				afterRepeat->GetEndPointY() - gap,

				afterRepeat->GetExpressionStartPointX(),
				afterRepeat->GetExpressionStartPointY() - gap,
				afterRepeat->GetExpressionEndPointX(),
				afterRepeat->GetExpressionEndPointY() - gap,

				afterRepeat->GetMiddlePointX(),
				afterRepeat->GetMiddlePointY() - gap,

				afterRepeat->GetExpression()
				);
			delete symbol;
			this->symbols.Modify(index, moveSymbol);
		}

	}
	return index;

}
/*
	함수이름 : CheckType
	설    명 : 종이 위의 기호의 종류를 string으로 출력한다
	입    력 : index
	출    력 : string type
	만 든 이 : 박컴 i5
*/
string	Paper::CheckType( Long index ) {
	string type;

	if( dynamic_cast< Sequence * > ( this->GetAt( index ) ) )	{
		type = "Sequence" ;
	}
	else if( dynamic_cast< BeforeRepeat * > ( this->GetAt( index ) ) )	{
		type = "BeforeRepeat" ;
	}
	else if( dynamic_cast < AfterRepeat * > ( this->GetAt( index ) ) )	{
		type = "AfterRepeat" ;
	}
	else if( dynamic_cast < Selection * > ( this->GetAt( index ) ) )	{
		type = "Selection" ;
				
	}
	else if( dynamic_cast < SwitchCase * > (this->GetAt( index ) ) )	{
		type = "SwitchCase" ;
	}
	if( dynamic_cast< Arrow * > ( this->GetAt( index ) ) )	{
		type = "Arrow" ;
	}
				
	return type ;
}
/*
	함수명:DeleteSymbol
	기능:입력받은 index번째 Symbol을 삭제한다.
	입력:selectedSymbolIndex
	출력:-1
	만든이:곽욱현
*/
Long Paper::DeleteSymbol ( Long selectedSymbolIndex ) {
	Long ret = this->symbols.DeleteModify( selectedSymbolIndex );
	this->length --;

	return ret;
}
/*
	함수명:MakeChart
	기능:종이에서 선택된 기호들을 차트로 옮기고 종이의 기호들을 삭제한다.
	입력:select
	출력:없음
	만든이:곽욱현
*/

void Paper::MakeChart ( Select * select ) {

	select->ReAllocateChart( );
	Symbol *symbol;
	Long selectedSymbolIndex;
	Symbol *chartSymbol ;

	Chart *chart = this->GetChart( );

	for( Long i = select->GetSelectPaper( )->GetLength( ) ; i > 0 ; i-- ){
		selectedSymbolIndex = select->GetSelectPaper( )->GetAt( i -1 ).GetSeletedSymbolIndex( );
		symbol = this->GetAt( selectedSymbolIndex );

		if( dynamic_cast<Sequence*>(symbol) ){
			chartSymbol = new Sequence( *(static_cast<Sequence*>(symbol) ) ) ;
		}
		else if( dynamic_cast<BeforeRepeat*>(symbol) ){
			chartSymbol = new BeforeRepeat( *( static_cast<BeforeRepeat*>(symbol) ) ) ;
		}
		else if( dynamic_cast<AfterRepeat*>(symbol) ){
			chartSymbol = new AfterRepeat( *( static_cast<AfterRepeat*>(symbol) )   ) ;
		}
		else if( dynamic_cast<Selection*>(symbol) ){
			chartSymbol = new Selection( *( static_cast<Selection*>(symbol) ) ) ;
		}
		else if( dynamic_cast<SwitchCase*>(symbol) ){
			chartSymbol = new SwitchCase( *(static_cast<SwitchCase*>(symbol) ) ) ;
		}
		else if( dynamic_cast<Arrow*>(symbol) ){
			chartSymbol = new Arrow( *( static_cast<Arrow*>(symbol) ) ) ;
		}
		
		chart->Paste( chartSymbol );
		this->DeleteSymbol( selectedSymbolIndex );
	}

}
/*
	함수명 : ReleaseChart
	기능 : 차트를 해제하고 종이에 기호들을 추가한다.
	입력 : select
	출력 : 없음
	작성자 : 곽욱현
*/
void Paper::ReleaseChart( Select *select ){

	SelectPaper *selectPaper = select->GetSelectPaper( );
	SelectChart *selectChart = select->GetSelectChart( );
	Chart *chart = this->GetChart( );
	Symbol *symbol;
	Symbol *paperSymbol;

	for ( Long i = 0; i<chart->GetLength( ) ; i++ ) {
		symbol = chart->GetAt( i );
		if( dynamic_cast< Sequence * > ( symbol ) ){
			paperSymbol = new Sequence ( * (static_cast< Sequence * >( symbol ) ) );
		}
		else if( dynamic_cast< BeforeRepeat * > ( symbol ) ){
			paperSymbol = new BeforeRepeat ( * ( static_cast< BeforeRepeat * > ( symbol ) ) );
		}
		else if( dynamic_cast< AfterRepeat * > ( symbol ) ) {
			paperSymbol = new AfterRepeat ( * ( static_cast < AfterRepeat * > ( symbol ) ) );
		}
		else if( dynamic_cast < Selection * > ( symbol ) ) {
			paperSymbol = new Selection ( * ( static_cast < Selection * > ( symbol ) ) );
		}
		else if( dynamic_cast < SwitchCase * > ( symbol ) ) {
			paperSymbol = new SwitchCase ( * ( static_cast < SwitchCase * > ( symbol ) ) );
		}
		else if( dynamic_cast< Arrow * > ( symbol ) ){
			paperSymbol = new Arrow ( * ( static_cast< Arrow * > ( symbol ) ) );
		}
		
		Long index = this->Draw( this->length  , paperSymbol );
		selectPaper->StoreSelectedSymbol( this, index );
	}
	this->GetChart( )->DeleteAllSymbols( );
	select->ReleaseChart( );
}

void Paper::Initialize ( ) {
	for( Long i = 0 ; i < length ; i ++ ) {
		this->symbols.DeleteModify( i ) ;
	}
	this->length = 0;
	this->capacity = MAX;
}


void	Paper::MovePoint( Long sPointX, Long sPointY, Long ePointX, Long ePointY, 
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

Long	Paper::Move ( Select *select, Long sPointX, Long sPointY, Long ePointX, Long ePointY ) {
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

	for ( Long i = 0; i < select->GetSelectPaper()->GetLength(); i++ ) {
		index = select->GetSelectPaper()->GetAt( i ).GetSeletedSymbolIndex();
		startPointX = this->GetAt( index )->GetStartPointX();
		startPointY = this->GetAt( index )->GetStartPointY();
		endPointX = this->GetAt( index )->GetEndPointX();
		endPointY = this->GetAt( index )->GetEndPointY();
		middlePointX = static_cast < Selection * >( this->GetAt( index ) )->GetMiddlePointX();
		middlePointY = static_cast < Selection * >( this->GetAt( index ) )->GetMiddlePointY();
		expression = this->GetAt( index )->GetExpression().c_str();
		columnCount = static_cast < SwitchCase * >( this->GetAt( index ) )->GetColumnCount();

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
		if ( dynamic_cast < Sequence * >( this->GetAt( index ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < BeforeRepeat * >( this->GetAt( index ) ) ) {
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < AfterRepeat * >( this->GetAt( index ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < Selection * >( this->GetAt( index ) ) ) {
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
		else if ( dynamic_cast < SwitchCase * >( this->GetAt( index ) ) ) {
			Long count = static_cast < SwitchCase * >( this->GetAt( index ) )->GetLength();
			wstring	*cases = new wstring[ columnCount + 1];
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( this->GetAt( index ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		else if ( dynamic_cast < Arrow * >( this->GetAt( index ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}		
		oldSymbol = this->GetAt( index );

		index = this->symbols.Modify( index, symbol );

		delete oldSymbol;
	}
	
	
	return index;
}


Long	Paper::MoveKey ( Select *select, Long direction )	{

	Long	startPointX = 0;
	Long	startPointY = 0;
	Long	endPointX = 0;
	Long	endPointY = 0;
	Long	middlePointX = 0;
	Long	middlePointY = 0;
	wstring	expression;
	Long	columnCount;

	Long	index;

	Symbol	*symbol;
	Symbol	*oldSymbol;

	for ( Long i = 0; i < select->GetSelectPaper()->GetLength(); i++ ) {

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

		index = select->GetSelectPaper()->GetAt( i ).GetSeletedSymbolIndex();
		startPointX += this->GetAt( index )->GetStartPointX();
		startPointY += this->GetAt( index )->GetStartPointY();
		endPointX += this->GetAt( index )->GetEndPointX();
		endPointY += this->GetAt( index )->GetEndPointY();
		
		if( dynamic_cast< Selection * > ( this->GetAt( index ) ) )	{
			middlePointX += static_cast < Selection * >( this->GetAt( index ) )->GetMiddlePointX();
			middlePointY += static_cast < Selection * >( this->GetAt( index ) )->GetMiddlePointY();
		}
		else	{
			middlePointX = -1;
			middlePointY = -1;
		}

		expression = this->GetAt( index )->GetExpression().c_str();
		columnCount = static_cast < SwitchCase * >( this->GetAt( index ) )->GetColumnCount();

		if ( dynamic_cast < Sequence * >( this->GetAt( index ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < BeforeRepeat * >( this->GetAt( index ) ) ) {
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < AfterRepeat * >( this->GetAt( index ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < Selection * >( this->GetAt( index ) ) ) {
			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, 
									middlePointX, middlePointY, expression );
		}
		else if ( dynamic_cast < SwitchCase * >( this->GetAt( index ) ) ) {
			Long count = static_cast < SwitchCase * >( this->GetAt( index ) )->GetLength();
			wstring	*cases = new wstring[ columnCount + 1];
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( this->GetAt( index ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		else if ( dynamic_cast < Arrow * >( this->GetAt( index ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}
		
		oldSymbol = this->GetAt( index );

		index = this->symbols.Modify( index, symbol );

		delete oldSymbol;
	}
	return index;
}