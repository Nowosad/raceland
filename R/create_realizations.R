#' Create Realizations
#'
#' It constructs a high-resolution grid (a racial landscape) in which each cell contains only inhabitants of a single race.
#' Realization is constructed based on race-specific grids. Racial composition at each cell is translated to probabilities of drawing a person of a specific race from a cell.
#' Thus, the race label of a cell is a random variable. To obtain a stochastic realization of racial landscape, we use the cell's race probabilities and a random number generator to randomly assign specific race label to each cell (Monte Carlo procedure).
#'
#' @param x SpatRaster with race-specific population densities assign to each cell
#' @param n A number of realizations
#'
#' @return A SpatRaster object containing n realizations. Single race label in a racial landscape is assigned based on the order of race-specific grids in SpatRaster with input data (For example, the `race_raster` object has five layers named: asian, black, hispanic, other, white. The race labels in racial landscape raster will be 1 - asian, 2- black, 3 - hispanic, 4 - other, 5 - white).
#' @export
#'
#' @examples
#' library(terra)
#' race_raster = rast(system.file("extdata/race_raster.tif", package = "raceland"))
#' real = create_realizations(race_raster, 10)
#' plot(real)
#'
create_realizations = function(x, n){
  is_raster = check_is_raster(x)
  x = check_input(x, is_raster)
  # scale proportions
  x = x/sum(x)

  # fork does not work on windows
  # cl = parallel::makeForkCluster(4L)
  # raster::stack(lapply(1:n, function(i) create_realization(x)))
  out = if (requireNamespace("pbapply", quietly = TRUE)){
    terra::rast(pbapply::pbreplicate(n, create_realization(x)))
                                       # , cl = cl))
  } else {
    terra::rast(replicate(n, create_realization(x)))
  }
  # parallel::stopCluster(cl)
  return(check_output(out, is_raster))
}
create_realization = function(x){
  tmp_rst = terra::rast(ncols = terra::ncol(x), nrows = terra::nrow(x),
                        extent = terra::ext(x), crs = terra::crs(x),
                        res = terra::res(x))

  x = terra::values(x)
  names_cat = seq_len(ncol(x))
  v = draw_values(x, names_cat)
  tmp_rst = terra::setValues(tmp_rst, v)
  tmp_rst
}

# create_realizations2 = function(x, n){
#   a = parallel::mclapply(1:n, FUN = function(i) create_realization(x), mc.cores = 8)
#   raster::stack(a)
# }
# Rcpp::sourceCpp('src/draw_values.cpp')
# create_realizations2 = function(x, n){
#   oopts = options(future.globals.maxSize = +Inf)
#   on.exit(options(oopts))
#   raster::stack(future.apply::future_lapply(1:n, function(i) create_realization(x)), future.globals = FALSE)
# }
