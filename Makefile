FLAGS := -Wall -pedantic
LIBS :=

ifeq ($(ARCH),win)
	GCC := i486-mingw32-gcc
	OUTPUT := sudokuloeser.exe
else
	GCC := gcc
	LIBS +=-lrt
	OUTPUT := sudokuloeser
endif

ifeq ($(BUILD),devel)
	FLAGS += -ggdb
endif

sudokuloeser: input.o input_nstd.o main.o output.o output_nstd.o output_std.o solver.o solver_nstd.o solver_std.o html.o
	${GCC} ${FLAGS} ${LIBS} -o ${OUTPUT} input.o input_nstd.o main.o output.o output_nstd.o output_std.o solver.o solver_nstd.o solver_std.o html.o

install: sudokuloeser
	install -vDm755 sudokuloeser /usr/bin/sudokuloeser

uninstall:
	rm /usr/bin/sudokuloeser

input.o: input.c input.h types.h
	${GCC} ${FLAGS} -c input.c
input_nstd.o: input_nstd.c input_nstd.h types.h
	${GCC} ${FLAGS} -c input_nstd.c
main.o: main.c main.h types.h input.h input_nstd.h solver.h solver_std.h solver_nstd.h output.h output_std.h output_nstd.h html.h
	${GCC} ${FLAGS} -c main.c
output.o: output.c output.h types.h
	${GCC} ${FLAGS} -c output.c
output_nstd.o: output_nstd.c output_nstd.h types.h
	${GCC} ${FLAGS} -c output_nstd.c
output_std.o: output_std.c output_std.h types.h
	${GCC} ${FLAGS} -c output_std.c
solver.o: solver.c solver.h types.h
	${GCC} ${FLAGS} -c solver.c
solver_nstd.o: solver_nstd.c solver_nstd.h types.h
	${GCC} ${FLAGS} -c solver_nstd.c
solver_std.o: solver_std.c solver_std.h types.h
	${GCC} ${FLAGS} -c solver_std.c
html.o: html.c html.h types.h
	${GCC} ${FLAGS} -c html.c

clean:
	rm -vf *.o

clean_all:
	rm -vf *.o sudokuloeser sudokuloeser.exe

help:
	@echo "make [target] [options]"
	@echo 
	@echo "Targets:"
	@echo "  sudokuloeser  creates the executable (default)"
	@echo "  install       installs the binary to /usr/bin/"
	@echo "  uninstall     uninstalls the binary"
	@echo "  clean         Remove objects"
	@echo "  clean_all     Remove objects and executables"
	@echo "  help          Print this help."
	@echo "Options:"
	@echo "  BUILD=devel   include debug symbols"
	@echo "  "
	@echo "  ARCH=win      Cross Compile for Windows"

