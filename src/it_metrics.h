#ifndef IT_METRICS_H
#define IT_METRICS_H
#include <comat.h>
// [[Rcpp::depends(comat)]]
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
double rcpp_ent(const Rcpp::NumericMatrix x, std::string base = "log2");

// [[Rcpp::export]]
double rcpp_joinent(const Rcpp::NumericMatrix x,
                    std::string base = "log2",
                    bool ordered = true);

// [[Rcpp::export]]
double rcpp_condent(const Rcpp::NumericMatrix x,
                    std::string base = "log2",
                    bool ordered = true);

// [[Rcpp::export]]
double rcpp_mutinf(const Rcpp::NumericMatrix x,
                   std::string base = "log2",
                   bool ordered = true);

#endif // IT_METRICS_H
