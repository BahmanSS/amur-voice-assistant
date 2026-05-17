set(TOOLCHAIN_PREFIX $ENV{MIK32_TOOLCHAIN_DIR}/riscv-none-elf-)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)

set(CMAKE_C_FLAGS "-march=rv32imc_zicsr_zifencei -mabi=ilp32 -O3 -ffunction-sections")
set(CMAKE_ASM_FLAGS ${CMAKE_C_FLAGS})

set(CMAKE_EXE_LINKER_FLAGS " \
    -T ${CMAKE_SOURCE_DIR}/hardware/mik32v2-shared/ldscripts/spifi.ld \
    -L ${CMAKE_SOURCE_DIR}/hardware/mik32v2-shared/ldscripts \
    -Wl,-Map,${CMAKE_PROJECT_NAME}.map \
    -Xlinker --gc-sections -nostartfiles \
")

set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")