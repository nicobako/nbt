# **__nbt__**

## **note**
This readme is pretty out of date,
and I plan on updating in early January 2019 time frame.

*nbt* originally started as a place where I was developing small C++ functionality,
but it has quickly become a collection of third party tools.
Each third party tool is a submodule, and has cmake support.

The remainder of this document is out-of-date.

## summary
*nbt* (nico bako tools) is a collection of C++ libraries that is being
developed to provide an *object-oriented API* for performing tasks like
parsing files and generating 3D plots (still a work in progress).

It is specifically designed to help c++ developers create custom 3D plots
and custom 3D plotting applications.

## getting started

### building nbt

*nbt* is a collection of C++ libraries; some libraries are header only,
while others must be compiled into static libraries which your application
can link to.

Building *nbt* is easy when using CMake. 
Simply set this directory as the CMake root directory, 
and that should be all you need to do.

### a note about 3rd party dependencies

*nbt* uses a handful of 3rd party libraries :


| library          | purpose                   | included with *nbt*|
|------------------|---------------------------|----------|
| glew             | OpenGL Extension Wrangler | yes      |
| SDL2             | creates the GUI           | yes      |
| glm              | vector and matrix library | yes      |
| stb_image        | an image loading library  | yes      |
| google test/mock | a unit testing framework  | **no**   |

For your convenience, the majority of these 3rd party libraries are included
in the nbt repository. I know including these libraries in the nbt repository
is a practice that may be frowned upon,but I did it only to make it easier
for users to start using nbt without having to download so many other 3rd
party libraries.

Google Test/Mock is not included due to its size. If you want to run the tests please download
it and set change the location of the GTEST_DIR variable in the test's [CMakeLists.txt](tests/CMakeLists.txt).

## contributing

If there is any functionality you would like to see added to *nbt*,
or if you spot a bug, and you want *me* to do it,
feel free to let me know by email or in person.

If you would like to contribute, please follow this wonderful 
[guide to contributing to open sourced projects](https://akrabat.com/the-beginners-guide-to-contributing-to-a-github-project/)


## versioning

*nbt* is still in its infancy stage, so we are still in version 0.0.0,
but when it matures a little more I plan on using SemVer for versioning.

## license

No established license. Feel free to do with *nbt* as you please!

## acknowledgements

Thanks to all of the people who helped create the 3rd party libraries that
*nbt* depends on.
