#ifndef _PAPERLIST_H
#define _PAPERLIST_H

#include "Array.h"

typedef signed long int Long;

class Paper;

class PaperList {
public:
	
	PaperList ( );
	PaperList ( const PaperList& source ) ;
	PaperList& operator = ( const PaperList& source ) ;
	~PaperList( ) ;

	Paper* Undo(  );
	Paper* Redo(  );
	Long CaptureLastPaper( Paper *paper );
	void Initialize( );

	Paper* GetAt( Long index ) const;
	Long GetCapacity( ) const ;
	Long GetLength( ) const;
	Long GetCurrent( ) const ;

private :
	Array < Paper * > paperLists;
	Long capacity;
	Long length;
	Long current;
};

inline Paper* PaperList::GetAt( Long index ) const {
	return const_cast< Paper* >( this->paperLists.GetAt( index ) ) ;
}

inline Long PaperList::GetCapacity( ) const {
	return this->capacity;
}

inline Long PaperList::GetLength( ) const {
	return this->length;
}

inline Long PaperList::GetCurrent( ) const {
	return this->current;
}

#endif //_PAPERLIST_H
