#include <iostream>
#include <ctime>
#include <fstream>
#include <Windows.h>

void Rez();

using namespace std;

const int a = 500; // a - размер всех символьных массивов в коде

// int64_t - большое число на 8 байт вместо 4

struct People
{
	char people[a];//ФИО - char[] массив символов
	int64_t number;//номер телефона
	char conn[a];//дата
	char disconn[a];//дата
	int64_t percent;//задолжность
	int64_t credite;//кредит
}People[10]{};

struct Services
{
	char service[a];//название
	int64_t code;
	int64_t cost;//тариф
	char data[a];//интервал
} Services[10]{};

struct PeopleService
{
	int64_t phone;//номер телефона
	int64_t Pcode;//код
	int64_t Pday;//день
	int64_t Pmonth;//месяц
	int64_t Pyear;//год
	char Ptime[a];//время
	int64_t Punit;//время использования
}PeopleServices[10]{};

int main()
{

	SetConsoleCP(1251); // Подключение русского языка
	SetConsoleOutputCP(1251); // Подключение русского языка


	FILE* file_1; // FILE* тип данных для указания на файл
	if (fopen_s(&file_1, "People.txt", "r") == 0) { // Если удалось открыть файл
		for (int i = 0; i < 10; i++) {
			fscanf_s(
				file_1,
				// %500[^,] - Прочитать как строку максимум 500 символов до ,
				// %d - Прочитать целое число
				"%500[^,], %d, %500[^,], %500[^,], %d, %d \n",
				People[i].people, a,
				&People[i].number,
				People[i].conn, a,
				People[i].disconn, a,
				&People[i].percent,
				&People[i].credite
			);
		}
		fclose(file_1);
	}
	// Если не удалось открыть файл
	else {
		cout << "Список клиентов пуст!" << endl;
		return -1;
	}
	FILE* file_3;
	if (fopen_s(&file_3, "PeopleServices.txt", "r") == 0) {
		for (int i = 0; i < 10; i++) {
			fscanf_s(
				file_3,
				"%d, %d, %d.%d.%d %500[^,], %d \n",
				&PeopleServices[i].phone,
				&PeopleServices[i].Pcode,
				&PeopleServices[i].Pday,
				&PeopleServices[i].Pmonth,
				&PeopleServices[i].Pyear,
				PeopleServices[i].Ptime, a,
				&PeopleServices[i].Punit
			);
		}
		fclose(file_3);
	}
	else {
		cout << "Нет используемых услуг!" << endl;
		return -2;
	}
	FILE* file_4;
	if (fopen_s(&file_4, "Services.txt", "r") == 0) {
		for (int i = 0; i < 10; i++) {
			fscanf_s(file_4,
				"%500[^,], %d, %d, %500[^\n] \n",
				Services[i].service, a,
				&Services[i].code,
				&Services[i].cost,
				Services[i].data, a
			);
		}
		fclose(file_4);
	}
	else {
		cout << "Нет услуг!" << endl;
		return -3;
	}
	Rez(); // Вызывает выполнение функции Rez
	return 0;
}

void Rez()
{
	ifstream param("Param.txt");
	int64_t duty;
	param >> duty;
	param.close();

	time_t t = time(0) - 60 * 60 * 24 * 30;
	tm tr;
	localtime_s(&tr, &t);

	ofstream fout("Report.txt");

	// Прохождение по списку клиентов
	for (int i = 0; i < 10; i++) {
		if (People[i].percent <= duty) {
			bool t = false;
			// Прохождение по списку использованных услуг
			for (int j = 0; j < 10; j++) {
				if (
					PeopleServices[j].phone == People[i].number &&
					PeopleServices[j].Pyear == tr.tm_year + 1900 &&
					PeopleServices[j].Pmonth == tr.tm_mon + 1
					) {
					t = true;
					break;
				}
			}
			if (!t) {
				fout << People[i].people << '\n';
			}
		}
	}
	fout.close();
}