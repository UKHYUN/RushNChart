//Copy.h

#ifndef _COPYSYMBOL_H
#define	_COPYSYMBOL_H
#include "Array.h"
#include "Symbol.h"
#include < string >

using namespace std ;

typedef	signed long int Long ;

class	Select;
class	Paper;

class	CopySymbol {

	public :

		CopySymbol ( ) ; 
		CopySymbol ( const CopySymbol&	source );
		~CopySymbol ( ) ;

		CopySymbol&	operator = ( const CopySymbol& source );

		Long	CopySymbols ( Select *select, Paper *paper );
		Long	PasteSymbols ( Select *select, Paper *paper );
		Long	CutSymbols ( Select *select, Paper *paper );


		Long	GetCapacity ( ) const ;
		Long	GetLength ( ) const ;

		Symbol* GetAt ( Long index ) const ;

	private :

		Array < Symbol* > symbols ;
		Long	capacity;
		Long	length;

};

inline Long CopySymbol::GetCapacity( ) const{
	return this->capacity;
}
inline Long CopySymbol::GetLength( ) const{
	return this->length;
}

#endif //_COPYSYMBOL_H