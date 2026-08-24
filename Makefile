export VCPKG_ROOT ?= $(CURDIR)/vcpkg

SOURCES := $(shell find src tests -name '*.cpp' -o -name '*.hpp')

.PHONY: all build test run clean distclean asan tidy format format-check help

all: build

help:
	@echo "make            - configure + build (debug)"
	@echo "make test       - build, then run the test suite"
	@echo "make run        - build, then run gbcemu"
	@echo "make asan       - configure + build + test with ASan/UBSan"
	@echo "make tidy       - configure + build with clang-tidy (needs clang)"
	@echo "make format     - reformat all sources with clang-format"
	@echo "make format-check - check formatting without modifying files"
	@echo "make clean      - remove the debug build directory"
	@echo "make distclean  - remove all build directories (all presets)"

build:
	cmake --preset debug
	cmake --build --preset debug

test: build
	ctest --preset debug

run: build
	./build/debug/gbcemu

asan:
	cmake --preset asan
	cmake --build --preset asan
	ctest --preset asan

tidy:
	CC=clang CXX=clang++ cmake --preset tidy
	CC=clang CXX=clang++ cmake --build --preset tidy

format:
	clang-format -i $(SOURCES)

format-check:
	clang-format --dry-run --Werror $(SOURCES)

clean:
	rm -rf build/debug

distclean:
	rm -rf build
