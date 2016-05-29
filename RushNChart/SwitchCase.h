#ifndef _SWITCHCASE_H
#define _SWITCHCASE_H

#include "Symbol.h"
#include "Array.h"

#include <string>
using namespace std ;


class Selection;
class Sequence;


class	SwitchCase : public Symbol {
public :
	SwitchCase ( ) ;
	SwitchCase ( Long columnCount, Long startPointX, Long startPointY, wstring expression ) ;
	SwitchCase ( Long columnCount, Long startPointX, Long startPointY, Long endPointX, Long endPointY,
		wstring expression );
	
	SwitchCase ( Long columnCount, Long startPointX, Long startPointY, Long endPointX, Long endPointY,
		wstring expression, Long middlePointX, Long middlePointY, wstring *( caseExpressions ) );
	
	SwitchCase ( Long columnCount, Long startPointX, Long startPointY, Long endPointX, Long endPointY, 
		wstring expression, Selection *selection, Sequence *( *caseArray ) ) ;
	
	SwitchCase::SwitchCase ( Long columnCount, Long startPointX, Long startPointY, Long endPointX,
		Long endPointY, wstring expression, wstring *( caseExpressions ) );

	SwitchCase ( const SwitchCase& source ) ;
	
	SwitchCase& operator= ( const SwitchCase& source ) ;
		
	~SwitchCase ( ) ;
	
	Long	GetColumnCount ( ) const ;
	//Long	GetMiddlePointX ( ) const ;
	//Long	GetMiddlePointY ( ) const ;

	
	Selection*	GetSelection ( ) const ;
	Sequence*	GetCases ( Long index ) const ;
	

	Long	GetCapacity ( ) const ;
	Long	GetLength ( ) const ;
	

	//StickingSign
	Long upSign ;
	Long falseSign ;

	
private :
	Long	columnCount ;
	//Long	middlePointX ;
	//Long	middlePointY ;

	Selection *selection;
	Array< Sequence * >	cases ;
	
	Long capacity;
	Long length;
} ;

inline	Long SwitchCase::GetColumnCount ( ) const {
	return	this->columnCount ;
}

inline	Selection* SwitchCase::GetSelection ( ) const	{
	return const_cast< Selection * > ( this->selection );
}

inline	Sequence* SwitchCase::GetCases ( Long index ) const	{
	return const_cast< Sequence * > (this->cases.GetAt( index ) );
}

inline	Long SwitchCase::GetCapacity ( ) const	{
	return this->capacity;
}

inline	Long SwitchCase::GetLength ( )	const	{
	return this->length;
}

#endif //_SWITCHCASE_H