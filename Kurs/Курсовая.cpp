#include"User.h"

string fileUser = "accounts.txt";
string fileEmployee = "employees.txt";
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x,y });
}
void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void overwritingUsersFromFileToVector()
{
	ifstream fin(fileUser);
	string login;
	string password;
	bool isAdmin = 0;
	bool isBanned = 0;
	if (!fin.is_open())
		cout << "Не удалось открыть файл" << endl;
	else
	{
		while (fin >> login)
		{
			fin >> password;
			fin >> isAdmin;
			fin >> isBanned;
			UserArr.push_back({ login,password,isAdmin,isBanned });
		}
	}
	fin.close();
}
void overwritingUsersFromVectorToFile()
{
	ofstream fout(fileUser);
	if (!fout.is_open())
		cout << "Не удалось открыть файл" << endl;
	else
		for (int i = 0; i < UserArr.size(); i++)
			fout << UserArr[i].login << endl << UserArr[i].password << endl << UserArr[i].isAdmin << endl << UserArr[i].isAdmin << endl;
	fout.close();
}
void overwritingEmployeesFromFileToVector()
{
	ifstream fin(fileEmployee);
	string Name;
	string post;
	string dataBegin;
	string dataEnd;
	if (!fin.is_open())
		cout << "Не удалось открыть файл" << endl;
	else
	{
		while (getline(fin, Name))
		{
			getline(fin, post);
			getline(fin, dataBegin);
			getline(fin, dataEnd);
			EmployeeArr.push_back({ Name,post,dataBegin,dataEnd });
		}
	}
	fin.close();
}
void overwritingEmployeesFromFVectorToFile()
{
	ofstream fout(fileEmployee);
	string Name;
	string post;
	string dataBegin;
	string dataEnd;
	if (!fout.is_open())
		cout << "Не удалось открыть файл" << endl;
	else
		for (int i = 0; i < EmployeeArr.size(); i++)
			fout << EmployeeArr[i].Name << endl << EmployeeArr[i].post << endl << EmployeeArr[i].dataBegin << endl << EmployeeArr[i].dataEnd << endl;
	fout.close();
}

void registration()
{
	string login;
	string password;
	string space;
	ofstream fout(fileUser, ios::app);
	int x = 50, y = 12;
	bool end = 0;
	char choice = '0';
	while (1)
	{ 
		
		x = 50, y = 12;
		bool isCorrect = 1;
		GoToXY(x, y++);
		cout << "Введите логин" << endl;
		GoToXY(x, y++);
		cin >> login;
		getline(cin, space);
		system("cls");
		if (space == "")
		{
			for (int i = 0; i < UserArr.size(); i++)
			{
				if (UserArr[i].login == login)
				{
					GoToXY(38, 10);
					cout << "Пользователь с таким именем уже зарегистрирован" << endl;
					isCorrect = 0;
					break;
				}
			}
			if (isCorrect == 1)
				break;
		}
		else
		{
			GoToXY(x, y++);
			cout << "Логин не должен содержать пробелов" << endl;
		}
		if (isCorrect == 0)
		{
			string regMenu[] = { "Попробовать снова","Вернуться в главное меню" };
			int activeMenu = 0;
				while (!end)
				{
					int x = 50, y = 12;
					GoToXY(x, y);
					for (int i = 0; i < size(regMenu); i++)
					{
						if (i == activeMenu)
							SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						else SetConsoleTextAttribute(hStdOut, 0x0007);
						GoToXY(x, y++);
						cout << regMenu[i];
					}
					SetConsoleTextAttribute(hStdOut, 0x0007);
					choice = _getch();
					if (choice == -32)
						choice = _getch();
					switch (choice)
					{
					case DOWN:
						if (activeMenu < size(regMenu) - 1)
							activeMenu++;
						break;
					case UP:
						if (activeMenu > 0)
							activeMenu--;
						break;
					case ENTER:
						switch (activeMenu)
						{
						case 0:
							system("cls");
							registration();

						case 1:
							system("cls");
							menuMain();
							GoToXY(0, 25);
							exit(0);
							break;
						}
					}
				}
		}
	}
	system("cls");
	while (1)
	{
		x = 50;
		y = 12;
		GoToXY(x, y++);
		cout << "Введите пароль" << endl;
		GoToXY(x, y++);
		cin >> password;
		system("cls");
		getline(cin, space);
		GoToXY(38, 10);
		if (space != "")
			cout << "Пароль не должен содержать пробелов" << endl;
		else if (size(password) < 8)
			cout << "Пароль должен содержать не менее 8 символов" << endl;
		else
			break;


	}
	UserArr.push_back({ login,password,0,0 });
	fout << login << endl;
	fout << password << endl;
	fout << 0 << endl;
	fout << 0 << endl;
	GoToXY(x, y++);
	cout << "Вы успешно зарегистрировались!" << endl;
	GoToXY(0, 29);
	system("pause");
	system("cls");
	
}
int authorization()
{
	int numOfUser;
	bool end = 0;
	bool isLogged;
	while (!end)
	{
		string login;
		string password;
		bool isLogCorrect = 0;
		bool isPassCorrect = 1;
		isLogged = 0;
		char choice = 0;
		numOfUser = 0;
		bool end2 = 0;


		int x = 50, y = 12;
		GoToXY(x, y++);
		cout << "Введите логин" << endl;
		GoToXY(x, y++);
		cin >> login;
		GoToXY(x, y++);
		for (; numOfUser < UserArr.size(); numOfUser++)
		{
			if (UserArr[numOfUser].login == login)
			{
				isLogCorrect = 1;
				cout << "Введите пароль" << endl;
				GoToXY(x, y++);
				cin >> password;
				if (password == UserArr[numOfUser].password)
				{
					system("cls");
					GoToXY(x, 12);
					isLogged = 1;
					end++;
					break;
				}
				else
				{
					system("cls");
					GoToXY(x, 12);
					cout << "Неверный пароль" << endl;
					isPassCorrect = 0;
					break;
				}
			}
		}
		if (!isLogCorrect)
		{
			system("cls");
			GoToXY(40, 12);
			cout << "Пользователь с таким именем не зарегистрирован" << endl;
		}
		string autMenu[] = { "Попробовать снова","Вернуться в главное меню" };
		int activeMenu = 0;
		if (!isLogCorrect || !isPassCorrect)
		{
			while (!end2 && !end)
			{
				int x = 50, y = 14;
				GoToXY(x, y);
				for (int i = 0; i < size(autMenu); i++)
				{
					if (i == activeMenu)
						SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					else SetConsoleTextAttribute(hStdOut, 0x0007);
					GoToXY(x, y++);
					cout << autMenu[i];
				}
				SetConsoleTextAttribute(hStdOut, 0x0007);
				choice = _getch();
				if (choice == -32)
					choice = _getch();
				switch (choice)
				{
				case DOWN:
					if (activeMenu < size(autMenu) - 1)
						activeMenu++;
					break;
				case UP:
					if (activeMenu > 0)
						activeMenu--;
					break;
				case ENTER:
					switch (activeMenu)
					{
					case 0:
						system("cls");
						end2++;
						break;
					case 1:
						system("cls");
						end++;
						break;
					}
				}
			}
		}
	}
	if (isLogged)
		return numOfUser;
	else
		return -1;
}


void printEmployee()
{
	int length = 77;
	cout << " " << setfill('_') << setw(length - 2) << "" << setfill(' ') << " " << endl;
	cout << "| " << setw(16) << "ФИО" << setw(15) << " |"
		<< setw(12) << "Должность" << setw(5) << " |"
		<< setw(15) << "Стаж" << setw(12) << " |" << endl;
	for (int i = 0; i < EmployeeArr.size(); i++)
	{
		cout << "|" << setfill('=') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
		cout << "|" << setw(30) << EmployeeArr[i].Name << " |"
			<< setw(15) << EmployeeArr[i].post << " |"
			<< setw(25) << EmployeeArr[i].expStr << " |" << endl;

	}
	cout << "|" << setfill('_') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
}
void countExperience(int i)
{
		int yearBegin = stoi(EmployeeArr[i].dataBegin.substr(EmployeeArr[i].dataBegin.rfind('.') + 1));
		int yearEnd = stoi(EmployeeArr[i].dataEnd.substr(EmployeeArr[i].dataEnd.rfind('.') + 1));
		int monthBegin = stoi(EmployeeArr[i].dataBegin.substr(EmployeeArr[i].dataBegin.find('.') + 1, EmployeeArr[i].dataBegin.rfind('.') - EmployeeArr[i].dataBegin.find('.') - 1));
		int monthEnd = stoi(EmployeeArr[i].dataEnd.substr(EmployeeArr[i].dataEnd.find('.') + 1, EmployeeArr[i].dataEnd.rfind('.') - EmployeeArr[i].dataEnd.find('.') - 1));

		int expYears = yearEnd - yearBegin;
		int expMonths = monthEnd - monthBegin;
		EmployeeArr[i].experience = expYears * 12 + expMonths;
		if (expMonths < 0)
		{
			expMonths += 12;
			expYears--;
		}
		string expStr;
		if (expYears <= 0) {
			expStr = "";
		}
		else if (expYears % 10 == 1) {
			expStr = to_string(expYears) + " год и ";
		}
		else if (expYears % 10 >= 2 && expYears % 10 <= 4) {
			expStr = to_string(expYears) + " года и ";
		}
		else {
			expStr = to_string(expYears) + " лет и ";
		}
		if (expMonths == 0) {
			expStr += "менее месяца";
		}
		else if (expMonths == 1) {
			expStr += "1 месяц";
		}
		else if (expMonths >= 2 && expMonths <= 4) {
			expStr += to_string(expMonths) + " месяца";
		}
		else {
			expStr += to_string(expMonths) + " месяцев";
		}
		EmployeeArr[i].expStr = expStr;
}
void printUser()
{
	int length = 92;
	string admin;
	string ban;
	system("cls");
	cout << " " << setfill('_') << setw(length - 2) << "" << setfill(' ') << endl;
	cout << "| " << setw(16) << "Логин" << setw(15) << " |"
		<< setw(27) << "Статус учётной записи" << setw(5) << " |"
		<< setw(23) << "Роль учётной записи" << setw(4) << " |" << endl;
	cout << "|" << setfill('=') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
	for (int i = 0; i < UserArr.size(); i++)
	{
		if (UserArr[i].isAdmin == 1)
			admin = "Администратор";
		else
			admin = "Пользователь";
		if (UserArr[i].isBanned == 1)
			ban = "Заблокирована";
		else
			ban = "Активна";
		cout << "|" << setw(30) << UserArr[i].login << " |"
			<< setw(30) << ban << " |"
			<< setw(25) << admin << " |" << endl
			<< "|" << setfill('=') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
	}
	system("pause");
}
void changePassword(int numOfUser)
{
	bool end = 0;
	string password;
	string newPassword;
	string verifyPassword;
	string error;
	char space;
	while (!end)
	{
		while (1)
		{
			int x = 50, y = 12;
			GoToXY(x, y++);
			cout << "Введите пароль" << endl;
			GoToXY(x, y++);
			cin >> password;
			if (password == UserArr[numOfUser].password)
			{
				GoToXY(x, y++);
				cout << "Введите новый пароль" << endl;
				GoToXY(x, y++);
				cin >> newPassword;
				space = getchar();
				if (newPassword.length() < 8)
				{
					system("cls");
					GoToXY(x, y++);
					error =  "Пароль должен содержать не менее 8 символов\n";
					break;
				}
				else if (newPassword == UserArr[numOfUser].password)
				{
					system("cls");
					GoToXY(x, y++);
					error = "Старый и новый пароли совпадают\n";
					break;
				}
				else if (space == ' ')
				{
					system("cls");
					GoToXY(x, y++);
					error =  "Пароль не должен содержать пробелов\n";
					break;
				}
				GoToXY(x, y++);
				cout << "Подтвердите пароль:" << endl;
				GoToXY(x, y++);
				cin >> verifyPassword;
				if (newPassword != verifyPassword)
				{
					system("cls");
					error = "Введенные пароли не совпадают\n";
					break;
				}
				UserArr[numOfUser].password = newPassword;
				end = 1;
				GoToXY(x, y++);
				cout << "Пароль успешно изменён!" << endl;
				GoToXY(0, 27);
				system("pause");
				system("cls");
				break;
			}
			else
			{
				system("cls");
				error = "Неверный пароль\n" ;
			}
		}
		string menuChangePassword[] = { "Попробовать ещё раз",
		"Назад"};
		int activeMenu = 0;
		while (!end)
		{

			
			SetConsoleTextAttribute(hStdOut, 0x0007);
			int x = 50, y = 12;
			GoToXY(x, y++);
			cout << error << endl;
			for (int i = 0; i < size(menuChangePassword); i++)
			{
				if (i == activeMenu)
					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				else SetConsoleTextAttribute(hStdOut, 0x0007);
				GoToXY(x, y++);
				cout << menuChangePassword[i];
			}
			char choice = _getch();
			if (choice == -32)
				choice = _getch();
			switch (choice)
			{
			case DOWN:
				if (activeMenu < size(menuChangePassword) - 1)
					activeMenu++;
				break;
			case UP:
				if (activeMenu > 0)
					activeMenu--;
				break;
			case ENTER:
				switch (activeMenu)
			case 0:
				{
					system("cls");
					changePassword(numOfUser);
					break;
				}
			case 1:
				end++;
				break;

			}
		}
	}
}
void addEmployee()
{
	string Name;
	string post;
	string dataBegin;
	string dataEnd;
	int x = 50, y = 12;
	GoToXY(x, y++);
	getchar();
	cout << "Введите ФИО сотрудника" << endl;
	GoToXY(x, y++);
	getline(cin, Name);
	GoToXY(x, y++);
	cout << "Введите должность сотрудника" << endl;
	GoToXY(x, y++);
	getline(cin, post);
	GoToXY(x, y++);
	cout << "Введите дату вступления сотрудника в должность " << endl;
	GoToXY(x, y++);
	getline(cin, dataBegin);
	GoToXY(x, y++);
	cout << "Введите дату отстранения сотрудника от должности " << endl;
	GoToXY(x, y++);
	getline(cin, dataEnd);
	EmployeeArr.push_back({ Name, post, dataBegin, dataEnd });
	countExperience(EmployeeArr.size() - 1);
}
void deleteEmployee()
{
	int activeMenu = 0;
	char choice;
	bool end = 0;
	while (!end)
	{
		int activeProof = 0;
		int x = 50, y = 10;
		system("cls");
		GoToXY(x, y++);
		cout << "Выберите сотрудника, данные о котором хотите удалить" << endl;
		for (int i = 0; i < EmployeeArr.size(); i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			GoToXY(x, y++);
			cout << EmployeeArr[i].Name;
		}
		SetConsoleTextAttribute(hStdOut, 0x0007);
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu < EmployeeArr.size() - 1)
				activeMenu++;
			break;
		case UP:
			if (activeMenu > 0)
				activeMenu--;
			break;
		case ENTER:
		{
			while (!end)
			{
				system("cls");
				x = 30, y = 12;
				GoToXY(x, y);
				y += 6;
				x = 50;
				cout << "Вы точно хотите удалить данные сотрудника " << EmployeeArr[activeMenu].Name << "?" << endl;
				string proof[] = { "Да","Нет" };
				for (int i = 0; i < size(proof); i++)
				{
					if (i == activeProof)
						SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					else SetConsoleTextAttribute(hStdOut, 0x0007);
					GoToXY(x, y);
					x += 20;
					cout << proof[i];
				}
				SetConsoleTextAttribute(hStdOut, 0x0007);
				choice = _getch();
				if (choice == -32)
					choice = _getch();
				switch (choice)
				{
				case RIGHT:
					if (activeProof < size(proof)-1)
						activeProof++;
					break;
				case LEFT:
					if (activeProof > 0)
						activeProof--;
					break;
				case ENTER:
					switch (activeProof)
					{
					case 0:
						EmployeeArr.erase(EmployeeArr.begin() + activeMenu);
						break;
					case 1:
						break;
					}
					end++;
					break;
				}
			}

		}
		}
	}
}
void editEmployee()
{
	char choice = 0;
	bool end = 0;
	int activeMenu = 0;
	while (!end)
	{
		int x = 50, y = 12;
		system("cls");
		GoToXY(38, 10);
		cout << "Выберите сотрудника, данные о котором хотите редактировать" << endl;
		for (int i = 0; i < EmployeeArr.size()+1; i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			GoToXY(x, y++);
			if (i != EmployeeArr.size())
				cout << EmployeeArr[i].Name;
			else
			{
				GoToXY(57, y++);
				cout << "Назад";
			}
		}
		SetConsoleTextAttribute(hStdOut, 0x0007);
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu < EmployeeArr.size())
				activeMenu++;
			break;
		case UP:
			if (activeMenu > 0)
				activeMenu--;
			break;
		case ENTER:
		{
			if (activeMenu == EmployeeArr.size())
				end++;
			else
			{ 
			string EmplEdit[] = {"ФИО:" + EmployeeArr[activeMenu].Name,
		"Должность: "+EmployeeArr[activeMenu].post,
		"Дата вступления в должность: "+EmployeeArr[activeMenu].dataBegin,
		"Дата отстранения от должности: "+EmployeeArr[activeMenu].dataEnd};
			
			system("cls");
			GoToXY(x, y);
			y += 2;
			cout << "Выберите данные, которые хотите редактировать" << endl;
			int activeMenu2 = 0;
			
		while(!end)
		{
			x = 50, y = 12;
			system("cls");
			for (int i = 0; i < size(EmplEdit); i++)
			{
				if (i == activeMenu2)
					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				else SetConsoleTextAttribute(hStdOut, 0x0007);
				GoToXY(x, y++);
				cout << EmplEdit[i];
			}
			SetConsoleTextAttribute(hStdOut, 0x0007);
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu2 < size(EmplEdit) - 1)
				activeMenu2++;
			break;
		case UP:
			if (activeMenu2 > 0)
				activeMenu2--;
			break;
		case ENTER:
		{
			x = 50, y = 12;
			system("cls");
			switch (activeMenu2)
			{
			case 0:
				GoToXY(x, y++);
				cout << "Введите новое ФИО:";
				GoToXY(x, y++);
				getline(cin >> ws, EmployeeArr[activeMenu].Name);
				break;
			case 1:
				GoToXY(x, y++);
				cout << "Введите новую должность:";
				GoToXY(x, y++);
				getline(cin >> ws, EmployeeArr[activeMenu].post);
				break;
			case 2:
				GoToXY(x, y++);
				cout << "Введите новую дату вступления в должность:";
				GoToXY(x, y++);
				getline(cin >> ws, EmployeeArr[activeMenu].dataBegin);
				break;
			case 3:
				GoToXY(x, y++);
				cout << "Введите новую дату отстранения от должности:";
				GoToXY(x, y++);
				getline(cin >> ws, EmployeeArr[activeMenu].dataEnd);
				break;
			}
			end++;
		}
		}
			}

			}
		}
		}
		}
	}
	 
void menuCRUDEmplAdm(int n)
{
	string EmplCRUDmenuAdm[] = { "Сортировать список сотрудников",
		"Найти сотрудника",
		"Добавить информацию о новом сотруднике",
		"Удалить информацию о сотруднике",
		"Редактировать информацию о сотруднике",
		"Выйти из меню сотрудников" };
	int activeMenu = 0;
	char choice = 0;
	bool end = 0;
	while (!end)
	{
		system("cls");
		SetConsoleTextAttribute(hStdOut, 0x0007);
		printEmployee();
		for (int i = 0; i < size(EmplCRUDmenuAdm); i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			cout << EmplCRUDmenuAdm[i] << endl;
		}
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu < size(EmplCRUDmenuAdm) - 1)
				activeMenu++;
			break;
		case UP:
			if (activeMenu > 0)
				activeMenu--;
			break;
		case ENTER:
			switch (activeMenu)
			{
			case 0:
				menuSort(n);
				break;
			case 1:
				system("cls");
				menuSearch(n);
				system("pause");
				break;
			case 2:
				system("cls");
				addEmployee();
				break;
			case 3:
				system("cls");
				deleteEmployee();
				break;
			case 4:
				system("cls");
				editEmployee();
				break;
			case 5:
				end = 1;
				break;
			}
		}
	}
}
void menuCRUDEmplUser(int n)
{
	string EmplCRUDmenuUser[] = { "Сортировать список сотрудников",
		"Найти сотрудника",
		"Выйти из меню сотрудников" };
	int activeMenu = 0;
	char choice = 0;
	bool end = 0;
	while (!end)
	{
		system("cls");
		SetConsoleTextAttribute(hStdOut, 0x0007);
		printEmployee();
		for (int i = 0; i < size(EmplCRUDmenuUser); i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			cout << EmplCRUDmenuUser[i] << endl;
		}
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu < size(EmplCRUDmenuUser) - 1)
				activeMenu++;
			break;
		case UP:
			if (activeMenu > 0)
				activeMenu--;
			break;
		case ENTER:
			switch (activeMenu)
			{
			case 0:
				menuSort(n);
				break;
			case 1:
				system("cls");
				menuSearch(n);
				system("pause");
				break;
			case 2:
				end = 1;
				break;
			}
		}
	}
}
void menuAdmin(int n)
{
	int activeMenu = 1;
	int numOfUser = n;
	char choice = 0;
	string garbage;
	string menuAdmin[] = { "",
		"Вывести сотрудников" ,
		"Изменить пароль", 
		"Вывести пользователей" ,
		"Выйти из учетной записи" };
	bool end = 0;
	while (!end)

	{
		SetConsoleTextAttribute(hStdOut, 0x0007);
		int x = 50, y = 10;
		GoToXY(x, y);
		cout << "Добро пожаловать, " << UserArr[n].login << "!";
		y += 2;
		for (int i = 0; i < size(menuAdmin); i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			GoToXY(x, y++);
			cout << menuAdmin[i];
		}
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu < size(menuAdmin) - 1)
				activeMenu++;
			break;
		case UP:
			if (activeMenu > 1)
				activeMenu--;
			break;
		case ENTER:
			switch (activeMenu)
			{
			case 1:
			{
				system("cls");
				menuCRUDEmplAdm(numOfUser);
				break;
			}
			case 2:
			{
				system("cls");
				changePassword(numOfUser);
				break;
			}
			case 3:
			{
				system("cls");
				printUser();
				break;
			}
			case 4:
			{
				end++;
				break;
			}

			}
			system("cls");
		}
	}
}
void menuUser(int n)    
{
	int activeMenu = 1;
	int numOfUser = n;
	char choice = 0;
	string garbage;
	string menuUs[] = { "",
		"Вывести сотрудников" ,
		"Изменить пароль",
		"Выйти из учетной записи" };
	bool end = 0;
	while (!end)

	{
		int x = 50, y = 10;
		GoToXY(x, y);
		cout << "Добро пожаловать, " << UserArr[n].login << "!";
		y += 2;
		for (int i = 0; i < size(menuUs); i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			GoToXY(x, y++);
			cout << menuUs[i];
		}
		SetConsoleTextAttribute(hStdOut, 0x0007);
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu < size(menuUs) - 1)
				activeMenu++;
			break;
		case UP:
			if (activeMenu > 1)
				activeMenu--;
			break;
		case ENTER:
			switch (activeMenu)
			{
			case 1:
			{
				system("cls");
				menuCRUDEmplUser(numOfUser);
				break;
			}
			case 2:
			{
				system("cls");
				changePassword(numOfUser);
				break;
			}
			case 3:
			{
				end++;
				break;
			}
			}
			system("cls");
		}
	}
}
void menuSort(int n)
{
	string sortMenu[] = { "Сортировать пользователей по имени",
			"Сортировать пользователей по должности",
			"Сортировать пользователей по стажу",
			"Назад" };
	int activeMenu = 0;
	char choice = 0;
	bool end = 0;
	while (!end)
	{
		system("cls");
		SetConsoleTextAttribute(hStdOut, 0x0007);
		printEmployee();
		for (int i = 0; i < size(sortMenu); i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			cout << sortMenu[i] << endl;
		}
		SetConsoleTextAttribute(hStdOut, 0x0007);
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu < size(sortMenu) - 1)
				activeMenu++;
			break;
		case UP:
			if (activeMenu > 0)
				activeMenu--;
			break;
		case ENTER:
			switch (activeMenu)
			{
			case 0:
				sortName(n);
				break;
			case 1:
				sortPost(n);
				break;
			case 2:
				sortExp(n);
				break;
			case 3:
				end = 1;
				break;
			}
		}
	}
};
void menuSearch(int n)
{
	string searchMenu[] = { "Найти по имени",
		"Найти по должности",
		"Найти по стажу",
		"Назад" };
	int activeMenu = 0;
	char choice = 0;
	bool end = 0;
	while (!end)
	{
		system("cls");
		for (int i = 0; i < size(searchMenu); i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			cout << searchMenu[i] << endl;
		}
		SetConsoleTextAttribute(hStdOut, 0x0007);
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu < size(searchMenu) - 1)
				activeMenu++;
			break;
		case UP:
			if (activeMenu > 0)
				activeMenu--;
			break;
		case ENTER:
			switch (activeMenu)
			{
			case 0:
				searchName(n);
				break;
			case 1:
				searchPost(n);
				break;
			case 2:
				searchExp(n);
				break;
			case 3:
				end = 1;
				break;
			}
		}
	}
}

int flag = -1;
void sortName(int n)
{
	if (flag == 1)
		flag = -1;
	else
		flag = 1;
	for (int j = 0; j < EmployeeArr.size(); j++)
		for (int i = 0; i < EmployeeArr.size() - 1; i++)
		{
			if (flag == 1)
			{
				if (EmployeeArr[i].Name > EmployeeArr[i + 1].Name)
					swap(EmployeeArr[i], EmployeeArr[i + 1]);
			}
			else
				if (EmployeeArr[i].Name < EmployeeArr[i + 1].Name)
					swap(EmployeeArr[i], EmployeeArr[i + 1]);
		}			
}
void sortPost(int n)
{
	if (flag == 1)
		flag = -1;
	else
		flag = 1;
	for (int j = 0; j < EmployeeArr.size(); j++)
		for (int i = 0; i < EmployeeArr.size() - 1; i++)
		{	
			if (flag == 1)
			{
				if (EmployeeArr[i].post > EmployeeArr[i + 1].post)
					swap(EmployeeArr[i], EmployeeArr[i + 1]);
			}
			else
				if (EmployeeArr[i].post <  EmployeeArr[i + 1].post)
					swap(EmployeeArr[i], EmployeeArr[i + 1]);
		}	
}
void sortExp(int n)
{
	if (flag == 1)
		flag = -1;
	else
		flag = 1;
	for (int j = 0; j < EmployeeArr.size(); j++)
		for (int i = 0; i < EmployeeArr.size() - 1; i++)
			if (EmployeeArr[i].experience * flag < EmployeeArr[i + 1].experience * flag)
				swap(EmployeeArr[i], EmployeeArr[i + 1]);
}

void searchName(int n)
{
	string name;
	bool first = 1;
	int length = 75;
	int numOfResult=0;
	string search;
	cout << "Введите строку для поиска: ";
	cin >> search;
	for (int i = 0; i < EmployeeArr.size(); i++)
	{
		if (EmployeeArr[i].Name.find(search) != string::npos)
		{
			if (first == 1)
			{

				cout << " " << setfill('_') << setw(length) << "" << setfill(' ') << " " << endl;
				cout << "| " << setw(16) << "ФИО" << setw(15) << " |"
					<< setw(12) << "Должность" << setw(5) << " |"
					<< setw(15) << "Стаж" << setw(12) << " |" << endl;
				first=0;
			}
					cout << "|" << setfill('=') << setw(length) << "" << setfill(' ') << "|" << endl;
					cout << "|" << setw(30) << EmployeeArr[i].Name << " |"
						<< setw(15) << EmployeeArr[i].post << " |"
						<< setw(25) << EmployeeArr[i].expStr << " |" << endl;
			numOfResult++;
		}
	}
	if (numOfResult == 0)
		cout << "По вашему запросу ничего не найдено" << endl;
	else
	cout << "|" << setfill('_') << setw(length) << "" << setfill(' ') << "|" << endl;
	system("pause");
}
void searchPost(int n)
{
	string name;
	bool first = 1;
	int length = 75;
	int numOfResult=0;
	string search;
	cout << "Введите строку для поиска: ";
	cin >> search;
	for (int i = 0; i < EmployeeArr.size(); i++)
	{
		if (EmployeeArr[i].post.find(search) != string::npos)
		{
			if (first == 1)
			{

				cout << " " << setfill('_') << setw(length) << "" << setfill(' ') << " " << endl;
				cout << "| " << setw(16) << "ФИО" << setw(15) << " |"
					<< setw(12) << "Должность" << setw(5) << " |"
					<< setw(15) << "Стаж" << setw(12) << " |" << endl;
				first=0;
			}
					cout << "|" << setfill('=') << setw(length) << "" << setfill(' ') << "|" << endl;
					cout << "|" << setw(30) << EmployeeArr[i].Name << " |"
						<< setw(15) << EmployeeArr[i].post << " |"
						<< setw(25) << EmployeeArr[i].expStr << " |" << endl;
			numOfResult++;
		}
	}
	if (numOfResult == 0)
		cout << "По вашему запросу ничего не найдено" << endl;
	else
	cout << "|" << setfill('_') << setw(length) << "" << setfill(' ') << "|" << endl;
	system("pause");
}
void searchExp(int n)
{
	string name;
	bool first = 1;
	int length = 75;
	int numOfResult=0;
	string search;
	cout << "Введите строку для поиска: ";
	cin >> search;
	for (int i = 0; i < EmployeeArr.size(); i++)
	{
		if (EmployeeArr[i].expStr.find(search) != string::npos)
		{
			if (first == 1)
			{

				cout << " " << setfill('_') << setw(length) << "" << setfill(' ') << " " << endl;
				cout << "| " << setw(16) << "ФИО" << setw(15) << " |"
					<< setw(12) << "Должность" << setw(5) << " |"
					<< setw(15) << "Стаж" << setw(12) << " |" << endl;
				first=0;
			}
					cout << "|" << setfill('=') << setw(length) << "" << setfill(' ') << "|" << endl;
					cout << "|" << setw(30) << EmployeeArr[i].Name << " |"
						<< setw(15) << EmployeeArr[i].post << " |"
						<< setw(25) << EmployeeArr[i].expStr << " |" << endl;
			numOfResult++;
		}
	}
	if (numOfResult == 0)
		cout << "По вашему запросу ничего не найдено" << endl;
	else
	cout << "|" << setfill('_') << setw(length) << "" << setfill(' ') << "|" << endl;
	system("pause");
}

vector <User> UserArr;
vector <Employee> EmployeeArr;

void menuMain()
{
	string mainMenu[] = { "\tГлавное меню",
		"Зарегистрироваться",
		"Войти",
		"Завершить работу" };
	char choice = 0;
	int activeMenu = 1;
	bool end = 0;
	while (!end)
	{
		int x = 50, y = 12;
		GoToXY(x, 10);
		for (int i = 0; i < size(mainMenu); i++)
		{
			if (i == activeMenu) 
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN| FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			
			cout << mainMenu[i];
			GoToXY(x, y++);
		}
		SetConsoleTextAttribute(hStdOut, 0x0007);
		choice = _getch();
		if (choice == -32) 
			choice = _getch();
		switch (choice)
		{
			case DOWN:
				if(activeMenu<size(mainMenu)-1)
					activeMenu++;
				break;
			case UP:
				if(activeMenu>1)
					activeMenu--;
				break;
			case ENTER:
				switch (activeMenu)
				{
				case 1:
					system("cls");
					registration();
					break;
				case 2:
				{
					system("cls");
					int n = authorization();
					if (n != -1)
					{
						if (UserArr[n].isAdmin == 1)
							menuAdmin(n);
						else
							menuUser(n);
					}
					break;
				}
				case 3:
					end++;
					break;
				}
		}
	}
}
int main()
{
	SetConsoleTitle(L"Программа учёта стажа сотрудников предприятия");
	ConsoleCursorVisible(false, 100);
	overwritingUsersFromFileToVector();
	overwritingEmployeesFromFileToVector();
	for (int i = 0; i < EmployeeArr.size(); i++)
		countExperience(i);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	menuMain();
	overwritingUsersFromVectorToFile();
	overwritingEmployeesFromFVectorToFile();
	GoToXY(0, 25);
}