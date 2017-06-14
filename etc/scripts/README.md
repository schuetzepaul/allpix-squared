# Tools

## print_module_parameters.sh

Simple tool which parses the source code of a module and prints a list of all available configuration parameters together with their type. It takes the source code directory of the respective module as command line argument.

Exmaple usage:

```
etc/scripts/print_module_parameters.sh src/modules/DefaultDigitizer/
```

Example output:

```
Parameters for module "DefaultDigitizer":

NAME                TYPE
---------------     ------------------

output_plots        bool
electronics_noise   double
output_plots        bool
threshold           double
threshold_smearing  unsigned int
adc_smearing        double
```

Parameters found in the source code are not de-duplicated, thus some might appear several times.

For the explanation of the parameters, please refer to the documentation of the respective module.


## setup_lxplus.sh

Script to facilitate the compilation of allpix<sup>2</sup> on the CERN LXPLUS Linux cluster. Sourcing the script via

```
source etc/scripts/setup_lxplus.sh
```

will setup all required build dependencies.
