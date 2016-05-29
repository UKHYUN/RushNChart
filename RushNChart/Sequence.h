//Sequence.h
#ifndef	_SEQUENCE_H
#define	_SEQUENCE_H
#include <string>
#include "Symbol.h"
using namespace std;

typedef signed long int Long;

class Sequence : public Symbol {
	
	public :
		Sequence ();
		Sequence ( Long startPointX, Long startPointY, wstring expression );
		Sequence ( Long startPointX, Long startPointY, Long endPointX, Long endPointY );
		Sequence ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression );
		Sequence (
                  Long startPointX,
                  Long startPointY,
                  Long endPointX,
                  Long endPointY,
                  
                  Long expressionStartpointX,
                  Long expressionStartpointY, 
                  Long expressionEndPointX,
                  Long expressionEndPointY,
                  
                  wstring expression );
		
		virtual	~Sequence ();
		Sequence ( const Sequence&	source );
		Sequence& operator = ( const Sequence&	source );


		//StickingSign
		Long upSign;
		Long downSign;


};



#endif //_SEQUENCE_H