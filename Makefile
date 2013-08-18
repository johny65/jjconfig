SALIDA=lib

all: dirs libjjconfig.a

dirs:
	mkdir -p ${SALIDA}
	
libjjconfig.a: jjconfig.o
	ar -rcs ${SALIDA}/$@ $<
	cp src/jjConfig.h ${SALIDA}/jjconfig.h

jjconfig.o: src/jjConfig.cpp src/jjConfig.h
	g++ -c $< -o $@ -static -O2 -s

clean:
	rm jjconfig.o
	rm -R ${SALIDA}

doc: Doxyfile
	doxygen

.PHONY: all dirs clean doc