.PHONY: engine-run
engine-run:
	cd Engine && make && cd ..
	cd Application && make run

engine-build-delete: 
	cd Engine && make clean && cd ..
	cd Application && make clean