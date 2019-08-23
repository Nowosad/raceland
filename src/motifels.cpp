#include "motifels.h"

using namespace Rcpp;

// calculates a numer of pixels of each category
// in each motifel
// motifels (rows)
// categories (columns)
IntegerMatrix motifel_areas(IntegerMatrix x, int size) {

  const int na = NA_INTEGER;

  std::vector<int> classes = comat::get_unique_values(x, true);
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

// calculates a sum of values of pixels
// in each motifel
// motifels (rows)
NumericMatrix motifel_sums(NumericMatrix x, int size) {

  // const double na = nan;

  int num_r = x.nrow();
  int num_c = x.ncol();

  // Rcout << "The value of x : \n" << x << "\n";

  int nr_of_motifels = 0;
  for (int i = 0; i < num_r; i = i + size) {
    for (int j = 0; j < num_c; j = j + size) {
      nr_of_motifels ++;
    }
  }

  NumericMatrix result(nr_of_motifels, 1);
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
      NumericMatrix motifel = x(Range(i, i_max), Range(j, j_max));
      // Rcout << "The value of motifel : \n" << motifel << "\n";

      for (int k = 0; k < motifel.length(); k++){
        const double tmp = motifel[k];
        // Rcout << "The value of tmp : \n" << tmp << "\n";
        // Rcout << "The value of na : \n" << na << "\n";

        if (std::isnan(tmp))
          continue;
        result(nr_of_motifels2, 0) = result(nr_of_motifels2, 0) + tmp;
      }
      nr_of_motifels2 ++;
    }
  }

  return(result);
}

// adjust values in the second matrix based on a missing values in the first one
NumericMatrix motifel_adjustment(NumericMatrix x, NumericMatrix y){

  // get input data dimensions
  int num_r = x.nrow();
  int num_c = x.ncol();

  // calculate how many values are left in each motifel
  // to be moved to different classes
  NumericMatrix missing_vals(num_r, 1);
  for (int i = 0; i < num_r; i++){
    for (int j = 0; j < num_c; j++){
      if (x(i, j) == 0){
        missing_vals(i, 0) = missing_vals(i, 0) + y(i, j);
        y(i, j) = 0;
      }
    }
  }
  //Rcpp::Rcout << "missing_vals: " << missing_vals << std::endl;

  // distribute leftover values in each motifel
  // to an existing classes
  NumericVector row_sums_y = rowSums(y);
  NumericVector tmp_y(num_c);
  int row_sums_y_len = row_sums_y.length();

  for (int i = 0; i < row_sums_y_len; i++) {
    tmp_y = y(i,_) / row_sums_y[i];
    y(i,_) = ((missing_vals(i, 0) * tmp_y) + y(i,_)) / x(i,_);
  }

  return y;
}

// redispose outputs of motifel_adjustment to a raster
NumericMatrix motifel_to_grid(IntegerMatrix x, NumericMatrix y, int size){

  const int na = NA_INTEGER;

  // get classes
  std::vector<int> classes = comat::get_unique_values(x, true);
  std::map<int, unsigned> class_index = get_class_index_map(classes);
  unsigned n_classes = class_index.size();
  // NAs need an index, otherwise they are counted as neighbors of class[0]
  class_index.insert(std::make_pair(na, n_classes));

  // calculate output dimensions
  // and create an output
  int num_r = x.nrow();
  int num_c = x.ncol();
  NumericMatrix result(num_r, num_c);
  std::fill(result.begin(), result.end(), NA_REAL);

  // for each motifel
  int m = 0;
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

      // fill the values
      // for each cell in each motifel
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
        }
      }
      m++;
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

race_a = raster(nrows = 4, ncols = 4,
                xmn = 0, xmx = 4, ymn = 0, ymx = 4,
                crs = NA,
                vals = c(NA, 2, 2, 1, NA, NA, 8, 6, 2, 6, 5, 1, NA, 0, 3, 0))

race_b = raster(nrows = 4, ncols = 4,
                xmn = 0, xmx = 4, ymn = 0, ymx = 4,
                crs = NA,
                vals = c(NA, 6, 7, 4, NA, NA, 0, 0, 1, 3, 2, 6, NA, 8, 7, 9))

race_c = raster(nrows = 4, ncols = 4,
                xmn = 0, xmx = 4, ymn = 0, ymx = 4,
                crs = NA,
                vals = c(NA, 2, 1, 5, NA, NA, 2, 4, 7, 1, 3, 3, NA, 2, 0, 1))

plot(cats)
a = motifel_areas(as.matrix(cats), 2, 2)
s = cbind(
  motifel_sums(as.matrix(race_a), 2, 2),
  motifel_sums(as.matrix(race_b), 2, 2),
  motifel_sums(as.matrix(race_c), 2, 2)
  )

# s2 = cbind(
#   motifel_sums(as.matrix(race_raster[[1]]), 20, 20),
#   motifel_sums(as.matrix(race_raster[[2]]), 20, 20),
#   motifel_sums(as.matrix(race_raster[[3]]), 20, 20),
#   motifel_sums(as.matrix(race_raster[[4]]), 20, 20),
#   motifel_sums(as.matrix(race_raster[[5]]), 20, 20)
# )

ma = motifel_adjustment(a, s)
# motifel_adjustment(x_areas, y_sums)
*/
