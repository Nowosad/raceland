#ifndef motifels_H
#define motifels_H
#include "Rcpp.h"

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
Rcpp::IntegerMatrix motifel_areas(Rcpp::IntegerMatrix x, int size);

// [[Rcpp::export]]
Rcpp::IntegerMatrix motifel_sums(Rcpp::IntegerMatrix x, int size);

// [[Rcpp::export]]
Rcpp::NumericMatrix motifel_adjustment(Rcpp::NumericMatrix x, Rcpp::NumericMatrix y);

// [[Rcpp::export]]
Rcpp::List motifel_to_grid(Rcpp::NumericMatrix x, Rcpp::NumericMatrix y, int size);

#endif // motifels_H
