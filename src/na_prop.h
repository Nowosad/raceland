#ifndef na_prop_H
#define na_prop_H
#include "RcppArmadillo.h"
#include <algorithm>     // for count_if
// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
double na_prop(Rcpp::IntegerMatrix x);

#endif // na_prop_H
