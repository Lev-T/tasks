#include <assert.h>
#include "iface.h"
#include <stdio.h>

int main(){
    typedef Task::DList<int> List;
    typedef List::Unit Unit;
    
    List list;
    assert(list.size() == 0);
    assert(list.first() == 0);
    assert(list.first() == list.last());
    
    
    list.push_front(3);
    list.push_front(123);
    assert(list.last()->val() == 3);
    assert(list.first()->val() == 123);
    assert(list.size() == 2);
    assert(list.first()->prev() == 0);
    assert(list.last()->next() == 0);
    assert(!list.empty());
    
    list.clear();
    assert(list.size() == 0);
    assert(list.first() == 0);
    assert(list.first() == list.last());
    assert(list.empty());
    
    list.push_back(3);
    list.push_back(123);
    assert(list.first()->val() == 3);
    assert(list.last()->val() == 123);
    assert(list.size() == 2);
    
    list.pop_back();
    assert(list.first() == list.last());
    assert(list.first()->val() == 3);
    
    list.push_front(123);
    list.pop_front();
    assert(list.first() == list.last());
    assert(list.first()->val() == 3);
    
    list.clear();
    for (int i = 1; i < 11; i++) {
        list.push_front(i);
    }
    Unit* unit = list.erase(list.first());
    assert(unit->val() == 9);
    assert(list.size() == 9);

    unit = list.erase(list.last());
    assert(unit == 0);
    assert(list.size() == 8);
    
    unit = list.erase(list.first()->next()->next());
    assert(list.size() == 7);
    assert(unit->prev()->val() == 8);
    assert(unit->next()->val() == 5);
    
    list.clear();
    for (int i = 1; i < 11; i++) {
        list.push_front(i);
    }
    
    list.insert(list.first(), 11);
    assert(list.first()->next()->val() == 10);
    assert(list.first()->val() == 11);
    assert(list.size() == 11);
    
    list.insert(list.last(), 12);
    assert(list.last()->prev()->val() == 12);
    assert(list.last()->prev()->prev()->val() == 2);
    

    
    
    printf("all tests completed\n");
//    getchar();
    return 0;
    
}