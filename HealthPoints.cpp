//
// Created by EDEN on 04/03/2024.
//
#include "HealthPoints.h"

HealthPoints::HealthPoints(int hp, int maxHP ) {
    if(hp <= 0){
        throw NegHp();
    }
    else{
        this->hp = hp;
        this->maxHP = hp;
    }
}





HealthPoints& HealthPoints::operator+(const int add) {
    if(this->hp + add > this->maxHP){
        this->hp = this->maxHP;
    }
    else{
        this->hp += add;
    }
    return *this;
}

HealthPoints& HealthPoints::operator+=(const int add) {
   HealthPoints result(*this);
   return result + add;
}


HealthPoints& HealthPoints::operator-(const int subs) {
    if(this->hp - subs < 0){
        this->hp = 0;
    }
    else{
        this->hp -= subs;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(const int subs) {
    HealthPoints result(*this);
    return result - subs;
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
    if(healthPoints1 > healthPoints2){
        return true;
    }
    return false;
}

bool operator!=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1 == healthPoints2){
        return false;
    }
    return true;
}
