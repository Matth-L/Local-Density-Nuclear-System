MAKE = make
.PHONY: code doc clean tests style pov bench

all: code tests doc style pov 

code:
	mkdir -p bin
	mkdir -p code/obj
	$(MAKE) -C code

tests:
	mkdir -p bin
	mkdir -p code/obj
	$(MAKE) -C tests

doc:
	$(MAKE) -C doc

bench :
	mkdir -p bin
	mkdir -p code/obj
	$(MAKE) -C code 
	$(MAKE) -C benchmark

style : 
	astyle -A1 --recursive *.cxx *.h 
	find . -type f -name '*.orig' -delete

pov : 
	povray code/src/visu.pov -Oresultat.png

clean: 
	$(MAKE) -C code clean
	$(MAKE) -C tests clean
	$(MAKE) -C doc clean
	$(MAKE) -C benchmark clean
	rm -rf .vscode
	rm -rf bin
	rm -rf code/obj
	rm -f resultat.png


