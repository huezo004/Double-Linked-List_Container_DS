//Const_Iterator

//typename  
template<typename T>
const T& List<T>::const_iterator::operator*() const{
  return retrieve(); 
}

//typename 
template <typename T>
List<T>::const_iterator::const_iterator( ): current {NULL}{
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *p):current{p}{
}
        
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++(){
  current = current->next;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator:: operator++(int){
  const_iterator old= *this;
  ++(*this);
  return old;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator:: operator--(){
  current= current->prev;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator:: operator--(int){
  const_iterator old = *this;
  --(*this);
  return old;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const{
  return ( rhs.current == current);
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const{
  return !(*this==rhs );
}

template <typename T>
T & List<T>::const_iterator::retrieve() const{
  return current -> data;
}

//-----------------------------------------------------------------------------------------------------------
//iterator class**

template<typename T>
List<T>::iterator::iterator(){
}

template <typename T>
const T & List<T>::iterator::operator*() const{
   return const_iterator::operator*();
}

template <typename T>
T& List<T>::iterator::operator*(){
return const_iterator :: retrieve();
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++(){
  this->current= this->current->next;
  return *this;
}

template <typename T>
typename List <T> ::iterator List<T>::iterator::operator++(int){
  iterator old= *this;
  ++(*this);
  return old;
    
}

template <typename T>
typename List<T>::iterator&  List<T>::iterator::operator--(){
  this->current= this->current->prev;
  return *this;
    
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int){    
  iterator old= *this;
  --(*this);
  return old;
}

template <typename T>
List<T>::iterator::iterator(Node *p):const_iterator{p}
{}

//-----------------------------------------------------------------------------------------------
//**LIST FUNCTIONS**

template <typename T>
void List<T>::init(){    
  theSize= 0;
  head = new Node;
  tail = new Node;
  head->next= tail;
  tail->prev= head;
}

template <typename T>
List<T>::List(){    
  init();
}

template <typename T>
List<T>::List(const List & rhs){
  init();
  for( auto & x: rhs)
    push_back(x);
}

template <typename T>
List<T>::List(List && rhs): theSize(rhs.theSize), head( rhs.head), tail( rhs.tail){
  rhs.theSize= 0;
  rhs.head= nullptr;
  rhs.tail= nullptr;
}

template <typename T>
void List<T>::pop_front(){    
  erase(begin());
}
template <typename T>
List<T>::~List(){   
  clear();
  delete head;
  delete tail;
}
template <typename T>
const List<T> & List<T>::operator=(const List & rhs){
  List copy = rhs;
  std::swap(*this, copy);
  return *this;
}
template <typename T>
List<T> & List<T>::operator=(List && rhs){
  std::swap(theSize, rhs.theSize);
  std::swap(head, rhs.head);
  std::swap(tail, rhs.tail);
  return *this;
}
template <typename T>
int List<T>::size() const{
  return theSize;   
}

template <typename T>
bool List<T>::empty() const{
  return (theSize==0);
}

template <typename T>
void List<T>::clear(){   
  while (!empty()) {
        
    pop_front();
  }
}

template <typename T>
T& List<T>::front(){
  return *begin();
}

template <typename T>
const T& List<T>::front() const{ 
  return *begin();
}

template <typename T>
T & List<T>::back(){     
  return *--end();
    
}

template <typename T>
const T & List<T>::back() const{   
  return *--end();
}

template <typename T>
void List<T>::push_front(const T & val){    
  insert(begin(),val);
}
template <typename T>
void List<T>::push_front(T && val){   
  insert(begin(),std::move(val));
}

template <typename T>
void List<T>::push_back(const T & val){
    
  insert(end(),val);
    
}// insert to the end

template <typename T>
void List<T>::push_back(T && val){
insert(end(),std::move(val));
}

template <typename T>
void List<T>::pop_back(){    
  erase(--end());
}

template <typename T>
typename List<T>::iterator List<T>::begin(){
  return iterator( head->next);
}


template <typename T>
typename List<T>::const_iterator List<T>::begin() const{
  return const_iterator( head->next);   
}

template <typename T>
typename List<T>::iterator List<T>::end(){
  return iterator(tail);
}

template <typename T>
typename List <T>::const_iterator List<T>::end() const{   
  return const_iterator(tail);
}
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val){    
  Node *p= itr.current;
  ++theSize;
  return iterator(p->prev = p->prev->next= new Node{val,p->prev,p});
 }
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val){ // move version of insert
    
  Node *p = itr.current;
  ++theSize;
  return iterator(p->prev= p->prev->next= new Node( std:: move(val),p->prev,p));
    
}
template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr){   
  Node *p= itr.current;
  iterator returnValue(p->next);
  p->prev->next= p->next;
  p->next->prev= p->prev;
  delete p;
  --theSize;
  return returnValue;
}
template <typename T>
typename List <T>::iterator List<T>::erase(iterator start, iterator end){
   for( iterator itr = start; itr!= end;)
    itr= erase(itr);    
    return end;
}

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const{

  if(empty())
    os << "List is empty";
    
  for(const_iterator itr= begin(); itr != end(); ++itr) 
    os<< *itr << ofc;
}    
    
template <typename T>
List<T>::List(int num, const T& val ) {
        
    init();

    iterator itrs = begin(); 
    int times=0;
    
    while( times!= num){
      insert(itrs, val);
      times++; 
    }   
} 

template <typename T>
void List<T>::reverse(){
  
    List lc = *this;

    erase(begin(), end());
       
    for(iterator nl = lc.begin(); nl !=lc.end(); nl++) 
                push_front(*nl);
}  

template <typename T>
void List<T>::remove (const T& val){
        
    for(iterator itr = begin(); itr != end(); ++itr){
          if((*itr) == val)
	   erase(itr);
    } 
}
template <typename T>
List<T>::List(const_iterator start, const_iterator end){
     init();
     iterator it = begin();

     for( const_iterator dd= start; dd!= end; ++dd)
               insert(it, *dd);
} 
        
template<typename T>
bool operator==(const List<T>& lhs, const List<T>& rhs){

  int l= lhs.size();

  int r= rhs.size();

  if(l == r) {
    for(auto l1 =lhs.begin(), l2= rhs.begin(); l1 != lhs.end(); ++l1, ++l2){
                     if(*l1==*l2)
		      return true; 
    }
 }
    return false;
}

template <typename T>
bool operator !=(const List<T> &lhs, const List<T> &rhs){
	return !(lhs== rhs); 
}

//remove all elements for which Predicate pred
//returns true. pred can take in a function object



// sets list to the elements of the initializer_list
template<typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList){
  init();
  for( auto & x: iList)
    push_back(x);
}

template<typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l){
  l.print(os);  
  return os; 
}
 
template<typename T>
List<T>::List(std::initializer_list<T> iList){
  init();
  for( auto & x: iList)
    push_back(x);
 }

template<typename T>
template<typename PREDICATE>
void List<T>::remove_if(PREDICATE pred){  
  for(iterator itr =begin(); itr!= end(); ++itr){
    if(pred(*itr))
    erase(itr);
  }
}
