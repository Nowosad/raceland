#ifndef draw_values_H
#define draw_values_H
#include "Rcpp.h"

// [[Rcpp::export]]
Rcpp::IntegerVector draw_values(Rcpp::NumericMatrix x, Rcpp::IntegerVector y);

#endif // draw_values_H
