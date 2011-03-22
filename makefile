sudokuloeser: sudokuloeser.c
	gcc -Wall -pedantic -lrt sudokuloeser.c -o sudokuloeser

windows: sudokuloeser.c
	i486-mingw32-gcc -Wall -pedantic sudokuloeser.c -o sudokuloeser.exe

win: sudokuloeser.c
	i586-mingw32msvc-gcc -Wall -pedantic sudokuloeser.c -o sudokuloeser.exe
