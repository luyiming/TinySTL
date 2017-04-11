.PHONY: all test clean

all:
	@cd test; make all

test:
	@cd test; make test

clean:
	@cd test; make clean
	rm -f include/*.gch include/detail/*.gch
