sudokuloeser: input.o input_nstd.o main.o output.o output_nstd.o output_std.o solver.o solver_nstd.o solver_std.o
	gcc -lrt -o sudokuloeser input.o input_nstd.o main.o output.o output_nstd.o output_std.o solver.o solver_nstd.o solver_std.o

input.o: input.c
	gcc -Wall -pedantic -c input.c
input_nstd.o: input_nstd.c
	gcc -Wall -pedantic -c input_nstd.c
main.o: main.c
	gcc -Wall -pedantic -c main.c
output.o: output.c
	gcc -Wall -pedantic -c output.c
output_nstd.o: output_nstd.c
	gcc -Wall -pedantic -c output_nstd.c
output_std.o: output_std.c
	gcc -Wall -pedantic -c output_std.c
solver.o: solver.c
	gcc -Wall -pedantic -c solver.c
solver_nstd.o: solver_nstd.c
	gcc -Wall -pedantic -c solver_nstd.c
solver_std.o: solver_std.c
	gcc -Wall -pedantic -c solver_std.c

clean:
	rm -vf *.o sudokuloeser