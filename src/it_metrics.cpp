// [[Rcpp::depends(wecoma)]]
#include <RcppArmadillo.h>
#include <wecoma.h>
using namespace Rcpp;

double rcpp_ent(const NumericMatrix x,
                std::string base = "log2"){
  NumericVector com_c = colSums(x);
  double comp = wecoma::rcpp_get_entropy(com_c, base);
  return comp;
}

double rcpp_joinent(const NumericMatrix x,
                    std::string base = "log2",
                    bool ordered = TRUE){

  NumericVector coh = wecoma::rcpp_get_wecove(x, ordered);

  double cplx = wecoma::rcpp_get_entropy(coh, base);
  return cplx;
}

double rcpp_condent(const NumericMatrix x,
                    std::string base = "log2",
                    bool ordered = TRUE){

  double comp = rcpp_ent(x, base);
  double cplx = rcpp_joinent(x, base, ordered);

  double conf = cplx - comp;
  return conf;
}

double rcpp_mutinf(const NumericMatrix x,
                    std::string base = "log2",
                    bool ordered = TRUE){

  double comp = rcpp_ent(x, base);
  double cplx = rcpp_joinent(x, base, ordered);

  double conf = cplx - comp;
  double aggr = comp - conf;
  return aggr;
}
