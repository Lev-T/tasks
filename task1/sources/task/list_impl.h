/**
 * @file: task/list_impl.h 
 * Solution implementation of the programming task 1
 */

namespace Task {
// ---- DList::Unit class implementation ----
    
    template <class T>  DList<T>::Unit::Unit():
        value(new T),
        next_elem(0),
        prev_elem(0)
    {}
    
    template <class T>  DList<T>::Unit::~Unit() {
        delete value;
    }

    template <class T> typename DList<T>::Unit*
    DList<T>::Unit::next() {
        return next_elem;
    }

    template <class T> typename DList<T>::Unit*
    DList<T>::Unit::prev() {
        return prev_elem;
    }
    
    template <class T> T&
    DList<T>::Unit::val() {
        return *value;
    }
    
// ---- End of DList::Unit class implementation ----

    
// ---- DList template class implementation ----
    
    template <class T>  DList<T>::DList():
        first_elem(0),
        last_elem(0),
        size_value(0),
        mode(0)
    {}
    
    template <class T>  DList<T>::~DList()
    {}

    template <class T> void DList<T>::push_front (const T& val) {
        if(size_value == 0){
            first_elem = new Unit;
            *(first_elem->value) = val;
            last_elem = first_elem;
            size_value++;
            return;
        }
        first_elem->prev_elem = new Unit;
        first_elem->prev_elem->next_elem = first_elem;
        first_elem = first_elem->prev_elem;
        *(first_elem->value) = val;
        size_value++;
    }

    template <class T> void DList<T>::pop_front() {
        switch (size_value) {
            case 0:
                if(mode)
                    throw DList_error(1);
                return;
            case 1:
                delete first_elem;
                first_elem = 0;
                last_elem = 0;
                size_value = 0;
                return;
            default:
                first_elem = first_elem->next_elem;
                delete first_elem->prev_elem;
                first_elem->prev_elem = 0;
                size_value--;
        }
    }
    
    template <class T> void DList<T>::push_back(const T& val) {
        if(size_value == 0){
            first_elem = new Unit;
            *(first_elem->value) = val;
            last_elem = first_elem;
            size_value++;
            return;
        }
        last_elem->next_elem = new Unit;
        last_elem->next_elem->prev_elem = last_elem;
        last_elem = last_elem->next_elem;
        *(last_elem->value) = val;
        size_value++;
    }
    
    template <class T> void DList<T>::pop_back() {
        switch (size_value) {
            case 0:
                if(mode)
                    throw DList_error(2);
                return;
            case 1:
                delete first_elem;
                first_elem = 0;
                last_elem = 0;
                size_value = 0;
                return;
            default:
                last_elem = last_elem->prev_elem;
                delete last_elem->next_elem;
                last_elem->next_elem = 0;
                size_value--;
        }
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::insert(DList<T>::Unit* u, const T& val){
        Unit* new_elem = new Unit;
        new_elem->next_elem = u;
        new_elem->prev_elem = u->prev_elem;
        if(new_elem->prev_elem == 0)
            first_elem = new_elem;
        u->prev_elem = new_elem;
        *(new_elem->value) = val;
        size_value++;
        if(new_elem->prev_elem != 0)
            new_elem->prev_elem->next_elem = new_elem;
        return new_elem;
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::first() const {
        return first_elem;
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::last() const {
        return last_elem;
    }
    
    template <class T> typename DList<T>::Unit*
    DList<T>::erase(DList<T>::Unit* u) {
        if(u->prev_elem == 0){
            pop_front();
            return first_elem;
        }
        if(u->next_elem == 0){
            pop_back();
            return 0;
        }
        
        DList<T>::Unit* ret = u->next_elem;
        u->prev_elem->next_elem = u->next_elem;
        u->next_elem->prev_elem = u->prev_elem;
        delete u;
        size_value--;
        return ret;
    }

    template <class T> void DList<T>::clear() {
        int n = size_value;
        for (int i = 0; i < n; i++) {
            pop_front();
        }
    }
    
    template <class T> bool DList<T>::empty() {
        return size_value == 0 ? true : false;
    }
    
    template <class T> unsigned DList<T>::size() const {
        return size_value;
    }
    
    template <class T> void DList<T>::reverse() {
        Unit* currentSwap = first_elem;
        Unit* buf = first_elem;
        first_elem = last_elem;
        last_elem = buf;
        for (int i = 0; i < size_value; i++) {
            buf = currentSwap->next_elem;
            currentSwap->next_elem = currentSwap->prev_elem;
            currentSwap->prev_elem = buf;
            currentSwap = currentSwap->prev_elem;
        }
    }
    
    template< class T> void DList<T>::set_throw_mode(bool mode_){
        mode = mode_;
    }
    
    template< class T> bool DList<T>::get_throw_mode(){
        return mode;
    }
    
// ---- End of DList template class implementation ----
};