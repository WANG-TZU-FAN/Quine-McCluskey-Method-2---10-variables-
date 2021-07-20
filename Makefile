E14061313_Logic_System_QM: QM.o
	g++ -o E14061313_Logic_System_QM QM.o

QM.o: QM.cpp QM.h
	g++ -c QM.cpp

clean:
	rm QM *.o
