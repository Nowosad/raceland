
<!-- README.md is generated from README.Rmd. Please edit that file -->

# raceland

<!-- badges: start -->

[![Travis build
status](https://travis-ci.org/Nowosad/raceland.svg?branch=master)](https://travis-ci.org/Nowosad/raceland)
[![Codecov test
coverage](https://codecov.io/gh/Nowosad/raceland/branch/master/graph/badge.svg)](https://codecov.io/gh/Nowosad/raceland?branch=master)
[![CRAN
status](https://www.r-pkg.org/badges/version/raceland)](https://CRAN.R-project.org/package=raceland)
[![CRAN RStudio mirror
downloads](http://cranlogs.r-pkg.org/badges/raceland)](https://cran.r-project.org/package=raceland)
<!-- badges: end -->

The **raceland** package implements a computational framework for a
pattern-based, zoneless analysis, and visualization of (ethno)racial
topography. It is a reimagined approach for analyzing residential
segregation and racial diversity based on the concept of ‘landscape’
used in the domain of landscape ecology. A racial landscape, represented
by a high-resolution raster grid with each cell containing only
inhabitants of a single race, is quantified by two metrics (entropy and
mutual information) derived from Information Theory concept (IT).
Entropy is the measure of racial diversity and mutual information
measures racial segregation.

Racial landscape method is based on the raster gridded data, and unlike
the previous methods, does not depend on the division of specific zones
(census tract, census block, etc.). Calculation of racial diversity
(entropy) and racial segregation (mutual information) can be performed
for the whole area of interests (i.e., metropolitan area) without
introducing any arbitrary divisions. Racial landscape method also allows
for performing calculations at different spatial scales.

## Installation

You can install the released version of raceland from
[CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("raceland")
```

You can install the development version from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("Nowosad/raceland")
```

## Example

``` r
library(raceland)
library(raster)
#> Loading required package: sp
```

``` r
# Plot the input data
data(race_raster, package = "raceland")
plot(race_raster)
```

<img src="man/figures/README-unnamed-chunk-3-1.png" width="100%" />

``` r
# Construct racial landscape
real_raster = create_realizations(x = race_raster, n = 100)
race_colors = c("#F16667", "#6EBE44", "#7E69AF", "#C77213","#F8DF1D")
plot(real_raster, col = race_colors, maxnl = 9)
```

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" />

``` r
# Plot racial ladnscape 
plot_realization(x = real_raster[[1]], y = race_raster, hex = race_colors)
```

<img src="man/figures/README-unnamed-chunk-5-1.png" width="100%" />

``` r
# Calculate local subpopulation densities
dens_raster = create_densities(real_raster, race_raster, window_size = 10)
plot(dens_raster, maxnl = 9)
```

<img src="man/figures/README-unnamed-chunk-6-1.png" width="100%" />

``` r
# Calculate IT-metrics 
metr_df = calculate_metrics(x = real_raster, w = dens_raster,
                            neighbourhood = 4, fun = "mean", 
                            size = NULL, threshold = 1)
head(metr_df)
#>   realization row col      ent  joinent  condent    mutinf
#> 1           1   1   1 1.642960 3.172001 1.529041 0.1139193
#> 2           2   1   1 1.622988 3.126443 1.503456 0.1195318
#> 3           3   1   1 1.648145 3.193061 1.544916 0.1032296
#> 4           4   1   1 1.652367 3.198486 1.546119 0.1062475
#> 5           5   1   1 1.635775 3.152407 1.516632 0.1191429
#> 6           6   1   1 1.646357 3.187201 1.540844 0.1055126
```

``` r
# Summarize IT metrics 
summary(metr_df[, c("ent", "mutinf")])
#>       ent            mutinf       
#>  Min.   :1.610   Min.   :0.09508  
#>  1st Qu.:1.627   1st Qu.:0.10456  
#>  Median :1.634   Median :0.11101  
#>  Mean   :1.634   Mean   :0.11088  
#>  3rd Qu.:1.640   3rd Qu.:0.11640  
#>  Max.   :1.653   Max.   :0.13660
```

## Contribution

Contributions to this package are welcome. The preferred method of
contribution is through a GitHub pull request. Feel free to contact us
by creating [an issue](https://github.com/Nowosad/raceland/issues).
