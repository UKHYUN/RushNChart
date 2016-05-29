
// 만든이 : 채 형 석
/*
	프로젝트명 : Rush & Chart
	파  일  명 : CopySymbol.cpp
	작  성  일 : 2014년 06월 18일
	팀      명 : i5(five)
	팀      원 : 안영보 ( 팀장 ), 채형석, 김지수, 고요셉(작가), 곽욱현 
*/
#include "CopySymbol.h"
#include "Paper.h"
#include "Chart.h"

#include "Symbol.h"
#include "Selection.h"
#include "Sequence.h"
#include "AfterRepeat.h"
#include "BeforeRepeat.h"
#include "SwitchCase.h"
#include "Arrow.h"

#include "Select.h"
#include "SelectChart.h"
#include "SelectPaper.h"
#include "SelectedSymbol.h"

#define MAX 100

CopySymbol::CopySymbol ()
	: symbols ( MAX ) {
		this->capacity = MAX;
		this->length = 0;;
}

CopySymbol::~CopySymbol () {

}

CopySymbol::CopySymbol (const CopySymbol& source )
	: symbols ( source.capacity ) {
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
			else if ( dynamic_cast < SwitchCase *> ( temp ) ) {
				symbol = new SwitchCase ( *( SwitchCase * ) temp );
			}
			if( dynamic_cast< Arrow * >( temp ) )	{
				symbol = new Arrow( *( Arrow * ) temp );
			}
			
			this->symbols.Store( i, symbol );
		}

		this->capacity = source.capacity;
		this->length = source.length;
}

CopySymbol&	CopySymbol::operator= ( const CopySymbol& source ) {
	this->symbols.Clear ( ) ;
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
		else if ( dynamic_cast < SwitchCase *> ( temp ) ) {
				symbol = new SwitchCase ( *( SwitchCase * ) temp );
		}
		if( dynamic_cast< Arrow * >( temp ) )	{
			symbol = new Arrow( *( Arrow * ) temp );
		}			
		this->symbols.Store( i, symbol );
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Symbol* CopySymbol::GetAt( Long index ) const{

	return const_cast< Symbol* >(this->symbols.GetAt( index ) );
}

/*
	함수이름 : CopySymbols
	설    명 : 선택한 기호를 복사하다
	입    력 : select, Paper
	출    력 : index
	만 든 이 : 채형석
*/
Long	CopySymbol::CopySymbols ( Select *select, Paper *paper ) {
	Long	startPointX;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;
	Long	middlePointX;
	Long	middlePointY;
	Long	index;
	Symbol	*symbol;
	Long	i = 0;
	wstring	expression;
	// 복사되어 있는 기호를 초기화 하다
	if ( this->length != 0) {
		this->symbols.Clear();
		this->capacity = 0;
		this->length = 0;
	}
	// 선택된 종이를 복사 한다.
	while ( i < select->GetSelectPaper()->GetLength() ) {
		index = select->GetSelectPaper()->GetAt( i ).GetSeletedSymbolIndex();
		startPointX = paper->GetAt( index )->GetStartPointX() + 30;
		startPointY = paper->GetAt( index )->GetStartPointY() + 30;
		endPointX = paper->GetAt( index )->GetEndPointX() + 30;
		endPointY = paper->GetAt( index )->GetEndPointY() + 30;
		expression = paper->GetAt( index )->GetExpression();

		if ( dynamic_cast <Sequence *>( paper->GetAt( index ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast <BeforeRepeat *>( paper->GetAt( index ) ) ) {										////////////////////////
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast <AfterRepeat *>( paper->GetAt( index ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast <Selection *>( paper->GetAt( index ) ) ) {
			middlePointX = static_cast <Selection *>( paper->GetAt( index ))->GetMiddlePointX() + 30;
			middlePointY = static_cast <Selection *>( paper->GetAt( index ))->GetMiddlePointY() + 30;

			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, middlePointX, middlePointY, expression );
		}

		else if ( dynamic_cast <SwitchCase *>( paper->GetAt( index ) ) ) {
			Long	columnCount = static_cast < SwitchCase * >( paper->GetAt( index ) )->GetColumnCount( );
			wstring	*cases = new wstring[7];
			Long count = static_cast < SwitchCase * >( paper->GetAt( index ) )->GetLength();
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( paper->GetAt( index ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		if ( dynamic_cast <Arrow *>( paper->GetAt( index ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}

		if ( this->length < this->capacity ) {
			this->symbols.Store( i, symbol );
		}
		else {
			this->symbols.AppendFromRear( symbol );
			this->capacity++;
		}
		this->length++;
		i++;
	}
	i = 0;

	// 선택된 차트를 복사하다.
	while ( i < paper->GetChart( )->GetLength() ) {
		startPointX = paper->GetChart()->GetAt( i )->GetStartPointX() + 30;
		startPointY = paper->GetChart()->GetAt( i )->GetStartPointY() + 30;
		endPointX = paper->GetChart()->GetAt( i )->GetEndPointX() + 30;
		endPointY = paper->GetChart()->GetAt( i )->GetEndPointY() + 30;
		expression = paper->GetChart()->GetAt( i )->GetExpression();

		if ( dynamic_cast <Sequence *>( paper->GetChart()->GetAt( i ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		
		else if ( dynamic_cast <BeforeRepeat *>( paper->GetChart()->GetAt( i ) ) ) {									/////////////////////////////
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}

		else if ( dynamic_cast <AfterRepeat *>( paper->GetChart()->GetAt( i ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}

		else if ( dynamic_cast <Selection *>( paper->GetChart()->GetAt( i ) ) ) {
			middlePointX = static_cast <Selection *>( paper->GetChart()->GetAt( i ))->GetMiddlePointX() + 30;
			middlePointY = static_cast <Selection *>( paper->GetChart()->GetAt( i ))->GetMiddlePointY() + 30;

			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, middlePointX, middlePointY, expression );
		}

		else if ( dynamic_cast <SwitchCase *>( paper->GetChart()->GetAt( i ) ) ) {
			Long	columnCount = static_cast < SwitchCase * >( paper->GetChart()->GetAt( i ) )->GetColumnCount( );
			wstring	*cases = new wstring[7];
			Long count = static_cast < SwitchCase * >( paper->GetChart()->GetAt( i ) )->GetLength();
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( paper->GetChart()->GetAt( i ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		else if ( dynamic_cast <Arrow *>( paper->GetChart()->GetAt( i ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}

		if ( this->length < this->capacity ) {
			this->symbols.Store( i, symbol );
		}
		else {
			this->symbols.AppendFromRear( symbol );
			this->capacity++;
		}
		this->length++;
		i++;
	}


	return this->length;
}


/*
	함수이름 : PasteSymbols
	설    명 : 선택한 기호를 붙여넣다.
	입    력 : select, Paper
	출    력 : index
	만 든 이 : 채형석
*/
Long	CopySymbol::PasteSymbols ( Select *select, Paper *paper ) {
	Long	startPointX;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;
	Long	middlePointX;
	Long	middlePointY;
	Long	index;
	Symbol	*symbol;
	Long	i = 0;
	wstring	expression;

	// 선택되어 있는 기호를 초기화 한다.
	if ( select->GetSelectChart( ) != 0 ) {
		select->ReleaseChart( );
	}
	if ( select->GetSelectPaper()->GetLength() > 0 ) {
		select->GetSelectPaper()->ReleaseAllSymbols();
	}
	// 복사되어 있는 기호를 종이에 다시 넣는다.
	while ( i < this->length ) {
		startPointX = this->GetAt( i )->GetStartPointX();
		startPointY = this->GetAt( i )->GetStartPointY();
		endPointX = this->GetAt( i )->GetEndPointX();
		endPointY = this->GetAt( i )->GetEndPointY();
		expression = this->GetAt( i )->GetExpression();

		if ( dynamic_cast < Sequence * >( this->GetAt( i ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < BeforeRepeat * >( this->GetAt( i ) ) ) {															/////////////////////
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < AfterRepeat * >( this->GetAt( i ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast < Selection * >( this->GetAt( i ) ) ) {
			middlePointX = static_cast < Selection * >( this->GetAt( i ) )->GetMiddlePointX();
			middlePointY = static_cast < Selection * >( this->GetAt( i ) )->GetMiddlePointY();

			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, middlePointX, middlePointY, expression );
		}
		else if ( dynamic_cast <SwitchCase *>( this->GetAt( i ) ) ) {
			Long	columnCount = static_cast < SwitchCase * >( this->GetAt( i ) )->GetColumnCount( );
			wstring	*cases = new wstring[7];
			Long count = static_cast < SwitchCase * >( this->GetAt( i ) )->GetLength();
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( this->GetAt( i ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		else if ( dynamic_cast < Arrow * >( this->GetAt( i ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}

		index = paper->Draw( paper->GetLength(), symbol );
		// 다시 넣은 기호를 선택한다.
		select->GetSelectPaper()->StoreSelectedSymbol( paper, index );

		i++;
	}

	return paper->GetLength();
}

/*
	함수이름 : CutSymbols
	설    명 : 선택한 기호를 붙여넣다.
	입    력 : select, Paper
	출    력 : index
	만 든 이 : 채형석
*/
Long	CopySymbol::CutSymbols ( Select *select, Paper *paper ) {
	Long	startPointX;
	Long	startPointY;
	Long	endPointX;
	Long	endPointY;
	Long	middlePointX;
	Long	middlePointY;
	Long	index;
	Symbol	*symbol;
	Long	i = 0;
	wstring	expression;
	// 복사되어 있는 기호를 초기화 한다.
	if ( this->length != 0) {
		this->symbols.Clear();
		this->capacity = 0;
		this->length = 0;
	}
	// 종이에 선택되어 있는 기호를 잘라낸다.
	while ( i < select->GetSelectPaper()->GetLength() ) {
		index = select->GetSelectPaper()->GetAt( i ).GetSeletedSymbolIndex();
		startPointX = paper->GetAt( index )->GetStartPointX() ;
		startPointY = paper->GetAt( index )->GetStartPointY() ;
		endPointX = paper->GetAt( index )->GetEndPointX() ;
		endPointY = paper->GetAt( index )->GetEndPointY() ;
		expression = paper->GetAt( index )->GetExpression();

		if ( dynamic_cast <Sequence *>( paper->GetAt( index ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast <BeforeRepeat *>( paper->GetAt( index ) ) ) {														//////////////////////
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast <AfterRepeat *>( paper->GetAt( index ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast <Selection *>( paper->GetAt( index ) ) ) {
			middlePointX = static_cast <Selection *>( paper->GetAt( index ))->GetMiddlePointX() ;
			middlePointY = static_cast <Selection *>( paper->GetAt( index ))->GetMiddlePointY() ;

			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, middlePointX, middlePointY, expression );
		}

		else if ( dynamic_cast <SwitchCase *>( paper->GetAt( index ) ) ) {
			Long	columnCount = static_cast < SwitchCase * >( paper->GetAt( index ) )->GetColumnCount( );
			wstring	*cases = new wstring[7];
			Long count = static_cast < SwitchCase * >( paper->GetAt( index ) )->GetLength();
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( paper->GetAt( index ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		else if ( dynamic_cast <Arrow *>( paper->GetAt( index ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}

		if ( this->length < this->capacity ) {
			this->symbols.Store( i, symbol );
		}
		else {
			this->symbols.AppendFromRear( symbol );
			this->capacity++;
		}
		this->length++;
		i++;
	}
	i = 0;

	// 차트에 선택되어있는 기호를 잘라낸다.
	while ( i < paper->GetChart( )->GetLength() ) {
		startPointX = paper->GetChart()->GetAt( i )->GetStartPointX() ;
		startPointY = paper->GetChart()->GetAt( i )->GetStartPointY() ;
		endPointX = paper->GetChart()->GetAt( i )->GetEndPointX() ;
		endPointY = paper->GetChart()->GetAt( i )->GetEndPointY() ;
		expression = paper->GetChart()->GetAt( i )->GetExpression();

		if ( dynamic_cast <Sequence *>( paper->GetChart()->GetAt( index ) ) ) {
			symbol = new Sequence ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast <BeforeRepeat *>( paper->GetChart()->GetAt( index ) ) ) {									/////////////////////
			symbol = new BeforeRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast <AfterRepeat *>( paper->GetChart()->GetAt( index ) ) ) {
			symbol = new AfterRepeat ( startPointX, startPointY, endPointX, endPointY, expression );
		}
		else if ( dynamic_cast <Selection *>( paper->GetChart()->GetAt( index ) ) ) {
			middlePointX = static_cast <Selection *>( paper->GetChart()->GetAt( index ))->GetMiddlePointX();
			middlePointY = static_cast <Selection *>( paper->GetChart()->GetAt( index ))->GetMiddlePointY();

			symbol = new Selection ( startPointX, startPointY, endPointX, endPointY, middlePointX, middlePointY, expression );
		}

		else if ( dynamic_cast <SwitchCase *>( paper->GetChart()->GetAt( index ) ) ) {
			Long	columnCount = static_cast < SwitchCase * >( paper->GetChart()->GetAt( index ) )->GetColumnCount( );
			wstring	*cases = new wstring[7];
			Long count = static_cast < SwitchCase * >( paper->GetChart()->GetAt( index ) )->GetLength();
			
			for ( Long j = 0; j < count; j++ ) {
				cases[j] = static_cast < SwitchCase * >( paper->GetChart()->GetAt( index ) )->GetCases( j )->GetExpression();
			}
			symbol = new SwitchCase ( columnCount, startPointX, startPointY, endPointX, endPointY, expression, cases );
		}
		else if ( dynamic_cast <Arrow *>( paper->GetChart()->GetAt( index ) ) ) {
			symbol = new Arrow ( startPointX, startPointY, endPointX, endPointY );
		}

		if ( this->length < this->capacity ) {
			this->symbols.Store( i, symbol );
		}
		else {
			this->symbols.AppendFromRear( symbol );
			this->capacity++;
		}
		this->length++;
		i++;
	}
	if ( select->GetSelectPaper()->GetLength() != 0 ) {
		paper->DeleteSymbols( select->GetSelectPaper() );
	}
	if ( select->IsChartSelected( ) == true ) {
		paper->GetChart()->DeleteAllSymbols( );
	}

	return this->length;
}