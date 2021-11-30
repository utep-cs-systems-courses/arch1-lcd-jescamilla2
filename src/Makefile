# makefile configuration
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} buzzer.o led.o switches.o stateMachines.o wdt_handler.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: main.elf
	msp430loader.sh  $^

main-s.elf: ${COMMON_OBJECTS} buzzer.o led.o switches.o stateMachines.o wdt_handler.o main.o led-a.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load-s: main-s.elf
	msp430loader.sh  $^


clean: $^
	rm -f *.o *.elf *.c~ *.h~ *.c# *.s~

buzzer.o: buzzer.h
led.o: led.h
switches.o: switches.h led.h
stateMachines.o: stateMachines.h led.h
main.o: buzzer.h led.h switches.h stateMachines.h
