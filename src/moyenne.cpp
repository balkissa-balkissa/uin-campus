#include "uincampus/moyenne.hpp"
namespace uincampus {
double moyenne_ponderee(const std::vector<double>& notes, const std::vector<double>& coeffs){
  double sum=0, sumCoeff=0;
  for(size_t i=0;i<notes.size();++i){ sum+=notes[i]*coeffs[i]; sumCoeff+=coeffs[i]; }
  return sumCoeff==0 ? 0 : sum/sumCoeff;
}
}
