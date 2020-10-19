
<!-- README.md is generated from README.Rmd. Please edit that file -->

# raceland

<!-- badges: start -->

[![R build
status](https://github.com/Nowosad/raceland/workflows/pkgdown/badge.svg)](https://github.com/Nowosad/raceland/actions)
[![Codecov test
coverage](https://codecov.io/gh/Nowosad/raceland/branch/master/graph/badge.svg)](https://codecov.io/gh/Nowosad/raceland?branch=master)
[![CRAN
status](https://www.r-pkg.org/badges/version/raceland)](https://CRAN.R-project.org/package=raceland)
[![CRAN RStudio mirror
downloads](http://cranlogs.r-pkg.org/badges/raceland)](https://cran.r-project.org/package=raceland)
<!-- badges: end -->

The **raceland** package implements a computational framework for a
pattern-based, zoneless analysis, and visualization of (ethno)racial
topography (Dmowska et al., 2020). It is a reimagined approach for
analyzing residential segregation and racial diversity based on the
concept of ‘landscape’ used in the domain of landscape ecology. A racial
landscape, represented by a high-resolution raster grid with each cell
containing only inhabitants of a single race, is quantified by two
metrics (entropy and mutual information) derived from Information Theory
concept (IT). Entropy is the measure of racial diversity and mutual
information measures racial segregation.

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
# install.packages("remotes")
remotes::install_github("Nowosad/raceland")
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
#> 1           1   1   1 1.641782 3.168828 1.527046 0.1147355
#> 2           2   1   1 1.638414 3.159920 1.521506 0.1169076
#> 3           3   1   1 1.635824 3.141920 1.506096 0.1297275
#> 4           4   1   1 1.633109 3.151669 1.518560 0.1145495
#> 5           5   1   1 1.629351 3.132725 1.503373 0.1259784
#> 6           6   1   1 1.630314 3.137547 1.507233 0.1230802
```

``` r
# Summarize IT metrics 
summary(metr_df[, c("ent", "mutinf")])
#>       ent            mutinf       
#>  Min.   :1.608   Min.   :0.09049  
#>  1st Qu.:1.625   1st Qu.:0.10599  
#>  Median :1.633   Median :0.11340  
#>  Mean   :1.633   Mean   :0.11268  
#>  3rd Qu.:1.641   3rd Qu.:0.11902  
#>  Max.   :1.660   Max.   :0.13287
```

## References

  - Dmowska, A., Stepinski T., Nowosad J. Racial landscapes – a
    pattern-based, zoneless method for analysis and visualization of
    racial topography. Applied Geography. 122:1-9,
    <http://dx.doi.org/10.1016/j.apgeog.2020.102239>

## Contribution

Contributions to this package are welcome. The preferred method of
contribution is through a GitHub pull request. Feel free to contact us
by creating [an issue](https://github.com/Nowosad/raceland/issues).
