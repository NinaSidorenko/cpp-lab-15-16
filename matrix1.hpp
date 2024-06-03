#ifndef Matrix1_HPP
#define Matrix1_HPP

#include <iostream>
#include <fstream>
#include <thread>
#include <random>
#include <vector>
#include <stack>
#include <future>

template <typename T>
class Matrix
{
        size_t matr_rows;
        size_t matr_cols;
        T** matrix;

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

        void addition_threading(Matrix<T>& result, int thread_number, int numb_of_thr, const Matrix<T>& m2) const
        {
          const int n_elements = (this->matr_rows * m2.matr_cols);
          const int n_operations = n_elements / numb_of_thr; //operations for each thread
          const int rest_operations = n_elements % numb_of_thr; //operations, which will be given to the first thread

          int start_op, end_op;

          if (thread_number == 0) {
            // First thread does more job
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
            result.matrix[row][col] = e1 + e2;

          }
        }

        void substraction_threading(Matrix<T>& result, int thread_number, int numb_of_thr, const Matrix<T>& m2) const
        {
          const int n_elements = (this->matr_rows * m2.matr_cols);
          const int n_operations = n_elements / numb_of_thr; //operations for each thread
          const int rest_operations = n_elements % numb_of_thr; //operations, which will be given to the first thread

          int start_op, end_op;

          if (thread_number == 0) {
            // First thread does more job
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
          const int n_elements = (this->matr_rows * this->matr_cols);
          const int n_operations = n_elements / numb_of_thr; //operations for each thread
          const int rest_operations = n_elements % numb_of_thr; //operations, which will be given to the first thread

          int start_op, end_op;

          if (thread_number == 0) {
            // First thread does more job
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
          const int n_elements = (this->matr_rows * m2.matr_cols);
          const int n_operations = n_elements / numb_of_thr; //operations for each thread
          const int rest_operations = n_elements % numb_of_thr; //operations, which will be given to the first thread

          int start_op, end_op;

          if (thread_number == 0) {
            // First thread does more job
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

        T determ_threading (size_t col) const
        {
          Matrix<T> minmatr(*this, 0, col);

          T res;
          if ((col % 2) == 0)
              res = matrix[0][col] * minmatr.multithreading_determ();
          else
              res = - matrix[0][col] * minmatr.multithreading_determ();
          return res;
        }

    public:
        Matrix () : matr_rows(0), matr_cols(0), matrix (NULL)// пустой
        {}

        Matrix (size_t rows, size_t cols, T** matr): matr_rows(rows), matr_cols(cols), matrix (std::move(matr))
        {}

        Matrix (size_t rows, size_t cols) : matr_rows(rows), matr_cols(cols), matrix (NULL)//с заданными размерами
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

        Matrix (const Matrix<T> &other): matr_rows (other.matr_rows), matr_cols (other.matr_cols), matrix (NULL)//копирования
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

        Matrix (std::ifstream& is)//считывание из файла
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

        void setmatrix(T** matr) {matrix = matr;}
        void setrows (size_t rows) {matr_rows = rows;}
        void setcols (size_t cols) {matr_cols = cols;}

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

        Matrix<T> operator + (const Matrix<T>& right) const
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
                  threads.emplace(std::thread ([this, &result, &right, i, j](){result.matrix[i][j] = matrix[i][j] + right.matrix[i][j];}));

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

        Matrix<T> multithreading_addition (const Matrix<T>& right, int numb_of_thr) const
        {
          if ((matr_rows == right.matr_rows) && (matr_cols == right.matr_cols))
          {
            T** res_matrix = new T* [matr_rows];
            for (size_t i = 0; i < matr_rows; ++i)
            {
              res_matrix [i] = new T [matr_cols];
              for (size_t j = 0; j < matr_cols; ++j)
              {
                res_matrix[i][j] = 0;
              }
            }
            Matrix<T> result (matr_rows, right.matr_cols, res_matrix);

            std::vector <std::future<void>> futures;

            for (int i = 0; i < numb_of_thr; ++i)
            {
              futures.emplace_back(std::async(&Matrix<T>::addition_threading, this, std::ref(result), i, numb_of_thr, std::cref(right)));
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

        Matrix<T> operator - (const Matrix<T>& right) const
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
              for (size_t j = 0; j < matr_cols; ++j)
              {
                res_matrix[i][j] = 0;
              }
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

        Matrix<T> operator * (T scalar) const
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
            for (size_t j = 0; j < matr_cols; ++j)
            {
              res_matrix[i][j] = 0;
            }
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

        Matrix<T> operator * (const Matrix<T>& right) const
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

        T multithreading_determ () const
        {
            if (matr_rows == matr_cols)
            {
                if (matr_rows == 1)
                {
                    return matrix[0][0];
                }
                else
                {

                    std::vector <std::future<T>> async_threads;

                    for (size_t i = 0; i < matr_cols; ++i)
                    {
                      async_threads.emplace_back (std::async (&Matrix<T>::determ_threading, this, i));
                    }
                    T determ = 0;
                    for (auto i = async_threads.begin(); i < async_threads.end(); ++i)
                      determ += i->get();
                    return determ;
                }
            }
            throw ("The matrice is not square!");
        }

};
template <typename T> // ввод матрицы
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

template <typename T> // вывод матрицы
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
