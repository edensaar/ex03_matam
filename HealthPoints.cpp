//
// Created by EDEN on 07/03/2024.
//

#include "HealthPoints.h"
#include <iostream>
using namespace std;

HealthPoints::HealthPoints(int hp, int maxHP ) {
    if(hp <= 0){
        throw InvalidArgument();
    }
    else{
        this->hp = hp;
        this->maxHP = hp;
    }
}

HealthPoints& HealthPoints::operator+=(const int add) {
    if(this->hp + add > this->maxHP){
        this->hp = this->maxHP;
    }
    else{
        this->hp += add;
    }
    return *this;
}

HealthPoints operator+(const int add, const HealthPoints& obj) {
    HealthPoints result = obj;
    if(result.hp + add > result.maxHP){
        result.hp = result.maxHP;
    }
    else{
        result.hp += add;
    }
    return result;
}

HealthPoints operator+(const HealthPoints& obj, const int add) {
    HealthPoints result = obj;
    if(result.hp + add > result.maxHP){
        result.hp = result.maxHP;
    }
    else{
        result.hp += add;
    }
    return result;
}

HealthPoints& HealthPoints::operator-=(const int subs) {
    if(this->hp - subs < 0){
        this->hp = 0;
    }
    else{
        this->hp -= subs;
    }
    return *this;
}

HealthPoints operator-(const int subs, const HealthPoints& obj) {
    HealthPoints result = obj;
    if(result.hp - subs < 0){
        result.hp = 0;
    }
    else{
        result.hp -= subs;
    }
    return result;
}

HealthPoints operator-(const HealthPoints& obj, const int subs) {
    HealthPoints result = obj;
    if(result.hp - subs < 0){
        result.hp = 0;
    }
    else{
        result.hp -= subs;
    }
    return result;
}


bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1.hp == healthPoints2.hp){
        return true;
    }
    return false;
}

bool operator<(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1.hp < healthPoints2.hp){
        return true;
    }
    return false;
}

bool operator<=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1 < healthPoints2 || healthPoints1 == healthPoints2){
        return true;
    }
    return false;
}

bool operator>=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1 > healthPoints2 || healthPoints1 == healthPoints2){
        return true;
    }
    return false;
}

bool operator>(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1.hp <= healthPoints2.hp){
        return false;
    }
    return true;
}

bool operator!=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1 == healthPoints2){
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints){
    os << healthPoints.hp << "(" << healthPoints.maxHP << ")";
    return os;
}

int main(){
    HealthPoints healthPoints1; /* has 100 points out of 100 */
    HealthPoints healthPoints2(150);
    if(healthPoints2 == healthPoints1){
        cout << "sarah is the best" << endl;
    }
}