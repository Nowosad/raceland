#ifndef GET_METRICS_H
#define GET_METRICS_H
#include "it_metrics.h"
#include "na_prop.h"
#include "RcppArmadillo.h"
#include <comat.h>
// [[Rcpp::depends(comat)]]
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
Rcpp::NumericMatrix get_metrics(Rcpp::IntegerMatrix& x,
                          Rcpp::NumericMatrix& w,
                          const arma::imat& directions,
                          const std::string fun = "mean",
                          const std::string na_action = "replace",
                          std::string base = "log2",
                          bool ordered = true,
                          int size = 0,
                          int shift = 0,
                          double na_threshold = 0.5);

#endif // GET_METRICS_H
