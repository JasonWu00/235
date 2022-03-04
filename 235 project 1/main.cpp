#include <iostream>
#include "GuestManager.h"
#include <vector>

//g++  -std=c++17  -Wall  main.cpp  GuestManager.cpp  -o test
//use the above to compile the program

int main() {
  std::cout << "Hello world" << std::endl;

  class GuestManager *manager = new GuestManager(4,5,4,8);
  delete manager;
  GuestManager *manager2 = new GuestManager(4,5,4,6);
  delete manager2;

  Guest *test45 = new class Businessman(GuestType::Businessman, RoomType::Standard, 2, 4);

  delete test45;

  return 0;
}
