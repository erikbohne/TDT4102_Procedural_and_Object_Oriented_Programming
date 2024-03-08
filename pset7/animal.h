#pragma once
#include "std_lib_facilities.h"


// Animal er en abstrakt klasse som inneholder en ren virtuell funksjon toString som ikke har noen implementasjon. 
// Dette er fordi den er avhengig av hvilken klasse som arver fra Animal.
class Animal {
protected:
    string name;
    int age;

public:
    Animal(string name, int age) : name(name), age(age) {}
    virtual ~Animal() {}
    virtual string toString() = 0;
};


// Cat og Dog er klasser som arver fra Animal.
class Cat : public Animal {
public:
    Cat(string name, int age) : Animal(name, age) {}
    string toString() override {
        return "Cat: " + name + ", " + to_string(age);
    }
};

class Dog : public Animal {
public:
    Dog(string name, int age) : Animal(name, age) {}
    string toString() override {
        return "Dog: " + name + ", " + to_string(age);
    }
};
