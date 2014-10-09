/**
 * @file: task/list_impl.h 
 * Solution implementation of the programming task 1
 */

namespace Task {
// ---- DList::Unit class implementation ----
    
    template <class T>  DList<T>::Unit::Unit():
        value(new T),
        nextElem(0),
        prevElem(0)
    {}
    
    template <class T>  DList<T>::Unit::~Unit() {
        delete value;
    }

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
        return *value;
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
        if(sizeValue == 0){
            firstElem = new Unit;
            *(firstElem->value) = val;
            lastElem = firstElem;
            sizeValue++;
            return;
        }
        firstElem->prevElem = new Unit;
        firstElem->prevElem->nextElem = firstElem;
        firstElem = firstElem->prevElem;
        *(firstElem->value) = val;
        sizeValue++;
    }

    template <class T> void DList<T>::pop_front() {
        switch (sizeValue) {
            case 0:
                return;
            case 1:
                delete firstElem;
                firstElem = 0;
                lastElem = 0;
                sizeValue = 0;
                return;
            default:
                firstElem = firstElem->nextElem;
                delete firstElem->prevElem;
                firstElem->prevElem = 0;
                sizeValue--;
        }
    }
    
    template <class T> void DList<T>::push_back(const T& val) {
        if(sizeValue == 0){
            firstElem = new Unit;
            *(firstElem->value) = val;
            lastElem = firstElem;
            sizeValue++;
            return;
        }
        lastElem->nextElem = new Unit;
        lastElem->nextElem->prevElem = lastElem;
        lastElem = lastElem->nextElem;
        *(lastElem->value) = val;
        sizeValue++;
    }
    
    template <class T> void DList<T>::pop_back() {
        switch (sizeValue) {
            case 0:
                return;
            case 1:
                delete firstElem;
                firstElem = 0;
                lastElem = 0;
                sizeValue = 0;
                return;
            default:
                lastElem = lastElem->prevElem;
                delete lastElem->nextElem;
                lastElem->nextElem = 0;
                sizeValue--;
        }
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::insert(DList<T>::Unit* u, const T& val){
        Unit* newElem = new Unit;
        newElem->nextElem = u;
        newElem->prevElem = u->prevElem;
        u->prevElem = newElem;
        *(newElem->value) = val;
        sizeValue++;
        if(newElem->prevElem != 0)
            newElem->prevElem->nextElem = newElem;
        return newElem;
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::first() const {
        return firstElem;
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::last() const {
        return lastElem;
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::erase(DList<T>::Unit* u) {
        if(u->prevElem == 0){
            pop_front();
            return firstElem;
        }
        if(u->nextElem == 0){
            pop_back();
            return 0;
        }
        
        DList<T>::Unit* ret = u->nextElem;
        u->prevElem->nextElem = u->nextElem;
        u->nextElem->prevElem = u->prevElem;
        delete u;
        sizeValue--;
        return ret;
    }

    template <class T> void DList<T>::clear() {
        int n = sizeValue;
        for (int i = 0; i < n; i++) {
            pop_front();
        }
    }
    
    template <class T> bool DList<T>::empty() {
        return sizeValue == 0 ? true : false;
    }
    
    template <class T> unsigned DList<T>::size() const {
        return sizeValue;
    }
    
    template <class T> void DList<T>::reverse() {
        Unit* currentSwap = firstElem;
        Unit* buf = firstElem;
        firstElem = lastElem;
        lastElem = buf;
        for (int i = 0; i < sizeValue; i++) {
            buf = currentSwap->nextElem;
            currentSwap->nextElem = currentSwap->prevElem;
            currentSwap->prevElem = buf;
            currentSwap = currentSwap->prevElem;
        }
    }
    
    template <class T> void DList<T>::intDump() const {
        if(sizeValue == 0){
            printf("DList with 0 elements\n");
            if((firstElem == 0) && (lastElem == 0))
                printf("both pointers are null\n");
            else
                printf("error in pointers\n");
            return;
        }
        
        printf("DList with %d elements:\n",sizeValue);
        printf("first to last:\n");
        Unit* elemToPrint = firstElem;
        
        for (int i = 1; i < sizeValue; i++) {
            printf("%d -> ", *(elemToPrint->value));
            elemToPrint = elemToPrint->nextElem;
        }
        printf("%d\n",*(elemToPrint->value));
        
        printf("last to first:\n");
        elemToPrint = lastElem;
        for (int i = 1; i < sizeValue; i++) {
            printf("%d -> ", *(elemToPrint->value));
            elemToPrint = elemToPrint->prevElem;
        }
        printf("%d\n",*(elemToPrint->value));
        printf("dump end.\n");
    }
    
// ---- End of DList template class implementation ----
};