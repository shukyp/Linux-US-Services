
# US_infra SW description
---------------------------
As its name implies the module is the entry point for the whole US application.

Currently it provides the following facilities:

## main.c
-----------
(1) invokes teh CLI parser facility
(2) invokes a selected module (9f any indicated in the CLI )

## us_cli.c
-----------
Parses the CLOI options

-h:	it display the CLI syntax (all options)
-s: 	presents the OS run-time capabilities and POSIX features
-v: 	enables the verbose mode (and displays the actual  command line components)
-l: 	presents a list of all supported modules
-m #: enables the invocation of a specific module

## us_modules.c
----------------
Holdes the information of teh supported modules and provides interfaces
so a request can be done to run any given module, one at a time.
(p.s. later on, the application will support running the different modules concurrently
bu using multi-threading). 

## us_sys_ftr.c
----------------
Supports investigate the susytem as for its run time capabilities and (POSIX defined)
featurtes.
