check_input = function(x){
  if (!(methods::is(x, "SpatRaster"))){
    if (methods::is(x, "RasterLayer") || methods::is(x, "RasterStack") || methods::is(x, "RasterBrick")){
      x = terra::rast(x)
    } else {
      stop("x needs to be either SpatRaster, RasterStack or RasterBrick", call. = FALSE)
    }
  }
  return(x)
}


