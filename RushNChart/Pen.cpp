//Pen.cpp

#include "Pen.h"

Pen::Pen( )	{
	this->currentIndex = -1;
	this->currentPointX = 0;
	this->currentPointY = 0;
	this->width = 0;
	this->height = 0;
}

Pen::Pen( Long currentIndex, Long currentPointX, Long currentPointY, Long width, Long height )	{
	this->currentIndex = currentIndex;
	this->currentPointX = currentPointX;
	this->currentPointY = currentPointY;
	this->width = width;
	this->height = height;
}

Pen::Pen( const Pen& source )	{
	this->currentIndex = source.currentIndex;
	this->currentPointX = source.currentPointX;
	this->currentPointY = source.currentPointY;
	this->width = source.width;
	this->height = source.height;
}

Pen& Pen::operator = ( const Pen& source )	{
	this->currentIndex = source.currentIndex;
	this->currentPointX = source.currentPointX;
	this->currentPointY = source.currentPointY;
	this->width = source.width;
	this->height = source.height;

	return *this;
}

Long Pen::MoveLeft ( Long moveWidth )	{
	this->currentIndex--;

	this->currentPointX -= moveWidth;
	//this->width -= moveWidth;

	return this->currentPointX;
}

Long Pen::MoveRight ( Long moveWidth )	{
	this->currentIndex++;

	this->currentPointX += moveWidth;
	//this->width += moveWidth;

	return this->currentPointX;
}

Pen::~Pen()	{

}