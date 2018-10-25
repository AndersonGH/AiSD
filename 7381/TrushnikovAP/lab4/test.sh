#!/bin/bash

echo "Запуск тестов..."

echo "Тест №1: (a+b)*3"
./lab4 \( a + b \) \* 3

echo "Тест №2: a"
./lab4 a

echo "Тест №3: a*6-9+3*(a-7)"
./lab4 a \* 6 - 9 + 3 \* \( a - 7 \)

echo "Тест №4: (b-c-d)*(a+b)-3"
./lab4 \( b - c - d \) \* \( a + b \) - 3