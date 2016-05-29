//AfterRepeat.h
#ifndef	_AFTERREPEAT_H
#define	_AFTERREPEAT_H
#include "Symbol.h"
#include <string>
using	namespace std;
typedef signed long int Long;

class	AfterRepeat :  public Symbol {

	public :
		AfterRepeat ();
		AfterRepeat ( Long startPointX, Long startPointY, wstring expression );
		AfterRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY );
		AfterRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression );
		AfterRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, Long middlePointX, Long middlePoint );
		AfterRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, Long middlePointX, Long middlePointY, wstring expression );
		
		AfterRepeat ( const AfterRepeat& source );
		AfterRepeat (
                     Long startPointX,
                     Long startPointY,
                     Long endPointX,
                     Long endPointY,
			
                     Long expressionStartpointX,
                     Long expressionStartpointY,
                     Long expressionEndPointX,
                     Long expressionEndPointY,
                     
                     wstring expression );

		AfterRepeat( 
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

		virtual ~AfterRepeat ();
		AfterRepeat&	operator = ( const AfterRepeat& source );
		Long	GetMiddlePointX () const;
		Long	GetMiddlePointY () const;

		//StickingSign
		Long upSign ;
		Long inSign ;
		Long downSign ;


	private :
		Long	middlePointX;
		Long	middlePointY;
};

inline	Long	AfterRepeat::GetMiddlePointX () const {
	return	this->middlePointX;
}
inline	Long	AfterRepeat::GetMiddlePointY () const {
	return	this->middlePointY;
}

#endif //_AFTERREPEAT_H