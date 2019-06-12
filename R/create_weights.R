#' Title
#'
#' @param x
#' @param y
#' @param size
#'
#' @return
#' @export
#'
#' @examples
#' \dontrun{
#' library(raster)
#' real_raster = create_realization(perc_raster)
#' plot(real_raster)
#' output = create_weights(real_raster, perc_raster, size = 10)
#' output
#' plot(output)
#' }
create_weights = function(x, y, size){
  # x = real_raster; y = perc_raster; size = 10
  # x = cats; y = s; size = 2;
  w = calculate_weights(x, y, size = size)
  vals = motifel_to_grid(raster::as.matrix(x), w, size = size)

  raster_template = raster::raster(x)
  raster::setValues(raster_template, values = vals)
}


