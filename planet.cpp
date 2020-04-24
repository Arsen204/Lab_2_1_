#include "planet.h"
#include <iostream>
#include <iomanip>
using namespace std;

Planet::Planet() {
    name = nullptr;
    dim = 0;
    life = 0;
    sp_count = 0;
}

void Planet::print(){
    cout<<left<<setw(15)<<name;
    cout<<left<<setw(15)<<dim;
    cout<<left<<setw(15)<<life;
    cout<<left<<setw(15)<<sp_count<<endl;
}

char* Planet::get_name(){
    return name;
}

unsigned int Planet::get_dim(){
    return dim;
}

bool Planet::get_life(){
    return life;
}

unsigned int Planet::get_sp_count(){
    return sp_count;
}

void Planet::set_name(const char* name){
    if (this->name == nullptr) this->name = new char[strlen(name)-1];
    strcpy(this->name, name);
}

void Planet::set_dim(unsigned long dim){
    this->dim = dim;
}

void Planet::set_life(bool life){
    this->life = life;
}

void Planet::set_sp_count(unsigned int sp_count){
    this->sp_count = sp_count;
}

bool operator ==(Planet& a,Planet& b){
    return (strcmp(a.name,b.name)==0);
}

bool operator <(Planet& a,Planet& b){
    return (strcmp(a.name,b.name)<0);
}

Planet::~Planet(){
    delete[] this->name;
}