.PHONY: build
build:
	mkdir -p build
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make -j 6

clean:
	rm -rf build

default: build
