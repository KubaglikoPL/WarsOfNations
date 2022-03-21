cmake_minimum_required(VERSION 3.10.2)
project(GAME C)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(DEBUG_BUILD ON)
endif()

if(EMSCRIPTEN)
  set(EMSCRIPTEN_FLAGS "-s WASM=1 s USE_SDL=2 ")
  if (DEBUG_BUILD)
    set(EMSCRIPTEN_FLAGS "${EMSCRIPTEN_FLAGS} -s DEMANGLE_SUPPORT=1 -g4 --source-map-base http://localhost:6931/")
  endif()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EMSCRIPTEN_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_FLAGS}")
  set($ENV{CFLAGS} ${EMSCRIPTEN_FLAGS})
	set($ENV{LDFLAGS} ${EMSCRIPTEN_FLAGS})
	set(CMAKE_REQUIRED_FLAGS ${EMSCRIPTEN_FLAGS})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE game_src "src/*.c" "src/*.cpp" "include/*.h" "3rd_party/*.c")

add_executable(GAME ${game_src})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_definitions(GAME PUBLIC BUILD_64BIT)
endif()

if(NOT SDL2_FETCH_CONTENT_VERSION)
	set(SDL2_FETCH_CONTENT_VERSION release-2.0.20)
endif()

if(NOT EMSCRIPTEN)
	file(GLOB_RECURSE sdl_net_src "sdl_net/*.c")
	target_sources(GAME PUBLIC ${sdl_net_src})

	include(FetchContent)
	FetchContent_Declare(
		SDL2
		GIT_REPOSITORY	https://github.com/libsdl-org/SDL
		GIT_TAG			${SDL2_FETCH_CONTENT_VERSION}
	)
	set(LIBC TRUE)
	set(SDL_SHARED FALSE)
	set(SDL_STATIC TRUE)
	set(SDL_LIBC TRUE)
	set(SDL_VULKAN FALSE)
	set(SDL_METAL FALSE)
	set(SDL_RENDER_D3D FALSE)
	set(SDL_RENDER_METAL FALSE)
	FetchContent_MakeAvailable(SDL2)

	target_include_directories(GAME PUBLIC "${sdl2_SOURCE_DIR}/include" "sdl_net")
	if (DEBUG_BUILD)
		target_link_libraries(GAME SDL2d)
	else()
		target_link_libraries(GAME SDL2)
	endif()
	add_dependencies(GAME SDL2-static)
endif()

target_compile_definitions(GAME PUBLIC SDL_MAIN_HANDLED)
target_compile_definitions(GAME PUBLIC WIN32_LEAN_AND_MEAN)
target_include_directories(GAME PUBLIC "include" "3rd_party" "src")

if(WIN32)
	target_link_libraries(GAME imm32 winmm hid setupapi version Ws2_32 Iphlpapi)
endif(WIN32)

if(WIN32)
	if (CMAKE_C_COMPILER_ID MATCHES "MSVC")
		if (DEBUG_BUILD)
			target_compile_options(${PROJECT_NAME} PRIVATE "/ZI")
			target_link_options(${PROJECT_NAME} PRIVATE "/SAFESEH:NO")
		endif()
	endif()
endif(WIN32)

add_custom_command(TARGET GAME POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)

