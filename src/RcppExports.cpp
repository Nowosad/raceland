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
// motifel_areas
Rcpp::IntegerMatrix motifel_areas(Rcpp::IntegerMatrix x, int size);
RcppExport SEXP _sd_motifel_areas(SEXP xSEXP, SEXP sizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type size(sizeSEXP);
    rcpp_result_gen = Rcpp::wrap(motifel_areas(x, size));
    return rcpp_result_gen;
END_RCPP
}
// motifel_sums
Rcpp::IntegerMatrix motifel_sums(Rcpp::IntegerMatrix x, int size);
RcppExport SEXP _sd_motifel_sums(SEXP xSEXP, SEXP sizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type size(sizeSEXP);
    rcpp_result_gen = Rcpp::wrap(motifel_sums(x, size));
    return rcpp_result_gen;
END_RCPP
}
// motifel_adjustment
Rcpp::NumericMatrix motifel_adjustment(Rcpp::NumericMatrix x, Rcpp::NumericMatrix y);
RcppExport SEXP _sd_motifel_adjustment(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(motifel_adjustment(x, y));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_get_unique_values
std::vector<int> rcpp_get_unique_values(const Rcpp::IntegerVector& x, bool na_omit);
RcppExport SEXP _sd_rcpp_get_unique_values(SEXP xSEXP, SEXP na_omitSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type na_omit(na_omitSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_get_unique_values(x, na_omit));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_sd_draw_values", (DL_FUNC) &_sd_draw_values, 2},
    {"_sd_motifel_areas", (DL_FUNC) &_sd_motifel_areas, 2},
    {"_sd_motifel_sums", (DL_FUNC) &_sd_motifel_sums, 2},
    {"_sd_motifel_adjustment", (DL_FUNC) &_sd_motifel_adjustment, 2},
    {"_sd_rcpp_get_unique_values", (DL_FUNC) &_sd_rcpp_get_unique_values, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_sd(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
