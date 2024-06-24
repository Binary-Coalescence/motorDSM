motorDSM
==========

EPICS motor drivers for the following [Dynamic Structures and
Materials](https://www.dynamic-structures.com/) motor controllers: MD-90

[![Build Status](https://github.com/Binary-Coalescence/motorDSM/actions/workflows/ci-scripts-build.yml/badge.svg)](https://github.com/Binary-Coalescence/motorDSM/actions/workflows/ci-scripts-build.yml)

motorDSM is a submodule of [motor](https://github.com/epics-modules/motor).
When motorDSM is built in the ``motor/modules`` directory, no manual
configuration is needed.

motorDSM can also be built outside of motor by copying it's
``EXAMPLE_RELEASE.local`` file to ``RELEASE.local`` and defining the paths to
``EPICS_BASE``, ``MOTOR``, and itself.

motorDSM contains an example IOC that is built if ``CONFIG_SITE.local`` sets
``BUILD_IOCS = YES``.  The example IOC can be built outside of driver module.

------------------------

To set up a full EPICS stack for development and testing, install and configure
all of the following dependencies:

------------------------
epics-base
------------------------

Install make, gcc, and perl packages if not already installed, then clone and
build epics-base:

    $ export SUPPORT=/path/to/install/directory
    $ cd $SUPPORT
    $ git clone git@github.com:epics-base/epics-base.git
    $ cd epics-base
    $ make distclean
    $ make


------------------------
asyn
------------------------

    $ cd $SUPPORT
    $ git clone git@github.com:epics-modules/asyn.git

Needed to install (on Arch Linux) ``rpcsvc-proto`` package to get ``rpcgen``
binary needed to make asyn.

In ``asyn/configure``, copy ``RELEASE`` to ``RELEASE.local`` and set ``SUPPORT``
and ``EPICS_BASE`` paths.

In ``asyn/configure``, create ``CONFIG_SITE.local`` file with the line:  
	TIRPC=YES  
if appropriate header files are in ``/usr/include/tirpc/rpc`` instead
of ``/usr/include/rpc``.

    $ cd asyn
    $ make clean
    $ make


------------------------
seq
------------------------

    $ cd $SUPPORT
    $ git clone git@github.com:ISISComputingGroup/EPICS-seq.git seq

Install the ``re2c`` package (Arch).

Create ``seq/configure/RELEASE.local`` and set path for ``EPICS_BASE``.  
(Note this package seems to forget to git-ignore the .local file.)

Edit ``seq/configure/RELEASE`` to add the missing '-' before include for ``ISIS_CONFIG``
on the next to last line.  Seems to be a typo.

    $ cd seq
    $ make clean
    $ make


------------------------
motor
------------------------

    $ cd $SUPPORT
    $ git clone git@github.com:epics-modules/motor.git

Optionally, if you want to install additional motor drivers:

    $ cd motor
    $ git submodule init
    $ git submodule update modules/motorAcs
    $ git submodule update modules/foo
    $ git submodule update modules/bar

Optionally, edit ``motor/modules/Makefile`` and comment out all unused driver
submodules.

Optionally, create ``motor/config/CONFIG_SITE.local`` with the line:  
	BUILD_IOCS = YES

Create ``motor/config/RELEASE.local`` and set ``SUPPORT``, ``ASYN``, ``SNCSEQ``,
and ``EPICS_BASE`` to the appropriate paths.

    $ cd motor
    $ make distclean
    $ make


------------------------
motorDSM (this package)
------------------------

    $ cd $SUPPORT
    $ git clone git@github.com:Binary-Coalescence/motorDSM.git

In ``motorDSM/configure``, copy ``EXAMPLE_CONFIG_SITE.local``
to ``CONFIG_SITE.local`` and set:  
	BUILD_IOCS = YES

In ``motorDSM/configure``, copy ``EXAMPLE_RELEASE.local`` to ``RELEASE.local``
and set paths for ``EPICS_BASE``, ``MOTOR``, and ``MOTOR_DSM``.

    $ cd motorDSM
    $ make distclean
    $ make
