//
// Created by EDEN on 04/03/2024.
//

#ifndef UNTITLED4_HEALTHPOINTS_H
#define UNTITLED4_HEALTHPOINTS_H

#endif //UNTITLED4_HEALTHPOINTS_H
#include "iostream"

class NegHp {};

class HealthPoints{


public:
    int hp;
    int maxHP;
    HealthPoints(int hp = 100, int maxHP = 100);

    HealthPoints(const HealthPoints& healthPoints) = default;
    HealthPoints& operator=(const HealthPoints& other) = default;

    HealthPoints() = default;
    ~HealthPoints() = default;

    HealthPoints& operator+=(const int add);
    HealthPoints& operator+(const int add);
    HealthPoints& operator-(const int add);
    HealthPoints& operator-=(const int add);

    friend bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);
    friend bool operator<(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);
    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints);
};

bool operator>(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);
bool operator>=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);
bool operator<=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);
bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);

