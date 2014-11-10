#include <functional>
#include <set>
#include <stdio.h>

struct T {
    int val;
    int b;
};

int main() {
    std::set<std::reference_wrapper<T> > s;
    T a;
    a.val = 1;
    a.b = 2;
    s.insert(a);
    printf("%d",*(s.begin()).get.val);
}