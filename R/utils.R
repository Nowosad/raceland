check_is_raster = function(x){
  if (!(methods::is(x, "SpatRaster"))){
    if (methods::is(x, "RasterLayer") || methods::is(x, "RasterStack") || methods::is(x, "RasterBrick")){
      return(TRUE)
    } else {
      stop("x needs to be either SpatRaster, RasterStack or RasterBrick", call. = FALSE)
    }
  } else{
    return(FALSE)
  }
}
check_input = function(x, is_raster){
  if (is_raster){
      x = terra::rast(x)
  }
  return(x)
}
check_output = function(out, is_raster){
  if (is_raster){
    out = raster::stack(out)
  }
  return(out)
}
