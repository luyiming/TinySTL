.PHONY: all test clean bench

all:
	@cd test; make all

test:
	@cd test; make test

bench:
	@cd bench; make bench

clean:
	@cd test; make clean
	rm -f include/*.gch include/detail/*.gch
