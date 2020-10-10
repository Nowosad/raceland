#include "get_metrics.h"
using namespace Rcpp;

NumericMatrix get_metrics(Rcpp::IntegerMatrix& x,
                          Rcpp::NumericMatrix& w,
                          const arma::imat& directions,
                          const std::string fun,
                          const std::string na_action,
                          std::string base,
                          bool ordered,
                          int size,
                          int shift,
                          double na_threshold){

  if (size == 0){
    NumericMatrix result(1, 6);

    double ent = NA_REAL;
    double joinent = NA_REAL;
    double condent = NA_REAL;
    double mutinf = NA_REAL;

    double na_perc = na_prop(x);

    if (na_perc <= na_threshold){

      NumericMatrix wecoma = comat::rcpp_get_wecoma(x, w, directions, fun, na_action);

      ent = comat::rcpp_ent(wecoma, base);
      joinent = comat::rcpp_joinent(wecoma, base, ordered);
      condent = comat::rcpp_condent(wecoma, base, ordered);
      mutinf = comat::rcpp_mutinf(wecoma, base, ordered);

    }
    result(0, 0) = 1;
    result(0, 1) = 1;
    result(0, 2) = ent;
    result(0, 3) = joinent;
    result(0, 4) = condent;
    result(0, 5) = mutinf;

    // add names
    colnames(result) = CharacterVector::create("row", "col", "ent", "joinent", "condent", "mutinf");
    return result;

  } else {
    int num_r = x.nrow();
    int num_c = x.ncol();

    int nr_of_motifels = 0;
    for (int i = 0; i < num_r; i = i + shift) {
      for (int j = 0; j < num_c; j = j + shift) {
        nr_of_motifels ++;
      }
    }

    NumericMatrix result(nr_of_motifels, 6);

    int nr_of_motifels2 = 0;
    int m_row = 1;
    int m_col = 1;

    for (int i = 0; i < num_r; i = i + shift){
      for (int j = 0; j < num_c; j = j + shift){
        result(nr_of_motifels2, 0) = m_row;
        result(nr_of_motifels2, 1) = m_col;

        int i_max = i + (size - 1);
        if (i_max >= num_r){
          i_max = num_r - 1;
        }
        int j_max = j + (size - 1);
        if (j_max >= num_c){
          j_max = num_c - 1;
        }

        IntegerMatrix motifel_x = x(Range(i, i_max), Range(j, j_max));
        NumericMatrix motifel_w = w(Range(i, i_max), Range(j, j_max));

        double ent = NA_REAL;
        double joinent = NA_REAL;
        double condent = NA_REAL;
        double mutinf = NA_REAL;

        double na_perc = na_prop(motifel_x);

        if (na_perc <= na_threshold){
          NumericMatrix wecoma = comat::rcpp_get_wecoma(motifel_x, motifel_w, directions, fun, na_action);

          ent = comat::rcpp_ent(wecoma, base);
          joinent = comat::rcpp_joinent(wecoma, base, ordered);
          condent = comat::rcpp_condent(wecoma, base, ordered);
          mutinf = comat::rcpp_mutinf(wecoma, base, ordered);
        }

        result(nr_of_motifels2, 2) = ent;
        result(nr_of_motifels2, 3) = joinent;
        result(nr_of_motifels2, 4) = condent;
        result(nr_of_motifels2, 5) = mutinf;

        nr_of_motifels2 ++;
        m_col++;
      }
      m_col = 1;
      m_row++;
    }
    // add names
    colnames(result) = CharacterVector::create("row", "col", "ent", "joinent", "condent", "mutinf");
    return result;
  }
}


/*** R
library(raceland)
library(raster)
x = create_realizations(perc_raster, n = 1)
w = create_densities(x, perc_raster, window_size = 10)

plot(w)
plot(x)

get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean")
get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_threshold = 0.9)
get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_threshold = 0.9, size = 100, shift = 100)

# bench::mark(
#   get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean"),
#   get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_threshold = 0.9),
#   get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_threshold = 0.9, size = 100, shift = 100),
#   iterations = 10,
#   check = FALSE
# )
#
# na_prop(as.matrix(x))

# sd::get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_action = "replace", base = "log2", ordered = TRUE, size = 0)
# sd::get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_action = "replace", base = "log2", ordered = FALSE, size = 0)
# sd::get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_action = "replace", base = "log2", ordered = FALSE, size = 100)

*/

