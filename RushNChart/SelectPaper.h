#ifndef _SELECTPAPER_H
#define _SELECTPAPER_H

typedef signed long int Long;

#include "SelectedSymbol.h"
#include "Array.h"

class Paper;

class SelectPaper{

	public:
		SelectPaper( );
		SelectPaper( const SelectPaper& source );
		~SelectPaper( );
	
		SelectPaper& operator= ( const SelectPaper& source );
		
		Long	CheckSymbol( Paper *paper, Long pointX, Long pointY );
		Long	CheckDuplication( Long selectedSymbolIndex );
		Long	StoreSelectedSymbol ( Paper *paper, Long selectedSymbolIndex );
		Long	StoreSelectedSymbol( Paper *paper );
		Long	Release( Long selectedSymbolIndex );
		Long	CheckSymbols( Paper *paper, Long sPointX, Long sPointY, Long ePointX, Long ePointY );
		void	ReleaseAllSymbols( );
		Long	TransNumber( Paper *paper, Long pointX, Long pointY );
		Long	ReNewSelected( Paper *paper );
		Long	StringCheck( Paper *paper, Long pointX, Long pointY );

		SelectedSymbol& GetAt( Long index ) const;

		Long	GetCapacity( ) const;
		Long	GetLength( ) const;
		Long	GetSelectedSymbolIndex( ) const;

	private :
		Array< SelectedSymbol >	selectedSymbols;
		Long	capacity;
		Long	length;
		Long	selectedSymbolIndex;
};
inline SelectedSymbol& SelectPaper::GetAt( Long index ) const {
	return const_cast<SelectedSymbol&>(this->selectedSymbols.GetAt( index ) );
}
inline Long SelectPaper::GetCapacity( ) const{
	return this->capacity;
}
inline Long SelectPaper::GetLength( ) const{
	return this->length;
}
inline Long SelectPaper::GetSelectedSymbolIndex( ) const{
	return this->selectedSymbolIndex;
}
#endif //_SELECTPAPER_H
