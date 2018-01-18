CXX = g++
EXE = revSpecGen
C11 = -std=c++11

#CFLAGS = -g -Wall $(C11)
#CFLAGS = -O3 -Wall -g $(C11)
CFLAGS = -O3 -Wall $(C11)

CSRCS     = $(wildcard *.cpp) $(wildcard *.c)
CHDRS     = $(wildcard *.h)
COBJS     = $(addsuffix .o, $(basename $(CSRCS)))

$(EXE): $(COBJS) 
	@echo ">> Building $(EXE) ..."
	@$(CXX) -o $@ $(COBJS) $(CFLAGS)

%.o: %.cpp $(CHDRS)
	@echo "> Compiling $< ..."
	@$(CXX) $< -c $(CFLAGS)

clean: 
	@echo "> Removing $(EXE) ..."
	@echo "> Removing *.o ..."
	@rm -f $(EXE) *.o 

cleanall:
	@echo "> Removing $(EXE) ..."
	@echo "> Removing *.o *.cnf *.table *.result ..."
	@rm -f $(EXE) *.o *.cnf *.table *.result
