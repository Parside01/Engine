build:
	mkdir -p build 
	cd build && cmake .. && make -j$(nproc)
clean:
	rm -rf build
run: 
	mkdir -p build 
	cd build && cmake .. && make -j$(nproc) && ./Sandbox
default: 
	run