//Selection.h
#ifndef	_SELECTION_H
#define	_SELECTION_H
#include "Symbol.h"
#include <string>
using	namespace std;
typedef signed long int Long;

class	Selection :  public Symbol {

	public :
		Selection ();
		Selection ( Long startPointX, Long startPointY, wstring expression );
		Selection ( Long startPointX, Long startPointY, Long endPointX, Long endPointY );


		Selection ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression );

		Selection ( Long startPointX, Long startPointY, Long endPointX, Long endPointY,
			Long middlePointX, Long middlePointY );

		Selection ( Long startPointX, Long startPointY, Long endPointX, Long endPointY,
			Long middlePointX, Long middlePointY, wstring expression );


		Selection (
                   Long startPointX,
                   Long startPointY,
                   Long endPointX,
                   Long endPointY,
			
                   Long expressionStartpointX,
                   Long expressionStartpointY,
                   Long expressionEndPointX,
                   Long expressionEndPointY,
                   
                   wstring expression );

		Selection (
                   Long startPointX,
                   Long startPointY,

                   Long endPointX,
                   Long endPointY,
			
                   Long expressionStartpointX,
                   Long expressionStartpointY,

                   Long expressionEndPointX,
                   Long expressionEndPointY,
                   
				   Long middlePointX,
				   Long middlePointY,

                   wstring expression );


		Selection ( const Selection& source );
		
		virtual ~Selection ();

		Selection&	operator = ( const Selection& source );

		Long	GetMiddlePointX () const;
		Long	GetMiddlePointY () const;

		//StickingSign
		Long upSign ;
		Long trueSign ;
		Long falseSign ;


	private :
		Long	middlePointX;
		Long	middlePointY;
};

inline	Long	Selection::GetMiddlePointX () const {
	return	this->middlePointX;
}
inline	Long	Selection::GetMiddlePointY () const {
	return	this->middlePointY;
}

#endif //_SELECTION_H
