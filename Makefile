default:
	g++ driver.cpp stu_database.cpp -o driver

driver.run: driver.o stu_database.o
	g++ driver.run driver.o stu_database.o
driver.o: driver.cpp stu_database.h
	g++ -c -o driver.o driver.cpp
stu_database.o: stu_database.cpp stu_database.h
	g++ -c -o stu_database.o stu_database.cpp

clean:
	rm -f ./driver *.o
run:
	./driver
