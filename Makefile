default:
	g++ volimage.cpp -o volimage

volimage.run: volimage.o
	g++ volimage.run volimage.o
volimage.o: volimage.cpp
	g++ -c -o volimage.o volimage.cpp

clean:
	rm -f ./volimage *.o
run:
	./volimage
