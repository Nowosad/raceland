#' Calculate Densities
#'
#' @param x RasterStack with realizations
#' @param y RasterStack with shares
#' @param size size of a motifel
#'
#' @return a list of data.frames
#' @keywords internal
#'
#' @examples
#' \dontrun{
#' library(raster)
#' real_rasters = create_realizations(race_raster, n = 5)
#' plot(real_rasters)
#' d = calculate_densities(real_rasters, race_raster, size = 10)
#' }
calculate_densities = function(x, y, size){
  if (!(methods::is(x, "RasterStack") || methods::is(x, "RasterBrick"))){
    stop("x needs to be either RasterStack or RasterBrick", call. = FALSE)
  }
  if (!(methods::is(y, "RasterStack") || methods::is(y, "RasterBrick"))){
    stop("y needs to be either RasterStack or RasterBrick", call. = FALSE)
  }
  out = if (requireNamespace("pbapply", quietly = TRUE)){
    # raster::stack(
      pbapply::pblapply(raster::as.list(x), calculate_density, y = y, size = size)
      # )
  } else {
    # raster::stack(
      lapply(raster::as.list(x), calculate_density, y = y, size = size)
      # )
  }
  return(out)
}

# real_raster = create_realization(perc_raster)
# plot(real_raster)
# b = calculate_density(real_raster, perc_raster, size = 10)
calculate_density = function(x, y, size){
  # x = cats; y = s; size = 2
  x_areas = motifel_areas(x = raster::as.matrix(x[[1]]), size = size)

  y_prep = lapply(raster::as.list(y), raster::as.matrix)

  y_sums = do.call(cbind, lapply(y_prep, motifel_sums, size = size))

  motifel_adjustment(x_areas, y_sums)
}
