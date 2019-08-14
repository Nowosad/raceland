// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// colander
Rcpp::NumericVector colander(Rcpp::NumericMatrix x, Rcpp::IntegerVector y);
RcppExport SEXP _raceland_colander(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(colander(x, y));
    return rcpp_result_gen;
END_RCPP
}
// create_motifels
IntegerMatrix create_motifels(IntegerMatrix x, int size, int shift);
RcppExport SEXP _raceland_create_motifels(SEXP xSEXP, SEXP sizeSEXP, SEXP shiftSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type size(sizeSEXP);
    Rcpp::traits::input_parameter< int >::type shift(shiftSEXP);
    rcpp_result_gen = Rcpp::wrap(create_motifels(x, size, shift));
    return rcpp_result_gen;
END_RCPP
}
// create_motifels_ids
IntegerMatrix create_motifels_ids(IntegerMatrix x, int size, int shift);
RcppExport SEXP _raceland_create_motifels_ids(SEXP xSEXP, SEXP sizeSEXP, SEXP shiftSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type size(sizeSEXP);
    Rcpp::traits::input_parameter< int >::type shift(shiftSEXP);
    rcpp_result_gen = Rcpp::wrap(create_motifels_ids(x, size, shift));
    return rcpp_result_gen;
END_RCPP
}
// draw_values
Rcpp::IntegerVector draw_values(Rcpp::NumericMatrix x, Rcpp::IntegerVector y);
RcppExport SEXP _raceland_draw_values(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(draw_values(x, y));
    return rcpp_result_gen;
END_RCPP
}
// get_metrics
Rcpp::NumericMatrix get_metrics(Rcpp::IntegerMatrix x, Rcpp::NumericMatrix w, const arma::imat directions, const std::string fun, const std::string na_action, std::string base, bool ordered, int size, int shift, double na_threshold);
RcppExport SEXP _raceland_get_metrics(SEXP xSEXP, SEXP wSEXP, SEXP directionsSEXP, SEXP funSEXP, SEXP na_actionSEXP, SEXP baseSEXP, SEXP orderedSEXP, SEXP sizeSEXP, SEXP shiftSEXP, SEXP na_thresholdSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type w(wSEXP);
    Rcpp::traits::input_parameter< const arma::imat >::type directions(directionsSEXP);
    Rcpp::traits::input_parameter< const std::string >::type fun(funSEXP);
    Rcpp::traits::input_parameter< const std::string >::type na_action(na_actionSEXP);
    Rcpp::traits::input_parameter< std::string >::type base(baseSEXP);
    Rcpp::traits::input_parameter< bool >::type ordered(orderedSEXP);
    Rcpp::traits::input_parameter< int >::type size(sizeSEXP);
    Rcpp::traits::input_parameter< int >::type shift(shiftSEXP);
    Rcpp::traits::input_parameter< double >::type na_threshold(na_thresholdSEXP);
    rcpp_result_gen = Rcpp::wrap(get_metrics(x, w, directions, fun, na_action, base, ordered, size, shift, na_threshold));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_ent
double rcpp_ent(const Rcpp::NumericMatrix x, std::string base);
RcppExport SEXP _raceland_rcpp_ent(SEXP xSEXP, SEXP baseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string >::type base(baseSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_ent(x, base));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_joinent
double rcpp_joinent(const Rcpp::NumericMatrix x, std::string base, bool ordered);
RcppExport SEXP _raceland_rcpp_joinent(SEXP xSEXP, SEXP baseSEXP, SEXP orderedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string >::type base(baseSEXP);
    Rcpp::traits::input_parameter< bool >::type ordered(orderedSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_joinent(x, base, ordered));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_condent
double rcpp_condent(const Rcpp::NumericMatrix x, std::string base, bool ordered);
RcppExport SEXP _raceland_rcpp_condent(SEXP xSEXP, SEXP baseSEXP, SEXP orderedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string >::type base(baseSEXP);
    Rcpp::traits::input_parameter< bool >::type ordered(orderedSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_condent(x, base, ordered));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_mutinf
double rcpp_mutinf(const Rcpp::NumericMatrix x, std::string base, bool ordered);
RcppExport SEXP _raceland_rcpp_mutinf(SEXP xSEXP, SEXP baseSEXP, SEXP orderedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string >::type base(baseSEXP);
    Rcpp::traits::input_parameter< bool >::type ordered(orderedSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_mutinf(x, base, ordered));
    return rcpp_result_gen;
END_RCPP
}
// motifel_areas
Rcpp::IntegerMatrix motifel_areas(Rcpp::IntegerMatrix x, int size);
RcppExport SEXP _raceland_motifel_areas(SEXP xSEXP, SEXP sizeSEXP) {
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
Rcpp::NumericMatrix motifel_sums(Rcpp::NumericMatrix x, int size);
RcppExport SEXP _raceland_motifel_sums(SEXP xSEXP, SEXP sizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type size(sizeSEXP);
    rcpp_result_gen = Rcpp::wrap(motifel_sums(x, size));
    return rcpp_result_gen;
END_RCPP
}
// motifel_adjustment
Rcpp::NumericMatrix motifel_adjustment(Rcpp::NumericMatrix x, Rcpp::NumericMatrix y);
RcppExport SEXP _raceland_motifel_adjustment(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(motifel_adjustment(x, y));
    return rcpp_result_gen;
END_RCPP
}
// motifel_to_grid
Rcpp::NumericMatrix motifel_to_grid(Rcpp::IntegerMatrix x, Rcpp::NumericMatrix y, int size);
RcppExport SEXP _raceland_motifel_to_grid(SEXP xSEXP, SEXP ySEXP, SEXP sizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type y(ySEXP);
    Rcpp::traits::input_parameter< int >::type size(sizeSEXP);
    rcpp_result_gen = Rcpp::wrap(motifel_to_grid(x, y, size));
    return rcpp_result_gen;
END_RCPP
}
// na_prop
double na_prop(Rcpp::IntegerMatrix x);
RcppExport SEXP _raceland_na_prop(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::IntegerMatrix >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(na_prop(x));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_get_unique_values
std::vector<int> rcpp_get_unique_values(const Rcpp::IntegerVector& x, bool na_omit);
RcppExport SEXP _raceland_rcpp_get_unique_values(SEXP xSEXP, SEXP na_omitSEXP) {
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
    {"_raceland_colander", (DL_FUNC) &_raceland_colander, 2},
    {"_raceland_create_motifels", (DL_FUNC) &_raceland_create_motifels, 3},
    {"_raceland_create_motifels_ids", (DL_FUNC) &_raceland_create_motifels_ids, 3},
    {"_raceland_draw_values", (DL_FUNC) &_raceland_draw_values, 2},
    {"_raceland_get_metrics", (DL_FUNC) &_raceland_get_metrics, 10},
    {"_raceland_rcpp_ent", (DL_FUNC) &_raceland_rcpp_ent, 2},
    {"_raceland_rcpp_joinent", (DL_FUNC) &_raceland_rcpp_joinent, 3},
    {"_raceland_rcpp_condent", (DL_FUNC) &_raceland_rcpp_condent, 3},
    {"_raceland_rcpp_mutinf", (DL_FUNC) &_raceland_rcpp_mutinf, 3},
    {"_raceland_motifel_areas", (DL_FUNC) &_raceland_motifel_areas, 2},
    {"_raceland_motifel_sums", (DL_FUNC) &_raceland_motifel_sums, 2},
    {"_raceland_motifel_adjustment", (DL_FUNC) &_raceland_motifel_adjustment, 2},
    {"_raceland_motifel_to_grid", (DL_FUNC) &_raceland_motifel_to_grid, 3},
    {"_raceland_na_prop", (DL_FUNC) &_raceland_na_prop, 1},
    {"_raceland_rcpp_get_unique_values", (DL_FUNC) &_raceland_rcpp_get_unique_values, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_raceland(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
