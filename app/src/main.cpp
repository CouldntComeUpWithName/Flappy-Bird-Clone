#include<iostream>
#include<binary_loader.h>

int main(int argc, char** argv)
{
  binary_loader loader;
  
  loader.load("../../app/res/file.bin"); // Here's how relative paths work in every dev. environment
  
  std::cout << loader.data() << std::endl;
  std::cin.get();
}