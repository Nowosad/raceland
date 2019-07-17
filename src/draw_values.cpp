#include "draw_values.h"
using namespace Rcpp;

IntegerVector draw_values(NumericMatrix x, IntegerVector y) {

  // get a number of cells
  int number_of_elements = x.nrow();

  // create random numbers
  NumericVector random_numbers = runif(number_of_elements);

  // create an output
  IntegerVector result(number_of_elements);

  // for each row (a vector of shares of several categories)
  // 1. calculate a row cumulative sum
  // 2. get random number
  // 3. if the values is NA set NA, else
  // 4. get a values above the random number threshold
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

/*** R
# race_raster = readRDS("example.rds")
# plot(race_raster)
#
# perc_raster = race_raster/sum(race_raster)
# names(perc_raster) = names(race_raster)
# perc_raster
#
# real_raster = create_realizations(perc_raster, n = 1)
# plot(real_raster)
*/
