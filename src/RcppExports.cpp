// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// Cfits_read_col
SEXP Cfits_read_col(Rcpp::String filename, int colref, int ext);
RcppExport SEXP _Rfits_Cfits_read_col(SEXP filenameSEXP, SEXP colrefSEXP, SEXP extSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type colref(colrefSEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    rcpp_result_gen = Rcpp::wrap(Cfits_read_col(filename, colref, ext));
    return rcpp_result_gen;
END_RCPP
}
// Cfits_read_nrow
int Cfits_read_nrow(Rcpp::String filename, int ext);
RcppExport SEXP _Rfits_Cfits_read_nrow(SEXP filenameSEXP, SEXP extSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    rcpp_result_gen = Rcpp::wrap(Cfits_read_nrow(filename, ext));
    return rcpp_result_gen;
END_RCPP
}
// Cfits_read_ncol
int Cfits_read_ncol(Rcpp::String filename, int ext);
RcppExport SEXP _Rfits_Cfits_read_ncol(SEXP filenameSEXP, SEXP extSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    rcpp_result_gen = Rcpp::wrap(Cfits_read_ncol(filename, ext));
    return rcpp_result_gen;
END_RCPP
}
// Cfits_read_colname
SEXP Cfits_read_colname(Rcpp::String filename, int colref, int ext);
RcppExport SEXP _Rfits_Cfits_read_colname(SEXP filenameSEXP, SEXP colrefSEXP, SEXP extSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type colref(colrefSEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    rcpp_result_gen = Rcpp::wrap(Cfits_read_colname(filename, colref, ext));
    return rcpp_result_gen;
END_RCPP
}
// Cfits_create_bintable
void Cfits_create_bintable(Rcpp::String filename, int tfields, Rcpp::CharacterVector ttypes, Rcpp::CharacterVector tforms, Rcpp::CharacterVector tunits, Rcpp::String extname);
RcppExport SEXP _Rfits_Cfits_create_bintable(SEXP filenameSEXP, SEXP tfieldsSEXP, SEXP ttypesSEXP, SEXP tformsSEXP, SEXP tunitsSEXP, SEXP extnameSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type tfields(tfieldsSEXP);
    Rcpp::traits::input_parameter< Rcpp::CharacterVector >::type ttypes(ttypesSEXP);
    Rcpp::traits::input_parameter< Rcpp::CharacterVector >::type tforms(tformsSEXP);
    Rcpp::traits::input_parameter< Rcpp::CharacterVector >::type tunits(tunitsSEXP);
    Rcpp::traits::input_parameter< Rcpp::String >::type extname(extnameSEXP);
    Cfits_create_bintable(filename, tfields, ttypes, tforms, tunits, extname);
    return R_NilValue;
END_RCPP
}
// Cfits_write_col
void Cfits_write_col(Rcpp::String filename, SEXP data, int nrow, int colref, int ext, int typecode);
RcppExport SEXP _Rfits_Cfits_write_col(SEXP filenameSEXP, SEXP dataSEXP, SEXP nrowSEXP, SEXP colrefSEXP, SEXP extSEXP, SEXP typecodeSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    Rcpp::traits::input_parameter< int >::type nrow(nrowSEXP);
    Rcpp::traits::input_parameter< int >::type colref(colrefSEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    Rcpp::traits::input_parameter< int >::type typecode(typecodeSEXP);
    Cfits_write_col(filename, data, nrow, colref, ext, typecode);
    return R_NilValue;
END_RCPP
}
// Cfits_read_key
SEXP Cfits_read_key(Rcpp::String filename, Rcpp::String keyname, int typecode, int ext);
RcppExport SEXP _Rfits_Cfits_read_key(SEXP filenameSEXP, SEXP keynameSEXP, SEXP typecodeSEXP, SEXP extSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< Rcpp::String >::type keyname(keynameSEXP);
    Rcpp::traits::input_parameter< int >::type typecode(typecodeSEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    rcpp_result_gen = Rcpp::wrap(Cfits_read_key(filename, keyname, typecode, ext));
    return rcpp_result_gen;
END_RCPP
}
// Cfits_update_key
void Cfits_update_key(Rcpp::String filename, SEXP keyvalue, Rcpp::String keyname, Rcpp::String comment, int ext, int typecode);
RcppExport SEXP _Rfits_Cfits_update_key(SEXP filenameSEXP, SEXP keyvalueSEXP, SEXP keynameSEXP, SEXP commentSEXP, SEXP extSEXP, SEXP typecodeSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< SEXP >::type keyvalue(keyvalueSEXP);
    Rcpp::traits::input_parameter< Rcpp::String >::type keyname(keynameSEXP);
    Rcpp::traits::input_parameter< Rcpp::String >::type comment(commentSEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    Rcpp::traits::input_parameter< int >::type typecode(typecodeSEXP);
    Cfits_update_key(filename, keyvalue, keyname, comment, ext, typecode);
    return R_NilValue;
END_RCPP
}
// Cfits_create_image
void Cfits_create_image(Rcpp::String filename, int bitpix, long naxis1, long naxis2);
RcppExport SEXP _Rfits_Cfits_create_image(SEXP filenameSEXP, SEXP bitpixSEXP, SEXP naxis1SEXP, SEXP naxis2SEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type bitpix(bitpixSEXP);
    Rcpp::traits::input_parameter< long >::type naxis1(naxis1SEXP);
    Rcpp::traits::input_parameter< long >::type naxis2(naxis2SEXP);
    Cfits_create_image(filename, bitpix, naxis1, naxis2);
    return R_NilValue;
END_RCPP
}
// Cfits_read_img
Rcpp::NumericMatrix Cfits_read_img(Rcpp::String filename, int naxis1, int naxis2, int ext);
RcppExport SEXP _Rfits_Cfits_read_img(SEXP filenameSEXP, SEXP naxis1SEXP, SEXP naxis2SEXP, SEXP extSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type naxis1(naxis1SEXP);
    Rcpp::traits::input_parameter< int >::type naxis2(naxis2SEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    rcpp_result_gen = Rcpp::wrap(Cfits_read_img(filename, naxis1, naxis2, ext));
    return rcpp_result_gen;
END_RCPP
}
// Cfits_write_image
void Cfits_write_image(Rcpp::String filename, SEXP data, int datatype, long naxis1, long naxis2, int ext);
RcppExport SEXP _Rfits_Cfits_write_image(SEXP filenameSEXP, SEXP dataSEXP, SEXP datatypeSEXP, SEXP naxis1SEXP, SEXP naxis2SEXP, SEXP extSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< SEXP >::type data(dataSEXP);
    Rcpp::traits::input_parameter< int >::type datatype(datatypeSEXP);
    Rcpp::traits::input_parameter< long >::type naxis1(naxis1SEXP);
    Rcpp::traits::input_parameter< long >::type naxis2(naxis2SEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    Cfits_write_image(filename, data, datatype, naxis1, naxis2, ext);
    return R_NilValue;
END_RCPP
}
// Cfits_read_header
SEXP Cfits_read_header(Rcpp::String filename, int ext);
RcppExport SEXP _Rfits_Cfits_read_header(SEXP filenameSEXP, SEXP extSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type ext(extSEXP);
    rcpp_result_gen = Rcpp::wrap(Cfits_read_header(filename, ext));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_Rfits_Cfits_read_col", (DL_FUNC) &_Rfits_Cfits_read_col, 3},
    {"_Rfits_Cfits_read_nrow", (DL_FUNC) &_Rfits_Cfits_read_nrow, 2},
    {"_Rfits_Cfits_read_ncol", (DL_FUNC) &_Rfits_Cfits_read_ncol, 2},
    {"_Rfits_Cfits_read_colname", (DL_FUNC) &_Rfits_Cfits_read_colname, 3},
    {"_Rfits_Cfits_create_bintable", (DL_FUNC) &_Rfits_Cfits_create_bintable, 6},
    {"_Rfits_Cfits_write_col", (DL_FUNC) &_Rfits_Cfits_write_col, 6},
    {"_Rfits_Cfits_read_key", (DL_FUNC) &_Rfits_Cfits_read_key, 4},
    {"_Rfits_Cfits_update_key", (DL_FUNC) &_Rfits_Cfits_update_key, 6},
    {"_Rfits_Cfits_create_image", (DL_FUNC) &_Rfits_Cfits_create_image, 4},
    {"_Rfits_Cfits_read_img", (DL_FUNC) &_Rfits_Cfits_read_img, 4},
    {"_Rfits_Cfits_write_image", (DL_FUNC) &_Rfits_Cfits_write_image, 6},
    {"_Rfits_Cfits_read_header", (DL_FUNC) &_Rfits_Cfits_read_header, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_Rfits(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
