#' Plot a Realization
#'
#' Displays realization taking into account also subpopulation density.
#'
#' @param x A RasterLayer or a RasterStack/RasterBrick with one layer.
#'   Each value should correspond to a layer in `y`.
#' @param y A RasterStack/RasterBrick with race-specific population densities
#' @param hex A character vector with colors specified in hexadecimal format.
#'   Each color should correspond to a layer in `y` and value in `x`.
#' @param ... Additional arguments as for [raster::plotRGB()]
#'
#' @export
#'
#' @examples
#' library(raster)
#' hex_colors = c("#F16667", "#6EBE44", "#7E69AF", "#C77213","#F8DF1D")
#' realization = create_realizations(race_raster, 1)
#' plot(race_raster)
#' plot(realization)
#'
#' plot_realization(realization, race_raster, hex = hex_colors)
plot_realization = function(x, y, hex, ...){
  if (!(methods::is(x, "RasterLayer") || methods::is(x, "RasterStack") || methods::is(x, "RasterBrick"))){
    stop("x needs to be either RasterLayer, RasterStack or RasterBrick", call. = FALSE)
  }
  if (raster::nlayers(x) != 1){
    stop("x needs have only one layer", call. = FALSE)
  }
  if (!(methods::is(y, "RasterStack") || methods::is(y, "RasterBrick"))){
    stop("y needs to be either RasterStack or RasterBrick", call. = FALSE)
  }
  if (length(hex) != raster::nlayers(y)){
    stop("Number of colors in hex should correspond to a number of layers in y", call. = FALSE)
  }
  if (!all.equal(dim(x)[c(1, 2)], dim(y)[c(1, 2)])){
    stop("x and y must have the same number of rows and columns", call. = FALSE)
  }

  min_l = 0.35

  # converts hex to HSL
  df = cbind(data.frame(cat = seq_along(hex), t(plotwidgets::col2hsl(hex))))
  # df = data.table::data.table(cbind(data.frame(cat = seq_along(hex), t(plotwidgets::col2hsl(hex)))))

  # extract density values for a given race
  cats = as.numeric(x[])
  y_mat = data.frame(id = seq_along(cats), cat = cats)
  # y_mat = data.table::data.table(data.frame(id = seq_along(cats), cat = cats))
  y_mat$vals = colander(y[], y_mat$cat)

  # add HSL
  y_mat = merge(y_mat, df, by = "cat", all.x = TRUE)
  # y_mat = merge(data.table::data.table(y_mat), data.table::data.table(df), by = "cat", all.x = TRUE)
  # y_mat = dplyr::left_join(y_mat, df, by = "cat")

  # replace values below 5 percentile and above 95 percentile
  q5 = stats::quantile(y_mat$vals, probs = 0.05, na.rm = TRUE)
  q95 = stats::quantile(y_mat$vals, probs = 0.95, na.rm = TRUE)

  y_mat$vals[y_mat$vals <= q5] = q5
  y_mat$vals[y_mat$vals >= q95] = q95

  # calculate log
  # log or log1p?
  y_mat$vals = log(y_mat$vals)
  y_mat$vals[is.infinite(y_mat$vals )] = NA

  # calculate density stats
  density_median = stats::median(y_mat$vals, na.rm = TRUE)
  density_min = min(y_mat$vals, na.rm = TRUE)
  density_max = max(y_mat$vals, na.rm = TRUE)
  density_stats = c(density_min, density_median, density_max)

  # create linear model for below median
  create_model_min = function(old_l){
    lightness = c(1, old_l)
    vals = density_stats[1:2]
    stats::lm(lightness ~ vals)
  }

  # create linear model for above median
  create_model_max = function(old_l, min_l){
    lightness = c(old_l, min_l)
    vals = density_stats[2:3]
    stats::lm(lightness ~ vals)
  }

  # calculate linear models
  l_model_min = lapply(df$L, create_model_min)
  l_model_max = lapply(df$L, create_model_max, min_l)

  # create a function to predict based on some properties (cat and density group)
  recalc_l = function(mat){
    group = unique(mat$group)
    cat = unique(mat$cat)
    if(group == 1){
      mat$new_l = stats::predict(l_model_min[[cat]], newdata = mat["vals"])
    } else if (group == 2){
      mat$new_l = stats::predict(l_model_max[[cat]], newdata = mat["vals"])
    }
    mat
  }

  # recalculates L
  y_mat$group = ifelse(y_mat$vals < density_median, 1, 2)
  y_mat = split(y_mat, list(y_mat$cat, y_mat$group))
  y_mat = y_mat[lapply(y_mat, nrow) > 0]
  y_mat = do.call(rbind, lapply(y_mat, recalc_l))

  # converts new HSL to RGB
  y_mat = cbind(y_mat, t(plotwidgets::hsl2rgb(t(as.matrix(y_mat[c("H", "S", "new_l")])))))

  # reconnects data to colors
  df_cols = data.frame(id = seq_along(cats))
  # df_cols = data.table::data.table(data.frame(id = seq_along(cats)))

  y_mat = merge(df_cols, y_mat, by = "id", all.x = TRUE)
  # y_mat = merge(data.table::data.table(df_cols), data.table::data.table(y_mat), by = "id", all.x = TRUE)
  # y_mat = dplyr::left_join(df_cols, y_mat, by = "id")

  # creates a raster stack
  rgb_rast = raster::stack(raster::setValues(x, y_mat$R),
                           raster::setValues(x, y_mat$G),
                           raster::setValues(x, y_mat$B))

  # plots
  raster::plotRGB(rgb_rast, r = 1, g = 2, b = 3, ...)
}

