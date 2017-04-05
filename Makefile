.PHONY: test clean

test :
	@cd test; make test

clean :
	@cd test; make clean
	rm -f *.gch test/*.gch detail/*.gch
