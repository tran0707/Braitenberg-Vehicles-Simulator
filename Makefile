.PHONY: docs

all:
	cd src; make
	cd tests; make

check-style:
	cd src; make check-style

check-style-cse:
	cd src; make check-style-cse
	
clean:
	cd src; make clean
	cd tests; make clean 
	rm -rf build
	rm -rf docs/html
	rm -rf docs/latex

docs:
	doxygen docs/Doxyfile

clobber: clean
	cd src; make clobber
