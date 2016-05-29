#include "SwitchCase.h"
#include "Selection.h"
#include "Sequence.h"

SwitchCase::SwitchCase( )
: Symbol( ), selection( ), cases( 10 )	{

	this->columnCount = 0 ;
	this->capacity = 10;
	this->length = 0;
}

SwitchCase::SwitchCase ( Long columnCount, Long startPointX, Long startPointY, wstring expression )
	: Symbol( startPointX, startPointY, expression ), cases( columnCount + 1 )	{
	
	this->columnCount = columnCount ;
	this->capacity = columnCount + 1 ;
	this->length = 0 ;

	this->endPointX = this->startPointX+280;
	this->endPointY = this->startPointY+80;

	Long selectionEndPointX = this->endPointX ;
	Long selectionEndPointY = this->startPointY + 40 ;
	Long width = ( this->endPointX - this->startPointX ) / ( this->columnCount + 2 ) ;
	Long selectionMiddlePointX = selectionEndPointX - width;
	Long selectionMiddlePointY = selectionEndPointY ;

	Long selectionExpressionStartPointX = startPointX + ( ( selectionMiddlePointX - startPointX ) / 2 );
	Long selectionExpressionStartPointY = startPointY + - 2;
	Long selectionExpressionEndPointX = selectionMiddlePointX + width / 2 ;
	Long selectionExpressionEndPointY = startPointY + 22;

	this->selection = new Selection ( startPointX, startPointY, selectionEndPointX, selectionEndPointY,
		selectionExpressionStartPointX, selectionExpressionStartPointY, selectionExpressionEndPointX,
		selectionExpressionEndPointY, selectionMiddlePointX, selectionMiddlePointY, expression );

	this->expressionStartPointX = this->selection->GetExpressionStartPointX();
	this->expressionStartPointY = this->selection->GetExpressionStartPointY();
	this->expressionEndPointX = this->selection->GetExpressionEndPointX();
	this->expressionEndPointY = this->selection->GetExpressionEndPointY();

	for ( Long i = 0; i < ( columnCount + 1 ); i++ )	{
		wstring caseExpression;
		
		if ( i < columnCount )	{
			caseExpression = to_wstring((long long)(i+1));
		}
		else	{
			caseExpression = L"default";
		}

		Long caseStartPointX ;
		Long caseStartPointY = endPointY;

		if ( i > 0 )	{
			caseStartPointX = this->cases.GetAt( i - 1 )->GetEndPointX() ;
		}
		else	{
			caseStartPointX = startPointX;
		}

		Long caseEndPointX = caseStartPointX + ( ( selectionMiddlePointX - startPointX) / ( columnCount + 1 ) ) ;

		Sequence *tempCase = new Sequence ( caseStartPointX, selectionMiddlePointY, caseEndPointX, endPointY,
			caseExpression );

		if ( this->length < this->capacity )	{
			this->cases.Store ( i, tempCase );
		}
		else if ( this->length >= this->capacity )	{
			this->cases.AppendFromRear ( tempCase );
			this->capacity++;
		}

		this->length++;
	}
	this->upSign = -1 ;
	this->falseSign = -1 ;
}

SwitchCase::SwitchCase ( Long columnCount, Long startPointX, Long startPointY, Long endPointX, Long endPointY,
	wstring expression )
	: Symbol ( startPointX, startPointY, endPointX, endPointY, expression ), cases ( columnCount + 1 )	{
		
		this->columnCount = columnCount;
		this->capacity = columnCount + 1;
		this->length = 0;

		Long selectionEndPointX = this->endPointX ;
		Long selectionEndPointY ;
		if ( endPointY - startPointY >= 80 ) {
			selectionEndPointY = this->startPointY + 80 ;
		}
		else {
			selectionEndPointY = startPointY + ( endPointY - startPointY ) / 2 ;
		}
		Long width = ( this->endPointX-this->startPointX ) / ( this->columnCount + 2 ) ;
		Long selectionMiddlePointX = selectionEndPointX - width ;
		Long selectionMiddlePointY = selectionEndPointY ;

		this->selection = new Selection ( startPointX, startPointY, selectionEndPointX, selectionEndPointY,
			selectionMiddlePointX, selectionMiddlePointY, expression );

		this->expressionStartPointX = this->selection->GetExpressionStartPointX();
		this->expressionStartPointY = this->selection->GetExpressionStartPointY();
		this->expressionEndPointX = this->selection->GetExpressionEndPointX();
		this->expressionEndPointY = this->selection->GetExpressionEndPointY();

		for ( Long i = 0; i < ( columnCount + 1 ); i++ )	{
			wstring caseExpression;

			if ( i < columnCount )	{
				caseExpression = to_wstring((long long)(i+1));
			}
			else	{
				caseExpression = L"default";
			}

			Long caseStartPointX ;
			Long caseStartPointY = endPointY;

			if ( i > 0 )	{
				caseStartPointX = this->cases.GetAt( i - 1 )->GetEndPointX() ;
			}
			else	{
				caseStartPointX = startPointX;
			}

			Long caseEndPointX = caseStartPointX + ( ( selectionMiddlePointX - startPointX) / ( columnCount + 1 ) ) ;

			Sequence *tempCase = new Sequence ( caseStartPointX, selectionMiddlePointY, caseEndPointX, endPointY,
				caseExpression );

			if ( this->length < this->capacity )	{
				this->cases.Store ( i, tempCase );
			}
			else if ( this->length >= this->capacity )	{
				this->cases.AppendFromRear ( tempCase );
				this->capacity++;
			}

			this->length++;
		}
		this->upSign = -1 ;
		this->falseSign = -1 ;
}

SwitchCase::SwitchCase ( Long columnCount, Long startPointX, Long startPointY, Long endPointX,
	Long endPointY, wstring expression, Long middlePointX, Long middlePointY, wstring *( caseExpressions ) )
: Symbol( startPointX, startPointY, endPointX, endPointY, expression ), cases( columnCount + 1 )	{
	
	this->columnCount = columnCount;
	this->capacity = columnCount + 1;
	this->length = 0;

	Long selectionEndPointX = endPointX;
	Long selectionEndPointY = middlePointY;
	Long selectionMiddlePointX = middlePointX;
	Long selectionMiddlePointY = middlePointY;

	this->selection = new Selection ( startPointX, startPointY, selectionEndPointX, selectionEndPointY,
		selectionMiddlePointX, selectionMiddlePointY, expression );

	this->expressionStartPointX = this->selection->GetExpressionStartPointX();
	this->expressionStartPointY = this->selection->GetExpressionStartPointY();
	this->expressionEndPointX = this->selection->GetExpressionEndPointX();
	this->expressionEndPointY = this->selection->GetExpressionEndPointY();

	for ( Long i = 0; i < ( columnCount + 1 ); i++ )	{
		wstring caseExpression = caseExpressions [ i ];

		Long caseStartPointX ;
		Long caseStartPointY = endPointY;

		if ( i > 0 )	{
			caseStartPointX = this->cases.GetAt( i - 1 )->GetEndPointX() ;
		}
		else	{
			caseStartPointX = startPointX;
		}

		Long caseEndPointX = caseStartPointX + ( ( selectionMiddlePointX - startPointX) / ( columnCount + 1 ) ) ;

		Sequence *tempCase = new Sequence ( caseStartPointX, selectionMiddlePointY, caseEndPointX, endPointY,
			caseExpression );

		if ( this->length < this->capacity )	{
			this->cases.Store ( i, tempCase );
		}
		else if ( this->length >= this->capacity )	{
			this->cases.AppendFromRear ( tempCase );
			this->capacity++;
		}

		this->length++;
	}
	this->upSign = -1 ;
	this->falseSign = -1 ;
}

SwitchCase::SwitchCase ( Long columnCount, Long startPointX, Long startPointY, Long endPointX,
	Long endPointY, wstring expression, wstring *( caseExpressions ) )
: Symbol( startPointX, startPointY, endPointX, endPointY, expression ), cases( columnCount + 1 )	{
	
	this->columnCount = columnCount;
	this->capacity = columnCount + 1;
	this->length = 0;

	Long selectionEndPointX = endPointX;
	Long selectionEndPointY;
	if ( endPointY - startPointY >= 120 ) {
		selectionEndPointY = startPointY + 80 ;
	}
	else {
		selectionEndPointY = endPointY - 40 ;
	}
	
	Long width = ( this->endPointX-this->startPointX ) / ( this->columnCount + 2 ) ;
	Long selectionMiddlePointX = selectionEndPointX - width;

	Long selectionMiddlePointY = selectionEndPointY ;

	this->selection = new Selection ( startPointX, startPointY, selectionEndPointX, selectionEndPointY,
		selectionMiddlePointX, selectionMiddlePointY, expression );

	this->expressionStartPointX = this->selection->GetExpressionStartPointX();
	this->expressionStartPointY = this->selection->GetExpressionStartPointY();
	this->expressionEndPointX = this->selection->GetExpressionEndPointX();
	this->expressionEndPointY = this->selection->GetExpressionEndPointY();

	for ( Long i = 0; i < ( columnCount + 1 ); i++ )	{
		wstring caseExpression = caseExpressions [ i ];

		Long caseStartPointX ;
		Long caseStartPointY = endPointY;

		if ( i > 0 )	{
			caseStartPointX = this->cases.GetAt( i - 1 )->GetEndPointX() ;
		}
		else	{
			caseStartPointX = startPointX;
		}

		Long caseEndPointX = caseStartPointX + ( ( selectionMiddlePointX - startPointX) / ( columnCount + 1 ) ) ;

		Sequence *tempCase = new Sequence ( caseStartPointX, selectionMiddlePointY, caseEndPointX, endPointY,
			caseExpression );

		if ( this->length < this->capacity )	{
			this->cases.Store ( i, tempCase );
		}
		else if ( this->length >= this->capacity )	{
			this->cases.AppendFromRear ( tempCase );
			this->capacity++;
		}

		this->length++;
	}
	this->upSign = -1 ;
	this->falseSign = -1 ;
}


SwitchCase::SwitchCase ( Long columnCount, Long startPointX, Long startPointY, Long endPointX, Long endPointY,
	wstring expression, Selection *selection, Sequence *( *caseArray ) )
	: Symbol ( startPointX, startPointY, endPointX, endPointY, expression ), cases ( columnCount + 1 )	{
	
	this->columnCount = columnCount;

	this->selection = new Selection ( *selection );

	this->capacity = columnCount + 1;
	this->length = 0;

	this->expressionStartPointX = this->selection->GetExpressionStartPointX();
	this->expressionStartPointY = this->selection->GetExpressionStartPointY();
	this->expressionEndPointX = this->selection->GetExpressionEndPointX();
	this->expressionEndPointY = this->selection->GetExpressionEndPointY();

	for ( Long i = 0; i < ( this->columnCount + 1 ); i++ )	{
		if ( i < this->cases.GetCapacity() )	{
			this->cases.Store( i, caseArray [ i ] );
		}
		else	{
			this->cases.AppendFromRear( caseArray [ i ] );
			this->capacity++;
		}

		this->length++;
	}
	this->upSign = -1 ;
	this->falseSign = -1 ;
}

SwitchCase::SwitchCase ( const SwitchCase& source )
	: Symbol ( source.startPointX, source.startPointY, source.endPointX, source.endPointY,
	source.expressionStartPointX, source.expressionStartPointY, source.expressionEndPointX, source.expressionEndPointY, source.expression )	{
	this->columnCount = source.columnCount;

	this->selection = new Selection ( *source.selection );

	for ( Long i = 0; i < source.length; i++ )	{
		Sequence *tempCase = new Sequence ( * ( source.GetCases ( i ) ) );
		this->cases.Store( i, tempCase );
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->upSign = -1 ;
	this->falseSign = -1 ;
}

SwitchCase& SwitchCase::operator= ( const SwitchCase& source )	{
	
	if ( this->selection != 0 )	{
		delete selection;
	}

	this->cases.Clear();

	this->columnCount = source.columnCount;
	this->selection = new Selection ( source.selection->GetStartPointX(), source.selection->GetStartPointY(), source.selection->GetEndPointX(), source.selection->GetEndPointY(),
		source.selection->GetExpression() );

	this->startPointX = this->selection->GetStartPointX();
	this->startPointY = this->selection->GetStartPointY();
	this->endPointX = this->selection->GetEndPointX();
	this->endPointY = this->selection->GetEndPointY();

	this->expressionStartPointX = this->selection->GetExpressionStartPointX();
	this->expressionStartPointY = this->selection->GetExpressionStartPointY();
	this->expressionEndPointX = this->selection->GetExpressionEndPointX();
	this->expressionEndPointY = this->selection->GetExpressionEndPointY();

	//this->cases = new Sequence [ source.capacity ]; 
	for ( Long i = 0; i < source.length; i++ )	{
		Sequence *tempCase = new Sequence ( * ( source.GetCases ( i ) ) );
		this->cases.Store ( i, tempCase );
	}

	this->capacity = source.capacity;
	this->length = source.length;

	this->upSign = source.upSign ;
	this->falseSign = source.falseSign ;

	return *this;

}

SwitchCase::~SwitchCase ( )	{
	if ( this->selection != 0 )	{
		delete this->selection;
	}

	for ( Long i = 0; i < this->length; i++ )	{
		Sequence *sequence = this->cases.GetAt ( i );

		if ( sequence != 0 )	{
			delete sequence;
		}
	}
}