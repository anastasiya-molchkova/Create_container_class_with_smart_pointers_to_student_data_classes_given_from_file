#ifndef STUDENT_DATA
#define STUDENT_DATA

#include <iostream>
#include <string>  // для работы со строками

using std::cout; using std::string;

// структура полное имя - ФИО
struct Full_name
{
	string surname_;
	string name_;
	string patronymic_;
	// Full_name() {}
	Full_name(string surname, string name, string patronymic) :
		surname_(surname), name_(name), patronymic_(patronymic)
	{}
};

// класс данных о студенте - ФИО, оценки и средний балл
class Student_data
{
public:
	// перечисление возможных оценок
	enum marks { one = 1, bad, satisfactorily, good, excellent };

	// чтобы не создавать геттеры, делаю все данные публичными:
	Full_name full_name_;
	marks math_;
	marks physics_;
	marks info_technology_;
	double average_score_;

	// конструктор класса
	Student_data(const string& surname, const string& name, const string& patronymic, const marks first_mark, const marks second_mark, const marks third_mark) :
		full_name_(Full_name(surname, name, patronymic)), math_(first_mark), physics_(second_mark), info_technology_(third_mark),
		average_score_(static_cast<double>(first_mark + second_mark + third_mark) / 3)
	{}

	// перегрузка оператора вывода данных студента
	friend std::ostream& operator<<(std::ostream& out, const Student_data& student)
	{
		out << student.full_name_.surname_ << " " << student.full_name_.name_ << " " << student.full_name_.patronymic_
			<< " " << student.math_ << " " << student.physics_ << " " << student.info_technology_ << '\n';
		return out;
	}
};

#endif