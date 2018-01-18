verify.d: ../../include/verifier.h 
../../include/verifier.h: verifier.h
	@rm -f ../../include/verifier.h
	@ln -fs ../src/verify/verifier.h ../../include/verifier.h
