# lethality_monorepo

The goal of this project is to create a *monorepo* for the *lethality team*.

A *monorepo* is not very different from what most developpers
in the lethality team are already doing ... writing code!

A *monorepo* differs only in this regard:

    In a monorepo all of your projects are in one place,
	under the umbrella of one directory,
	and under one form of source control.

A monorepo offers many benefits over the traditional *one repo per project* philosophy. For example:

- One commit, one tag, one push, one pull.
- All projects are **always in sync** since they are developped together in one place.
- Projects can link to one another with ease since the directory organization is known and configurable.
- Managing dependencies becomes effortless:
  - As a result, developpers are more likely to use third-party libraries instead of *reinventing the wheel*.
  - There are no *different versions* of individual projects/libraries ... everything is in the same current version.
- All developpers know with certainty that everyone has the **exact same code*.
  
To learn more about *monorepos* please read
[this short article](https://danluu.com/monorepo/)

## dependencies

Dependencies fall into two categories:

1) can be built from source with ease
  - these dependencies are in the `third_party` directory
  - these are a mixture of *submodules*, and *directories*

2) are too large to build from source
  - currently, `boost` is the only one in this category
  - To learn more about how to set up *boost* pleas consult [the boost readme](third_party/boost/readme.md)

## organization

The main method of organization is to split projects
into separate directories and subdirectories
based on the projects' logical relationship to one another.


## building the *lethality_monorepo*
### install boost
You must first *install* the appropriate version of boost.
Please see [the boost readme](nbt/extern/boost/readme.md) for further directions.

### build the *lethality_monorepo*
Type the following commands into a git-bash terminal:
```bash
# clone the repo an initialize all submodules
git clone --recursive git@GITLAB:Lethality/Nico/lethality_monorepo
cd lethality_monorepo
# create the build directory and go into it
mkdir build && cd build
cmake ../
```

You can also build via the CMake GUI if you know how to use it.

Now the build files have been generated.
You can continue building by using your build system of your choice (*i.e.* Visual Studio),
or you can build using *CMake*
```bash
cmake --build ./
```


## git workflow
This project uses this [git branching model](https://nvie.com/posts/a-successful-git-branching-model/).
It has worked really well, and once you get comfortable with branching with *git*,
it is a very intuitive git workflow.

## preparing a release

First, create a new *release branch* (see the [git workflow section](#git-workflow)).
Then, modify the version number of the main [CMakeLists](CMakeLists.txt)
file to have the correct version of the release you are preparing.

It is crucial to begin with a *clean* project.
That means that all submodules should be *deinitialized*,
and all *build files* and  *git-ignored* files should be removed.

You can do this by hand,
```bash
git submodule deinit --all
git clean -fdx
```

then build the *Release* version of the code:
```bash
mkdir build
cd build
cmake -Dboost_root_dir=<path_to_boost> -Droot_install_dir=<installation_path> ../
cmake --build ./ --config Release
cmake --build ./ --target RUN_TESTS --config Release
cmake --build ./ --target INSTALL --config Release
```
Make sure to replace `path_to_boost` and `root_install_dir`
with their correct values.
This will build all targets, run all the tests,
and install everything in the `root_install_dir`.

If you have *gitlab-ci* configured properly,
you can run a local *gitlab-runner*
```bash
/c/Gitlab-Runner/gitlab-runner exec shell run_all
```
The *gitlab-runner* is designed to stop when a failure occurs,
ensuring that everything is in proper working order before a release is finalized.
