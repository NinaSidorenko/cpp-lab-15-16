#include <iostream>
#include <chrono>
#include "multmatrix.hpp"

#define THREADS 6

int main()
{
  std::cout << "EQUAL NUMBERS OF THREADS" << std::endl;
  std::cout << "Addition:" << std::endl;
  int suma [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int k = 0; k < 3; ++k)
  {

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

      suma[i-1]+= elapsed.count();
    }
  }
  for (int i = 0; i <10; ++i)
    std::cout << "Size is " << 3*(i+1) <<". Time is " << suma[i]/3 << " ms"<< std::endl;

  std::cout << "Substraction:"<< std::endl;
  int sums [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int k = 0; k < 3; ++k)
  {


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

      sums[i-1]+= elapsed.count();
    }
  }
  for (int i = 0; i <10; ++i)
    std::cout << "Size is " << 3*(i+1) <<". Time is " << sums[i]/3 << " ms"<< std::endl;

  std::cout << "Scalar multiplication:"<< std::endl;
  int sumsm [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int k = 0; k < 3; ++k)
  {

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

      sumsm[i-1]+= elapsed.count();
    }
  }
  for (int i = 0; i <10; ++i)
    std::cout << "Size is " << 3*(i+1) <<". Time is " << sumsm[i]/3 << " ms"<< std::endl;

  std::cout << "Matrix multiplication:"<<std::endl;
  int summ [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int k = 0; k < 3; ++k)
  {

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

      summ[i-1]+= elapsed.count();
    }
  }
  for (int i = 0; i <10; ++i)
    std::cout << "Size is " << 3*(i+1) <<". Time is " << summ[i]/3 << " ms"<< std::endl;

  std::cout << "Transposition:"<< std::endl;
  int sumt [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int k = 0; k < 3; ++k)
  {

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

      sumt[i-1]+= elapsed.count();
    }
  }
  for (int i = 0; i <10; ++i)
    std::cout << "Size is " << 3*(i+1) <<". Time is " << sumt[i]/3 << " ms"<< std::endl;

  std::cout << std::endl << "EQUAL SIZES OF MATRIXES" << std::endl;

  Matrix <double> m1 (10, 10);
  m1.randomise();

  Matrix <double> m2 (10, 10);
  m2. randomise();

  std::cout << "Addition:" << std::endl;
  int summa [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int k = 0; k < 100; ++k)
  {
    for (int i = 1; i < 11; ++i)
    {

      const auto start = std::chrono::high_resolution_clock::now();

      Matrix <double> res1 = m1.multithreading_addition (m2, i);

      const auto stop = std::chrono::high_resolution_clock::now();

      auto elapsed = (stop - start);

      summa[i-1] += elapsed.count();
    }
  }
  for (int i = 0; i < 10; ++i)
    std::cout << "Number of threads " << i+1 << ". Time is " << summa[i]/3 << " ms"<< std::endl;


  return 0;
}
