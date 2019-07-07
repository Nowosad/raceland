library(sd)
library(raster)
library(dplyr)
library(sf)

load("data/prop_raster.rda")

set.seed(22)
real_raster = create_realizations(prop_raster, n = 5)

weig_raster = create_weights(real_raster, prop_raster, size = 100)

metr_df = calculate_metrics(real_raster, weig_raster,
                            neighbourhood = 4, fun = "mean", size = 100)

grid_sf = create_grid(real_raster, size = 100)

dir.create("tests/testthat/results")
save(real_raster, file = "tests/testthat/results/real_raster.rda", compress = "bzip2")
save(weig_raster, file = "tests/testthat/results/weig_raster.rda", compress = "bzip2")
save(metr_df, file = "tests/testthat/results/metr_df.rda", compress = "bzip2")
save(grid_sf, file = "tests/testthat/results/grid_sf.rda", compress = "bzip2")
