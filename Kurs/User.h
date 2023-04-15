#pragma once
#include"libraries.h"
struct User {
	string login;
	string password;
	bool isAdmin;
	bool isBanned;
	bool access;
};
extern vector <User> UserArr;
struct Employee {
	string Name; 
	string post;
	string dataBegin;
	string dataEnd;
	int experience;
	string expStr;
};
extern vector <Employee> EmployeeArr;
