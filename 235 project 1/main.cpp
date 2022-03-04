#include <iostream>
#include "GuestManager.h"
#include <vector>

int main() {
  std::cout << "Hello world" << std::endl;

  class GuestManager *manager = new GuestManager(4,5,4,8);
  delete manager;
  GuestManager *manager2 = new GuestManager(4,5,4,6);
  delete manager2;

  Guest *test45 = new class Businessman(Businessman, Standard, 2, 4);

  std::vector<int> test;
  test.push_back(3);
  test.push_back(5);
  test.pop_back();
  return 0;
}
