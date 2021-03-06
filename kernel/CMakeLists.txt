INCLUDE_DIRECTORIES(inc)

LIST(APPEND KERNEL_SOURCES boot.S)

LIST(APPEND KERNEL_HEADERS mmio.hpp)
LIST(APPEND KERNEL_SOURCES mmio.cpp)

IF (TARGET_SYSTEM STREQUAL "bcm2711")
LIST(APPEND KERNEL_HEADERS bcm2711/mailbox.hpp)
LIST(APPEND KERNEL_SOURCES bcm2711/mailbox.cpp)

LIST(APPEND KERNEL_HEADERS bcm2711/uart.hpp)
LIST(APPEND KERNEL_SOURCES bcm2711/uart.cpp)

LIST(APPEND KERNEL_HEADERS bcm2711/gpio.hpp)
LIST(APPEND KERNEL_SOURCES bcm2711/gpio.cpp)

LIST(APPEND KERNEL_HEADERS bcm2711/fb.hpp)
LIST(APPEND KERNEL_SOURCES bcm2711/fb.cpp)

LIST(APPEND KERNEL_HEADERS bcm2711/timer.hpp)
LIST(APPEND KERNEL_SOURCES bcm2711/timer.cpp)

LIST(APPEND KERNEL_HEADERS bcm2711/contrib.hpp)
LIST(APPEND KERNEL_SOURCES bcm2711/contrib.cpp)

LIST(APPEND KERNEL_HEADERS arm/gic.hpp)
LIST(APPEND KERNEL_SOURCES arm/gic.cpp)

ENDIF(TARGET_SYSTEM STREQUAL "bcm2711")

ADD_LIBRARY(Kernel STATIC
	${KERNEL_HEADERS}
	${KERNEL_SOURCES})
