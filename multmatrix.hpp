#ifndef Multmatrix_HPP
#define Multmatrix_HPP

#include <iostream>
#include <fstream>
#include <thread>
#include <random>
#include <vector>
#include <stack>
#include <future>
#include <type_traits>

template <typename T>
class Matrix
{
        size_t matr_rows;
        size_t matr_cols;
        T** matrix;

        //конструктор для создания минора, передаётся изначальная матрица и строка со стоблцом, которые я хочу убрать
        Matrix (const Matrix<T>& matr, size_t row, size_t col): matr_rows (matr.matr_rows - 1), matr_cols(matr.matr_cols - 1), matrix (NULL)//создание алгебраического дополнения
        {
            if (matr.matrix != NULL)
            {
                matrix = new T* [matr_rows];
                for (size_t i = 0; i < matr_rows; ++i)
                {
                    matrix[i] = new T[matr_cols];
                }
                for (size_t i = 0; i < matr.matr_rows; ++i)
                {
                    if (i < row)
                    {
                        for (size_t j = 0; j < matr.matr_cols; ++j)
                        {
                            if (j < col)
                                matrix[i][j] = matr.matrix[i][j];
                            if (j > col)
                                matrix[i][j - 1] = matr.matrix[i][j];
                        }
                    }
                    if (i > row)
                    {
                        for (size_t j = 0; j < matr.matr_cols; ++j)
                        {
                            if (j < col)
                                matrix[i - 1][j] = matr.matrix[i][j];
                            if (j > col)
                                matrix[i - 1][j - 1] = matr.matrix[i][j];
                        }
                    }
                }
            }
        }
        //вспомогательные функции, которые я передаю в потоки в основных блочных методах через futures
        void addition_threading(Matrix<T>& result, int thread_number, int numb_of_thr, const Matrix<T>& m2) const
        //функция принимает по ссылке матрицу, в которую записывается результат, номер потока, который работает, количество всего потоков,
        //вторую матрицу, которая работает
        {
          const int n_elements = (matr_rows * m2.matr_cols); //считаем количество элементов в матрице
          const int n_operations = n_elements / numb_of_thr; //сколько операций будет выполнять каждый поток (делю на сколько-то блоков)
          const int rest_operations = n_elements % numb_of_thr; //"лишние" операции, которые передадутся первому потоку

          int start_op, end_op; //начало и конец блока элементов

          if (thread_number == 0) {//первый поток обрабатывает стандартное количество и ещё "лишние" операции

            start_op = n_operations * thread_number;
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }
          else {
            start_op = n_operations * thread_number + rest_operations;//другие потоки выполняют стандартное количество операций
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }

          for (int op = start_op; op < end_op; ++op)
          {
            const int row = op / m2.matr_cols; //номер ряда равен номеру элемента/количество столбиков
            const int col = op % m2.matr_cols;//номер столбика равен номеру элемента%количество столбиков
            const T e1 = this->el(row, col); // достаём нужные элементы из исходных матриц и складываем их (делаем другу операцию)
            const T e2 = m2.el(row, col);
            result.matrix[row][col] = e1 + e2;

          }
        }

        void substraction_threading(Matrix<T>& result, int thread_number, int numb_of_thr, const Matrix<T>& m2) const
        {
          const int n_elements = (matr_rows * m2.matr_cols);
          const int n_operations = n_elements / numb_of_thr;
          const int rest_operations = n_elements % numb_of_thr;

          int start_op, end_op;

          if (thread_number == 0) {

            start_op = n_operations * thread_number;
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }
          else {
            start_op = n_operations * thread_number + rest_operations;
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }

          for (int op = start_op; op < end_op; ++op)
          {
            const int row = op / m2.matr_cols;
            const int col = op % m2.matr_cols;
            const T e1 = this->el(row, col);
            const T e2 = m2.el(row, col);
            result.matrix[row][col] = e1 - e2;

          }
        }

        void scalar_threading(Matrix<T>& result, int thread_number, int numb_of_thr,  T right) const
        {
          const int n_elements = (matr_rows * this->matr_cols);
          const int n_operations = n_elements / numb_of_thr;
          const int rest_operations = n_elements % numb_of_thr;

          int start_op, end_op;

          if (thread_number == 0) {

            start_op = n_operations * thread_number;
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }
          else {
            start_op = n_operations * thread_number + rest_operations;
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }

          for (int op = start_op; op < end_op; ++op)
          {
            const int row = op / this->matr_cols;
            const int col = op % this->matr_cols;
            const T e = this->el(row, col);
            result.matrix[row][col] = right * e;

          }
        }

        void multiply_threading(Matrix<T>& result, int thread_number, int numb_of_thr, const Matrix<T>& m2) const
        {
          const int n_elements = (matr_rows * m2.matr_cols);
          const int n_operations = n_elements / numb_of_thr;
          const int rest_operations = n_elements % numb_of_thr;

          int start_op, end_op;

          if (thread_number == 0) {

            start_op = n_operations * thread_number;
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }
          else {
            start_op = n_operations * thread_number + rest_operations;
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }

          for (int op = start_op; op < end_op; ++op)
          {
            const int row = op / m2.matr_cols;
            const int col = op % m2.matr_cols;
            for (int i = 0; i < m2.matr_rows; ++i)
            {
              const T e1 = this->el(row, i);
              const T e2 = m2.el(i, col);
              result.matrix[row][col] += e1 * e2;
            }
          }
        }

        void transpose_threading(Matrix<T>& result, int thread_number, int numb_of_thr) const
        {
          const int n_elements = (matr_rows * matr_cols);
          const int n_operations = n_elements / numb_of_thr;
          const int rest_operations = n_elements % numb_of_thr;

          int start_op, end_op;

          if (thread_number == 0) {

            start_op = n_operations * thread_number;
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }
          else {
            start_op = n_operations * thread_number + rest_operations;
            end_op = (n_operations * (thread_number + 1)) + rest_operations;
          }

          for (int op = start_op; op < end_op; ++op)
          {
            const int row = op / matr_cols;
            const int col = op % matr_cols;
            result.matrix[row][col] = this->el(col, row);

          }
        }

        //функция для подсчёта алгебраического дополнения
        T determ_threading (size_t col) const //передаётся номер столбца, который вычёркивается (первая строка вычёркивается по умолчанию)
        {
          Matrix<T> minmatr(*this, 0, col); //строим минор

          T res;
          if ((col % 2) == 0)
              res = matrix[0][col] * minmatr.multithreading_determ(); //считаю произведение элемента на нужный определеитель маленький
          else
              res = - matrix[0][col] * minmatr.multithreading_determ();
          return res;
        }
    public:
        Matrix () : matr_rows(0), matr_cols(0), matrix (NULL)// конструктор по умолчанию
        {}

        Matrix (size_t rows, size_t cols, T** matr): matr_rows(rows), matr_cols(cols), matrix (std::move(matr))//констурктор со всеми размерами
        {}

        Matrix (size_t rows, size_t cols) : matr_rows(rows), matr_cols(cols), matrix (NULL)//конструктор с заданными размерами
        {
            matrix = new T* [matr_rows];
            for (unsigned i = 0; i < matr_rows; ++i)
            {
                matrix[i] = new T[matr_cols];
            }
            for (unsigned i = 0; i < matr_rows; ++i)
            {
                for (unsigned j = 0; j < matr_cols; ++j)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        Matrix (const Matrix<T> &other): matr_rows (other.matr_rows), matr_cols (other.matr_cols), matrix (NULL)//констурктор копирования
        {
            if (other.matrix != NULL){
            matrix = new T* [other.matr_rows];

            for (unsigned i = 0; i < matr_rows; ++i)
            {
                matrix[i] = new T[matr_cols];
            }
            for (unsigned i = 0; i < matr_rows; ++i)
            {
                for (unsigned j = 0; j < matr_cols; ++j)
                {
                    matrix[i][j] = other.matrix[i][j];
                }
            }
            }
        }

        Matrix (std::ifstream& is)// констурктор по считыванию из файла
        {
            if (is.is_open())
            {
                is >> matr_rows;
                is >> matr_cols;

                matrix = new T* [matr_rows];

                for (size_t i = 0; i < matr_rows; ++i)
                {
                    matrix[i] = new T[matr_cols];
                }
                for (size_t i = 0; i < matr_rows; ++i)
                {
                    for (size_t j = 0; j < matr_cols; ++j)
                    {
                        is >> matrix[i][j];
                    }
                }
            }

            else
            {
                throw "Stream is not opened";
            }
        }

        ~Matrix ()//деструктор
        {
            for (unsigned i = 0; i < matr_rows; ++i)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }

        T& el (size_t i, size_t j) const //возврат элемента
        {
            if (i < matr_rows && j < matr_cols)
            {
                 return matrix[i][j];
            }
            else
            {
                 throw (std::out_of_range("Array::operator[] wrong index"));
            }
        }

        size_t& getrows() {return matr_rows;} const //возврат количества строк
        size_t& getcols() {return matr_cols;} const //возврат количества столбцов

        //установка у матрицы значений полей
        void setmatrix(T** matr) {matrix = matr;} 
        void setrows (size_t rows) {matr_rows = rows;}
        void setcols (size_t cols) {matr_cols = cols;}

        //метод для заполнения матрицы рандомными значениями
        void randomise ()
        {
            std::default_random_engine e;
            std::uniform_real_distribution <T> rnd (1, 10);

            for (size_t i = 0; i < matr_rows; ++i)
            {
              for (size_t j = 0; j < matr_cols; ++j)
                matrix[i][j] = rnd(e);
            }
        }

        //оператор не равно для дальнейшего использования в операторе присываивания
        bool operator != (const Matrix<T>& other) const
        {
          if (matr_rows != other.matr_rows || matr_cols != other.matr_cols)
            return true;
          else
          {
            for (size_t i = 0; i < matr_rows; ++i)
            {
              for (size_t j = 0; j < matr_cols; ++j)
              {
                if (matrix[i][j] != other.matrix[i][j])
                  return true;
              }
            }
          }
          return false;
        }

        //оператор присыванивания
        Matrix<T>& operator =  (const Matrix<T>& other)
        {
          if (*this != other)
          {
            matr_rows = other.matr_rows;
            matr_cols = other.matr_cols;
            matrix = other.matrix;
          }
          return *this;
        }

        //многопоточные методы. Идут парами: просто thread и работа с futures через закрытые методы
        Matrix<T>  multithreading_addition (const Matrix<T>& right) const //передаётся матрица, котоаря прибавляется
        {
            if ((matr_rows == right.matr_rows) && (matr_cols == right.matr_cols)) //проверка, что может быть совершено действие
            {

              std::stack <std::thread> threads; //стэк с потоками, которые запускаются

              T** res_matrix = new T* [matr_rows]; // создание массива для результирующей матрицы
              Matrix<T> result (matr_rows, right.matr_cols, res_matrix);//результирующая матрица
              for (size_t i = 0; i < matr_rows; ++i)
              {
                result.matrix [i] = new T [matr_cols];
                for (size_t j = 0; j < matr_cols; ++j)
                  //поток с лямбда-функцией, которой передаются элементы на поределённом месте в обеиз матрицах
                  //потоки создаются для каждого элемента
                  threads.emplace(std::thread ([this, &result, &right, i, j](){result.matrix[i][j] = matrix[i][j] + right.matrix[i][j];}));

              }

              for (int i = 0; i < matr_rows*matr_cols; ++i)//всего потоков столько же, сколько элементов в матрице
              {
                //ожидание и присоединение всех потоков, начиная с последнего
                threads.top().join();
                threads.pop();
              }

              return result;
            }
            else
            {
              throw "Matrices have not equal sizes";
            }
        }

        Matrix<T> multithreading_addition (const Matrix<T>& right, int numb_of_thr) const 
        // передаётся матрица, которая прибавляется и количество потоков (блоков, на которые поделится матрица)
        {
          if ((matr_rows == right.matr_rows) && (matr_cols == right.matr_cols)) //проверка на возможность операции
          {
            T** res_matrix = new T* [matr_rows]; //создание массива для результирующей матрицы
            for (size_t i = 0; i < matr_rows; ++i)
            {
              res_matrix [i] = new T [matr_cols];
            }
            Matrix<T> result (matr_rows, right.matr_cols, res_matrix); //результирующая матрица

            std::vector <std::future<void>> futures; //создание вектора с фьючерсами

            for (int i = 0; i < numb_of_thr; ++i)
            {
              futures.emplace_back(std::async(&Matrix<T>::addition_threading, this, std::ref(result), i, numb_of_thr, std::cref(right)));
              //создаю асинхронные потоки с закрытыми методами
            }

            for (auto i = futures.begin(); i < futures.end(); ++i)
            {
              i->get();
              //получаю результаты из каждого потока
            }

            return result;
          }
          else
          {
            throw "Matrices have not equal sizes";
          }
        }

        Matrix<T> multithreading_substraction (const Matrix<T>& right) const
        {
            if ((matr_rows == right.matr_rows) && (matr_cols == right.matr_cols))
            {

              std::stack <std::thread> threads;

              T** res_matrix = new T* [matr_rows];
              Matrix<T> result (matr_rows, right.matr_cols, res_matrix);
              for (size_t i = 0; i < matr_rows; ++i)
              {
                result.matrix [i] = new T [matr_cols];
                for (size_t j = 0; j < matr_cols; ++j)
                  threads.emplace(std::thread ([this, &result, &right, i, j](){result.matrix[i][j] = matrix[i][j] - right.matrix[i][j];}));

              }

              for (int i = 0; i < matr_rows*matr_cols; ++i)
              {
                threads.top().join();
                threads.pop();
              }

              return result;
            }
            else
            {
              throw "Matrices have not equal sizes";
            }
        }

        Matrix<T> multithreading_substraction (const Matrix<T>& right, int numb_of_thr) const
        {
          if ((matr_rows == right.matr_rows) && (matr_cols == right.matr_cols))
          {
            T** res_matrix = new T* [matr_rows];
            for (size_t i = 0; i < matr_rows; ++i)
            {
              res_matrix [i] = new T [matr_cols];
            }
            Matrix<T> result (matr_rows, right.matr_cols, res_matrix);

            std::vector <std::future<void>> futures;

            for (int i = 0; i < numb_of_thr; ++i)
            {
              futures.emplace_back(std::async(&Matrix<T>::substraction_threading, this, std::ref(result), i, numb_of_thr, std::cref(right)));
            }

            for (auto i = futures.begin(); i < futures.end(); ++i)
            {
              i->get();
            }

            return result;
          }
          else
          {
            throw "Matrices have not equal sizes";
          }
        }

        Matrix<T> multithreading_scalar (T scalar) const
        {
              std::stack <std::thread> threads;

              T** res_matrix = new T* [matr_rows];
              Matrix<T> result (matr_rows, matr_cols, res_matrix);
              for (size_t i = 0; i < matr_rows; ++i)
              {
                result.matrix [i] = new T [matr_cols];
                for (size_t j = 0; j < matr_cols; ++j)
                  threads.emplace(std::thread ([this, &result, scalar, i, j](){result.matrix[i][j] = matrix[i][j]*scalar;}));

              }

              for (int i = 0; i < matr_rows*matr_cols; ++i)
              {
                threads.top().join();
                threads.pop();
              }

              return result;
          }

        Matrix<T> multithreading_scalar (T right, int numb_of_thr) const
        {
          T** res_matrix = new T* [matr_rows];
          for (size_t i = 0; i < matr_rows; ++i)
          {
            res_matrix [i] = new T [matr_cols];
          }
          Matrix<T> result (matr_rows, matr_cols, res_matrix);

          std::vector <std::future<void>> futures;

          for (int i = 0; i < numb_of_thr; ++i)
          {
            futures.emplace_back(std::async(&Matrix<T>::scalar_threading, this, std::ref(result), i, numb_of_thr, std::cref(right)));

          }

          for (auto i = futures.begin(); i < futures.end(); ++i)
          {
            i->get();
          }

          return result;
        }

        Matrix<T> multithreading_multiplication (const Matrix<T>& right) const
        {
            if (matr_cols == right.matr_rows)
            {

              std::stack <std::thread> threads;

              T** res_matrix = new T* [matr_rows];
              Matrix<T> result (matr_rows, right.matr_cols, res_matrix);
              for (size_t i = 0; i < matr_rows; ++i)
              {
                result.matrix [i] = new T [matr_cols];
                for (size_t j = 0; j < matr_cols; ++j)
                  threads.emplace(std::thread ([this, &result, &right, i, j](){
                    result.matrix[i][j] = 0;

                    for (size_t k = 0; k < matr_cols; ++k)
                      result.matrix[i][j] += matrix[i][k]*right.matrix[k][j];
                  }));

              }

              for (int i = 0; i < matr_rows*matr_cols; ++i)
              {
                threads.top().join();
                threads.pop();
              }

              return result;
            }
            else
            {
              throw "A number of left matrix rows is not equalt to a number of right matrix columns";
            }
        }

        Matrix <T> multithreading_multiplication (const Matrix<T>& m2, int numb_of_thr) const
        {
          if (matr_cols == m2.matr_rows)
          {
              T** res_matrix = new T* [matr_rows];
              for (size_t i = 0; i < matr_rows; ++i)
              {
                  res_matrix[i] = new T [m2.matr_cols];
                  for (size_t j = 0; j < m2.matr_cols; ++j)
                      res_matrix[i][j] = 0;
              }
              Matrix<T> result (matr_rows, m2.matr_cols, res_matrix);

              std::vector <std::future<void>> futures;

              for (int i = 0; i < numb_of_thr; ++i)
              {
                futures.emplace_back(std::async(&Matrix<T>::multiply_threading, this, std::ref(result), i, numb_of_thr, std::cref(m2)));

              }

              for (auto i = futures.begin(); i < futures.end(); ++i)
              {
                i->get();
              }

              return result;
          }
          else
          {
              throw "Wrong matrices' sizes";
          }
        }

        Matrix<T> multithreading_transpose() const
        {
            T** res_matr = new T* [matr_cols];
            Matrix<T> matr_transpose(matr_cols, matr_rows, res_matr);

            std::stack <std::thread> threads;

            for (size_t i = 0; i < matr_cols; ++i)
            {
                matr_transpose.matrix[i] = new T [matr_rows];
                for (size_t j = 0; j < matr_rows; ++j)
                    threads.emplace (std::thread ([this, &matr_transpose, i, j](){matr_transpose.matrix[i][j]=matrix[j][i];}));
            }

            for (int i = 0; i < matr_rows*matr_cols; ++i)
            {
              threads.top().join();
              threads.pop();
            }
            return matr_transpose;
        }

        Matrix<T> multithreading_transpose(int numb_of_thr) const
        {
            T** res_matr = new T* [matr_cols];
            Matrix<T> matr_transpose(matr_cols, matr_rows, res_matr);

            std::vector <std::future<void>> futures;

            for (size_t i = 0; i < matr_cols; ++i)
            {
                matr_transpose.matrix[i] = new T [matr_rows];
            }

            for (int i = 0; i < numb_of_thr; ++i)
            {
              futures.emplace_back (std::async (&Matrix<T>::transpose_threading, this, std::ref(matr_transpose), i, numb_of_thr));
            }

            for (auto i = futures.begin(); i < futures.end(); ++i)
            {
              i->get();
            }
            return matr_transpose;
        }

        //многопоточный подсчёт определителя
        T multithreading_determ () const
        {
            if (matr_rows == matr_cols) //проверка возможности подсчёта
            {
                if (matr_rows == 1) //случай крайний при раскрытии рекурсии
                {
                    return matrix[0][0];
                }
                else
                {

                    std::vector <std::future<T>> async_threads; 
                    //создаю вектор с фьючерсами, в который хранятся значения для каждого элемента первой строки

                    for (size_t i = 0; i < matr_cols; ++i)
                    {
                      async_threads.emplace_back (std::async (&Matrix<T>::determ_threading, this, i));
                      //в асинхронный поток идёт закрытая функция с подсчётом алгебрического дополнения для каждого элемента первой строки
                      //после алгебраическое дополнение умножается на элемент и берётся с нужным знаком
                    }
                    T determ = 0; //результирующее значение определителя
                    for (auto i = async_threads.begin(); i < async_threads.end(); ++i)
                      determ += i->get(); //получаю значения из асинхронных потоков
                    return determ;
                }
            }
            throw ("The matrice is not square!");
        }

        //создание обратной матрицы
        Matrix<T> multithreading_reverse ()
        {
          T det = this-> multithreading_determ();

          if (det != 0)
          {
            Matrix <T> res = this->multithreading_reverse (det, std::is_integral<T>());//расхождение на два случая для целых и нецелых типов
            return res;
          }
          else
          {
              throw ("The determinant is zero");
          }
        }

        Matrix<long double> multithreading_reverse (T deter, std::true_type)
        {
          long double det = static_cast<long double> (deter); //подсчёт опрееделителя
          long double** res_matr = new long double* [matr_rows]; //массив для матрицы

          Matrix<long double> A_matr (matr_rows, matr_cols, res_matr); //матрица алгебраических дополнений

          std::stack <std::thread> threads;

          for (size_t i = 0; i < matr_rows; ++i)
          {
            A_matr.matrix[i] = new long double [matr_cols];
            for (size_t j = 0; j < matr_cols; ++j)
            {
              threads.emplace (std::thread([this, &A_matr, i, j](){ 
                //поток с лямбда функцией, которая записывает в A_matr значение алгебраического дополнения
                Matrix<T> minmatr(*this, i, j);
                long double mindet = static_cast<long double>(minmatr.multithreading_determ());
                if (((i + j) % 2) == 0)
                    A_matr.matrix[i][j] = mindet;
                else
                    A_matr.matrix[i][j] = -1*mindet;
              }));

            }
          }

          for (int i = 0; i < matr_rows*matr_cols; ++i) //присоединяю все потоки
          {
            threads.top().join();
            threads.pop();
          }

          Matrix<long double> A_matr_transp = A_matr.multithreading_transpose(); //траснпонирую матрицу алгебраических дополнений

          long double det1 = 1 / det; //беру число, обратное определеителю

          Matrix<long double> res = A_matr_transp.multithreading_scalar(det1);//умножаю матрицу на число

          return res;
        }

        Matrix<T> multithreading_reverse (T det, std::false_type)
        {
          T** res_matr = new T* [matr_rows];

          Matrix<T> A_matr (matr_rows, matr_cols, res_matr);

          std::stack <std::thread> threads;

          for (size_t i = 0; i < matr_rows; ++i)
          {
            A_matr.matrix[i] = new T [matr_cols];
            for (size_t j = 0; j < matr_cols; ++j)
            {
              threads.emplace (std::thread([this, &A_matr, i, j](){
                Matrix<T> minmatr(*this, i, j);
                T mindet = minmatr.multithreading_determ();
                if (((i + j) % 2) == 0)
                    A_matr.matrix[i][j] = mindet;
                else
                    A_matr.matrix[i][j] = -1*mindet;
              }));

            }
          }

          for (int i = 0; i < matr_rows*matr_cols; ++i)
          {
            threads.top().join();
            threads.pop();
          }

          Matrix<T> A_matr_transp = A_matr.multithreading_transpose();

          T det1 = 1 / det;

          Matrix<T> res = A_matr_transp.multithreading_scalar(det1);

          return res;
        }


};
template <typename T> // ввод матрицы из потока
std::istream& operator >> (std::istream& is, Matrix<T>& matr)
{
    if (matr.getcols() == 0 or matr.getrows() == 0)
    {
        size_t rows = 0;
        size_t cols = 0;

        is >> rows;
        matr.setrows(rows);

        is >> cols;
        matr.setcols (cols);
    }

    T** matrix = new T* [matr.getrows()];
    for (size_t i = 0; i < matr.getrows(); ++i)
    {
        matrix[i] = new T [matr.getcols()];
        for (size_t j = 0; j < matr.getcols(); ++j)
        {
            is >> matrix[i][j];
        }
    }

    matr.setmatrix(matrix);
    return is;
}

template <typename T> // вывод матрицы в поток
std::ostream& operator << (std::ostream& os, Matrix<T>& matr)
{
    for (size_t i = 0; i < matr.getrows(); ++i)
    {
        os << matr.el(i, 0);
        for (size_t j = 1; j < matr.getcols(); ++j)
        {
            os << " " << matr.el(i, j);
        }
        os << std::endl;
    }
    return os;
}


#endif
