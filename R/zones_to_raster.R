#' Convert zones to rasters
#'
#' @param v An sf object (POLYGON or MULTIPOLYGON)
#' @param resolution A numeric vector of length 1 or 2 to set the resolution
#' @param variables A character vector with columns names from `v`.
#' The values from these columns will be (1) recalculated to densities and then (2) rasterized.
#' Each column will be represented as an layer in the output RasterStack.
#' @param ... Additional arguments as for [fasterize::fasterize()]
#'
#' @return a RasterStack
#' @export
#'
#' @examples
#' library(sf)
#' library(raster)
#' plot(pop_vector)
#' popdens_raster = zones_to_raster(pop_vector, resolution = 100,
#'                                  variables = c("NHW", "NHB", "NHAS", "NHOTHER", "HISP"))
#' plot(popdens_raster)
zones_to_raster = function(v, resolution, variables, ...){
  out = if (requireNamespace("pbapply", quietly = TRUE)){
    raster::stack(pbapply::pblapply(variables, zone_to_raster,
                                    v = v, resolution = resolution))
  } else {
    raster::stack(lapply(variables, zone_to_raster,
                         v = v, resolution = resolution))
  }
}

zone_to_raster = function(variable, v, resolution, ...){
  v[[variable]] = v[[variable]] / sf::st_area(v)
  template_raster = raster::raster(v, resolution = resolution)
  r = fasterize::fasterize(v, template_raster, field = variable, fun = "last", ...)
  names(r) = variable
  r
}
