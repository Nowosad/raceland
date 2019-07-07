#ifndef GET_METRICS_H
#define GET_METRICS_H
// [[Rcpp::depends(comat)]]
#include <comat.h>
#include "it_metrics.h"
#include "RcppArmadillo.h"
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
Rcpp::NumericMatrix get_metrics(Rcpp::IntegerMatrix x,
                          Rcpp::NumericMatrix w,
                          const arma::imat directions,
                          const std::string fun = "mean",
                          const std::string na_action = "replace",
                          std::string base = "log2",
                          bool ordered = true,
                          int size = 0,
                          int shift = 0);

#endif // GET_METRICS_H
