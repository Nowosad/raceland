#include "get_metrics.h"
using namespace Rcpp;

NumericMatrix get_metrics(const Rcpp::IntegerMatrix x,
                          const Rcpp::NumericMatrix w,
                          const arma::imat directions,
                          const std::string fun,
                          const std::string na_action,
                          std::string base,
                          bool ordered){

  NumericMatrix result(1, 4);
  NumericMatrix wecoma = wecoma::rcpp_get_wecoma(x, w, directions, fun, na_action);

  double ent = rcpp_ent(wecoma, base);
  double joinent = rcpp_joinent(wecoma, base, ordered);
  double condent = rcpp_condent(wecoma, base, ordered);
  double mutinf = rcpp_mutinf(wecoma, base, ordered);

  result(0, 0) = ent;
  result(0, 1) = joinent;
  result(0, 2) = condent;
  result(0, 3) = mutinf;

  return result;
}


/*** R
library(sd)
library(raster)
x = create_realization(perc_raster)
w = create_weights(x, perc_raster, size = 10)

plot(w)
plot(x)

get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_action = "replace", base = "log2", ordered = TRUE)
get_metrics(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_action = "replace", base = "log2", ordered = FALSE)
*/

// IntegerMatrix motifel_areas(IntegerMatrix x, int size) {
//
//   const int na = NA_INTEGER;
//
//   std::vector<int> classes = rcpp_get_unique_values(x);
//   std::map<int, unsigned> class_index = get_class_index_map(classes);
//   unsigned n_classes = class_index.size();
//   class_index.insert(std::make_pair(na, n_classes));
//
//   int num_r = x.nrow();
//   int num_c = x.ncol();
//
//   int nr_of_motifels = 0;
//   for (int i = 0; i < num_r; i = i + size) {
//     for (int j = 0; j < num_c; j = j + size) {
//       nr_of_motifels ++;
//     }
//   }
//
//   IntegerMatrix result(nr_of_motifels, n_classes);
//   int nr_of_motifels2 = 0;
//
//   for (int i = 0; i < num_r; i = i + size){
//     for (int j = 0; j < num_c; j = j + size){
//       int i_max = i + (size - 1);
//       if (i_max >= num_r){
//         i_max = num_r - 1;
//       }
//       int j_max = j + (size - 1);
//       if (j_max >= num_c){
//         j_max = num_c - 1;
//       }
//
//       IntegerMatrix motifel = x(Range(i, i_max), Range(j, j_max));
//       // Rcout << "The value of motifel : \n" << motifel << "\n";
//
//       for (int k = 0; k < motifel.length(); k++){
//         // Rcout << "The value of k : \n" << k << "\n";
//         const int tmp = motifel[k];
//         if (tmp == na)
//           continue;
//         unsigned focal_class = class_index[tmp];
//         result(nr_of_motifels2, focal_class)++;
//       }
//       nr_of_motifels2 ++;
//     }
//   }
//
//   return(result);
// }

