#pragma once
#include <iostream>
#include <vector>

#include "lab1_h1.h"
#include "lab1_h3.h"
/*
10. (***) Інформація про книги(назва, автор(и), дата виходу, кількість сторінок, коротка анотація) +
	та персонажів книг(список імен / псевдонімів, в яких книгах згадується, для кожної книги рівень участі – головний, чи другорядний, чи епізодичний персонаж).+

	Розбиття книг на серії(дві книги належать до однієї серії, якщо у них є	спільний головний чи другорядний персонаж; +
	в рамках серії книги впорядковано за датою виходу). +
		//a. + *за реалізацію «бази даних» - з можливістю +
		//додавати +
		//редагувати +
		//видаляти +
		//шукати книги +
		//шукати авторів +
		аналогічно лабораторній роботі №1 з минулого семестру)
	b. + *за підтримку «альтернативних реальностей» - наприклад, +
	канонічні серії книг, книги на основі фільмів, неофіційні книги, +
	…
	*/

	//СВЯЗЬ СО СПИСКОМ 1
/*
	С помощи функции creation_sparse_matrix строим СПИСОК 1 (MatrixElement_List) по принципу: Если данный персонаж упоминается в даной книге,
	то записываем в MatrixElement (i, j, 1), где i - номер персонажа, j - id книги.
	В итоге получаем разреженную матрицу, которая связывает персонажей и книги.
	В дальнейшем можем с ней работать как с обычной разреженной матрицей
*/

class Date
{
public:
	size_t number, month, year;
};

class Book
{
public:
	size_t id;
	char name[20];
	char writer[20];
	Date release_date; // дата выхода
	size_t number_of_pages; //количество страниц
	char short_abstract[30]; // короткая анотация
	size_t alternative_reality; // 1 - обычные книги, 2 - канонические книг, 3 - книги на основе фильмов 
	bool availability = 1;
};

class Element_List
{
public:
	char name[20];
	Book book; // книга, в которой вспоминается
	int level_of_participation; //1 - главный, 2 - второстепенный, 3 - эпизодический

	Element_List* next, * prev;
};

class List_Personage
{
public:
	Element_List* head = nullptr;
	Element_List* end = nullptr;

	void add(Book book, char name[20], int level_of_participation)
	{
		Element_List* element = new Element_List;
		element->book = book;
		for (size_t i = 0; i < 20; i++)
			element->name[i] = name[i];
		element->level_of_participation = level_of_participation;
		if (!head)
		{
			head = end = element;
		}
		else
		{
			element->next = head;
			head->prev = element;
			head = element;
		}
	}
};

class Personage
{
public:
	char person[10];
	int id_person = 0;
	List_Personage element;
};

class Element_Series
{
public:
	Book book; // книга, в которой вспоминается

	Element_Series* next, * prev;
};
class List_Series
{
public:

	Element_Series* head = nullptr;
	Element_Series* end = nullptr;

	void add(Book book)
	{
		Element_Series* element = new Element_Series;
		element->book = book;
		if (!head)
		{
			head = end = element;
		}
		else
		{
			element->next = head;
			head->prev = element;
			head = element;
		}
	}
};

bool check(Date dat1, Date dat2)
{//возращает 1, если dat1 > dat2
	if (dat1.year > dat2.year)
		return 1;
	else if (dat1.year == dat2.year)
	{
		if (dat1.month > dat2.month)
			return 1;
		else if (dat1.month == dat2.month)
		{
			if (dat1.number >= dat2.number)
				return 1;
		}
	}
	return 0;
}

void sorting(List_Series& series)
{
	Element_Series* element = series.end;

	Book book;

	while (element->prev)
	{
		Element_Series* e = element->prev;

		while (e)
		{
			if (check(element->book.release_date, e->book.release_date))
			{
				std::swap(element->book, e->book);
			}
			e = e->prev;
		}
		element = element->prev;
	}
}

bool this_book_in_the_series(Book book, List_Series series) //функция проверяет, имеется ли данная книга в серии
{
	Element_Series* element = series.end;
	while (element)
	{
		if (book.id == element->book.id)
			return 1;
		element = element->prev;
	}
	return 0;
}

void add_to_series(List_Series& series, List_Personage characters)
{
	Element_List* element = new Element_List;
	element = characters.end;
	while (element)
	{
		if (!this_book_in_the_series(element->book, series) && element->level_of_participation != 3)
			series.add(element->book);
		element = element->prev;
	}
}
// Создает серии книг по такому принцыпу: если у книги 1 есть герой А, у книги 2 есть герой Б, у книги 3 есть герои А и Б, то все три книги пренадлежат одной серии 
std::vector<List_Series> creation_series(List_Personage* characters, int n)
{
	std::vector<List_Series> myVector;

	bool* a = new bool[n]; //вспомогательный масив, який поможет определить, какие герои уже лежат в сериях, а какие свободны
	for (size_t i = 0; i < n; i++)
		a[i] = 0;
	bool b = 0;
	for (size_t count = 0; count < n; count++)
	{
		for (size_t k = 0; k < n; k++)
			if (!a[k]) //если есть хотя бы один свободный герой - то создаем еще одну серию
			{
				List_Series series;
				myVector.push_back(series);
				b = 1;
				break;
			}
		for (size_t i = 0; i < n; i++) //итерируемся только по неиспользованным героям
		{
			if (!a[i])
			{
				Element_List* element = new Element_List;
				element = characters[i].end;
				while (element)
				{
					if (b || (element->level_of_participation != 3 && this_book_in_the_series(element->book, myVector[count])))
						// если серия была только создана - то она пуста (b == 1), вносим в ней все книги, в которых упоминался неиспользованный герой 
						// или же если из книг серии есть книги, в которых помимо этого героя есть еще другие, 
						// то вносим в серию все книги, в которых упоминались эти другие герои
					{
						add_to_series(myVector[count], characters[i]);
						a[i] = true; // помечаем i-го героя использованным
						break;
					}
					element = element->prev;
				}
				b = 0;
			}
		}
	}
	//вдруг персонаж принимал участие только в одной книге и играл там эпизодическую роль, тогда мы создали пустую серию, её нужно удалить
	for (size_t count = 0; count < myVector.size(); count++)
	{
		if (myVector[count].end == nullptr)
		{
			myVector.erase(myVector.begin() + count);
			count--;
		}
	}

	for (size_t i = 0; i < myVector.size(); i++)
		sorting(myVector[i]);

	return myVector; //возращаем вектор серий
}

bool b_mas(char* mas1, char* mas2, int n)
{
	for (int i = 0; i < n; i++)
		if (mas1[i] != mas2[i])
			return 0;
	return 1;
}

bool b_library(Book& str) //проверяет наличие книги в библиотеке
{
	FILE* library;
	if (fopen_s(&library, "library", "rb"))
		perror("Error");
	else
	{
		Book str2;
		while (!feof(library))
		{
			fread(&str2, sizeof(Book), 1, library);

			if (b_mas(str.name, str2.name, std::size(str.name)) && b_mas(str.writer, str2.writer, std::size(str.writer) && str2.availability))
			{
				str = str2;
				fclose(library);
				return 1;
			}
		}
	}
	fclose(library);
	return 0;
}

void book_registration()
{
	using namespace std;
	Book registration;

	cout << "Введите название книги: ";
	cin >> registration.name;
	cout << "Введите автора: ";
	cin >> registration.writer;
	cout << "(пример ввода даты: 10 12 2012)" << endl << "Введите дату выхода: ";
	cin >> registration.release_date.number;
	cin >> registration.release_date.month;
	cin >> registration.release_date.year;

	cout << "Введите количество страниц в книге: ";
	cin >> registration.number_of_pages;
	cout << "Введите короткую анотацию: ";
	std::cin.ignore(256, '\n');
	cin.getline(registration.short_abstract, 30);

	cout << "(1 - обычная, 2 - каноническая, 3 - на основе фильмов)" << endl << "Введите альтернативную реальность книги: " << endl;
	cin >> registration.alternative_reality;

	if (!b_library(registration))
	{
		FILE* library1;
		if (fopen_s(&library1, "library", "rb"))
			perror("Error");
		else
		{
			Book str1;
			str1.id = 0;
			while (!feof(library1))
			{
				fread(&str1, sizeof(Book), 1, library1);
				if (feof(library1))
					break;
			}
			registration.id = str1.id + 1;
			cout << "ID: " << registration.id << endl;
			fclose(library1);
		}
		FILE* library2;
		if (fopen_s(&library2, "library", "a+b"))
			perror("Error");
		else
			fwrite(&registration, sizeof(Book), 1, library2);
		fclose(library2);
	}
	else
		out_BLUE_RED("Такая книга уже записана");
}


void edit_file(Book& b_ch) //редактируем информацию о книге в файле
{
	FILE* library;

	if (fopen_s(&library, "library", "rb+"))
		perror("Error");
	else
	{
		fseek(library, sizeof(Book) * (b_ch.id - 1), SEEK_SET);
		fwrite(&b_ch, sizeof(Book), 1, library);
	}
	fclose(library);
}

bool book_search_id(Book& str)
{
	using std::cout;
	using std::endl;
	FILE* library;
	bool b = 0;
	if (fopen_s(&library, "library", "rb"))
		perror("Error");
	else
	{
		Book str2;
		while (!feof(library))
		{
			fread(&str2, sizeof(Book), 1, library);
			if (str.id == str2.id && str2.availability)
			{
				str = str2;
				cout << endl << "ID: " << str2.id << endl << "Название книги: " << str2.name << endl << "Автор: " << str2.writer << endl
					<< "Дата выхода: " << str2.release_date.number << ' ' << str2.release_date.month << ' ' << str2.release_date.year << endl << "Количество страниц в книге: " << str2.number_of_pages << endl
					<< "Краткая аннотация: " << str2.short_abstract << endl << "Альтернативная реальность книги: " << str2.alternative_reality << endl;
				b = 1;
				fclose(library);
				return 1;
			}
		}
		if (!b)
			out_BLUE_RED("Такой книги нет в наличии");
	}
	fclose(library);
	return 0;
}

std::vector<Book> book_search_nameORwriter(Book& str, int a)
//а = 1 - поиск по названию
//а = 2 - поиск по автору
{
	using std::cout;
	using std::endl;
	std::vector<Book> MyVector;

	FILE* library;
	bool b = 0;
	if (fopen_s(&library, "library", "rb"))
		perror("Error");
	else
	{
		Book str2;
		while (!feof(library))
		{
			fread(&str2, sizeof(Book), 1, library);
			if ((a == 1 && b_mas(str.name, str2.name, std::size(str.name)) || a == 2 && b_mas(str.writer, str2.writer, std::size(str.writer)))
				&& str2.availability)
			{
				cout << endl << "ID: " << str2.id << endl << "Название книги: " << str2.name << endl << "Автор: " << str2.writer << endl
					<< "Дата выхода: " << str2.release_date.number << ' ' << str2.release_date.month << ' ' << str2.release_date.year << endl << "Количество страниц в книге: " << str2.number_of_pages << endl
					<< "Краткая аннотация: " << str2.short_abstract << endl << "Альтернативная реальность книги: " << str2.alternative_reality << endl;
				b = 1;
				MyVector.push_back(str2);
				break;
			}
		}
		if (!b)
			out_BLUE_RED("Такой книги нет в наличии");
		fclose(library);
	}
	return MyVector;
}

void menu()
{
	using std::cout;
	using std::endl;
	using std::cin;
	int k;
	while (1)
	{
		cout << endl << "1 - Посмотреть информацию о книге" << endl << "2 - Регистрация новой книги" << endl << "3 - Удаление книги" << endl
			<< "4 - Редактирование информации и книге" << endl
			<< "______________________" << endl << "Введите номер функции: ";
		cin >> k;
		Book b_ch;
		Book str;
		switch (k)
		{
		case 1:
			cout << "1 - По ID" << endl << "2 - По названию" << endl << "3 - По автору" << endl << "_____________" << endl;
			cout << "Введите номер функции: ";
			cin >> k;
			switch (k)
			{
			case 1:
				cout << "Введите ID книги: ";
				cin >> str.id;
				book_search_id(str);
				break;
			case 2:
				cout << "Введите название книги: ";
				cin >> str.name;
				book_search_nameORwriter(str, 1);
				break;
			case 3:
				cout << "Введите автора: ";
				cin >> str.writer;
				book_search_nameORwriter(str, 2);
				break;
			default:
				break;
			}
			break;
		case 2:
			book_registration();
			break;
		case 3:
			cout << "Введите ID книги: ";
			cin >> str.id;
			if (book_search_id(str))
			{
				str.availability = 0;
				edit_file(str);
			}
			if (!b_library(str) && !str.availability)
				out_GREEN("Книга успешно удалена");
			break;
		case 4:
			cout << "Введите ID книги: ";
			cin >> b_ch.id;
			if (book_search_id(b_ch))
			{
				cout << "Что хотите отредактировать?" << endl << "1 - Название" << endl << "2 - Автора" << endl << "3 - Количество страниц" << endl
					<< "4 - Дату выхода" << endl << "5 - Краткую аннотацию" << endl << "6 - Альтернативную реальность книги"
					<< "___________________________________" << endl;;
				//char a[100];
				//cin >> a;
				//b = input1_2_3(a);
				int b;
				cin >> b;
				switch (b)
				{
				case 1:
					cout << endl << "Введите новое название: " << endl;
					cin >> b_ch.name;
					break;
				case 2:
					cout << endl << "Введите нового автора: " << endl;
					cin >> b_ch.writer;
					break;
				case 3:
					cout << endl << "Введите новое количество страниц: " << endl;
					cin >> b_ch.number_of_pages;
					break;
				case 4:
					cout << endl << "(пример ввода даты: 10 12 2012)" << endl << "Введите новую дату выхода: " << endl;
					cin >> b_ch.release_date.number;
					cin >> b_ch.release_date.month;
					cin >> b_ch.release_date.year;
					break;
				case 5:
					cout << endl << "Введите новую короткую анатоцию: " << endl;
					cin >> b_ch.short_abstract;
					break;
				case 6:
					cout << endl << "(1 - обычная, 2 - каноническая, 3 - на основе фильмов)" << endl << "Введите новую альтернативную реальность: " << endl;
					cin >> b_ch.alternative_reality;
					break;
				default:
					out_RED("Номер функции введен не правильно!");
					break;
				}
				edit_file(b_ch);
				out_GREEN("Книга отредактирована");
				break;
			}
			else
				out_BLUE_RED("Такой книги нет в наличии!");
			break;
		default:
			break;
		}
		cout << endl << "Желаете продолжить работу с библиотекой?" << endl;
		cout << "1 - Да" << endl << "2 - Нет" << endl << "_______" << endl;
		cin >> k;
		if (k == 2)
			break;
	}
}

void print_all_books()
{
	using std::cout;
	using std::endl;
	FILE* library;
	if (fopen_s(&library, "library", "rb"))
		perror("Error");
	else
	{
		Book str2;
		while (!feof(library))
		{
			fread(&str2, sizeof(Book), 1, library);
			if (feof(library))
				break;
			//cout << "str1.availability: " << str1.availability << endl;
			if (str2.availability)
			{
				cout << endl << "ID: " << str2.id << endl << "Название книги: " << str2.name << endl << "Автор: " << str2.writer << endl
					<< "Дата выхода: " << str2.release_date.number << ' ' << str2.release_date.month << ' ' << str2.release_date.year << endl << "Количество страниц в книге: " << str2.number_of_pages << endl
					<< "Краткая аннотация: " << str2.short_abstract << endl << "Альтернативная реальность книги: " << str2.alternative_reality << endl;
				cout << endl << endl;
			}
		}
	}
	fclose(library);
}

MatrixElement_List* creation_sparse_matrix(List_Personage* person, int n)
{
	using std::cout;
	using std::endl;

	MatrixElement_List* horizontal = new MatrixElement_List[n];

	for (size_t i = 0; i < n; i++)
	{
		Element_List* element = person[i].end;

		while (element)
		{
			horizontal[i].add(i, element->book.id - 1, 1);
			element = element->prev;
		}
	}
	return horizontal;
}

Book* creating_an_array_of_books()
{
	int size = 0;
	FILE* library;
	if (fopen_s(&library, "library", "rb"))
		perror("Error");
	else
	{
		Book str;
		while (!feof(library))
		{
			fread(&str, sizeof(Book), 1, library);
			if (str.availability)
				size++;
			if (feof(library))
				break;
		}
	}
	fclose(library);

	Book* book = new Book[size];

	if (fopen_s(&library, "library", "rb"))
		perror("Error");
	else
	{
		size = 0;
		Book str;
		while (!feof(library))
		{
			fread(&str, sizeof(Book), 1, library);
			if (str.availability)
			{
				book[size] = str;
				size++;
			}
			if (feof(library))
				break;
		}
	}
	fclose(library);

	return book;
}

List_Personage* creation_character(Book* book, int n)
{
	using std::cout;
	using std::endl;
	int b;
	List_Personage* person = new List_Personage[n];

	int id;
	for (size_t i = 0; i < n; i++)
	{
		out_BLUE_RED("Регистрация персонажа");
		//std::cout << i + 1 << std::endl;

		while (1)
		{
			cout << "Введите id книги, в которой вспоминается герой: " << endl;
			std::cin >> id;
			cout << "Введите имя герой: " << endl;
			char name[20];
			std::cin >> name;
			cout << "(1 - главный, 2 - второстепенный, 3 - эпизодический)" << endl << "Введите уровень участия героя: " << endl;
			int level_of_participation;
			std::cin >> level_of_participation;

			person[i].add(book[id - 1], name, level_of_participation);

			cout << endl << "Есть еще книги, в которых вспоминается данный герой?" << endl;
			cout << "1 - Да" << endl << "2 - Нет" << endl << "_______" << endl;
			std::cin >> b;
			if (b == 2)
				break;
		}
	}
	return person;
}

void out_personage(List_Personage* person, int n)
{
	using std::cout;
	using std::endl;

	for (size_t i = 0; i < n; i++)
	{
		out_RED("Персонаж ");
		std::cout << i + 1 << std::endl;

		Element_List* element = person[i].end;
		while (element)
		{
			cout << "id книги: " << element->book.id << endl;
			cout << "Имя: " << element->name << endl;
			cout << "Уровень участия: " << element->level_of_participation << endl;

			element = element->prev;
		}
	}
}

void print_elements_of_the_character_matrix(MatrixElement_List* horizontal, int n)
{//вывод элементов
	for (int i = 0; i < n; i++)
	{
		MatrixElement* element = horizontal[i].end;
		while (element)
		{
			std::cout << "i = " << element->i << std::endl
				<< "j = " << element->j << std::endl
				<< "data = " << element->data << std::endl;
			element = element->prev;
		}
		std::cout << std::endl;
	}
}

std::vector<List_Series> support_for_alternative_realities(List_Personage* person, int n) //поддержка альтернативных реальностей
{
	size_t alternative_reality;
	std::cout << std::endl << "(1 - обычная, 2 - каноническая, 3 - на основе фильмов)" << std::endl <<
		"Введите альтернативную реальность, по которой хотите создавать серии: ";
	std::cin >> alternative_reality;

	List_Personage* person_2 = new List_Personage[n]; //создание копии персонажей с книгами только с даной альтернативной реальности 
	for (size_t i = 0; i < n; i++)
	{
		Element_List* element = person[i].end;
		while (element)
		{
			if (element->book.alternative_reality == alternative_reality)
				person_2[i].add(element->book, element->name, element->level_of_participation);

			element = element->prev;
		}
	}
	out_personage(person_2, n); //выводим всех персонажей в консоль

	std::vector<List_Series> series = creation_series(person_2, n);
	return series;
}

