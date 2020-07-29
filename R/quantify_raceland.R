#' Quantify a racial landscape
#'
#' This function is a wrapper of several steps (functions) implemented in the raceland package: `create_realizations()`, `create_densities()`, `calculate_metrics()`, and `create_grid()`.
#'
#' @param x RasterStack with race-specific population densities assign to each cell
#' @param n A number of realizations
#' @param window_size Size, expressed in the number of cells, of a square-shaped local window for which local densities will be calculated; it is recommended to use the small window_size, i.e., 10
#' @param neighbourhood The number of directions in which cell adjacencies are considered as neighbours: `4` (rook's case), `8` (queen's case). The default is `4`.
#' @param fun Function to calculate values from adjacent cells to contribute to exposure matrix, `"mean"` - calculate average values of local population densities from adjacent cells, `"geometric_mean"` - calculate geometric mean values of local population densities from adjacent cells, or `"focal"` assign value from the focal cell
#' @param size Expressed in the numbers of cells, is a length of the side of a square-shaped block of cells. It defines the extent of a local pattern. If `size=NULL` calculations are performed for a whole area
#' @param na_action Decides on how to behave in the presence of missing values in `w`. Possible options are `"replace"`, `"omit"`, `"keep"`. The default, `"replace"`, replaces missing values with 0, `"omit"` does not use cells with missing values, and `"keep"` keeps missing values.
#' @param base The unit in which entropy is measured. The default is "log2", which compute entropy in "bits". `"log"` and `"log10"` can be also used
#' @param ordered The type of pairs considered. Either ordered (`TRUE`) or unordered (`FALSE`). The default is `TRUE`
#' @param threshold The share of NA cells to allow metrics calculation in a square-shaped window
#'
#' @return An sf polygon object with five columns - `row` and `col` allowing for identification of each square polygon, `ent` - entropy measuring racial diversity, `mutinf` - mutual information, which is associated with measuring racial segregation, and `geometry` containing spatial geometries.
#' @export
#'
#' @examples
#' library(raster)
#' rl = quanfity_raceland(race_raster, n = 10, window_size = 10,
#'  neighbourhood = 4, fun = "mean", size = 20)
quanfity_raceland = function(x, n,
                        window_size,
                        neighbourhood = 4, fun,
                        size = NULL,
                        na_action = "replace", base = "log2",
                        ordered = TRUE, threshold = 0.5){

  realization_rasters = create_realizations(x = x, n = n)
  dens_raster = create_densities(x = realization_rasters,
                                 y = x,
                                 window_size = window_size)
  metr_df = calculate_metrics(x = realization_rasters,
                                 w = dens_raster,
                                 neighbourhood = neighbourhood,
                                 fun = fun,
                                 size = size,
                                 threshold = threshold)
  smr = stats::aggregate(formula = cbind(ent, mutinf) ~ row + col,
                  data = metr_df,
                  FUN = function(x){
                    c(mean = mean(x))
                  })
  grid_sf = create_grid(realization_rasters, size = size)
  grid_attr = merge(grid_sf, smr, by = c("row", "col"), all.x = TRUE)
  grid_attr = stats::na.omit(grid_attr)
  grid_attr
}
