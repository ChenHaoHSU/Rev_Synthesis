gnuplot.d: ../../include/gnuplotter.h ../../include/gnuplot_i.h 
../../include/gnuplotter.h: gnuplotter.h
	@rm -f ../../include/gnuplotter.h
	@ln -fs ../src/gnuplot/gnuplotter.h ../../include/gnuplotter.h
../../include/gnuplot_i.h: gnuplot_i.h
	@rm -f ../../include/gnuplot_i.h
	@ln -fs ../src/gnuplot/gnuplot_i.h ../../include/gnuplot_i.h
