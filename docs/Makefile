# plantuml diagram compilation configuration
FORMAT ?= svg

PLANTUML := $(shell command -v plantuml 2> /dev/null)

DIAGRAM_DIR := diagrams
OUTPUT_DIR := $(DIAGRAM_DIR)/generated

DIAGRAM_SRCS := $(wildcard $(DIAGRAM_DIR)/*.puml)

.PHONY: check-puml diagram clean

ifeq ($(strip $(PLANTUML)),)
$(error plantuml not found)
endif

# compile the uml diagrams with `make diagram`
diagram: check-puml
	@mkdir -p "$(OUTPUT_DIR)"
	@"$(PLANTUML)" -t$(FORMAT) -o "$(abspath $(OUTPUT_DIR))" $(DIAGRAM_SRCS)

# check that the plantuml binary / executable is not empty
check-puml:
	@test -n "$(PLANTUML)"

# delete generated files using `make clean`
clean: 
	@rm -rf $(OUTPUT_DIR)