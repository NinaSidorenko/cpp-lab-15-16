#include <iostream>
#include "multmatrix.hpp"

int main()
{
  Matrix <double> m1 (3, 3);
  m1.randomise();
  std::cout << m1;

  Matrix <double> m2 (3, 4);
  m2. randomise();

  Matrix <double> m3 (3, 3);
  m3.randomise();


  Matrix <double> res1 = m1.multithreading_addition (m3);
  std::cout << res1;

  Matrix <double> res2 = m1.multithreading_addition (m3, 4);
  std::cout << res2;

  Matrix <double> res3 = m1.multithreading_substraction (m3);
  std::cout << res3;

  Matrix <double> res4 = m1.multithreading_substraction (m3, 4);
  std::cout << res4;

  Matrix <double> res5 = m2.multithreading_scalar (3);
  std::cout << res5;

  Matrix <double> res6 = m2.multithreading_scalar (4, 4);
  std::cout << res6;

  Matrix <double> res7 = m1.multithreading_multiplication (m2);
  std::cout << res7;

  Matrix <double> res8 = m1.multithreading_multiplication (m2, 4);
  std::cout << res8;

  double det = m1.multithreading_determ();
  std::cout << det << std::endl;

  Matrix <double> res9 = m1.multithreading_transpose();
  std::cout << res9;

  Matrix <double> res10 = m1.multithreading_transpose(2);
  std::cout << res10;

  Matrix <double> res11 = m1.multithreading_reverse();
  std::cout << res11;

  return 0;
}
