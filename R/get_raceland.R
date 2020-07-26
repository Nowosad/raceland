#' Title
#'
#' @param x
#' @param n
#' @param window_size
#' @param neighbourhood
#' @param fun
#' @param size
#' @param shift
#' @param na_action
#' @param base
#' @param ordered
#' @param threshold
#'
#' @return
#' @export
#'
#' @examples
#' library(raster)
#' rl = get_raceland(race_raster, n = 10, window_size = 10, neighbourhood = 4, fun = "mean", size = 20)
get_raceland = function(x, n,
                        window_size,
                        neighbourhood = 4, fun,
                        size = NULL, shift = NULL,
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
  smr = aggregate(formula = cbind(ent, mutinf) ~ row + col,
                  data = metr_df,
                  FUN = function(x){
                    c(mean = mean(x))
                  })
  grid_sf = create_grid(realization_rasters, size = size)
  grid_attr = merge(grid_sf, smr, by = c("row", "col"), all.x = TRUE)
  grid_attr = na.omit(grid_attr)
  grid_attr
}
