# Get a list of all subdirectories that contain a Makefile
SUBDIRS := $(wildcard */Makefile)
SUBDIRS := $(patsubst %/Makefile,%,$(SUBDIRS))

# Added 'analyze' to .PHONY
.PHONY: all clean analyze $(SUBDIRS)

# Default target
all: $(SUBDIRS)

# New Target: This tells make to run 'analyze' in every sub-module
analyze:
	@echo "Starting System-Wide Static Analysis..."
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir analyze; \
	done
	@echo "Analysis Complete."

# Rule to enter each subdirectory and run make
$(SUBDIRS):
	@echo "------------------------------------------"
	@echo "Building VxWorks module: $@"
	@echo "------------------------------------------"
	$(MAKE) -C $@
	@echo "Done"

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done