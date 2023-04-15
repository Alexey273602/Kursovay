#pragma once
#include "User.h"
void menu();
void authorization()
{
	string login;
	string password;
	bool isLogCorrect = 0;
	bool isPassCorrect = 1;
	char choise = 0;
	int numOfUser = 0;
	string garbage;
	cout << "Введите логин" << endl;
	getline(cin, login);
	for (; numOfUser < UserArr.size(); numOfUser++)
	{
		if (UserArr[numOfUser].login == login)
		{
			isLogCorrect = 1;
			cout << "Введите пароль" << endl;
			cin >> password;
			getchar();
			if (password == UserArr[numOfUser].password)
			{
				cout << "Добро пожаловать, " << UserArr[numOfUser].login << "!" << endl;
				menu();
				break;
			}
			else
			{
				cout << "Неверный пароль" << endl;
				isPassCorrect = 0;
				break;
			}
		}
	}
	if (!isLogCorrect)
		cout << "Пользователь с таким именем не зарегистрирован" << endl;
	if (!isLogCorrect || !isPassCorrect)
	{

		while (choise != '2')
		{
			cout << "1.Войти" << endl;
			cout << "2.Вернуться в меню" << endl;
			choise = getchar();
			getline(cin, garbage);
			if (garbage == "")
			{
				switch (choise)
				{
				case'1':
					authorization();
				case'2':
					break;
				default:
					cout << "Выбран неверный пункт" << endl;
					break;
				}
			}
			else
			{
				cout << "Неверно выбран пункт меню" << endl;
				choise = 0;
			}
		}
	}
}
