
cmake_minimum_required (VERSION 2.8)

project(griels-quest C)

# be verbose
#set(CMAKE_VERBOSE_MAKEFILE ON)

# original flags from legacy makefile
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -finline-functions -funswitch-loops -fpredictive-commoning -fgcse-after-reload -ftree-vectorize")
#add_definitions(-Wall -Wextra -pedantic)

add_executable(griels
  src/history.c
  src/intro.c
  src/game.c
  src/hud.c
  src/hero.c
  src/loading.c
  src/ending.c
  src/main.c
)

# pkg-config finds our needed libraries under Linux
include(FindPkgConfig)
if(PKG_CONFIG_FOUND)
  pkg_search_module(SDL REQUIRED sdl)
  pkg_search_module(SDL_MIXER REQUIRED SDL_mixer)
  pkg_search_module(SDL_IMAGE REQUIRED SDL_image)
  pkg_search_module(SDL_GFX REQUIRED SDL_gfx)
  pkg_search_module(SDL_TTF REQUIRED SDL_ttf)
else()
  # fallback to CMake modules
  find_package(SDL REQUIRED)
  find_package(SDL_mixer REQUIRED)
  find_package(SDL_image REQUIRED)
  find_package(SDL_gfx REQUIRED)
  find_package(SDL_ttf REQUIRED)
endif()

include_directories(
  src
  ${SDL_MIXER_INCLUDE_DIRS}
  ${SDL_IMAGE_INCLUDE_DIRS}
  ${SDL_GFX_INCLUDE_DIRS}
  ${SDL_TTF_INCLUDE_DIRS}
  ${SDL_INCLUDE_DIRS}
)

target_link_libraries(griels
  ${SDL_MIXER_LIBRARIES}
  ${SDL_IMAGE_LIBRARIES}
  ${SDL_GFX_LIBRARIES}
  ${SDL_TTF_LIBRARIES}
  ${SDL_LIBRARIES}
)

# installation
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/griels DESTINATION bin)
install(FILES griels.desktop DESTINATION share/applications)
install(FILES png/icon.png DESTINATION share/pixmaps RENAME griels.png)
install(DIRECTORY music fx data png DESTINATION share/griels)
