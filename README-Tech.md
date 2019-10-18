
# Linux-US-OS-Services / Tech Info

Linux-US-OS-Services stands for Linux User-Space services offered by the Linux kernel.

The code is sperated to modules, each covers a different topic.

Each module holds its own read me file and resides in a dedicated path.

Assume modules name is xxxxx (e.g. prcs_mng) then:
1. each module's entry point is at a function called xxxxx_main()
2. each module provides a header file whose name is xxxxx.h

The executable object named 'exe' resides at obj/ folder (creaded by the make file).
Calling make while in 'initial' folder. make will use the Makefile located in that folder.

Calling the exec -h will tell about the supported CLI options.
One of the supported CLI options is: -m # (where # is the numer of the module).
calling exec -l will amke exec report the supported modules along with module name and its ID.
Calling exec -m #ID will make exec call the intended module.


## Makefile(s)

The makefilea are heirarcical.

The root Makefile calls each module's makefile to create a library.
As its final step, the root Makefile links all lbraries to create the executable.

Please note that when a single header file is changed, all c files will be recompiled.
The author decidec not to use teh GNI make capability to build depenedency lists for each c file
(using the gcc cpability to report #included files).


## Deployment

The repository can be forked or cloned according to the
interest of the one who has interest in the code.

Please refer to README and LICENSE files.


## Available modules

1. Process Management (Create, Manage, Destroy)
