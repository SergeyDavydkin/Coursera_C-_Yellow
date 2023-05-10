//*********************************************************************************************
//*********************************************************************************************
/*
Условие
В этой задаче вам надо разработать класс Matrix для представления целочисленной матрицы. 
Более подробно класс Matrix должен иметь:

- конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
- конструктор от двух целочисленных параметров: num_rows и num_cols, — которые задают количество 
строк и столбцов матрицы соответственно
- метод Reset, принимающий два целочисленных параметра, которые задают новое количество строк 
и столбцов матрицы соответственно; метод Reset меняет размеры матрицы на заданные и обнуляет 
все её элементы
- константный метод At, который принимает номер строки и номер столбца 
(именно в этом порядке; нумерация строк и столбцов начинается с нуля) и возвращает значение 
в соответствущей ячейке матрицы
- неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в 
соответствущей ячейке матрицы
- константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов 
матрицы соответственно
Если количество строк или количество столбцов, переданное в конструктор класса Matrix или 
метод Reset, оказалось отрицательным, то должно быть выброшено стандартное исключение out_of_range.

Это же исключение должен бросать метод At, если переданная в него ячейка выходит 
за границы матрицы.

Кроме того для класса Matrix должны быть определены следующие операторы:

- оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк 
и столбцов (именно в этом порядке), а затем все элементы матрицы: сначала элемент первой строки 
и первого столбца, затем элемент первой строки и второго столбца и так далее
- оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает 
оператор ввода, — в первой строке количество строк и столбцов, во второй — элементы первой строки, 
в третьей — элементы второй строки и т.д.
- оператор проверки на равенство (==): он должен возвращать true, если сравниваемые матрицы имеют 
одинаковый размер и все их соответствующие элементы равны между собой, в противном случае он 
должен возвращать false.
- оператор сложения: он должен принимать две матрицы и возвращать новую матрицу, которая является 
их суммой; если переданные матрицы имеют разные размеры этот оператор должен выбрасывать 
стандартное исключение invalid_argument.

Вам дана заготовка решения, а также пример ввода и вывода. Когда вы реализуете класс Matrix, 
вы можете использовать этот пример, чтобы убедиться, что ваш код работает правильно.

Важно! Пример не проверяет выполнение всех требований, приведённых в условии.

Автор задачи — Дмитрий Минченко Файл с заготовкой решения задачи
mstrix_sum.cpp

Пример ввода
3 5
6 4 -1 9 8
12 1 2 9 -5
-4 0 12 8 6

3 5
5 1 0 -8 23
14 5 -6 6 9
8 0 5 4 1

Пример вывода

3 5
11 5 -1 1 31
26 6 -4 15 4
4 0 17 12 7
Примечание Матрицы с нулём строк или нулём столбцов считаются пустыми. 
Любые две пустые матрицы равны. Сумма двух пустых матриц также является пустой матрицей.
*/
//*********************************************************************************************
//*********************************************************************************************

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
class Matrix {
public:
	Matrix()
		: num_rows(0)
		, num_cols(0) {}

	Matrix(int rows, int cols) {
		Reset(rows, cols);
	}
		

	void Reset(int new_rows, int new_cols) {
		if (new_rows < 0) {
			throw out_of_range("nums_rows must be >= 0");
		}

		if (new_cols < 0) {
			throw out_of_range("nums_columns must be >= 0");
		}

		if (new_rows == 0 || new_cols == 0) {
			new_cols = new_cols = 0;
		}
		num_rows = new_rows;
		num_cols = new_cols;
		elements.assign(new_rows, vector<int>(new_cols));
	}

	int& At(int rows, int cols) {
		return elements.at(rows).at(cols);
	}

	int At(int rows, int cols) const {
		return elements.at(rows).at(cols);
	}

	int GetNumRows() const {
		return num_rows;
	}

	int GetNumColumns() const {
		return num_cols;
	}

private:
	int num_rows;
	int num_cols;

	vector<vector<int>> elements;
};
 
// * оператор ввода для класса Matrix из потока istream
istream& operator >>(istream& in, Matrix& matrix) {
	int num_rows;
	in >> num_rows;

	int num_columns;
	in >> num_columns;

	matrix.Reset(num_rows, num_columns);
	for (int row = 0; row < num_rows; ++row) {
		for (int column = 0; column < num_columns; ++column) {
			in >> matrix.At(row, column);
		}
	}
	return in;
}
 
// * оператор вывода класса Matrix в поток ostream
ostream& operator <<(ostream& out, const Matrix& matrix) {
	out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
	
	for (int row = 0; row < matrix.GetNumRows(); ++row) {
		for (int column = 0; column < matrix.GetNumColumns(); ++column) {
			if (column > 0) {
				out << " ";
			}
			out << matrix.At(row, column);
		}
		out << endl;
	}
	return out;
}
 
// * оператор проверки на равенство двух объектов класса Matrix
bool operator ==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() != rhs.GetNumRows()) {
		return false;
	}
	if (lhs.GetNumColumns() != rhs.GetNumColumns()) {
		return false;
	}

	for (int row = 0; row < lhs.GetNumRows(); ++row) {
		for (int col = 0; col < lhs.GetNumColumns(); ++col) {
			if (lhs.At(row, col) != rhs.At(row, col)) {
				return false;
			}
		}
	}
	return true;
}
 
// * оператор сложения двух объектов класса Matrix
Matrix operator +(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() != rhs.GetNumRows()) {
		throw invalid_argument("Mismatched number of rows");
	}

	if (lhs.GetNumColumns() != rhs.GetNumColumns()) {
		throw invalid_argument("Mismatched number of columns");
	}

	Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());
	for (int row = 0; row < lhs.GetNumRows(); ++row) {
		for (int col = 0; col < lhs.GetNumColumns(); ++col) {
			result.At(row, col) = lhs.At(row, col) + rhs.At(row, col);
		}
	}
	return result;
}

int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;
	return 0;
}
