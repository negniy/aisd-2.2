#include "stdio.h"
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;


struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

void revers_vector(vector<int>& v, int size) {
	for (int i = 0; i < size / 2; i++) {
		int tmp = v[i];
		v[i] = v[(size - 1) - i];
		v[(size - 1) - i] = tmp;
	}
}

stats comb_sort(vector<int>& v, int size) {
	stats s;

	double fakt = 1.2473309; // ������ ����������
	int step = size - 1;

	while (step >= 1)
	{
		for (int i = 0; i + step < size; ++i)
		{
			if (v[i] > v[i + step])
			{
				swap(v[i], v[i + step]);
				s.copy_count++;
			}
			s.comparison_count++;
		}
		step = step / fakt;
	}
	// ���������� ���������
	for (int i = 0; i < size - 1; i++)
	{
		bool swapped = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (v[j] > v[j + 1]) {
				swap(v[j], v[j + 1]);
				swapped = true;
				s.copy_count++;
			}
			s.comparison_count++;
		}

		if (!swapped)
			break;
	}
	return s;

}

stats selection_sort(vector<int>& v, int size) {
	stats s;
	for (int i = 0; i < size-1; i++) {
		int i_min = i;
		for (int j = i+1; j < size; j++) {
			if (v[j] < v[i_min]) i_min = j;
			s.comparison_count++;
		}
		s.copy_count++;
		int tmp = v[i_min];
		v[i_min] = v[i];
		v[i] = tmp;
	}
	return s;
};

stats shaker_sort(vector<int>& v, int size) {
	stats s;
	bool sort_or_not = true;
	int right = size - 1;
	int left = 0;
	do {
		sort_or_not = true;
		for (int i = left; i < right; i++) {
			if (v[i] > v[i+1]) {
				int tmp = v[i];
				v[i] = v[i+1];
				v[i+1] = tmp;
				s.copy_count++;
				sort_or_not = false;
			}
			s.comparison_count++;
		}
		right--;
		for (int i = right; i > left; i--) {
			if (v[i] < v[i - 1]) {
				int tmp = v[i];
				v[i] = v[i - 1];
				v[i - 1] = tmp;
				s.copy_count++;
				sort_or_not = false;
			}
			s.comparison_count++;
		}
		left++;
	} while (sort_or_not == false);
	return s;
}

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
};

void random_v(int n) {

	vector<int> v;
	stats sum_sel;
	stats sum_sh;
	stats sum_c;

	for (int a = 0; a < 100; a++) {

		for (int i = 0; i < n; i++) {
			int key = int(lcg());
			v.push_back(key);
		}

		/*for (int i = 0; i < n; i++) {
			cout << v[i] << endl;
		}*/

		//cout << "//////////////////////////"<< endl;
		
		stats s1 = selection_sort(v, n);
		
		/*for (int i = 0; i < n; i++) {
			cout<< v[i]<< endl;
		}*/
		
		sum_sel.comparison_count += s1.comparison_count;
		sum_sel.copy_count += s1.copy_count;
		v.clear();
	}

	cout << "���-�� ��������� � ���������� �������: " << sum_sel.comparison_count/100 << " ���-�� ����������� � ���������� �������: " << sum_sel.copy_count/100 << endl;
	
	for (int a = 0; a < 100; a++) {
		
		for (int i = 0; i < n; i++) {
			int key = int(lcg());
			v.push_back(key);
		}
		
		stats s2 = shaker_sort(v, n);
		sum_sh.comparison_count += s2.comparison_count;
		sum_sh.copy_count += s2.copy_count;
		v.clear();
	}

	cout << "���-�� ��������� � ���������� ��������: " << sum_sh.comparison_count/100 << " ���-�� ����������� � ���������� ��������: " << sum_sh.copy_count/100 << endl;

	for (int a = 0; a < 100; a++) {

		for (int i = 0; i < n; i++) {
			int key = int(lcg());
			v.push_back(key);
		}
		/*for (int i = 0; i < n; i++) {
			cout << v[i] << endl;
		}*/

		//cout << "//////////////////////////"<< endl;
		stats s3 = comb_sort(v, n);

		/*for (int i = 0; i < n; i++) {
			cout<< v[i]<< endl;
		}*/

		sum_c.comparison_count += s3.comparison_count;
		sum_c.copy_count += s3.copy_count;
		v.clear();
	}

	cout << "���-�� ��������� � ���������� ���������: " << sum_c.comparison_count / 100 << " ���-�� ����������� � ���������� ���������: " << sum_c.copy_count / 100 << endl;
}

void sorted_v(int n) {

	vector<int> v;
	stats sel;
	stats sh;
	stats c;

	for (int i = 0; i < n; i++) {
		int key = int(lcg());
		v.push_back(key);
	}

	/*for (int i = 0; i < n; i++) {
		cout << v[i] << endl;
	}

	cout << "//////////////////////////"<< endl;
	*/
	selection_sort(v, n);
	/*
	for (int i = 0; i < n; i++) {
		cout<< v[i]<< endl;
	}
	*/
	sel = selection_sort(v, n);
	sh = shaker_sort(v, n);
	c = comb_sort(v, n);

	cout << "���-�� ��������� � ���������� �������: " << sel.comparison_count << " ���-�� ����������� � ���������� �������: " << sel.copy_count << endl;
	cout << "���-�� ��������� � ���������� ��������: " << sh.comparison_count << " ���-�� ����������� � ���������� ��������: " << sh.copy_count << endl;
	cout << "���-�� ��������� � ���������� ���������: " << c.comparison_count  << " ���-�� ����������� � ���������� ���������: " << c.copy_count << endl;
}

void rev_sorted_v(int n) {

	vector<int> v;
	stats sel;
	stats sh;
	stats c;

	for (int i = 0; i < n; i++) {
		int key = int(lcg());
		v.push_back(key);
	}
	/*
	for (int i = 0; i < n; i++) {
		cout << v[i] << endl;
	}

	cout << "//////////////////////////"<< endl;
	*/
	stats s1 = selection_sort(v, n);
	/*
	for (int i = 0; i < n; i++) {
		cout<< v[i]<< endl;
	}
	*/
	revers_vector(v, n);
	/*
	cout << "//////////////////////////" << endl;
	for (int i = 0; i < n; i++) {
		cout<< v[i]<< endl;
	}
	*/
	sel = selection_sort(v, n);

	revers_vector(v, n);
	sh = shaker_sort(v, n);

	revers_vector(v, n);
	c = comb_sort(v, n);

	cout << "���-�� ��������� � ���������� �������: " << sel.comparison_count << " ���-�� ����������� � ���������� �������: " << sel.copy_count << endl;
	cout << "���-�� ��������� � ���������� ��������: " << sh.comparison_count << " ���-�� ����������� � ���������� ��������: " << sh.copy_count << endl;
	cout << "���-�� ��������� � ���������� ���������: " << c.comparison_count << " ���-�� ����������� � ���������� ���������: " << c.copy_count << endl;
}

void time_of_selection() {
	int n = 100;

	for (int i = 0; i < 8; i++) {

		float times = 0;

		for (int j = 0; j < 100; j++) {

			vector<int> v;

			for (int k = 0; k < n; k++) {
				int key = int(lcg());
				v.push_back(key);
			}

			auto start = chrono::high_resolution_clock::now();
			shaker_sort(v, n);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<float> time = end - start;
			times += time.count();

			v.clear();
		}

		cout << "���-�� ��-��� ������� � ���������� ��������: " << n << " ����� ����������: " << times / 100 << endl;
		n = n * 2;
	}

}

void time_of_shaker() {

	int n = 100;

	for (int i = 0; i < 8; i++) {

		float times = 0;

		for (int j = 0; j < 100; j++) {

			vector<int> v;

			for (int k = 0; k < n; k++) {
				int key = int(lcg());
				v.push_back(key);
			}

			auto start = chrono::high_resolution_clock::now();
			selection_sort(v, n);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<float> time = end - start;
			times += time.count();

			v.clear();
		}

		cout << "���-�� ��-��� ������� � ���������� ��������: " << n << " ����� ����������: " << times / 100 << endl;
		n = n * 2;
	}

}

void time_of_comb() {
	int n = 100;

	for (int i = 0; i < 8; i++) {

		float times = 0;

		for (int j = 0; j < 100; j++) {

			vector<int> v;

			for (int k = 0; k < n; k++) {
				int key = int(lcg());
				v.push_back(key);
			}

			auto start = chrono::high_resolution_clock::now();
			comb_sort(v, n);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<float> time = end - start;
			times += time.count();

			v.clear();
		}

		cout << "���-�� ��-��� ������� � ���������� ���������: " << n << " ����� ����������: " << times / 100 << endl;
		n = n * 2;
	}

}

void time_of_sort() {
	while (true) {

		system("cls");
		std::cout << "����:\n";
		std::cout << "[1] - ����� ���������� �������\n";
		std::cout << "[2] - ����� ���������� ��������\n";
		std::cout << "[3] - ����� ���������� ���������\n";
		std::cout << "[ESC] - �����\n";
		int m = get_key();

		switch (m)
		{
		case 49:
			time_of_selection();
			get_key();
			break;
		case 50:
			time_of_shaker();
			get_key();
			break;
		case 51:
			time_of_comb();
			get_key();
			break;
		case 27:
			return;
			break;
		}
	}
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");

	int n = 10000;

	while (true) {

		system("cls");
		std::cout << "����:\n";
		std::cout << "[1] - ���������� �������� ���������������� �������\n";
		std::cout << "[2] - ���������� ���������������� �������\n";
		std::cout << "[3] - ���������� ������� ���������������� �������\n";
		std::cout << "[4] - ����� ����������\n";
		std::cout << "[ESC] - �����\n";

		int m = get_key();

		switch (m)
		{
		case 49:
			random_v(n);
			get_key();
			break;
		case 50:
			sorted_v(n);
			get_key();
			break;
		case 51:
			rev_sorted_v(n);
			get_key();
			break;
		case 52:
			time_of_sort(); 
			get_key();
			break;
		case 27:
			return 0;
			break;
		}
	}
}
