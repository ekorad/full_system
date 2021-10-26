LIBS := libs
LR_SYSTEM := lr_system

TARGETS := $(LIBS) $(LR_SYSTEM)

TARGETS_ALL := $(foreach trg,$(TARGETS), $(addprefix $(trg),-all))
TARGETS_CLEAN := $(foreach trg,$(TARGETS), $(addprefix $(trg),-clean))
TARGETS_INSTALL := $(foreach trg,$(TARGETS), $(addprefix $(trg),-install))
TARGETS_UNINSTALL := $(foreach trg,$(TARGETS), $(addprefix $(trg),-uninstall))
TARGETS_REINSTALL := $(foreach trg,$(TARGETS), $(addprefix $(trg),-reinstall))

ALL_TARGETS := all all-clean all-install all-uninstall all-reinstall
ALL_TARGETS += $(TARGETS_ALL) $(TARGETS_CLEAN) $(TARGETS_INSTALL) $(TARGETS_UNINSTALL) $(TARGETS_REINSTALL)

.PHONY: $(ALL_TARGETS)

all: $(TARGETS_ALL)

all-clean: $(TARGETS_CLEAN)

all-install: $(TARGETS_INSTALL)

all-uninstall: $(TARGETS_UNINSTALL)

all-reinstall: $(TARGETS_REINSTALL)

$(TARGETS_ALL): %-all:
	$(MAKE) -C $* all

$(TARGETS_CLEAN): %-clean:
	$(MAKE) -C $* all-clean

$(TARGETS_INSTALL): %-install:
	$(MAKE) -C $* all-install

$(TARGETS_UNINSTALL): %-uninstall:
	$(MAKE) -C $* all-uninstall

$(TARGETS_REINSTALL): %-reinstall:
	$(MAKE) -C $* all-reinstall