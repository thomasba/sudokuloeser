sudokuloeser: sudokuloeser.c
	gcc -Wall -pedantic -O3 -lrt sudokuloeser.c -o sudokuloeser

windows: sudokuloeser.c
	sh -c '[ -x /usr/bin/i486-mingw32-gcc ] && i486-mingw32-gcc -Wall -pedantic sudokuloeser.c -o sudokuloeser.exe || [ -x /usr/bin/i586-mingw32msvc-gcc ] && i586-mingw32msvc-gcc -Wall -pedantic sudokuloeser.c -o sudokuloeser.exe || echo "Compiler not found"'
