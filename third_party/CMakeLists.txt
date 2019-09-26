

# create the glm interface library
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)

# create the catch2 interface library
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE Catch2/single_include)

# create the better_enum interface library
add_subdirectory(better_enum)

# build glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "No glfw examples" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "No glfw tests" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "No glfw docs" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "No glfw install" FORCE)
add_subdirectory(glfw)

# build fmt
add_subdirectory(fmt)
put_target_in_folder(fmt third_party)


# build json
set(JSON_BuildTests OFF CACHE INTERNAL "No json tests")
set(JSON_Install OFF CACHE INTERNAL "Don't install the json library")
add_subdirectory(json)

