#' Create Realizations
#'
#' @param x RasterStack with shares
#' @param n number of realizations
#'
#' @return a RasterStack
#' @export
#'
#' @examples
#' \dontrun{
#' library(raster)
#' system.time({a = create_realization(perc_raster)})
#' plot(a)
#' system.time({b = create_realizations(perc_raster, 10)})
#' plot(b)
#' }

create_realizations = function(x, n){
  # fork does not work on windows
  # cl = parallel::makeForkCluster(4L)
  # raster::stack(lapply(1:n, function(i) create_realization(x)))
  out = if (requireNamespace("pbapply", quietly = TRUE)){
    raster::stack(pbapply::pbreplicate(n, create_realization(x)))
                                       # , cl = cl))
  } else {
    raster::stack(replicate(n, create_realization(x)))
  }
  # parallel::stopCluster(cl)
  return(out)
}

#' @export
create_realization = function(x){
  tmp_rst = raster::raster(ncols = raster::ncol(x), nrows = raster::nrow(x),
                           ext = raster::extent(x), crs = raster::crs(x),
                           res = raster::res(x))

  x = raster::getValues(x)
  names_cat = seq_len(ncol(x))
  v = draw_values(x, names_cat)
  tmp_rst = raster::setValues(tmp_rst, v)
  tmp_rst
}

# create_realizations2 = function(x, n){
#   a = parallel::mclapply(1:n, FUN = function(i) create_realization(x), mc.cores = 8)
#   raster::stack(a)
# }
# Rcpp::sourceCpp('src/draw_values.cpp')
# create_realizations2 = function(x, n){
#   oopts = options(future.globals.maxSize = +Inf)
#   on.exit(options(oopts))
#   raster::stack(future.apply::future_lapply(1:n, function(i) create_realization(x)), future.globals = FALSE)
# }
