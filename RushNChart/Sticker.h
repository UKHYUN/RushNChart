//Sticker.h

#ifndef _STICKER_H
#define _STICKER_H

#define STICKER 10
#define LINE 5
#define YES 1
#define NO -1
#define DRAW 0
#define MOVE 1

#include "Symbol.h"
#include "Paper.h"

#include "Select.h"

class Sticker {

public:
		Sticker() ;
	//복사생성자
		Sticker( const Sticker& source ) ;
		~Sticker() ;

		Sticker& operator =  (const Sticker& source ) ;

		//ok 01
		void CheckStickingField ( Paper *paper, Select *select, Long index ) ;
			// 01
		void CheckStickingFieldForMove ( Paper *paper, Select *select, Long index, Long moveX, Long moveY ) ;
		


		//ok 02
		void GetInfo ( Paper *paper, Long stickedIndex, Long stickingField,  Long oldIndex ) ;
		
		//ok 03 
		Long	 StickTo ( Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex ) ;
			// 0	2
		Symbol*  StickToForPre ( Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex ) ;



		//ok 04
		void SearchTopBottom( Paper *paper, Select *select ) ;// 다중 선택된 기호들 중 제일 위의 기호의 첨자를 구한다
		//ok 05
		void GetGap( Paper *paper, Long oldIndex ) ;// 위치좌표의 x축,y축을 이동 시킬 거리를 구한다

		//ok 06
		void StickBundleTo( Paper *paper, Select *select, Long startGapX, Long startGapY ) ; // 다중 선택된 기호들을 붙인다
			// 03
		void StickBundleToForPre ( Paper *paper, Select *select, Long startGapX, Long startGapY, Symbol* (*symbols), Long symbolsLength ) ; 



		//ok 07
		Long	StickLine( Paper *paper, Long modifiedIndex, Long transNumber ) ;
			// 04
		Symbol* StickLineForPre( Paper *paper, Long modifiedIndex, Long transNumber ) ;

		//ok 08	
		Long CheckStickingSign ( Paper *paper, Long index ) ;


		Long GetStickedIndex () const ;
		Long GetStickingField () const ;


		Long GetStartX() const ;
		Long GetStartY() const ;
		Long GetEndX() const ;
		Long GetEndY() const ;

		Long GetStartGapX() const ;
		Long GetStartGapY() const ;
		Long GetChangingWidth() const ;
		
		Long GetTopIndex() const ;
		Long GetBottonIndex() const ;

private:
	Long stickedIndex ;
	Long stickingField ;

	Long startX ;
	Long startY ;
	Long endX ;
	Long endY ;
	

	// 다중선택 후 붙일 때 필요한 속성

	Long startGapX ; //위치 x축 변화량
	Long startGapY ; //위치 y축 변화량
	Long changingWidth ; //가로길이 증감크기

	Long topIndex ; // 선택된 기호들 중 맨 위 기호의 첨자
	Long bottomIndex ; // 선택된 기호들 중 맨 아래 기호의 첨자
	
	Symbol *dotSymbol ;


	// 다중선택구조
	Long stickedCase ;
};

inline Long Sticker::GetStickedIndex () const {
	return this->stickedIndex ;
}

inline Long Sticker::GetStickingField () const {
	return this->stickingField ;
}

inline Long Sticker::GetStartX() const {
	return this->startX ;
}
inline Long Sticker::GetStartY() const {
	return this->startY ;
}
inline Long Sticker::GetEndX() const {
	return this->endX ;
}
inline Long Sticker::GetEndY() const {
	return this->endY ;
}

inline Long Sticker::GetStartGapX() const {
	return this->startGapX ;
}
inline Long Sticker::GetStartGapY() const {
	return this->startGapY ;
}
inline Long Sticker::GetChangingWidth() const {
	return this->changingWidth ;
}
inline Long Sticker::GetTopIndex() const {
	return this->topIndex ;
}

inline Long Sticker::GetBottonIndex() const {
	return this->bottomIndex ;
}



#endif //