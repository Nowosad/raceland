real_raster = create_realizations(race_raster, n = 2)

test_that("create_realizations is stable", {
  expect_s4_class(real_raster, "SpatRaster")
  expect_equal(res(real_raster), res(race_raster))
  expect_equal(nlyr(real_raster), 2)
})
