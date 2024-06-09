.PHONY: build
build:
	rm -rf build
	mkdir -p build
	cd build && cmake .. && make -j$(nproc)

clean:
	rm -rf build

default: build
