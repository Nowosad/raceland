
<!-- README.md is generated from README.Rmd. Please edit that file -->

# raceland

<!-- badges: start -->

[![Travis build
status](https://travis-ci.org/Nowosad/raceland.svg?branch=master)](https://travis-ci.org/Nowosad/raceland)
[![Codecov test
coverage](https://codecov.io/gh/Nowosad/raceland/branch/master/graph/badge.svg)](https://codecov.io/gh/Nowosad/raceland?branch=master)
[![CRAN
status](https://www.r-pkg.org/badges/version/raceland)](https://CRAN.R-project.org/package=raceland)
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
#> 1           1   1   1 1.633341 3.142363 1.509022 0.1243184
#> 2           2   1   1 1.637324 3.160367 1.523043 0.1142804
#> 3           3   1   1 1.634186 3.146756 1.512570 0.1216158
#> 4           4   1   1 1.629882 3.152127 1.522246 0.1076359
#> 5           5   1   1 1.638865 3.177159 1.538294 0.1005704
#> 6           6   1   1 1.635714 3.152158 1.516443 0.1192709
```

``` r
# Summarize IT metrics 
summary(metr_df[, c("ent", "mutinf")])
#>       ent            mutinf       
#>  Min.   :1.609   Min.   :0.09275  
#>  1st Qu.:1.630   1st Qu.:0.10834  
#>  Median :1.636   Median :0.11335  
#>  Mean   :1.635   Mean   :0.11365  
#>  3rd Qu.:1.640   3rd Qu.:0.11992  
#>  Max.   :1.655   Max.   :0.13526
```

## Contribution

Contributions to this package are welcome. The preferred method of
contribution is through a GitHub pull request. Feel free to contact us
by creating [an issue](https://github.com/Nowosad/raceland/issues).
