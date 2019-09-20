#include <algorithm>
#include <utility>
#include <vector>
#include <Rcpp.h>

#include "cfitsio/fitsio.h"

using namespace Rcpp;

std::runtime_error fits_status_to_exception(const char *func_name, int status)
{
    char err_msg[30];
    fits_get_errstatus(status, err_msg);
    std::ostringstream os;
    os << "Error when invoking fits_" << func_name << ": " << err_msg;
    throw std::runtime_error(os.str());
}

/**
 * Utility function to convert FITS API call errors into exceptions.
 *
 * Notably, this doesn't work with fits_open_file as this name is actually
 * defined as a macro function, so it cannot be just passed around.
 */
template <typename F, typename ... Args>
void _fits_invoke(const char *func_name, F&& func, Args&& ... args)
{
  int status = 0;
  func(std::forward<Args>(args)..., &status);
  if (status) {
    throw fits_status_to_exception(func_name, status);
  }
}

fitsfile *fits_safe_open_file(const char *filename, int mode)
{
  int status = 0;
  fitsfile *file;
  fits_open_file(&file, const_cast<char *>(filename), mode, &status);
  if (status) {
    throw fits_status_to_exception("open_file", status);
  }
  return file;
}

#define fits_invoke(F, ...) _fits_invoke(#F, fits_ ## F, __VA_ARGS__)

std::vector<char *> to_string_vector(const Rcpp::CharacterVector &strings)
{
  std::vector<char *> c_strings(strings.size());
  std::transform(strings.begin(), strings.end(), c_strings.begin(),
                 [](const Rcpp::String &string) {
                   return const_cast<char *>(string.get_cstring());
                 }
  );
  return c_strings;
}

// [[Rcpp::export]]
SEXP Cfits_read_col(Rcpp::String filename, int colref=1, int ext=2){

  int hdutype,anynull,typecode,ii;
  long nrow,repeat,width;

  auto *fptr = fits_safe_open_file(filename.get_cstring(), READONLY);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  fits_invoke(get_num_rows, fptr, &nrow);
  fits_invoke(get_coltype, fptr, colref, &typecode, &repeat, &width);

  if ( typecode == TSTRING ) {
    int cwidth;
    fits_invoke(get_col_display_width, fptr, colref, &cwidth);

    char **data = (char **)malloc(sizeof(char *) * nrow);
    for (ii = 0 ; ii < nrow ; ii++ ) {
      data[ii] = (char*)calloc(cwidth + 1, 1);
    }
    fits_invoke(read_col, fptr, TSTRING, colref, 1, 1, nrow, nullptr, data, &anynull);
    Rcpp::StringVector out(nrow);
    std::copy(data, data + nrow, out.begin());
    for (int i = 0; i != nrow; i++) {
      free(data[i]);
    }
    free(data);
    fits_invoke(close_file, fptr);
    return out;
  }
  else if ( typecode == TBYTE ) {
    int nullval = 0;
    std::vector<Rbyte> col(nrow);
    fits_invoke(read_col, fptr, TBYTE, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::IntegerVector out(nrow);
    std::copy(col.begin(), col.end(), out.begin());
    fits_invoke(close_file, fptr);
    return out;
  }
  else if ( typecode == TINT ) {
    int nullval = -999;
    std::vector<int> col(nrow);
    fits_invoke(read_col, fptr, TINT, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::IntegerVector out(nrow);
    std::copy(col.begin(), col.end(), out.begin());
    fits_invoke(close_file, fptr);
    return out;
  }
  else if ( typecode == TUINT ) {
    unsigned int nullval = 0;
    std::vector<unsigned int> col(nrow);
    fits_invoke(read_col, fptr, TUINT, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::IntegerVector out(nrow);
    std::copy(col.begin(), col.end(), out.begin());
    fits_invoke(close_file, fptr);
    return out;
  }
  else if ( typecode == TINT32BIT ) {
    long nullval = 0;
    std::vector<long> col(nrow);
    fits_invoke(read_col, fptr, TINT32BIT, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::IntegerVector out(nrow);
    std::copy(col.begin(), col.end(), out.begin());
    fits_invoke(close_file, fptr);
    return out;
  }
  else if ( typecode == TSHORT ) {
    short nullval = -128;
    std::vector<short> col(nrow);
    fits_invoke(read_col, fptr, TSHORT, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::IntegerVector out(nrow);
    std::copy(col.begin(), col.end(), out.begin());
    fits_invoke(close_file, fptr);
    return out;
  }
  else if ( typecode == TUSHORT ) {
    unsigned short nullval = 255;
    std::vector<unsigned short> col(nrow);
    fits_invoke(read_col, fptr, TUSHORT, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::IntegerVector out(nrow);
    std::copy(col.begin(), col.end(), out.begin());
    fits_invoke(close_file, fptr);
    return out;
  }
  else if ( typecode == TFLOAT ) {
    float nullval = -999;
    std::vector<float> col(nrow);
    fits_invoke(read_col, fptr, TFLOAT, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::NumericVector out(nrow);
    std::copy(col.begin(), col.end(), out.begin());
    fits_invoke(close_file, fptr);
    return out;
  }
  else if ( typecode == TLONG ) {
    long nullval = -999;
    std::vector<long> col(nrow);
    fits_invoke(read_col, fptr, TLONG, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::NumericVector out(nrow);
    std::copy(col.begin(), col.end(), out.begin());
    fits_invoke(close_file, fptr);
    return out;
  }
  else if ( typecode == TLONGLONG ) {
    long nullval = -999;
    std::vector<int64_t> col(nrow);
    fits_invoke(read_col, fptr, TLONGLONG, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::NumericVector out(nrow);
    std::memcpy(&(out[0]), &(col[0]), nrow * sizeof(double));
    fits_invoke(close_file, fptr);
    out.attr("class") = "integer64";
    return out;
  }
  else if ( typecode == TDOUBLE ) {
    double nullval = -999;
    std::vector<double> col(nrow);
    fits_invoke(read_col, fptr, TDOUBLE, colref, 1, 1, nrow, &nullval, col.data(), &anynull);
    Rcpp::NumericVector out(nrow);
    std::copy(col.begin(), col.end(), out.begin());
    fits_invoke(close_file, fptr);
    return out;
  }

  throw std::runtime_error("unsupported type");
}

// [[Rcpp::export]]
int Cfits_read_nrow(Rcpp::String filename, int ext=2){
  int hdutype;
  long nrow;

  auto *fptr = fits_safe_open_file(filename.get_cstring(), READONLY);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  fits_invoke(get_num_rows, fptr, &nrow);
  fits_invoke(close_file, fptr);
  return nrow;
}

// [[Rcpp::export]]
int Cfits_read_ncol(Rcpp::String filename, int ext=2){
  int hdutype,ncol;

  auto *fptr = fits_safe_open_file(filename.get_cstring(), READONLY);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  fits_invoke(get_num_cols, fptr,&ncol);
  fits_invoke(close_file, fptr);
  return ncol;
}

// [[Rcpp::export]]
SEXP Cfits_read_colname(Rcpp::String filename, int colref=1, int ext=2){
  int hdutype, ncol;

  auto *fptr = fits_safe_open_file(filename.get_cstring(), READONLY);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  fits_invoke(get_num_cols, fptr, &ncol);

  Rcpp::StringVector out(ncol);

  char colname[81];

  int status = 0;
  int ii = 0;
  while ( status != COL_NOT_FOUND ) {
    fits_get_colname(fptr, CASEINSEN, (char *)"*", (char *)colname, &colref, &status);
    if (status != COL_NOT_FOUND) {
      out[ii] = colname;
    }
    ii++;
  }

  fits_invoke(close_file, fptr);
  return out;
}

// [[Rcpp::export]]
void Cfits_create_bintable(Rcpp::String filename, int tfields,
                         Rcpp::CharacterVector ttypes, Rcpp::CharacterVector tforms,
                         Rcpp::CharacterVector tunits, Rcpp::String extname)
{
  fitsfile *fptr;

  fits_invoke(create_file, &fptr, filename.get_cstring());
  fits_invoke(create_hdu, fptr);

  auto c_ttypes = to_string_vector(ttypes);
  auto c_tforms = to_string_vector(tforms);
  auto c_tunits = to_string_vector(tunits);
  fits_invoke(create_tbl, fptr, BINARY_TBL, 0, tfields,
              c_ttypes.data(), c_tforms.data(), c_tunits.data(),
              (char *)extname.get_cstring());
  fits_invoke(close_file, fptr);
}

// [[Rcpp::export]]
void Cfits_write_col(Rcpp::String filename, SEXP data, int nrow, int colref=1, int ext=2, int typecode=1){
  
  int hdutype,ii;

  auto *fptr = fits_safe_open_file(filename.get_cstring(), READWRITE);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);

  if ( typecode == TSTRING ) {
    std::vector<char *> s_data(nrow);
    for (ii = 0 ; ii < nrow ; ii++ ) {
      s_data[ii] = (char*)CHAR(STRING_ELT(data, ii));
    }
    fits_invoke(write_col, fptr, typecode, colref, 1, 1, nrow, s_data.data());
  }else if (typecode == TINT){
    fits_invoke(write_col, fptr, typecode, colref, 1, 1, nrow, INTEGER(data));
  }else if(typecode == TLONGLONG){
    fits_invoke(write_col, fptr, typecode, colref, 1, 1, nrow, REAL(data));
  }else if(typecode == TDOUBLE){
    fits_invoke(write_col, fptr, typecode, colref, 1, 1, nrow, REAL(data));
  }
  
  fits_invoke(close_file, fptr);
}

// int CFITS_API ffgkey(fitsfile *fptr, const char *keyname, char *keyval, char *comm,
//                      int *status);
// 
// int CFITS_API ffgky( fitsfile *fptr, int datatype, const char *keyname, void *value,
//                      char *comm, int *status);
// [[Rcpp::export]]
SEXP Cfits_read_key(Rcpp::String filename, Rcpp::String keyname, int typecode, int ext=1){
  int hdutype;
  
  auto *fptr = fits_safe_open_file(filename.get_cstring(), READWRITE);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  
  char comment[81];
  
  if ( typecode == TDOUBLE ) {
    Rcpp::NumericVector out(1);
    std::vector<double> keyvalue(1);
    fits_invoke(read_key, fptr, TDOUBLE, keyname.get_cstring(), keyvalue.data(), comment);
    std::copy(keyvalue.begin(), keyvalue.end(), out.begin());
    fits_invoke(close_file, fptr);
    return(out);
  }else if ( typecode == TSTRING){
    Rcpp::StringVector out(1);
    //std::vector<std::string> keyvalue(1);
    char keyvalue[81];
    fits_invoke(read_key, fptr, TSTRING, keyname.get_cstring(), keyvalue, comment);
    out[0] = keyvalue;
    //std::copy(keyvalue.begin(), keyvalue.end(), out.begin());
    fits_invoke(close_file, fptr);
    return(out);
  }
  throw std::runtime_error("unsupported type");
}

// [[Rcpp::export]]
void Cfits_update_key(Rcpp::String filename, SEXP keyvalue, Rcpp::String keyname, Rcpp::String comment, int ext=2, int typecode=1){
  int hdutype;
  
  auto *fptr = fits_safe_open_file(filename.get_cstring(), READWRITE);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  
  if ( typecode == TSTRING ) {
    char *s_keyvalue;
    s_keyvalue = (char*)CHAR(STRING_ELT(keyvalue, 0));
    fits_invoke(update_key, fptr, typecode, keyname.get_cstring(), s_keyvalue, comment.get_cstring());
  }else if (typecode == TINT){
    fits_invoke(update_key, fptr, typecode, keyname.get_cstring(), INTEGER(keyvalue), comment.get_cstring());
  }else if(typecode == TLONGLONG){
    fits_invoke(update_key, fptr, typecode, keyname.get_cstring(), REAL(keyvalue), comment.get_cstring());
  }else if(typecode == TDOUBLE){
    fits_invoke(update_key, fptr, typecode, keyname.get_cstring(), REAL(keyvalue), comment.get_cstring());
  }
  
  fits_invoke(close_file, fptr);
}

//fitsfile *fptr, int bitpix, int naxis, long *naxes, int *status
// BYTE_IMG      =   8   ( 8-bit byte pixels, 0 - 255)
//   SHORT_IMG     =  16   (16 bit integer pixels)
//   LONG_IMG      =  32   (32-bit integer pixels)
//   LONGLONG_IMG  =  64   (64-bit integer pixels)
//   FLOAT_IMG     = -32   (32-bit floating point pixels)
//   DOUBLE_IMG    = -64   (64-bit floating point pixels)
//fits_write_pix(fitsfile *fptr, int datatype, long *fpixel,
//               long nelements, void *array, int *status);
// [[Rcpp::export]]
void Cfits_create_image(Rcpp::String filename, int bitpix, long naxis1 , long naxis2)
{
  fitsfile *fptr;
  
  long naxes[] = {naxis1, naxis2};
  
  fits_invoke(create_file, &fptr, filename.get_cstring());
  fits_invoke(create_hdu, fptr);
  fits_invoke(create_img, fptr, bitpix, 2, naxes);
  fits_invoke(close_file, fptr);
}

// [[Rcpp::export]]
SEXP Cfits_read_img(Rcpp::String filename, int naxis1=100, int naxis2=100,
                                   int ext=1, int datatype=-32)
{
  int anynull, nullvals = 0, hdutype;
  
  fitsfile *fptr;
  fits_invoke(open_image, &fptr, filename.get_cstring(), READONLY);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  
  int npixels = naxis1 * naxis2;
  
  if (datatype==TFLOAT){
    std::vector<float> pixels(npixels);
    fits_invoke(read_img, fptr, datatype, 1, npixels, &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    NumericMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }else if (datatype==TDOUBLE){
    std::vector<double> pixels(npixels);
    fits_invoke(read_img, fptr, datatype, 1, npixels, &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    NumericMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }else if (datatype==TBYTE){
    std::vector<int> pixels(npixels);
    fits_invoke(read_img, fptr, datatype, 1, npixels, &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    IntegerMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }else if (datatype==TSHORT){
    std::vector<short> pixels(npixels);
    fits_invoke(read_img, fptr, datatype, 1, npixels, &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    IntegerMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }else if (datatype==TLONG){
    std::vector<long> pixels(npixels);
    fits_invoke(read_img, fptr, datatype, 1, npixels, &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    IntegerMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }
  throw std::runtime_error("unsupported type");
}

// [[Rcpp::export]]
void Cfits_write_image(Rcpp::String filename, SEXP data, int datatype, long naxis1 , long naxis2, int ext=1)
{
  int hdutype;
  long nelements = naxis1 * naxis2;
  long fpixel[] = {1, 1};
  
  auto *fptr = fits_safe_open_file(filename.get_cstring(), READWRITE);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  //below need to work for integers and doubles:
  if(datatype == TINT){
    fits_invoke(write_pix, fptr, datatype, fpixel, nelements, INTEGER(data));
  }else if(datatype == TSHORT){
    fits_invoke(write_pix, fptr, datatype, fpixel, nelements, INTEGER(data));
  }else if(datatype == TLONG){
    fits_invoke(write_pix, fptr, datatype, fpixel, nelements, INTEGER(data));
  }else if(datatype == TDOUBLE){
    fits_invoke(write_pix, fptr, datatype, fpixel, nelements, REAL(data));
  }else if(datatype == TFLOAT){
    fits_invoke(write_pix, fptr, datatype, fpixel, nelements, REAL(data));
  }
  fits_invoke(close_file, fptr);
}

// [[Rcpp::export]]
SEXP Cfits_read_header(Rcpp::String filename, int ext=1){
  int nkeys, keypos, ii, hdutype;
  fitsfile *fptr;
  fits_invoke(open_image, &fptr, filename.get_cstring(), READONLY);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  fits_invoke(get_hdrpos, fptr, &nkeys, &keypos);
  
  Rcpp::StringVector out(nkeys);
  char card[FLEN_CARD];
  
  for (ii = 1; ii <= nkeys; ii++)  {
    fits_invoke(read_record, fptr, ii, card);
    out[ii-1] = card;
  }
  fits_invoke(close_file, fptr);
  return(out);
}

// [[Rcpp::export]]
void Cfits_delete_HDU(Rcpp::String filename, int ext=1){
  int hdutype;
  fitsfile *fptr;
  fits_invoke(open_image, &fptr, filename.get_cstring(), READWRITE);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  fits_invoke(delete_hdu, fptr, &hdutype);
  fits_invoke(close_file, fptr);
}

// [[Rcpp::export]]
void Cfits_delete_key(Rcpp::String filename, Rcpp::String keyname, int ext=1){
  int hdutype;
  fitsfile *fptr;
  fits_invoke(open_image, &fptr, filename.get_cstring(), READWRITE);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  fits_invoke(delete_key, fptr, keyname.get_cstring());
  fits_invoke(close_file, fptr);
}

// [[Rcpp::export]]
void Cfits_delete_header(Rcpp::String filename, int ext=1){
  int hdutype, nkeys, keypos, ii;
  fitsfile *fptr;
  fits_invoke(open_image, &fptr, filename.get_cstring(), READWRITE);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  fits_invoke(get_hdrpos, fptr, &nkeys, &keypos);
  for (ii = 2; ii <= nkeys; ii++)  {
    Rcpp::Rcout << "The key is" << ii << std::endl;
    fits_invoke(delete_record, fptr, 2);
  }
  fits_invoke(close_file, fptr);
}

// [[Rcpp::export]]
SEXP Cfits_read_img_subset(Rcpp::String filename, long fpixel0=1, long fpixel1=100,
                           long lpixel0=1, long lpixel1=100, int ext=1, int datatype=-32)
{
  int anynull, nullvals = 0, hdutype;
  
  fitsfile *fptr;
  fits_invoke(open_image, &fptr, filename.get_cstring(), READONLY);
  fits_invoke(movabs_hdu, fptr, ext, &hdutype);
  
  long fpixel[] = {fpixel0, fpixel1};
  long lpixel[] = {lpixel0, lpixel1};
  
  int naxis1 = (lpixel[1] - fpixel[0] + 1);
  int naxis2 = (lpixel[1] - lpixel[0] + 1);
  int npixels = naxis1 * naxis2;
  long *inc= (long *)1;
  
  if (datatype==TFLOAT){
    std::vector<float> pixels(npixels);
    fits_invoke(read_subset, fptr, datatype, fpixel, lpixel, inc,
                  &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    NumericMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }else if (datatype==TDOUBLE){
    std::vector<double> pixels(npixels);
    fits_invoke(read_subset, fptr, datatype, fpixel, lpixel, inc,
                  &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    NumericMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }else if (datatype==TBYTE){
    std::vector<int> pixels(npixels);
    fits_invoke(read_subset, fptr, datatype, fpixel, lpixel, inc,
                  &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    IntegerMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }else if (datatype==TSHORT){
    std::vector<short> pixels(npixels);
    fits_invoke(read_subset, fptr, datatype, fpixel, lpixel, inc,
                  &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    IntegerMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }else if (datatype==TLONG){
    std::vector<long> pixels(npixels);
    fits_invoke(read_subset, fptr, datatype, fpixel, lpixel, inc,
                  &nullvals, pixels.data(), &anynull);
    fits_invoke(close_file, fptr);
    IntegerMatrix pixel_matrix(naxis1, naxis2);
    std::copy(pixels.begin(), pixels.end(), pixel_matrix.begin());
    return(pixel_matrix);
  }
  throw std::runtime_error("unsupported type");
}

//int fits_read_subset(fitsfile *fptr, int  datatype, long *fpixel,
//                     long *lpixel, long *inc, void *nulval,  void *array,
//                     int *anynul, int *status)
  
  
