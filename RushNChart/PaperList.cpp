#include "PaperList.h"
#include "Paper.h"
#define MAX 100

PaperList::PaperList( )
	:paperLists( MAX )	{
		this->capacity = MAX ;
		this->length = 0 ;
		this->current= 0 ;
}

PaperList::PaperList( const PaperList& source )
	:paperLists( source.paperLists ){
		this->capacity = source.capacity ; 
		this->length = source.length ;
		this->current = source.current ; 
}

PaperList& PaperList::operator = ( const PaperList& source ) {
	this->paperLists = source.paperLists ;
	this->capacity = source.capacity ;
	this->length = source.length ;
	this->current = source.current ;

	return *this;
}

PaperList::~PaperList( ) {
	Long oldLength = this->length;
	for ( Long i = 0 ; i < oldLength ; i ++ ) {
		this->paperLists.DeleteModify( i );
	}
	this->paperLists.Clear( );
	this->length = 0;
	this->capacity = 0;
	this->current = 0;
}


Paper* PaperList::Undo( ) {
	Paper *undoPaper = this->GetAt( this->current - 1 ) ;

	if( this->current  - 1 > 0 ) {
		current --;
		undoPaper = new Paper ( * ( this->GetAt( current - 1 ) ) ) ;
	}

	return undoPaper ;
}

Paper* PaperList::Redo(  ) {
	Paper *redoPaper = this->GetAt( current - 1 );

	if( this->current + 1 <= this->length ){
		current ++;
		redoPaper = new Paper ( * ( this->GetAt( current - 1 ) ) );
	}
	
	return redoPaper ; 
}

Long PaperList::CaptureLastPaper( Paper *lastPaper ) {
	
	Long oldLength = this->length ;
	Long oldCurrent = this->current ;

	while ( oldCurrent != oldLength && oldCurrent + 1 <= oldLength ) {

		this->paperLists.DeleteModify(  current );
		length --;
		current++;
		oldCurrent ++;
	}

	Paper *storePaper = new Paper ( * ( lastPaper ) );
	this->current = this->length;

	if ( length < capacity ) {
		this->paperLists.Store( current , storePaper ) ; 
	}
	else { 
		this->paperLists.AppendFromRear( storePaper );
		this->capacity ++;
	}
	this->length++;
	this->current++;

	return this->current ;
}

void PaperList::Initialize( ) {
	Long oldLength = this->length;
	
	for( Long i = 0 ; i < oldLength ; i ++ ){
		this->paperLists.DeleteModify( i ) ;
	}

	this->length = 0;
	this->capacity = MAX ;
	this->current = 0;
}