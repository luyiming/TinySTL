.PHONY: test clean

test :
	@cd TinySTL/test; make test

clean :
	@cd TinySTL/test; make clean
	rm -f TinySTL/*.gch TinySTL/test/*.gch TinySTL/detail/*.gch
