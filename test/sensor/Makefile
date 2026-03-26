CC       = gcc
CXX      = g++
CXXFLAGS = -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage
CFLAGS   = -DUNIT_TEST --coverage -Iinclude -I.
LDFLAGS += -fprofile-arcs -ftest-coverage

TESTSRC  = hltc_altitude_monitoring.cpp ../../source/sensor/sensor.c mock_sensor.c
TESTOBJ  = altitudemeasure.o alarm.o sensor.o
OUTDIR   = gtest
TARGET   = $(OUTDIR)/runTests
COV_DIR  = coverage

.PHONY: test clean

# Compile C sources into OUTDIR
$(OUTDIR)/%.o: ../../source/sensor/%.c
	@echo "Compile C sources into $(OUTDIR)"
	@mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ test source into OUTDIR
$(OUTDIR)/%.o: %.cpp
	@mkdir -p $(OUTDIR)
	@echo "Compile C++ test source into $(OUTDIR)"
	$(CXX) $(CFLAGS) -c $< -o $@

# Compile C++ test source into OUTDIR
$(OUTDIR)/%.o: %.c
	@mkdir -p $(OUTDIR)
	@echo "Compile C test source into $(OUTDIR)"
	$(CC) $(CFLAGS) -c $< -o $@

test: $(addprefix $(OUTDIR)/,$(TESTOBJ)) $(OUTDIR)/hltc_altitude_monitoring.o  $(OUTDIR)/sensor.o $(OUTDIR)/mock_sensor.o
	$(CXX) --coverage $^ $(CXXFLAGS) -o $(TARGET)
	@echo "Run test target $(TARGET)"
	./$(TARGET)
	@echo ">>> Generating coverage..."
	mkdir -p $(COV_DIR)
	gcov -o $(OUTDIR) $(TESTSRC) -n
	lcov --capture --directory $(OUTDIR) --output-file $(COV_DIR)/coverage.info --ignore-errors mismatch
	lcov --remove $(COV_DIR)/coverage.info '/usr/*' --output-file $(COV_DIR)/coverage.info
	genhtml $(COV_DIR)/coverage.info --output-directory $(COV_DIR)
	@echo ">>> Coverage report available in $(COV_DIR)/index.html"

clean:
	rm -rf $(OUTDIR) $(COV_DIR)
