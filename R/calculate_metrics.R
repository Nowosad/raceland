#' Calculate Metrics
#'
#' @param x RasterStack with realizations
#' @param w RasterStack with weights
#' @param neighbourhood 4/8
#' @param fun "mean", "geometric_mean", or "focal"
#' @param size size of a motifel
#' @param shift shift of a motifel
#' @param na_action "replace", "omit", "keep"
#' @param base the unit in which entropy is measured. The default is "log2", which compute entropy in "bits". "log" and "log10" can be also used
#' @param ordered the type of pairs considered. Either ordered (TRUE) or unordered (FALSE). The default is TRUE
#'
#' @return a data.frame
#' @export
#'
#' @examples
#' library(sd)
#' library(raster)
#' x = create_realizations(perc_raster, n = 5)
#' w = create_weights(x, perc_raster, size = 100)
#'
#' #1
#' df = calculate_metrics(x, w, neighbourhood = 4, fun = "mean")
#'
#' #2
#' df2 = calculate_metrics(x, w, neighbourhood = 4, fun = "mean", size = 100)
#' my_grid = create_grid(x, size = 100)
#' \dontrun{
#'  df3 = dplyr::filter(df2, realization == 2)
#'  result = dplyr::left_join(my_grid, df2, by = c("row", "col"))
#'  plot(result)
#' }
calculate_metrics = function(x, w, neighbourhood, fun, size = NULL, shift = NULL,
                             na_action = "replace", base = "log2", ordered = TRUE){
  if (is.null(size)){
    size = 0
  }
  if (missing(shift)){
    shift = size
  }
  # out = if (requireNamespace("pbapply", quietly = TRUE)){
  #   pbapply::pbmapply(calculate_metric, raster::as.list(x), raster::as.list(w), neighbourhood = neighbourhood,
  #                     fun = fun, size = size, na_action = na_action, base = base, ordered = ordered, SIMPLIFY = FALSE)
  # } else {
  out = mapply(calculate_metric, raster::as.list(x), raster::as.list(w), neighbourhood = neighbourhood,
           fun = fun, size = size, shift = shift, na_action = na_action, base = base, ordered = ordered, SIMPLIFY = FALSE)
  # }

  out = mapply(function(x, y) "[<-"(x, "realization", value = y), out, seq_along(out), SIMPLIFY = FALSE)
  out = do.call(rbind, out)
  out = out[c("realization", "row", "col", "ent", "joinent", "condent", "mutinf")]

  return(out)
}

calculate_metric = function(x, w, neighbourhood, fun, size = NULL, shift = NULL,
                            na_action = "replace", base = "log2", ordered = TRUE){
  if (is.null(size)){
    size = 0
  }
  if (missing(shift)){
    shift = size
  }
  df_metrics = get_metrics(x = raster::as.matrix(x), w = raster::as.matrix(w),
              directions = as.matrix(neighbourhood), fun = fun,
              na_action = na_action, base = base, ordered = ordered, size = size, shift = shift)
  as.data.frame(df_metrics)
}

