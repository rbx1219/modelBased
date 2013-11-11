CC = g++

# Flags for -c compilation and linking
FLAG = -c -g
LFLAG = -lm

OBJS  = main.o \
	random.o utility.o \
	gene.o chromosome.o population.o objfunc.o \
	intlist.o subset.o mpm.o cache.o ecga.o model.o

OBJS2 = bisection.o\
		random.o utility.o\
		 gene.o chromosome.o population.o objfunc.o \
	     intlist.o subset.o mpm.o cache.o ecga.o model.o

all: ecga bisection

ecga: $(OBJS)
	$(CC) $(LFLAG) -o ecga $(OBJS)

bisection: $(OBJS2)
	$(CC) $(LFLAG) -o bisection $(OBJS2)

#--- UTILITY stuff --------------------------------------------------------

# random number generator
random.o: random.cpp random.hpp
	$(CC) $(FLAG) random.cpp

# utility functions and procedures
utility.o: utility.cpp utility.hpp random.hpp
	$(CC) $(FLAG) utility.cpp


#--- general GA stuff -----------------------------------------------------

# gene
gene.o: gene.cpp gene.hpp random.hpp
	$(CC) $(FLAG) gene.cpp
# chromosome
chromosome.o: chromosome.cpp chromosome.hpp random.hpp gene.hpp parameter.hpp
	$(CC) $(FLAG) chromosome.cpp

# population
population.o: population.cpp population.hpp parameter.hpp utility.hpp
	$(CC) $(FLAG) population.cpp

# objective function
objfunc.o: objfunc.cpp objfunc.hpp
	$(CC) $(FLAG) objfunc.cpp

#model
model.o: model.cpp model.hpp intlist.hpp subset.hpp
#--- ECGA stuff ----------------------------------------------------------

# list of integers in C++
intlist.o: intlist.cpp intlist.hpp
	$(CC) $(FLAG) intlist.cpp

# a set in the mpm
subset.o: subset.cpp subset.hpp parameter.hpp utility.hpp population.hpp 
	$(CC) $(FLAG) subset.cpp

# an MPM is a collection of "subsets"
mpm.o: mpm.cpp mpm.hpp subset.hpp population.hpp parameter.hpp cache.hpp
	$(CC) $(FLAG) mpm.cpp

# cache to store mergers
cache.o: cache.cpp cache.hpp parameter.hpp subset.hpp
	$(CC) $(FLAG) cache.cpp

# ECGA
ecga.o: ecga.cpp ecga.hpp parameter.hpp population.hpp mpm.hpp utility.hpp
	$(CC) $(FLAG) ecga.cpp

#--- MAIN  -----------------------------------------------------------------

main.o: main.cpp utility.hpp intlist.hpp random.hpp parameter.hpp ecga.hpp
	$(CC) $(FLAG) main.cpp

bisection.o: bisection.cpp utility.hpp intlist.hpp random.hpp parameter.hpp ecga.hpp
	$(CC) $(FLAG) bisection.cpp
