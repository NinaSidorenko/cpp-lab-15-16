#include <iostream>
#include <chrono>
#include "multmatrix.hpp"

#define THREADS 4

int main()
{
  std::cout << "EQUAL NUMBERS OF THREADS" << std::endl;
  std::cout << "Addition:" << std::endl;
  for (int i = 1; i < 11; ++i)
  {

    Matrix <double> m1 (3*i, 3*i);
    m1.randomise();

    Matrix <double> m2 (3*i, 3*i);
    m2. randomise();

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_addition (m2, THREADS);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Size is " << 3*i << " * "<< 3*i <<". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  std::cout << "Substraction:"<< std::endl;
  for (int i = 1; i < 11; ++i)
  {

    Matrix <double> m1 (3*i, 3*i);
    m1.randomise();

    Matrix <double> m2 (3*i, 3*i);
    m2. randomise();

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_substraction (m2, THREADS);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Size is " << 3*i << " * "<< 3*i <<". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  std::cout << "Scalar multiplication:"<< std::endl;
  for (int i = 1; i < 11; ++i)
  {

    Matrix <double> m1 (3*i, 3*i);
    m1.randomise();

    Matrix <double> m2 (3*i, 3*i);
    m2. randomise();

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_scalar (2, THREADS);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Size is " << 3*i << " * "<< 3*i <<". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  std::cout << "Matrix multiplication:"<<std::endl;
  for (int i = 1; i < 11; ++i)
  {

    Matrix <double> m1 (3*i, 3*i);
    m1.randomise();

    Matrix <double> m2 (3*i, 3*i);
    m2. randomise();

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_multiplication (m2, THREADS);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Size is " << 3*i << " * "<< 3*i <<". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  std::cout << "Transposition:"<< std::endl;
  for (int i = 1; i < 11; ++i)
  {

    Matrix <double> m1 (3*i, 3*i);
    m1.randomise();

    Matrix <double> m2 (3*i, 3*i);
    m2. randomise();

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_transpose (THREADS);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Size is " << 3*i << " * "<< 3*i <<". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  std::cout << std::endl << "EQUAL SIZES OF MATRIXES" << std::endl;

  Matrix <double> m1 (10, 10);
  m1.randomise();

  Matrix <double> m2 (10, 10);
  m2. randomise();

  std::cout << "Addition:" << std::endl;
  for (int i = 1; i < 11; ++i)
  {

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_addition (m2, i);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Number of threads " << i << ". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  std::cout << "Substraction:" << std::endl;
  for (int i = 1; i < 11; ++i)
  {

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_substraction (m2, i);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Number of threads " << i << ". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  std::cout << "Scalar multiplication:" << std::endl;
  for (int i = 1; i < 11; ++i)
  {

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_scalar (2, i);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Number of threads " << i << ". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  std::cout << "Matrix multiplication:" << std::endl;
  for (int i = 1; i < 11; ++i)
  {

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_multiplication (m2, i);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Number of threads " << i << ". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  std::cout << "Transposition:" << std::endl;
  for (int i = 1; i < 11; ++i)
  {

    const auto start = std::chrono::high_resolution_clock::now();

    Matrix <double> res1 = m1.multithreading_transpose (i);

    const auto stop = std::chrono::high_resolution_clock::now();

    auto elapsed = (stop - start);

    std::cout << "Number of threads " << i << ". Time is " << elapsed.count() << " ms"<< std::endl;
  }

  return 0;
}
