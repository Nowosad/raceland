#include "get_metrics.h"
using namespace Rcpp;

NumericMatrix get_metrics(Rcpp::IntegerMatrix x,
                          Rcpp::NumericMatrix w,
                          const arma::imat directions,
                          const std::string fun,
                          const std::string na_action,
                          std::string base,
                          bool ordered,
                          int size,
                          int shift){

  if (size == 0){
    NumericMatrix result(1, 6);

    NumericMatrix wecoma = wecoma::rcpp_get_wecoma(x, w, directions, fun, na_action);

    double ent = rcpp_ent(wecoma, base);
    double joinent = rcpp_joinent(wecoma, base, ordered);
    double condent = rcpp_condent(wecoma, base, ordered);
    double mutinf = rcpp_mutinf(wecoma, base, ordered);

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

        NumericMatrix wecoma = wecoma::rcpp_get_wecoma(motifel_x, motifel_w, directions, fun, na_action);

        double ent = rcpp_ent(wecoma, base);
        double joinent = rcpp_joinent(wecoma, base, ordered);
        double condent = rcpp_condent(wecoma, base, ordered);
        double mutinf = rcpp_mutinf(wecoma, base, ordered);

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
library(sd)
library(raster)
x = create_realization(perc_raster)
w = create_weights(x, perc_raster, size = 10)

plot(w)
plot(x)

# sd::get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_action = "replace", base = "log2", ordered = TRUE, size = 0)
# sd::get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_action = "replace", base = "log2", ordered = FALSE, size = 0)
# sd::get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_action = "replace", base = "log2", ordered = FALSE, size = 100)

*/

