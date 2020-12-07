# Assume x86_64 and not EFI for now.

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR aarch64)
SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

SET(CMAKE_C_COMPILER "clang")
SET(CMAKE_LINKER "ld.lld")
SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linkin.ld)
SET(CMAKE_ASM_NASM_OBJECT_FORMAT "elf64")
SET(CMAKE_C_FLAGS "-target aarch64-none-elf -ffreestanding -nostdlib -mno-red-zone -c -fno-vectorize -fstack-protector-all -fPIE -fPIC -Wall -Wextra -O2 -Wstrict-prototypes -Wvla -fstack-protector-all ${CMAKE_C_FLAGS}")
SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> -T ${LINKER_SCRIPT} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

# Don't even try with host stuff.
SET(CMAKE_SHARED_LIBRARY_PREFIX "")
SET(CMAKE_SHARED_MODULE_PREFIX "")
