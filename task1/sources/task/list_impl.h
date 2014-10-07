/**
 * @file: task/list_impl.h 
 * Solution implementation of the programming task 1
 */

namespace Task {
// ---- DList::Unit class implementation ----
    
    template <class T>  DList<T>::Unit::Unit():
        T(),
        nextElem(),
        prevElem()
    {}
    
    template <class T>  DList<T>::Unit::~Unit()
    {}

    template <class T> typename DList<T>::Unit*
    DList<T>::Unit::next() {
        return nextElem;
    }

    template <class T> typename DList<T>::Unit*
    DList<T>::Unit::prev() {
        return prevElem;
    }
    
    template <class T> T&
    DList<T>::Unit::val() {
        return value;
    }
    
// ---- End of DList::Unit class implementation ----

    
// ---- DList template class implementation ----
    
    template <class T>  DList<T>::DList():
        firstElem(0),
        lastElem(0),
        sizeValue(0)
    {}
    
    template <class T>  DList<T>::~DList()
    {}

    template <class T> void DList<T>::push_front (const T& val) {
        firstElem->nextElem = new Unit;
        firstElem->nextElem->prevElem = firstElem;
        firstElem = firstElem->nextElem;
        firstElem->value = val;
        sizeValue++;
    }

    template <class T> void DList<T>::pop_front() {
        switch (sizeValue) {
            case 0:
                return;
            case 1:
                clear();
                return;
            default:
                firstElem = firstElem->prevElem;
                delete firstElem->nextElem;
                firstElem->nextElem = 0;
        }
    }
    
    template <class T> void DList<T>::push_back(const T& val) {
        lastElem->prevElem = new Unit;
        lastElem->prevElem->nextElem = lastElem;
        lastElem = lastElem->prevElem;
        lastElem->value = val;
        sizeValue++;
    }
    
    template <class T> void DList<T>::pop_back() {
        switch (sizeValue) {
            case 0:
                return;
            case 1:
                clear();
                return;
            default:
                lastElem = lastElem->nextElem;
                delete lastElem->prevElem;
                lastElem->prevElem = 0;
        }
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::insert(DList<T>::Unit* u, const T& val){
        Unit* newElem = new Unit;
        newElem->nextElem = u;
        newElem->prevElem = u->prevElem;
        u->prevElem = newElem;
        newElem->value = val;
        sizeValue++;
        return newElem;
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::first(){
        return firstElem;
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::last(){
        return lastElem;
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::erase(DList<T>::Unit *u) {
        if(u->next() == 0){
            pop_front();
            return 0;
        }
        if(u->prev() == 0){
            pop_back();
            return lastElem;
        }
        DList<T>::Unit* ret = u->next();
        u->prev()->nextElem = u->next();
        u->next()->prevElem = u->prev();
        delete u;
        return ret;
    }

    template <class T> bool DList<T>::empty() {
        return sizeValue == 0 ? true : false;
    }
    
    template <class T> unsigned DList<T>::size() {
        return sizeValue;
    }
// ---- End of DList template class implementation ----
};














