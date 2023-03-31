library(testthat)
library(raceland)
library(terra)
library(sf)

race_raster = rast(system.file("extdata/race_raster.tif", package = "raceland"))
test_check("raceland")
