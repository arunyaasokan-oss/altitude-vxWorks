# Compiler and Flags
CC      = wr-cc
CFLAGS  = -rtp -static
TARGET  = altitude.vxe
SRC     = sensor.c alarm.c altitudemeasure.c main.c
DEPS    = sensor.h alarm.h altitudemeasure.h

.PHONY: all clean analyze

all: $(TARGET)

# The Static Analysis Target
analyze:
	@echo "--- Running Static Analysis on Altitude Module ---"
	$(CC) $(CFLAGS) -c --analyze $(SRC)
	@echo "--- Running Cppcheck ---"
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --std=c99 --platform=unix32 $(SRC)

$(TARGET): $(SRC) $(DEPS)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)