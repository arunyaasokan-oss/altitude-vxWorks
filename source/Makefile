# Just pass the command down to the next level
SUBDIRS := $(wildcard */.)

.PHONY: all clean $(SUBDIRS)

all clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)