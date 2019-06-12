# test_that("multiplication works", {
#   expect_equal(2 * 2, 4)
# })

# test_that("multiplication works", {
#   expect_equal(2 * 2, 4)
# })
library(raster)

# prepare data ------------------------------------------------------------
a = raster(nrows = 4, ncols = 4,
           xmn = 0, xmx = 4, ymn = 0, ymx = 4,
           crs = NA,
           vals = c(NA, 2, 2, 1, NA, NA, 8, 6, 2, 6, 5, 1, NA, 0, 3, 0))

b = raster(nrows = 4, ncols = 4,
           xmn = 0, xmx = 4, ymn = 0, ymx = 4,
           crs = NA,
           vals = c(NA, 6, 7, 4, NA, NA, 0, 0, 1, 3, 2, 6, NA, 8, 7, 9))

w = raster(nrows = 4, ncols = 4,
           xmn = 0, xmx = 4, ymn = 0, ymx = 4,
           crs = NA,
           vals = c(NA, 2, 1, 5, NA, NA, 2, 4, 7, 1, 3, 3, NA, 2, 0, 1))

#build raster stack based on race-specific grids
s = stack(a, b, w)
names(s) = c("a", "b", "w")

#create proportion of each race in cell
perc = s / sum(s)
names(perc) = names(s)

cats = raster(nrows = 4, ncols = 4,
              xmn = 0, xmx = 4, ymn = 0, ymx = 4,
              crs = NA,
              vals = c(NA, 2, 2, 3, NA, NA, 1, 1, 3, 1, 1, 2, NA, 2, 2, 2))

plot(cats)

calculate_weights(cats, s, size = 4)
