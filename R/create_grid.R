#' Create a grid of square-shaped windows
#'
#' @param x A RasterLayer/RasterStack/RasterBrick
#' @param size Expressed in the numbers of cells, is a length of the side of a square-shaped block of cells. It defines the extent of a local pattern. If `size=NULL` calculations are perfomed for the whole area
#' @param shift Defines the shift between adjacent squares of cells along with the N-S and W-E directions. It describes the density (resolution) of the output grid. The resolution of the output map will be reduced to the original resolution multiplied by the shift. If shift=size the input map will be divided into a grid of non-overlapping square windows. Each square window defines the extent of a local pattern. If shift < size - results in the grid of overlapping square windows.
#'
#' @return An sf polygon object
#' @export
#'
#' @examples
#' x = create_realizations(race_raster, 1)
#' y = create_grid(x, size = 10)
#' y
create_grid = function(x, size, shift = NULL){
  if (!(methods::is(x, "RasterStack") || methods::is(x, "RasterBrick"))){
    stop("x needs to be either RasterLayer, RasterStack or RasterBrick", call. = FALSE)
  }
  if (missing(shift)){
    shift = size
  }
  bb = sf::st_bbox(raster::extent(x))
  offset = bb[c("xmin", "ymax")]

  cellsize = c((size * raster::res(x)[1]), (size * raster::res(x)[2]))
  cellshift = c(((shift) * raster::res(x)[[1]]),
                ((shift) * raster::res(x)[[2]]))

  nx = ceiling(abs((bb[3] - offset[1]) / cellshift[1]))
  ny = ceiling(abs((bb[2] - offset[2]) / cellshift[2]))

  ret = vector("list", nx * ny)
  square = function(x1, y1, x2, y2){
    sf::st_polygon(list(matrix(c(x1, x2, x2, x1, x1, y1, y1, y2, y2, y1), 5)))
  }

  xc = offset[1] + (0:nx) * cellshift[1]
  yc = offset[2] - (0:ny) * cellshift[2]

  for (i in 1:nx){
    for (j in 1:ny){
      ret[[(j - 1) * nx + i]] = square(xc[i], yc[j], xc[i] + cellshift[1], yc[j] - cellshift[2])
    }
  }

  my_grid = sf::st_sf(geom = sf::st_sfc(ret, crs = sf::st_crs(x)))

  # if (raster::nlayers(x) == 1){
  #   df_ids = create_motifels_ids(raster::as.matrix(x), size, shift)
  # } else {
    df_ids = create_motifels_ids(raster::as.matrix(x[[1]]), size, shift)
  # }

  my_grid = cbind(df_ids, my_grid)
  colnames(my_grid) = c("row", "col", "geom")

  # my_grid$area = sf::st_area(my_grid)

  return(my_grid)
}
