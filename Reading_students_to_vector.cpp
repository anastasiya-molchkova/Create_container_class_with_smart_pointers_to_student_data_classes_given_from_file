/* Напишите программу учёта оценок студентов. Для этого создайте текстовый файл с именем input_data.txt,
содержащий список из 10 студентов и их оценки по трём предметам: математике, физике, информатике.
Содержимое файла:
   в первой строке находится общее количество студентов;
   в каждой последующей строке находится ФИО студента и три целых числа (оценки);
   данные в строке разделены пробелами, а оценки варьируются в диапазоне от 1 до 5.
Затем создайте класс, с помощью которого вы будете считывать данные с файла.
На экран выведите ФИО студентов с оценками в порядке убывания их среднего бала. */

#include "The_list_of_students.h"
#include <fstream> // для работы с файлами
#include <cstdlib> // для exit
#include <sstream> // для работы со строковым потоком, чтобы превращать данные из строки в нужные данные разного типа

// ОБЪЯВЛЕНИЕ вспомогательных фукций для чтения из файла:
bool line_is_ok(const string&);
std::unique_ptr<Student_data> convert_string_to_smart_pointer(const string&);
unsigned short get_number_of_students_from_file(const string&);

// заполняем передаваемый массив данных о студентах данными из файла
void fill_from_file(The_list_of_students& array)
{
	std::ifstream data_file("input_data.txt");
	if (!data_file)
	{
		std::cerr << "Файл невозможно прочитать!" << '\n';
		exit(1);
	}

	// считываем количество строк в файле
	string number_from_file;
	getline(data_file, number_from_file);
	unsigned short n_students = get_number_of_students_from_file(number_from_file);
	array.set_number(n_students);

	unsigned short lines_index = 0;
	while (lines_index < n_students)  // читаем только обозначенное в файле количество строк, остальные не читаем
	{
		string line_from_file;
		getline(data_file, line_from_file);
		if (line_is_ok(line_from_file))
		{
			auto student_ptr = convert_string_to_smart_pointer(line_from_file);
			array.add_student(std::move(student_ptr));
		}
		else cout << "В файле есть некорректная строка" << '\n';
		++lines_index;
	}
}

int main()
{
	setlocale(LC_CTYPE, "rus");   // для вывода сообщений на кириллице

	The_list_of_students Students{};
	fill_from_file(Students);
	Students.sort_by_average();
	cout << "ФИО студентов с оценками в порядке убывания их среднего балла:";
	Students.print();

	return 0;
}

// РЕАЛИЗАЦИЯ вспомогательных функций для чтения из файла:

// функция возвращает истину, если строка соответствует ожидаемому формату "Ф И О ц1 ц1 ц3" и ложь, если не соответствует
bool line_is_ok(const string& line_from_file)
{
	if (line_from_file.length() < 10) return false; //т.к. строка должна иметь вид "Ф И О ц1 ц1 ц3" - как минимум 11 символов
	unsigned short spaces_counter = 0; // счётчик пробелов
	unsigned short index = 0;          // индекс символов строки

	while ((index < line_from_file.size()) && (spaces_counter < 6))
		// 1ый пробел - окончание фамилии, 2ой- окончание имени, 3ий - отчества, потом через пробел идут три оценки
	{
		if (isspace(line_from_file[index]))
			spaces_counter++;
		else
		{
			if ((spaces_counter < 3) && (!isalpha(line_from_file[index]))) return false;
			if ((spaces_counter >= 3) && (!isdigit(line_from_file[index]))) return false;
		}
		index++;
	}
	if (index < line_from_file.size()) return false; // если было 6 и более пробелов до конца строки
	else return true;
}

// функция превращает строку в правильном формате в умный указатель на класс с данными о студенте
std::unique_ptr<Student_data> convert_string_to_smart_pointer(const string& correct_string)
{
	std::stringstream string_from_file;
	string_from_file << correct_string;

	string surname, name, patronymic;
	string_from_file >> surname;
	string_from_file >> name;
	string_from_file >> patronymic;

	unsigned short math(0), physics(0), it(0);
	string_from_file >> math;
	string_from_file >> physics;
	string_from_file >> it;

	return std::make_unique<Student_data>(surname, name, patronymic, static_cast<Student_data::marks>(math), static_cast<Student_data::marks>(physics), static_cast<Student_data::marks>(it));
}

// считываем количество строк в файле
unsigned short get_number_of_students_from_file(const string& number_from_file)
{
	std::stringstream number;
	number << number_from_file;
	unsigned short n(0);
	number >> n;
	return n;
}