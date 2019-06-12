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
  w = calculate_weights(x, y, size = size)
  b = motifel_to_grid(raster::as.matrix(x), w, size = size)

  raster_template = raster::raster(x)

  raster::stack(lapply(b, create_raster, raster_template))
}

create_raster = function(vals, raster_template){
  raster::setValues(raster_template, vals)
}

