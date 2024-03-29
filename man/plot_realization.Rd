% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/plot_realization.R
\name{plot_realization}
\alias{plot_realization}
\title{Plot a Realization}
\usage{
plot_realization(x, y, hex, ...)
}
\arguments{
\item{x}{A SpatRaster with one layer.
Each value should correspond to a layer in \code{y}.}

\item{y}{A SpatRaster with race-specific population densities}

\item{hex}{A character vector with colors specified in hexadecimal format.
Each color should correspond to a layer in \code{y} and value in \code{x}.}

\item{...}{Additional arguments as for \code{\link[terra:plotRGB]{terra::plotRGB()}}}
}
\description{
Displays realization taking into account also subpopulation density.
}
\examples{
library(terra)
race_raster = rast(system.file("extdata/race_raster.tif", package = "raceland"))
hex_colors = c("#F16667", "#6EBE44", "#7E69AF", "#C77213","#F8DF1D")
realization = create_realizations(race_raster, 1)
plot(race_raster)
plot(realization)

plot_realization(realization, race_raster, hex = hex_colors)
}
