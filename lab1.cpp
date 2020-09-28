//БУЛО РЕАЛІЗОВАНО дев'ять зірочок (9*)


#include "lab1_h1.h"
#include "lab1_h2.h"

void test1()
{
	CREATING_AND_FILLING_THE_FILE_WITH_MATRIX_ELEMENTS(); 	// СОЗДАНИЕ И ЗАПОЛНЕНИЕ ФАЙЛА ЭЛЕМЕНТАМИ МАТРИЦЫ

	MatrixElement_List horizontal_A[order];
	matrix_creation(horizontal_A, "A"); //заполняем матрицу А с файла и печатаем
	std::cout << std::endl << std::endl;

	search_by_index_method_main(horizontal_A); //поиск элемента по индексу, вызывает метод класса MatrixElement_List

	std::cout << std::endl;
	search_by_index_function_main(horizontal_A); //поиск элемента по индексу, вызывает функцию

	search_first_by_value_main(horizontal_A); 	//поиск первого элемента по значению

	search_all_by_value_main(horizontal_A); 	//поиск всех элементов по значению

	search_first_element_by_condition(horizontal_A); //поиск первого элемента по заданному условию


	MatrixElement_List horizontal_B[order];
	matrix_creation(horizontal_B, "B");		//заполняем матрицу В с файла и печатаем
	std::cout << std::endl << std::endl;

	matrix_sum_main(horizontal_A, horizontal_B); //сумма матриц

	matrix_multiplication_main(horizontal_A, horizontal_B); 	//умножение матриц

	matrix_transpose_main(horizontal_A);	//транспонирование матрицы А

	matrix_multiplication_by_vector_main(horizontal_A);	//умножение матрицы А на вектор

}

void test2()
{

	FILE* library;
	fopen_s(&library, "library", "a+b");
	fclose(library);

	menu();

	print_all_books();

	Book* book = creating_an_array_of_books(); //считываем с файла все книги

	int n, b;
	std::cout << "Введите количество персонажей: " << std::endl;
	std::cin >> n;

	List_Personage* person = creation_character(book, n); //создаем персонажей

	out_personage(person, n); //выводим всех персонажей в консоль

	std::cout << "Хотите создать серии с учетом альтернативной реальности книг?" << std::endl
		<< "1 - Да" << std::endl << "2 - Нет" << std::endl << "_______" << std::endl;
	int k;
	std::cin >> k;

	std::vector<List_Series> series;
	if (k == 1)
		series = support_for_alternative_realities(person, n);
	else
		series = creation_series(person, n);

	MatrixElement_List* horizontal = creation_sparse_matrix(person, n); // Создание матрицы, которое описано в строке 616
	//print_elements_of_the_character_matrix(horizontal, n);

	for (List_Series element : series)
	{
		std::cout << std::endl;
		out_RED("Серия");
		Element_Series* e = element.end;
		while (e)
		{
			std::cout << "ID книги: " << e->book.id << std::endl;
			std::cout << "Дата: " << e->book.release_date.number << ' ' << e->book.release_date.month << ' ' << e->book.release_date.year << std::endl;
			e = e->prev;
		}
	}

}


int main()
{
	setlocale(LC_ALL, "");

	test1();

	test2();
}
