MAKE = make
.PHONY: code doc clean tests style pov bench

all: code tests doc style pov 

code:
	$(MAKE) -C code

tests: 
	$(MAKE) -C tests

doc:
	$(MAKE) -C doc


style : 
	astyle -A1 --recursive *.cxx *.h 
	find . -type f -name '*.orig' -delete

clean: 
	$(MAKE) -C code clean
	$(MAKE) -C tests clean
	$(MAKE) -C doc clean
	$(MAKE) -C benchmark clean
	rm -rf .vscode

pov : 
	povray code/src/visu.pov -Oresultat.png

bench : 
	$(MAKE) -C code 
	$(MAKE) -C benchmark

