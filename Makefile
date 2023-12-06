MAKE = make

.PHONY: code doc clean tests style 

all: code tests doc 

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

pov : 
	povray code/src/visu.pov -Oresultat.png