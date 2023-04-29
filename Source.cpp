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

	for (int a = 0; a < 100; a++) {

		for (int i = 0; i < n; i++) {
			int key = int(lcg());
			v.push_back(key);
		}

		/*for (int i = 0; i < n; i++) {
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
		sum_sel.comparison_count += s1.comparison_count;
		sum_sel.copy_count += s1.copy_count;
		v.clear();
	}
	cout << "Кол-во сравнений в сортировке выбором: " << sum_sel.comparison_count/100 << " Кол-во копирований в сортировке выбором: " << sum_sel.copy_count/100 << endl;


	for (int a = 0; a < 100; a++) {

		for (int i = 0; i < n; i++) {
			int key = int(lcg());
			v.push_back(key);
		}

		/*for (int i = 0; i < n; i++) {
			cout << v[i] << endl;
		}

		cout << "//////////////////////////" << endl;
		*/
		stats s2 = shaker_sort(v, n);

		/*for (int i = 0; i < n; i++) {
			cout << v[i] << endl;
		}*/
		sum_sh.comparison_count += s2.comparison_count;
		sum_sh.copy_count += s2.copy_count;
		v.clear();
	}

	cout << "Кол-во сравнений в сортировке шейкером: " << sum_sh.comparison_count/100 << " Кол-во копирований в сортировке шейкером: " << sum_sh.copy_count/100 << endl;
}

void sorted_v(int n) {

}

void rev_sorted_v(int n) {

}

void time_of_sort(int n) {

}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");

	int n = 10;

	while (true) {

		system("cls");
		std::cout << "Меню:\n";
		std::cout << "[1] - Сортировка случайно сгенерированный массив\n";
		std::cout << "[2] - Сортировка отсортированный массив массив\n";
		std::cout << "[3] - Сортировка обратно отсортированный массив массив\n";
		std::cout << "[4] - Время сортировки\n";
		std::cout << "[ESC] - Выход\n";

		int m = get_key();

		switch (m)
		{
		case 49:
			random_v(n);
			get_key();
			break;
		case 50:
			sorted_v(n);
			break;
		case 51:
			rev_sorted_v(n);
			break;
		case 52:
			time_of_sort(n);
			break;
		case 27:
			return 0;
			break;
		}

	}
}
