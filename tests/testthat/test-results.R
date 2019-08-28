# load a reference objects ------------------------------------------------
load(system.file("results", "real_raster.rda", package = "raceland"))
load(system.file("results", "weig_raster.rda", package = "raceland"))
load(system.file("results", "metr_df.rda", package = "raceland"))
load(system.file("results", "grid_sf.rda", package = "raceland"))
load(system.file("results", "popdens_raster.rda", package = "raceland"))

# calculate new results ---------------------------------------------------
set.seed(22)
real_raster2 = create_realizations(race_raster, n = 5)

weig_raster2 = create_densities(real_raster, race_raster, window_size = 4)

metr_df2 = calculate_metrics(real_raster, weig_raster,
                            neighbourhood = 4, fun = "mean", size = 4)

grid_sf2 = create_grid(real_raster, size = 4)

popdens_raster2 = zones_to_raster(pop_vector, resolution = 30,
                                  variables = c("ASIAN", "BLACK", "HISPANIC", "OTHER", "WHITE"))

# tests -------------------------------------------------------------------
expect_equal(real_raster2, real_raster)
expect_equal(weig_raster2, weig_raster)
expect_equal(metr_df2, metr_df)
expect_equal(grid_sf2, grid_sf)
expect_equal(popdens_raster2, popdens_raster)
