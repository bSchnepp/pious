# Assume x86_64 and not EFI for now.

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR aarch64)
SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

SET(CMAKE_C_COMPILER "clang")
SET(CMAKE_CXX_COMPILER "clang++")
SET(CMAKE_ASM_COMPILER "aarch64-none-elf-as")
SET(CMAKE_LINKER "ld.lld")
SET(CMAKE_OBJCOPY "aarch64-none-elf-objcopy")
SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linkin.ld)
SET(CMAKE_ASM_NASM_OBJECT_FORMAT "elf64")
SET(CMAKE_C_FLAGS "-target aarch64-none-elf -mgeneral-regs-only -mcmodel=large -ffreestanding -nostdlib -c -Wall -Wextra -Wvla -mcpu=cortex-a72 -mtune=cortex-a72 ${CMAKE_C_FLAGS}")
SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> -m aarch64elf -nostdlib -T ${LINKER_SCRIPT} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
SET(CMAKE_CXX_FLAGS "-target aarch64-none-elf -mcmodel=large -mgeneral-regs-only -ffreestanding -nostdlib -c -Wall -Wextra -Wvla -fno-rtti -fno-exceptions -mcpu=cortex-a72 -mtune=cortex-a72 ${CMAKE_C_FLAGS}")
SET(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> -m aarch64elf -nostdlib -T ${LINKER_SCRIPT} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

SET(CMAKE_EXE_LINKER_FLAGS "-nostdlib -nostartfiles")

SET(TARGET_SYSTEM "bcm2711")
SET(TARGET_SYSTEM_BCM2711 ON)

# Don't even try with host stuff.
SET(CMAKE_SHARED_LIBRARY_PREFIX "")
SET(CMAKE_SHARED_MODULE_PREFIX "")


