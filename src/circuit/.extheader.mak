circuit.d: ../../include/circuit.h ../../include/spec.h ../../include/gate.h ../../include/model.h 
../../include/circuit.h: circuit.h
	@rm -f ../../include/circuit.h
	@ln -fs ../src/circuit/circuit.h ../../include/circuit.h
../../include/spec.h: spec.h
	@rm -f ../../include/spec.h
	@ln -fs ../src/circuit/spec.h ../../include/spec.h
../../include/gate.h: gate.h
	@rm -f ../../include/gate.h
	@ln -fs ../src/circuit/gate.h ../../include/gate.h
../../include/model.h: model.h
	@rm -f ../../include/model.h
	@ln -fs ../src/circuit/model.h ../../include/model.h
