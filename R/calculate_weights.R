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
#' b = calculate_weights(real_raster, perc_raster, size = 10)
#' }
calculate_weights = function(x, y, size){
  # x = cats; y = s; size = 2
  x_areas = motifel_areas(x = raster::as.matrix(x), size = size)

  y_prep = lapply(raster::as.list(y), raster::as.matrix)

  y_sums = do.call(cbind, lapply(y_prep, motifel_sums, size = size))

  motifel_adjustment(x_areas, y_sums)
}
