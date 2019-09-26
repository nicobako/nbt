# create the better_better_enum interface library

add_library(better_enum INTERFACE)

target_include_directories(better_enum INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(${CMAKE_GENERATOR} MATCHES "Visual Studio 10 .+")
	
	target_compile_definitions(better_enum
		INTERFACE VISUAL_STUDIO_2017_2010_WORKAROUND
	)
	
endif()
