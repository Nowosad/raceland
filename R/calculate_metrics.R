#' Title
#'
#' @param x
#' @param w
#' @param directions
#' @param fun
#' @param size
#' @param na_action
#' @param base
#' @param ordered
#'
#' @return
#' @export
#'
#' @examples
#' library(sd)
#' library(raster)
#' x = create_realization(perc_raster)
#' w = create_weights(x, perc_raster, size = 100)
#' df = calculate_metrics(x, w, neighbourhood = 4, fun = "mean")
#' df = calculate_metrics(x, w, neighbourhood = 4, fun = "mean", size = 100)
#' my_grid = create_grid(x, size = 100)
#' \dontrun{
#'  result = dplyr::left_join(my_grid, df, by = c("row", "col"))
#' }
calculate_metrics = function(x, w, neighbourhood, fun, size = NULL, na_action = "replace", base = "log2", ordered = TRUE){
  if (is.null(size)){
    size = 0
  }
  df_metrics = get_metrics(x = raster::as.matrix(x), w = raster::as.matrix(w),
              directions = as.matrix(neighbourhood), fun = fun,
              na_action = na_action, base = base, ordered = ordered, size = size)
  as.data.frame(df_metrics)
}

