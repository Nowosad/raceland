#include "it_metrics.h"
using namespace Rcpp;

double rcpp_ent(const NumericMatrix x,
                std::string base){

  NumericVector com_c = colSums(x);
  double comp = comat::rcpp_get_entropy(com_c, base);
  return comp;
}

double rcpp_joinent(const NumericMatrix x,
                    std::string base,
                    bool ordered){

  NumericVector coh = comat::rcpp_get_wecove(x, ordered);

  double cplx = comat::rcpp_get_entropy(coh, base);
  return cplx;
}

double rcpp_condent(const NumericMatrix x,
                    std::string base,
                    bool ordered){

  double comp = rcpp_ent(x, base);
  double cplx = rcpp_joinent(x, base, ordered);

  double conf = cplx - comp;
  return conf;
}

double rcpp_mutinf(const NumericMatrix x,
                    std::string base,
                    bool ordered){

  double comp = rcpp_ent(x, base);
  double cplx = rcpp_joinent(x, base, ordered);

  double conf = cplx - comp;
  double aggr = comp - conf;
  return aggr;
}

/*** R
library(sd)
library(raster)
x = create_realization(perc_raster)
w = create_weights(x, perc_raster, size = 10)

plot(w)
plot(x)

a = comat::rcpp_get_wecoma(as.matrix(x), as.matrix(w), directions = as.matrix(4), fun = "mean", na_action = "replace")
# wecoma:::rcpp_get_wecove(a, ordered = FALSE)

rcpp_ent(a, base = "log2")
rcpp_joinent(a, base = "log2", ordered = TRUE)
rcpp_condent(a, base = "log2", ordered = TRUE)
rcpp_mutinf(a, base = "log2", ordered = FALSE)
*/
