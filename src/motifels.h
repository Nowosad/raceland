#ifndef motifels_H
#define motifels_H
#include "Rcpp.h"

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
Rcpp::IntegerMatrix motifel_areas(Rcpp::IntegerMatrix x, int size, int shift);

// [[Rcpp::export]]
Rcpp::IntegerMatrix motifel_sums(Rcpp::IntegerMatrix x, int size, int shift);

// [[Rcpp::export]]
Rcpp::NumericMatrix motifel_adjustment(Rcpp::NumericMatrix x, Rcpp::NumericMatrix y);

// [[Rcpp::export]]
Rcpp::NumericMatrix motifel_to_grid(Rcpp::IntegerMatrix x, Rcpp::NumericMatrix y, int size, int shift);

#endif // motifels_H
