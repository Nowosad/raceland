#ifndef motifels_H
#define motifels_H
// [[Rcpp::depends(comat)]]
#include <comat.h>

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
Rcpp::IntegerMatrix motifel_areas(Rcpp::IntegerMatrix x, int size);

// [[Rcpp::export]]
Rcpp::NumericMatrix motifel_sums(Rcpp::NumericMatrix x, int size);

// [[Rcpp::export]]
Rcpp::NumericMatrix motifel_adjustment(Rcpp::NumericMatrix x, Rcpp::NumericMatrix y);

// [[Rcpp::export]]
Rcpp::NumericMatrix motifel_to_grid(Rcpp::IntegerMatrix x, Rcpp::NumericMatrix y, int size);

#endif // motifels_H
