#include "Select.h"

Select::Select( ){
	this->selectChart = 0;
	this->selectPaper = new SelectPaper;
}

Select::Select( const Select& source )
	:selectPaper( source.selectPaper ), selectChart( source.selectChart ){
}

Select::~Select( ){
}

Select& Select::operator= ( const Select& source ){
	this->selectChart = source.selectChart;
	this->selectPaper = source.selectPaper;

	return *this;
}

void Select::ReleaseChart( ){
	if( this->selectChart != 0 ){
		delete selectChart;
		selectChart = 0;
	}
}

void Select::ReAllocateChart( ){
	this->selectChart = new SelectChart;
}

bool Select::IsChartSelected( ){
	bool ret = false;
	if( this->selectChart != 0 ){
		ret = true;
	}
	return ret;
}
