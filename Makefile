# Tinotenda Muzambi
# MZMTIN002

default:
	@g++ main.cpp volimage.cpp -o volimage

main.run: main.o volimage.o
	g++ main.run main.o volimage.o
main.o: main.cpp volimage.h
	g++ -c -o main.o main.cpp
volimage.o: volimage.cpp volimage.h
	g++ -c -o volimage.o volimage.cpp

clean:
	@rm -f ./volimage *.o
	@rm -f *.dat
	@rm -f *.bin
	@rm -f *.raw
