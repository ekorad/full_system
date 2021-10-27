BASE_LRSYS_DIR := ./lr_system
TX_ARTIFACT_NAME := transmitter
RX_ARTIFACT_NAME := receiver

TARGETS := $(TX_ARTIFACT_NAME) $(RX_ARTIFACT_NAME)
TARGETS_CLEAN := $(addsuffix -clean,$(TARGETS))

.PHONY: $(TX_ARTIFACT_NAME)

all: $(TX_ARTIFACT_NAME) $(RX_ARTIFACT_NAME)

$(TARGETS):
	$(MAKE) -C $(BASE_LRSYS_DIR)/$@
	install -m755 $(BASE_LRSYS_DIR)/$@/$@ .

$(TARGETS_CLEAN): %-clean:
	$(MAKE) -C $(BASE_LRSYS_DIR)/$* clean
	$(RM) $*

clean:
	$(MAKE) -C $(BASE_LRSYS_DIR)/$(TX_ARTIFACT_NAME) clean
	$(MAKE) -C $(BASE_LRSYS_DIR)/$(RX_ARTIFACT_NAME) clean
	$(RM) $(TARGETS)

