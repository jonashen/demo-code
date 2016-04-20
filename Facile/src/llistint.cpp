#include "../lib/llistint.h"
#include <cstdlib>
#include <stdexcept>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

/**
 * Copy constructor (deep copy)
 */
LListInt::LListInt(const LListInt& other)
{
    head_ = NULL; //set base values for each
    tail_ = NULL;
    size_ = 0;
    
    if(!other.empty()) //if other is not a null list
    {
        if(other.size_ == 1) //other is size 1
        {
            Item* temp = new Item;
            temp->val = other.head_->val;
            temp->prev = NULL, temp->next = NULL;
            head_ = temp; tail_ = temp;
            size_++;
        }
        
        else
        {
            head_ = new Item;
            head_->next = NULL; head_->prev = NULL;
            head_->val = other.head_->val; //new head is equal to other head
            size_++;
        
            Item *pItem = head_; //previous THIS item
            Item *tItem = head_->next; //tItem is THIS item
            Item *oItem = other.head_->next; //oItem is next item in other
            while(oItem != NULL) //runs until last item in other
            {
                tItem = new Item; //creates a new THIS Item
                tItem->next = NULL; tItem->prev = pItem; pItem->next = tItem;
                tItem->val = oItem->val;
                pItem = tItem;
                tItem = tItem->next;
                oItem = oItem->next;
                size_++;
            }
            tail_ = pItem; //tail sets to last val in this
        }
    }
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
    if(loc < 0 || loc > size_){
        throw std::invalid_argument("bad location");
    }
    
    if(loc == 0) { //insert in front of list
        if(size_ == 0) { //empty list
            Item* temp = new Item;
            head_ = temp; tail_ = temp;
            temp->val = val;
            temp->prev = NULL, temp->next = NULL;
        }
        else { //nonempty list
            Item* temp = new Item;
            temp->val = val;
            temp->next = head_; head_->prev = temp;
            temp->prev = NULL; head_ = temp;
        }
        size_++;
    }
    
    else if(loc == size()) { //insert in back of list
        Item* temp = new Item;
        temp->val = val;
        temp->prev = tail_; temp->next = NULL;
        tail_->next = temp; tail_ = temp;
        
        size_++;
    }
    
    else { //insert in list
        Item* tempP = getNodeAt(loc-1);
        Item* tempN = getNodeAt(loc);
        Item* temp = new Item;
    
        temp->prev = tempP; tempP->next = temp;
        temp->next = tempN; tempN->prev = temp;
        temp->val = val;
        
        size_++;
    }
} //insert

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
    if(loc < 0 || loc >= size_){
        throw std::invalid_argument("bad location");
    }
    
    if(loc == 0) { //remove front of list
        if(empty()) { //empty list
            return;
        }
        
        else if (size_ == 1) { //one item in list
            Item* temp = head_;
            delete temp;
            head_ = NULL, tail_ = NULL; --size_;
        }
        
        else { // >1 item in list
            Item* temp = head_;
            head_ = head_->next;
            delete temp; --size_;
        }
    }
    
    else if(loc == size() - 1) { //remove back of list
        Item* temp = tail_; tail_ = tail_->prev; tail_->next = NULL;
        delete temp; --size_;
    }
    
    else { //remove in list
        Item* tempP = getNodeAt(loc-1);
        Item* tempN = getNodeAt(loc+1);
        Item* temp = getNodeAt(loc);
        
        tempP->next = tempN; tempN->prev = tempP;
        delete temp; --size_;
    }
} //remove

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const
{
    Item* temp = head_;
    if(temp) { //temp is not NULL
    for (int i = 0; i < loc; i++)
        temp = temp->next;
    }
    return temp;
}

/**
 * Assignment Operator (deep copy)
 */
LListInt& LListInt::operator=(const LListInt& other)
{
    if(size_ != 0) //empties out this
    {
        Item* tempP = head_;
        Item* tempN = head_->next;
    
        while (tempN != NULL) //deletes every Item
        {
            delete tempP;
            tempP = tempN;
            tempN = tempN->next;
        }
        delete tempP;
        
        head_ = NULL; tail_ = NULL; size_ = 0; //reset all values
    }
    
    if(!other.empty()) //if other is not a null list
    {
        if(other.size_ == 1) //other is size 1
        {
            Item* temp = new Item;
            head_ = temp; tail_ = temp;
            temp->val = other.head_->val;
            temp->prev = NULL, temp->next = NULL;
            size_++;
        }
        
        else
        {
            head_ = new Item;
            head_->next = NULL; head_->prev = NULL;
            head_->val = other.head_->val; //new head is equal to other head
            size_++;
            
            Item *pItem = head_; //temp saves prev. item
            Item *tItem = head_->next; //tItem is next item in this
            Item *oItem = other.head_->next; //oItem is next item in other
            while(oItem != NULL) //while node is not tail
            {
                tItem = new Item; //creates a new Item in this
                tItem->next = NULL; tItem->prev = pItem; pItem->next = tItem;
                tItem->val = oItem->val;
                pItem = tItem;
                tItem = tItem->next;
                oItem = oItem->next;
                size_++;
            }
            tail_ = pItem; //tail sets to last val in this
        }
    }
    return *this;
}

/**
 * Concatenation Operator (other should be appended to the end of this)
 */
LListInt LListInt::operator+(const LListInt& other) const
{
    LListInt *newLL = new LListInt; //create new LL
    bool tEmpty = empty(), oEmpty = other.empty();
    
    if(tEmpty && oEmpty) //both are empty LL
        return *newLL;
    
    else if (!tEmpty && oEmpty) //other is empty LL
        *newLL = LListInt(*this);
    
    else if(tEmpty && !oEmpty) //this is empty LL
        *newLL = LListInt(other);
    
    else //neither are empty LL
    {
        *newLL = LListInt(*this); //first copy this into newLL
        
        newLL->size_ += other.size_;
        Item *pItem = newLL->tail_; //Previous item
        Item *tItem = newLL->tail_->next; //Last item in this
        Item *oItem = other.head_; //first item in other
        while(oItem != NULL) //loops until last item in other
        {
            tItem = new Item; //creates a new Item in this
            tItem->next = NULL; tItem->prev = pItem; pItem->next = tItem;
            tItem->val = oItem->val;
            pItem = tItem;
            tItem = tItem->next;
            oItem = oItem->next;
            ++newLL->size_;
        }
    }
    
    return *newLL;
}

/**
 * Access Operator
 */
int const & LListInt::operator[](int position) const
{
    if(position < 0 || position >= size_){
        throw std::invalid_argument("bad location");
    }
    Item *temp = getNodeAt(position);
    return temp->val;
}