//Symbol.h
#ifndef	_SYMBOL_H
#define	_SYMBOL_H
#include <string>
using	namespace std;
typedef signed long int Long;

class	Symbol {
	
	public :
		Symbol ();
		Symbol ( Long startPointX, Long startPointY, 
				Long endPointX,	Long endPointY,	 
				Long expressionStartPointX,	Long expressionStartPointY,
				Long expressionEndPointX, Long expressionEndPointY,
				wstring expression );
		Symbol ( Long startPointX,	Long startPointY, 
			 	Long endPointX,	Long endPointY,	 
				Long expressionStartPointX,	Long expressionStartPointY,
				Long expressionEndPointX, Long expressionEndPointY) ;

		
		Symbol ( Long startPointX, Long startPointY, wstring expression );
		Symbol ( Long startPointX, Long startPointY, Long endPointX, Long endPointY );
		Symbol ( Long startPointX, Long startPointY, Long endPointX, Long endPointY, wstring expression );
		Symbol	( const Symbol& source );


		virtual ~Symbol () = 0;

		Symbol&	operator = ( const Symbol& source );
		Long	GetStartPointX () const;
		Long	GetStartPointY () const;
		Long	GetEndPointX () const;
		Long	GetEndPointY () const;
		Long	GetExpressionStartPointX () const;
		Long	GetExpressionStartPointY () const;
		Long	GetExpressionEndPointX () const;
		Long	GetExpressionEndPointY () const;
		wstring	GetExpression () const;

	protected :
		Long	startPointX;
		Long	startPointY;
		Long	endPointX;
		Long	endPointY;
		Long	expressionStartPointX;
		Long	expressionStartPointY;
		Long	expressionEndPointX;
		Long	expressionEndPointY;
		wstring	expression;
};

inline	Long	Symbol::GetStartPointX () const {
	return	this->startPointX;
}
inline	Long	Symbol::GetStartPointY () const {
	return	this->startPointY;
}
inline	Long	Symbol::GetEndPointX () const {
	return	this->endPointX;
}
inline	Long	Symbol::GetEndPointY () const {
	return	this->endPointY;
}
inline	Long	Symbol::GetExpressionStartPointX () const {
	return	this->expressionStartPointX;
}
inline	Long	Symbol::GetExpressionStartPointY () const {
	return	this->expressionStartPointY;
}
inline	Long	Symbol::GetExpressionEndPointX () const {
	return	this->expressionEndPointX;
}
inline	Long	Symbol::GetExpressionEndPointY () const {
	return	this->expressionEndPointY;
}
inline	wstring	Symbol::GetExpression () const {
	return	this->expression;
}

#endif //_SYMBOL_H