//Array.h
//기능: Array자료형 라이브러리 
//작성자: 안영보 채형석 김지수 곽욱현 고요셉
//작성일자: 20140403

#ifndef _ARRAY_H
#define _ARRAY_H

typedef signed long int Long;

template <typename T>
class Array	{
public:
	//디폴트 생성자
	//capacity 값이 안주어지면 기본적으로 capacity값을 100으로 주겠다는 의미
	Array(Long capacity =100) ;
	//복사생성자
	Array(const Array& source) ;
	//소멸자
	~Array() ;

	Long Store(Long index, T object) ;
	Long Insert(Long index, T object) ;
	Long AppendFromFront(T object) ;  
	Long AppendFromRear(T object) ;

	Long Delete(Long index) ; 
	Long DeleteFromFront() ; 
	Long DeleteFromRear() ;
	
	void Clear() ;  
	Long Modify(Long index, T object) ;
	Long DeleteModify( Long index );

	Long LinearSearchUnique(void *key , Long (*compare)(void*, void*)) ;
	void LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, Long (*compare)(void*, void*)) ;
	
	Long BinarySearchUnique(void *key , Long (*compare)(void*, void*)) ;
	void BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, Long (*compare)(void*, void*)) ;
	
	void InsertionSort(Long (*compare)(void*, void*)) ;
	void SelectionSort(Long (*compare)(void*, void*)) ;
	void BubbleSort(Long (*compare)(void*, void*)) ;
	void MergeSort(const Array& one, const Array& other, Long (*compare)(void*, void*)) ;



	//치환 연산자
	Array& operator =(const Array& source) ;
	
	//첨자 연산자
	T& operator [](Long index) ;

	Long GetLength() const ;
	Long GetCapacity() const ;
	T& GetAt(Long index) const; 


private:
	T *front ;
	Long length ;
	Long capacity ;

}; //Array class


template <typename T>
Array<T>::Array(Long capacity =100){
	this->front = new T[capacity] ;
	this->length = 0 ;
	this->capacity = capacity ;

}
	//복사생성자
template<typename T>
Array<T>:: Array (const Array& source){
	

	this->front = new T [source.capacity];
	for(Long i = 0; i < source.length; i++){
		(this->front)[i] = source.front[i];
	}

	this->capacity = source.capacity;
	this->length = source.length;
}


//소멸자
template <typename T>
Array<T>::~Array()	{
	if( this->front != 0 )	{
		delete[] this->front;
	}
}


//Store
template <typename T>
Long Array<T>::Store(Long index, T object){
	(this->front)[index] = object;
	(this->length)++;

	return index;

}

template <typename T>
Long Array<T>::Insert(Long index, T object){
		Long i = 0 ;
		T (*tempObjects);

		tempObjects = new T [ this->capacity +1 ] ;

		while ( i < index) {
			tempObjects[i] = this->front [i] ;
			i++ ;
		}
		while( i < this->length ){
			tempObjects[i+1] = this->front [i ];
			i++ ;
		}
		if(this->front != 0) {
			delete[] this->front ;
		}

		this->front = tempObjects ;
		this->capacity ++ ;
		this->front[index] = object ;
		this->length ++ ;

		return index ;

	}

template <typename T>
Long Array<T>::AppendFromFront(T object){
		T (*tempObjects) ;
		Long index ;
		Long i = 0 ;

		tempObjects = new T [this->capacity +1] ;
		while(i<this->length){
			tempObjects[i+1] = this->front[i] ;
			i++ ;
		}
		if(this->front !=0){
			delete[] this->front ;
		}

		this->front = tempObjects ;
		this->capacity++ ;
		index=0 ;
		this->front[index] = object ;
		this->length++ ;  
		return index ;
	}

template <typename T>
Long Array<T>::AppendFromRear(T object){
		T (*tempObjects) ;
		Long index ;
		Long i=0 ;

		tempObjects= new T [this->capacity +1] ;

		while(i< this->capacity){
			tempObjects[i] = this->front[i] ;
			i++ ;
		}
		if(this->front != 0){
			delete[] this->front ;
		}

		this->front = tempObjects ;
		this->capacity ++ ;

		//배열의 제일 마지막 칸에 들어온 object를 저장한다 
		index = (this->capacity)-1 ;
		this->front[index] = object ;

		this->length ++ ;

		return index ;
	}


template <typename T>
Long Array<T>::Delete(Long index){
		T (*tempObjects) ;
		Long i = 0 ;
		
		if(this->capacity > 1){
			tempObjects = new T [ this->capacity - 1 ] ;
		}
		while(i  < index && this->capacity > 1){
			tempObjects[ i ] = this->front[ i ] ;
			i++ ;
		}
		while(i < this->length - 1 && this->capacity > 1){
			tempObjects[ i ] = this->front[ i + 1 ] ;
			i++ ;
		}
		if(this->front != 0){
			delete[] this->front ;
			this->front = 0 ;
		}

		if(this->capacity > 1){
			this->front = tempObjects ;
		}
		(this->capacity)-- ;
		(this->length)-- ;

		index = -1;

		return index ;
	}

template <typename T>
Long Array<T>::DeleteFromFront(){
		T (*tempObjects) ; 
		Long i = 1 ;


		if(this->capacity >1){
			tempObjects = new T [this->capacity -1 ] ;
		}
		while ( i < this->length ) {
			tempObjects[i-1] = this->front[i] ;
			i++ ;
		}
		if ( this->front  != 0 ){
			delete[] this->front ; 
			this->front = 0 ;
		}
		if (this->capacity > 1 ){
			this->front = tempObjects ; 
		}
		this->length -- ;
		this->capacity -- ;

		return -1 ;

	}


template <typename T>
Long Array<T>::DeleteFromRear(){
		T (*tempFront);
		if(this->capacity>1){
			tempFront = new T [this->capacity-1] ;
		}
		Long i = 0 ;
		while(i<this->capacity -1){
			tempFront[i] = this->front[i] ;
			i++ ;
		}
		if(this->front !=0){
			delete[] this->front ;
			this->front = 0 ;
		}
		if(this->capacity>1){
			this->front = tempFront ;
		}
		this->capacity -- ;
		this->length-- ;

		return -1 ;
	}

//Clear
template <typename T>
void	Array<T>::Clear()
{
	if (this->front != 0)
	{
		delete[] this->front ;
		this->front = 0;
	}
	this->capacity = 0 ;
	this->length = 0 ; 
}

//Modify
template <typename T>
Long	Array<T>::Modify(Long index, T object)
{
	this->front[index] = object ;
	return  index ;
}

//DeleteModify
template <typename T>
Long	Array<T>::DeleteModify(Long index ) {

	if( this->front[index] != 0 ) {
		delete this->front[ index ] ;
		this->front[ index ] = 0 ;
		length --;
	}
	return  index ;
}

//LinearSearchUnique
template <typename T>
Long	Array<T>::LinearSearchUnique(void *key , Long (*compare)(void*, void*))
{
	Long	i = 0 ;
	Long	index = -1 ;

	while ( i < this->length && compare( this->front + i, key ) != 0 )
	{
		i++ ;
	}

	if( i < this->length )
	{
		index = i ;
	}

	return index ;
}

//LinearSearchDuplicate
template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, Long (*compare)(void*, void*))
{
		Long	i = 0 ;
		Long	j = 0 ;
		(*count) = 0 ;

		*indexes = new Long [this->length ];
		
		while( i < this->length ) 
		{
			if( compare( this->front + i, key ) == 0 )
			{
				(*indexes)[j] = i ; 
				j++ ; 
				(*count)  ++ ;
			}
			i++ ;
		}
	}

//BinarySearchUnique
template <typename T>
Long	Array<T>::BinarySearchUnique(void *key , Long (*compare)(void*, void*))
{
		Long	low = 0 ;
		Long	index = -1 ;

		Long	high = this->length - 1 ;
		Long	middle  = ( low + high ) / 2 ;
		while ( low <= high && compare( this->front + middle, key ) != 0 )
		{
			if(compare( this->front + middle, key ) > 0)
			{
				high = middle - 1 ;
			}
			else {
				low = middle + 1 ;
			}
			middle = ( low + high) / 2 ;
		}
		if( low <= high){
			index = middle ;
		}

		return index ;
	}

//BinarySearchDuplicate
template <typename T>
void	Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, Long (*compare)(void*, void*))
{
		Long low = 0 ;

		(*count) = 0 ; 
		Long j = 0 ;

		*indexes = new Long [this->length ] ; 

		Long	high = this->length - 1 ;
		Long	middle = ( low + high ) / 2 ;

		while ( low <= high && compare(this->front + middle , key ) != 0 )
		{
			if (compare( this->front + middle , key ) == 0){
				high = middle - 1 ;
			}
			else
			{
				low = middle +1 ; 
			}
			middle = ( low + high ) / 2 ;
		}
		Long	i = middle -1 ;
		while( i>= 0 && compare( this->front + i , key ) ==0){
			i-- ;
		}

		i++ ;

		while( i < this->length && compare( this->front + i, key ) == 0 )
		{
			(*count) ++ ;
			(*indexes)[j] = i ;
			j++ ; 
			i++ ;
		}
}

//InsertionSort
template<typename T>		
void	Array<T>::InsertionSort(Long (*compare)(void*, void*))
{
	T		choice;
	Long	i = 0;

	while ( i < this->length - 1 )
	{
		if ( compare ( this->front + i, this->front + (i + 1) ) > 0 )
		{
			choice = this->front[i + 1];
			Long	j = 0;

			while ( compare ( &choice, this->front + j ) > 0 )
			{
				j++;
			}

			Long	k = i;

			while ( k >= j )
			{
				this->front[k + 1] = this->front[k];
				k--;
			}
			this->front[j] = choice;
		}
		i++;
	}
}

//SelectionSort
template<typename T>
void	Array<T>::SelectionSort(Long (*compare)(void*, void*))
{
	T		temp;
	Long	i = 0;
	Long	j;
	Long	index;

	while ( i < this->length - 1 )
	{
		j = i + 1;
		index = i;

		while ( j < this->length )
		{
			if ( compare ( this->front + (index), this->front + j ) > 0 )
			{
				index = j;
			}
			j++;
		}
		if ( i != index )
		{
			temp = this->front[i];
			this->front[i] = this->front[index];
			this->front[index] = temp;
		}
		i++;
	}

}

//BubbleSort
template<typename T>
void	Array<T>::BubbleSort(Long (*compare)(void*, void*))
{
	T temp;
	
	for(Long i = 0; i< this->length-1; i++)
	{

		for(Long j=0; j < this->length - i - 1 ; j++)
		{

			if( compare (this->front + j , this->front + ( j + 1 )) > 0 )
			{
				temp = this->front [j];
				this->front[j]= this->front[j+1];
				this->front[j+1] = temp;
			}
		}
	}
}

//MergeSort
template<typename T>
void	Array<T>::MergeSort(const Array& one, const Array& other, Long (*compare)(void*, void*))
{
	Long i=0;
	Long j=0;
	Long k=0;

	if(this->front != 0)
	{
		delete[] this->front;
	}
	this->front = new T[one.length + other.length] ;
	this->capacity = one.length + other.length ; 
	this->length = 0 ;

	while( i < one.length && j < other.length)
	{
		if( compare( one.front + i, other.front + j ) <= 0)
		{
			this->front[k] = one.front[i];
			k++;
			this->length++;
			//this->length + 1;
			i++;
		}
		else
		{
			this->front[k] = other.front[j];
			k++;
			this->length++;
			j++;
		}
	}

	while( i < one.length )
	{
		this->front[k] = one.front[i];
		k++;
		this->length++;
		i++;
	}

	while( j < other.length )
	{
		this->front[k] = other.front[j];
		//this->front[k] = one.front[j];
		k++;
		this->length++;
		j++;
	}
}



//치환 연산자
template<typename T>
Array<T>&	Array<T>::operator = (const Array& source)
{

	if( this->front != 0 )
	{
		delete[] this->front;
	}
	this->front = new T [source.capacity];

	for( Long i = 0; i < source.length; i++ )
	{
		(this->front)[i] = source.front[i];
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}


//첨자 연산자
template <typename T>
T&	Array<T>::operator[](Long index)
{
	return this->front[index];
}


template <typename T>
inline Long	Array<T>::GetLength() const 
{
	return this->length;
}

template <typename T>
inline Long	Array<T>::GetCapacity() const
{
	return this->capacity;
}

template <typename T>
T& Array<T>::GetAt(Long index) const
{
	return const_cast <T&>( this->front[index] );
}


#endif _ARRAY_H