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
	//���������
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
		void SearchTopBottom( Paper *paper, Select *select ) ;// ���� ���õ� ��ȣ�� �� ���� ���� ��ȣ�� ÷�ڸ� ���Ѵ�
		//ok 05
		void GetGap( Paper *paper, Long oldIndex ) ;// ��ġ��ǥ�� x��,y���� �̵� ��ų �Ÿ��� ���Ѵ�

		//ok 06
		void StickBundleTo( Paper *paper, Select *select, Long startGapX, Long startGapY ) ; // ���� ���õ� ��ȣ���� ���δ�
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
	

	// ���߼��� �� ���� �� �ʿ��� �Ӽ�

	Long startGapX ; //��ġ x�� ��ȭ��
	Long startGapY ; //��ġ y�� ��ȭ��
	Long changingWidth ; //���α��� ����ũ��

	Long topIndex ; // ���õ� ��ȣ�� �� �� �� ��ȣ�� ÷��
	Long bottomIndex ; // ���õ� ��ȣ�� �� �� �Ʒ� ��ȣ�� ÷��
	
	Symbol *dotSymbol ;


	// ���߼��ñ���
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