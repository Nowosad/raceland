#' Convert zones to rasters
#'
#' @param v An sf object (POLYGON or MULTIPOLYGON)
#' @param resolution A numeric vector of length 1 or 2 to set the resolution
#' @param variables A character vector with columns names from `v`.
#' The values from these columns will be (1) rasterized and (2) recalculated to densities.
#' Each column will be represented as an layer in the output RasterStack
#' @param ... Additional arguments as for [terra::rasterize()]
#'
#' @return a SpatRaster
#' @export
#'
#' @examples
#' library(sf)
#' library(terra)
#' plot(pop_vector)
#' popdens_raster = zones_to_raster(pop_vector, resolution = 30,
#'                                  variables = c("ASIAN", "BLACK", "HISPANIC", "OTHER", "WHITE"))
#' plot(popdens_raster)
zones_to_raster = function(v, resolution, variables, ...){

  v_extent = terra::ext(v)
  v_crs = sf::st_crs(v)$wkt
  template_raster = terra::rast(v_extent,
                                   crs = v_crs,
                                   resolution = resolution)

  # template_raster = raster::raster(v,
  #                                  resolution = resolution)

  v$id = seq_len(nrow(v))
  # r_id = fasterize::fasterize(v, template_raster, field = "id", ...)
  r_id = terra::rasterize(terra::vect(v), template_raster, field = "id", ...)

  out = if (requireNamespace("pbapply", quietly = TRUE)){
    terra::rast(pbapply::pblapply(variables, zone_to_raster,
                                    v = v, resolution = resolution,
                                    id_raster = r_id, ...))
  } else {
    terra::rast(lapply(variables, zone_to_raster,
                         v = v, resolution = resolution,
                         id_raster = r_id, ...))
  }
}

zone_to_raster = function(variable, v, resolution, id_raster, ...){
  # recalculate densities
  freq_df = as.data.frame(terra::freq(id_raster))
  vals_df = sf::st_drop_geometry(v[c(variable, "id")])
  names(vals_df) = c("pop", "value")
  df = merge(freq_df, vals_df, by = "value", all.x = TRUE)
  df$density = df$pop / df$count
  # reclasiffy values by densities
  rc_mat = df[c("value", "density")]
  r = terra::classify(id_raster, rc_mat)
  names(r) = variable
  r
}

# zone_to_raster2 = function(variable, v, resolution, ...){
#   v[[variable]] = v[[variable]] / sf::st_area(v)
#   template_raster = raster::raster(v, resolution = resolution)
#   r = fasterize::fasterize(v, template_raster = template_raster, field = variable, fun = "last", ...)
#   names(r) = variable
#   r
# }
