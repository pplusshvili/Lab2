
#include <iostream>
#include <fstream>
using namespace std;

//Файлы отсутствуют
const char* Matr_A = "Matr_A_1.1.txt";
const char* Matr_B = "Matr_B_1.1.txt";
//Файлы пустые
//const char* Matr_A = "Matr_A_1.2.txt";
//const char* Matr_B = "Matr_B_1.2.txt";
//Встречен символ
//const char* Matr_A = "Matr_A_1.3.txt";
//const char* Matr_B = "Matr_B_1.3.txt";
//Размеры не совпадают
//const char* Matr_A = "Matr_A_1.4.txt";
//const char* Matr_B = "Matr_B_1.4.txt";
//Матрицы не квадратные
//const char* Matr_A = "Matr_A_1.5.txt";
//const char* Matr_B = "Matr_B_1.5.txt";
//Идеальные данные
//const char* Matr_A = "Matr_A_2.1.txt";
//const char* Matr_B = "Matr_B_2.1.txt";
//Некоторые строки отрицательные
//const char* Matr_A = "Matr_A_2.2.txt";
//const char* Matr_B = "Matr_B_2.2.txt";
//Строки с 0
//const char* Matr_A = "Matr_A_2.3.txt";
//const char* Matr_B = "Matr_B_2.3.txt";
//Строки с 0 и отрицательными элем
//const char* Matr_A = "Matr_A_2.4.txt";
//const char* Matr_B = "Matr_B_2.4.txt";

//*****************ПРОТОТИПЫ ФУНКЦИЙ**************************

//Проверка файла на ошибки
int Read_File(int ***Matr, const char* FNAME, int &	N, int &M);

//Вывод матрицы на экран
void Print_Matr(int ***Matr, const int N, const int M);

//Нахождение сумм под главной диагональю матрицы
void Sum_UN_diagonal(int ***Matr, const int N, const int M, int **Sum_M);

//Находление наименьшей суммы
void Less_Sum(int **Sum_M, const int N);     //вектор сумм

//Вывод ошибки
void Error_type(const int ErrCode, const char* FNAME);

//*************************************************************

//********************ОПИСАНИЕ ФУНКЦИЙ*************************

#include "functions.h"

int	 Read_File(int ***Matr, const char* FNAME, int &N, int &M) {
    int temp = 0;
    int Sum_Elements = 0;
    ifstream fin(FNAME);
    //Проверка существования файла
    if (!fin) {
        fin.close();
        return 1;
    }
    //Проверка файла на содержание
    if (fin.peek()==EOF) {
        fin.close();
        return 2;
    }
    while (!fin.eof()) { //проверка содержание файла
        fin >> temp;
        if (fin.fail()) {
            fin.close();
            return 3;
        }
    }
    fin.seekg(0, ios::beg); //Возращение в начало файла

    fin >> N;
    fin >> M;
    *	Matr = new int* [N];
    for (int y = 0; y < N; y++)
        *(*Matr+y) = new int [M];
    int i = 0;
    while (fin.peek() != EOF && i<N) { //Подсчёт числа элементов
        for (int j = 0; j < M; j++) {
            fin >> *(*(*Matr+i)+j);
            Sum_Elements++;
        }
        i++;
    }


    if (M < 0) {
        fin.close();
        return 4;
    }
    if (N < 0) {
        fin.close();
        return 5;
    }
    if (Sum_Elements != (N * M)) {	//Количество элементов не совпало с указанными размерами
        fin.close();
        return 6;
    }
    fin.close();
    return 0;
}

void Print_Matr(int ***Matr, const int N, const int M) {

    for (int i = 0; i < N; i++) { //Пока не закончились строки
        for (int j = 0; j < M; j++) { //Пока не закончились столбцы
            cout << "\t" << *(*(*Matr + i) + j);
        }
        cout << endl;
    }
}

void Sum_UN_diagonal(int ***Matr, const int N, const int M, int **Sum_M) {
    int Sum = 0;
    int counter;
    *Sum_M = new int[N];
    for (int i = 1; i < N; i++) {//пока не кончились строки
        counter = 0;
        Sum = 0;
        for (int j = 0; j < i; j++) { //пока не кончились столбцы
            if (*(*(*Matr + i) + j) >= 0) {
                Sum = *(*(*Matr+i)+j) + Sum;
                counter++;
            }
        }
        if (counter==0) //нет чисел >=0
            *(*Sum_M+i) = -1;
        else {
            *(*Sum_M + i) = Sum;
            cout << "\t\nСумма строки [" << i + 1 << "] = " << *(*Sum_M + i);
        }
    }
    cout << "\n\n";}

void Less_Sum(int **Sum_M, const int N) {

    int less = *(*Sum_M+1);

    for (int i=2; i<N; i++) { //пока не наткнёмся на терминальный 0
        if (less > *(*Sum_M + i) && *(*Sum_M + i) != -1)
            less = *(*Sum_M + i);
    }

    cout << "Наименьшая сумма под главной диагональю: " << less << "\n\n\n";

}






void Error_type(const int ErrCode, const char* FNAME) {
    switch (ErrCode)
    {
        case 1:
            cout << "\nОшибка (1)!\nФайл " << FNAME << " не найден!\n\n\n";
            break;
        case 2:
            cout << "\nОшибка (2)!\nФайл " << FNAME << " пуст!\n\n\n";
            break;
        case 3:
            cout << "\nОшибка (3)!\nНекорректные данные (встречен символ) в файле " << FNAME << "\n\n\n";
            break;
        case 4:
            cout << "\nОшибка (4)!\nВ файле " << FNAME << " M < 0!\n\n\n";
            break;
        case 5:
            cout << "\nОшибка (5)!\nВ файле " << FNAME << " N < 0!\n\n\n";
            break;
        case 6:
            cout << "\nОшибка (6)!\nВ файле " << FNAME << " неверное число элементов!\n\n\n";
            break;
    }
}

//*************************************************************


int main() {
    int N_A = 0;					//Число строк в матрице А
    int M_A = 0;					//Число столбцов в матрице А

    int N_B = 0;					//Число строк в матрице B
    int M_B = 0;					//Число столбцов в матрице B

    int	*Sum_A = 0;			//Вектор суммы чисел (построчно) под диагональю в матрице А
    int	*Sum_B = 0;			//Вектор суммы чисел (построчно) под диагональю в матрице B

    int **MatrA = 0;				//Двумерный массив хранения матрицы А
    int **MatrB = 0;				//Двумерный массив хранения матрицы Б

    setlocale(LC_ALL, "ru");

    int ErrCode = Read_File(&MatrA, Matr_A, N_A, M_A);

    if (ErrCode == 0) {				//Проверка файла матрицы А на ошибки

        cout << "\n\tПечать матрицы А:\n";
        Print_Matr(&MatrA, N_A, M_A);	//Печать матрицы А

        if (N_A == M_A) {			//Проверка, квадратная ли матрица А
            cout << "\tМатрица квадратная!";
            cout << "\n\nСуммы построчно под главной диагональю матрицы А: ";
            Sum_UN_diagonal(&MatrA, N_A, M_A, &Sum_A);	//Вычисление сумм строк элементов под главной диагональю матрицы А
            Less_Sum(&Sum_A, N_A);	//Поиск наименьшей суммы в матрице А
        }
        else
            cout << "Суммы под главной диагональю матрицы A невозможно найти!\n\n";
    }
    else
        Error_type(ErrCode, Matr_A);	//Вывод ошибки матрицы A


    ErrCode = Read_File(&MatrB, Matr_B, N_B, M_B);

    if (ErrCode == 0) {				//Проверка файла матрицы А на ошибки
        cout << "\n\tПечать матрицы B:\n";
        Print_Matr(&MatrB, N_B, M_B);	//Печать матрицы B

        if (N_B == M_B) {			//Проверка, квадратная ли матрица B
            cout << "\tМатрица квадратная!";
            cout << "\n\nСуммы построчно под главной диагональю матрицы B: ";
            Sum_UN_diagonal(&MatrB, N_B, M_B, &Sum_B);	//Вычисление сумм строк элементов под главной диагональю матрицы B
            Less_Sum(&Sum_B, N_B);	//Поиск наименьшей суммы в матрице B
        }
        else
            cout << "Суммы под главной диагональю матрицы B невозможно найти!\n\n";
    }
    else
        Error_type(ErrCode, Matr_B);	//Вывод ошибки матрицы B

    for (int i = 0; i < N_A; i++)
        delete[] MatrA[i];
    delete[] MatrA;

    for (int i = 0; i < N_B; i++)
        delete[] MatrB[i];
    delete[] MatrB;

    return 0;
}
