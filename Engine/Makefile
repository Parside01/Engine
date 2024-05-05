build:
	mkdir -p build
	cd build && cmake ../
	cd build && make -j$(nproc)

clean:
	rm -rf build

default: build