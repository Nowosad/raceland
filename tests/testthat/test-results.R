# load a reference objects ------------------------------------------------
load(system.file("results", "real_raster.rda", package = "racialscape"))
load(system.file("results", "weig_raster.rda", package = "racialscape"))
load(system.file("results", "metr_df.rda", package = "racialscape"))
load(system.file("results", "grid_sf.rda", package = "racialscape"))

# calculate new results ---------------------------------------------------
set.seed(22)
real_raster2 = create_realizations(prop_raster, n = 5)

weig_raster2 = create_weights(real_raster, prop_raster, size = 100)

metr_df2 = calculate_metrics(real_raster, weig_raster,
                            neighbourhood = 4, fun = "mean", size = 100)

grid_sf2 = create_grid(real_raster, size = 100)

# tests -------------------------------------------------------------------
expect_equal(real_raster2, real_raster)
expect_equal(weig_raster2, weig_raster)
expect_equal(metr_df2, metr_df)
expect_equal(grid_sf2, grid_sf)