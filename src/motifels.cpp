#include "motifels.h"
#include "rcpp_get_unique_values.h"
#include "get_class_index_map.h"

using namespace Rcpp;

IntegerMatrix motifel_areas(IntegerMatrix x, int size, int shift) {

  const int na = NA_INTEGER;

  std::vector<int> classes = rcpp_get_unique_values(x);
  std::map<int, unsigned> class_index = get_class_index_map(classes);
  unsigned n_classes = class_index.size();
  // NAs need an index, otherwise they are counted as neighbors of class[0]
  class_index.insert(std::make_pair(na, n_classes));

  int num_r = x.nrow();
  int num_c = x.ncol();

  int nr_of_motifels = 0;
  for (int i = 0; i < num_r; i = i + shift) {
    for (int j = 0; j < num_c; j = j + shift) {
      nr_of_motifels ++;
    }
  }

  IntegerMatrix result(nr_of_motifels, n_classes);
  int nr_of_motifels2 = 0;

  for (int i = 0; i < num_r; i = i + shift){
    for (int j = 0; j < num_c; j = j + shift){
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

IntegerMatrix motifel_sums(IntegerMatrix x, int size, int shift) {

  const int na = NA_INTEGER;

  int num_r = x.nrow();
  int num_c = x.ncol();

  int nr_of_motifels = 0;
  for (int i = 0; i < num_r; i = i + shift) {
    for (int j = 0; j < num_c; j = j + shift) {
      nr_of_motifels ++;
    }
  }

  IntegerMatrix result(nr_of_motifels, 1);
  int nr_of_motifels2 = 0;

  for (int i = 0; i < num_r; i = i + shift){
    for (int j = 0; j < num_c; j = j + shift){
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
  // Rcpp::Rcout << "y: " << y << std::endl;
  NumericVector row_sums_y = rowSums(y);
  // Rcpp::Rcout << "rowSum: " << row_sums_y << std::endl;
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

NumericMatrix motifel_to_grid(IntegerMatrix x, NumericMatrix y, int size, int shift){

  const int na = NA_INTEGER;

  std::vector<int> classes = rcpp_get_unique_values(x);
  std::map<int, unsigned> class_index = get_class_index_map(classes);
  unsigned n_classes = class_index.size();
  // NAs need an index, otherwise they are counted as neighbors of class[0]
  class_index.insert(std::make_pair(na, n_classes));

  // int num_c_y = y.ncol();
  // int num_r_y = y.nrow();

  int num_r = x.nrow();
  int num_c = x.ncol();

  NumericMatrix result(num_r, num_c);
  std::fill(result.begin(), result.end(), NA_REAL);
  int m = 0;
  for (int i = 0; i < num_r; i = i + shift){
    for (int j = 0; j < num_c; j = j + shift){
      int i_max = i + (size - 1);
      if (i_max >= num_r){
        i_max = num_r - 1;
      }
      int j_max = j + (size - 1);
      if (j_max >= num_c){
        j_max = num_c - 1;
      }

      for (int ii = i; ii <= i_max; ii++){
        for (int jj = j; jj <= j_max; jj++){
          // Rcout << "The value of ii : \n" << ii << "\n";
          // Rcout << "The value of jj : \n" << jj << "\n";
          const int tmp = x(ii, jj);
          if (tmp == na)
            continue;
          unsigned focal_class = class_index[tmp];
          // Rcout << "The value of tmp : \n" << tmp << "\n";
          // Rcout << "The value of focal_class : \n" << focal_class << "\n";
          result(ii, jj) = y(m, focal_class);
          // Rcout << "The value of y : \n" << y << "\n";
          // r(ii, jj) = y(m, l);
        }
      }
      m++;
      // Rcout << "The value of m : \n" << m << "\n";
    }
  }
  return result;
}


/*** R
library(raster)
cats = raster(nrows = 4, ncols = 4,
              xmn = 0, xmx = 4, ymn = 0, ymx = 4,
              crs = NA,
              vals = c(NA, 2, 2, 3, NA, NA, 1, 1, 3, 1, 1, 2, NA, 2, 2, 2))

plot(cats)
motifel_areas(as.matrix(cats), 2, 2)
motifel_sums(as.matrix(cats), 2)
*/
