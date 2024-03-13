#pragma once
#include <iostream>
#include <utility>

class Dummy {
public:
    int *num;
    Dummy() {
        num = new int{0};
    }
    ~Dummy() {
        delete num;
    }
    Dummy(const Dummy& otherDummy){
        num = new int;
        *num = *otherDummy.num;
    }

    Dummy& operator=(const Dummy& otherDummy) {
        if (this != &otherDummy) {
            delete num;
            num = new int;
            *num = *otherDummy.num;
        }
        return *this;
    }

};

void dummyTest();