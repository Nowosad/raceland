#' Create Densities
#'
#' Calculate local densities of subpopulations (race-specific local densities)
#'
#' @param x SpatRaster with realizations
#' @param y SpatRaster with shares of subpopulations
#' @param window_size Size, expressed in the number of cells, of a square-shaped local window for which local densities will be calculated; it is recommended to use the small window_size, i.e., 10
#'
#' @return a SpatRaster containing n local densities. Local density layer is calculated for each realization
#' @export
#'
#' @examples
#' library(terra)
#' race_raster = rast(system.file("extdata/race_raster.tif", package = "raceland"))
#' real_rasters = create_realizations(race_raster, n = 5)
#' plot(real_rasters)
#' dens_raster = create_densities(real_rasters, race_raster, window_size = 10)
#' dens_raster
#' plot(dens_raster)
#'
create_densities = function(x, y, window_size){
  is_raster_x = check_is_raster(x)
  is_raster_y = check_is_raster(y)
  x = check_input(x, is_raster_x)
  y = check_input(y, is_raster_y)
  out = if (requireNamespace("pbapply", quietly = TRUE)){
    terra::rast(pbapply::pblapply(terra::as.list(x), create_density, y = y, window_size = window_size))
  } else {
    terra::rast(lapply(terra::as.list(x), create_density, y = y, window_size = window_size))
  }
  return(check_output(out, is_raster_x))
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
  vals = motifel_to_grid(terra::as.matrix(x[[1]], wide = TRUE), w, size = window_size)

  raster_template = terra::rast(x)
  terra::setValues(raster_template, values = vals)
}
