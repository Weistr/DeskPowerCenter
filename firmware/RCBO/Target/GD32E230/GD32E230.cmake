
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_compile_options(-mcpu=cortex-m23 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

add_compile_options(-O0 -g)

include_directories(
    ${PROJECT_SOURCE_DIR}/Lib/Src/Device/Mcu/GD32E230/GD32E23x_Firmware_Library_V210/CMSIS
    ${PROJECT_SOURCE_DIR}/Lib/Src/Device/Mcu/GD32E230/GD32E23x_Firmware_Library_V210/CMSIS/GD/GD32E23x/Include
    ${PROJECT_SOURCE_DIR}/Lib/Src/Device/Mcu/GD32E230/GD32E23x_Firmware_Library_V210/GD32E23x_standard_peripheral/Include
    ${PROJECT_SOURCE_DIR}/Lib/Src/Device/Mcu/GD32E230/Inc
    ${PROJECT_SOURCE_DIR}/Lib/Src/Device/LED
    ${PROJECT_SOURCE_DIR}/Lib/Src/Task
    ${PROJECT_SOURCE_DIR}/Lib/Src/Delay
    ${PROJECT_SOURCE_DIR}/Target/GD32E230/Src/App/Inc
    ${PROJECT_SOURCE_DIR}/Target/GD32E230/Src/HwConfig/Inc

)
add_definitions(-DDEBUG -DGD32E230 -DGD32E23x)

#请在此处此处添加.c文件目录
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/Lib/Src/Device/Mcu/GD32E230/GD32E23x_Firmware_Library_V210/CMSIS/GD/GD32E23x/Source/GCC/startup_gd32e23x.s"    
    "${PROJECT_SOURCE_DIR}/Lib/Src/Device/Mcu/GD32E230/GD32E23x_Firmware_Library_V210/CMSIS/GD/GD32E23x/Source/*.c"
    "${PROJECT_SOURCE_DIR}/Lib/Src/Device/Mcu/GD32E230/GD32E23x_Firmware_Library_V210/GD32E23x_standard_peripheral/Source/*.c"
    "${PROJECT_SOURCE_DIR}/Lib/Src/Device/Mcu/GD32E230/*.c"
    "${PROJECT_SOURCE_DIR}/Lib/Src/Device/LED/*.c"
    "${PROJECT_SOURCE_DIR}/Lib/Src/Task/*.c"
    "${PROJECT_SOURCE_DIR}/Lib/Src/Delay/*.c"    
    "${PROJECT_SOURCE_DIR}/Target/GD32E230/Src/*.c"
    "${PROJECT_SOURCE_DIR}/Target/GD32E230/Src/**/*.c"
    "${PROJECT_SOURCE_DIR}/Target/GD32E230/Src/HwConfig/*.c"
 
)
set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/gd32e23x_flash.ld)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
#add_link_options(-Wl,--no-warn-rwx-segments)
add_link_options(-mcpu=cortex-m23 -mthumb -mthumb-interwork)
add_link_options(-specs=nano.specs)
add_link_options(-T ${LINKER_SCRIPT})

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
