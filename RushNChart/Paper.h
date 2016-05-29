#ifndef	_PAPER_H
#define	_PAPER_H
#include "Array.h"
#include "Symbol.h"
#include "Chart.h"
#include < string >
using namespace std ;

typedef	signed long int Long ;

class Select;
class SelectPaper;


class	Paper {
public :
	
	Paper ( ) ; 
	~Paper ( ) ;
	
	Paper ( const	Paper& source ) ;
	Paper ( Long startPointX , Long startPointY , Long endPointX , Long endPointY , Long capacity ) ;
	Paper&	operator = ( const Paper& source ) ;
    
	Long Draw ( Long startPointX , Long startPointY , wstring expression , string type ) ;
	Long Draw ( Long startPointX , Long startPointY , Long endPointX, Long endPointY, wstring expression , string type, Long columnCount ) ;
	Long Draw ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression, string type );

	Long Draw ( Long index, Symbol *symbol );


	Long MoveSymbol( Long symbolIndex, Symbol* movedSymbol );

	void DeleteSymbols ( SelectPaper *selectPaper );


	Long Write( Long Index, wstring expression ) ;

	Long WriteCase( Long symbolIndex, Long caseNumber, Long expressionIndex, wstring expression ) ;

	Long TransForm ( Select * select, Long count, Long pointX, Long pointY );

	Long Correct ( Long symbolIndex, Long correctIndex, wstring expression );
	
	Long Erase ( Long symbolIndex, Long eraseIndex );

	Long EraseCase ( Long symbolIndex, Long caseNumber, Long eraseIndex );

	Long Save ( wchar_t *savePaper ) ;
	Long Load ( wchar_t *loadName ) ;

	void	ModifyTo( Symbol *symbol, Long index );
	Long	MoveTo(Long index, Long upDownSign, Long gap);

	void	MovePoint( Long sPointX, Long sPointY, Long ePointX, Long ePointY, 
						Long *transX, Long *transY, bool *isPointX, bool *isPointY );
	Long	Move ( Select *select, Long sPointX, Long sPointY, Long ePointX, Long ePointY );
	string	CheckType( Long index ) ; 

	Long	MoveKey ( Select *select, Long direction );

	Long	DeleteSymbol ( Long selectedSymbolIndex ) ;

	void	MakeChart ( Select *select );

	void	ReleaseChart ( Select *select );

	void	Initialize ( );

	Symbol* GetAt ( Long index ) const ;
	Long	GetCapacity ( ) const ;
	Long	GetLength ( ) const ;
	Long	GetStartPointX ( ) const ;
	Long	GetStartPointY ( ) const ;
	Long	GetEndPointX ( ) const ;
	Long	GetEndPointY ( ) const ;

	Long	GetAt() const ;

	Chart*	GetChart() const ;

	Long	GetStartIndex() const ;
	Long	GetStopIndex() const ;


private :
	Array < Symbol* > symbols ;
	Chart *chart ;
	Long capacity ;
	Long length ;
	Long startPointX ;
	Long startPointY ;
	Long endPointX ;
	Long endPointY ;

	
} ;

inline	Long	Paper::GetCapacity ( ) const {
	return	this->capacity ;
}
inline	Long	Paper::GetLength ( ) const {
	return	this->length ;
}
inline	Long	Paper::GetStartPointX ( ) const {
	return	this->startPointX ;
}
inline	Long	Paper::GetStartPointY ( ) const {
	return	this->startPointY ;
}
inline	Long	Paper::GetEndPointX ( ) const {
	return	this->endPointX ;
}
inline	Long	Paper::GetEndPointY ( ) const {
	return	this->endPointY ;
}

inline Chart*	Paper::GetChart() const{
	return const_cast<Chart*>(this->chart) ;
}

#endif	//_PAPER_H 