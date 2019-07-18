library(raceland)
library(raster)
library(dplyr)
library(sf)

load("data/race_raster.rda")

set.seed(22)
real_raster = create_realizations(race_raster, n = 5)

weig_raster = create_densities(real_raster, race_raster, size = 4)

metr_df = calculate_metrics(real_raster, weig_raster,
                            neighbourhood = 4, fun = "mean", size = 4)

grid_sf = create_grid(real_raster, size = 4)

dir.create("inst/results")
save(real_raster, file = "inst/results/real_raster.rda", compress = "bzip2")
save(weig_raster, file = "inst/results/weig_raster.rda", compress = "bzip2")
save(metr_df, file = "inst/results/metr_df.rda", compress = "bzip2")
save(grid_sf, file = "inst/results/grid_sf.rda", compress = "bzip2")
