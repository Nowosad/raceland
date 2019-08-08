#include "colander.h"
using namespace Rcpp;

// gets values from a raster stack
// and ids based on values from a raster layer
// next creates a vector with values from a raster stack
// given by the raster layer id
NumericVector colander(NumericMatrix x, IntegerVector y){
  const int y_len = y.length();
  const int na = NA_INTEGER;

  NumericVector result(y_len);
  for (int i = 0; i < y_len; i++){
    int y_val = y(i);
    if (y_val == na){
      result[i] = NA_REAL;
    } else {
      // Rcout << "The value of y_val : " << y_val << "\n";
      result[i] = x(i, y_val - 1);
    }
  }
  return result;
}

/*** R
library(raster)
race_raster = readRDS("resources/AKTUALIZACJA/KOLORY/dane/example.rds")
real_raster = raster("resources/AKTUALIZACJA/KOLORY/dane/c29_r30_map2_60_60.tif")
x = race_raster[][c(1:3600), c(5, 2, 1, 3, 4)]
y = real_raster[][c(1:3600)]
pp = colander(x, y)
*/
