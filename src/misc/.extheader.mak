misc.d: ../../include/argHandler.hpp ../../include/global.hpp ../../include/paramHandler.hpp ../../include/util.hpp 
../../include/argHandler.hpp: argHandler.hpp
	@rm -f ../../include/argHandler.hpp
	@ln -fs ../src/misc/argHandler.hpp ../../include/argHandler.hpp
../../include/global.hpp: global.hpp
	@rm -f ../../include/global.hpp
	@ln -fs ../src/misc/global.hpp ../../include/global.hpp
../../include/paramHandler.hpp: paramHandler.hpp
	@rm -f ../../include/paramHandler.hpp
	@ln -fs ../src/misc/paramHandler.hpp ../../include/paramHandler.hpp
../../include/util.hpp: util.hpp
	@rm -f ../../include/util.hpp
	@ln -fs ../src/misc/util.hpp ../../include/util.hpp
