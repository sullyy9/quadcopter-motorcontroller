# Set the toolchain.
####################################################################################################
set(CMAKE_SYSTEM_NAME           "Generic")
set(CMAKE_SYSTEM_PROCESSOR      "avr")
set(CMAKE_CROSSCOMPILING 1)

set(CMAKE_AR           "avr-ar")
set(CMAKE_ASM_COMPILER "avr-gcc")
set(CMAKE_C_COMPILER   "avr-gcc")
set(CMAKE_CXX_COMPILER "avr-g++")
set(CMAKE_LINKER       "avr-ld")
set(CMAKE_OBJCOPY      "avr-objcopy")
set(CMAKE_RANLIB       "avr-ranlib")
set(CMAKE_STRIP        "avr-strip")
set(CMAKE_SIZE         "avr-size")

# Set project.
####################################################################################################
cmake_minimum_required(VERSION 3.00)
project(quadcopter-motorcontroller
    VERSION 1.0
    LANGUAGES C
    )

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

# Clear default compile flags.
####################################################################################################
set(CMAKE_C_FLAGS                "")
set(CMAKE_C_FLAGS_DEBUG          "")
set(CMAKE_C_FLAGS_RELEASE        "")
set(CMAKE_C_FLAGS_MINSIZEREL     "")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "")

# Set input files.
####################################################################################################
file(GLOB_RECURSE USER_SOURCES  "src/*.c")
set(DEVICE_INCLUDES             "${CMAKE_SOURCE_DIR}/lib/include")
set(DEVICE_LIBRARIES            "${CMAKE_SOURCE_DIR}/lib/built")
set(LINKER_SCRIPT               "${CMAKE_SOURCE_DIR}/src/avrxmega3.xn")

# Set output file names.
####################################################################################################
set(PROJECT_ELF "${PROJECT_NAME}.elf")
set(PROJECT_HEX "${PROJECT_NAME}.hex")
set(PROJECT_BIN "${PROJECT_NAME}.bin")

# Configure the elf file.
####################################################################################################
add_executable(${PROJECT_ELF}
    ${USER_SOURCES}
    )

target_compile_options(${PROJECT_ELF}
    PUBLIC -mmcu=attiny3217 -Os -std=c99 -fdata-sections -ffunction-sections -fno-common
    PUBLIC -B "${DEVICE_LIBRARIES}"
    PRIVATE -Wall -Wextra -Wshadow -Wdouble-promotion -Wundef
    )

target_include_directories(${PROJECT_ELF}
    PUBLIC "${DEVICE_INCLUDES}"
    )
    
target_link_options(${PROJECT_ELF}
    PRIVATE -mmcu=attiny3217 -Os -std=c99 -fdata-sections -ffunction-sections -fno-common
    PUBLIC -B "${DEVICE_LIBRARIES}"
    PRIVATE "LINKER:--gc-sections,-T${LINKER_SCRIPT}"
    )

# Add bin and hex files.
####################################################################################################
add_custom_target(${PROJECT_HEX} ALL DEPENDS ${PROJECT_ELF})
add_custom_target(${PROJECT_BIN} ALL DEPENDS ${PROJECT_ELF})

add_custom_command(TARGET ${PROJECT_HEX}
        COMMENT "Building hex file"
        COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_ELF} ${PROJECT_HEX}
        )

add_custom_command(TARGET ${PROJECT_BIN}
        COMMENT "Building bin file"
        COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_ELF} ${PROJECT_BIN}
        )
