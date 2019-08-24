#' Create Densities
#'
#' Calculate local densities of subpopulations (race-specific local densities)
#'
#' @param x RasterStack with realizations
#' @param y RasterStack with shares of subpopulations
#' @param window_size Size, expressed in the number of cells, of a square-shaped local window for which local densities will be calculated; it is recommended to use the small window_size, i.e., 10
#'
#' @return a RasterStack containing n local densities. Local density layer is calculated for each realization
#' @export
#'
#' @examples
#' library(raster)
#' real_rasters = create_realizations(race_raster, n = 5)
#' plot(real_rasters)
#' dens_raster = create_densities(real_rasters, race_raster, window_size = 10)
#' dens_raster
#' plot(dens_raster)
#'
create_densities = function(x, y, window_size){
  if (!(methods::is(x, "RasterStack") || methods::is(x, "RasterBrick"))){
    stop("x needs to be either RasterStack or RasterBrick", call. = FALSE)
  }
  if (!(methods::is(y, "RasterStack") || methods::is(y, "RasterBrick"))){
    stop("y needs to be either RasterStack or RasterBrick", call. = FALSE)
  }
  out = if (requireNamespace("pbapply", quietly = TRUE)){
    raster::stack(pbapply::pblapply(raster::as.list(x), create_density, y = y, window_size = window_size))
  } else {
    raster::stack(lapply(raster::as.list(x), create_density, y = y, window_size = window_size))
  }
  return(out)
}

# real_raster = create_realization(perc_raster)
# plot(real_raster)
# output = create_density(real_raster, perc_raster, window_size = 10)
# output
# plot(output)
create_density = function(x, y, window_size){
  # x = real_raster; y = perc_raster; size = 10
  # x = cats; y = s; size = 2;
  w = calculate_density(x, y, window_size = window_size)
  vals = motifel_to_grid(raster::as.matrix(x[[1]]), w, size = window_size)

  raster_template = raster::raster(x)
  raster::setValues(raster_template, values = vals)
}
