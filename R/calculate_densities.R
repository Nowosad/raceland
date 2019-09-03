#' Calculate Densities
#'
#' @param x RasterStack with realizations
#' @param y RasterStack with shares
#' @param window_size size of a local window
#'
#' @return a list of data.frames
#' @keywords internal
#'
#' @examples
#' library(raster)
#' real_rasters = create_realizations(race_raster, n = 5)
#' plot(real_rasters)
#' d = raceland:::calculate_densities(real_rasters, race_raster, window_size = 10)
#'
calculate_densities = function(x, y, window_size){
  if (!(methods::is(x, "RasterStack") || methods::is(x, "RasterBrick"))){
    stop("x needs to be either RasterStack or RasterBrick", call. = FALSE)
  }
  if (!(methods::is(y, "RasterStack") || methods::is(y, "RasterBrick"))){
    stop("y needs to be either RasterStack or RasterBrick", call. = FALSE)
  }
  out = if (requireNamespace("pbapply", quietly = TRUE)){
      pbapply::pblapply(raster::as.list(x), calculate_density, y = y, window_size = window_size)
  } else {
      lapply(raster::as.list(x), calculate_density, y = y, window_size = window_size)
  }
  return(out)
}

# real_raster = create_realization(perc_raster)
# plot(real_raster)
# b = calculate_density(real_raster, perc_raster, window_size = 10)
calculate_density = function(x, y, window_size){
  # x = cats; y = s; size = 2
  x_areas = motifel_areas(x = raster::as.matrix(x[[1]]), size = window_size)

  y_prep = lapply(raster::as.list(y), raster::as.matrix)

  y_sums = do.call(cbind, lapply(y_prep, motifel_sums, size = window_size))

  motifel_adjustment(x_areas, y_sums)
}
