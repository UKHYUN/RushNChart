//BeforeRepeat.h
#ifndef	_BEFOREREPEAT_H
#define	_BEFOREREPEAT_H
#include "Symbol.h"
#include <string>
using	namespace std;
typedef signed long int Long;

class	BeforeRepeat : public Symbol {
	
	public :
		BeforeRepeat ();
		BeforeRepeat ( Long startPointX, Long startPointY, wstring expression );
		BeforeRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY );
		BeforeRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression );
		BeforeRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, Long middlePointX,
			Long middlePointY);
		BeforeRepeat ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, Long middlePointX,
			Long middlePointY, wstring expression );
		BeforeRepeat ( const BeforeRepeat& source );
		BeforeRepeat (
                      Long startPointX,
                      Long startPointY,

                      Long endPointX,
                      Long endPointY,
                      
                      Long expressionStartpointX,
                      Long expressionStartpointY,

                      Long expressionEndPointX, 
                      Long expressionEndPointY,
                      
                      wstring expression );

		BeforeRepeat (
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
	
			
	
			

		virtual ~BeforeRepeat ();

		BeforeRepeat&	operator = ( const BeforeRepeat& source );

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
inline	Long	BeforeRepeat::GetMiddlePointX () const {
	return	this->middlePointX;
}
inline	Long	BeforeRepeat::GetMiddlePointY () const {
	return	this->middlePointY;
}

#endif //_BEFOREREPEAT_H