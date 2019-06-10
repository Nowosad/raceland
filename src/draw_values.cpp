#include "draw_values.h"
using namespace Rcpp;

IntegerVector draw_values(NumericMatrix x, IntegerVector y) {
  int number_of_elements = x.nrow();
  NumericVector random_numbers = runif(number_of_elements);
  IntegerVector result(number_of_elements);
  for (int i = 0; i < number_of_elements; i++){
    NumericVector row_values = cumsum(x(i,_));
    double random_number = random_numbers[i];
    if (NumericVector::is_na(row_values[0])){
      result[i] = NA_INTEGER;
    } else {
      int j = 0;
      while(random_number > row_values[j]){
        j++;
      }
      result[i] = y[j];
    }
  }
  return result;
}
