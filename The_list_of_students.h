#ifndef THE_LIST_OF_STUDENTS
#define THE_LIST_OF_STUDENTS

#include <vector>  // ��� std::vector
#include <memory>  // ��� ������ � ������ �����������
#include <utility> // ��� �������� ������ ��������� ��� r-value
#include <algorithm> // ��� ������������� ���������� ����������
#include "Student_data.h"

using std::vector;

// �����-��������� ��� ��������� ������ � ���������
class The_list_of_students
{
private:
	vector<std::unique_ptr<Student_data>> students; // ������ �� ����� ���������� �� �����
	unsigned number_of_students;
public:
	// ����������� ������
	The_list_of_students() : students{}, number_of_students()
	{}

	// ����� ��� ������� ���������� ���������
	void set_number(const int some_number)
	{
		if (some_number < 0) cout << "�� ������� ������ ���������� ���������" << '\n';
		else number_of_students = some_number;
	}

	// ���������� ������ � ��� ����� �������� ����� ����� ���������
	void add_student(std::unique_ptr<Student_data> student)
	{
		students.push_back(std::move(student));
		if (number_of_students < students.size())
			number_of_students = students.size();
	}

	// ���������� ��������� ������� �� �������� ����� �� �������� � ��������
	void sort_by_average()
	{
		// ���������� ������ ������� ������� (����� ����������, �� ��� ����� ������������ � ���� �������, ����� �� �� ���� ��������)
		for (unsigned startIndex = 0; startIndex < (number_of_students - 1); ++startIndex)
		{
			// � ���������� maximumIndex �������� ������ ����������� ��������, ������� �� ����� � ���� ��������
			// �������� � ����, ��� ���������� ������� � ���� �������� - ��� ������ ������� (������ 0)
			int maximumIndex = startIndex;

			// ����� ���� ������� �������� � ��������� ����� �������
			for (unsigned currentIndex = startIndex + 1; currentIndex < number_of_students; ++currentIndex)
			{
				if (students.at(currentIndex)->average_score_ > students.at(maximumIndex)->average_score_)
					maximumIndex = currentIndex;
			} // maximumIndex ������ ������ �������� � ���������� ������� ������ 

			// ������ ������� ���� ��������� ���������� ����� � ���, ������� �� ����������
			std::swap(students[startIndex], students[maximumIndex]);
		}
	}

	// ������ ���� ��������� �������
	void print()
	{
		cout << '\n';
		if (students.size() == 0) cout << "������ ��������� ����!" << '\n';
		else for (unsigned i = 0; i < students.size(); i++)
			cout << *students[i];
	}
};

#endif