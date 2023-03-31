# load a reference objects ------------------------------------------------
load(system.file("results", "real_raster.rda", package = "raceland"))
load(system.file("results", "weig_raster.rda", package = "raceland"))
load(system.file("results", "metr_df.rda", package = "raceland"))
load(system.file("results", "grid_sf.rda", package = "raceland"))
load(system.file("results", "popdens_raster.rda", package = "raceland"))

# calculate new results ---------------------------------------------------
set.seed(22)
race_raster2 = raster::stack(race_raster)
real_raster2 = create_realizations(race_raster2, n = 5)

weig_raster2 = create_densities(real_raster2, race_raster2, window_size = 4)

metr_df2 = calculate_metrics(real_raster2, weig_raster2,
                            neighbourhood = 4, fun = "mean", size = 4)

grid_sf2 = create_grid(real_raster2, size = 4)

popdens_raster2 = zones_to_raster(pop_vector, resolution = 30,
                                  variables = c("ASIAN", "BLACK", "HISPANIC", "OTHER", "WHITE"))

# tests -------------------------------------------------------------------
expect_equivalent(real_raster2[], real_raster[])
names(weig_raster2) = names(weig_raster)
expect_equivalent(weig_raster2, weig_raster)
expect_equivalent(metr_df2, metr_df)
expect_equivalent(grid_sf2, grid_sf)
# expect_equivalent(popdens_raster2, popdens_raster)
