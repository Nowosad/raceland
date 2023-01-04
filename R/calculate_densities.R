#' Calculate Densities
#'
#' @param x SpatRaster with realizations
#' @param y SpatRaster with shares
#' @param window_size size of a local window
#'
#' @return a list of data.frames
#' @keywords internal
#'
#' @examples
#' library(terra)
#' race_raster = rast(system.file("extdata/race_raster.tif", package = "raceland"))
#' real_rasters = create_realizations(race_raster, n = 5)
#' plot(real_rasters)
#' d = raceland:::calculate_densities(real_rasters, race_raster, window_size = 10)
#'
calculate_densities = function(x, y, window_size){
  is_raster_x = check_is_raster(x)
  is_raster_y = check_is_raster(y)
  x = check_input(x, is_raster_x)
  y = check_input(y, is_raster_y)
  out = if (requireNamespace("pbapply", quietly = TRUE)){
      pbapply::pblapply(terra::as.list(x), calculate_density, y = y, window_size = window_size)
  } else {
      lapply(terra::as.list(x), calculate_density, y = y, window_size = window_size)
  }
  return(out)
}

# real_raster = create_realization(perc_raster)
# plot(real_raster)
# b = calculate_density(real_raster, perc_raster, window_size = 10)
calculate_density = function(x, y, window_size){
  # x = cats; y = s; size = 2
  x_areas = motifel_areas(x = terra::as.matrix(x[[1]], wide = TRUE), size = window_size)

  y_prep = lapply(terra::as.list(y), terra::as.matrix, wide = TRUE)

  y_sums = do.call(cbind, lapply(y_prep, motifel_sums, size = window_size))

  motifel_adjustment(x_areas, y_sums)
}
