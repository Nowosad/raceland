// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// draw_values
Rcpp::IntegerVector draw_values(Rcpp::NumericMatrix x, Rcpp::IntegerVector y);
RcppExport SEXP _sd_draw_values(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(draw_values(x, y));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_sd_draw_values", (DL_FUNC) &_sd_draw_values, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_sd(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
