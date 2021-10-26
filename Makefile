LIBS := libs
SYSTEM := transmitter receiver

TARGETS_ALL := all all-clean all-install all-uninstall all-reinstall
TARGETS_LIB := $(foreach trg,$(TARGETS_ALL), $(addsuffix $(TRG),$(LIBS)))
TARGETS_SYSTEM := $(foreach trg,$(TARGETS_ALL), $(addsuffix $(TRG),$(SYSTEM)))

.PHONY: $(TARGETS_SYSTEM) $(TARGETS_ALL) $(TARGETS_LIB)

all: $(TARGETS_SYSTEM) libs-all



libs-all:
	$(MAKE) -C libs all

libs-all-clean:
	$(MAKE) -C libs all-clean

libs-all-install:
	$(MAKE) -C libs all-install

libs-all-uninstall:
	$(MAKE) -C libs all-uninstall

libs-all-reinstall:
	$(MAKE) -C libs all-reinstall