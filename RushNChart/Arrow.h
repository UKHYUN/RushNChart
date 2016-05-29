//Arrow.h
#ifndef	_ARROW_H
#define	_ARROW_H

#include "Symbol.h"
#include <string>
using	namespace std;

typedef signed long int Long;

class Arrow : public Symbol {
	
	public :
		Arrow ();
		Arrow ( Long startPointX, Long startPointY );
		Arrow ( Long startPointX, Long startPointY, Long endPointX, Long endPointY );
		
		virtual	~Arrow ();
		Arrow ( const Arrow&	source );
		Arrow& operator = ( const Arrow&	source );


};

#endif //_SEQUENCE_H