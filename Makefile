NEED_DOC ?= false

all: run

.SILENT: build

.PHONY: clean

.ONESHELL:

reconf:
	meson build -DNEED_DOC=$(NEED_DOC) $(PKG_CONFIG_OPTION) --reconfigure

test: build/test/
	meson test -C build

build:
	meson build -DNEED_DOC=$(NEED_DOC) $(PKG_CONFIG_OPTION)
	meson compile -C build

clang:
	meson build --native-file=clang-tool.ini -DNEED_DOC=$(NEED_DOC)
	meson compile -C build

compile:
	meson compile -C build

clean:
	rm -rf build/

run: build/src/
	build/src/cpp_nn

