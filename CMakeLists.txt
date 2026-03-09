cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
include(cmake/misc.cmake)

project("Griel's Quest for the Sangraal" VERSION 1.0.1 LANGUAGES C
	DESCRIPTION "Puzzle game originally for MSX1(2005)/MSX2(1990)"
	HOMEPAGE_URL "https://github.com/nevat/griels-quest")

set(CMAKE_C_STANDARD 99)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# executable
add_executable(griels
	src/common.h
	src/ending.c src/ending.h
	src/game.c src/game.h
	src/hero.c src/hero.h
	src/history.c src/history.h
	src/hud.c src/hud.h
	src/intro.c src/intro.h
	src/loading.c src/loading.h
	src/main.c src/main.h)
target_compile_options(griels PRIVATE -Wall -Wextra)
target_compile_definitions(griels PRIVATE $<$<CONFIG:Debug>:DEBUG>)

if(EMSCRIPTEN)
	# emscripten ships "ports" of SDL2 libraries, no linking necessary
	list(APPEND SDLPORTS --use-port=sdl2 --use-port=sdl2_mixer:formats=ogg
		--use-port=sdl2_image:formats=png)
	target_compile_options(griels PRIVATE ${SDLPORTS} -flto)
	set_target_properties(griels PROPERTIES SUFFIX ".html")
	set(JS_SHELL "${CMAKE_CURRENT_SOURCE_DIR}/cmake/shell.html.in")
	set_source_files_properties("src/main.c" PROPERTIES OBJECT_DEPENDS "${JS_SHELL}")
	target_link_options(griels BEFORE PRIVATE
		-sMINIFY_HTML=0 -flto ${SDLPORTS} -sEXIT_RUNTIME=1 -sASYNCIFY -sASSERTIONS
		-sENVIRONMENT=web --closure 1 -sNO_DISABLE_EXCEPTION_CATCHING
		--shell-file=${JS_SHELL} --preload-file=${CMAKE_CURRENT_BINARY_DIR}/data@/data)

	# custom data directory
	set(DATADIR "/data")
	file(COPY data fx music png DESTINATION data)
	target_compile_definitions(griels PRIVATE DATADIR="${DATADIR}")
else()
	include(GNUInstallDirs)

	# options
	set(DATADIR "${CMAKE_INSTALL_PREFIX}/share/griels" CACHE PATH "Where the data files are installed")
	target_compile_definitions(griels PRIVATE DATADIR="${DATADIR}")

	# libs
	find_package(SDL2 REQUIRED)
	find_package(SDL2_mixer QUIET)
	find_package(SDL2_image QUIET)
	# on old systems there may be cmake files missing
	if(NOT SDL2_mixer_FOUND OR NOT SDL2_image_FOUND)
		include(FindPkgConfig)
		if(NOT SDL2_mixer_FOUND)
			pkg_check_modules(SDL2_mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
			add_library(SDL2_mixer::SDL2_mixer ALIAS PkgConfig::SDL2_mixer)
		endif()
		if(NOT SDL2_image_FOUND)
			pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)
			add_library(SDL2_image::SDL2_image ALIAS PkgConfig::SDL2_image)
		endif()
	endif()
	target_link_libraries(griels PRIVATE
		SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_image::SDL2_image)

	# installation
	install(TARGETS griels RUNTIME DESTINATION bin)
	install(FILES griels.desktop DESTINATION share/applications)
	install(FILES png/icon.png DESTINATION share/pixmaps RENAME griels.png)
	install(FILES png/icon.png DESTINATION share/icons/hicolor/48x48/apps RENAME griels.png)
	install(DIRECTORY data fx music png DESTINATION ${DATADIR})

	# uninstallation
	configure_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
		IMMEDIATE @ONLY)
	add_custom_target(uninstall
		COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

# packaging
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_SOURCE_GENERATOR ";")
set(CPACK_PACKAGE_DIRECTORY "packages")
set(CPACK_PACKAGE_FILE_NAME "griels-${PROJECT_VERSION}")
set(CPACK_ARCHIVE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}")
set(CPACK_ARCHIVE_ROM_FILE_NAME "${CPACK_ARCHIVE_FILE_NAME}")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY ON)
set(CPACK_COMPONENT_INCLUDE_TOPLEVEL_DIRECTORY ON)
include(CPack)

# summary
print_color_summary()
