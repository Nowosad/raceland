#' Create Weights
#'
#' @param x RasterStack with realizations
#' @param y RasterStack with shares
#' @param size size of a motifel
#' @param shift shift of a motifel
#'
#' @return a RasterStack
#' @export
#'
#' @examples
#' \dontrun{
#' library(raster)
#' real_raster = create_realization(perc_raster)
#' plot(real_raster)
#' output = create_weight(real_raster, perc_raster, size = 10)
#' output
#' plot(output)
#'
#' real_rasters = create_realizations(perc_raster, n = 5)
#' plot(real_rasters)
#' output2 = create_weights(real_rasters, perc_raster, size = 10)
#' output2
#' }
#'
create_weights = function(x, y, size, shift = NULL){
  if (missing(shift)){
    shift = size
  }
  out = if (requireNamespace("pbapply", quietly = TRUE)){
    raster::stack(pbapply::pblapply(raster::as.list(x), create_weight, y = y, size = size, shift = shift))
  } else {
    raster::stack(lapply(raster::as.list(x), create_weight, y = y, size = size, shift = shift))
  }
  return(out)
}

create_weight = function(x, y, size, shift){
  if (missing(shift)){
    shift = size
  }
  # x = real_raster; y = perc_raster; size = 10
  # x = cats; y = s; size = 2;
  w = calculate_weight(x, y, size = size, shift = shift)
  vals = motifel_to_grid(raster::as.matrix(x), w, size = size, shift = shift)

  raster_template = raster::raster(x)
  raster::setValues(raster_template, values = vals)
}
