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
	�Լ��̸� : CheckStickingField
	��    �� : �Ű������� ���� ��ȣ(÷��)�� ���� �� �ִ� ��ȣ�� ������ �� ��ȣ�� ÷�ڿ� �ٴ� ��ġ ������ ���Ѵ�
	��    �� : Paper *paper, Long index( ���� ��ȣ�� ÷�� )
	��    �� : void
	�� �� �� : i5
	Ư�̻��� : �ٴ� ������ ��ȣ�� ���ο� ���������� �ܺ�// �׸� �� ��� ��
*/
void Sticker::CheckStickingField ( Paper *paper, Select *select, Long index ) {

//======================================================================================���콺�� �ɸ� ��ȣ�� �ƴ϶� ���� �� ��ȣ���� ������ ��� ������===================================================================
		// index��ȣ�� ���� ���� �� ��ȣ�� ��ġ, ũ��, �̵�
			// �� ������� ���� ������ �����Ѵ�
			// paper Length��ŭ ������ Ȯ���ϱ� ������ ���� �ݺ�������� ���ϸ� �Բ� ��� ���Ѵ�
 		Long stickingStartX ;
		Long stickingStartY ;
		Long stickingEndX ;
		Long stickingEndY ;
		Long stickingMiddleX ;
		Long stickingMiddleY ;

		// index��ȣ�� ���� ���� �� ��ȣ�� SwitchCase�� ��
		Long swtichCaseSelectionStartX ;
		Long swtichCaseSelectionStartY ;
		Long swtichCaseSelectionEndX ;
		Long swtichCaseSelectionEndY ;

		Long swtichCaseFalseStartX ;
		Long swtichCaseFalseStartY ;


		//��ȣ�� ���� ��ȣ(���� ���� �ִ� ��ȣ)�� �������� �ּҸ� ���� �ڵ�����
		Symbol *symbol ; // checkSymbol
		
//=======================================================================================================================================================================================================================


//======================================================================================���콺�� �ɸ� ��ȣ(index)�� ������ ���� ������===================================================================================
		// index��ȣ�� SwitchCase���� ��ȣ�� �� ����� ����
		Long startX ;
		Long startY ;
		Long endX ;
		Long endY ;
		Long middleX ;
		Long middleY ;

		Symbol *indexSymbol = paper->GetAt( index ) ;



		// index��ȣ�� SwitchCase�� �� ����� ���� 
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
			/// ���� ���� ��ȣ�� Sequence�� ��
			if( dynamic_cast<Sequence*>(symbol) && i != index )
			{
				
				Sequence *checkSequence =  static_cast<Sequence*>(symbol) ;

				// Sequence�� �ٴ� index��ȣ�� Sequence�ų� Selection�̸�
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					 dynamic_cast<Selection*>(paper->GetAt( index ))
					)
				{ 
						// �Ʒ��� �ٱ� ����, ���� ������ ������ �ٴ� ������ ���� ��
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
						// �Ʒ��� �ٱ� ����, ������ ������ ������ �ٴ� ������ ���� ��
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

						// ���� �ٱ� ����, ���� �Ʒ����� ������ �ٴ� ������ ���� ��
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
						// ���� �ٱ� ����, ������ �Ʒ����� ������ �ٴ� ������ ���� ��
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





				// Sequence�� �ٴ� index��ȣ�� BeforeRepeat��
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					
					BeforeRepeat *indexBeforeRepeat =  static_cast<BeforeRepeat*>(paper->GetAt( index )) ;
					middleX = indexBeforeRepeat->GetMiddlePointX() ;
					middleY = indexBeforeRepeat->GetMiddlePointY() ;
					

					// �Ʒ��� �ٱ� ����, ���� ������ ������ �ٴ� ������ ���� ��
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
					// �Ʒ��� �ٱ� ����, ������ ���� ���� ������ �ٴ� ������ ���� ��
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

					// �Ʒ��� �ٱ� ����, ������ �߰����� ������ �ٴ� ������ ���� ��
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
					// �Ʒ��� �ٱ� ����, ������ �Ʒ����� ������ �ٴ� ������ ���� ��
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
					// ���� �ٱ� ����, ���� �Ʒ����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, �Ʒ��� �߰����� ������ �ٴ� ������ ���� ��
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

				// Sequence�� �ٴ� ��ȣ�� AfterRepeat��
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
					// �Ʒ��� �ٱ� ����, ���� ������ ������ �ٴ� ������ ���� ��
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

					// �Ʒ��� �ٱ� ����, ���� �� �߰����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ���� �Ʒ����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ������ �Ʒ����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ������ �Ʒ� �߰����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ������ �Ʒ� �߰����� ������ �ٴ� ������ ���� ��
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

			// Sequence�� �ٴ� ��ȣ�� SwitchCase�� �� 
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


				// �Ʒ��� �ٱ� ����, ���� ������ ������ �ٴ� ������ ���� ��
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
					// �Ʒ��� �ٱ� ����, ������ ������ ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ���� �Ʒ����� ������ �ٴ� ������ ���� ��
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
					
					// ���� �ٱ� ����, �߰� �Ʒ����� ������ �ٴ� ������ ���� ��
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


	   }// Sequence�� ��ȣ�� ���� �� ó�� �Լ� �ݴ� �߰�ȣ



	   /////	
		////
		/// ���� ���� ��ȣ�� Selection�� ��
		if( dynamic_cast<Selection*>(symbol) && i != index  ){
			
			stickingMiddleX = (static_cast<Selection*>(symbol))->GetMiddlePointX() ;
			stickingMiddleY = (static_cast<Selection*>(symbol))->GetMiddlePointY() ;
			Selection *checkSelection = static_cast<Selection*>(symbol) ;
			// ���ñ����� ���� �޶�ٴ� ��츦 �������� �߰��Ѵ� 
				// ���ñ����� ���� �޶�ٴ� ������ �����̰ų� ������ ��
			if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					dynamic_cast<Selection*>(paper->GetAt( index ))
				) {

					// TRUE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, ������ ������ �ٴ� ������ ���� �� 
					else if( checkSelection->trueSign == NO &&
								endX > stickingStartX &&
								endX < stickingMiddleX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +STICKER  ){
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSelection->trueSign = YES ;
					}
					// FALSE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					else if(checkSelection->falseSign == NO &&
							startX > stickingMiddleX &&
							startX < stickingEndX &&
							startY > stickingStartY &&
							startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}
				// ���� �ٱ� ����, ������ �Ʒ����� �ٴ� ������ ���� �� 
					if(	checkSelection->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
					// ���� �ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� �� 
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

				//���ñ����� ���� �޶�ٴ� ������ ���ݺ��� ��
			if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index ))) {

				middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
				middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
				// TRUE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, ������ ������ �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						endX > stickingStartX &&
						endX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, ������ �߰����� �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						endX > stickingStartX &&
						endX < stickingMiddleX &&
						startY + 40 > stickingStartY  &&
						startY + 40 < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, �߰����� �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						middleY > stickingStartY  &&
						middleY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					
					// FALSE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					else if(checkSelection->falseSign == NO && 
							startX > stickingMiddleX &&
							startX < stickingEndX &&
							startY > stickingStartY &&
							startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}

					// FALSE�ʿ� �ٱ� ����, �߰����� �ٴ� ������ ���� �� 
					if( checkSelection->falseSign == NO &&
						middleX > stickingMiddleX &&
						middleX < stickingEndX &&
						middleY > stickingStartY  &&
						middleY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
					}




				// ���� �ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� �� 
				if(	checkSelection->upSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					endY > stickingStartY - STICKER &&
					endY < stickingEndY ) {
						this->stickedIndex = i ;
						this->stickingField = 3 ;
					}
				// ���� �ٱ� ����, ���� �Ʒ� �߰����� �ٴ� ������ ����  ��	
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
				//���ñ����� ���� �޶�ٴ� ������ �Ĺݺ��� ��
			if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index ))) {

				middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
				middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;

					// TRUE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					if(  checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, �߰� ������ �ٴ� ������ ���� �� 
					else if(  checkSelection->trueSign == NO &&
								middleX > stickingStartX &&
								middleX < stickingMiddleX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +STICKER  ){
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSelection->trueSign = YES ;
					}
					// FALSE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					if( checkSelection->falseSign == NO &&
						startX > stickingMiddleX &&
						startX < stickingEndX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
					}
					// FALSE�ʿ� �ٱ� ����, �߰� ������ �ٴ� ������ ���� �� 
					else if( checkSelection->falseSign == NO &&
								middleX > stickingMiddleX &&
								middleX < stickingEndX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +STICKER  ){
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}

				//���� �ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				if(	checkSelection->upSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					endY > stickingStartY - STICKER &&
					endY < stickingEndY ) {
						this->stickedIndex = i ;
						this->stickingField = 3 ;
						checkSelection->upSign = YES ;
					}

				//���� �ٱ� ����, �߰����� �ٴ� ������ ���� ��
				else if( checkSelection->upSign == NO &&
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - STICKER &&
							middleY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
				//���� �ٱ� ����, ������ �Ʒ����� �ٴ� ������ ���� ��
				else if( checkSelection->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - STICKER &&
							endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
				//���� �ٱ� ����, ������ �Ʒ� �߰����� �ٴ� ������ ���� ��
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


				
			// Selection�� �ٴ� ��ȣ�� SwitchCase�� �� 
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


				// TRUE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
				if(  checkSelection->trueSign == NO &&
					selectionStartX > stickingStartX &&
					selectionStartX < stickingMiddleX &&
					selectionStartY > stickingStartY  &&
					selectionStartY < stickingMiddleY +STICKER  ){
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkSelection->trueSign = YES ;
				}

				// FALSE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� ��  
				else if(checkSelection->falseSign == NO && 
						selectionStartX > stickingMiddleX &&
						selectionStartX < stickingEndX &&
				 		selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
				}
				// FALSE�ʿ� �ٱ� ����, ������ ������ �ٴ� ������ ���� ��  
				else if(checkSelection->falseSign == NO && 
						selectionEndX > stickingMiddleX &&
						selectionEndX < stickingEndX &&
				 		selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY +STICKER  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
				}
				//���� �ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkSelection->upSign == NO &&
						firstCaseStartX > stickingStartX &&
						firstCaseStartX < stickingEndX &&
						firstCaseEndY > stickingStartY - STICKER &&
						firstCaseEndY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
				}
				//���� �ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
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
		}//Selection�� ��ȣ�� ���� �� ó�� �Լ� �ݴ� �߰�ȣ
			
		////
		////
		/// ���� ���� ��ȣ�� BeforeRepeat�� ��
		if( dynamic_cast<BeforeRepeat*>(symbol) && i != index  ){
			
			stickingMiddleX = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointX() ;
			stickingMiddleY = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointY() ;
			BeforeRepeat *checkBeforeRepeat = static_cast<BeforeRepeat*>(symbol) ;
			
			// ���ݺ������� �������� �޶�ٴ� ������ �����̰ų� ������ ��
			if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					dynamic_cast<Selection*>(paper->GetAt( index ))
				) {

				// ���ݺ������� �������� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}
			

				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
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
		


		// BeforeRepeat�� �ٴ� ��ȣ�� BeforeRepeat��
			if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
			{ 
				middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
				middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
				// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY &&
						middleY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, ������ �߰����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						middleY > stickingStartY &&
						middleY < stickingMiddleY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkBeforeRepeat->inSign = YES ;
				}
					// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO && 
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
					  	startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO &&  
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO && 
						startX > stickingStartX &&
					 	startX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
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
			// BeforeRepeat�� �ٴ� ��ȣ�� AfterRepeat��
			if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
			{ 
				middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
				middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;


				// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, �߰� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}

				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
					  	startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, �߰� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO && 
						endX > stickingStartX &&
					 	endX < stickingEndX &&
						endY > stickingStartY - STICKER &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO &&  
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY - STICKER &&
						middleY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}	
				// ���ݺ������� ���� �޶�ٱ� ����, ������ �߰����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO && 
						endX > stickingStartX &&
						endX < stickingEndX &&
						middleY > stickingStartY - STICKER &&
						middleY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
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
			// BeforeRepeat�� �ٴ� ��ȣ�� SwitchCase�� �� 
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

					
				// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				if( checkBeforeRepeat->inSign == NO &&
					selectionStartX > stickingStartX &&
					selectionStartX < stickingEndX &&
					selectionStartY > stickingStartY &&
					selectionStartY < stickingMiddleY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						selectionEndX > stickingStartX &&
						selectionEndX < stickingEndX &&
						selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkBeforeRepeat->inSign = YES ;
				}

				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						selectionStartX > stickingStartX &&
						selectionStartX < stickingMiddleX &&
					  	selectionStartY > stickingEndY - 20 &&
						selectionStartY < stickingEndY + STICKER ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO &&  
						selectionEndX > stickingStartX &&
						selectionEndX < stickingMiddleX &&
					  	selectionStartY > stickingEndY - 20 &&
						selectionStartY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}

				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO && 
						firstCaseStartX > stickingStartX &&
						firstCaseStartX < stickingEndX &&
						firstCaseEndY > stickingStartY - STICKER &&
						firstCaseEndY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
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
		}//BeforeRepeat�� ��ȣ�� ���� �� ó�� �Լ� �ݴ� �߰�ȣ






			////
			////
			/// ���� ���� ��ȣ�� AfterRepeat �� ��
			if( dynamic_cast<AfterRepeat*>(symbol) && i != index ){
			
				stickingMiddleX = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointX() ;
				stickingMiddleY = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointY() ;
				AfterRepeat *checkAfterRepeat = static_cast<AfterRepeat*>(symbol) ;
				// �Ĺݺ������� �Ʒ������� �޶�ٴ� ������ �����̰ų� ������ ��
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					 dynamic_cast<Selection*>(paper->GetAt( index ))
					) {

					// �Ĺݺ������� �Ʒ������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					if(	checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ������� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingMiddleY &&
							 startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;

					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, ������ �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}

					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO &&
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
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

				// AfterRepeats�� �ٴ� ��ȣ�� BeforeRepeat��
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					if( checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingMiddleY &&
							 startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if( checkAfterRepeat->downSign == NO && 
							 middleX > stickingStartX &&
							 middleX < stickingEndX &&
							 middleY > stickingMiddleY &&
							 middleY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ������ �߰����� �ٴ� ������ ���� ��
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 middleY > stickingMiddleY &&
							 middleY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// �Ĺݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
				
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - STICKER &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ������ �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							middleY > stickingStartY - STICKER &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}


				}//AfterRepeat�� ��ȣ�� ���� �� ó�� �Լ� �ݴ� �߰�ȣ


				// BeforeRepeat�� �ٴ� ��ȣ�� AfterRepeat��
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;

					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					if( checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, �߰� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->downSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							startY > stickingMiddleY &&
							startY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// �Ĺݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, ������ �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - STICKER  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO &&
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - STICKER  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - STICKER  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							middleY > stickingStartY - STICKER  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - STICKER &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, �߰� ������ �ٴ� ������ ���� ��
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

					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					if( checkAfterRepeat->downSign == NO &&
						selectionStartX > stickingStartX &&
						selectionStartX < stickingEndX &&
						selectionStartY > stickingMiddleY &&
						selectionStartY < stickingEndY + STICKER ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->downSign == NO && 
							selectionEndX > stickingStartX &&
							selectionEndX < stickingEndX &&
							selectionStartY > stickingMiddleY &&
							selectionStartY < stickingEndY + STICKER ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// �Ĺݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO &&
							firstCaseStartX > stickingStartX &&
							firstCaseStartX < stickingEndX &&
							firstCaseEndY > stickingStartY - STICKER  &&
							firstCaseEndY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO &&
							defaultCaseEndX > stickingStartX &&
							defaultCaseEndX < stickingEndX &&
							defaultCaseEndY > stickingStartY - STICKER  &&
							defaultCaseEndY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}

					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							selectionStartX > stickingStartX &&
							selectionStartX < stickingEndX &&
							selectionStartY > stickingStartY - STICKER &&
							selectionStartY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
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



			 } // ��ȣ�� ���� ��ȣ�� AfterRepeat�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ


			 //
			 ///
			 ///
			 // ���� ���� ��ȣ�� SwitchCase �� ��

			 if( dynamic_cast<SwitchCase*>(symbol) && i != index )
			 {
				Long swtichCaseFalseEndX = static_cast<SwitchCase*>(symbol)->GetSelection()->GetEndPointX() ;
				Long swtichCaseFalseEndY = static_cast<SwitchCase*>(symbol)->GetCases(0)->GetEndPointY() ;
				SwitchCase *checkSwitchCase = static_cast<SwitchCase*>(symbol) ;
				Long checkSwitchCaseUpsign = checkSwitchCase->upSign ;
				Long checkSwitchFalseSign = checkSwitchCase->falseSign ;
							
				
				// SwitchCase�� �ٴ� ��ȣ�� Sequence �� ��
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) )
				{ 
						//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, Sequence�� Selection ������ ������ �ٴ� ������ ���� ��//���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
								
							//   SwitchCase�� ���� �ٱ�����, Sequence�� Selection�� ���� �Ʒ����� �ٴ� ������ ���� �� 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
							}
							//   SwitchCase�� ���� �ٱ�����, Sequence�� Selection�� ������ �Ʒ����� �ٴ� ������ ���� �� 
							else if(checkSwitchCaseUpsign == NO &&
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� FALSE�� �Ʒ��� �ٱ� ����, Sequence ������ ������ �ٴ� ������ ���� �� //���α��� �߰����� �ٴ� ������ ���� �� 
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
							//   SwitchCase�� FALSE�� �Ʒ��� �ٱ� ����, Sequence ���� ������ �ٴ� ������ ���� �� 
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
							//   SwitchCase�� FALSE�� �Ʒ��� �ٱ� ����, Sequence ������ ������ �ٴ� ������ ���� �� 
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
				}// // SwitchCase�� �ٴ� ��ȣ�� Sequence�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ


					else if(	 dynamic_cast<Selection*>(paper->GetAt( index )) )
					{ 
							//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, Sequence�� Selection ������ ������ �ٴ� ������ ���� ��//���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
								
							//   SwitchCase�� ���� �ٱ�����, Sequence�� Selection�� ���� �Ʒ����� �ٴ� ������ ���� �� 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
							}
							//   SwitchCase�� ���� �ٱ�����, Sequence�� Selection�� ������ �Ʒ����� �ٴ� ������ ���� �� 
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
					}// // SwitchCase�� �ٴ� ��ȣ�� Selection�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ


					// SwitchCase�� �ٴ� ��ȣ�� BeforeRepeat��
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
					
					//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, BeforeRepeat ������ ������ �ٴ� ������ ���� �� //���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
							//   SwitchCase�� ���� �ٱ�����, BeforeRepeat�� ���� �Ʒ����� �ٴ� ������ ���� �� 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� ���� �ٱ�����, BeforeRepeat�� ������ �Ʒ����� �ٴ� ������ ���� �� 
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
				}// SwitchCase�� �ٴ� ��ȣ�� BeforeRepeat�� ���� ó���ϴ� �����ݴ� �߰�ȣ



				// SwitchCase�� �ٴ� ��ȣ�� AfterRepeat��
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
					
					//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, AfterRepeat ������ ������ �ٴ� ������ ���� ��//���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
							//   SwitchCase�� ���� �ٱ�����, AfterRepeat�� ���� �Ʒ����� �ٴ� ������ ���� �� 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� ���� �ٱ�����, AfterRepeat�� ������ �Ʒ����� �ٴ� ������ ���� �� 
							else if(checkSwitchCaseUpsign == NO && 
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� ���� �ٱ�����, AfterRepeat�� �̵����� �ٴ� ������ ���� �� 
							else if(checkSwitchCaseUpsign == NO &&
									middleX > swtichCaseSelectionStartX &&
									middleX < swtichCaseSelectionEndX &&
									middleY > swtichCaseSelectionStartY &&
									middleY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� ���� �ٱ�����, AfterRepeat�� ������ �̵����� �ٴ� ������ ���� �� 
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


				}//  SwitchCase�� �ٴ� ��ȣ�� AfterRepeat�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ
				
				 // SwitchCase�� �ٴ� ��ȣ�� SwitchCase��
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
					//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, AfterRepeat ���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
							this->stickedCase = j ; //������ ����ġ���̽��� �Ʒ� case�� ���� ���� ù��° case�� �����

							
						}
						j++ ;
		
					}
				
					if( this->stickedCase == -1 )
					{
						// SwitchCase ���� �Ʒ��� Y��ǥ, defaultSequence �Ʒ��� Y��ǥ
						Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
						Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount())->GetEndPointY() ;
						//  SwitchCase�� ���� �ٱ�����, SwitchCase�� ���� �Ʒ����� �ٴ� ������ ���� �� 
						if( checkSwitchCaseUpsign == NO &&
							selectionStartX > swtichCaseSelectionStartX &&
							selectionStartX < swtichCaseSelectionEndX &&
							firstCaseEndY > swtichCaseSelectionStartY &&
							firstCaseEndY < swtichCaseSelectionEndY ){
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSwitchCase->upSign = YES ;
						}
						//   SwitchCase�� ���� �ٱ�����, SwitchCase�� �߰� �Ʒ����� �ٴ� ������ ���� �� 
						else if(checkSwitchCaseUpsign == NO && 
								selectionMiddleX > swtichCaseSelectionStartX &&
								selectionMiddleX < swtichCaseSelectionEndX &&
								defaultCaseEndY > swtichCaseSelectionStartY &&
								defaultCaseEndY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
						}	
						//   SwitchCase�� ���� �ٱ�����, SwitchCase�� ������ �Ʒ����� �ٴ� ������ ���� �� 
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


			 } // ��ȣ�� ���� ��ȣ�� SwitchCase�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ
			i++ ;
		}// while�ݺ��� �ݴ� �߰�ȣ
	//}
}





	
/*
	�Լ��̸� : CheckStickingFieldForMove
	��    �� : �����̴� ��ȣ�� �ٸ� ��ȣ�� �ٴ��� �Ǵ��Ѵ� ( �ٴ� ������ ��ȣ �ܺΰ� �ƴϴ� )
	��    �� : Paper *paper, Long index, Long moveX( �̵��� ������ ��ġ�� ���� ��ġ�� ���̰�X ), Long moveY(  �̵��� ������ ��ġ�� ���� ��ġ�� ���̰�Y )
	��    �� : void
	�� �� �� : i5
	Ư�̻��� : �ٴ� ������ ��ȣ�� ���λ��̴�, moveX���� moveY���� ���콺��ư������ ���� 0�̴�  // �����϶�, �̸����� ���鶧 �����
*/

void Sticker::CheckStickingFieldForMove ( Paper *paper, Select *select, Long index, Long moveX, Long moveY ) {
//======================================================================================���콺�� �ɸ� ��ȣ�� �ƴ϶� ���� �� ��ȣ���� ������ ��� ������===================================================================
		// index��ȣ�� ���� ���� �� ��ȣ�� ��ġ, ũ��, �̵�
			// �� ������� ���� ������ �����Ѵ�
			// paper Length��ŭ ������ Ȯ���ϱ� ������ ���� �ݺ�������� ���ϸ� �Բ� ��� ���Ѵ�
 		Long stickingStartX ;
		Long stickingStartY ;
		Long stickingEndX ;
		Long stickingEndY ;
		Long stickingMiddleX ;
		Long stickingMiddleY ;


		//��ȣ�� ���� ��ȣ(���� ���� �ִ� ��ȣ)�� �������� �ּҸ� ���� �ڵ�����
		Symbol *symbol ; // checkSymbol
		





		// index��ȣ�� SwitchCase���� ��ȣ�� �� ����� ����
		Long startX ;
		Long startY ;
		Long endX ;
		Long endY ;
		Long middleX ;
		Long middleY ;

		Symbol *indexSymbol = paper->GetAt( index ) ;

		// index��ȣ�� SwitchCase�� �� ����� ���� 
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


			// ���� ���� ��ȣ�� ���õ� ��ȣ���� Ȯ���ϴ� ���� ����
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
			}// ���� ���� ��ȣ�� ���õ� ��ȣ���� Ȯ���ϴ� ���� ��


			if( tempSign == -1 ) //tempSign = -1�̸� ���� �� ��ȣ�� ���õ� ��ȣ�� �ƴϴ�
			{
				symbol = paper->GetAt( i ) ;
				stickingStartX = symbol->GetStartPointX () ;
				stickingStartY = symbol->GetStartPointY () ;
				stickingEndX = symbol->GetEndPointX () ;
				stickingEndY = symbol->GetEndPointY () ;
			}


			else  //tempSign = 1�̸� ���� �� ��ȣ�� ���õ� ��ȣ��
			{
				symbol = 0 ;
			}
			

			////	
			////
			////		   
			/// ���� ���� ��ȣ�� Sequence�� ��
			if( dynamic_cast<Sequence*>(symbol) && i != index )
			{
				
				Sequence *checkSequence =  static_cast<Sequence*>(symbol) ;

				// Sequence�� �ٴ� index��ȣ�� Sequence�ų� Selection�̸�
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					 dynamic_cast<Selection*>(paper->GetAt( index ))
					)
				{ 
					// �Ʒ��� �ٱ� ����, ���� ������ ������ �ٴ� ������ ���� ��
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
					// �Ʒ��� �ٱ� ����, ������ ������ ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ���� �Ʒ����� ������ �ٴ� ������ ���� ��
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
					// ���� �ٱ� ����, ������ �Ʒ����� ������ �ٴ� ������ ���� ��
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





				// Sequence�� �ٴ� index��ȣ�� BeforeRepeat��
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					
					BeforeRepeat *indexBeforeRepeat =  static_cast<BeforeRepeat*>(paper->GetAt( index )) ;
					middleX = indexBeforeRepeat->GetMiddlePointX() + moveX  ;
					middleY = indexBeforeRepeat->GetMiddlePointY() + moveY  ;
					

					// �Ʒ��� �ٱ� ����, ���� ������ ������ �ٴ� ������ ���� ��
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
					// �Ʒ��� �ٱ� ����, ������ ���� ���� ������ �ٴ� ������ ���� ��
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

					// �Ʒ��� �ٱ� ����, ������ �߰����� ������ �ٴ� ������ ���� ��
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
					// �Ʒ��� �ٱ� ����, ������ �Ʒ����� ������ �ٴ� ������ ���� ��
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
					// ���� �ٱ� ����, ���� �Ʒ����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, �Ʒ��� �߰����� ������ �ٴ� ������ ���� ��
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

				// Sequence�� �ٴ� ��ȣ�� AfterRepeat��
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() ;
				
					// �Ʒ��� �ٱ� ����, ���� ������ ������ �ٴ� ������ ���� ��
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

					// �Ʒ��� �ٱ� ����, ���� �� �߰����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ���� �Ʒ����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ������ �Ʒ����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ������ �Ʒ� �߰����� ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ������ �Ʒ� �߰����� ������ �ٴ� ������ ���� ��
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

			// Sequence�� �ٴ� ��ȣ�� SwitchCase�� �� 
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


				// �Ʒ��� �ٱ� ����, ���� ������ ������ �ٴ� ������ ���� ��
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
					// �Ʒ��� �ٱ� ����, ������ ������ ������ �ٴ� ������ ���� ��
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

					// ���� �ٱ� ����, ���� �Ʒ����� ������ �ٴ� ������ ���� ��
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
					
					// ���� �ٱ� ����, �߰� �Ʒ����� ������ �ٴ� ������ ���� ��
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


	   }// Sequence�� ��ȣ�� ���� �� ó�� �Լ� �ݴ� �߰�ȣ



	   /////	
		////
		/// ���� ���� ��ȣ�� Selection�� ��
		if( dynamic_cast<Selection*>(symbol) && i != index  ){
			
			stickingMiddleX = (static_cast<Selection*>(symbol))->GetMiddlePointX() ;
			stickingMiddleY = (static_cast<Selection*>(symbol))->GetMiddlePointY() ;
			Selection *checkSelection = static_cast<Selection*>(symbol) ;
			// ���ñ����� ���� �޶�ٴ� ��츦 �������� �߰��Ѵ� 
				// ���ñ����� ���� �޶�ٴ� ������ �����̰ų� ������ ��
			if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					dynamic_cast<Selection*>(paper->GetAt( index ))
				) {

					// TRUE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, ������ ������ �ٴ� ������ ���� �� 
					else if( checkSelection->trueSign == NO &&
								endX > stickingStartX &&
								endX < stickingMiddleX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +0  ){
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSelection->trueSign = YES ;
					}
					// FALSE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					else if(checkSelection->falseSign == NO &&
							startX > stickingMiddleX &&
							startX < stickingEndX &&
							startY > stickingStartY &&
							startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}
				// ���� �ٱ� ����, ������ �Ʒ����� �ٴ� ������ ���� �� 
					if(	checkSelection->upSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
					// ���� �ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� �� 
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

				//���ñ����� ���� �޶�ٴ� ������ ���ݺ��� ��
			if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index ))) {

				middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
				middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
				
				// TRUE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, ������ ������ �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						endX > stickingStartX &&
						endX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, ������ �߰����� �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						endX > stickingStartX &&
						endX < stickingMiddleX &&
						startY + 40 > stickingStartY  &&
						startY + 40 < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, �߰����� �ٴ� ������ ���� �� 
					if( checkSelection->trueSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						middleY > stickingStartY  &&
						middleY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					
					// FALSE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					else if(checkSelection->falseSign == NO && 
							startX > stickingMiddleX &&
							startX < stickingEndX &&
							startY > stickingStartY &&
							startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}

					// FALSE�ʿ� �ٱ� ����, �߰����� �ٴ� ������ ���� �� 
					if( checkSelection->falseSign == NO &&
						middleX > stickingMiddleX &&
						middleX < stickingEndX &&
						middleY > stickingStartY  &&
						middleY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
					}




				// ���� �ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� �� 
				if(	checkSelection->upSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					endY > stickingStartY - 0 &&
					endY < stickingEndY ) {
						this->stickedIndex = i ;
						this->stickingField = 3 ;
					}
				// ���� �ٱ� ����, ���� �Ʒ� �߰����� �ٴ� ������ ����  ��	
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
				//���ñ����� ���� �޶�ٴ� ������ �Ĺݺ��� ��
			if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index ))) {

				middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
				middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;

					// TRUE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					if(  checkSelection->trueSign == NO &&
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkSelection->trueSign = YES ;
					}
					// TRUE�ʿ� �ٱ� ����, �߰� ������ �ٴ� ������ ���� �� 
					else if(  checkSelection->trueSign == NO &&
								middleX > stickingStartX &&
								middleX < stickingMiddleX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +0  ){
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkSelection->trueSign = YES ;
					}
					// FALSE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
					if( checkSelection->falseSign == NO &&
						startX > stickingMiddleX &&
						startX < stickingEndX &&
						startY > stickingStartY  &&
						startY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
					}
					// FALSE�ʿ� �ٱ� ����, �߰� ������ �ٴ� ������ ���� �� 
					else if( checkSelection->falseSign == NO &&
								middleX > stickingMiddleX &&
								middleX < stickingEndX &&
				 				startY > stickingStartY &&
								startY < stickingMiddleY +0  ){
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSelection->falseSign = YES ;
					}

				//���� �ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				if(	checkSelection->upSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					endY > stickingStartY - 0 &&
					endY < stickingEndY ) {
						this->stickedIndex = i ;
						this->stickingField = 3 ;
						checkSelection->upSign = YES ;
					}

				//���� �ٱ� ����, �߰����� �ٴ� ������ ���� ��
				else if( checkSelection->upSign == NO &&
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - 0 &&
							middleY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
				//���� �ٱ� ����, ������ �Ʒ����� �ٴ� ������ ���� ��
				else if( checkSelection->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - 0 &&
							endY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
					}
				//���� �ٱ� ����, ������ �Ʒ� �߰����� �ٴ� ������ ���� ��
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


				
			// Selection�� �ٴ� ��ȣ�� SwitchCase�� �� 
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


				// TRUE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� �� 
				if(  checkSelection->trueSign == NO &&
					selectionStartX > stickingStartX &&
					selectionStartX < stickingMiddleX &&
					selectionStartY > stickingStartY  &&
					selectionStartY < stickingMiddleY +0  ){
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkSelection->trueSign = YES ;
				}

				// FALSE�ʿ� �ٱ� ����, ���� ������ �ٴ� ������ ���� ��  
				else if(checkSelection->falseSign == NO && 
						selectionStartX > stickingMiddleX &&
						selectionStartX < stickingEndX &&
				 		selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
				}
				// FALSE�ʿ� �ٱ� ����, ������ ������ �ٴ� ������ ���� ��  
				else if(checkSelection->falseSign == NO && 
						selectionEndX > stickingMiddleX &&
						selectionEndX < stickingEndX &&
				 		selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY +0  ){
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkSelection->falseSign = YES ;
				}
				//���� �ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkSelection->upSign == NO &&
						firstCaseStartX > stickingStartX &&
						firstCaseStartX < stickingEndX &&
						firstCaseEndY > stickingStartY - 0 &&
						firstCaseEndY < stickingEndY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkSelection->upSign = YES ;
				}
				//���� �ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
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
		}//Selection�� ��ȣ�� ���� �� ó�� �Լ� �ݴ� �߰�ȣ
			
		////
		////
		/// ���� ���� ��ȣ�� BeforeRepeat�� ��
		if( dynamic_cast<BeforeRepeat*>(symbol) && i != index  ){
			
			stickingMiddleX = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointX() ;
			stickingMiddleY = (static_cast<BeforeRepeat*>(symbol))->GetMiddlePointY() ;
			BeforeRepeat *checkBeforeRepeat = static_cast<BeforeRepeat*>(symbol) ;
			
			// ���ݺ������� �������� �޶�ٴ� ������ �����̰ų� ������ ��
			if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					dynamic_cast<Selection*>(paper->GetAt( index ))
				) {

				// ���ݺ������� �������� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}
			

				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
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
		


		// BeforeRepeat�� �ٴ� ��ȣ�� BeforeRepeat��
			if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
			{ 
				middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
				middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
				
				// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY &&
						middleY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, ������ �߰����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						endX > stickingStartX &&
						endX < stickingEndX &&
						middleY > stickingStartY &&
						middleY < stickingMiddleY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkBeforeRepeat->inSign = YES ;
				}
					// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO && 
						endX > stickingStartX &&
						endX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
					  	startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO &&  
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO && 
						startX > stickingStartX &&
					 	startX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
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
			// BeforeRepeat�� �ٴ� ��ȣ�� AfterRepeat��
			if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
			{ 
				middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
				middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;


				// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				if( checkBeforeRepeat->inSign == NO &&
					startX > stickingStartX &&
					startX < stickingEndX &&
					startY > stickingStartY &&
					startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, �߰� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						startY > stickingStartY &&
						startY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}

				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						startX > stickingStartX &&
						startX < stickingMiddleX &&
					  	startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, �߰� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						middleX > stickingStartX &&
						middleX < stickingMiddleX &&
						startY > stickingEndY - 20 &&
						startY < stickingEndY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO && 
						endX > stickingStartX &&
					 	endX < stickingEndX &&
						endY > stickingStartY - 0 &&
						endY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO &&  
						middleX > stickingStartX &&
						middleX < stickingEndX &&
						middleY > stickingStartY - 0 &&
						middleY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}	
				// ���ݺ������� ���� �޶�ٱ� ����, ������ �߰����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO && 
						endX > stickingStartX &&
						endX < stickingEndX &&
						middleY > stickingStartY - 0 &&
						middleY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
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
			// BeforeRepeat�� �ٴ� ��ȣ�� SwitchCase�� �� 
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

					
				// ���ݺ������� �������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				if( checkBeforeRepeat->inSign == NO &&
					selectionStartX > stickingStartX &&
					selectionStartX < stickingEndX &&
					selectionStartY > stickingStartY &&
					selectionStartY < stickingMiddleY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 1 ;
						checkBeforeRepeat->inSign = YES ;
				}
				// ���ݺ������� �������� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->inSign == NO &&
						selectionEndX > stickingStartX &&
						selectionEndX < stickingEndX &&
						selectionStartY > stickingStartY &&
						selectionStartY < stickingMiddleY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkBeforeRepeat->inSign = YES ;
				}

				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO && 
						selectionStartX > stickingStartX &&
						selectionStartX < stickingMiddleX &&
					  	selectionStartY > stickingEndY - 20 &&
						selectionStartY < stickingEndY + 0 ) {
						this->stickedIndex = i ;
						this->stickingField = 2 ;
						checkBeforeRepeat->downSign = YES ;
				}
				// ���ݺ������� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->downSign == NO &&  
						selectionEndX > stickingStartX &&
						selectionEndX < stickingMiddleX &&
					  	selectionStartY > stickingEndY - 20 &&
						selectionStartY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 2 ;
							checkBeforeRepeat->downSign = YES ;
				}

				// ���ݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
				else if(checkBeforeRepeat->upSign == NO && 
						firstCaseStartX > stickingStartX &&
						firstCaseStartX < stickingEndX &&
						firstCaseEndY > stickingStartY - 0 &&
						firstCaseEndY < stickingMiddleY ) {
							this->stickedIndex = i ;
							this->stickingField = 3 ;
							checkBeforeRepeat->upSign = YES ;
				}
				// ���ݺ������� ���� �޶�ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
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
		}//BeforeRepeat�� ��ȣ�� ���� �� ó�� �Լ� �ݴ� �߰�ȣ






			////
			////
			/// ���� ���� ��ȣ�� AfterRepeat �� ��
			if( dynamic_cast<AfterRepeat*>(symbol) && i != index ){
			
				stickingMiddleX = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointX() ;
				stickingMiddleY = (static_cast<AfterRepeat*>(symbol))->GetMiddlePointY() ;
				AfterRepeat *checkAfterRepeat = static_cast<AfterRepeat*>(symbol) ;
				// �Ĺݺ������� �Ʒ������� �޶�ٴ� ������ �����̰ų� ������ ��
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) ||
					 dynamic_cast<Selection*>(paper->GetAt( index ))
					) {

					// �Ĺݺ������� �Ʒ������� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					if(	checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ������� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingMiddleY &&
							 startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;

					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, ������ �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}

					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO &&
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
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

				// AfterRepeats�� �ٴ� ��ȣ�� BeforeRepeat��
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
					middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
				
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					if( checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 startY > stickingMiddleY &&
							 startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if( checkAfterRepeat->downSign == NO && 
							 middleX > stickingStartX &&
							 middleX < stickingEndX &&
							 middleY > stickingMiddleY &&
							 middleY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ������ �߰����� �ٴ� ������ ���� ��
					else if( checkAfterRepeat->downSign == NO &&
							 endX > stickingStartX &&
							 endX < stickingEndX &&
							 middleY > stickingMiddleY &&
							 middleY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// �Ĺݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
				
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - 0 &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ������ �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							middleY > stickingStartY - 0 &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}


				}//AfterRepeat�� ��ȣ�� ���� �� ó�� �Լ� �ݴ� �߰�ȣ


				// BeforeRepeat�� �ٴ� ��ȣ�� AfterRepeat��
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;

					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					if( checkAfterRepeat->downSign == NO &&
						startX > stickingStartX &&
						startX < stickingEndX &&
						startY > stickingMiddleY &&
						startY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, �߰� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->downSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							startY > stickingMiddleY &&
							startY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// �Ĺݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, ������ �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							endX > stickingStartX &&
							endX < stickingEndX &&
							endY > stickingStartY - 0  &&
							endY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO &&
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - 0  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO && 
							middleX > stickingStartX &&
							middleX < stickingEndX &&
							middleY > stickingStartY - 0  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO &&
							endX > stickingStartX &&
							endX < stickingEndX &&
							middleY > stickingStartY - 0  &&
							middleY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							startX > stickingStartX &&
							startX < stickingEndX &&
							startY > stickingStartY - 0 &&
							startY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, �߰� ������ �ٴ� ������ ���� ��
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

					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					if( checkAfterRepeat->downSign == NO &&
						selectionStartX > stickingStartX &&
						selectionStartX < stickingEndX &&
						selectionStartY > stickingMiddleY &&
						selectionStartY < stickingEndY + 0 ) {
							this->stickedIndex = i ;
							this->stickingField = 1 ;
							checkAfterRepeat->downSign = YES ;
					}
					// �Ĺݺ������� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->downSign == NO && 
							selectionEndX > stickingStartX &&
							selectionEndX < stickingEndX &&
							selectionStartY > stickingMiddleY &&
							selectionStartY < stickingEndY + 0 ) {
								this->stickedIndex = i ;
								this->stickingField = 1 ;
								checkAfterRepeat->downSign = YES ;
					}

					// �Ĺݺ������� ���� �޶�ٱ� ����, ���� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO &&
							firstCaseStartX > stickingStartX &&
							firstCaseStartX < stickingEndX &&
							firstCaseEndY > stickingStartY - 0  &&
							firstCaseEndY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}
					// �Ĺݺ������� ���� �޶�ٱ� ����, �߰� �Ʒ����� �ٴ� ������ ���� ��
					else if(checkAfterRepeat->upSign == NO &&
							defaultCaseEndX > stickingStartX &&
							defaultCaseEndX < stickingEndX &&
							defaultCaseEndY > stickingStartY - 0  &&
							defaultCaseEndY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkAfterRepeat->upSign = YES ;
					}

					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ���� ������ �ٴ� ������ ���� ��
					else if(checkAfterRepeat->inSign == NO && 
							selectionStartX > stickingStartX &&
							selectionStartX < stickingEndX &&
							selectionStartY > stickingStartY - 0 &&
							selectionStartY < stickingStartY + 20 ) {
								this->stickedIndex = i ;
								this->stickingField = 3 ;
								checkAfterRepeat->inSign = YES ;
					}
					// �Ĺݺ������� ���� �Ʒ��� �޶�ٱ� ����, ������ ������ �ٴ� ������ ���� ��
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



			 } // ��ȣ�� ���� ��ȣ�� AfterRepeat�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ


			 //
			 ///
			 ///
			 // ���� ���� ��ȣ�� SwitchCase �� ��

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
							
				
				// SwitchCase�� �ٴ� ��ȣ�� Sequence �� ��
				if(  dynamic_cast<Sequence*>(paper->GetAt( index )) )
				{ 
						//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, Sequence�� Selection ������ ������ �ٴ� ������ ���� ��//���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
								
							//   SwitchCase�� ���� �ٱ�����, Sequence�� Selection�� ���� �Ʒ����� �ٴ� ������ ���� �� 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
							}
							//   SwitchCase�� ���� �ٱ�����, Sequence�� Selection�� ������ �Ʒ����� �ٴ� ������ ���� �� 
							else if(checkSwitchCaseUpsign == NO &&
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� FALSE�� �Ʒ��� �ٱ� ����, Sequence ������ ������ �ٴ� ������ ���� �� //���α��� �߰����� �ٴ� ������ ���� �� 
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
							//   SwitchCase�� FALSE�� �Ʒ��� �ٱ� ����, Sequence ���� ������ �ٴ� ������ ���� �� 
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
							//   SwitchCase�� FALSE�� �Ʒ��� �ٱ� ����, Sequence ������ ������ �ٴ� ������ ���� �� 
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
				}// // SwitchCase�� �ٴ� ��ȣ�� Sequence�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ


					else if(	 dynamic_cast<Selection*>(paper->GetAt( index )) )
					{ 
							//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, Sequence�� Selection ������ ������ �ٴ� ������ ���� ��//���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
								
							//   SwitchCase�� ���� �ٱ�����, Sequence�� Selection�� ���� �Ʒ����� �ٴ� ������ ���� �� 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
							}
							//   SwitchCase�� ���� �ٱ�����, Sequence�� Selection�� ������ �Ʒ����� �ٴ� ������ ���� �� 
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
					}// // SwitchCase�� �ٴ� ��ȣ�� Selection�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ


					// SwitchCase�� �ٴ� ��ȣ�� BeforeRepeat��
				if(  dynamic_cast<BeforeRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
					middleY = static_cast<BeforeRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
					
					//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, BeforeRepeat ������ ������ �ٴ� ������ ���� �� //���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
							//   SwitchCase�� ���� �ٱ�����, BeforeRepeat�� ���� �Ʒ����� �ٴ� ������ ���� �� 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� ���� �ٱ�����, BeforeRepeat�� ������ �Ʒ����� �ٴ� ������ ���� �� 
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
				}// SwitchCase�� �ٴ� ��ȣ�� BeforeRepeat�� ���� ó���ϴ� �����ݴ� �߰�ȣ



				// SwitchCase�� �ٴ� ��ȣ�� AfterRepeat��
				if(  dynamic_cast<AfterRepeat*>(paper->GetAt( index )) )
				{ 
					middleX = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointX() + moveX ;
					middleY = static_cast<AfterRepeat*>(paper->GetAt( index ))->GetMiddlePointY() + moveY ;
					
					//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, AfterRepeat ������ ������ �ٴ� ������ ���� ��//���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
							//   SwitchCase�� ���� �ٱ�����, AfterRepeat�� ���� �Ʒ����� �ٴ� ������ ���� �� 
							if( checkSwitchCaseUpsign == NO &&
								startX > swtichCaseSelectionStartX &&
								startX < swtichCaseSelectionEndX &&
								endY > swtichCaseSelectionStartY &&
								endY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� ���� �ٱ�����, AfterRepeat�� ������ �Ʒ����� �ٴ� ������ ���� �� 
							else if(checkSwitchCaseUpsign == NO && 
									endX > swtichCaseSelectionStartX &&
									endX < swtichCaseSelectionEndX &&
									endY > swtichCaseSelectionStartY &&
									endY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� ���� �ٱ�����, AfterRepeat�� �̵����� �ٴ� ������ ���� �� 
							else if(checkSwitchCaseUpsign == NO &&
									middleX > swtichCaseSelectionStartX &&
									middleX < swtichCaseSelectionEndX &&
									middleY > swtichCaseSelectionStartY &&
									middleY < swtichCaseSelectionEndY ){
										this->stickedIndex = i ;
										this->stickingField = 2 ;
										checkSwitchCase->upSign = YES ;

							}
							//   SwitchCase�� ���� �ٱ�����, AfterRepeat�� ������ �̵����� �ٴ� ������ ���� �� 
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


				}//  SwitchCase�� �ٴ� ��ȣ�� AfterRepeat�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ
				
				 // SwitchCase�� �ٴ� ��ȣ�� SwitchCase��
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
					//  SwitchCase�� Ư�� case �Ʒ��� �ٱ�����, AfterRepeat ���� ���α��� �߰� ���� �ٴ� ������ ���� �� 
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
							this->stickedCase = j ; //������ ����ġ���̽��� �Ʒ� case�� ���� ���� ù��° case�� �����

							
						}
						j++ ;
		
					}
				
					if( this->stickedCase == -1 )
					{
						// SwitchCase ���� �Ʒ��� Y��ǥ, defaultSequence �Ʒ��� Y��ǥ
						Long firstCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(0)->GetEndPointY() ;
						Long defaultCaseEndY = static_cast<SwitchCase*>(paper->GetAt( index ))->GetCases(static_cast<SwitchCase*>(paper->GetAt( index ))->GetColumnCount())->GetEndPointY() ;
						//  SwitchCase�� ���� �ٱ�����, SwitchCase�� ���� �Ʒ����� �ٴ� ������ ���� �� 
						if( checkSwitchCaseUpsign == NO &&
							selectionStartX > swtichCaseSelectionStartX &&
							selectionStartX < swtichCaseSelectionEndX &&
							firstCaseEndY > swtichCaseSelectionStartY &&
							firstCaseEndY < swtichCaseSelectionEndY ){
								this->stickedIndex = i ;
								this->stickingField = 2 ;
								checkSwitchCase->upSign = YES ;
						}
						//   SwitchCase�� ���� �ٱ�����, SwitchCase�� �߰� �Ʒ����� �ٴ� ������ ���� �� 
						else if(checkSwitchCaseUpsign == NO && 
								selectionMiddleX > swtichCaseSelectionStartX &&
								selectionMiddleX < swtichCaseSelectionEndX &&
								defaultCaseEndY > swtichCaseSelectionStartY &&
								defaultCaseEndY < swtichCaseSelectionEndY ){
									this->stickedIndex = i ;
									this->stickingField = 2 ;
									checkSwitchCase->upSign = YES ;
						}	
						//   SwitchCase�� ���� �ٱ�����, SwitchCase�� ������ �Ʒ����� �ٴ� ������ ���� �� 
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


			 } // ��ȣ�� ���� ��ȣ�� SwitchCase�� ���� ó���ϴ� ���� �ݴ� �߰�ȣ
			i++ ;
		}// while�ݺ��� �ݴ� �߰�ȣ
	//}
}



/*
	�Լ��̸� : GetInfo
	��    �� : ��ȣ�� �ٸ� ��ȣ�� ���� �� �ʿ��� ��ġ�� ũ�� ������ ���Ѵ�
	��    �� : Paper *paper, Long stickedIndex(��ȣ�� ���� ��ȣ�� ÷��), Long stickingField(�ٴ� ������ ���� ����), Long oldIndex
	��    �� : void ( Sticker�� �Ӽ� startX, startY, endX, endY ���鿡�ٰ� ���� ���� ��ġ, ũ�⸦ ���� )
	�� �� �� : i5
*/
void Sticker::GetInfo ( Paper *paper, Long stickedIndex, Long stickingField, Long oldIndex ){
	 
	Symbol *symbol = paper->GetAt( stickedIndex ) ; // ��ȣ�� �ٴ� ��ȣ
	Symbol *oldSymbol = paper->GetAt( oldIndex ) ; // ��ȣ�� �ٴ� ��ȣ
	
	
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
				//Ư�� case�� ���� ��, 
					//�� case�� �������� �����.
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
	�Լ��̸� : StickTo
	��    �� : ��ȣ�� �ٸ� ��ȣ�� ���δ�
	��    �� : Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex
	��    �� : void
	�� �� �� : i5
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
	//�̵���ǥ�� �ٸ� ��ǥ���� �̵��� ���缭 ��ȭ��������Ѵ�
	//������ Ȱ���Ѵ�
		Selection *oldSymbol = static_cast<Selection*>( paper->GetAt( oldIndex ) ) ; // �̵���ǥ�� �б����ؼ� ��ȯ
		double trueWidth = oldSymbol->GetMiddlePointX() - oldSymbol->GetStartPointX() ; // ������ ���ϱ� ���ؼ� trueWidth ���Ѵ�
		double falseWidth = oldSymbol->GetEndPointX() - oldSymbol->GetMiddlePointX() ; // ������ ���ϱ� ���ؼ� falseWidth ���Ѵ�
		double width = this->endX - this->startX ; // �ٿ��� ���� ���α���
		double rateWidth = ( width * ( trueWidth / ( trueWidth + falseWidth ) ) ) ; // ������ ���̸� ���Ѵ�
		Selection *temp = new Selection ( startX , startY , endX, endY, expression ) ; // �켱 �̵��� ��ǥ�� ��ȣ�� �׸���
		
		symbol = new Selection ( // �̵� ��ǥ�� �̵��� ��ȣ�� ���� ������ �׷��� ��ȣ�� �׸���
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
		delete temp ; // �ӽ÷� �׸� ��ȣ �Ҵ� ����

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

	delete paper->GetAt( oldIndex ) ; // ���� symbols�� ��ȣ �Ҵ� ����
	
	//���� �ٿ� �׸� ��ȣ�� Paper::ModifyTo(~) ȣ���ؼ� �ֱ�
	 paper->ModifyTo( symbol, oldIndex ) ;
	//*/
	 return oldIndex ;


}

/*
	�Լ��̸� : SearchTop
	��    �� : ��ȣ���� ���� ��, ���õ� ��ȣ�� �� ���� ���� ��ġ�� ��ȣ�� ã�´�
	��    �� : Paper *paper, Select *select
	��    �� : topIndex
	�� �� �� : i5
*/
void Sticker::SearchTopBottom( Paper *paper, Select *select ) // ���� ���õ� ��ȣ�� �� ���� ���� ��ȣ�� ÷�ڸ� ���Ѵ�
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

		// top ���ϱ�
		if( dynamic_cast<SwitchCase*>(symbol) || dynamic_cast<SwitchCase*>(topSymbol) ){ //�ϳ��� SwitchCase�� �� 
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
		else{ // �� ��  SwitchCase �ƴ� �� 
			if( symbol->GetStartPointY() <  topSymbol->GetStartPointY() ){
				this->topIndex = selectedIndex ;
			}
		}

		// bottom ���ϱ�
		if( dynamic_cast<SwitchCase*>(symbol) || dynamic_cast<SwitchCase*>(bottomSymbol) ){ //�ϳ��� SwitchCase�� �� 
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
		else{ // �� ��  SwitchCase �ƴ� ��
			if( symbol->GetStartPointY() > bottomSymbol->GetStartPointY() ) {
				this->bottomIndex = selectedIndex ;
			}
		}
	}
	// �߰ߵ� ���� ����
		// �Ĺݺ������� ���ʿ� ���� �Լ��� top��ȣ�� �Ǵ� �� ����
	Long sign = -1 ; //topIndex�� �ٲ�� 1�̵Ǿ �ݺ������� Ż���ϰ� �Ѵ�
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
	�Լ��̸� : GetGap
	��    �� : ��ȣ���� ���� ��, ��ȣ���� ��ġ�� �̵��ؾ� �ϴ�  ��ȭ���� ũ���� ��ȭ���� ���Ѵ� 
	��    �� : Paper *paper, Long oldIndex 
	��    �� : void
	�� �� �� : i5
*/
void Sticker::GetGap( Paper *paper, Long oldIndex  ) {// ��ġ��ǥ�� x��,y���� �̵� ��ų �Ÿ��� ���Ѵ�
	// preStartX, preStartY�� oldIndex ��
	// startX, startY��  stickedIndex��

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

	// ���� �� ���̸鼭 ����� ũ�� ���̸� ���ϴ� ����
	Long preWidth =  preEndX - preStartX ;
	Long stickedWidth = (this->endX - this->startX) ;
	this->changingWidth = 0 ;//stickedWidth - preWidth ; //ũ�� �����ؼ� ���ߺ��̱�.
}


/*
	�Լ��̸� : StickBundleTo
	��    �� : ��ȣ���� ���δ�
	��    �� : Paper *paper, Select *select, Long startGapX, Long startGapY
	��    �� : void
	�� �� �� : i5
*/
void  Sticker::StickBundleTo( Paper *paper, Select *select, Long startGapX, Long startGapY ) {// ���� ���õ� ��ȣ���� ���δ�


	Long selectPaperLength = select->GetSelectPaper()->GetLength() ;
	for( Long i = 0 ; i < selectPaperLength ; i++ ) {
		Long selectedIndex = select->GetSelectPaper()->GetAt(i).GetSeletedSymbolIndex() ;
		Symbol *symbol = paper->GetAt( selectedIndex ) ;  
		Symbol *stcikingSymbol ;

			// ��ġ�� �����Ѵ�
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

				Selection *oldSymbol = static_cast<Selection*>( symbol ) ; // �̵���ǥ�� �б����ؼ� ��ȯ
				//double trueWidth = oldSymbol->GetMiddlePointX() - oldSymbol->GetStartPointX() ; // ������ ���ϱ� ���ؼ� trueWidth ���Ѵ�
				//double falseWidth = oldSymbol->GetEndPointX() - oldSymbol->GetMiddlePointX() ; // ������ ���ϱ� ���ؼ� falseWidth ���Ѵ�
				//double width = this->endX - this->startX ; // �ٿ��� ���� ���α���
				//double rateWidth = ( width * ( trueWidth / ( trueWidth + falseWidth ) ) ) ; // ������ ���̸� ���Ѵ�
		

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



		//���� symbols�� ��ȣ �Ҵ� ����
		delete symbol ;

		//���� �ٿ� �׸� ��ȣ�� Paper::ModifyTo(~) ȣ���ؼ� �ֱ�
		paper->ModifyTo( stcikingSymbol, selectedIndex ) ;
		//*/
			
	}
	this->stickedIndex = -1 ;
	this->stickingField = -1 ;
	
}


/*
	�Լ��̸� : StickToForPre
	��    �� : �̵� �߿� ��ȣ�� �ٸ� ��ȣ�� �ٴ� ��Ȳ�̸� ���� �ٿ��� ��ȣ�� ������ �����Ѵ�
	��    �� : Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex
	��    �� : Symbol *symbol
	�� �� �� : i5
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
		//�̵���ǥ�� �ٸ� ��ǥ���� �̵��� ���缭 ��ȭ��������Ѵ�
		//������ Ȱ���Ѵ�
		Selection *oldSymbol = static_cast<Selection*>( paper->GetAt( oldIndex ) ) ; // �̵���ǥ�� �б����ؼ� ��ȯ
		double trueWidth = oldSymbol->GetMiddlePointX() - oldSymbol->GetStartPointX() ; // ������ ���ϱ� ���ؼ� trueWidth ���Ѵ�
		double falseWidth = oldSymbol->GetEndPointX() - oldSymbol->GetMiddlePointX() ; // ������ ���ϱ� ���ؼ� falseWidth ���Ѵ�
		double width = this->endX - this->startX ; // �ٿ��� ���� ���α���
		double rateWidth = ( width * ( trueWidth / ( trueWidth + falseWidth ) ) ) ; // ������ ���̸� ���Ѵ�

		Selection *temp = new Selection ( startX , startY , endX, endY, expression ) ; // �켱 �̵��� ��ǥ�� ��ȣ�� �׸���
		
		this->dotSymbol = new Selection ( // �̵� ��ǥ�� �̵��� ��ȣ�� ���� ������ �׷��� ��ȣ�� �׸���
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
		delete temp ; // �ӽ÷� �׸� ��ȣ �Ҵ� ����

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
	�Լ��̸� : StickBundleToForPre
	��    �� : �̵� �߿� ��ȣ���� �ٸ� ��ȣ�� �ٴ� ��Ȳ�̸� ���� �ٿ��� ��ȣ�� ������ �����Ѵ�
	��    �� : Paper *paper, Long startX, Long startY, Long endX, Long endY, wstring expression, string type, Long oldIndex
	��    �� : Symbol *symbol
	�� �� �� : i5
*/
void Sticker::StickBundleToForPre ( Paper *paper, Select *select, Long startGapX, Long startGapY, Symbol* (*symbols), Long symbolsLength ){

	
	for( Long i = 0 ; i < symbolsLength ; i++ ) 
	{
		Long selectedIndex = select->GetSelectPaper()->GetAt(i).GetSeletedSymbolIndex() ;
		Symbol *symbol = paper->GetAt( selectedIndex ) ;  
		Symbol *stcikingSymbol ;

			// ��ġ�� �����Ѵ�
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

				Selection *oldSymbol = static_cast<Selection*>( symbol ) ; // �̵���ǥ�� �б����ؼ� ��ȯ
				//double trueWidth = oldSymbol->GetMiddlePointX() - oldSymbol->GetStartPointX() ; // ������ ���ϱ� ���ؼ� trueWidth ���Ѵ�
				//double falseWidth = oldSymbol->GetEndPointX() - oldSymbol->GetMiddlePointX() ; // ������ ���ϱ� ���ؼ� falseWidth ���Ѵ�
				//double width = this->endX - this->startX ; // �ٿ��� ���� ���α���
				//double rateWidth = ( width * ( trueWidth / ( trueWidth + falseWidth ) ) ) ; // ������ ���̸� ���Ѵ�
		

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
	�Լ��̸� : StickLine
	��    �� : ������ �� ������ �����ش�
	��    �� : Paper *paper, Long modifiedIndex, Long transNumber
	��    �� : Long ( ÷�� )
	�� �� �� : i5
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

	// ��ģ ��ȣ�� ���������̰�, �������� 6���̸� 
	if( dynamic_cast<Sequence*>( modifiedSymbol ) && transNumber == 6 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY)�� (endX, endY) )�� ������
			paperSymbol = paper->GetAt(i) ;
			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// ���������� BeforeRepeat�ȿ��� 6�� �������� ���� �� 
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
			{// ���������� AfterRepeat�ȿ��� 6�� �������� ���� �� 
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
			
			// 1. ��ģ ���������� ������ ������ ������ ,
				// ��ȣ�� ���� �Ʒ� ������ �������� ���� �� 
			if(  paperStartX >= modifiedEndX &&
				 paperStartX <= modifiedEndX + LINE &&
				 paperEndY >= modifiedEndY - LINE &&
				 paperEndY <= modifiedEndY + LINE &&
				 i != modifiedIndex)
			{
				lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
			}
			// 2. ��ģ ���������� ���� ������ ������ ,
				// ��ȣ�� ������ �Ʒ� ������ �������� ���� �� 
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



	// ��ģ ��ȣ�� ���ݺ������̰�, �������� 6���̸� 
	else if( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) && transNumber == 6 )
	{
		modifiedMiddlePointX = (static_cast<BeforeRepeat*>( modifiedSymbol ))->GetMiddlePointX() ;
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY))�� ������
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;

			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// ���ݺ������� BeforeRepeat�ȿ��� 6�� �������� ���� �� 
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
			{// ���ݺ������� AfterRepeat�ȿ��� 6�� �������� ���� �� 
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
			


			// 1. ��ģ ���ݺ������� ������ ������ ������ ,
				// ��ȣ�� ���� �Ʒ� ������ �������� ���� �� 
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




	// ��ģ ��ȣ�� �Ĺݺ������̰�, �������� 6���̸� 
	else if( dynamic_cast<AfterRepeat*>( modifiedSymbol ) && transNumber == 6 )
	{
		modifiedMiddlePointX = (static_cast<AfterRepeat*>( modifiedSymbol ))->GetMiddlePointX() ;
		modifiedMiddlePointY = (static_cast<AfterRepeat*>( modifiedSymbol ))->GetMiddlePointY() ;
		
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY)�� ������
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;


			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// �Ĺݺ������� BeforeRepeat�ȿ��� 6�� �������� ���� �� 
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
			{// �Ĺݺ������� AfterRepeat�ȿ��� 6�� �������� ���� �� 
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
			

			// 1. ��ģ �Ĺݺ������� ������ ������ ������ ,
				// ��ȣ�� ���� �Ʒ� ������ �������� ���� �� 
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

	// ��ģ ��ȣ�� �������� 4���̸� // ��ǥ�� modifiedSymbol�� ���α��� ����
	if( transNumber == 4 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY)�� (endX, endY) )�� ������
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{ // paperSymbol�� BeforeRepeat�̸� 
				
				Long paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
		
				// ��ģ ��ȣ�� ������ �� ������ �κ��� Ư�� ������,
					// BeforeRepeat�� ����� ������ �Ʒ� ������ ������(endX, middleY)�� ���� ��
				if ( paperEndX >= modifiedEndX - LINE &&
					 paperEndX <= modifiedEndX + LINE &&
					 paperMiddleY >= modifiedStartY - LINE &&
					 paperMiddleY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol�� endX��ǥ�� �����Ѵ�
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
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // �̵���ǥ�� �б����ؼ� ��ȯ
							
							lineSymbol = new Selection ( // �̵� ��ǥ�� �̵��� ��ȣ�� ���� ������ �׷��� ��ȣ�� �׸���
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
			{// paperSybmol�� BeforeRepeat�� �ƴϸ�
			// ��ģ ��ȣ�� ������ �� ������ �κ��� Ư�� ������,
				// ��ȣ�� ������ �Ʒ� ������ ������(endX, endY)�� ���� �� 
				if ( paperEndX >= modifiedEndX - LINE &&
					 paperEndX <= modifiedEndX + LINE &&
					 paperEndY >= modifiedStartY - LINE &&
					 paperEndY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol�� endX��ǥ�� �����Ѵ�
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
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // �̵���ǥ�� �б����ؼ� ��ȯ
							lineSymbol = new Selection ( // �̵� ��ǥ�� �̵��� ��ȣ�� ���� ������ �׷��� ��ȣ�� �׸���
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
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY)�� (endX, endY) )�� ������
			paperSymbol = paper->GetAt(i) ;
			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			// ��ģ ��ȣ�� ������ �� ������ �κ��� Ư�� ������,
				// ��ȣ�� ������ �Ʒ� ������ ������(endX, endY)�� ���� �� 
				if ( paperStartX >= modifiedStartX - LINE &&
					 paperStartX <= modifiedStartX + LINE &&
					 paperEndY >= modifiedStartY - LINE &&
					 paperEndY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol�� endX��ǥ�� �����Ѵ�
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
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // �̵���ǥ�� �б����ؼ� ��ȯ
							lineSymbol = new Selection ( // �̵� ��ǥ�� �̵��� ��ȣ�� ���� ������ �׷��� ��ȣ�� �׸���
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
		delete paper->GetAt( modifiedIndex ) ; // ���� symbols�� ��ȣ �Ҵ� ����
		//���� �ٿ� �׸� ��ȣ�� Paper::ModifyTo(~) ȣ���ؼ� �ֱ�
		 paper->ModifyTo( lineSymbol, modifiedIndex ) ;
	}
		
	//*/
	return modifiedIndex ;
}

/*
	�Լ��̸� : StickLineForPre
	��    �� : ������ �� ������ ������ ��, �̸� ������ ��ȣ�� �����
	��    �� : Paper *paper, Long modifiedIndex, Long transNumber
	��    �� : Long ( ÷�� )
	�� �� �� : i5
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

	// ��ģ ��ȣ�� ���������̰�, �������� 6���̸� 
	if( dynamic_cast<Sequence*>( modifiedSymbol ) && transNumber == 6 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY)�� (endX, endY) )�� ������
			paperSymbol = paper->GetAt(i) ;
			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// ���������� BeforeRepeat�ȿ��� 6�� �������� ���� �� 
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
			{// ���������� AfterRepeat�ȿ��� 6�� �������� ���� �� 
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
			
			// 1. ��ģ ���������� ������ ������ ������ ,
				// ��ȣ�� ���� �Ʒ� ������ �������� ���� �� 
			if(  paperStartX >= modifiedEndX &&
				 paperStartX <= modifiedEndX + LINE &&
				 paperEndY >= modifiedEndY - LINE &&
				 paperEndY <= modifiedEndY + LINE &&
				 i != modifiedIndex)
			{
				lineSymbol = new Sequence ( modifiedSymbol->GetStartPointX() , modifiedSymbol->GetStartPointY() , modifiedSymbol->GetEndPointX(), paperEndY, modifiedSymbol->GetExpression() ) ;
			}
			// 2. ��ģ ���������� ���� ������ ������ ,
				// ��ȣ�� ������ �Ʒ� ������ �������� ���� �� 
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



	// ��ģ ��ȣ�� ���ݺ������̰�, �������� 6���̸� 
	else if( dynamic_cast<BeforeRepeat*>( modifiedSymbol ) && transNumber == 6 )
	{
		modifiedMiddlePointX = (static_cast<BeforeRepeat*>( modifiedSymbol ))->GetMiddlePointX() ;
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY))�� ������
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;

			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// ���ݺ������� BeforeRepeat�ȿ��� 6�� �������� ���� �� 
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
			{// ���ݺ������� AfterRepeat�ȿ��� 6�� �������� ���� �� 
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
			


			// 1. ��ģ ���ݺ������� ������ ������ ������ ,
				// ��ȣ�� ���� �Ʒ� ������ �������� ���� �� 
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




	// ��ģ ��ȣ�� �Ĺݺ������̰�, �������� 6���̸� 
	else if( dynamic_cast<AfterRepeat*>( modifiedSymbol ) && transNumber == 6 )
	{
		modifiedMiddlePointX = (static_cast<AfterRepeat*>( modifiedSymbol ))->GetMiddlePointX() ;
		modifiedMiddlePointY = (static_cast<AfterRepeat*>( modifiedSymbol ))->GetMiddlePointY() ;
		
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY)�� ������
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;


			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{// �Ĺݺ������� BeforeRepeat�ȿ��� 6�� �������� ���� �� 
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
			{// �Ĺݺ������� AfterRepeat�ȿ��� 6�� �������� ���� �� 
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
			

			// 1. ��ģ �Ĺݺ������� ������ ������ ������ ,
				// ��ȣ�� ���� �Ʒ� ������ �������� ���� �� 
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

	// ��ģ ��ȣ�� �������� 4���̸� // ��ǥ�� modifiedSymbol�� ���α��� ����
	if( transNumber == 4 )
	{
		for( Long i = 0 ; i < paper->GetLength() ; i++ ) 
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY)�� (endX, endY) )�� ������
			paperSymbol = paper->GetAt(i) ;

			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			if( dynamic_cast<BeforeRepeat*>( paperSymbol ) )
			{ // paperSymbol�� BeforeRepeat�̸� 
				
				Long paperMiddleY = (static_cast<AfterRepeat*>( paperSymbol ))->GetMiddlePointY() ;
		
				// ��ģ ��ȣ�� ������ �� ������ �κ��� Ư�� ������,
					// BeforeRepeat�� ����� ������ �Ʒ� ������ ������(endX, middleY)�� ���� ��
				if ( paperEndX >= modifiedEndX - LINE &&
					 paperEndX <= modifiedEndX + LINE &&
					 paperMiddleY >= modifiedStartY - LINE &&
					 paperMiddleY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol�� endX��ǥ�� �����Ѵ�
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
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // �̵���ǥ�� �б����ؼ� ��ȯ
							
							lineSymbol = new Selection ( // �̵� ��ǥ�� �̵��� ��ȣ�� ���� ������ �׷��� ��ȣ�� �׸���
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
			else { // paperSymbol�� BeforeRepeat�� �ƴϸ�
			// ��ģ ��ȣ�� ������ �� ������ �κ��� Ư�� ������,
				// ��ȣ�� ������ �Ʒ� ������ ������(endX, endY)�� ���� �� 
				if ( paperEndX >= modifiedEndX - LINE &&
					 paperEndX <= modifiedEndX + LINE &&
					 paperEndY >= modifiedStartY - LINE &&
					 paperEndY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol�� endX��ǥ�� �����Ѵ�
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
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // �̵���ǥ�� �б����ؼ� ��ȯ
							lineSymbol = new Selection ( // �̵� ��ǥ�� �̵��� ��ȣ�� ���� ������ �׷��� ��ȣ�� �׸���
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
		{	// ��ģ ��ȣ�� Ư�� ������ �ٿ��׷����� ��ȣ(�� ��ȣ�� (startX,endY)�� (endX, endY) )�� ������
			paperSymbol = paper->GetAt(i) ;
			paperStartX = paperSymbol->GetStartPointX() ;
			paperEndX = paperSymbol->GetEndPointX() ;
			paperEndY = paperSymbol->GetEndPointY() ;
			// ��ģ ��ȣ�� ������ �� ������ �κ��� Ư�� ������,
				// ��ȣ�� ������ �Ʒ� ������ ������(endX, endY)�� ���� �� 
				if ( paperStartX >= modifiedStartX - LINE &&
					 paperStartX <= modifiedStartX + LINE &&
					 paperEndY >= modifiedStartY - LINE &&
					 paperEndY <= modifiedStartY &&
					 i != modifiedIndex)
				{// modifiedSymbol�� endX��ǥ�� �����Ѵ�
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
							Selection *oldSymbol = static_cast<Selection*>( modifiedSymbol )  ; // �̵���ǥ�� �б����ؼ� ��ȯ
							lineSymbol = new Selection ( // �̵� ��ǥ�� �̵��� ��ȣ�� ���� ������ �׷��� ��ȣ�� �׸���
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
	�Լ��̸� : CheckStickingSign
	��    �� : �Ű������� ���� index��ȣ�� ���� ���� ��ȣ�� �پ��ִ��� Ȯ���ؼ� stickSign���� ��ȭ��Ų��
	��    �� : Paper *paper, Long index( ���� ����ȣ�� ÷�� )
	��    �� : index
	�� �� �� : i5
	Ư�̻��� : �ٴ� ������ ��ȣ�� ���ο� ���������� �ܺ�// �׸� �� ��� ��
*/
Long Sticker::CheckStickingSign ( Paper *paper, Long index ) 
 {
	Symbol *indexSymbol = paper->GetAt( index ) ;// Ư����ȣ
	
	
	//Ư����ȣ�� Sequence�� ��
	if ( dynamic_cast<Sequence*>( indexSymbol ) ) 
	{ 
		Sequence *indexSequence = static_cast<Sequence*>(indexSymbol) ;
			
		// NO�� �صд�
		indexSequence->upSign = NO ;
		indexSequence->downSign = NO ;
			
		Long indexStartX = indexSequence->GetStartPointX() ;
		Long indexStartY = indexSequence->GetStartPointY() ;
		Long indexEndX = indexSequence->GetEndPointX() ;
		Long indexEndY = indexSequence->GetEndPointY() ;

		// upSign ���� ����
		Long i = 0 ;
		while( indexSequence->upSign == NO && i < paper->GetLength() ) // YES�� Ż���ϰ� ���صд�
		{ 
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� SwitchCase�� ��, checkedSymbol�� indexSequence���� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� cases�� indexSequence�� �پ��ִ��� ����
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

					// indexSequence�� �ִ� ���� 
					if( indexSequence->upSign == NO ) // cases�Ʒ��� �پ����� ������, ���������� false�ʿ� �پ��ִ��� Ȯ���غ���
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
				} // checkedSymbol�� SwitchCase�� �� ��.

				else  // checkedSymbol�� SwitchCase�� �ƴ� ��, checkedSymbol�� indexSequence���� �پ��ִ��� �����Ѵ�
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // ���� ���� ��ȣ�� Selection�϶� FALSE�ʿ� index��ȣ�� �پ��ִ��� Ȯ�ζ����� ���� ó��
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
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� BeforeRepeat�� ��, index��ȣ�� BeforeRepeat�� ���ʿ� �پ��ִ��� Ȯ�� ������ ���� ó��
					{
						//1) BeforeRepeat�� �̵��� == indexSequence�� ��ġ
						//2) BeforeRepeat�� ���� �Ʒ��� == indexSequence�� ��ġ
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
					else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� AfterRepeat�� ��, index��ȣ�� AfterRepeat�� ���ʿ� �پ��ִ��� Ȯ��
					{
						//- �Ĺݺ������� �̵� ������ ������, ��� ��ȣ���� upSign�� yes�Ǿ�� �Ѵ�!!!!
							//- �Ĺݺ������� �̵� ���� ( middleX, startY )
						//- �Ĺݺ������� ���� ���� upSign�� �����ؾ��ϹǷ� �Ĺݺ������� ���� �Ʒ����� �ٴ� ��ȣ���� upSign�� �Բ� yes�� �����
							//- �Ĺݺ������� ���� �Ʒ��� ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexSequence->upSign = YES ; // indexSequence ���� ��ȣ�� �پ��ִ�
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexSequence->upSign = YES ; // indexSequence ���� ��ȣ�� �پ��ִ�
						}

					}
				
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexSequence�� ���� ������, checkedSymbol�� ���� �Ʒ����� ������ 
					{ 
								indexSequence->upSign = YES ; // indexSequence ���� ��ȣ�� �پ��ִ�
					}
				}
			} // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;

		}// While ���� indexSequence upSign ���� ��

		// indexSequence downSign ���� ����
		i = 0 ;
		while( indexSequence->downSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol�� SwitchCase�� ��, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� indexSequence�Ʒ��� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� indexSequence�� �Ʒ��� �پ��ִ��� ����
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexStartX == switchCaseSelectionStartX &&
						indexEndY == switchCaseSelectionStartY ) 
					{
						indexSequence->downSign = YES ;
					}
				}

				// checkedSymbol�� SwitchCase�� �ƴ� ��
				else  //checkedSymbol�� indexSequence�Ʒ��� �پ��ִ��� �����Ѵ�
				{			
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndX = checkedSymbol->GetEndPointX() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					if ( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� BeforeRepeat�� ��, downSign ���� ��� ó��
					{
						// BeforeRepeat�� �߰� �Ʒ����� indexSequence���� �� ó���� ���� ����
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
					else if ( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� AfterRepeat�� ��, downSign ���� ��� ó��
					{
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						//1} �Ĺݺ������� �̵��� == ������ ���� �Ʒ���
						//2} �Ĺݺ������� ���� ���� == ������ ���� �Ʒ���
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
						 	 indexEndY == checkStartY ) // indexSequence�� ���� �Ʒ�����, checkedSymbol�� ���� ������ ������
					{
						indexSequence->downSign = YES ; // indexSequence �Ʒ��� ��ȣ�� �پ��ִ�
					}	
					else if( indexEndX == checkEndX &&
								 indexEndY == checkStartY )
					{
							indexSequence->downSign = YES ;
					}
				}
			}  // �ڱ� �ڽ��� ���翡�� ���� ��

			i++ ;
		}// While ���� indexSequence downSign ���� ��

	}//Ư����ȣ�� Sequence�� �� ��
		
	
	//Ư����ȣ�� Selectino �� ��
	else if ( dynamic_cast<Selection*>( indexSymbol ) ) 
	{ 
		Selection *indexSelection = static_cast<Selection*>(indexSymbol) ;
			
		// NO�� �صд�
		indexSelection->upSign = NO ;
		indexSelection->trueSign = NO ;
		indexSelection->falseSign = NO ;

		Long indexStartX = indexSelection->GetStartPointX() ;
		Long indexStartY = indexSelection->GetStartPointY() ;
		Long indexEndX = indexSelection->GetEndPointX() ;
		Long indexEndY = indexSelection->GetEndPointY() ;

		// upSign ���� ����
		Long i = 0 ;
		while( indexSelection->upSign == NO && i < paper->GetLength() ) // YES�� Ż���ϰ� ���صд�
		{
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� SwitchCase�� ��, checkedSymbol�� indexSelection���� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� cases�� indexSelection�� �پ��ִ��� ����
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
				} // checkedSymbol�� SwitchCase�� �� ��.

				else  // checkedSymbol�� SwitchCase�� �ƴ� ��, checkedSymbol�� indexSelection���� �پ��ִ��� �����Ѵ�
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // ���� ���� ��ȣ�� Selection�϶� FALSE�ʿ� index��ȣ�� �پ��ִ��� Ȯ�ζ����� ���� ó��
					{
						Long checkSelectionStartX = static_cast<Selection*>(checkedSymbol)->GetStartPointX() ;
						Long checkSelectionEndX= static_cast<Selection*>(checkedSymbol)->GetEndPointY() ;
						Long checkMiddleX = static_cast<Selection*>(checkedSymbol)->GetMiddlePointX() ; 
						Long checkMiddleY = static_cast<Selection*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkSelectionStartX &&
							indexStartY == checkSelectionEndX ) // true�ʿ� �پ����� �� 
						{
								indexSelection->upSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkMiddleY ) // false�ʿ� �پ����� �� 
						{
								indexSelection->upSign = YES ;
						}
					}
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� BeforeRepeat�� ��, index��ȣ�� BeforeRepeat�� ���ʿ� �پ��ִ��� Ȯ�� ������ ���� ó��
					{
						//1) BeforeRepeat�� �̵��� == indexSelection�� ��ġ
						//2) BeforeRepeat�� ���� �Ʒ��� == indexSelection�� ��ġ
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

					else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� AfterRepeat�� ��, index��ȣ�� AfterRepeat�� ���ʿ� �پ��ִ��� Ȯ��
					{
						//- �Ĺݺ������� �̵� ������ ������, ��� ��ȣ���� upSign�� yes�Ǿ�� �Ѵ�!!!!
							//- �Ĺݺ������� �̵� ���� ( middleX, startY )
						//- �Ĺݺ������� ���� ���� upSign�� �����ؾ��ϹǷ� �Ĺݺ������� ���� �Ʒ����� �ٴ� ��ȣ���� upSign�� �Բ� yes�� �����
							//- �Ĺݺ������� ���� �Ʒ��� ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexSelection->upSign = YES ; // indexSelection ���� ��ȣ�� �پ��ִ�
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexSelection->upSign = YES ; // indexSelection ���� ��ȣ�� �پ��ִ�
						}

					}
				
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexSelection�� ���� ������, checkedSymbol�� ���� �Ʒ����� ������ 
					{ 
								indexSelection->upSign = YES ; // indexSelection ���� ��ȣ�� �پ��ִ�
					}
				}
			} // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// while () upSign ���� ��

		// indexSelection trueSign ���� ����
		i = 0 ;
		while( indexSelection->trueSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol�� SwitchCase�� ��, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� indexSelection�Ʒ��� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� indexSelection�� true�� �پ��ִ��� ����
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexStartX == switchCaseSelectionStartX &&
						indexEndY == switchCaseSelectionStartY ) 
					{
						indexSelection->trueSign = YES ;
					}
				}

				// checkedSymbol�� SwitchCase�� �ƴ� ��
				else  //checkedSymbol�� indexSelection true�� �پ��ִ��� �����Ѵ�
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
			}  // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// While ���� indexSelection trueSign ���� ��

		// indexSelection falseSign ���� ����
		i = 0 ;
		while( indexSelection->falseSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				Long indexMiddleX = indexSelection->GetMiddlePointX() ;
				Long indexMiddleY = indexSelection->GetMiddlePointY() ;

				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol�� SwitchCase�� ��, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� indexSelection�Ʒ��� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� indexSelection�� false�� �پ��ִ��� ����
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexMiddleX == switchCaseSelectionStartX &&
						indexMiddleY == switchCaseSelectionStartY ) 
					{
						indexSelection->falseSign = YES ;
					}
				}

				// checkedSymbol�� SwitchCase�� �ƴ� ��
				else  //checkedSymbol�� indexSelection false�� �پ��ִ��� �����Ѵ�
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
			}  // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// While ���� indexSelection falseSign ���� ��
	}//Ư����ȣ�� Selectino �� �� ��


	//Ư����ȣ�� BeforeRepeat �� ��
	else if ( dynamic_cast<BeforeRepeat*>( indexSymbol ) ) 
	{ 
		BeforeRepeat *indexBeforeRepeat = static_cast<BeforeRepeat*>(indexSymbol) ;
			
		// NO�� �صд�
		indexBeforeRepeat->upSign = NO ;
		indexBeforeRepeat->downSign = NO ;
		indexBeforeRepeat->inSign = NO ;

		Long indexStartX = indexBeforeRepeat->GetStartPointX() ;
		Long indexStartY = indexBeforeRepeat->GetStartPointY() ;
		Long indexEndX = indexBeforeRepeat->GetEndPointX() ;
		Long indexEndY = indexBeforeRepeat->GetEndPointY() ;

		// upSign ���� ����
		Long i = 0 ;
		while( indexBeforeRepeat->upSign == NO && i < paper->GetLength() ) // YES�� Ż���ϰ� ���صд�
		{
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� SwitchCase�� ��, checkedSymbol�� indexBeforeRepeat���� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� cases�� indexBeforeRepeat�� �پ��ִ��� ����
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
				} // checkedSymbol�� SwitchCase�� �� ��.

				else  // checkedSymbol�� SwitchCase�� �ƴ� ��, checkedSymbol�� indexBeforeRepeat���� �پ��ִ��� �����Ѵ�
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // ���� ���� ��ȣ�� Selection�϶� FALSE�ʿ� index��ȣ�� �پ��ִ��� Ȯ�ζ����� ���� ó��
					{
						Long checkSelectionStartX = static_cast<Selection*>(checkedSymbol)->GetStartPointX() ;
						Long checkSelectionEndX= static_cast<Selection*>(checkedSymbol)->GetEndPointY() ;
						Long checkMiddleX = static_cast<Selection*>(checkedSymbol)->GetMiddlePointX() ; 
						Long checkMiddleY = static_cast<Selection*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkSelectionStartX &&
							indexStartY == checkSelectionEndX ) // true�ʿ� �پ����� �� 
						{
								indexBeforeRepeat->upSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkMiddleY ) // false�ʿ� �پ����� �� 
						{
								indexBeforeRepeat->upSign = YES ;
						}
					}
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� BeforeRepeat�� ��, index��ȣ�� BeforeRepeat�� ���ʿ� �پ��ִ��� Ȯ�� ������ ���� ó��
					{
						//1) BeforeRepeat�� �̵��� == indexBeforeRepeat�� ��ġ
						//2) BeforeRepeat�� ���� �Ʒ��� == indexBeforeRepeat�� ��ġ
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
						else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� AfterRepeat�� ��, index��ȣ�� AfterRepeat�� ���ʿ� �پ��ִ��� Ȯ��
					{
						//- �Ĺݺ������� �̵� ������ ������, ��� ��ȣ���� upSign�� yes�Ǿ�� �Ѵ�!!!!
							//- �Ĺݺ������� �̵� ���� ( middleX, startY )
						//- �Ĺݺ������� ���� ���� upSign�� �����ؾ��ϹǷ� �Ĺݺ������� ���� �Ʒ����� �ٴ� ��ȣ���� upSign�� �Բ� yes�� �����
							//- �Ĺݺ������� ���� �Ʒ��� ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexBeforeRepeat->upSign = YES ; // indexBeforeRepeat ���� ��ȣ�� �پ��ִ�
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexBeforeRepeat->upSign = YES ; // indexBeforeRepeat ���� ��ȣ�� �پ��ִ�
						}

					}
				
				
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexBeforeRepeat�� ���� ������, checkedSymbol�� ���� �Ʒ����� ������ 
					{ 
								indexBeforeRepeat->upSign = YES ; // indexBeforeRepeat ���� ��ȣ�� �پ��ִ�
					}
				}
			} // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// while() upSign ���� ��
	

		
		// indexBeforeRepeat downSign ���� ����
		i = 0 ;
		while( indexBeforeRepeat->downSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol�� SwitchCase�� ��, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� indexBeforeRepeat�Ʒ��� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� indexBeforeRepeat�� true�� �پ��ִ��� ����
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexStartX == switchCaseSelectionStartX &&
						indexEndY == switchCaseSelectionStartY ) 
					{
						indexBeforeRepeat->downSign = YES ;
					}
				}

				// checkedSymbol�� SwitchCase�� �ƴ� ��
				else  //checkedSymbol�� indexBeforeRepeat �Ʒ��� �پ��ִ��� �����Ѵ�
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
			}  // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// While ���� indexBeforeRepeat downSign ���� ��

		// indexBeforeRepeat inSign ���� ����
		i = 0 ;
		while( indexBeforeRepeat->inSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				Long indexMiddleX = indexBeforeRepeat->GetMiddlePointX() ;
				Long indexMiddleY = indexBeforeRepeat->GetMiddlePointY() ;
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol�� SwitchCase�� ��, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� indexBeforeRepeat�ȿ� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� indexBeforeRepeat�� true�� �پ��ִ��� ����
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexMiddleX == switchCaseSelectionStartX &&
						indexMiddleY == switchCaseSelectionStartY ) 
					{
						indexBeforeRepeat->inSign = YES ;
					}
				}

				// checkedSymbol�� SwitchCase�� �ƴ� ��
				else  //checkedSymbol�� indexBeforeRepeat �ȿ� �پ��ִ��� �����Ѵ�
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
			}  // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// While ���� indexBeforeRepeat inSign ���� ��
	} //Ư����ȣ�� BeforeRepeat �� �� ��


	
	//Ư����ȣ�� AfterRepeat �� ��
	else if ( dynamic_cast<AfterRepeat*>( indexSymbol ) ) 
	{ 
		AfterRepeat *indexAfterRepeat = static_cast<AfterRepeat*>(indexSymbol) ;
			
		// NO�� �صд�
		indexAfterRepeat->upSign = NO ;
		indexAfterRepeat->downSign = NO ;
		indexAfterRepeat->inSign = NO ;

		Long indexStartX = indexAfterRepeat->GetStartPointX() ;
		Long indexStartY = indexAfterRepeat->GetStartPointY() ;
		Long indexEndX = indexAfterRepeat->GetEndPointX() ;
		Long indexEndY = indexAfterRepeat->GetEndPointY() ;

		// upSign ���� ����
		Long i = 0 ;
		while( indexAfterRepeat->upSign == NO && i < paper->GetLength() ) // YES�� Ż���ϰ� ���صд�
		{
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� SwitchCase�� ��, checkedSymbol�� indexAfterRepeat���� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� cases�� indexAfterRepeat�� �پ��ִ��� ����
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
				} // checkedSymbol�� SwitchCase�� �� ��.

				else  // checkedSymbol�� SwitchCase�� �ƴ� ��, checkedSymbol�� indexAfterRepeat���� �پ��ִ��� �����Ѵ�
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // ���� ���� ��ȣ�� Selection�϶� FALSE�ʿ� index��ȣ�� �پ��ִ��� Ȯ�ζ����� ���� ó��
					{
						Long checkSelectionStartX = static_cast<Selection*>(checkedSymbol)->GetStartPointX() ;
						Long checkSelectionEndX= static_cast<Selection*>(checkedSymbol)->GetEndPointY() ;
						Long checkMiddleX = static_cast<Selection*>(checkedSymbol)->GetMiddlePointX() ; 
						Long checkMiddleY = static_cast<Selection*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkSelectionStartX &&
							indexStartY == checkSelectionEndX ) // true�ʿ� �پ����� �� 
						{
								indexAfterRepeat->upSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkMiddleY ) // false�ʿ� �پ����� �� 
						{
								indexAfterRepeat->upSign = YES ;
						}
					}
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� BeforeRepeat�� ��, index��ȣ�� BeforeRepeat�� ���ʿ� �پ��ִ��� Ȯ�� ������ ���� ó��
					{
						//1) BeforeRepeat�� �̵��� == indexAfterRepeat�� ��ġ
						//2) BeforeRepeat�� ���� �Ʒ��� == indexAfterRepeat�� ��ġ
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
					else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� AfterRepeat�� ��, index��ȣ�� AfterRepeat�� ���ʿ� �پ��ִ��� Ȯ��
					{
						//- �Ĺݺ������� �̵� ������ ������, ��� ��ȣ���� upSign�� yes�Ǿ�� �Ѵ�!!!!
							//- �Ĺݺ������� �̵� ���� ( middleX, startY )
						//- �Ĺݺ������� ���� ���� upSign�� �����ؾ��ϹǷ� �Ĺݺ������� ���� �Ʒ����� �ٴ� ��ȣ���� upSign�� �Բ� yes�� �����
							//- �Ĺݺ������� ���� �Ʒ��� ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexAfterRepeat->upSign = YES ; // indexAfterRepeat ���� ��ȣ�� �پ��ִ�
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexAfterRepeat->upSign = YES ; // indexAfterRepeat ���� ��ȣ�� �پ��ִ�
						}

					}
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexBeforeRepeat�� ���� ������, checkedSymbol�� ���� �Ʒ����� ������ 
					{ 
								indexAfterRepeat->upSign = YES ; // indexBeforeRepeat ���� ��ȣ�� �پ��ִ�
					}
				}
			} // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// while() upSign ���� ��
	

		
		// indexAfterRepeat downSign ���� ����
		i = 0 ;
		while( indexAfterRepeat->downSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol�� SwitchCase�� ��, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� indexAfterRepeat�Ʒ��� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� indexBeforeRepeat�� true�� �پ��ִ��� ����
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexStartX == switchCaseSelectionStartX &&
						indexEndY == switchCaseSelectionStartY ) 
					{
						indexAfterRepeat->downSign = YES ;
					}
				}

				// checkedSymbol�� SwitchCase�� �ƴ� ��
				else  //checkedSymbol�� indexBeforeRepeat �Ʒ��� �پ��ִ��� �����Ѵ�
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
			}  // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// While ���� indexAfterRepeat downSign ���� ��

		// indexAfterRepeat inSign ���� ����
		i = 0 ;
		while( indexAfterRepeat->inSign == NO && i < paper->GetLength() )
		{ 
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				Long indexMiddleX = indexAfterRepeat->GetMiddlePointX() ;
				//Long indexMiddleY = indexAfterRepeat->GetMiddlePointY() ;
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ;


				// checkedSymbol�� SwitchCase�� ��, 
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� indexBeforeRepeat�ȿ� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� indexBeforeRepeat�� true�� �پ��ִ��� ����
					Long switchCaseSelectionStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long switchCaseSelectionStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;
					if( indexMiddleX == switchCaseSelectionStartX &&
						indexStartY == switchCaseSelectionStartY ) 
					{
						indexAfterRepeat->inSign = YES ;
					}
				}

				// checkedSymbol�� SwitchCase�� �ƴ� ��
				else  //checkedSymbol�� indexBeforeRepeat �ȿ� �پ��ִ��� �����Ѵ�
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
			}  // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// While ���� indexAfterRepeat inSign ���� ��
	} //Ư����ȣ�� indexAfterRepeat �� �� ��


	//Ư����ȣ�� SwitchCase �� ��
	else if ( dynamic_cast<SwitchCase*>( indexSymbol ) ) 
	{ 
		SwitchCase *indexSwitchCase = static_cast<SwitchCase*>(indexSymbol) ;
			
		// NO�� �صд�
		indexSwitchCase->upSign = NO ;
		indexSwitchCase->falseSign = NO ;
		for( Long i = 0 ; i < indexSwitchCase->GetLength() ; i++ ){
			indexSwitchCase->GetCases( i )->downSign = NO ;
		}

		Long indexStartX = indexSwitchCase->GetSelection()->GetStartPointX() ;
		Long indexStartY = indexSwitchCase->GetSelection()->GetStartPointY() ;
		Long indexEndY = indexSwitchCase->GetCases(0)->GetEndPointY() ;

		// upSign ���� ����
		Long i = 0 ;
		while( indexSwitchCase->upSign == NO && i < paper->GetLength() ) // YES�� Ż���ϰ� ���صд�
		{
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� SwitchCase�� ��, checkedSymbol�� indexSwitchCase���� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;

					// SwitchCase�� cases�� indexSwitchCase�� �پ��ִ��� ����
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
				} // checkedSymbol�� SwitchCase�� �� ��.

				else  // checkedSymbol�� SwitchCase�� �ƴ� ��, checkedSymbol�� indexSwitchCase���� �پ��ִ��� �����Ѵ�
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

				

					if( dynamic_cast<Selection*>( checkedSymbol ) )  // ���� ���� ��ȣ�� Selection�϶� FALSE�ʿ� index��ȣ�� �پ��ִ��� Ȯ�ζ����� ���� ó��
					{
						Long checkSelectionStartX = static_cast<Selection*>(checkedSymbol)->GetStartPointX() ;
						Long checkSelectionEndX= static_cast<Selection*>(checkedSymbol)->GetEndPointY() ;
						Long checkMiddleX = static_cast<Selection*>(checkedSymbol)->GetMiddlePointX() ; 
						Long checkMiddleY = static_cast<Selection*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkSelectionStartX &&
							indexStartY == checkSelectionEndX ) // true�ʿ� �پ����� �� 
						{
								indexSwitchCase->upSign = YES ;
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkMiddleY ) // false�ʿ� �پ����� �� 
						{
								indexSwitchCase->upSign = YES ;
						}
					}
					else if( dynamic_cast<BeforeRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� BeforeRepeat�� ��, index��ȣ�� BeforeRepeat�� ���ʿ� �پ��ִ��� Ȯ�� ������ ���� ó��
					{
						//1) BeforeRepeat�� �̵��� == indexSwitchCase�� ��ġ
						//2) BeforeRepeat�� ���� �Ʒ��� == indexSwitchCase�� ��ġ
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
					else if( dynamic_cast<AfterRepeat*>( checkedSymbol ) ) // ���� ���� ��ȣ�� AfterRepeat�� ��, index��ȣ�� AfterRepeat�� ���ʿ� �پ��ִ��� Ȯ��
					{
						//- �Ĺݺ������� �̵� ������ ������, ��� ��ȣ���� upSign�� yes�Ǿ�� �Ѵ�!!!!
							//- �Ĺݺ������� �̵� ���� ( middleX, startY )
						//- �Ĺݺ������� ���� ���� upSign�� �����ؾ��ϹǷ� �Ĺݺ������� ���� �Ʒ����� �ٴ� ��ȣ���� upSign�� �Բ� yes�� �����
							//- �Ĺݺ������� ���� �Ʒ��� ( startX, endY )
						Long checkMiddleX = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointX() ;
						//Long checkMiddleY = static_cast<AfterRepeat*>(checkedSymbol)->GetMiddlePointY() ;

						if( indexStartX == checkStartX &&
							indexStartY == checkEndY )
						{
							indexSwitchCase->upSign = YES ; // indexSwitchCase ���� ��ȣ�� �پ��ִ�
						}
						else if( indexStartX == checkMiddleX &&
								 indexStartY == checkStartY )
						{
							indexSwitchCase->upSign = YES ; // indexSwitchCase ���� ��ȣ�� �پ��ִ�
						}

					}
					else if( indexStartX == checkStartX && 
							 indexStartY == checkEndY ) // indexSwitchCase�� ���� ������, checkedSymbol�� ���� �Ʒ����� ������ 
					{ 
								indexSwitchCase->upSign = YES ; // indexSwitchCase ���� ��ȣ�� �پ��ִ�
					}
				}
			} // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		}// while() upSign ���� ��
	
		
		// indexSwitchCase falseSign ���� ����
		Long k = 0 ;
		while( indexSwitchCase->falseSign == NO && k < paper->GetLength() )
		{ 
			if( k != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( k ) ;

				if ( dynamic_cast<Sequence*>( checkedSymbol ) ) // checkedSymbol�� indexAfterRepeat�Ʒ��� �پ��ִ��� �����Ѵ�
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
		}// While ���� indexAfterRepeat falseSign ���� ��
		
		// indexSwitchCase cases donwSign ���� ����
		i = 0 ;
		while(i < paper->GetLength() )
		{ 
			if( i != index ) // �ڱ� �ڽ��� ���翡�� ����
			{
				//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol//checkedSymbol
				Symbol *checkedSymbol = paper->GetAt( i ) ; 
			
				if ( dynamic_cast<SwitchCase*>( checkedSymbol ) ) // checkedSymbol�� SwitchCase�� ��, checkedSymbol�� indexSwitchCase���� �پ��ִ��� �����Ѵ�
				{
					SwitchCase *checkSwitchCase = static_cast< SwitchCase* >(checkedSymbol) ;
					Long checkStartX = checkSwitchCase->GetSelection()->GetStartPointX() ;
					Long checkStartY = checkSwitchCase->GetSelection()->GetStartPointY() ;

					// indexSwitchCase�� cases�� checkSwitchCase�� �پ��ִ��� ����
					 
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
				} // checkedSymbol�� SwitchCase�� �� ��.

				else  // checkedSymbol�� SwitchCase�� �ƴ� ��, checkedSymbol�� indexSwitchCase���� �پ��ִ��� �����Ѵ�
				{
					Long checkStartX = checkedSymbol->GetStartPointX() ;
					Long checkStartY = checkedSymbol->GetStartPointY() ;
					Long checkEndY = checkedSymbol->GetEndPointY() ;

					// indexSwitchCase�� cases�� checkedSymbol�� �پ��ִ��� ����
					 
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
				} // checkedSymbol�� SwitchCase�ƴ� �� ��.
			} // �ڱ� �ڽ��� ���翡�� ���� ��
			i++ ;
		} // while()  indexSwitchCase cases donwSign ���� ��
	}
	return index ;
}