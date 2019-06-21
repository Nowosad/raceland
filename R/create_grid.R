#' Title
#'
#' @param x
#' @param size
#'
#' @return
#' @export
#'
#' @examples
#' x = create_realization(perc_raster)
#' y = create_grid(x, size = 10)
#' y
create_grid = function(x, size){
  bb = sf::st_bbox(raster::extent(x))
  offset = bb[c("xmin", "ymin")]

  cellsize = c((size * raster::res(x)[1]), (size * raster::res(x)[2]))

  nx = ceiling((bb[3] - offset[1]) / cellsize[1])
  ny = ceiling((bb[4] - offset[2]) / cellsize[2])

  xc = offset[1] + (0:nx) * cellsize[1]
  yc = offset[2] + (0:ny) * cellsize[2]

  ret = vector("list", nx * ny)
  square = function(x1, y1, x2, y2){
    sf::st_polygon(list(matrix(c(x1, x2, x2, x1, x1, y1, y1, y2, y2, y1), 5)))
  }

  for (i in 1:nx){
    for (j in 1:ny){
      ret[[(j - 1) * nx + i]] = square(xc[i], yc[j], xc[i + 1], yc[j + 1])
    }
  }

  my_grid = sf::st_sf(geom  = sf::st_sfc(ret, crs = sf::st_crs(x)))

  if (raster::nlayers(x) == 1){
    df_ids = create_motifels_ids(raster::as.matrix(x), size)
  } else {
    df_ids = create_motifels_ids(raster::as.matrix(x[[1]]), size)
  }

  my_grid = cbind(df_ids, my_grid)
  colnames(my_grid) = c("row", "col", "geom")

  return(my_grid)
}
