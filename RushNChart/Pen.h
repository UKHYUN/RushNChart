//Pen.h

#ifndef _PEN_H
#define _PEN_H

typedef signed long int Long;

class Pen	{
	public :
		
		Pen( );
		
		Pen( Long currentIndex, Long currentPointX, Long currentPointY, Long width, Long height );

		Pen( const Pen& source );

		~Pen( );

		Pen& operator = ( const Pen& source );

		Long MoveLeft( Long moveWidth );
		Long MoveRight( Long moveWidth );

		Long GetCurrentIndex() const;
		Long GetCurrentPointX() const;
		Long GetCurrentPointY() const;
		Long GetWidth() const;
		Long GetHeight() const;

	private :
		Long currentIndex;
		Long currentPointX;
		Long currentPointY;
		Long width;
		Long height;
};

inline Long Pen::GetCurrentIndex()	const	{
	return this->currentIndex;
}


inline Long Pen::GetCurrentPointX()	const	{
	return this->currentPointX;
}


inline Long Pen::GetCurrentPointY()	const	{
	return this->currentPointY;
}

inline Long Pen::GetWidth()	const	{
	return this->width;
}

inline Long Pen::GetHeight()	const	{
	return this->height;
}

#endif	// _PEN_H