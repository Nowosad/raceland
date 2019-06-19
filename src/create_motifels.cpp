// using namespace Rcpp;
//
// IntegerMatrix create_motifels(IntegerMatrix x, int size) {
//
//   int num_r = x.nrow();
//   int num_c = x.ncol();
//
//   NumericMatrix result(num_r, num_c);
//   // std::fill(result.begin(), result.end(), NA_REAL);
//   int m = 0;
//   int m_row = 1;
//   int m_col = 1;
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
//       for (int ii = i; ii <= i_max; ii++){
//         for (int jj = j; jj <= j_max; jj++){
//           result(ii, jj) = y(m, focal_class);
//         }
//       }
//       m++;
//       m_col++;
//     }
//     m_row++;
//   }
//   return result;
// }


/*** R
library(raster)
cats = raster(nrows = 4, ncols = 4,
              xmn = 0, xmx = 4, ymn = 0, ymx = 4,
              crs = NA,
              vals = c(NA, 2, 2, 3, NA, NA, 1, 1, 3, 1, 1, 2, NA, 2, 2, 2))

plot(cats)
motifel_areas(as.matrix(cats), 2)
motifel_sums(as.matrix(cats), 2)
*/
