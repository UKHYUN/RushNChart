#ifndef	_CHART_H
#define	_CHART_H
#include	"Array.h"
#include	"Symbol.h"
#include	<string>

using	namespace	std ;

typedef signed long int Long ;

class Select;
class Paper;

class	Chart {
public :
	Chart ( ) ;
	Chart ( const Chart& source ) ;
	Chart ( Long	capacity ) ;
	~Chart ( ) ;
	Chart&	operator = ( const Chart& source ) ;

	Long	Paste ( Symbol	*symbol ) ;
	Long	Detach ( Long symbolIndex ) ;
	Long	MoveSymbol( Long index, Symbol *movedSymbol );
	void	MovePoint( Long sPointX, Long sPointY, Long ePointX, Long ePointY, 
						Long *transX, Long *transY, bool *isPointX, bool *isPointY );
	Long	Move ( Long sPointX, Long sPointY, Long ePointX, Long ePointY );
	Long	MoveKey ( Select *select, Long direction );

	void DeleteAllSymbols( );

	//Long	TransForm ( Select * select, Long number, Long pointX, Long pointY ) ;

	Long	GetCapacity ( ) const ;
	Long	GetLength ( ) const ;
	Symbol*	GetAt ( Long index ) const ;
	

private :
	Array <Symbol*> symbols ;
	Long	capacity ;
	Long	length ;

} ;
inline Symbol* Chart::GetAt( Long index ) const{
	return const_cast<Symbol*>( this->symbols.GetAt( index ) ) ;
}
inline	Long Chart::GetCapacity ( ) const {
	return	capacity ;
}
inline	Long Chart::GetLength ( ) const {
	return	length ;
}

#endif	//_CHART_H