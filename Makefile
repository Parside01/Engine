.PHONY: engine-run
engine-run:
	cd Engine && make && cd ..
	cd Application && make run