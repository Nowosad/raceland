library(raster)
x = create_realizations(race_raster, n = 5)
w = create_densities(x, race_raster, window_size = 100)
df = calculate_metrics(x, w, neighbourhood = 4, fun = "mean")
df2 = calculate_metrics(x, w, neighbourhood = 4, fun = "mean", size = 100)

test_that("calculate_metrics output structure is stable", {
  expect_equal(dim(df), c(5, 7))
  expect_equal(dim(df2), c(5, 7))
})
