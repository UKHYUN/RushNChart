#include "Sticker.h"
#include "Sequence.h"
#include "AfterRepeat.h"
#include "BeforeRepeat.h"
#include "Selection.h"
#include "SwitchCase.h"
#include "Arrow.h"

Sticker::Sticker() {
	this->stickedIndex = -1 ;
	this->stickingField = -1 ;
	this->stickedCase = -1 ;
}
Sticker::Sticker( const Sticker& source ) {
	this->stickedIndex = source.stickedIndex ;
	this->stickingField = source.stickingField ;
	this->stickedCase = -1 ;
}
Sticker::~Sticker(){
}
Sticker& Sticker::operator= ( const Sticker& source ) {
	this->stickedIndex = source.stickedIndex ;
	this->stickingField = source.stickingField ;
	this->stickedCase = -1 ;

	return *this ;
}



/*
	함수이름 : CheckStickingField
	설    명 : 매개변수로 들어온 기호(첨자)가 붙을 수 있는 기호가 있으면 그 기호의 첨자와 붙는 위치 정보를 구한다
	입    력 : Paper *paper, Long index( 붙을 기호의 첨자 )
	출    력 : void
	만 든 이 : i5
	특이사항 : 붙는 영역이 기호의 내부와 일정범위의 외부// 그릴 때 사용 중
*/
void Sticker::CheckStickingField ( Paper *paper, Select *select, Long index ) {

//======================================================================================마우스에 걸린 기호가 아니라 종이 위 기호들의 정보를 담는 변수들===================================================================
		// index기호가 붙을 종이 위 기호의 위치, 크기, 미들
			// 이 변수들로 붙을 영역을 설정한다
			// paper Length만큼 돌려서 확인하기 때문에 값은 반복제어변수가 변하면 함께 계속 변한다
 		Long stickingStartX ;
		Long stickingStartY ;
		Long stickingEndX ;
		Long stickingEndY ;
		Long stickingMiddleX ;
		Long stickingMiddleY ;

		// index기호가 붙을 종이 위 기호가 SwitchCase일 떄
		Long swtichCaseSelectionStartX ;
		Long swtichCaseSelectionStartY ;
		Long swtichCaseSelectionEndX ;
		Long swtichCaseSelectionEndY ;

		Long swtichCaseFalseStartX ;
		Long swtichCaseFalseStartY ;


		//기호가 붙을 기호(종이 위에 있는 기호)의 힙데이터 주소를 담을 자동변수
		Symbol *symbol ; // checkSymbol
		
//=======================================================================================================================================================================================================================


//======================================================================================마우스에 걸린 기호(index)의 정보를 담을 변수들===================================================================================
		// index기호가 SwitchCase외의 기호일 때 사용할 변수
		Long startX ;
		Long startY ;
		Long endX ;
		Long endY ;
		Long middleX ;
		Long middleY ;

		Symbol *indexSymbol = paper->GetAt( index ) ;



		// index기호가 SwitchCase일 때 사용할 변수 
		Long selectionStartX ;
		Long selectionStartY ;
		Long selectionEndX ;
		Long selectionEndY ;
		Long selectionMiddleX ;

		Long swtichCaseFalseEndX ;
		Long swtichCaseFalseEndY ;

		if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
		{
			selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() ;
			selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() ;
			selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
			selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() ;
			selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() ;

			swtichCaseFalseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
			swtichCaseFalseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
		}
		else{
			startX = paper->GetAt( index )->GetStartPointX() ;
			startY = paper->GetAt( index )->GetStartPointY() ;
			endX = paper->GetAt( index )->GetEndPointX() ;
			endY = paper->GetAt( index )->GetEndPointY() ;
		}
		

//=======================================================================================================================================================================================================================

		Long i = 0 ;
		while ( i < paper->GetLength()  && this->stickingField == -1 ) {


			
				symbol = paper->GetAt( i ) ;
				if(  dynamic_cast<SwitchCase*>(symbol) ) 
				{
					swtichCaseSelectionStartX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetStartPointX() ;
					swtichCaseSelectionStartY = static_cast<SwitchCase*>(symbol)->GetSelection()->GetStartPointY() ;
					swtichCaseSelectionEndX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetEndPointX() ;
					swtichCaseSelectionEndY = static_cast<SwitchCase*>(symbol)->GetSelection()->GetEndPointY() ;
					
					swtichCaseFalseStartX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetMiddlePointX() ;
					swtichCaseFalseStartY = static_cast<SwitchCase*>(symbol)->GetSelection()->GetMiddlePointY() ;
					
				}
				else 
				{
					stickingStartX = symbol->GetStartPointX () ;
					stickingStartY = symbol->GetStartPointY () ;
					stickingEndX = symbol->GetEndPointX () ;
					stickingEndY = symbol->GetEndPointY() ;
				}
			////	
			////
			////		   
			/// 종이 위의 기호가 Sequence일 때
			if( dynamic_cast<Sequence*>(symbol) && i != index )
			{
				
				Sequence *checkSequence =  static_cast<Sequence*>(symbol) ;

				// Sequence에 붙는 index기호가 Sequence거나 Selection이면
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					 dynamic_cast<Selection*>(paper->GetAt( index ))
					)
				{ 
						// 아래로 붙기 위해, 왼쪽 윗점이 순차의 붙는 영역에 속할 때
						if( checkSequence->downSign == NO &&
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingEndY + STICKER
							)
						{
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSequence->downSign = YES ;
						}
						// 아래로 붙기 위해, 오른쪽 윗점이 순차의 붙는 영역에 속할 때
						else if( checkSequence->downSign == NO && 
								endX > stickingStartX &&
								 endX < stickingEndX &&
								 startY > stickingStartY - STICKER &&
								 startY < stickingEndY + STICKER 
								 )
						{
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSequence->downSign = YES ;
						}

						// 위로 붙기 위해, 왼쪽 아랫점이 순차의 붙는 영역에 속할 때
						else if( checkSequence->upSign == NO &&
								 startX > stickingStartX &&
								 startX < stickingEndX &&
								 endY > stickingStartY - STICKER &&
								 endY < stickingEndY + STICKER 
								 )
						{
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSequence->upSign = YES ;
						}
						// 위로 붙기 위해, 오른쪽 아랫점이 순차의 붙는 영역에 속할 때
						else if( checkSequence->upSign == NO &&
								 endX > stickingStartX &&
								 endX < stickingEndX &&
								 endY > stickingStartY - STICKER &&
								 endY < stickingEndY + STICKER 
								 )
						{
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSequence->upSign = YES ;
						}
				}





				// Sequence에 붙는 index기호가 BeforeRepeat면
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					
					BeforeRepeat *indexBeforeRepeat =  static_cast<BeforeRepeat*>(paper->GetAt( index )) ;
					middleX = indexBeforeRepeat->GetMiddlePointX() ;
					middleY = indexBeforeRepeat->GetMiddlePointY() ;
					

					// 아래로 붙기 위해, 왼쪽 위점이 순차의 붙는 영역에 속할 때
					if( checkSequence->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingStartY - STICKER &&
						startY < stickingEndY + STICKER
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}
					// 아래로 붙기 위해, 오른쪽 위의 점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->downSign == NO &&  
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingStartY - STICKER &&
							 startY < stickingEndY + STICKER 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}

					// 아래로 붙기 위해, 오른쪽 중간점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->downSign == NO && 
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY + 40 > stickingStartY - STICKER &&
							 startY + 40 < stickingEndY + STICKER 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}
					// 아래로 붙기 위해, 오른쪽 아랫점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->downSign == NO && 
							 middleX > stickingStartX &&
							 middleX < stickingEndX &&
							 middleY > stickingStartY - STICKER &&
							 middleY < stickingEndY + STICKER 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}
					// 위로 붙기 위해, 왼쪽 아랫점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->upSign == NO &&
							 startX > stickingStartX &&
							 startX < stickingEndX &&
							 endY > stickingStartY - STICKER &&
							 endY < stickingEndY + STICKER 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}

					// 위로 붙기 위해, 아랫쪽 중간점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->upSign == NO &&
							 startX + 40 > stickingStartX &&
							 startX + 40 < stickingEndX &&
							 endY > stickingStartY - STICKER &&
							 endY < stickingEndY + STICKER 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}
				
				}

				// Sequence에 붙는 기호가 AfterRepeat면
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
					// 아래로 붙기 위해, 왼쪽 위점이 순차의 붙는 영역에 속할 때
					if( checkSequence->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingStartY - STICKER &&
						startY < stickingEndY + STICKER
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}

					// 아래로 붙기 위해, 왼쪽 위 중간점이 순차의 붙는 영역에 속할 때
					if( checkSequence->downSign == NO && 
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						startY > stickingStartY - STICKER &&
						startY < stickingEndY + STICKER
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}

					// 위로 붙기 위해, 왼쪽 아랫점이 순차의 붙는 영역에 속할 때
					if( checkSequence->upSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingEndY + STICKER
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}

					// 위로 붙기 위해, 오른쪽 아랫점이 순차의 붙는 영역에 속할 때
					if( checkSequence->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingEndY + STICKER
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}

					// 위로 붙기 위해, 오른쪽 아래 중간점이 순차의 붙는 영역에 속할 때
					if( checkSequence->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY - 40 > stickingStartY - STICKER &&
						endY - 40 < stickingEndY + STICKER
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}

					// 위로 붙기 위해, 오른쪽 아래 중간점이 순차의 붙는 영역에 속할 때
					if( checkSequence->upSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY - STICKER &&
						middleY < stickingEndY + STICKER
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}
			}

			// Sequence에 붙는 기호가 SwitchCase일 때 
			if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
			{
				Long selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() ;
				Long selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() ;
				Long selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
				Long selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() ;
				Long selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() ;

				Long firstCaseStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetStartPointX() ;
				Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
				Long defaultCaseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointX() ;
				Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointY() ;


				// 아래로 붙기 위해, 왼쪽 위점이 순차의 붙는 영역에 속할 때
					if( checkSequence->downSign == NO && 
						selectionStartX > stickingStartX &&
						selectionStartX < stickingEndX &&
						selectionStartY > stickingStartY - STICKER &&
						selectionStartY < stickingEndY + STICKER
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}
					// 아래로 붙기 위해, 오른쪽 위점이 순차의 붙는 영역에 속할 때
					else if(checkSequence->downSign == NO &&  
							selectionEndX > stickingStartX &&
							selectionEndX < stickingEndX &&
							selectionStartY > stickingStartY - STICKER &&
							selectionStartY < stickingEndY + STICKER
							)
						{
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSequence->downSign = YES ;
						}

					// 위로 붙기 위해, 왼쪽 아랫점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->upSign == NO &&
							firstCaseStartX > stickingStartX &&
							firstCaseStartX < stickingEndX &&
							firstCaseEndY > stickingStartY - STICKER &&
							firstCaseEndY < stickingEndY + STICKER
							)
						{
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSequence->upSign = YES ;
						}
					
					// 위로 붙기 위해, 중간 아랫점이 순차의 붙는 영역에 속할 때
					else if(checkSequence->upSign == NO && 
							defaultCaseEndX > stickingStartX &&
							defaultCaseEndX < stickingEndX &&
							defaultCaseEndY > stickingStartY - STICKER &&
							defaultCaseEndY < stickingEndY + STICKER
							)
						{
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSequence->upSign = YES ;
						}
			}


	   }// Sequence에 기호가 붙을 때 처리 함수 닫는 중괄호



	   /////	
		////
		/// 종이 위의 기호가 Selection일 때
		if( dynamic_cast<Selection*>(symbol) && i != index  ){
			
			stickingMiddleX = (static_cast<Selection*>(symbol))->GetMiddlePointX() ;
			stickingMiddleY = (static_cast<Selection*>(symbol))->GetMiddlePointY() ;
			Selection *checkSelection = static_cast<Selection*>(symbol) ;
			// 선택구조에 위로 달라붙는 경우를 구조별로 추가한다 
				// 선택구조에 위로 달라붙는 구조가 순차이거나 선택일 때
			if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					dynamic_cast<Selection*>(paper->GetAt( index ))
				) {

					// TRUE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때 
					else if( checkSelection->trueSign == NO &&
								endX > stickingStartX &&
								endX < stickingMiddleX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +STICKER  ){
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSelection->trueSign = YES ;
					}
					// FALSE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					else if(checkSelection->falseSign == NO &&
							startX > stickingMiddleX &&
							startX < stickingEndX &&
							startY > stickingStartY &&
							startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}
				// 위로 붙기 위해, 오른쪽 아랫점이 붙는 영역에 속할 때 
					if(	checkSelection->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
					// 위로 붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때 
					else if(	checkSelection->upSign == NO &&
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - STICKER &&
							endY < stickingEndY ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkSelection->upSign = YES ;
					}
			}

				//선택구조에 위로 달라붙는 구조가 선반복일 때
			if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index ))) {

				middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
				middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
				// TRUE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						endX > stickingStartX &&
						endX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						endX > stickingStartX &&
						endX < stickingMiddleX &&
						startY + 40 > stickingStartY  &&
						startY + 40 < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 중간점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						middleY > stickingStartY  &&
						middleY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					
					// FALSE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					else if(checkSelection->falseSign == NO && 
							startX > stickingMiddleX &&
							startX < stickingEndX &&
							startY > stickingStartY &&
							startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}

					// FALSE쪽에 붙기 위해, 중간점이 붙는 영역에 속할 때 
					if( checkSelection->falseSign == NO &&
						middleX > stickingMiddleX &&
						middleX < stickingEndX &&
						middleY > stickingStartY  &&
						middleY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
					}




				// 위로 붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때 
				if(	checkSelection->upSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					endY > stickingStartY - STICKER &&
					endY < stickingEndY ) {
						this->stickedIndex = i ;
						this->stickingField = 3 ;
					}
				// 위로 붙기 위해, 왼쪽 아래 중간점이 붙는 영역에 속할  때	
				else if(checkSelection->upSign == NO &&
						startX + 40 > stickingStartX &&
						startX + 40 < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
			}
				//선택구조에 위로 달라붙는 구조가 후반복일 때
			if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index ))) {

				middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
				middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;

					// TRUE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					if(  checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 중간 윗점이 붙는 영역에 속할 때 
					else if(  checkSelection->trueSign == NO &&
								middleX > stickingStartX &&
								middleX < stickingMiddleX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +STICKER  ){
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSelection->trueSign = YES ;
					}
					// FALSE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					if( checkSelection->falseSign == NO &&
						startX > stickingMiddleX &&
						startX < stickingEndX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
					}
					// FALSE쪽에 붙기 위해, 중간 윗점이 붙는 영역에 속할 때 
					else if( checkSelection->falseSign == NO &&
								middleX > stickingMiddleX &&
								middleX < stickingEndX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +STICKER  ){
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}

				//위로 붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				if(	checkSelection->upSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					endY > stickingStartY - STICKER &&
					endY < stickingEndY ) {
						this->stickedIndex = i ;
						this->stickingField = 3 ;
						checkSelection->upSign = YES ;
					}

				//위로 붙기 위해, 중간점이 붙는 영역에 속할 때
				else if( checkSelection->upSign == NO &&
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - STICKER &&
							middleY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
				//위로 붙기 위해, 오른쪽 아랫점이 붙는 영역에 속할 때
				else if( checkSelection->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - STICKER &&
							endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
				//위로 붙기 위해, 오른쪽 아래 중간점이 붙는 영역에 속할 때
				else if( checkSelection->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY - 40 > stickingStartY - STICKER &&
							endY - 40 < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
			}


				
			// Selection에 붙는 기호가 SwitchCase일 때 
			if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
			{
				Long selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() ;
				Long selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() ;
				Long selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
				Long selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() ;
				Long selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() ;

				Long firstCaseStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetStartPointX() ;
				Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
				Long defaultCaseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointX() ;
				Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointY() ;


				// TRUE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
				if(  checkSelection->trueSign == NO &&
					selectionStartX > stickingStartX &&
					selectionStartX < stickingMiddleX &&
					selectionStartY > stickingStartY  &&
					selectionStartY < stickingMiddleY +STICKER  ){
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkSelection->trueSign = YES ;
				}

				// FALSE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때  
				else if(checkSelection->falseSign == NO && 
						selectionStartX > stickingMiddleX &&
						selectionStartX < stickingEndX &&
				 		selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
				}
				// FALSE쪽에 붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때  
				else if(checkSelection->falseSign == NO && 
						selectionEndX > stickingMiddleX &&
						selectionEndX < stickingEndX &&
				 		selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
				}
				//위로 붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkSelection->upSign == NO &&
						firstCaseStartX > stickingStartX &&
						firstCaseStartX < stickingEndX &&
						firstCaseEndY > stickingStartY - STICKER &&
						firstCaseEndY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
				}
				//위로 붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
				else if(checkSelection->upSign == NO && 
						defaultCaseEndX > stickingStartX &&
						defaultCaseEndX < stickingEndX &&
						defaultCaseEndY > stickingStartY - STICKER &&
						defaultCaseEndY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
				}
			}
		}//Selection에 기호가 붙을 때 처리 함수 닫는 중괄호
			
		////
		////
		/// 종이 위의 기호가 BeforeRepeat일 때
		if( dynamic_cast<BeforeRepeat*>(symbol) && i != index  ){
			
			stickingMiddleX = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointX() ;
			stickingMiddleY = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointY() ;
			BeforeRepeat *checkBeforeRepeat = static_cast<BeforeRepeat*>(symbol) ;
			
			// 선반복구조에 안쪽으로 달라붙는 구조가 순차이거나 선택일 때
			if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					dynamic_cast<Selection*>(paper->GetAt( index ))
				) {

				// 선반복구조에 안쪽으로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}
			

				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
			}
		


		// BeforeRepeat에 붙는 기호가 BeforeRepeat면
			if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
			{ 
				middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
				middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
				// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY &&
						middleY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						middleY > stickingStartY &&
						middleY < stickingMiddleY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkBeforeRepeat->inSign = YES ;
				}
					// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO && 
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
					  	startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO &&  
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						startX > stickingStartX &&
					 	startX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}							
			}
			// BeforeRepeat에 붙는 기호가 AfterRepeat면
			if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
			{ 
				middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
				middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;


				// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 중간 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}

				// 선반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
					  	startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 중간 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						endX > stickingStartX &&
					 	endX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO &&  
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY - STICKER &&
						middleY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}	
				// 선반복구조에 위로 달라붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						endX > stickingStartX &&
						endX < stickingEndX &&
						middleY > stickingStartY - STICKER &&
						middleY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						startX > stickingStartX &&
						startX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}


			}
			// BeforeRepeat에 붙는 기호가 SwitchCase일 때 
			if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
			{
				Long selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() ;
				Long selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() ;
				Long selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
				Long selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() ;
				Long selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() ;

				Long firstCaseStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetStartPointX() ;
				Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
				Long defaultCaseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointX() ;
				Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointY() ;

					
				// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				if( checkBeforeRepeat->inSign == NO &&
					selectionStartX > stickingStartX &&
					selectionStartX < stickingEndX &&
					selectionStartY > stickingStartY &&
					selectionStartY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						selectionEndX > stickingStartX &&
						selectionEndX < stickingEndX &&
						selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkBeforeRepeat->inSign = YES ;
				}

				// 선반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						selectionStartX > stickingStartX &&
						selectionStartX < stickingMiddleX &&
					  	selectionStartY > stickingEndY - 20 &&
						selectionStartY < stickingEndY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO &&  
						selectionEndX > stickingStartX &&
						selectionEndX < stickingMiddleX &&
					  	selectionStartY > stickingEndY - 20 &&
						selectionStartY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}

				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						firstCaseStartX > stickingStartX &&
						firstCaseStartX < stickingEndX &&
						firstCaseEndY > stickingStartY - STICKER &&
						firstCaseEndY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						defaultCaseEndX > stickingStartX &&
						defaultCaseEndX < stickingEndX &&
						defaultCaseEndY > stickingStartY - STICKER &&
						defaultCaseEndY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}

			}
		}//BeforeRepeat에 기호가 붙을 때 처리 함수 닫는 중괄호






			////
			////
			/// 종이 위의 기호가 AfterRepeat 일 때
			if( dynamic_cast<AfterRepeat*>(symbol) && i != index ){
			
				stickingMiddleX = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointX() ;
				stickingMiddleY = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointY() ;
				AfterRepeat *checkAfterRepeat = static_cast<AfterRepeat*>(symbol) ;
				// 후반복구조에 아래쪽으로 달라붙는 구조가 순차이거나 선택일 때
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					 dynamic_cast<Selection*>(paper->GetAt( index ))
					) {

					// 후반복구조에 아래쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					if(	checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래쪽으로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingMiddleY &&
							 startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;

					}
					// 후반복구조에 위로 달라붙기 위해, 오른쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}

					// 후반복구조에 안쪽 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO &&
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
				}

				// AfterRepeats에 붙는 기호가 BeforeRepeat면
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
					// 후반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					if( checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingMiddleY &&
							 startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if( checkAfterRepeat->downSign == NO && 
							 middleX > stickingStartX &&
							 middleX < stickingEndX &&
							 middleY > stickingMiddleY &&
							 middleY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 middleY > stickingMiddleY &&
							 middleY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// 후반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
				
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - STICKER &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							middleY > stickingStartY - STICKER &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}


				}//AfterRepeat에 기호가 붙을 때 처리 함수 닫는 중괄호


				// BeforeRepeat에 붙는 기호가 AfterRepeat면
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;

					// 후반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					if( checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 중간 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->downSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							startY > stickingMiddleY &&
							startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// 후반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 오른쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO &&
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - STICKER  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - STICKER  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							middleY > stickingStartY - STICKER  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 중간 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
				}


				if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
				{
					Long selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() ;
					Long selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() ;
					Long selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
					Long selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() ;
					Long selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() ;

					Long firstCaseStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetStartPointX() ;
					Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
					Long defaultCaseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointX() ;
					Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointY() ;

					// 후반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					if( checkAfterRepeat->downSign == NO &&
						selectionStartX > stickingStartX &&
						selectionStartX < stickingEndX &&
						selectionStartY > stickingMiddleY &&
						selectionStartY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->downSign == NO && 
							selectionEndX > stickingStartX &&
							selectionEndX < stickingEndX &&
							selectionStartY > stickingMiddleY &&
							selectionStartY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// 후반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO &&
							firstCaseStartX > stickingStartX &&
							firstCaseStartX < stickingEndX &&
							firstCaseEndY > stickingStartY - STICKER  &&
							firstCaseEndY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO &&
							defaultCaseEndX > stickingStartX &&
							defaultCaseEndX < stickingEndX &&
							defaultCaseEndY > stickingStartY - STICKER  &&
							defaultCaseEndY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}

					// 후반복구조에 안쪽 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							selectionStartX > stickingStartX &&
							selectionStartX < stickingEndX &&
							selectionStartY > stickingStartY - STICKER &&
							selectionStartY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							selectionEndX > stickingStartX &&
							selectionEndX < stickingEndX &&
							selectionStartY > stickingStartY - STICKER &&
							selectionStartY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
				
				
				}



			 } // 기호가 붙을 기호가 AfterRepeat일 때를 처리하는 로직 닫는 중괄호


			 //
			 ///
			 ///
			 // 종이 위의 기호가 SwitchCase 일 때

			 if( dynamic_cast<SwitchCase*>(symbol) && i != index )
			 {
				Long swtichCaseFalseEndX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetEndPointX() ;
				Long swtichCaseFalseEndY = static_cast<SwitchCase*>(symbol)->GetCases(0)->GetEndPointY() ;
				SwitchCase *checkSwitchCase = static_cast<SwitchCase*>(symbol) ;
				Long checkSwitchCaseUpsign = checkSwitchCase->upSign ;
				Long checkSwitchFalseSign = checkSwitchCase->falseSign ;
							
				
				// SwitchCase에 붙는 기호가 Sequence 일 때
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) )
				{ 
						//  SwitchCase의 특정 case 아래로 붙기위해, Sequence나 Selection 오른쪽 윗점이 붙는 영역에 속할 때//위의 가로길이 중간 점이 붙는 영역에 속할 때 
						Long j = 0 ;
						while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
						{
							Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
							Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
							Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
							Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;
							Long checkCaseDownSign = checkSwitchCase->GetCases( j )->downSign ; // checkCaseDownSign == NO &&

							if( checkCaseDownSign == NO &&
								startX  > caseStartX && //startX + ( ( endX - startX )/2 ) > caseStartX &&
								startX < caseEndX && //startX + ( ( endX - startX )/2 ) < caseEndX &&
								startY > caseStartY &&
								startY < caseEndY )
							{
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								this->stickedCase = j ;
								checkSwitchCase->GetCases( j )->downSign = YES ;
							}
							j++ ;
						}

						if( this->stickedCase == -1 ){
								
							//   SwitchCase의 위로 붙기위해, Sequence나 Selection의 왼쪽 아랫점이 붙는 영역에 속할 때 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
							}
							//   SwitchCase의 위로 붙기위해, Sequence나 Selection의 오른쪽 아랫점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO &&
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 FALSE쪽 아래로 붙기 위해, Sequence 오른쪽 윗점이 붙는 영역에 속할 때 //가로길이 중간점이 붙는 영역에 속할 때 
							else if(    checkSwitchCase->falseSign == NO &&
										startX > swtichCaseFalseStartX && //startX + ( ( endX - startX )/2 ) > swtichCaseFalseStartX &&
										startX < swtichCaseFalseEndX && //startX + ( ( endX - startX )/2 ) < swtichCaseFalseEndX &&
										startY > swtichCaseFalseStartY - 80 &&
										startY < swtichCaseFalseEndY ) 
							{
											this->stickedIndex = i ;
											this->stickingField = 3 ;
											checkSwitchCase->falseSign = YES ;						
							}
							//   SwitchCase의 FALSE쪽 아래로 붙기 위해, Sequence 왼쪽 윗점이 붙는 영역에 속할 때 
							else if(	checkSwitchCase->falseSign == NO &&
										startX > swtichCaseFalseStartX &&
										startX < swtichCaseFalseEndX &&
										startY > swtichCaseFalseStartY - 80 &&
										startY < swtichCaseFalseEndY ) 
							{
											this->stickedIndex = i ;
											this->stickingField = 3 ;
											checkSwitchCase->falseSign = YES ;						
							}
							//   SwitchCase의 FALSE쪽 아래로 붙기 위해, Sequence 오른쪽 윗점이 붙는 영역에 속할 때 
							else if(	checkSwitchCase->falseSign == NO &&
										endX > swtichCaseFalseStartX &&
										endX < swtichCaseFalseEndX &&
										startY > swtichCaseFalseStartY - 80 &&
										startY < swtichCaseFalseEndY ) 
							{
											this->stickedIndex = i ;
											this->stickingField = 3 ;
											checkSwitchCase->falseSign = YES ;
							}

						}
				}// // SwitchCase에 붙는 기호가 Sequence일 때를 처리하는 로직 닫는 중괄호


					else if(	 dynamic_cast<Selection*>(paper->GetAt( index )) )
					{ 
							//  SwitchCase의 특정 case 아래로 붙기위해, Sequence나 Selection 오른쪽 윗점이 붙는 영역에 속할 때//위의 가로길이 중간 점이 붙는 영역에 속할 때 
						Long j = 0 ;
						while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
						{
							Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
							Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
							Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
							Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;
							Long checkCaseDownSign = checkSwitchCase->GetCases( j )->downSign ; // checkCaseDownSign == NO &&

							if( checkCaseDownSign == NO &&
								startX  > caseStartX && //startX + ( ( endX - startX )/2 ) > caseStartX &&
								startX < caseEndX && //startX + ( ( endX - startX )/2 ) < caseEndX &&
								startY > caseStartY &&
								startY < caseEndY )
							{
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								this->stickedCase = j ;
								checkSwitchCase->GetCases( j )->downSign = YES ;
							}
							j++ ;
						}

						if( this->stickedCase == -1 ){
								
							//   SwitchCase의 위로 붙기위해, Sequence나 Selection의 왼쪽 아랫점이 붙는 영역에 속할 때 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
							}
							//   SwitchCase의 위로 붙기위해, Sequence나 Selection의 오른쪽 아랫점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO &&
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
						}
					}// // SwitchCase에 붙는 기호가 Selection일 때를 처리하는 로직 닫는 중괄호


					// SwitchCase에 붙는 기호가 BeforeRepeat면
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
					
					//  SwitchCase의 특정 case 아래로 붙기위해, BeforeRepeat 오른쪽 윗점이 붙는 영역에 속할 때 //위의 가로길이 중간 점이 붙는 영역에 속할 때 
					Long j = 0 ;
					while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
					{
						Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
						Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
						Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
						Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;
						Long checkCaseDownSign = checkSwitchCase->GetCases( j )->downSign ; // checkCaseDownSign == NO &&
						if( checkCaseDownSign == NO &&
							startX > caseStartX &&//startX + ( ( endX - startX )/2 ) > caseStartX &&
							startX < caseEndX && //startX + ( ( endX - startX )/2 ) < caseEndX &&
							startY > caseStartY &&
							startY < caseEndY )
						{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							this->stickedCase = j ;
							checkSwitchCase->GetCases( j )->downSign = YES ;
						}
						j++ ;
		
					}

					if( this->stickedCase == -1 )
					{
							//   SwitchCase의 위로 붙기위해, BeforeRepeat의 왼쪽 아랫점이 붙는 영역에 속할 때 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 위로 붙기위해, BeforeRepeat의 오른쪽 아랫점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO && 
									middleX > swtichCaseSelectionStartX &&
									middleX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}	
					}
				}// SwitchCase에 붙는 기호가 BeforeRepeat일 때를 처리하는 로직닫는 중괄호



				// SwitchCase에 붙는 기호가 AfterRepeat면
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
					
					//  SwitchCase의 특정 case 아래로 붙기위해, AfterRepeat 오른쪽 윗점이 붙는 영역에 속할 때//위의 가로길이 중간 점이 붙는 영역에 속할 때 
					Long j = 0 ;
					while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
					{
						Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
						Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
						Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
						Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;
						Long checkCaseDownSign = checkSwitchCase->GetCases( j )->downSign ; // checkCaseDownSign == NO &&

						if( checkCaseDownSign == NO &&
							startX > caseStartX &&//startX + ( ( middleX - startX )/2 ) > caseStartX &&
							startX < caseEndX && //startX + ( ( middleX - startX )/2 ) < caseEndX &&
							startY > caseStartY &&
							startY < caseEndY )
						{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							this->stickedCase = j ;
							checkSwitchCase->GetCases( j )->downSign = YES ;
						}
						j++ ;
		
					}
					if( this->stickedCase == -1 )
					{
							//   SwitchCase의 위로 붙기위해, AfterRepeat의 왼쪽 아랫점이 붙는 영역에 속할 때 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 위로 붙기위해, AfterRepeat의 오른쪽 아랫점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO && 
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 위로 붙기위해, AfterRepeat의 미들점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO &&
									middleX > swtichCaseSelectionStartX &&
									middleX < swtichCaseSelectionEndX &&
									middleY > swtichCaseSelectionStartY &&
									middleY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 위로 붙기위해, AfterRepeat의 오른쪽 미들점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO &&
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									middleY > swtichCaseSelectionStartY &&
									middleY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
					}


				}//  SwitchCase에 붙는 기호가 AfterRepeat일 때를 처리하는 로직 닫는 중괄호
				
				 // SwitchCase에 붙는 기호가 SwitchCase면
				if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
				{ 
					/*
					 selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() ;
					 selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() ;
					 selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
					 selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() ;
					 selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() ;

					 swtichCaseFalseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
					 swtichCaseFalseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
					 //*/
					//  SwitchCase의 특정 case 아래로 붙기위해, AfterRepeat 위의 가로길이 중간 점이 붙는 영역에 속할 때 
					Long j = 0 ;
					while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
					{
						Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
						Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
						Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
						Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;

						
						if(
							selectionStartX //+ ( ( middleX - startX )/2 ) 
							> caseStartX &&
							selectionStartX //+ ( ( middleX - startX )/2 ) 
							< caseEndX &&
							selectionStartY > caseStartY &&
							selectionStartY < caseEndY )
						{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							this->stickedCase = j ; //무조건 스위치케이스는 아래 case에 붙을 때는 첫번째 case에 맞춘다

							
						}
						j++ ;
		
					}
				
					if( this->stickedCase == -1 )
					{
						// SwitchCase 왼쪽 아랫점 Y좌표, defaultSequence 아랫점 Y좌표
						Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
						Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount())->GetEndPointY() ;
						//  SwitchCase의 위로 붙기위해, SwitchCase의 왼쪽 아랫점이 붙는 영역에 속할 때 
						if( checkSwitchCaseUpsign == NO &&
							selectionStartX > swtichCaseSelectionStartX &&
							selectionStartX < swtichCaseSelectionEndX &&
							firstCaseEndY > swtichCaseSelectionStartY &&
							firstCaseEndY < swtichCaseSelectionEndY ){
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSwitchCase->upSign = YES ;
						}
						//   SwitchCase의 위로 붙기위해, SwitchCase의 중간 아랫점이 붙는 영역에 속할 때 
						else if(checkSwitchCaseUpsign == NO && 
								selectionMiddleX > swtichCaseSelectionStartX &&
								selectionMiddleX < swtichCaseSelectionEndX &&
								defaultCaseEndY > swtichCaseSelectionStartY &&
								defaultCaseEndY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
						}	
						//   SwitchCase의 위로 붙기위해, SwitchCase의 오른쪽 아랫점이 붙는 영역에 속할 때 
						else if(checkSwitchCaseUpsign == NO && 
								selectionEndX > swtichCaseSelectionStartX &&
								selectionEndX < swtichCaseSelectionEndX &&
								defaultCaseEndY > swtichCaseSelectionStartY &&
								defaultCaseEndY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
						}	
					}
				}//*/


			 } // 기호가 붙을 기호가 SwitchCase일 때를 처리하는 로직 닫는 중괄호
			i++ ;
		}// while반복을 닫는 중괄호
	//}
}





	
/*
	함수이름 : CheckStickingFieldForMove
	설    명 : 움직이는 기호가 다른 기호에 붙는지 판단한다 ( 붙는 영역이 기호 외부가 아니다 )
	입    력 : Paper *paper, Long index, Long moveX( 이동을 시작한 위치와 현재 위치의 차이값X ), Long moveY(  이동을 시작한 위치와 현재 위치의 차이값Y )
	출    력 : void
	만 든 이 : i5
	특이사항 : 붙는 영역이 기호의 내부뿐이다, moveX값과 moveY값은 마우스버튼없에선 값이 0이다  // 움직일때, 미리보기 만들때 사용중
*/

void Sticker::CheckStickingFieldForMove ( Paper *paper, Select *select, Long index, Long moveX, Long moveY ) {
//======================================================================================마우스에 걸린 기호가 아니라 종이 위 기호들의 정보를 담는 변수들===================================================================
		// index기호가 붙을 종이 위 기호의 위치, 크기, 미들
			// 이 변수들로 붙을 영역을 설정한다
			// paper Length만큼 돌려서 확인하기 때문에 값은 반복제어변수가 변하면 함께 계속 변한다
 		Long stickingStartX ;
		Long stickingStartY ;
		Long stickingEndX ;
		Long stickingEndY ;
		Long stickingMiddleX ;
		Long stickingMiddleY ;


		//기호가 붙을 기호(종이 위에 있는 기호)의 힙데이터 주소를 담을 자동변수
		Symbol *symbol ; // checkSymbol
		





		// index기호가 SwitchCase외의 기호일 때 사용할 변수
		Long startX ;
		Long startY ;
		Long endX ;
		Long endY ;
		Long middleX ;
		Long middleY ;

		Symbol *indexSymbol = paper->GetAt( index ) ;

		// index기호가 SwitchCase일 때 사용할 변수 
		Long selectionStartX ;
		Long selectionStartY ;
		Long selectionEndX ;
		Long selectionEndY ;
		Long selectionMiddleX ;

		Long swtichCaseFalseEndX ;
		Long swtichCaseFalseEndY ;

		if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
		{
			selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() + moveX ;
			selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() + moveY ;
			selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() + moveX ;
			selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() + moveY  ;
			selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() + moveX ;

			swtichCaseFalseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() + moveX ;
			swtichCaseFalseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() + moveY  ;
		}
		else{
			startX = paper->GetAt( index )->GetStartPointX() + moveX ;
			startY = paper->GetAt( index )->GetStartPointY() + moveY  ;
			endX = paper->GetAt( index )->GetEndPointX() + moveX ;
			endY = paper->GetAt( index )->GetEndPointY() + moveY  ;
		}
		


		Long i = 0 ;
		while ( i < paper->GetLength()  && this->stickingField == -1 ) {


			// 종이 위의 기호가 선택된 기호인지 확인하는 로직 시작
			Long k = 0 ;
			Long tempSign = -1 ;
			while( k < select->GetSelectPaper()->GetLength() && tempSign == -1 )
			{
				Long selectIndex = select->GetSelectPaper()->GetAt( k ).GetSeletedSymbolIndex() ;
				if( i == selectIndex ) 
				{
					tempSign = 1 ;
				}
				k++ ;
			}// 종이 위의 기호가 선택된 기호인지 확인하는 로직 끝


			if( tempSign == -1 ) //tempSign = -1이면 종이 위 기호가 선택된 기호가 아니다
			{
				symbol = paper->GetAt( i ) ;
				stickingStartX = symbol->GetStartPointX () ;
				stickingStartY = symbol->GetStartPointY () ;
				stickingEndX = symbol->GetEndPointX () ;
				stickingEndY = symbol->GetEndPointY () ;
			}


			else  //tempSign = 1이면 종이 위 기호가 선택된 기호다
			{
				symbol = 0 ;
			}
			

			////	
			////
			////		   
			/// 종이 위의 기호가 Sequence일 때
			if( dynamic_cast<Sequence*>(symbol) && i != index )
			{
				
				Sequence *checkSequence =  static_cast<Sequence*>(symbol) ;

				// Sequence에 붙는 index기호가 Sequence거나 Selection이면
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					 dynamic_cast<Selection*>(paper->GetAt( index ))
					)
				{ 
					// 아래로 붙기 위해, 왼쪽 윗점이 순차의 붙는 영역에 속할 때
					if( checkSequence->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingStartY - 0 &&
						startY < stickingEndY + 0
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}
					// 아래로 붙기 위해, 오른쪽 윗점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->downSign == NO && 
							endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingStartY - 0 &&
							 startY < stickingEndY + 0 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}

					// 위로 붙기 위해, 왼쪽 아랫점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->upSign == NO &&
							 startX > stickingStartX &&
							 startX < stickingEndX &&
							 endY > stickingStartY - 0 &&
							 endY < stickingEndY + 0 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}
					// 위로 붙기 위해, 오른쪽 아랫점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->upSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 endY > stickingStartY - 0 &&
							 endY < stickingEndY + 0 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}
				}





				// Sequence에 붙는 index기호가 BeforeRepeat면
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					
					BeforeRepeat *indexBeforeRepeat =  static_cast<BeforeRepeat*>(paper->GetAt( index )) ;
					middleX = indexBeforeRepeat->GetMiddlePointX() + moveX  ;
					middleY = indexBeforeRepeat->GetMiddlePointY() + moveY  ;
					

					// 아래로 붙기 위해, 왼쪽 위점이 순차의 붙는 영역에 속할 때
					if( checkSequence->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingStartY - 0 &&
						startY < stickingEndY + 0
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}
					// 아래로 붙기 위해, 오른쪽 위의 점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->downSign == NO &&  
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingStartY - 0 &&
							 startY < stickingEndY + 0 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}

					// 아래로 붙기 위해, 오른쪽 중간점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->downSign == NO && 
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY + 40 > stickingStartY - 0 &&
							 startY + 40 < stickingEndY + 0 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}
					// 아래로 붙기 위해, 오른쪽 아랫점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->downSign == NO && 
							 middleX > stickingStartX &&
							 middleX < stickingEndX &&
							 middleY > stickingStartY - 0 &&
							 middleY < stickingEndY + 0 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}
					// 위로 붙기 위해, 왼쪽 아랫점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->upSign == NO &&
							 startX > stickingStartX &&
							 startX < stickingEndX &&
							 endY > stickingStartY - 0 &&
							 endY < stickingEndY + 0 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}

					// 위로 붙기 위해, 아랫쪽 중간점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->upSign == NO &&
							 startX + 40 > stickingStartX &&
							 startX + 40 < stickingEndX &&
							 endY > stickingStartY - 0 &&
							 endY < stickingEndY + 0 
							 )
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}
				
				}

				// Sequence에 붙는 기호가 AfterRepeat면
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
					// 아래로 붙기 위해, 왼쪽 위점이 순차의 붙는 영역에 속할 때
					if( checkSequence->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingStartY - 0 &&
						startY < stickingEndY + 0
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}

					// 아래로 붙기 위해, 왼쪽 위 중간점이 순차의 붙는 영역에 속할 때
					if( checkSequence->downSign == NO && 
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						startY > stickingStartY - 0 &&
						startY < stickingEndY + 0
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}

					// 위로 붙기 위해, 왼쪽 아랫점이 순차의 붙는 영역에 속할 때
					if( checkSequence->upSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingEndY + 0
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}

					// 위로 붙기 위해, 오른쪽 아랫점이 순차의 붙는 영역에 속할 때
					if( checkSequence->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingEndY + 0
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}

					// 위로 붙기 위해, 오른쪽 아래 중간점이 순차의 붙는 영역에 속할 때
					if( checkSequence->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY - 40 > stickingStartY - 0 &&
						endY - 40 < stickingEndY + 0
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}

					// 위로 붙기 위해, 오른쪽 아래 중간점이 순차의 붙는 영역에 속할 때
					if( checkSequence->upSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY - 0 &&
						middleY < stickingEndY + 0
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSequence->upSign = YES ;
					}
			}

			// Sequence에 붙는 기호가 SwitchCase일 때 
			if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
			{
				Long selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() + moveX ;
				Long selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() + moveY ;
				Long selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() + moveX ;
				Long selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() + moveY ;
				Long selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() + moveX ;

				Long firstCaseStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetStartPointX() + moveX ;
				Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() + moveY ;
				Long defaultCaseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointX() + moveX ;
				Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointY() + moveY ;


				// 아래로 붙기 위해, 왼쪽 위점이 순차의 붙는 영역에 속할 때
					if( checkSequence->downSign == NO && 
						selectionStartX > stickingStartX &&
						selectionStartX < stickingEndX &&
						selectionStartY > stickingStartY - 0 &&
						selectionStartY < stickingEndY + 0
						)
					{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSequence->downSign = YES ;
					}
					// 아래로 붙기 위해, 오른쪽 위점이 순차의 붙는 영역에 속할 때
					else if(checkSequence->downSign == NO &&  
							selectionEndX > stickingStartX &&
							selectionEndX < stickingEndX &&
							selectionStartY > stickingStartY - 0 &&
							selectionStartY < stickingEndY + 0
							)
						{
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSequence->downSign = YES ;
						}

					// 위로 붙기 위해, 왼쪽 아랫점이 순차의 붙는 영역에 속할 때
					else if( checkSequence->upSign == NO &&
							firstCaseStartX > stickingStartX &&
							firstCaseStartX < stickingEndX &&
							firstCaseEndY > stickingStartY - 0 &&
							firstCaseEndY < stickingEndY + 0
							)
						{
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSequence->upSign = YES ;
						}
					
					// 위로 붙기 위해, 중간 아랫점이 순차의 붙는 영역에 속할 때
					else if(checkSequence->upSign == NO && 
							defaultCaseEndX > stickingStartX &&
							defaultCaseEndX < stickingEndX &&
							defaultCaseEndY > stickingStartY - 0 &&
							defaultCaseEndY < stickingEndY + 0
							)
						{
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSequence->upSign = YES ;
						}
			}


	   }// Sequence에 기호가 붙을 때 처리 함수 닫는 중괄호



	   /////	
		////
		/// 종이 위의 기호가 Selection일 때
		if( dynamic_cast<Selection*>(symbol) && i != index  ){
			
			stickingMiddleX = (static_cast<Selection*>(symbol))->GetMiddlePointX() ;
			stickingMiddleY = (static_cast<Selection*>(symbol))->GetMiddlePointY() ;
			Selection *checkSelection = static_cast<Selection*>(symbol) ;
			// 선택구조에 위로 달라붙는 경우를 구조별로 추가한다 
				// 선택구조에 위로 달라붙는 구조가 순차이거나 선택일 때
			if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					dynamic_cast<Selection*>(paper->GetAt( index ))
				) {

					// TRUE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때 
					else if( checkSelection->trueSign == NO &&
								endX > stickingStartX &&
								endX < stickingMiddleX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +0  ){
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSelection->trueSign = YES ;
					}
					// FALSE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					else if(checkSelection->falseSign == NO &&
							startX > stickingMiddleX &&
							startX < stickingEndX &&
							startY > stickingStartY &&
							startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}
				// 위로 붙기 위해, 오른쪽 아랫점이 붙는 영역에 속할 때 
					if(	checkSelection->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
					// 위로 붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때 
					else if(	checkSelection->upSign == NO &&
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - 0 &&
							endY < stickingEndY ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkSelection->upSign = YES ;
					}
			}

				//선택구조에 위로 달라붙는 구조가 선반복일 때
			if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index ))) {

				middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
				middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
				
				// TRUE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						endX > stickingStartX &&
						endX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						endX > stickingStartX &&
						endX < stickingMiddleX &&
						startY + 40 > stickingStartY  &&
						startY + 40 < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 중간점이 붙는 영역에 속할 때 
					if( checkSelection->trueSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						middleY > stickingStartY  &&
						middleY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					
					// FALSE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					else if(checkSelection->falseSign == NO && 
							startX > stickingMiddleX &&
							startX < stickingEndX &&
							startY > stickingStartY &&
							startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}

					// FALSE쪽에 붙기 위해, 중간점이 붙는 영역에 속할 때 
					if( checkSelection->falseSign == NO &&
						middleX > stickingMiddleX &&
						middleX < stickingEndX &&
						middleY > stickingStartY  &&
						middleY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
					}




				// 위로 붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때 
				if(	checkSelection->upSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					endY > stickingStartY - 0 &&
					endY < stickingEndY ) {
						this->stickedIndex = i ;
						this->stickingField = 3 ;
					}
				// 위로 붙기 위해, 왼쪽 아래 중간점이 붙는 영역에 속할  때	
				else if(checkSelection->upSign == NO &&
						startX + 40 > stickingStartX &&
						startX + 40 < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
			}
				//선택구조에 위로 달라붙는 구조가 후반복일 때
			if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index ))) {

				middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
				middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;

					// TRUE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					if(  checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE쪽에 붙기 위해, 중간 윗점이 붙는 영역에 속할 때 
					else if(  checkSelection->trueSign == NO &&
								middleX > stickingStartX &&
								middleX < stickingMiddleX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +0  ){
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSelection->trueSign = YES ;
					}
					// FALSE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
					if( checkSelection->falseSign == NO &&
						startX > stickingMiddleX &&
						startX < stickingEndX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
					}
					// FALSE쪽에 붙기 위해, 중간 윗점이 붙는 영역에 속할 때 
					else if( checkSelection->falseSign == NO &&
								middleX > stickingMiddleX &&
								middleX < stickingEndX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +0  ){
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}

				//위로 붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				if(	checkSelection->upSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					endY > stickingStartY - 0 &&
					endY < stickingEndY ) {
						this->stickedIndex = i ;
						this->stickingField = 3 ;
						checkSelection->upSign = YES ;
					}

				//위로 붙기 위해, 중간점이 붙는 영역에 속할 때
				else if( checkSelection->upSign == NO &&
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - 0 &&
							middleY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
				//위로 붙기 위해, 오른쪽 아랫점이 붙는 영역에 속할 때
				else if( checkSelection->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - 0 &&
							endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
				//위로 붙기 위해, 오른쪽 아래 중간점이 붙는 영역에 속할 때
				else if( checkSelection->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY - 40 > stickingStartY - 0 &&
							endY - 40 < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
			}


				
			// Selection에 붙는 기호가 SwitchCase일 때 
			if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
			{
				Long selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() + moveX ;
				Long selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() + moveY ;
				Long selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() + moveX ;
				Long selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() + moveY ;
				Long selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() + moveX ;

				Long firstCaseStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetStartPointX() + moveX ;
				Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() + moveY ;
				Long defaultCaseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointX() + moveX ;
				Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointY() + moveY ;


				// TRUE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때 
				if(  checkSelection->trueSign == NO &&
					selectionStartX > stickingStartX &&
					selectionStartX < stickingMiddleX &&
					selectionStartY > stickingStartY  &&
					selectionStartY < stickingMiddleY +0  ){
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkSelection->trueSign = YES ;
				}

				// FALSE쪽에 붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때  
				else if(checkSelection->falseSign == NO && 
						selectionStartX > stickingMiddleX &&
						selectionStartX < stickingEndX &&
				 		selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
				}
				// FALSE쪽에 붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때  
				else if(checkSelection->falseSign == NO && 
						selectionEndX > stickingMiddleX &&
						selectionEndX < stickingEndX &&
				 		selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
				}
				//위로 붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkSelection->upSign == NO &&
						firstCaseStartX > stickingStartX &&
						firstCaseStartX < stickingEndX &&
						firstCaseEndY > stickingStartY - 0 &&
						firstCaseEndY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
				}
				//위로 붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
				else if(checkSelection->upSign == NO && 
						defaultCaseEndX > stickingStartX &&
						defaultCaseEndX < stickingEndX &&
						defaultCaseEndY > stickingStartY - 0 &&
						defaultCaseEndY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
				}
			}
		}//Selection에 기호가 붙을 때 처리 함수 닫는 중괄호
			
		////
		////
		/// 종이 위의 기호가 BeforeRepeat일 때
		if( dynamic_cast<BeforeRepeat*>(symbol) && i != index  ){
			
			stickingMiddleX = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointX() ;
			stickingMiddleY = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointY() ;
			BeforeRepeat *checkBeforeRepeat = static_cast<BeforeRepeat*>(symbol) ;
			
			// 선반복구조에 안쪽으로 달라붙는 구조가 순차이거나 선택일 때
			if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					dynamic_cast<Selection*>(paper->GetAt( index ))
				) {

				// 선반복구조에 안쪽으로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}
			

				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
			}
		


		// BeforeRepeat에 붙는 기호가 BeforeRepeat면
			if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
			{ 
				middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
				middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
				
				// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY &&
						middleY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						middleY > stickingStartY &&
						middleY < stickingMiddleY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkBeforeRepeat->inSign = YES ;
				}
					// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO && 
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
					  	startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO &&  
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						startX > stickingStartX &&
					 	startX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}							
			}
			// BeforeRepeat에 붙는 기호가 AfterRepeat면
			if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
			{ 
				middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
				middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;


				// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 중간 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}

				// 선반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
					  	startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 중간 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						endX > stickingStartX &&
					 	endX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO &&  
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY - 0 &&
						middleY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}	
				// 선반복구조에 위로 달라붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						endX > stickingStartX &&
						endX < stickingEndX &&
						middleY > stickingStartY - 0 &&
						middleY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						startX > stickingStartX &&
						startX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}


			}
			// BeforeRepeat에 붙는 기호가 SwitchCase일 때 
			if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
			{
				Long selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() + moveX ;
				Long selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() + moveY ;
				Long selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() + moveX ;
				Long selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() + moveY ;
				Long selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() + moveX ;

				Long firstCaseStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetStartPointX() + moveX ;
				Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() + moveY ;
				Long defaultCaseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointX() + moveX ;
				Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointY() + moveY ;

					
				// 선반복구조에 안쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				if( checkBeforeRepeat->inSign == NO &&
					selectionStartX > stickingStartX &&
					selectionStartX < stickingEndX &&
					selectionStartY > stickingStartY &&
					selectionStartY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// 선반복구조에 안쪽으로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->inSign == NO &&
						selectionEndX > stickingStartX &&
						selectionEndX < stickingEndX &&
						selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkBeforeRepeat->inSign = YES ;
				}

				// 선반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO && 
						selectionStartX > stickingStartX &&
						selectionStartX < stickingMiddleX &&
					  	selectionStartY > stickingEndY - 20 &&
						selectionStartY < stickingEndY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// 선반복구조에 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->downSign == NO &&  
						selectionEndX > stickingStartX &&
						selectionEndX < stickingMiddleX &&
					  	selectionStartY > stickingEndY - 20 &&
						selectionStartY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}

				// 선반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						firstCaseStartX > stickingStartX &&
						firstCaseStartX < stickingEndX &&
						firstCaseEndY > stickingStartY - 0 &&
						firstCaseEndY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// 선반복구조에 위로 달라붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
				else if(checkBeforeRepeat->upSign == NO && 
						defaultCaseEndX > stickingStartX &&
						defaultCaseEndX < stickingEndX &&
						defaultCaseEndY > stickingStartY - 0 &&
						defaultCaseEndY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}

			}
		}//BeforeRepeat에 기호가 붙을 때 처리 함수 닫는 중괄호






			////
			////
			/// 종이 위의 기호가 AfterRepeat 일 때
			if( dynamic_cast<AfterRepeat*>(symbol) && i != index ){
			
				stickingMiddleX = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointX() ;
				stickingMiddleY = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointY() ;
				AfterRepeat *checkAfterRepeat = static_cast<AfterRepeat*>(symbol) ;
				// 후반복구조에 아래쪽으로 달라붙는 구조가 순차이거나 선택일 때
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					 dynamic_cast<Selection*>(paper->GetAt( index ))
					) {

					// 후반복구조에 아래쪽으로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					if(	checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래쪽으로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingMiddleY &&
							 startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;

					}
					// 후반복구조에 위로 달라붙기 위해, 오른쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}

					// 후반복구조에 안쪽 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO &&
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
				}

				// AfterRepeats에 붙는 기호가 BeforeRepeat면
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
					middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
				
					// 후반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					if( checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingMiddleY &&
							 startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if( checkAfterRepeat->downSign == NO && 
							 middleX > stickingStartX &&
							 middleX < stickingEndX &&
							 middleY > stickingMiddleY &&
							 middleY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 middleY > stickingMiddleY &&
							 middleY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// 후반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
				
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - 0 &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 오른쪽 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							middleY > stickingStartY - 0 &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}


				}//AfterRepeat에 기호가 붙을 때 처리 함수 닫는 중괄호


				// BeforeRepeat에 붙는 기호가 AfterRepeat면
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;

					// 후반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					if( checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 중간 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->downSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							startY > stickingMiddleY &&
							startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// 후반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 오른쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO &&
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - 0  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - 0  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							middleY > stickingStartY - 0  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 중간 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
				}


				if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
				{
					Long selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() + moveX ;
					Long selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() + moveY ;
					Long selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() + moveX ;
					Long selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() + moveY ;
					Long selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() + moveX ;

					Long firstCaseStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetStartPointX() + moveX ;
					Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() + moveY ;
					Long defaultCaseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointX() + moveX ;
					Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases( static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount() )->GetEndPointY() + moveY ;

					// 후반복구조에 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					if( checkAfterRepeat->downSign == NO &&
						selectionStartX > stickingStartX &&
						selectionStartX < stickingEndX &&
						selectionStartY > stickingMiddleY &&
						selectionStartY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// 후반복구조에 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->downSign == NO && 
							selectionEndX > stickingStartX &&
							selectionEndX < stickingEndX &&
							selectionStartY > stickingMiddleY &&
							selectionStartY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// 후반복구조에 위로 달라붙기 위해, 왼쪽 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO &&
							firstCaseStartX > stickingStartX &&
							firstCaseStartX < stickingEndX &&
							firstCaseEndY > stickingStartY - 0  &&
							firstCaseEndY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// 후반복구조에 위로 달라붙기 위해, 중간 아랫점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->upSign == NO &&
							defaultCaseEndX > stickingStartX &&
							defaultCaseEndX < stickingEndX &&
							defaultCaseEndY > stickingStartY - 0  &&
							defaultCaseEndY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}

					// 후반복구조에 안쪽 아래로 달라붙기 위해, 왼쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							selectionStartX > stickingStartX &&
							selectionStartX < stickingEndX &&
							selectionStartY > stickingStartY - 0 &&
							selectionStartY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// 후반복구조에 안쪽 아래로 달라붙기 위해, 오른쪽 윗점이 붙는 영역에 속할 때
					else if(checkAfterRepeat->inSign == NO && 
							selectionEndX > stickingStartX &&
							selectionEndX < stickingEndX &&
							selectionStartY > stickingStartY - 0 &&
							selectionStartY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
				
				
				}



			 } // 기호가 붙을 기호가 AfterRepeat일 때를 처리하는 로직 닫는 중괄호


			 //
			 ///
			 ///
			 // 종이 위의 기호가 SwitchCase 일 때

			 if( dynamic_cast<SwitchCase*>(symbol) && i != index )
			 {
				Long swtichCaseSelectionStartX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetStartPointX() + moveX ;
				Long swtichCaseSelectionStartY = static_cast<SwitchCase*>(symbol)->GetSelection()->GetStartPointY() + moveY ;
				Long swtichCaseSelectionEndX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetEndPointX() + moveX ;
				Long swtichCaseSelectionEndY = static_cast<SwitchCase*>(symbol)->GetSelection()->GetEndPointY() + moveY ;

				Long swtichCaseFalseStartX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetMiddlePointX() + moveX ;
				Long swtichCaseFalseStartY = static_cast<SwitchCase*>(symbol)->GetSelection()->GetMiddlePointY() + moveY ;
				Long swtichCaseFalseEndX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetEndPointX() + moveX ;
				Long swtichCaseFalseEndY = static_cast<SwitchCase*>(symbol)->GetCases(0)->GetEndPointY() + moveY ;

				SwitchCase *checkSwitchCase = static_cast<SwitchCase*>(symbol) ;
				Long checkSwitchCaseUpsign = checkSwitchCase->upSign ;
				Long checkSwitchFalseSign = checkSwitchCase->falseSign ;
							
				
				// SwitchCase에 붙는 기호가 Sequence 일 때
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) )
				{ 
						//  SwitchCase의 특정 case 아래로 붙기위해, Sequence나 Selection 오른쪽 윗점이 붙는 영역에 속할 때//위의 가로길이 중간 점이 붙는 영역에 속할 때 
						Long j = 0 ;
						while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
						{
							Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
							Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
							Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
							Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;
							Long checkCaseDownSign = checkSwitchCase->GetCases( j )->downSign ; // checkCaseDownSign == NO &&

							if( checkCaseDownSign == NO &&
								startX  > caseStartX && //startX + ( ( endX - startX )/2 ) > caseStartX &&
								startX < caseEndX && //startX + ( ( endX - startX )/2 ) < caseEndX &&
								startY > caseStartY &&
								startY < caseEndY )
							{
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								this->stickedCase = j ;
								checkSwitchCase->GetCases( j )->downSign = YES ;
							}
							j++ ;
						}

						if( this->stickedCase == -1 ){
								
							//   SwitchCase의 위로 붙기위해, Sequence나 Selection의 왼쪽 아랫점이 붙는 영역에 속할 때 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
							}
							//   SwitchCase의 위로 붙기위해, Sequence나 Selection의 오른쪽 아랫점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO &&
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 FALSE쪽 아래로 붙기 위해, Sequence 오른쪽 윗점이 붙는 영역에 속할 때 //가로길이 중간점이 붙는 영역에 속할 때 
							else if(    checkSwitchCase->falseSign == NO &&
										startX > swtichCaseFalseStartX && //startX + ( ( endX - startX )/2 ) > swtichCaseFalseStartX &&
										startX < swtichCaseFalseEndX && //startX + ( ( endX - startX )/2 ) < swtichCaseFalseEndX &&
										startY > swtichCaseFalseStartY - 80 &&
										startY < swtichCaseFalseEndY ) 
							{
											this->stickedIndex = i ;
											this->stickingField = 3 ;
											checkSwitchCase->falseSign = YES ;						
							}
							//   SwitchCase의 FALSE쪽 아래로 붙기 위해, Sequence 왼쪽 윗점이 붙는 영역에 속할 때 
							else if(	checkSwitchCase->falseSign == NO &&
										startX > swtichCaseFalseStartX &&
										startX < swtichCaseFalseEndX &&
										startY > swtichCaseFalseStartY - 80 &&
										startY < swtichCaseFalseEndY ) 
							{
											this->stickedIndex = i ;
											this->stickingField = 3 ;
											checkSwitchCase->falseSign = YES ;						
							}
							//   SwitchCase의 FALSE쪽 아래로 붙기 위해, Sequence 오른쪽 윗점이 붙는 영역에 속할 때 
							else if(	checkSwitchCase->falseSign == NO &&
										endX > swtichCaseFalseStartX &&
										endX < swtichCaseFalseEndX &&
										startY > swtichCaseFalseStartY - 80 &&
										startY < swtichCaseFalseEndY ) 
							{
											this->stickedIndex = i ;
											this->stickingField = 3 ;
											checkSwitchCase->falseSign = YES ;
							}

						}
				}// // SwitchCase에 붙는 기호가 Sequence일 때를 처리하는 로직 닫는 중괄호


					else if(	 dynamic_cast<Selection*>(paper->GetAt( index )) )
					{ 
							//  SwitchCase의 특정 case 아래로 붙기위해, Sequence나 Selection 오른쪽 윗점이 붙는 영역에 속할 때//위의 가로길이 중간 점이 붙는 영역에 속할 때 
						Long j = 0 ;
						while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
						{
							Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
							Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
							Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
							Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;
							Long checkCaseDownSign = checkSwitchCase->GetCases( j )->downSign ; // checkCaseDownSign == NO &&

							if( checkCaseDownSign == NO &&
								startX  > caseStartX && //startX + ( ( endX - startX )/2 ) > caseStartX &&
								startX < caseEndX && //startX + ( ( endX - startX )/2 ) < caseEndX &&
								startY > caseStartY &&
								startY < caseEndY )
							{
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								this->stickedCase = j ;
								checkSwitchCase->GetCases( j )->downSign = YES ;
							}
							j++ ;
						}

						if( this->stickedCase == -1 ){
								
							//   SwitchCase의 위로 붙기위해, Sequence나 Selection의 왼쪽 아랫점이 붙는 영역에 속할 때 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
							}
							//   SwitchCase의 위로 붙기위해, Sequence나 Selection의 오른쪽 아랫점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO &&
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
						}
					}// // SwitchCase에 붙는 기호가 Selection일 때를 처리하는 로직 닫는 중괄호


					// SwitchCase에 붙는 기호가 BeforeRepeat면
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
					middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
					
					//  SwitchCase의 특정 case 아래로 붙기위해, BeforeRepeat 오른쪽 윗점이 붙는 영역에 속할 때 //위의 가로길이 중간 점이 붙는 영역에 속할 때 
					Long j = 0 ;
					while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
					{
						Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
						Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
						Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
						Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;
						Long checkCaseDownSign = checkSwitchCase->GetCases( j )->downSign ; // checkCaseDownSign == NO &&
						if( checkCaseDownSign == NO &&
							startX > caseStartX &&//startX + ( ( endX - startX )/2 ) > caseStartX &&
							startX < caseEndX && //startX + ( ( endX - startX )/2 ) < caseEndX &&
							startY > caseStartY &&
							startY < caseEndY )
						{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							this->stickedCase = j ;
							checkSwitchCase->GetCases( j )->downSign = YES ;
						}
						j++ ;
		
					}

					if( this->stickedCase == -1 )
					{
							//   SwitchCase의 위로 붙기위해, BeforeRepeat의 왼쪽 아랫점이 붙는 영역에 속할 때 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 위로 붙기위해, BeforeRepeat의 오른쪽 아랫점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO && 
									middleX > swtichCaseSelectionStartX &&
									middleX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}	
					}
				}// SwitchCase에 붙는 기호가 BeforeRepeat일 때를 처리하는 로직닫는 중괄호



				// SwitchCase에 붙는 기호가 AfterRepeat면
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
					
					//  SwitchCase의 특정 case 아래로 붙기위해, AfterRepeat 오른쪽 윗점이 붙는 영역에 속할 때//위의 가로길이 중간 점이 붙는 영역에 속할 때 
					Long j = 0 ;
					while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
					{
						Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
						Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
						Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
						Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;
						Long checkCaseDownSign = checkSwitchCase->GetCases( j )->downSign ; // checkCaseDownSign == NO &&

						if( checkCaseDownSign == NO &&
							startX > caseStartX &&//startX + ( ( middleX - startX )/2 ) > caseStartX &&
							startX < caseEndX && //startX + ( ( middleX - startX )/2 ) < caseEndX &&
							startY > caseStartY &&
							startY < caseEndY )
						{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							this->stickedCase = j ;
							checkSwitchCase->GetCases( j )->downSign = YES ;
						}
						j++ ;
		
					}
					if( this->stickedCase == -1 )
					{
							//   SwitchCase의 위로 붙기위해, AfterRepeat의 왼쪽 아랫점이 붙는 영역에 속할 때 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 위로 붙기위해, AfterRepeat의 오른쪽 아랫점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO && 
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 위로 붙기위해, AfterRepeat의 미들점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO &&
									middleX > swtichCaseSelectionStartX &&
									middleX < swtichCaseSelectionEndX &&
									middleY > swtichCaseSelectionStartY &&
									middleY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase의 위로 붙기위해, AfterRepeat의 오른쪽 미들점이 붙는 영역에 속할 때 
							else if(checkSwitchCaseUpsign == NO &&
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									middleY > swtichCaseSelectionStartY &&
									middleY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
					}


				}//  SwitchCase에 붙는 기호가 AfterRepeat일 때를 처리하는 로직 닫는 중괄호
				
				 // SwitchCase에 붙는 기호가 SwitchCase면
				if(  dynamic_cast<SwitchCase*>(paper->GetAt( index )) )
				{ 
					/*
					 selectionStartX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointX() ;
					 selectionStartY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetStartPointY() ;
					 selectionEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
					 selectionEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointY() ;
					 selectionMiddleX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetMiddlePointX() ;

					 swtichCaseFalseEndX = static_cast<SwitchCase*>(paper->GetAt( index ))->GetSelection()->GetEndPointX() ;
					 swtichCaseFalseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
					 //*/
					//  SwitchCase의 특정 case 아래로 붙기위해, AfterRepeat 위의 가로길이 중간 점이 붙는 영역에 속할 때 
					Long j = 0 ;
					while( j < static_cast<SwitchCase*>(symbol)->GetLength() && this->stickedCase == -1 )
					{
						Long caseStartX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointX() ;
						Long caseStartY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetStartPointY() ; 
						Long caseEndX = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointX() ;
						Long caseEndY = static_cast<SwitchCase*>(symbol)->GetCases(j)->GetEndPointY() ;

						
						if(
							selectionStartX //+ ( ( middleX - startX )/2 ) 
							> caseStartX &&
							selectionStartX //+ ( ( middleX - startX )/2 ) 
							< caseEndX &&
							selectionStartY > caseStartY &&
							selectionStartY < caseEndY )
						{
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							this->stickedCase = j ; //무조건 스위치케이스는 아래 case에 붙을 때는 첫번째 case에 맞춘다

							
						}
						j++ ;
		
					}
				
					if( this->stickedCase == -1 )
					{
						// SwitchCase 왼쪽 아랫점 Y좌표, defaultSequence 아랫점 Y좌표
						Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
						Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount())->GetEndPointY() ;
						//  SwitchCase의 위로 붙기위해, SwitchCase의 왼쪽 아랫점이 붙는 영역에 속할 때 
						if( checkSwitchCaseUpsign == NO &&
							selectionStartX > swtichCaseSelectionStartX &&
							selectionStartX < swtichCaseSelectionEndX &&
							firstCaseEndY > swtichCaseSelectionStartY &&
							firstCaseEndY < swtichCaseSelectionEndY ){
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSwitchCase->upSign = YES ;
						}
						//   SwitchCase의 위로 붙기위해, SwitchCase의 중간 아랫점이 붙는 영역에 속할 때 
						else if(checkSwitchCaseUpsign == NO && 
								selectionMiddleX > swtichCaseSelectionStartX &&
								selectionMiddleX < swtichCaseSelectionEndX &&
								defaultCaseEndY > swtichCaseSelectionStartY &&
								defaultCaseEndY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
						}	
						//   SwitchCase의 위로 붙기위해, SwitchCase의 오른쪽 아랫점이 붙는 영역에 속할 때 
						else if(checkSwitchCaseUpsign == NO && 
								selectionEndX > swtichCaseSelectionStartX &&
								selectionEndX < swtichCaseSelectionEndX &&
								defaultCaseEndY > swtichCaseSelectionStartY &&
								defaultCaseEndY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
						}	
					}
				}//*/


			 } // 기호가 붙을 기호가 SwitchCase일 때를 처리하는 로직 닫는 중괄호
			i++ ;
		}// while반복을 닫는 중괄호
	//}
}



/*
	함수이름 : GetInfo
	설    명 : 기호가 다른 기호에 붙을 때 필요한 위치와 크기 정보를 구한다
	입    력 : Paper *paper, Long stickedIndex(기호가 붙을 기호의 첨자), Long stickingField(붙는 영역에 대한 정보), Long oldIndex
	출    력 : void ( Sticker의 속성 startX, startY, endX, endY 값들에다가 붙일 때의 위치, 크기를 저장 )
	만 든 이 : i5
*/
void Sticker::GetInfo ( Paper *paper, Long stickedIndex, Long stickingField, Long oldIndex ){
	 
	Symbol *symbol = paper->GetAt( stickedIndex ) ; // 기호가 붙는 기호
	Symbol *oldSymbol = paper->GetAt( oldIndex ) ; // 기호에 붙는 기호
	
	
	//Sequence
	if( dynamic_cast<Sequence*>(symbol) )
	{
		if( dynamic_cast<SwitchCase*>(oldSymbol) ){
			SwitchCase *switchCase = static_cast<SwitchCase*>( oldSymbol ) ;
		
				 if( stickingField == 1 ){
					startX = symbol->GetStartPointX() ;
					startY = symbol->GetEndPointY() ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }
				  else if( stickingField == 2 ){
					startX = symbol->GetStartPointX() ;
					startY = symbol->GetStartPointY() - ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }
				  

			 
		}
		else{
			if( stickingField == 1 ){
				 startX = symbol->GetStartPointX() ;
				 startY = symbol->GetEndPointY() ;
				 endX = symbol->GetEndPointX() ;
				 endY = symbol->GetEndPointY() + ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
			}
			else if( stickingField == 2 ){
				 startX = symbol->GetStartPointX() ;
				 startY = symbol->GetStartPointY() - ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
				 endX = symbol->GetEndPointX() ;
				 endY = symbol->GetStartPointY() ;
			}
		}
	}



	//Selection
	if( dynamic_cast<Selection*>(symbol) ){
		if( dynamic_cast<SwitchCase*>(oldSymbol) ){
			SwitchCase *switchCase = static_cast<SwitchCase*>( oldSymbol ) ;
				
			
				 if( stickingField == 1 ){
					startX = symbol->GetStartPointX() ;
					startY = (static_cast<Selection*>(symbol))->GetMiddlePointY() ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }
				  else if( stickingField == 2 ){
					startX = (static_cast<Selection*>(symbol))->GetMiddlePointX() ;
					startY = (static_cast<Selection*>(symbol))->GetMiddlePointY() ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }
				else if( stickingField == 3 ){
					startX = symbol->GetStartPointX() ;
					startY = symbol->GetStartPointY() - ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }

			 
		}
		else{
			if( stickingField == 1 ){
				 startX = symbol->GetStartPointX() ;
				 startY = (static_cast<Selection*>(symbol))->GetMiddlePointY() ;
				 endX = (static_cast<Selection*>(symbol))->GetMiddlePointX() ;
				 endY = (static_cast<Selection*>(symbol))->GetMiddlePointY() + ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
			}
			else if( stickingField == 2 ){
				startX = (static_cast<Selection*>(symbol))->GetMiddlePointX() ;
				startY = (static_cast<Selection*>(symbol))->GetMiddlePointY() ;
				endX = symbol->GetEndPointX() ;
				endY = (static_cast<Selection*>(symbol))->GetMiddlePointY() + ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
			}
			else if( stickingField == 3 ){
				startX = symbol->GetStartPointX() ;
				startY = symbol->GetStartPointY() - ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
				endX = symbol->GetEndPointX() ;
				endY = symbol->GetStartPointY() ;
			}
		}
	}



	// BeforeRepeat
	if( dynamic_cast<BeforeRepeat*>(symbol) ){
		if( dynamic_cast<SwitchCase*>(oldSymbol) ){
			SwitchCase *switchCase = static_cast<SwitchCase*>( oldSymbol ) ;
				
			
				 if( stickingField == 1 ){
					startX = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointX() ;
					startY = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointY() ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }
				  else if( stickingField == 2 ){
					startX = symbol->GetStartPointX() ;
					startY = symbol->GetEndPointY() ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }
				else if( stickingField == 3 ){
					startX = symbol->GetStartPointX() ;
					startY = symbol->GetStartPointY() - ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }

			 
		}
		else{
			if( stickingField == 1 ){
				startX = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointX() ;
				startY = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointY() ;
				endX = symbol->GetEndPointX() ;
				endY = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointY() + ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
			}
			else if( stickingField == 2 ){
				startX = symbol->GetStartPointX() ;
				startY = symbol->GetEndPointY() ;
				endX = symbol->GetEndPointX() ;
				endY = symbol->GetEndPointY() + ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
			}
			else if( stickingField == 3 ){
				startX = symbol->GetStartPointX() ;
				startY = symbol->GetStartPointY() - ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
				endX = symbol->GetEndPointX() ;
				endY = symbol->GetStartPointY() ;
			}
		}
	}

		
	//AfterRepeat
	if( dynamic_cast<AfterRepeat*>(symbol) ){
		if( dynamic_cast<SwitchCase*>(oldSymbol) ){
			SwitchCase *switchCase = static_cast<SwitchCase*>( oldSymbol ) ;
			
				 if( stickingField == 1 ){
					startX = symbol->GetStartPointX() ;
					startY = symbol->GetEndPointY() ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }
				  else if( stickingField == 2 ){
					startX = symbol->GetStartPointX() ;
					startY = symbol->GetStartPointY() - ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }
				else if( stickingField == 3 ){
					startX = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointX() ;
					startY = symbol->GetStartPointY() ;
					endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
					endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				 }

			 
		}
		else{
			if( stickingField == 1 ){
				startX = symbol->GetStartPointX() ;
				startY = symbol->GetEndPointY() ;
				endX = symbol->GetEndPointX() ;
				endY = symbol->GetEndPointY() + ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
			}
			else if( stickingField == 2 ){
				startX = symbol->GetStartPointX() ;
				startY = symbol->GetStartPointY() - ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
				endX = symbol->GetEndPointX() ;
				endY = symbol->GetStartPointY() ;
			}
			else if( stickingField == 3 ){
				startX = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointX() ;
				startY = symbol->GetStartPointY() ;
				endX = symbol->GetEndPointX() ;
				endY = symbol->GetStartPointY() + ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
			}
		}
	}
	
	//SwitchCase 
	if( dynamic_cast<SwitchCase*>(symbol) )
	{
		SwitchCase *stickedSwitchCase =  static_cast<SwitchCase*>( symbol ) ;
		SwitchCase *switchCase = static_cast<SwitchCase*>( oldSymbol ) ;
				
		 if(dynamic_cast<SwitchCase*>(oldSymbol))
		 {
			 if( stickingField == 1 ){
				startX = static_cast<SwitchCase*>(symbol)->GetCases( this->stickedCase )->GetStartPointX() ;
				startY = static_cast<SwitchCase*>(symbol)->GetCases( this->stickedCase )->GetEndPointY() ;
				endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
				endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
			 }
			  else if( stickingField == 2 ){
				startX = stickedSwitchCase->GetSelection()->GetStartPointX() ;
				startY = stickedSwitchCase->GetSelection()->GetStartPointY() - ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;
				endX = stickedSwitchCase->GetSelection()->GetEndPointX() ;
				endY = stickedSwitchCase->GetSelection()->GetStartPointY() ;
			 }


		 }
		 else
		 {
			if( stickingField == 1 ){
				//특정 case에 붙을 때, 
					//그 case의 가로폭을 맞춘다.
				startX = static_cast<SwitchCase*>(symbol)->GetCases( this->stickedCase )->GetStartPointX() ;
				startY = static_cast<SwitchCase*>(symbol)->GetCases( this->stickedCase )->GetEndPointY() ;
				endX = static_cast<SwitchCase*>(symbol)->GetCases( this->stickedCase )->GetEndPointX()  ;
				endY = static_cast<SwitchCase*>(symbol)->GetCases( this->stickedCase )->GetEndPointY()  + ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;

			}
		
			else if( stickingField == 2 ){
				startX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetStartPointX() ;
				startY = static_cast<SwitchCase*>(symbol)->GetSelection()->GetStartPointY() - ( oldSymbol->GetEndPointY() - oldSymbol->GetStartPointY() ) ;
				endX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetEndPointX() ;
				endY = static_cast<SwitchCase*>(symbol)->GetSelection()->GetStartPointY() ;
			}
		
			else if( stickingField == 3 ){
				Long lastCaseIndex =  static_cast<SwitchCase*>(symbol)->GetColumnCount() ;
	
				startX = static_cast<SwitchCase*>(symbol)->GetCases( lastCaseIndex )->GetEndPointX()  ; 
					//static_cast<SwitchCase*>(symbol)->GetSelection()->GetMiddlePointX() ; //
				startY = static_cast<SwitchCase*>(symbol)->GetSelection()->GetMiddlePointY() ;
				endX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetEndPointX() ;
				endY = static_cast<SwitchCase*>(symbol)->GetCases( 0 )->GetEndPointY() ;
			}
		//*/
		}

	}
	 this->stickedIndex = -1 ;
	 this->stickingField = -1 ;

}
	

/*
	함수이름 : StickTo
	설    명 : 기호를 다른 기호에 붙인다
	입    력 : Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex
	출    력 : void
	만 든 이 : i5
*/
Long Sticker::StickTo ( Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex ) {
	
	Symbol *symbol ;
	if ( type.compare("Sequence") == 0 ) {
		symbol = new Sequence ( startX , startY , endX, endY, expression ) ;
	}
	else if ( type.compare("BeforeRepeat") == 0 ) {
		symbol = new BeforeRepeat ( startX , startY , endX, endY, expression ) ;
	}
	else if ( type.compare("AfterRepeat") == 0 ) {
		symbol = new AfterRepeat ( startX , startY , endX, endY, expression ) ;
	}
	else if ( type.compare("Selection") == 0 ) {
	//미들좌표를 다른 좌표들의 이동에 맞춰서 변화시켜줘야한다
	//비율을 활용한다
		Selection *oldSymbol = static_cast<Selection*>( paper->GetAt( oldIndex ) ) ; // 미들좌표를 읽기위해서 변환
		double trueWidth = oldSymbol->GetMiddlePointX() - oldSymbol->GetStartPointX() ; // 비율을 구하기 위해서 trueWidth 구한다
		double falseWidth = oldSymbol->GetEndPointX() - oldSymbol->GetMiddlePointX() ; // 비율을 구하기 위해서 falseWidth 구한다
		double width = this->endX - this->startX ; // 붙였을 때의 가로길이
		double rateWidth = ( width * ( trueWidth / ( trueWidth + falseWidth ) ) ) ; // 비율로 길이를 구한다
		Selection *temp = new Selection ( startX , startY , endX, endY, expression ) ; // 우선 이동된 좌표로 기호를 그린다
		
		symbol = new Selection ( // 미들 좌표가 이동전 기호와 같은 비율로 그려진 기호를 그린다
					temp->GetStartPointX(), 
					temp->GetStartPointY(), 
					temp->GetEndPointX(), 
					temp->GetEndPointY(), 
//					temp->GetExpressionStartPointX(), 
//					temp->GetExpressionStartPointY(), 
//					temp->GetExpressionEndPointX(), 
//					temp->GetExpressionEndPointY(), 
					temp->GetStartPointX() + rateWidth,
					static_cast<Selection*>(temp)->GetMiddlePointY(),
					temp->GetExpression() ) ;
		delete temp ; // 임시로 그린 기호 할당 해제

	}
	else if ( type.compare("SwitchCase") == 0 ) {
		SwitchCase *oldSymbol = static_cast<SwitchCase*>( paper->GetAt( oldIndex ) ) ;
		Long columnCount = oldSymbol->GetColumnCount() ;
		wstring expression = oldSymbol->GetExpression() ;
		wstring *caseExpressions = new wstring[ oldSymbol->GetLength()] ;
		
		for(Long i = 0 ; i < oldSymbol->GetLength() ; i++ ){
			caseExpressions[i] = oldSymbol->GetCases(i)->GetExpression() ;
		}
		symbol =  new SwitchCase ( columnCount, startX , startY , endX, endY , expression, caseExpressions) ;
	}

	delete paper->GetAt( oldIndex ) ; // 기존 symbols의 기호 할당 해제
	
	//새로 붙여 그린 기호를 Paper::ModifyTo(~) 호출해서 넣기
	 paper->ModifyTo( symbol, oldIndex ) ;
	//*/
	 return oldIndex ;


}

/*
	함수이름 : SearchTop
	설    명 : 기호들을 붙일 때, 선택된 기호들 중 제일 위에 위치한 기호를 찾는다
	입    력 : Paper *paper, Select *select
	출    력 : topIndex
	만 든 이 : i5
*/
void Sticker::SearchTopBottom( Paper *paper, Select *select ) // 다중 선택된 기호들 중 제일 위의 기호의 첨자를 구한다
{

	this->topIndex = select->GetSelectPaper()->GetAt(0).GetSeletedSymbolIndex() ;
	this->bottomIndex = select->GetSelectPaper()->GetAt(0).GetSeletedSymbolIndex() ;


	Long selectPaperLength = select->GetSelectPaper()->GetLength() ;
	for( Long i = 0 ; i < selectPaperLength ; i++ )
	{
		Long selectedIndex = select->GetSelectPaper()->GetAt(i).GetSeletedSymbolIndex() ;
		Symbol *symbol = paper->GetAt( selectedIndex ) ;  
		Symbol *topSymbol =  paper->GetAt(this->topIndex) ;
		Symbol *bottomSymbol = paper->GetAt( this->bottomIndex ) ;

		// top 정하기
		if( dynamic_cast<SwitchCase*>(symbol) || dynamic_cast<SwitchCase*>(topSymbol) ){ //하나라도 SwitchCase일 때 
			if( dynamic_cast<SwitchCase*>(symbol) ){
				SwitchCase *switchCase = static_cast<SwitchCase*>(symbol) ;
				if( switchCase->GetSelection()->GetStartPointY() <  topSymbol->GetStartPointY() ){
					this->topIndex = selectedIndex ;
				}
			}

			else if( dynamic_cast<SwitchCase*>(topSymbol) ) {
				SwitchCase *switchCase = static_cast<SwitchCase*>(topSymbol) ;
				if( symbol->GetStartPointY() <  switchCase->GetSelection()->GetStartPointY() ){
					this->topIndex = selectedIndex ;
				}
			}
		
		}
		else{ // 둘 다  SwitchCase 아닐 때 
			if( symbol->GetStartPointY() <  topSymbol->GetStartPointY() ){
				this->topIndex = selectedIndex ;
			}
		}

		// bottom 정하기
		if( dynamic_cast<SwitchCase*>(symbol) || dynamic_cast<SwitchCase*>(bottomSymbol) ){ //하나라도 SwitchCase일 때 
			if( dynamic_cast<SwitchCase*>(symbol) ){
				SwitchCase *switchCase = static_cast<SwitchCase*>(symbol) ;
				if( switchCase->GetSelection()->GetStartPointY() >  bottomSymbol->GetStartPointY() ){
					this->bottomIndex = selectedIndex ;
				}
			}

			else if( dynamic_cast<SwitchCase*>(bottomSymbol) ) {
				SwitchCase *switchCase = static_cast<SwitchCase*>(bottomSymbol) ;
				if( symbol->GetStartPointY()  >  switchCase->GetSelection()->GetStartPointY() ){
					this->bottomIndex = selectedIndex ;
				}
				
			}
		
		}
		else{ // 둘 다  SwitchCase 아닐 때
			if( symbol->GetStartPointY() > bottomSymbol->GetStartPointY() ) {
				this->bottomIndex = selectedIndex ;
			}
		}
	}
	// 발견된 버그 수정
		// 후반복구조의 안쪽에 붙은 함수가 top기호가 되는 것 수정
	Long sign = -1 ; //topIndex가 바뀌면 1이되어서 반복구조를 탈출하게 한다
	Long j = 0 ;
	while(  j < select->GetSelectPaper()->GetLength()  && sign == -1 )
	{
		Long topStartX = paper->GetAt( this->topIndex )->GetStartPointX() ;
		Long topStartY = paper->GetAt( this->topIndex )->GetStartPointY() ;

		Long selectedIndex = select->GetSelectPaper()->GetAt( j ).GetSeletedSymbolIndex() ;
		Symbol *tempSymbol = paper->GetAt( selectedIndex ) ;
		if( dynamic_cast< AfterRepeat* >( tempSymbol ) )
		{

			Long afterRepeatMiddleX = static_cast< AfterRepeat* >(tempSymbol)->GetMiddlePointX() ;
			Long afterRepeatStartY = static_cast< AfterRepeat* >(tempSymbol)->GetStartPointY() ;
			if( afterRepeatMiddleX == topStartX &&
				afterRepeatStartY == topStartY )
			{
				this->topIndex = selectedIndex ;
				sign = 1 ;
			}

		}
		j++ ;
	}

}
	

/*
	함수이름 : GetGap
	설    명 : 기호들을 붙일 때, 기호들의 위치가 이동해야 하는  변화량과 크기의 변화량을 구한다 
	입    력 : Paper *paper, Long oldIndex 
	출    력 : void
	만 든 이 : i5
*/
void Sticker::GetGap( Paper *paper, Long oldIndex  ) {// 위치좌표의 x축,y축을 이동 시킬 거리를 구한다
	// preStartX, preStartY는 oldIndex 값
	// startX, startY는  stickedIndex값

	Long preStartX ;
	Long preStartY ;
	Long preEndX ;
	Symbol *oldSymbol = ( paper->GetAt( oldIndex ) ) ;
	if( dynamic_cast<SwitchCase*>(oldSymbol) ){
		SwitchCase *switchCase = static_cast<SwitchCase*>(oldSymbol) ;
		preStartX = switchCase->GetSelection()->GetStartPointX() ;
		preStartY = switchCase->GetSelection()->GetStartPointY() ;
		preEndX = switchCase->GetSelection()->GetEndPointX() ;
	}
	else{
		preStartX = ( paper->GetAt( oldIndex ) )->GetStartPointX() ;
		preStartY = ( paper->GetAt( oldIndex ) )->GetStartPointY() ;
		preEndX = ( paper->GetAt( oldIndex ) )->GetEndPointX() ;
	}


	this->startGapX = preStartX - this->startX ;
	this->startGapY = preStartY - this->startY ;

	// 붙을 때 붙이면서 생기는 크기 차이를 구하는 로직
	Long preWidth =  preEndX - preStartX ;
	Long stickedWidth = (this->endX - this->startX) ;
	this->changingWidth = 0 ;//stickedWidth - preWidth ; //크기 유지해서 다중붙이기.
}


/*
	함수이름 : StickBundleTo
	설    명 : 기호들을 붙인다
	입    력 : Paper *paper, Select *select, Long startGapX, Long startGapY
	출    력 : void
	만 든 이 : i5
*/
void  Sticker::StickBundleTo( Paper *paper, Select *select, Long startGapX, Long startGapY ) {// 다중 선택된 기호들을 붙인다


	Long selectPaperLength = select->GetSelectPaper()->GetLength() ;
	for( Long i = 0 ; i < selectPaperLength ; i++ ) {
		Long selectedIndex = select->GetSelectPaper()->GetAt(i).GetSeletedSymbolIndex() ;
		Symbol *symbol = paper->GetAt( selectedIndex ) ;  
		Symbol *stcikingSymbol ;

			// 위치를 변경한다
			if( dynamic_cast< Sequence * > ( symbol ) )	{
				stcikingSymbol = new Sequence ( 
					symbol->GetStartPointX() - this->startGapX  , 
					symbol->GetStartPointY() - this->startGapY, 
					symbol->GetEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetEndPointY() - this->startGapY, 
					symbol->GetExpressionStartPointX() - this->startGapX  , 
					symbol->GetExpressionStartPointY() - this->startGapY, 
					symbol->GetExpressionEndPointX() - this->startGapX  + this->changingWidth, 
					symbol->GetExpressionEndPointY() - this->startGapY, 
					symbol->GetExpression() );
			}

			else if( dynamic_cast< BeforeRepeat * > ( symbol ) )	{
				stcikingSymbol = new BeforeRepeat ( 
					symbol->GetStartPointX() - this->startGapX  , 
					symbol->GetStartPointY() - this->startGapY, 
					symbol->GetEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetEndPointY() - this->startGapY, 
					//symbol->GetExpressionStartPointX() - this->startGapX  , 
					//symbol->GetExpressionStartPointY() - this->startGapY, 
					//symbol->GetExpressionEndPointX() - this->startGapX   + this->changingWidth, 
					//symbol->GetExpressionEndPointY() - this->startGapY, 
					symbol->GetExpression() );
				
			}
			else if( dynamic_cast < AfterRepeat * > ( symbol ) )	{
				stcikingSymbol = new AfterRepeat ( 
					symbol->GetStartPointX() - this->startGapX  , 
					symbol->GetStartPointY() - this->startGapY, 
					symbol->GetEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetEndPointY() - this->startGapY, 
					//symbol->GetExpressionStartPointX() - this->startGapX  , 
					//symbol->GetExpressionStartPointY() - this->startGapY, 
					//symbol->GetExpressionEndPointX() - this->startGapX   + this->changingWidth, 
					//symbol->GetExpressionEndPointY() - this->startGapY, 
					symbol->GetExpression() );
				
			}
			else if( dynamic_cast < Selection * > ( symbol ) )	{

				Selection *oldSymbol = static_cast<Selection*>( symbol ) ; // 미들좌표를 읽기위해서 변환
				//double trueWidth = oldSymbol->GetMiddlePointX() - oldSymbol->GetStartPointX() ; // 비율을 구하기 위해서 trueWidth 구한다
				//double falseWidth = oldSymbol->GetEndPointX() - oldSymbol->GetMiddlePointX() ; // 비율을 구하기 위해서 falseWidth 구한다
				//double width = this->endX - this->startX ; // 붙였을 때의 가로길이
				//double rateWidth = ( width * ( trueWidth / ( trueWidth + falseWidth ) ) ) ; // 비율로 길이를 구한다
		

				stcikingSymbol = new Selection ( 
					symbol->GetStartPointX() - this->startGapX  , 
					symbol->GetStartPointY() - this->startGapY, 
					symbol->GetEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetEndPointY() - this->startGapY, 

					symbol->GetExpressionStartPointX() - this->startGapX  , 
					symbol->GetExpressionStartPointY() - this->startGapY, 
					symbol->GetExpressionEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetExpressionEndPointY() - this->startGapY, 

					oldSymbol->GetMiddlePointX() - this->startGapX ,
					oldSymbol->GetMiddlePointY() - this->startGapY,
					//symbol->GetStartPointX() - this->startGapX + rateWidth,
					//static_cast<Selection*>(symbol)->GetMiddlePointY() - this->startGapY,
					symbol->GetExpression() );
			}
		else if( dynamic_cast < SwitchCase * > ( symbol ) )	{
			SwitchCase *switchCase = static_cast<SwitchCase*>( symbol ) ;
				
			Long columnCount = switchCase->GetColumnCount() ;

			Long startX = switchCase->GetSelection()->GetStartPointX() - this->startGapX ;//symbol->GetStartPointX() - this->startGapX ;
			Long startY = switchCase->GetSelection()->GetStartPointY() - this->startGapY ;//symbol->GetEndPointY() - this->startGapY ;

			Long endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
			Long endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;

			wstring expression = switchCase->GetExpression() ;
			wstring *caseExpressions = new wstring[ switchCase->GetLength()] ;

			for(Long i = 0 ; i < switchCase->GetLength() ; i++ ){
				caseExpressions[i] = switchCase->GetCases(i)->GetExpression() ;
			}
			stcikingSymbol =  new SwitchCase ( columnCount, startX , startY , endX, endY , expression, caseExpressions) ;

		}



		//기존 symbols의 기호 할당 해제
		delete symbol ;

		//새로 붙여 그린 기호를 Paper::ModifyTo(~) 호출해서 넣기
		paper->ModifyTo( stcikingSymbol, selectedIndex ) ;
		//*/
			
	}
	this->stickedIndex = -1 ;
	this->stickingField = -1 ;
	
}


/*
	함수이름 : StickToForPre
	설    명 : 이동 중에 기호가 다른 기호에 붙는 상황이면 힙에 붙여진 기호를 정보를 저장한다
	입    력 : Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex
	출    력 : Symbol *symbol
	만 든 이 : i5
*/
Symbol* Sticker::StickToForPre ( Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex ) {

	if ( type.compare("Sequence") == 0 ) {
		this->dotSymbol = new Sequence ( startX , startY , endX, endY, expression ) ;
	}
	else if ( type.compare("BeforeRepeat") == 0 ) {
		this->dotSymbol = new BeforeRepeat ( startX , startY , endX, endY, expression ) ;
	}
	else if ( type.compare("AfterRepeat") == 0 ) {
		this->dotSymbol = new AfterRepeat ( startX , startY , endX, endY, expression ) ;
	}
	else if ( type.compare("Selection") == 0 ) {
		//미들좌표를 다른 좌표들의 이동에 맞춰서 변화시켜줘야한다
		//비율을 활용한다
		Selection *oldSymbol = static_cast<Selection*>( paper->GetAt( oldIndex ) ) ; // 미들좌표를 읽기위해서 변환
		double trueWidth = oldSymbol->GetMiddlePointX() - oldSymbol->GetStartPointX() ; // 비율을 구하기 위해서 trueWidth 구한다
		double falseWidth = oldSymbol->GetEndPointX() - oldSymbol->GetMiddlePointX() ; // 비율을 구하기 위해서 falseWidth 구한다
		double width = this->endX - this->startX ; // 붙였을 때의 가로길이
		double rateWidth = ( width * ( trueWidth / ( trueWidth + falseWidth ) ) ) ; // 비율로 길이를 구한다

		Selection *temp = new Selection ( startX , startY , endX, endY, expression ) ; // 우선 이동된 좌표로 기호를 그린다
		
		this->dotSymbol = new Selection ( // 미들 좌표가 이동전 기호와 같은 비율로 그려진 기호를 그린다
					temp->GetStartPointX(), 
					temp->GetStartPointY(), 
					temp->GetEndPointX(), 
					temp->GetEndPointY(), 
					temp->GetExpressionStartPointX(), 
					temp->GetExpressionStartPointY(), 
					temp->GetExpressionEndPointX(), 
					temp->GetExpressionEndPointY(), 
					temp->GetStartPointX() + rateWidth,
					static_cast<Selection*>(temp)->GetMiddlePointY(),
					temp->GetExpression() ) ;
		delete temp ; // 임시로 그린 기호 할당 해제

	}
	else if ( type.compare("SwitchCase") == 0 ) {
		SwitchCase *oldSymbol = static_cast<SwitchCase*>( paper->GetAt( oldIndex ) ) ;
		Long columnCount = oldSymbol->GetColumnCount() ;
		wstring expression = oldSymbol->GetExpression() ;
		wstring *caseExpressions = new wstring[ oldSymbol->GetLength()] ;
		
		for(Long i = 0 ; i < oldSymbol->GetLength() ; i++ ){
			caseExpressions[i] = oldSymbol->GetCases(i)->GetExpression() ;
		}
		this->dotSymbol =  new SwitchCase ( columnCount, startX , startY , endX, endY , expression, caseExpressions) ;
			//( columnCount, startPointX , startPointY , endPointX, endPointY , expression, caseExpressions) ;
		
		
		//SwitchCase *switchCaseSymbol = static_cast<SwitchCase*>(symbol) ;
	}
	return this->dotSymbol ;
}


/*
	함수이름 : StickBundleToForPre
	설    명 : 이동 중에 기호들이 다른 기호에 붙는 상황이면 힙에 붙여진 기호들 정보를 저장한다
	입    력 : Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex
	출    력 : Symbol *symbol
	만 든 이 : i5
*/
void Sticker::StickBundleToForPre ( Paper *paper, Select *select, Long startGapX, Long startGapY, Symbol* (*symbols), Long symbolsLength ){

	
	for( Long i = 0 ; i < symbolsLength ; i++ ) 
	{
		Long selectedIndex = select->GetSelectPaper()->GetAt(i).GetSeletedSymbolIndex() ;
		Symbol *symbol = paper->GetAt( selectedIndex ) ;  
		Symbol *stcikingSymbol ;

			// 위치를 변경한다
			if( dynamic_cast< Sequence * > ( symbol ) )	{
				stcikingSymbol = new Sequence ( 
					symbol->GetStartPointX() - this->startGapX  , 
					symbol->GetStartPointY() - this->startGapY, 
					symbol->GetEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetEndPointY() - this->startGapY, 
					symbol->GetExpressionStartPointX() - this->startGapX  , 
					symbol->GetExpressionStartPointY() - this->startGapY, 
					symbol->GetExpressionEndPointX() - this->startGapX  + this->changingWidth, 
					symbol->GetExpressionEndPointY() - this->startGapY, 
					symbol->GetExpression() );
			}

			else if( dynamic_cast< BeforeRepeat * > ( symbol ) )	{
				stcikingSymbol = new BeforeRepeat ( 
					symbol->GetStartPointX() - this->startGapX  , 
					symbol->GetStartPointY() - this->startGapY, 
					symbol->GetEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetEndPointY() - this->startGapY, 
					//symbol->GetExpressionStartPointX() - this->startGapX  , 
					//symbol->GetExpressionStartPointY() - this->startGapY, 
					//symbol->GetExpressionEndPointX() - this->startGapX   + this->changingWidth, 
					//symbol->GetExpressionEndPointY() - this->startGapY, 
					symbol->GetExpression() );
				
			}
			else if( dynamic_cast < AfterRepeat * > ( symbol ) )	{
				stcikingSymbol = new AfterRepeat ( 
					symbol->GetStartPointX() - this->startGapX  , 
					symbol->GetStartPointY() - this->startGapY, 
					symbol->GetEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetEndPointY() - this->startGapY, 
					//symbol->GetExpressionStartPointX() - this->startGapX  , 
					//symbol->GetExpressionStartPointY() - this->startGapY, 
					//symbol->GetExpressionEndPointX() - this->startGapX   + this->changingWidth, 
					//symbol->GetExpressionEndPointY() - this->startGapY, 
					symbol->GetExpression() );
				
			}
			else if( dynamic_cast < Selection * > ( symbol ) )	{

				Selection *oldSymbol = static_cast<Selection*>( symbol ) ; // 미들좌표를 읽기위해서 변환
				//double trueWidth = oldSymbol->GetMiddlePointX() - oldSymbol->GetStartPointX() ; // 비율을 구하기 위해서 trueWidth 구한다
				//double falseWidth = oldSymbol->GetEndPointX() - oldSymbol->GetMiddlePointX() ; // 비율을 구하기 위해서 falseWidth 구한다
				//double width = this->endX - this->startX ; // 붙였을 때의 가로길이
				//double rateWidth = ( width * ( trueWidth / ( trueWidth + falseWidth ) ) ) ; // 비율로 길이를 구한다
		

				stcikingSymbol = new Selection ( 
					symbol->GetStartPointX() - this->startGapX  , 
					symbol->GetStartPointY() - this->startGapY, 
					symbol->GetEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetEndPointY() - this->startGapY, 

					symbol->GetExpressionStartPointX() - this->startGapX  , 
					symbol->GetExpressionStartPointY() - this->startGapY, 
					symbol->GetExpressionEndPointX() - this->startGapX   + this->changingWidth, 
					symbol->GetExpressionEndPointY() - this->startGapY, 

					oldSymbol->GetMiddlePointX() - this->startGapX ,
					oldSymbol->GetMiddlePointY() - this->startGapY,
					//symbol->GetStartPointX() - this->startGapX + rateWidth,
					//static_cast<Selection*>(symbol)->GetMiddlePointY() - this->startGapY,
					symbol->GetExpression() );
			}
		else if( dynamic_cast < SwitchCase * > ( symbol ) )	{
			SwitchCase *switchCase = static_cast<SwitchCase*>( symbol ) ;
				
			Long columnCount = switchCase->GetColumnCount() ;

			Long startX = switchCase->GetSelection()->GetStartPointX() - this->startGapX ;//symbol->GetStartPointX() - this->startGapX ;
			Long startY = switchCase->GetSelection()->GetStartPointY() - this->startGapY ;//symbol->GetEndPointY() - this->startGapY ;

			Long endX = startX + ( switchCase->GetSelection()->GetEndPointX() - switchCase->GetSelection()->GetStartPointX() ) ;
			Long endY = startY + ( switchCase->GetCases(0)->GetEndPointY() - switchCase->GetSelection()->GetStartPointY() ) ;

			wstring expression = switchCase->GetExpression() ;
			wstring *caseExpressions = new wstring[ switchCase->GetLength()] ;

			for(Long i = 0 ; i < switchCase->GetLength() ; i++ ){
				caseExpressions[i] = switchCase->GetCases(i)->GetExpression() ;
			}
			stcikingSymbol =  new SwitchCase ( columnCount, startX , startY , endX, endY , expression, caseExpressions) ;

		}
			if( symbols[i] != 0 )
			{
				delete symbols[i] ;
			}
			symbols[i] = stcikingSymbol ;


	}
}


/*
	함수이름 : StickLine
	설    명 : 수정할 때 라인을 맞춰준다
	입    력 : Paper *paper, Long modifiedIndex, Long transNumber
	출    력 : Long ( 첨자 )
	만 든 이 : i5
*/
Long Sticker::StickLine( Paper *paper, Long modifiedIndex, Long transNumber ) {
	
	Symbol *modifiedSymbol = paper->GetAt( modifiedIndex ) ;
	Symbol *paperSymbol ;
	Symbol *lineSymbol = 0 ;

	Long modifiedStartX = modifiedSymbol->GetStartPointX() ;
	Long modifiedStartY = modifiedSymbol->GetStartPointY() ;
	Long modifiedEndX = modifiedSymbol->GetEndPointX() ;
	Long modifiedEndY = modifiedSymbol->GetEndPointY() ;
	Long modifiedMiddlePointX ;
	Long modifiedMiddlePointY ;

	Long paperStartX ;
	Long paperEndX ;
	Long paperEndY ;
	Long paperMiddleX ;
	Long paperMiddleY ;

	// 고친 기호가 순차구조이고, 수정점이 6번이면 
	if( dynamic_cast<Sequence*>( modifiedSymbol ) && transNumber == 6 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY)나 (endX, endY) )가 있으면
			paperSymbol = paper->GetAt(i) ;
			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// 순차구조가 BeforeRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<BeforeRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperEndY >= modifiedEndY - LINE &&
					  paperEndY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
				}
			}
			else if( dynamic_cast<AfterRepeat*>( paperSymbol ) )
			{// 순차구조가 AfterRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperMiddleY >= modifiedEndY - LINE &&
					  paperMiddleY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperMiddleY, modifiedSymbol->GetExpression() ) ;
				}
			}
			
			// 1. 고친 순차구조의 오른쪽 귀퉁이 영역에 ,
				// 기호의 왼쪽 아래 귀퉁이 꼭지점이 속할 때 
			if(  paperStartX >= modifiedEndX &&
				 paperStartX <= modifiedEndX + LINE &&
				 paperEndY >= modifiedEndY - LINE &&
				 paperEndY <= modifiedEndY + LINE &&
				 i != modifiedIndex)
			{
				lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
			}
			// 2. 고친 순차구조의 왼쪽 귀퉁이 영역에 ,
				// 기호의 오른쪽 아래 귀퉁이 꼭지점이 속할 때 
			else if ( paperEndX >= modifiedStartX - LINE &&
					  paperEndX <= modifiedStartX &&
					  paperEndY >= modifiedEndY - LINE &&
					  paperEndY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
			{ 
				lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
			}

		}


	}



	// 고친 기호가 선반복구조이고, 수정점이 6번이면 
	else if( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) && transNumber == 6 )
	{
		modifiedMiddlePointX = (static_cast<BeforeRepeat*>( modifiedSymbol ))->GetMiddlePointX() ;
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY))가 있으면
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;

			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// 선반복구조가 BeforeRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<BeforeRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperEndY >= modifiedEndY - LINE &&
					  paperEndY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
				}
			}
			else if( dynamic_cast<AfterRepeat*>( paperSymbol ) )
			{// 선반복구조가 AfterRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperMiddleY >= modifiedEndY - LINE &&
					  paperMiddleY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperMiddleY, modifiedSymbol->GetExpression() ) ;
				}
			}
			


			// 1. 고친 선반복구조의 오른쪽 귀퉁이 영역에 ,
				// 기호의 왼쪽 아래 귀퉁이 꼭지점이 속할 때 
			if(  paperStartX >= modifiedMiddlePointX &&
				 paperStartX <= modifiedMiddlePointX + LINE &&
				 paperEndY >= modifiedEndY - LINE &&
				 paperEndY <= modifiedEndY + LINE &&
				 i != modifiedIndex)
			{
				lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
			}

		}
	}




	// 고친 기호가 후반복구조이고, 수정점이 6번이면 
	else if( dynamic_cast<AfterRepeat*>( modifiedSymbol ) && transNumber == 6 )
	{
		modifiedMiddlePointX = (static_cast<AfterRepeat*>( modifiedSymbol ))->GetMiddlePointX() ;
		modifiedMiddlePointY = (static_cast<AfterRepeat*>( modifiedSymbol ))->GetMiddlePointY() ;
		
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY)가 있으면
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;


			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// 후반복구조가 BeforeRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<BeforeRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperEndY >= modifiedEndY - LINE &&
					  paperEndY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperMiddleY , modifiedSymbol->GetExpression() ) ;
				}
			}
			else if( dynamic_cast<AfterRepeat*>( paperSymbol ) )
			{// 후반복구조가 AfterRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperMiddleY >= modifiedEndY - LINE &&
					  paperMiddleY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(),paperMiddleY , modifiedSymbol->GetExpression() ) ;
				}
			}
			

			// 1. 고친 후반복구조의 오른쪽 귀퉁이 영역에 ,
				// 기호의 왼쪽 아래 귀퉁이 꼭지점이 속할 때 
			if(  paperStartX >= modifiedMiddlePointX &&
				 paperStartX <= modifiedMiddlePointX + LINE &&
				 paperEndY >= modifiedMiddlePointY - LINE &&
				 paperEndY <= modifiedMiddlePointY + LINE &&
				 i != modifiedIndex)
			{
				lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY + 40 , modifiedSymbol->GetExpression() ) ;
			}

		}
	}

	// 고친 기호의 수정점이 4번이면 // 목표는 modifiedSymbol의 가로길이 조절
	if( transNumber == 4 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY)나 (endX, endY) )가 있으면
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{ // paperSymbol이 BeforeRepeat이면 
				
				Long paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
		
				// 고친 기호의 오른쪽 위 귀퉁이 부분의 특정 영역에,
					// BeforeRepeat의 모양의 오른쪽 아래 귀퉁이 꼭지점(endX, middleY)이 속할 때
				if ( paperEndX >= modifiedEndX - LINE &&
					 paperEndX <= modifiedEndX + LINE &&
					 paperMiddleY >= modifiedStartY - LINE &&
					 paperMiddleY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol의 endX좌표를 조절한다
						if ( dynamic_cast<Sequence*>( modifiedSymbol ) ) {
							lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<AfterRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression()  ) ;
						}
						else if ( dynamic_cast<Selection*>( modifiedSymbol ) ) {
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // 미들좌표를 읽기위해서 변환
							
							lineSymbol = new Selection ( // 미들 좌표가 이동전 기호와 같은 비율로 그려진 기호를 그린다
										oldSymbol->GetStartPointX(), 
										oldSymbol->GetStartPointY(), 
										paperEndX, 
										oldSymbol->GetEndPointY(), 
										oldSymbol->GetExpressionStartPointX(), 
										oldSymbol->GetExpressionStartPointY(), 
										oldSymbol->GetExpressionEndPointX(), 
										oldSymbol->GetExpressionEndPointY(), 
										oldSymbol->GetMiddlePointX(), //+ rateWidth,
										oldSymbol->GetMiddlePointY(),
										oldSymbol->GetExpression() ) ;
						}
				}
				
			}
			else 
			{// paperSybmol이 BeforeRepeat가 아니면
			// 고친 기호의 오른쪽 위 귀퉁이 부분의 특정 영역에,
				// 기호의 오른쪽 아래 귀퉁이 꼭지점(endX, endY)이 속할 때 
				if ( paperEndX >= modifiedEndX - LINE &&
					 paperEndX <= modifiedEndX + LINE &&
					 paperEndY >= modifiedStartY - LINE &&
					 paperEndY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol의 endX좌표를 조절한다
						if ( dynamic_cast<Sequence*>( modifiedSymbol ) ) {
							lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<AfterRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression()  ) ;
						}
						else if ( dynamic_cast<Selection*>( modifiedSymbol ) ) {
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // 미들좌표를 읽기위해서 변환
							lineSymbol = new Selection ( // 미들 좌표가 이동전 기호와 같은 비율로 그려진 기호를 그린다
										oldSymbol->GetStartPointX(), 
										oldSymbol->GetStartPointY(), 
										paperEndX, 
										oldSymbol->GetEndPointY(), 
										oldSymbol->GetExpressionStartPointX(), 
										oldSymbol->GetExpressionStartPointY(), 
										oldSymbol->GetExpressionEndPointX(), 
										oldSymbol->GetExpressionEndPointY(), 
										oldSymbol->GetMiddlePointX(), //+ rateWidth,
										oldSymbol->GetMiddlePointY(),
										oldSymbol->GetExpression() ) ;

						}
						else if ( dynamic_cast<SwitchCase*>( modifiedSymbol ) ) {
							SwitchCase *oldSymbol = static_cast<SwitchCase*>( modifiedSymbol ) ;
							Long columnCount = oldSymbol->GetColumnCount() ;
							wstring expression = oldSymbol->GetExpression() ;
							wstring *caseExpressions = new wstring[ oldSymbol->GetLength()] ;
		
							for(Long i = 0 ; i < oldSymbol->GetLength() ; i++ ){
								caseExpressions[i] = oldSymbol->GetCases(i)->GetExpression() ;
							}
							Long startX = oldSymbol->GetSelection()->GetStartPointX() ;
							Long startY = oldSymbol->GetSelection()->GetStartPointY() ;
							Long endY = oldSymbol->GetCases(0)->GetEndPointY() ;
							lineSymbol =  new SwitchCase ( columnCount, startX , startY , paperEndX, endY , expression, caseExpressions) ;
						
						}

				}
			}
		
		}
	}

	
	else if( transNumber == 8 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY)나 (endX, endY) )가 있으면
			paperSymbol = paper->GetAt(i) ;
			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			// 고친 기호의 오른쪽 위 귀퉁이 부분의 특정 영역에,
				// 기호의 오른쪽 아래 귀퉁이 꼭지점(endX, endY)이 속할 때 
				if ( paperStartX >= modifiedStartX - LINE &&
					 paperStartX <= modifiedStartX + LINE &&
					 paperEndY >= modifiedStartY - LINE &&
					 paperEndY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol의 endX좌표를 조절한다
						if ( dynamic_cast<Sequence*>( modifiedSymbol ) ) {
							lineSymbol = new Sequence ( paperStartX , modifiedSymbol->GetStartPointY(), modifiedSymbol->GetEndPointX(), modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new BeforeRepeat ( paperStartX , modifiedSymbol->GetStartPointY(), modifiedSymbol->GetEndPointX(), modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<AfterRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new AfterRepeat ( paperStartX , modifiedSymbol->GetStartPointY(), modifiedSymbol->GetEndPointX(), modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression()  ) ;
						}
						else if ( dynamic_cast<Selection*>( modifiedSymbol ) ) {
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // 미들좌표를 읽기위해서 변환
							lineSymbol = new Selection ( // 미들 좌표가 이동전 기호와 같은 비율로 그려진 기호를 그린다
										paperStartX, 
										oldSymbol->GetStartPointY(), 
										modifiedSymbol->GetEndPointX(), 
										oldSymbol->GetEndPointY(), 
										oldSymbol->GetExpressionStartPointX(), 
										oldSymbol->GetExpressionStartPointY(), 
										oldSymbol->GetExpressionEndPointX(), 
										oldSymbol->GetExpressionEndPointY(), 
										oldSymbol->GetMiddlePointX(), //+ rateWidth,
										oldSymbol->GetMiddlePointY(),
										oldSymbol->GetExpression() ) ;

						}
				}
		}
	}//*/
	if( lineSymbol != 0 ) 
	{
		delete paper->GetAt( modifiedIndex ) ; // 기존 symbols의 기호 할당 해제
		//새로 붙여 그린 기호를 Paper::ModifyTo(~) 호출해서 넣기
		 paper->ModifyTo( lineSymbol, modifiedIndex ) ;
	}
		
	//*/
	return modifiedIndex ;
}

/*
	함수이름 : StickLineForPre
	설    명 : 수정할 때 라인을 맞춰줄 때, 미리 보여줄 기호를 만든다
	입    력 : Paper *paper, Long modifiedIndex, Long transNumber
	출    력 : Long ( 첨자 )
	만 든 이 : i5
*/
Symbol* Sticker::StickLineForPre( Paper *paper, Long modifiedIndex, Long transNumber ) {
		
	Symbol *modifiedSymbol = paper->GetAt( modifiedIndex ) ;
	Symbol *paperSymbol ;
	Symbol *lineSymbol = 0 ;

	Long modifiedStartX = modifiedSymbol->GetStartPointX() ;
	Long modifiedStartY = modifiedSymbol->GetStartPointY() ;
	Long modifiedEndX = modifiedSymbol->GetEndPointX() ;
	Long modifiedEndY = modifiedSymbol->GetEndPointY() ;
	Long modifiedMiddlePointX ;
	Long modifiedMiddlePointY ;

	Long paperStartX ;
	Long paperEndX ;
	Long paperEndY ;
	Long paperMiddleX ;
	Long paperMiddleY ;

	// 고친 기호가 순차구조이고, 수정점이 6번이면 
	if( dynamic_cast<Sequence*>( modifiedSymbol ) && transNumber == 6 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY)나 (endX, endY) )가 있으면
			paperSymbol = paper->GetAt(i) ;
			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// 순차구조가 BeforeRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<BeforeRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperEndY >= modifiedEndY - LINE &&
					  paperEndY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
				}
			}
			else if( dynamic_cast<AfterRepeat*>( paperSymbol ) )
			{// 순차구조가 AfterRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperMiddleY >= modifiedEndY - LINE &&
					  paperMiddleY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperMiddleY, modifiedSymbol->GetExpression() ) ;
				}
			}
			
			// 1. 고친 순차구조의 오른쪽 귀퉁이 영역에 ,
				// 기호의 왼쪽 아래 귀퉁이 꼭지점이 속할 때 
			if(  paperStartX >= modifiedEndX &&
				 paperStartX <= modifiedEndX + LINE &&
				 paperEndY >= modifiedEndY - LINE &&
				 paperEndY <= modifiedEndY + LINE &&
				 i != modifiedIndex)
			{
				lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
			}
			// 2. 고친 순차구조의 왼쪽 귀퉁이 영역에 ,
				// 기호의 오른쪽 아래 귀퉁이 꼭지점이 속할 때 
			else if ( paperEndX >= modifiedStartX - LINE &&
					  paperEndX <= modifiedStartX &&
					  paperEndY >= modifiedEndY - LINE &&
					  paperEndY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
			{ 
				lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
			}

		}


	}



	// 고친 기호가 선반복구조이고, 수정점이 6번이면 
	else if( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) && transNumber == 6 )
	{
		modifiedMiddlePointX = (static_cast<BeforeRepeat*>( modifiedSymbol ))->GetMiddlePointX() ;
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY))가 있으면
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;

			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// 선반복구조가 BeforeRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<BeforeRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperEndY >= modifiedEndY - LINE &&
					  paperEndY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
				}
			}
			else if( dynamic_cast<AfterRepeat*>( paperSymbol ) )
			{// 선반복구조가 AfterRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperMiddleY >= modifiedEndY - LINE &&
					  paperMiddleY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperMiddleY, modifiedSymbol->GetExpression() ) ;
				}
			}
			


			// 1. 고친 선반복구조의 오른쪽 귀퉁이 영역에 ,
				// 기호의 왼쪽 아래 귀퉁이 꼭지점이 속할 때 
			if(  paperStartX >= modifiedMiddlePointX &&
				 paperStartX <= modifiedMiddlePointX + LINE &&
				 paperEndY >= modifiedEndY - LINE &&
				 paperEndY <= modifiedEndY + LINE &&
				 i != modifiedIndex)
			{
				lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
			}

		}
	}




	// 고친 기호가 후반복구조이고, 수정점이 6번이면 
	else if( dynamic_cast<AfterRepeat*>( modifiedSymbol ) && transNumber == 6 )
	{
		modifiedMiddlePointX = (static_cast<AfterRepeat*>( modifiedSymbol ))->GetMiddlePointX() ;
		modifiedMiddlePointY = (static_cast<AfterRepeat*>( modifiedSymbol ))->GetMiddlePointY() ;
		
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY)가 있으면
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;


			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// 후반복구조가 BeforeRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<BeforeRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperEndY >= modifiedEndY - LINE &&
					  paperEndY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperMiddleY , modifiedSymbol->GetExpression() ) ;
				}
			}
			else if( dynamic_cast<AfterRepeat*>( paperSymbol ) )
			{// 후반복구조가 AfterRepeat안에서 6번 수정점을 내릴 때 
				paperMiddleX = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointX() ;
				paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
				if(   paperMiddleX >= modifiedStartX - LINE &&
					  paperMiddleX <= modifiedStartX &&
					  paperMiddleY >= modifiedEndY - LINE &&
					  paperMiddleY <= modifiedEndY + LINE &&
					  i != modifiedIndex)
				{
					lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(),paperMiddleY , modifiedSymbol->GetExpression() ) ;
				}
			}
			

			// 1. 고친 후반복구조의 오른쪽 귀퉁이 영역에 ,
				// 기호의 왼쪽 아래 귀퉁이 꼭지점이 속할 때 
			if(  paperStartX >= modifiedMiddlePointX &&
				 paperStartX <= modifiedMiddlePointX + LINE &&
				 paperEndY >= modifiedMiddlePointY - LINE &&
				 paperEndY <= modifiedMiddlePointY + LINE &&
				 i != modifiedIndex)
			{
				lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY + 40 , modifiedSymbol->GetExpression() ) ;
			}

		}
	}

	// 고친 기호의 수정점이 4번이면 // 목표는 modifiedSymbol의 가로길이 조절
	if( transNumber == 4 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY)나 (endX, endY) )가 있으면
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{ // paperSymbol이 BeforeRepeat이면 
				
				Long paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
		
				// 고친 기호의 오른쪽 위 귀퉁이 부분의 특정 영역에,
					// BeforeRepeat의 모양의 오른쪽 아래 귀퉁이 꼭지점(endX, middleY)이 속할 때
				if ( paperEndX >= modifiedEndX - LINE &&
					 paperEndX <= modifiedEndX + LINE &&
					 paperMiddleY >= modifiedStartY - LINE &&
					 paperMiddleY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol의 endX좌표를 조절한다
						if ( dynamic_cast<Sequence*>( modifiedSymbol ) ) {
							lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<AfterRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression()  ) ;
						}
						else if ( dynamic_cast<Selection*>( modifiedSymbol ) ) {
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // 미들좌표를 읽기위해서 변환
							
							lineSymbol = new Selection ( // 미들 좌표가 이동전 기호와 같은 비율로 그려진 기호를 그린다
										oldSymbol->GetStartPointX(), 
										oldSymbol->GetStartPointY(), 
										paperEndX, 
										oldSymbol->GetEndPointY(), 
										oldSymbol->GetExpressionStartPointX(), 
										oldSymbol->GetExpressionStartPointY(), 
										oldSymbol->GetExpressionEndPointX(), 
										oldSymbol->GetExpressionEndPointY(), 
										oldSymbol->GetMiddlePointX(), //+ rateWidth,
										oldSymbol->GetMiddlePointY(),
										oldSymbol->GetExpression() ) ;
						}
				}
				
			}
			else { // paperSymbol이 BeforeRepeat가 아니면
			// 고친 기호의 오른쪽 위 귀퉁이 부분의 특정 영역에,
				// 기호의 오른쪽 아래 귀퉁이 꼭지점(endX, endY)이 속할 때 
				if ( paperEndX >= modifiedEndX - LINE &&
					 paperEndX <= modifiedEndX + LINE &&
					 paperEndY >= modifiedStartY - LINE &&
					 paperEndY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol의 endX좌표를 조절한다
						if ( dynamic_cast<Sequence*>( modifiedSymbol ) ) {
							lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new BeforeRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<AfterRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new AfterRepeat ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY(), paperEndX, modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression()  ) ;
						}
						else if ( dynamic_cast<Selection*>( modifiedSymbol ) ) {
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // 미들좌표를 읽기위해서 변환
							lineSymbol = new Selection ( // 미들 좌표가 이동전 기호와 같은 비율로 그려진 기호를 그린다
										oldSymbol->GetStartPointX(), 
										oldSymbol->GetStartPointY(), 
										paperEndX, 
										oldSymbol->GetEndPointY(), 
										oldSymbol->GetExpressionStartPointX(), 
										oldSymbol->GetExpressionStartPointY(), 
										oldSymbol->GetExpressionEndPointX(), 
										oldSymbol->GetExpressionEndPointY(), 
										oldSymbol->GetMiddlePointX(), //+ rateWidth,
										oldSymbol->GetMiddlePointY(),
										oldSymbol->GetExpression() ) ;

						}
						else if ( dynamic_cast<SwitchCase*>( modifiedSymbol ) ) {
							SwitchCase *oldSymbol = static_cast<SwitchCase*>( modifiedSymbol ) ;
							Long columnCount = oldSymbol->GetColumnCount() ;
							wstring expression = oldSymbol->GetExpression() ;
							wstring *caseExpressions = new wstring[ oldSymbol->GetLength()] ;
		
							for(Long i = 0 ; i < oldSymbol->GetLength() ; i++ ){
								caseExpressions[i] = oldSymbol->GetCases(i)->GetExpression() ;
							}
							Long startX = oldSymbol->GetSelection()->GetStartPointX() ;
							Long startY = oldSymbol->GetSelection()->GetStartPointY() ;
							Long endY = oldSymbol->GetCases(0)->GetEndPointY() ;
							lineSymbol =  new SwitchCase ( columnCount, startX , startY , paperEndX, endY , expression, caseExpressions) ;
						
						}

				}
			}
		
		}
	}	

	
	else if( transNumber == 8 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// 고친 기호의 특정 범위에 붙여그려야할 기호(그 기호의 (startX,endY)나 (endX, endY) )가 있으면
			paperSymbol = paper->GetAt(i) ;
			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			// 고친 기호의 오른쪽 위 귀퉁이 부분의 특정 영역에,
				// 기호의 오른쪽 아래 귀퉁이 꼭지점(endX, endY)이 속할 때 
				if ( paperStartX >= modifiedStartX - LINE &&
					 paperStartX <= modifiedStartX + LINE &&
					 paperEndY >= modifiedStartY - LINE &&
					 paperEndY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol의 endX좌표를 조절한다
						if ( dynamic_cast<Sequence*>( modifiedSymbol ) ) {
							lineSymbol = new Sequence ( paperStartX , modifiedSymbol->GetStartPointY(), modifiedSymbol->GetEndPointX(), modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new BeforeRepeat ( paperStartX , modifiedSymbol->GetStartPointY(), modifiedSymbol->GetEndPointX(), modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression() ) ;
						}
						else if ( dynamic_cast<AfterRepeat*>( modifiedSymbol ) ) {
							lineSymbol = new AfterRepeat ( paperStartX , modifiedSymbol->GetStartPointY(), modifiedSymbol->GetEndPointX(), modifiedSymbol->GetEndPointY() , modifiedSymbol->GetExpression()  ) ;
						}
						else if ( dynamic_cast<Selection*>( modifiedSymbol ) ) {
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // 미들좌표를 읽기위해서 변환
							lineSymbol = new Selection ( // 미들 좌표가 이동전 기호와 같은 비율로 그려진 기호를 그린다
										paperStartX, 
										oldSymbol->GetStartPointY(), 
										modifiedSymbol->GetEndPointX(), 
										oldSymbol->GetEndPointY(), 
										oldSymbol->GetExpressionStartPointX(), 
										oldSymbol->GetExpressionStartPointY(), 
										oldSymbol->GetExpressionEndPointX(), 
										oldSymbol->GetExpressionEndPointY(), 
										oldSymbol->GetMiddlePointX(), //+ rateWidth,
										oldSymbol->GetMiddlePointY(),
										oldSymbol->GetExpression() ) ;

						}
				}
		}
	}//*/
	return lineSymbol ;
}



/*
	함수이름 : CheckStickingSign
	설    명 : 매개변수로 들어온 index기호에 종이 위의 기호가 붙어있는지 확인해서 stickSign값을 변화시킨다
	입    력 : Paper *paper, Long index( 조사 대상기호의 첨자 )
	출    력 : index
	만 든 이 : i5
	특이사항 : 붙는 영역이 기호의 내부와 일정범위의 외부// 그릴 때 사용 중
*/
Long Sticker::CheckStickingSign ( Paper *paper, Long index ) 
 {
	Symbol *indexSymbol = paper->GetAt( index ) ;// 특정기호
	
	
	//특정기호가 Sequence일 때
	if ( dynamic_cast<Sequence*>( indexSymbol ) ) 
	{ 
		Sequence *indexSequence = static_cast<Sequence*>(indexSymbol) ;
			
		// NO로 해둔다
		indexSequence->upSign = NO ;
		indexSequence->downSign = NO ;
			
		Long indexStartX = indexSequence->GetStartPointX() ;
		Long indexStartY = indexSequence->GetStartPointY() ;
		Long indexEndX = indexSequence->GetEndPointX() ;
		Long indexEndY = indexSequence->GetEndPointY() ;

		// upSign 조사 시작
		Long i = 0 ;
		while( indexSequence->upSign == NO && i < paper->GetLength() ) // YES면 탈출하게 정해둔다
		{ 
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 SwitchCase일 때, checkedSymbol이 indexSequence위에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase의 cases에 indexSequence가 붙어있는지 조사
					Long checkSign = NO ; 
					Long j = 0 ;
					while( j < checkSwitchCase->GetLength() && checkSign == NO )
					{
						Long caseStartX = checkSwitchCase->GetCases( j )->GetStartPointX() ;
						Long caseEndY = checkSwitchCase->GetCases( j )->GetEndPointY() ;
					
						if(  indexStartX == caseStartX &&
							 indexStartY == caseEndY )
						{
							indexSequence->upSign = YES ;
							checkSign = YES ;
						}
						j++ ;
					}

					// indexSequence만 있는 조건 
					if( indexSequence->upSign == NO ) // cases아래에 붙어있지 않으면, 마지막으로 false쪽에 붙어있는지 확인해본다
					{
						Long switchCaseMiddleX = checkSwitchCase->GetSelection()->GetMiddlePointX() ;
						Long switchCaseMiddleY = checkSwitchCase->GetSelection()->GetMiddlePointY() ;
						if( indexStartX == switchCaseMiddleX &&
							indexStartY == switchCaseMiddleY ) 
						{
								indexSequence->upSign = YES ;
								indexSequence->downSign = YES ;
						}
						else if( indexStartX == switchCaseMiddleX - 1 &&
							indexStartY == switchCaseMiddleY ) 
						{
								indexSequence->upSign = YES ;
								indexSequence->downSign = YES ;
						}
						else if( indexStartX == switchCaseMiddleX + 1 &&
							indexStartY == switchCaseMiddleY ) 
						{
								indexSequence->upSign = YES ;
								indexSequence->downSign = YES ;
						}
					}
				} // checkedSymbol이 SwitchCase일 때 끝.

				else  // checkedSymbol이 SwitchCase가 아닐 때, checkedSymbol이 indexSequence위에 붙어있는지 조사한다
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // 종이 위의 기호가 Selection일때 FALSE쪽에 index기호가 붙어있는지 확인때문에 따로 처리
					{
						Long checkSelectionStartX = static_cast<Selection*>(checkedSymbol)->GetStartPointX() ;
						Long checkSelectionEndX= static_cast<Selection*>(checkedSymbol)->GetEndPointY() ;
						Long checkMiddleX = static_cast<Selection*>(checkedSymbol)->GetMiddlePointX() ; 
						Long checkMiddleY = static_cast<Selection*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkSelectionStartX &&
							indexStartY == checkSelectionEndX )
						{
								indexSequence->upSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkMiddleY ) 
						{
								indexSequence->upSign = YES ;
						}
					}
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 BeforeRepeat일 때, index기호가 BeforeRepeat의 안쪽에 붙어있는지 확인 때문에 따로 처리
					{
						//1) BeforeRepeat의 미들점 == indexSequence의 위치
						//2) BeforeRepeat의 왼쪽 아랫점 == indexSequence의 위치
						Long checkMiddleX = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						Long checkMiddleY = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkMiddleX &&
							indexStartY == checkMiddleY ) {
								indexSequence->upSign = YES ;
						}
						else if( indexStartX == checkStartX &&
							  	 indexStartY == checkEndY ) {
									indexSequence->upSign = YES ;
						}	
					}
					else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 AfterRepeat일 때, index기호가 AfterRepeat의 안쪽에 붙어있는지 확인
					{
						//- 후반복구조의 미들 윗점에 붙으면, 모든 기호들의 upSign은 yes되어야 한다!!!!
							//- 후반복구조의 미들 윗점 ( middleX, startY )
						//- 후반복구조를 따로 빼서 upSign을 정리해야하므로 후반복구조의 왼쪽 아랫점에 붙는 기호들의 upSign도 함께 yes로 만든다
							//- 후반복구조의 왼쪽 아랫점 ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexSequence->upSign = YES ; // indexSequence 위에 기호가 붙어있다
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexSequence->upSign = YES ; // indexSequence 위에 기호가 붙어있다
						}

					}
				
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexSequence의 왼쪽 윗점이, checkedSymbol의 왼쪽 아랫점과 같은면 
					{ 
								indexSequence->upSign = YES ; // indexSequence 위에 기호가 붙어있다
					}
				}
			} // 자기 자신은 조사에서 제외 끝
			i++ ;

		}// While 구문 indexSequence upSign 조사 끝

		// indexSequence downSign 조사 시작
		i = 0 ;
		while( indexSequence->downSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol이 SwitchCase일 때, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 indexSequence아래에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase가 indexSequence의 아래에 붙어있는지 조사
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexStartX == switchCaseSelectionStartX &&
						indexEndY == switchCaseSelectionStartY ) 
					{
						indexSequence->downSign = YES ;
					}
				}

				// checkedSymbol이 SwitchCase가 아닐 때
				else  //checkedSymbol이 indexSequence아래에 붙어있는지 조사한다
				{			
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndX = checkedSymbol->GetEndPointX() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					if ( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 BeforeRepeat일 때, downSign 예외 경우 처리
					{
						// BeforeRepeat의 중간 아랫점에 indexSequence속할 때 처리를 위한 변수
						Long checkMiddleX = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						if(indexStartX == checkStartX &&
						   indexEndY == checkStartY )
						{
							indexSequence->downSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexEndY == checkEndY )
						{
							indexSequence->downSign = YES ;
						}
						else if( indexEndX == checkEndX &&
								 indexEndY == checkStartY )
						{
							indexSequence->downSign = YES ;
						}
						

					}
					else if ( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 AfterRepeat일 때, downSign 예외 경우 처리
					{
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						//1} 후반복구조의 미들점 == 순차의 왼쪽 아랫점
						//2} 후반복구조의 왼쪽 윗점 == 순차의 왼쪽 아랫점
						if( indexStartX == checkMiddleX &&
							indexEndY == checkMiddleY )
						{
							indexSequence->downSign = YES ;
						}
						else if( indexStartX == checkStartX &&
								 indexEndY == checkStartY )
						{
							indexSequence->downSign = YES ;
						}
						else if( indexEndX == checkEndX &&
								 indexEndY == checkStartY )
						{
							indexSequence->downSign = YES ;
						}
					}
					

					else if( indexStartX == checkStartX &&
						 	 indexEndY == checkStartY ) // indexSequence의 왼쪽 아랫점이, checkedSymbol의 왼쪽 윗점과 같은면
					{
						indexSequence->downSign = YES ; // indexSequence 아래에 기호가 붙어있다
					}	
					else if( indexEndX == checkEndX &&
								 indexEndY == checkStartY )
					{
							indexSequence->downSign = YES ;
					}
				}
			}  // 자기 자신은 조사에서 제외 끝

			i++ ;
		}// While 구문 indexSequence downSign 조사 끝

	}//특정기호가 Sequence일 때 끝
		
	
	//특정기호가 Selectino 일 때
	else if ( dynamic_cast<Selection*>( indexSymbol ) ) 
	{ 
		Selection *indexSelection = static_cast<Selection*>(indexSymbol) ;
			
		// NO로 해둔다
		indexSelection->upSign = NO ;
		indexSelection->trueSign = NO ;
		indexSelection->falseSign = NO ;

		Long indexStartX = indexSelection->GetStartPointX() ;
		Long indexStartY = indexSelection->GetStartPointY() ;
		Long indexEndX = indexSelection->GetEndPointX() ;
		Long indexEndY = indexSelection->GetEndPointY() ;

		// upSign 조사 시작
		Long i = 0 ;
		while( indexSelection->upSign == NO && i < paper->GetLength() ) // YES면 탈출하게 정해둔다
		{
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 SwitchCase일 때, checkedSymbol이 indexSelection위에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase의 cases에 indexSelection가 붙어있는지 조사
					Long checkSign = NO ; 
					Long j = 0 ;
					while( j < checkSwitchCase->GetLength() && checkSign == NO )
					{
						Long caseStartX = checkSwitchCase->GetCases( j )->GetStartPointX() ;
						Long caseEndY = checkSwitchCase->GetCases( j )->GetEndPointY() ;
					
						if(  indexStartX == caseStartX &&
							 indexStartY == caseEndY )
						{
							indexSelection->upSign = YES ;
							checkSign = YES ;
						}
						j++ ;
					}
				} // checkedSymbol이 SwitchCase일 때 끝.

				else  // checkedSymbol이 SwitchCase가 아닐 때, checkedSymbol이 indexSelection위에 붙어있는지 조사한다
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // 종이 위의 기호가 Selection일때 FALSE쪽에 index기호가 붙어있는지 확인때문에 따로 처리
					{
						Long checkSelectionStartX = static_cast<Selection*>(checkedSymbol)->GetStartPointX() ;
						Long checkSelectionEndX= static_cast<Selection*>(checkedSymbol)->GetEndPointY() ;
						Long checkMiddleX = static_cast<Selection*>(checkedSymbol)->GetMiddlePointX() ; 
						Long checkMiddleY = static_cast<Selection*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkSelectionStartX &&
							indexStartY == checkSelectionEndX ) // true쪽에 붙어있을 때 
						{
								indexSelection->upSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkMiddleY ) // false쪽에 붙어있을 때 
						{
								indexSelection->upSign = YES ;
						}
					}
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 BeforeRepeat일 때, index기호가 BeforeRepeat의 안쪽에 붙어있는지 확인 때문에 따로 처리
					{
						//1) BeforeRepeat의 미들점 == indexSelection의 위치
						//2) BeforeRepeat의 왼쪽 아랫점 == indexSelection의 위치
						Long checkMiddleX = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						Long checkMiddleY = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkMiddleX &&
							indexStartY == checkMiddleY ) {
								indexSelection->upSign = YES ;
						}
						else if( indexStartX == checkStartX &&
							  	 indexStartY == checkEndY ) {
									indexSelection->upSign = YES ;
						}
						
					}

					else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 AfterRepeat일 때, index기호가 AfterRepeat의 안쪽에 붙어있는지 확인
					{
						//- 후반복구조의 미들 윗점에 붙으면, 모든 기호들의 upSign은 yes되어야 한다!!!!
							//- 후반복구조의 미들 윗점 ( middleX, startY )
						//- 후반복구조를 따로 빼서 upSign을 정리해야하므로 후반복구조의 왼쪽 아랫점에 붙는 기호들의 upSign도 함께 yes로 만든다
							//- 후반복구조의 왼쪽 아랫점 ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexSelection->upSign = YES ; // indexSelection 위에 기호가 붙어있다
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexSelection->upSign = YES ; // indexSelection 위에 기호가 붙어있다
						}

					}
				
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexSelection의 왼쪽 윗점이, checkedSymbol의 왼쪽 아랫점과 같은면 
					{ 
								indexSelection->upSign = YES ; // indexSelection 위에 기호가 붙어있다
					}
				}
			} // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// while () upSign 조사 끝

		// indexSelection trueSign 조사 시작
		i = 0 ;
		while( indexSelection->trueSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol이 SwitchCase일 때, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 indexSelection아래에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase가 indexSelection의 true에 붙어있는지 조사
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexStartX == switchCaseSelectionStartX &&
						indexEndY == switchCaseSelectionStartY ) 
					{
						indexSelection->trueSign = YES ;
					}
				}

				// checkedSymbol이 SwitchCase가 아닐 때
				else  //checkedSymbol이 indexSelection true에 붙어있는지 조사한다
				{			
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					if( indexStartX == checkStartX &&
						indexEndY == checkStartY ) 
					{
						indexSelection->trueSign = YES ;
					}
				}
			}  // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// While 구문 indexSelection trueSign 조사 끝

		// indexSelection falseSign 조사 시작
		i = 0 ;
		while( indexSelection->falseSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				Long indexMiddleX = indexSelection->GetMiddlePointX() ;
				Long indexMiddleY = indexSelection->GetMiddlePointY() ;

				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol이 SwitchCase일 때, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 indexSelection아래에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase가 indexSelection의 false에 붙어있는지 조사
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexMiddleX == switchCaseSelectionStartX &&
						indexMiddleY == switchCaseSelectionStartY ) 
					{
						indexSelection->falseSign = YES ;
					}
				}

				// checkedSymbol이 SwitchCase가 아닐 때
				else  //checkedSymbol이 indexSelection false에 붙어있는지 조사한다
				{			
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					if( indexMiddleX == checkStartX &&
						indexMiddleY == checkStartY ) 
					{
						indexSelection->falseSign = YES ;
					}
				}
			}  // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// While 구문 indexSelection falseSign 조사 끝
	}//특정기호가 Selectino 일 때 끝


	//특정기호가 BeforeRepeat 일 때
	else if ( dynamic_cast<BeforeRepeat*>( indexSymbol ) ) 
	{ 
		BeforeRepeat *indexBeforeRepeat = static_cast<BeforeRepeat*>(indexSymbol) ;
			
		// NO로 해둔다
		indexBeforeRepeat->upSign = NO ;
		indexBeforeRepeat->downSign = NO ;
		indexBeforeRepeat->inSign = NO ;

		Long indexStartX = indexBeforeRepeat->GetStartPointX() ;
		Long indexStartY = indexBeforeRepeat->GetStartPointY() ;
		Long indexEndX = indexBeforeRepeat->GetEndPointX() ;
		Long indexEndY = indexBeforeRepeat->GetEndPointY() ;

		// upSign 조사 시작
		Long i = 0 ;
		while( indexBeforeRepeat->upSign == NO && i < paper->GetLength() ) // YES면 탈출하게 정해둔다
		{
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 SwitchCase일 때, checkedSymbol이 indexBeforeRepeat위에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase의 cases에 indexBeforeRepeat가 붙어있는지 조사
					Long checkSign = NO ; 
					Long j = 0 ;
					while( j < checkSwitchCase->GetLength() && checkSign == NO )
					{
						Long caseStartX = checkSwitchCase->GetCases( j )->GetStartPointX() ;
						Long caseEndY = checkSwitchCase->GetCases( j )->GetEndPointY() ;
					
						if(  indexStartX == caseStartX &&
							 indexStartY == caseEndY )
						{
							indexBeforeRepeat->upSign = YES ;
							checkSign = YES ;
						}
						j++ ;
					}
				} // checkedSymbol이 SwitchCase일 때 끝.

				else  // checkedSymbol이 SwitchCase가 아닐 때, checkedSymbol이 indexBeforeRepeat위에 붙어있는지 조사한다
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // 종이 위의 기호가 Selection일때 FALSE쪽에 index기호가 붙어있는지 확인때문에 따로 처리
					{
						Long checkSelectionStartX = static_cast<Selection*>(checkedSymbol)->GetStartPointX() ;
						Long checkSelectionEndX= static_cast<Selection*>(checkedSymbol)->GetEndPointY() ;
						Long checkMiddleX = static_cast<Selection*>(checkedSymbol)->GetMiddlePointX() ; 
						Long checkMiddleY = static_cast<Selection*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkSelectionStartX &&
							indexStartY == checkSelectionEndX ) // true쪽에 붙어있을 때 
						{
								indexBeforeRepeat->upSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkMiddleY ) // false쪽에 붙어있을 때 
						{
								indexBeforeRepeat->upSign = YES ;
						}
					}
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 BeforeRepeat일 때, index기호가 BeforeRepeat의 안쪽에 붙어있는지 확인 때문에 따로 처리
					{
						//1) BeforeRepeat의 미들점 == indexBeforeRepeat의 위치
						//2) BeforeRepeat의 왼쪽 아랫점 == indexBeforeRepeat의 위치
						Long checkMiddleX = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						Long checkMiddleY = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkMiddleX &&
							indexStartY == checkMiddleY ) {
								indexBeforeRepeat->upSign = YES ;
						}
						else if( indexStartX == checkStartX &&
							  	 indexStartY == checkEndY ) {
									indexBeforeRepeat->upSign = YES ;
						}
						
					}
						else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 AfterRepeat일 때, index기호가 AfterRepeat의 안쪽에 붙어있는지 확인
					{
						//- 후반복구조의 미들 윗점에 붙으면, 모든 기호들의 upSign은 yes되어야 한다!!!!
							//- 후반복구조의 미들 윗점 ( middleX, startY )
						//- 후반복구조를 따로 빼서 upSign을 정리해야하므로 후반복구조의 왼쪽 아랫점에 붙는 기호들의 upSign도 함께 yes로 만든다
							//- 후반복구조의 왼쪽 아랫점 ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexBeforeRepeat->upSign = YES ; // indexBeforeRepeat 위에 기호가 붙어있다
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexBeforeRepeat->upSign = YES ; // indexBeforeRepeat 위에 기호가 붙어있다
						}

					}
				
				
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexBeforeRepeat의 왼쪽 윗점이, checkedSymbol의 왼쪽 아랫점과 같은면 
					{ 
								indexBeforeRepeat->upSign = YES ; // indexBeforeRepeat 위에 기호가 붙어있다
					}
				}
			} // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// while() upSign 조사 끝
	

		
		// indexBeforeRepeat downSign 조사 시작
		i = 0 ;
		while( indexBeforeRepeat->downSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol이 SwitchCase일 때, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 indexBeforeRepeat아래에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase가 indexBeforeRepeat의 true에 붙어있는지 조사
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexStartX == switchCaseSelectionStartX &&
						indexEndY == switchCaseSelectionStartY ) 
					{
						indexBeforeRepeat->downSign = YES ;
					}
				}

				// checkedSymbol이 SwitchCase가 아닐 때
				else  //checkedSymbol이 indexBeforeRepeat 아래에 붙어있는지 조사한다
				{			
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndX = checkedSymbol->GetEndPointX() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					if( indexStartX == checkStartX &&
						indexEndY == checkStartY ) 
					{
						indexBeforeRepeat->downSign = YES ;
					}
					else if( indexEndX == checkEndX &&
								 indexEndY == checkStartY )
					{
							indexBeforeRepeat->downSign = YES ;
					}
				}
			}  // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// While 구문 indexBeforeRepeat downSign 조사 끝

		// indexBeforeRepeat inSign 조사 시작
		i = 0 ;
		while( indexBeforeRepeat->inSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				Long indexMiddleX = indexBeforeRepeat->GetMiddlePointX() ;
				Long indexMiddleY = indexBeforeRepeat->GetMiddlePointY() ;
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol이 SwitchCase일 때, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 indexBeforeRepeat안에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase가 indexBeforeRepeat의 true에 붙어있는지 조사
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexMiddleX == switchCaseSelectionStartX &&
						indexMiddleY == switchCaseSelectionStartY ) 
					{
						indexBeforeRepeat->inSign = YES ;
					}
				}

				// checkedSymbol이 SwitchCase가 아닐 때
				else  //checkedSymbol이 indexBeforeRepeat 안에 붙어있는지 조사한다
				{			
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					if( indexMiddleX == checkStartX &&
						indexMiddleY == checkStartY ) 
					{
						indexBeforeRepeat->inSign = YES ;
					}
				}
			}  // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// While 구문 indexBeforeRepeat inSign 조사 끝
	} //특정기호가 BeforeRepeat 일 때 끝


	
	//특정기호가 AfterRepeat 일 때
	else if ( dynamic_cast<AfterRepeat*>( indexSymbol ) ) 
	{ 
		AfterRepeat *indexAfterRepeat = static_cast<AfterRepeat*>(indexSymbol) ;
			
		// NO로 해둔다
		indexAfterRepeat->upSign = NO ;
		indexAfterRepeat->downSign = NO ;
		indexAfterRepeat->inSign = NO ;

		Long indexStartX = indexAfterRepeat->GetStartPointX() ;
		Long indexStartY = indexAfterRepeat->GetStartPointY() ;
		Long indexEndX = indexAfterRepeat->GetEndPointX() ;
		Long indexEndY = indexAfterRepeat->GetEndPointY() ;

		// upSign 조사 시작
		Long i = 0 ;
		while( indexAfterRepeat->upSign == NO && i < paper->GetLength() ) // YES면 탈출하게 정해둔다
		{
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 SwitchCase일 때, checkedSymbol이 indexAfterRepeat위에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase의 cases에 indexAfterRepeat가 붙어있는지 조사
					Long checkSign = NO ; 
					Long j = 0 ;
					while( j < checkSwitchCase->GetLength() && checkSign == NO )
					{
						Long caseStartX = checkSwitchCase->GetCases( j )->GetStartPointX() ;
						Long caseEndY = checkSwitchCase->GetCases( j )->GetEndPointY() ;
					
						if(  indexStartX == caseStartX &&
							 indexStartY == caseEndY )
						{
							indexAfterRepeat->upSign = YES ;
							checkSign = YES ;
						}
						j++ ;
					}
				} // checkedSymbol이 SwitchCase일 때 끝.

				else  // checkedSymbol이 SwitchCase가 아닐 때, checkedSymbol이 indexAfterRepeat위에 붙어있는지 조사한다
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // 종이 위의 기호가 Selection일때 FALSE쪽에 index기호가 붙어있는지 확인때문에 따로 처리
					{
						Long checkSelectionStartX = static_cast<Selection*>(checkedSymbol)->GetStartPointX() ;
						Long checkSelectionEndX= static_cast<Selection*>(checkedSymbol)->GetEndPointY() ;
						Long checkMiddleX = static_cast<Selection*>(checkedSymbol)->GetMiddlePointX() ; 
						Long checkMiddleY = static_cast<Selection*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkSelectionStartX &&
							indexStartY == checkSelectionEndX ) // true쪽에 붙어있을 때 
						{
								indexAfterRepeat->upSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkMiddleY ) // false쪽에 붙어있을 때 
						{
								indexAfterRepeat->upSign = YES ;
						}
					}
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 BeforeRepeat일 때, index기호가 BeforeRepeat의 안쪽에 붙어있는지 확인 때문에 따로 처리
					{
						//1) BeforeRepeat의 미들점 == indexAfterRepeat의 위치
						//2) BeforeRepeat의 왼쪽 아랫점 == indexAfterRepeat의 위치
						Long checkMiddleX = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						Long checkMiddleY = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkMiddleX &&
							indexStartY == checkMiddleY ) {
								indexAfterRepeat->upSign = YES ;
						}
						else if( indexStartX == checkStartX &&
							  	 indexStartY == checkEndY ) {
									indexAfterRepeat->upSign = YES ;
						}
						
					}
					else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 AfterRepeat일 때, index기호가 AfterRepeat의 안쪽에 붙어있는지 확인
					{
						//- 후반복구조의 미들 윗점에 붙으면, 모든 기호들의 upSign은 yes되어야 한다!!!!
							//- 후반복구조의 미들 윗점 ( middleX, startY )
						//- 후반복구조를 따로 빼서 upSign을 정리해야하므로 후반복구조의 왼쪽 아랫점에 붙는 기호들의 upSign도 함께 yes로 만든다
							//- 후반복구조의 왼쪽 아랫점 ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexAfterRepeat->upSign = YES ; // indexAfterRepeat 위에 기호가 붙어있다
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexAfterRepeat->upSign = YES ; // indexAfterRepeat 위에 기호가 붙어있다
						}

					}
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexBeforeRepeat의 왼쪽 윗점이, checkedSymbol의 왼쪽 아랫점과 같은면 
					{ 
								indexAfterRepeat->upSign = YES ; // indexBeforeRepeat 위에 기호가 붙어있다
					}
				}
			} // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// while() upSign 조사 끝
	

		
		// indexAfterRepeat downSign 조사 시작
		i = 0 ;
		while( indexAfterRepeat->downSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol이 SwitchCase일 때, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 indexAfterRepeat아래에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase가 indexBeforeRepeat의 true에 붙어있는지 조사
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexStartX == switchCaseSelectionStartX &&
						indexEndY == switchCaseSelectionStartY ) 
					{
						indexAfterRepeat->downSign = YES ;
					}
				}

				// checkedSymbol이 SwitchCase가 아닐 때
				else  //checkedSymbol이 indexBeforeRepeat 아래에 붙어있는지 조사한다
				{			
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndX = checkedSymbol->GetEndPointX() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					if( indexStartX == checkStartX &&
						indexEndY == checkStartY ) 
					{
							indexAfterRepeat->downSign = YES ;
					}
					else if( indexEndX == checkEndX &&
								 indexEndY == checkStartY )
					{
							indexAfterRepeat->downSign = YES ;
					}
				}
			}  // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// While 구문 indexAfterRepeat downSign 조사 끝

		// indexAfterRepeat inSign 조사 시작
		i = 0 ;
		while( indexAfterRepeat->inSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				Long indexMiddleX = indexAfterRepeat->GetMiddlePointX() ;
				//Long indexMiddleY = indexAfterRepeat->GetMiddlePointY() ;
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol이 SwitchCase일 때, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 indexBeforeRepeat안에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase가 indexBeforeRepeat의 true에 붙어있는지 조사
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexMiddleX == switchCaseSelectionStartX &&
						indexStartY == switchCaseSelectionStartY ) 
					{
						indexAfterRepeat->inSign = YES ;
					}
				}

				// checkedSymbol이 SwitchCase가 아닐 때
				else  //checkedSymbol이 indexBeforeRepeat 안에 붙어있는지 조사한다
				{			
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					if( indexMiddleX == checkStartX &&
						indexStartY == checkStartY ) 
					{
						indexAfterRepeat->inSign = YES ;
					}
				}
			}  // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// While 구문 indexAfterRepeat inSign 조사 끝
	} //특정기호가 indexAfterRepeat 일 때 끝


	//특정기호가 SwitchCase 일 때
	else if ( dynamic_cast<SwitchCase*>( indexSymbol ) ) 
	{ 
		SwitchCase *indexSwitchCase = static_cast<SwitchCase*>(indexSymbol) ;
			
		// NO로 해둔다
		indexSwitchCase->upSign = NO ;
		indexSwitchCase->falseSign = NO ;
		for( Long i = 0 ; i < indexSwitchCase->GetLength() ; i++ ){
			indexSwitchCase->GetCases( i )->downSign = NO ;
		}

		Long indexStartX = indexSwitchCase->GetSelection()->GetStartPointX() ;
		Long indexStartY = indexSwitchCase->GetSelection()->GetStartPointY() ;
		Long indexEndY = indexSwitchCase->GetCases(0)->GetEndPointY() ;

		// upSign 조사 시작
		Long i = 0 ;
		while( indexSwitchCase->upSign == NO && i < paper->GetLength() ) // YES면 탈출하게 정해둔다
		{
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 SwitchCase일 때, checkedSymbol이 indexSwitchCase위에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase의 cases에 indexSwitchCase가 붙어있는지 조사
					Long checkSign = NO ; 
					Long j = 0 ;
					while( j < checkSwitchCase->GetLength() && checkSign == NO )
					{
						Long caseStartX = checkSwitchCase->GetCases( j )->GetStartPointX() ;
						Long caseEndY = checkSwitchCase->GetCases( j )->GetEndPointY() ;
					
						if(  indexStartX == caseStartX &&
							 indexStartY == caseEndY )
						{
							indexSwitchCase->upSign = YES ;
							checkSign = YES ;
						}
						j++ ;
					}
				} // checkedSymbol이 SwitchCase일 때 끝.

				else  // checkedSymbol이 SwitchCase가 아닐 때, checkedSymbol이 indexSwitchCase위에 붙어있는지 조사한다
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // 종이 위의 기호가 Selection일때 FALSE쪽에 index기호가 붙어있는지 확인때문에 따로 처리
					{
						Long checkSelectionStartX = static_cast<Selection*>(checkedSymbol)->GetStartPointX() ;
						Long checkSelectionEndX= static_cast<Selection*>(checkedSymbol)->GetEndPointY() ;
						Long checkMiddleX = static_cast<Selection*>(checkedSymbol)->GetMiddlePointX() ; 
						Long checkMiddleY = static_cast<Selection*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkSelectionStartX &&
							indexStartY == checkSelectionEndX ) // true쪽에 붙어있을 때 
						{
								indexSwitchCase->upSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkMiddleY ) // false쪽에 붙어있을 때 
						{
								indexSwitchCase->upSign = YES ;
						}
					}
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 BeforeRepeat일 때, index기호가 BeforeRepeat의 안쪽에 붙어있는지 확인 때문에 따로 처리
					{
						//1) BeforeRepeat의 미들점 == indexSwitchCase의 위치
						//2) BeforeRepeat의 왼쪽 아랫점 == indexSwitchCase의 위치
						Long checkMiddleX = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						Long checkMiddleY = static_cast<BeforeRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkMiddleX &&
							indexStartY == checkMiddleY ) {
								indexSwitchCase->upSign = YES ;
						}
						else if( indexStartX == checkStartX &&
							  	 indexStartY == checkEndY ) {
									indexSwitchCase->upSign = YES ;
						}
						
					}
					else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // 종이 위의 기호가 AfterRepeat일 때, index기호가 AfterRepeat의 안쪽에 붙어있는지 확인
					{
						//- 후반복구조의 미들 윗점에 붙으면, 모든 기호들의 upSign은 yes되어야 한다!!!!
							//- 후반복구조의 미들 윗점 ( middleX, startY )
						//- 후반복구조를 따로 빼서 upSign을 정리해야하므로 후반복구조의 왼쪽 아랫점에 붙는 기호들의 upSign도 함께 yes로 만든다
							//- 후반복구조의 왼쪽 아랫점 ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexSwitchCase->upSign = YES ; // indexSwitchCase 위에 기호가 붙어있다
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexSwitchCase->upSign = YES ; // indexSwitchCase 위에 기호가 붙어있다
						}

					}
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexSwitchCase의 왼쪽 윗점이, checkedSymbol의 왼쪽 아랫점과 같은면 
					{ 
								indexSwitchCase->upSign = YES ; // indexSwitchCase 위에 기호가 붙어있다
					}
				}
			} // 자기 자신은 조사에서 제외 끝
			i++ ;
		}// while() upSign 조사 끝
	
		
		// indexSwitchCase falseSign 조사 시작
		Long k = 0 ;
		while( indexSwitchCase->falseSign == NO && k < paper->GetLength() )
		{ 
			if( k != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( k ) ;

				if ( dynamic_cast<Sequence*>( checkedSymbol ) ) // checkedSymbol이 indexAfterRepeat아래에 붙어있는지 조사한다
				{
					Long indexSwitchCaseMiddleX = indexSwitchCase->GetSelection()->GetMiddlePointX() ;
					Long indexSwitchCaseMiddleY = indexSwitchCase->GetSelection()->GetMiddlePointY() ;
					
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					if( indexSwitchCaseMiddleX == checkStartX &&
						indexSwitchCaseMiddleY == checkStartY )
					{
						indexSwitchCase->falseSign = YES ;
					}
					else if( indexSwitchCaseMiddleX - 1  == checkStartX &&
						indexSwitchCaseMiddleY == checkStartY )
					{
						indexSwitchCase->falseSign = YES ;
					}
					else if( indexSwitchCaseMiddleX + 1  == checkStartX &&
						indexSwitchCaseMiddleY == checkStartY )
					{
						indexSwitchCase->falseSign = YES ;
					}
				}
					
			}
			k++ ;
		}// While 구문 indexAfterRepeat falseSign 조사 끝
		
		// indexSwitchCase cases donwSign 조사 시작
		i = 0 ;
		while(i < paper->GetLength() )
		{ 
			if( i != index ) // 자기 자신은 조사에서 제외
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol이 SwitchCase일 때, checkedSymbol이 indexSwitchCase위에 붙어있는지 조사한다
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;
					Long checkStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long checkStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;

					// indexSwitchCase의 cases에 checkSwitchCase가 붙어있는지 조사
					 
					Long j = 0 ;
					while( j < indexSwitchCase->GetLength()  )
					{
						Long indexCaseStartX = indexSwitchCase->GetCases( j )->GetStartPointX() ;
						Long indexCaseEndY = indexSwitchCase->GetCases( j )->GetEndPointY() ;
					
						if(  indexCaseStartX == checkStartX &&
							 indexCaseEndY == checkStartY )
						{
							indexSwitchCase->GetCases( j )->downSign = YES ;
							
						}
						j++ ;
					}
				} // checkedSymbol이 SwitchCase일 때 끝.

				else  // checkedSymbol이 SwitchCase가 아닐 때, checkedSymbol이 indexSwitchCase위에 붙어있는지 조사한다
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					// indexSwitchCase의 cases에 checkedSymbol이 붙어있는지 조사
					 
					Long j = 0 ;
					while( j < indexSwitchCase->GetLength()  )
					{
						Long indexCaseStartX = indexSwitchCase->GetCases( j )->GetStartPointX() ;
						Long indexCaseEndY = indexSwitchCase->GetCases( j )->GetEndPointY() ;
					
						if(  indexCaseStartX == checkStartX &&
							 indexCaseEndY == checkStartY )
						{
							indexSwitchCase->GetCases( j )->downSign = YES ;
							
						}
						j++ ;
					}
				} // checkedSymbol이 SwitchCase아닐 때 끝.
			} // 자기 자신은 조사에서 제외 끝
			i++ ;
		} // while()  indexSwitchCase cases donwSign 조사 끝
	}
	return index ;
}