
# Linux-US-Services / Tech Info
-----------------------------------
Linux-US-OS-Services stands for Linux User-Space services offered by the Linux kernel.

The code is divided into modules, each covers a different topic.

The root module is located at the us_infra folder (where the main() function resides).

Each module holds its own readme file, Makefile and source files (*.c, *.h) - all resides
at a dedicated path.

Assume module's name is xxxx (e.g. prcs_mng) then each module has:
1. entry point file is at a function called xxxx_main()
2. "internal" header file - xxxx_inner.h - that exposes definitions/API
   internlly to module's logic.
3. "external" header file - xxxx.h - located in root-folder/incl
   that exposes definitions/API externally to other module's logic.

The executable object named 'exec' resides at the root-folder/bin/ folder.
The bin folder will be created automaticaly by the make file if absent.

## Makefile(s)
-----------------
The makefilea are heirarcical.

The root Makefile calls each module's makefile to create a library file (module.a).
As its final step, the root Makefile links all lbraries to create the executable.

## CLI options
----------------
Calling the exec -h will tell the supported CLI options.

Once the user gets familiar with the application, he/she will call exec -m #
to invoke a selected module to enjoy what it has to offer.

## Development Environment
-------------------------
Ubuntu 16.04 LTS

## Deployment
----------------
The repository can be forked or cloned according to the
interest of the one who has interest in the code.

Please refer to README and LICENSE files.


## Available modules
----------------------
run: exec -l
doc: each module comes along with redame file
