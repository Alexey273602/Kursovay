#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<string>
#include<Windows.h>
#include<conio.h>
const char ESC = 27;
const char UP = 72;
const char DOWN = 80;
const char ENTER = 13;
const char LEFT = 75;
const char RIGHT = 77;
using namespace std;

void menuSearch(int n);
void menuSort(int n);
void menuCRUDEmplAdm(int n);
void menuCRUDEmplUser(int n);
void searchExp(int n);
void searchName(int n);
void searchPost(int n);
void sortExp(int n);
void sortName(int n);
void sortPost(int n);
void clear();
void menuMain();
void overwritingEmployeesFromFVectorToFile();