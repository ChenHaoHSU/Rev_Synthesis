parser.d: ../../include/parser.h 
../../include/parser.h: parser.h
	@rm -f ../../include/parser.h
	@ln -fs ../src/parser/parser.h ../../include/parser.h
