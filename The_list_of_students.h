#ifndef THE_LIST_OF_STUDENTS
#define THE_LIST_OF_STUDENTS

#include <vector>  // для std::vector
#include <memory>  // для работы с умными указателями
#include <utility> // для передачи умного указателя как r-value
#include <algorithm> // для использования алгоритмов сортировки
#include "Student_data.h"

using std::vector;

// класс-контейнер для обработки данных о студентах
class The_list_of_students
{
private:
	vector<std::unique_ptr<Student_data>> students; // вектор из умных указателей на класс
	unsigned number_of_students;
public:
	// конструктор класса
	The_list_of_students() : students{}, number_of_students()
	{}

	// метод для задания количества студентов
	void set_number(const int some_number)
	{
		if (some_number < 0) cout << "Не удалось задать количество студентов" << '\n';
		else number_of_students = some_number;
	}

	// добавление данных о ещё одном студенте через умный указатель
	void add_student(std::unique_ptr<Student_data> student)
	{
		students.push_back(std::move(student));
		if (number_of_students < students.size())
			number_of_students = students.size();
	}

	// сортировка элементов вектора по среднему баллу от большего к меньшему
	void sort_by_average()
	{
		// Перебираем каждый элемент массива (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберёмся)
		for (unsigned startIndex = 0; startIndex < (number_of_students - 1); ++startIndex)
		{
			// В переменной maximumIndex хранится индекс наибольшего значения, которое мы нашли в этой итерации
			// Начинаем с того, что наибольший элемент в этой итерации - это первый элемент (индекс 0)
			int maximumIndex = startIndex;

			// Затем ищем элемент поменьше в остальной части массива
			for (unsigned currentIndex = startIndex + 1; currentIndex < number_of_students; ++currentIndex)
			{
				if (students.at(currentIndex)->average_score_ > students.at(maximumIndex)->average_score_)
					maximumIndex = currentIndex;
			} // maximumIndex теперь индекс студента с наибольшим средним баллом 

			// Меняем местами наше начальное наибольшее число с тем, которое мы обнаружили
			std::swap(students[startIndex], students[maximumIndex]);
		}
	}

	// печать всех элементов массива
	void print()
	{
		cout << '\n';
		if (students.size() == 0) cout << "Список студентов пуст!" << '\n';
		else for (unsigned i = 0; i < students.size(); i++)
			cout << *students[i];
	}
};

#endif