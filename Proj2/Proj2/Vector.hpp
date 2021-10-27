using namespace cop4530;
// Vector(): Default zero-parameter constructor. 
// This will create an empty vector with both size and capacity to be zero.
//  You need to initialize the member variables. In particular, you need to assign array to NULL (nullptr for c++11).
template <typename T>
Vector<T>::Vector(){
    theSize = 0;
    theCapacity = 0;
    array = NULL;
}
// Vector(const Vector &rhs): Copy constructor. 
// Create the new vector using elements in existing vector rhs.
template <typename T>
Vector<T>::Vector(const Vector &rhs){
    array = NULL;
    operator=(rhs);
}
// Vector(Vector &&rhs): move constructor.
template <typename T>
Vector<T>::Vector(Vector &&rhs){
    array = NULL;
    operator=(std::move(rhs));
}

// Vector(int num, const T & val = T()): Construct a Vector with num elements, 
// all initialized with value val. Note that the capacity should also be num.
template <typename T>
Vector<T>::Vector(int num, const T& val){	    
    theCapacity = num;
    array = new T[theCapacity];
    for(int i = 0; i < num; ++i){
	array[i] = val;
    }	
}
// Vector(const_iterator start, const_iterator end): construct a Vector with elements from another Vector between start and end.
//  Including the element referred to by the start iterator, but not by the end iterator, 
// that is, the new vector should contain the elements in the range [start, end).
template <typename T>
Vector<T>::Vector(const_iterator start, const_iterator end){
//not sure what this constructor requires
    int i = 0;
    theSize = 0;
    theCapacity = 0;
    array = NULL;

    for(const T* Titr= start; Titr != end; Titr++){
	push_back(*Titr);
    }
}
// ~Vector(): destructor. You should properly reclaim memory.
template <typename T>
Vector<T>::~Vector(){
    delete [] array;
}

// operator=(const Vector &rhs): Copy assignment operator
// operator=(Vector &&rhs): move assignment operator
template <typename T>
const Vector<T>& Vector <T>::operator = (const Vector &rhs){	
    
    if(*this != rhs){
	delete [] array;
	theSize = rhs.size();
	theCapacity = rhs.theCapacity;

	array = new T[theCapacity];
	for(int i = 0; i < size(); i++){
	    array[i] = rhs.array[i];
	}
    }
    return *this;
}
// operator[](index): index operator. Return reference to the element at the specified location. 
// No error checking on value of index. Note that there are two versions of the index operator.
template <typename T>
T& Vector<T>::operator[](int index){
    return array[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const{
    return array[index];
}
// at(index): Return reference to the element at the specified location. 
// Throw "out_of_range" exception if index is not in the valid range [0, theSize).  
// There are two versions of this member function.

 template <typename T>
 T& Vector<T>::at(int loc){
     return array[loc];
 }

 template <typename T>
 const T& Vector<T>::at(int loc) const{
     return array[loc];
 }



// front() and back(): return reference to the first and last element in the vector, respectively.
//  There are two versions of both member functions.
template <typename T>
T& Vector<T>::front(){
    return size() == 0;
}
template <typename T>
const T& Vector<T>::front() const{
    return size() == 0;
}

template <typename T>
T& Vector<T>::back(){
    return &array[size()];		//refer to the non-const version
}

template <typename T>
const T& Vector<T>::back() const{
    //needs to return the last element in the vector
    return &array[size()];		//copied iterator end, possibly different, consider *T or just T;
}
// size(): return the number of elements currently stored in the vector.
template <typename T>
int Vector<T>::size() const{
    return theSize;
}
// capacity(): return the number of elements that can be stored in the vector without any new memory allocation.
template <typename T>
int Vector<T>::capacity() const{
    return theCapacity;
}
// empty(): return true if no element is in the vector; otherwise, return false.
template <typename T>
bool Vector<T>::empty() const{
    return size() == 0;
}
// clear(): delete all the elements in the vector. Memory associated with the vector does not need to be reclaimed.
template <typename T>
void Vector<T>::clear(){
    theSize = 0;
    delete [] array;
    array = new T [theCapacity];
}


// push_back(): insert a new object as the last element into the vector.
template <typename T>
void Vector<T>::push_back(const T& val){
    if(theSize == theCapacity)
	reserve(2 * theCapacity + 1);
    array[theSize++] = val;
}
// pop_back(): delete the last element in the vector.
template <typename T>
void Vector<T>::pop_back(){
    theSize--;
}
// resize(newSize, newValue): Change the size of the vector to newSize. 
// If newSize is greater than the current size theSize, 
// the new positions in the vector should hold the value newValue. Note that capacity may also be changed accordingly.
template <typename T>
void Vector<T>::resize(int num, T val){
    if(num > theCapacity)
	reserve(num * 2 + 1);
    theSize = num;
}
// reserve(newCapacity): Change the capacity of the vector to newCapacity, 
// if newCapacity is greater than the current capacity of the vector. Otherwise, 
// this function does not change the capacity of the vector.
template <typename T>
void Vector<T>::reserve(int size){
    if(size < theSize)
	return;
    T *oldArray = array;		    //Ts = new T[theCapacity]

    array = new T[size];
    for(int i = 0; i < theSize; i ++){
	array[i] = oldArray[i];
    }
    theCapacity = size;

    delete [] oldArray;

}

// print(ostream &os, char ofc = ' '): print all elements in the Vector, 
// using character ofc as the deliminator between elements of the vector.
template <typename T>
void Vector<T>::print(std::ostream& os, char ocf) const{
    for(int i = 0; i < theSize; i++){
	os << array[i] << ocf;
    }
}
// begin(): return iterator to the first element in the vector. 
// No error checking is required. There are two versions of this member function.
template <typename T>
T* Vector<T>::begin(){
    return &array[0];
}

template <typename T>
const T* Vector<T>::begin() const{
    return &array[0];
}


// end(): return iterator to the end marker of the vector (the position after the last element in the vector). 
// No error checking is required. There are two versions of this member function.
template <typename T>
T* Vector<T>::end(){
    return &array[size()];
}

template <typename T>
const T* Vector<T>::end() const{
    return &array[size()];
}
// insert(iterator itr, const T & val): insert value val ahead of the element referred by the iterator itr. 
// All current elements in the vector starting at itr should be pushed back by one position. 
// The return value is the iterator referring to the newly inserted element.
template <typename T>
T* Vector<T>::insert(iterator itr, const T& val){
    T temp1; 
    T temp2 = val;
    for(iterator i = itr; i < end(); i++){
	temp1 = *i;
	*i = temp2;
	temp2 =  temp1;
    }
    theSize++;
    return itr;
}
// erase(iterator itr): delete element referred to by itr.
//  The return value is the iterator referring to the element following the deleted element.
template <typename T>
T* Vector<T>::erase(iterator itr){
    theSize--;
    for(itr; itr != end(); itr++){
	*itr = *(itr + 1);
    }
    return itr;
}
// erase(iterator start, iterator end): delete all elements between start and end (including start but not end),
//  that is, all elements in the range [start, end). The return value is the iterator referring to the element following the last element being deleted.
template <typename T>
T* Vector<T>::erase(iterator start, iterator end){
//for loop that traverses from back to front 
//uses pop_back
    Vector<T>::iterator flag = end;
    for(iterator itr = start; itr != end; itr++){
	*start = *end;
	start++;
    }
    return flag;
}
// operator==(const Vector<T> & lhs, const Vector<T> & rhs): check if two vectors contain the same sequence of elements.
//  Two vectors are equal if they have the same number of elements and the elements at the corresponding position are equal.
template <typename T>
bool operator==(const Vector<T> &lhs, const Vector<T> &rhs){
    if(lhs.size() == rhs.size()){
	for(int i = 0; i < lhs.size(); i++){
    	    if(lhs[i] != rhs[i])
		return false;
	}
    }
    return true;
}
// operator!=(const Vector<T> & lhs, const Vector<T> & rhs): opposite of operator==().
template <typename T>
bool operator !=(const Vector<T> & lhs, const Vector<T> & rhs){
    return !(lhs == rhs);
}
// operator<<(ostream & os, const Vector<T> & v): print out all elements in Vector v by calling Vector<T>::print() function. 
template <typename T>
std::ostream& operator << (std::ostream &os, const Vector<T> &v){
    v.print(os);
    return os;
}














