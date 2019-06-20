#' Title
#'
#' @param x
#' @param size
#'
#' @return
#' @export
#'
#' @examples
#' y = create_grid(perc_raster, size = 100)
#' y
create_grid = function(x, size){
  bb = sf::st_bbox(raster::extent(x))
  offset = bb[c(1, 4)]
  nx = size
  ny = size
  xc = seq(offset[1], bb[3], length.out = nx + 1)
  yc = seq(offset[2], bb[2], length.out = ny + 1)

  ret = vector("list", nx * ny)
  square = function(x1, y1, x2, y2){
    sf::st_polygon(list(matrix(c(x1, x2, x2, x1, x1, y1, y1, y2, y2, y1), 5)))
  }
  for (i in 1:nx) {
    for (j in 1:ny) {
      ret[[(j - 1) * nx + i]] = square(xc[i], yc[j], xc[i + 1], yc[j + 1])
    }
  }

  my_grid = sf::st_sf(geometry = sf::st_sfc(ret, crs = sf::st_crs(x)))

  return(my_grid)
}



