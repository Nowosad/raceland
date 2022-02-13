library(raceland)
library(terra)
library(dplyr)
library(sf)

# fixes input data
# load("data/race_raster.rda")
# race_raster = terra::rast(race_raster)
# terra::crs(race_raster) = "ESRI:102003"
# race_raster = terra::wrap(race_raster)
# usethis::use_data(race_raster, overwrite = TRUE)
# writeRaster(race_raster, "inst/data/race_raster.tif", overwrite = TRUE)

# sf::st_crs(pop_vector) = "ESRI:102003"
# usethis::use_data(pop_vector, overwrite = TRUE)

race_raster = rast(system.file("data/race_raster.tif", package = "raceland"))
set.seed(22)
real_raster = create_realizations(race_raster, n = 5)

weig_raster = create_densities(real_raster, race_raster, window_size = 4)

metr_df = calculate_metrics(real_raster, weig_raster,
                            neighbourhood = 4, fun = "mean", size = 4)

grid_sf = create_grid(real_raster, size = 4)

popdens_raster = zones_to_raster(pop_vector, resolution = 30,
                                 variables = c("ASIAN", "BLACK", "HISPANIC", "OTHER", "WHITE"))


# hex_colors = c("#F16667", "#6EBE44", "#7E69AF", "#C77213","#F8DF1D")
# plot_realization(real_raster[[1]], race_raster, hex = hex_colors)

dir.create("inst/results")
save(real_raster, file = "inst/results/real_raster.rda", compress = "bzip2")
save(weig_raster, file = "inst/results/weig_raster.rda", compress = "bzip2")
save(metr_df, file = "inst/results/metr_df.rda", compress = "bzip2")
save(grid_sf, file = "inst/results/grid_sf.rda", compress = "bzip2")
save(popdens_raster, file = "inst/results/popdens_raster.rda", compress = "bzip2")
