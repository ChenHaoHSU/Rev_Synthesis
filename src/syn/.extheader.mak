syn.d: ../../include/synthesis.h 
../../include/synthesis.h: synthesis.h
	@rm -f ../../include/synthesis.h
	@ln -fs ../src/syn/synthesis.h ../../include/synthesis.h
