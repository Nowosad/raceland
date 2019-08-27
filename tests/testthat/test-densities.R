real_raster = create_realizations(race_raster, n = 1)
weig_raster = create_densities(real_raster, race_raster, window_size = 10)

test_that("total population stays the same for a realization", {
  expect_equal(sum(race_raster[], na.rm = TRUE),
               sum(weig_raster[[1]][], na.rm = TRUE))
})

test_that("wrong output returns an error", {
  expect_error(create_densities(as.matrix(real_rasters), race_raster, window_size = 10))
  expect_error(create_densities(real_rasters, as.matrix(race_raster), window_size = 10))
})
