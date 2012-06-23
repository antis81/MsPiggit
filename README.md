# MsPiggit Git user interface

MsPiggit is a platform independent solution for a Git user interface with a special focus on submodules.

## Building

The most easy way to compile is using QtCreator. Just load the project and hit the run button.

Build from the console:

    qmake mspiggit.pro -r -spec YOUR-PLATFORM CONFIG+=release
    make -w

## Library dependencies

* libqgti2 / libgit2
* zlib
* Qt4
