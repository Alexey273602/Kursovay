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
	cout << "������� �����" << endl;
	getline(cin, login);
	for (; numOfUser < UserArr.size(); numOfUser++)
	{
		if (UserArr[numOfUser].login == login)
		{
			isLogCorrect = 1;
			cout << "������� ������" << endl;
			cin >> password;
			getchar();
			if (password == UserArr[numOfUser].password)
			{
				cout << "����� ����������, " << UserArr[numOfUser].login << "!" << endl;
				menu();
				break;
			}
			else
			{
				cout << "�������� ������" << endl;
				isPassCorrect = 0;
				break;
			}
		}
	}
	if (!isLogCorrect)
		cout << "������������ � ����� ������ �� ���������������" << endl;
	if (!isLogCorrect || !isPassCorrect)
	{

		while (choise != '2')
		{
			cout << "1.�����" << endl;
			cout << "2.��������� � ����" << endl;
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
					cout << "������ �������� �����" << endl;
					break;
				}
			}
			else
			{
				cout << "������� ������ ����� ����" << endl;
				choise = 0;
			}
		}
	}
}
