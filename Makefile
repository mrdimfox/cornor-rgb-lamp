ifeq ($(OS),Windows_NT)
	RM=powershell rm -Force
else
	RM=rm -rf
endif

ifndef BOARD
	BOARD=nucleo_l476rg
endif

# See https://docs.zephyrproject.org/latest/guides/zephyr_cmake_package.html
# Only for ver 2.2.99+
.PHONY: zephyr-export
zephyr-export:
	west zephyr-export

.PHONY: configure
configure:
	west build -b $(BOARD) -p auto app --cmake-only

.PHONY: build
build:
	west build -b $(BOARD) -p auto app

.PHONY: init-repo
init-repo:
	west update

.PHONY: reinit-repo
reinit-repo:
	west update

.PHONY: clean
clean:
	$(RM) build
