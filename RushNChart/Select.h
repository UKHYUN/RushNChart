#ifndef _SELECT_H
#define _SELECT_H

#include "SelectPaper.h"
#include "SelectChart.h"

typedef signed long int Long;

class Select{
public :
	Select( );
	Select( const Select& source );
	~Select( );
	Select& operator = ( const Select& source );

	void ReleaseChart ( );
	void ReAllocateChart ( );
	bool IsChartSelected( );

	SelectPaper* GetSelectPaper( ) const;
	SelectChart* GetSelectChart( ) const;

private :
	SelectPaper *selectPaper;
	SelectChart *selectChart;
};
inline SelectPaper* Select:: GetSelectPaper( ) const{
	return this->selectPaper;
}
inline SelectChart* Select:: GetSelectChart( ) const{
	return this->selectChart;
}

#endif _SELECT_H