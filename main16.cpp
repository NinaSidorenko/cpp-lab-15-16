#include <iostream>
#include <chrono>
#include "multmatrix.hpp"

#define THREADS 5
#define THREADS1 10

int main()
{
  int size [5] = {10, 50, 100, 500, 1000};

  std::cout << "EQUAL NUMBERS OF THREADS 5" << std::endl;
  std::cout << "Addition:" << std::endl;
    for (int i: size)
    {

      Matrix <double> m1 (i, i);
      m1.randomise();

      Matrix <double> m2 (i, i);
      m2. randomise();

      const auto start = std::chrono::high_resolution_clock::now();

      Matrix <double> res1 = m1.multithreading_addition (m2, THREADS);

      const auto stop = std::chrono::high_resolution_clock::now();

      auto elapsed = (stop - start);

      std::cout << elapsed.count() << std::endl;
    }

  std::cout << "Scalar multiplication:"<< std::endl;

    for (int i: size)
    {

      Matrix <double> m1 (i, i);
      m1.randomise();

      Matrix <double> m2 (i, i);
      m2. randomise();

      const auto start = std::chrono::high_resolution_clock::now();

      Matrix <double> res1 = m1.multithreading_scalar (2, THREADS);

      const auto stop = std::chrono::high_resolution_clock::now();

      auto elapsed = (stop - start);

      std::cout << elapsed.count() << std::endl;
    }


  std::cout << "Matrix multiplication:"<<std::endl;

    for (int i: size)
    {

      Matrix <double> m1 (i, i);
      m1.randomise();

      Matrix <double> m2 (i, i);
      m2. randomise();

      const auto start = std::chrono::high_resolution_clock::now();

      Matrix <double> res1 = m1.multithreading_multiplication (m2, THREADS);

      const auto stop = std::chrono::high_resolution_clock::now();

      auto elapsed = (stop - start);

      std::cout << elapsed.count() << std::endl;
    }

    std::cout << "EQUAL NUMBERS OF THREADS 10" << std::endl;
    std::cout << "Addition:" << std::endl;
      for (int i: size)
      {

        Matrix <double> m1 (i, i);
        m1.randomise();

        Matrix <double> m2 (i, i);
        m2. randomise();

        const auto start = std::chrono::high_resolution_clock::now();

        Matrix <double> res1 = m1.multithreading_addition (m2, THREADS1);

        const auto stop = std::chrono::high_resolution_clock::now();

        auto elapsed = (stop - start);

      std::cout << elapsed.count() << std::endl;
      }

    std::cout << "Scalar multiplication:"<< std::endl;

      for (int i: size)
      {

        Matrix <double> m1 (i, i);
        m1.randomise();

        Matrix <double> m2 (i, i);
        m2. randomise();

        const auto start = std::chrono::high_resolution_clock::now();

        Matrix <double> res1 = m1.multithreading_scalar (2, THREADS1);

        const auto stop = std::chrono::high_resolution_clock::now();

        auto elapsed = (stop - start);

      std::cout << elapsed.count() << std::endl;
      }


    std::cout << "Matrix multiplication:"<<std::endl;

      for (int i: size)
      {

        Matrix <double> m1 (i, i);
        m1.randomise();

        Matrix <double> m2 (i, i);
        m2. randomise();

        const auto start = std::chrono::high_resolution_clock::now();

        Matrix <double> res1 = m1.multithreading_multiplication (m2, THREADS1);

        const auto stop = std::chrono::high_resolution_clock::now();

        auto elapsed = (stop - start);

      std::cout << elapsed.count() << std::endl;
      }

    /*std::cout << std::endl << "EQUAL SIZES OF MATRIXES 10" << std::endl;

    Matrix <double> m10 (10, 10);
    m10.randomise();

    std::cout << "Addition:" << std::endl;
    int summa10 [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int k = 0; k < 100; ++k)
    {
      for (int i = 1; i < 11; ++i)
      {

        const auto start = std::chrono::high_resolution_clock::now();

        Matrix <double> res1 = m10.multithreading_addition (m10, i);

        const auto stop = std::chrono::high_resolution_clock::now();

        auto elapsed = (stop - start);

        summa10[i-1] += elapsed.count();
      }
    }
    for (int i = 0; i < 10; ++i)
      std::cout << "Number of threads " << i+1 << ". Time is " << summa10[i]/100 << " ms"<< std::endl;

      std::cout << std::endl << "EQUAL SIZES OF MATRIXES 100" << std::endl;

      Matrix <double> m100 (100, 100);
      m100.randomise();

      std::cout << "Addition:" << std::endl;
      int summa100 [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      for (int k = 0; k < 100; ++k)
      {
        for (int i = 1; i < 11; ++i)
        {

          const auto start = std::chrono::high_resolution_clock::now();

          Matrix <double> res1 = m100.multithreading_addition (m100, i);

          const auto stop = std::chrono::high_resolution_clock::now();

          auto elapsed = (stop - start);

          summa100[i-1] += elapsed.count();
        }
      }
      for (int i = 0; i < 10; ++i)
        std::cout << "Number of threads " << i+1 << ". Time is " << summa100[i]/100 << " ms"<< std::endl;


    std::cout << std::endl << "EQUAL SIZES OF MATRIXES 500" << std::endl;

    Matrix <double> m500 (500, 500);
    m500.randomise();

    std::cout << "Addition:" << std::endl;
    int summa500 [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int k = 0; k < 100; ++k)
    {
      for (int i = 1; i < 11; ++i)
      {

        const auto start = std::chrono::high_resolution_clock::now();

        Matrix <double> res1 = m500.multithreading_addition (m500, i);

        const auto stop = std::chrono::high_resolution_clock::now();

        auto elapsed = (stop - start);

        summa500[i-1] += elapsed.count();
      }
    }
    for (int i = 0; i < 10; ++i)
      std::cout << "Number of threads " << i+1 << ". Time is " << summa500[i]/100 << " ms"<< std::endl;


        std::cout << std::endl << "EQUAL SIZES OF MATRIXES 1000" << std::endl;

        Matrix <double> m1000 (1000, 1000);
        m1000.randomise();

        std::cout << "Addition:" << std::endl;
        int summa1000 [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int k = 0; k < 100; ++k)
        {
          for (int i = 1; i < 11; ++i)
          {

            const auto start = std::chrono::high_resolution_clock::now();

            Matrix <double> res1 = m1000.multithreading_addition (m1000, i);

            const auto stop = std::chrono::high_resolution_clock::now();

            auto elapsed = (stop - start);

            summa1000[i-1] += elapsed.count();
          }
        }
        for (int i = 0; i < 10; ++i)
          std::cout << "Number of threads " << i+1 << ". Time is " << summa1000[i]/100 << " ms"<< std::endl;*/

  return 0;
}
