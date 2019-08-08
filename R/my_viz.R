#' Title
#'
#' @param race_raster A
#' @param real_raster B
#' @param hex C
#'
#' @return D
#' @export
#'
#' @examples
#' library(raster)
#' hex_colors = c("#F16667", "#6EBE44", "#7E69AF", "#C77213","#F8DF1D")
#' real = create_realizations(race_raster, 1)
#' plot(race_raster)
#' plot(real)
#'
#' my_viz(race_raster, real, hex_colors)
my_viz = function(race_raster, real_raster, hex){

  df = cbind(data.frame(cat = seq_along(hex), t(plotwidgets::col2hsl(hex))))

  # prepare data
  cats = as.numeric(real_raster[])
  race_raster_mat = data.frame(id = seq_along(cats),
                               cat = cats)
  race_raster_mat$vals = colander(race_raster[], race_raster_mat$cat)

  race_raster_mat = merge(race_raster_mat, df, by = "cat", all.x = TRUE)

  # replace values below 5 percentile and above 95 percentile
  q5 = stats::quantile(race_raster_mat$vals, probs = 0.05, na.rm = TRUE)
  q95 = stats::quantile(race_raster_mat$vals, probs = 0.95, na.rm = TRUE)

  race_raster_mat$vals[race_raster_mat$vals <= q5] = q5
  race_raster_mat$vals[race_raster_mat$vals >= q95] = q95

  # calculate log
  # log or log1p?
  race_raster_mat$vals = log(race_raster_mat$vals)

  density_median = stats::median(race_raster_mat$vals, na.rm = TRUE)
  density_min = min(race_raster_mat$vals, na.rm = TRUE)
  density_max = max(race_raster_mat$vals, na.rm = TRUE)
  density_stats = c(density_min, density_median, density_max)

  # create linear models
  create_model_min = function(old_l){
    lightness = c(1, old_l)
    vals = density_stats[1:2]
    stats::lm(lightness ~ vals)
  }

  create_model_max = function(old_l){
    lightness = c(old_l, 0.35)
    vals = density_stats[2:3]
    stats::lm(lightness ~ vals)
  }

  l_model_min = lapply(df$L, create_model_min)
  l_model_max = lapply(df$L, create_model_max)
  recalc_l = function(x){
    group = unique(x$group)
    cat = unique(x$cat)
    if(group == 1){
      x$new_l = stats::predict(l_model_min[[cat]], newdata = x["vals"])
    } else if (group == 2){
      x$new_l = stats::predict(l_model_max[[cat]], newdata = x["vals"])
    }
    x
  }

  race_raster_mat$group = ifelse(race_raster_mat$vals < density_median, 1, 2)
  race_raster_mat = split(race_raster_mat, list(race_raster_mat$cat, race_raster_mat$group))
  race_raster_mat = race_raster_mat[lapply(race_raster_mat, nrow) > 0]
  race_raster_mat = do.call(rbind, lapply(race_raster_mat, recalc_l))
  race_raster_mat = cbind(race_raster_mat,
                          t(plotwidgets::hsl2rgb(t(as.matrix(race_raster_mat[c("H", "S", "new_l")])))))

  df_cols = data.frame(id = seq_along(cats))
  df_cols = merge(df_cols, race_raster_mat, by = "id", all.x = TRUE)

  rgb_rast = raster::stack(raster::setValues(real_raster, df_cols$R),
                           raster::setValues(real_raster, df_cols$G),
                           raster::setValues(real_raster, df_cols$B))

  raster::plotRGB(rgb_rast)
}
