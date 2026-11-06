#include <iostream>
#include <vector>
#include "uincampus/moyenne.hpp"
int main(){
  std::vector<double> n={12,15,10};
  std::vector<double> c={1,2,1};
  std::cout << "Moyenne ponderee: " << uincampus::moyenne_ponderee(n,c) << std::endl;
  return 0;
}
