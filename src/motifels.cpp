#include "rcpp_get_unique_values.h"
#include "get_class_index_map.h"
using namespace Rcpp;

// [[Rcpp::export]]
IntegerMatrix motifel_areas(IntegerMatrix x, int size) {

  const int na = NA_INTEGER;

  std::vector<int> classes = rcpp_get_unique_values(x);
  std::map<int, unsigned> class_index = get_class_index_map(classes);
  unsigned n_classes = class_index.size();
  // NAs need an index, otherwise they are counted as neighbors of class[0]
  class_index.insert(std::make_pair(na, n_classes));

  int num_r = x.nrow();
  int num_c = x.ncol();

  int nr_of_motifels = 0;
  for (int i = 0; i < num_r; i = i + size) {
    for (int j = 0; j < num_c; j = j + size) {
      nr_of_motifels ++;
    }
  }

  IntegerMatrix result(nr_of_motifels, n_classes);
  int nr_of_motifels2 = 0;

  for (int i = 0; i < num_r; i = i + size){
    for (int j = 0; j < num_c; j = j + size){
      int i_max = i + (size - 1);
      if (i_max >= num_r){
        i_max = num_r - 1;
      }
      int j_max = j + (size - 1);
      if (j_max >= num_c){
        j_max = num_c - 1;
      }

      IntegerMatrix motifel = x(Range(i, i_max), Range(j, j_max));
      // Rcout << "The value of motifel : \n" << motifel << "\n";

      for (int k = 0; k < motifel.length(); k++){
        // Rcout << "The value of k : \n" << k << "\n";
        const int tmp = motifel[k];
        if (tmp == na)
          continue;
        unsigned focal_class = class_index[tmp];
        result(nr_of_motifels2, focal_class)++;
      }
      nr_of_motifels2 ++;
    }
  }

  return(result);
}

// [[Rcpp::export]]
IntegerMatrix motifel_sums(IntegerMatrix x, int size) {

  const int na = NA_INTEGER;

  int num_r = x.nrow();
  int num_c = x.ncol();

  int nr_of_motifels = 0;
  for (int i = 0; i < num_r; i = i + size) {
    for (int j = 0; j < num_c; j = j + size) {
      nr_of_motifels ++;
    }
  }

  IntegerMatrix result(nr_of_motifels, 1);
  int nr_of_motifels2 = 0;

  for (int i = 0; i < num_r; i = i + size){
    for (int j = 0; j < num_c; j = j + size){
      int i_max = i + (size - 1);
      if (i_max >= num_r){
        i_max = num_r - 1;
      }
      int j_max = j + (size - 1);
      if (j_max >= num_c){
        j_max = num_c - 1;
      }
      IntegerMatrix motifel = x(Range(i, i + (size - 1)), Range(j, j + (size - 1)));
      // Rcout << "The value of motifel : \n" << motifel << "\n";

      for (int k = 0; k < motifel.length(); k++){
        const int tmp = motifel[k];
        // Rcout << "The value of tmp : \n" << tmp << "\n";
        if (tmp == na)
          continue;
        result(nr_of_motifels2, 0) = result(nr_of_motifels2, 0) + tmp;
        // Rcout << "The value of result(nr_of_motifels2, 1) : \n" << result(nr_of_motifels2, 1) << "\n";
        // Rcout << "The value of nr_of_motifels2 : \n" << nr_of_motifels2 << "\n";
      }
      nr_of_motifels2 ++;

    }
  }

  return(result);
}

// [[Rcpp::export]]
NumericMatrix motifel_adjustment(NumericMatrix x, NumericMatrix y){

  int num_r = x.nrow();
  int num_c = x.ncol();

  NumericMatrix missing_vals(num_r, 1);

  for (int i = 0; i < num_r; i++){
    for (int j = 0; j < num_c; j++){
      if (x(i, j) == 0){
        missing_vals(i, 0) = missing_vals(i, 0) + y(i, j);
        y(i, j) = 0;
      }
    }
  }
  // return missing_vals;

  NumericVector row_sums_y = rowSums(y);
  // Rcpp::Rcout << "rowSum: " << row_sums_x << std::endl;
  NumericVector tmp_y(num_c);

  int row_sums_y_len = row_sums_y.length();

  for (int i = 0; i < row_sums_y_len; i++) {
    tmp_y = y(i,_) / row_sums_y[i];
    // Rcpp::Rcout << "y: " << tmp_y << std::endl;
    // Rcpp::Rcout << "mv: " << missing_vals << std::endl;
    y(i,_) = ((missing_vals(i, 0) * tmp_y) + y(i,_)) / x(i,_);
  }

  return y;
}


/*** R
library(raster)
cats = raster(nrows = 4, ncols = 4,
              xmn = 0, xmx = 4, ymn = 0, ymx = 4,
              crs = NA,
              vals = c(NA, 2, 2, 3, NA, NA, 1, 1, 3, 1, 1, 2, NA, 2, 2, 2))

plot(cats)
motifel_areas(as.matrix(cats), 2)
motifel_sums(as.matrix(cats), 2)
*/
