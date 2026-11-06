#include <iostream>
#include <vector>
double moyenne_ponderee(const std::vector<double>& notes, const std::vector<double>& coeffs){
  double sum=0,sumCoeff=0;
  for(size_t i=0;i<notes.size();++i){ sum+=notes[i]*coeffs[i]; sumCoeff+=coeffs[i]; }
  return sum/sumCoeff;
}
int main(){
  std::vector<double> n={12,15,10}; std::vector<double> c={1,2,1};
  std::cout << "Moyenne ponderee: " << moyenne_ponderee(n,c) << std::endl;
  return 0;
}
