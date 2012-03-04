#ifndef main_h__
#define main_h__

int main(int argc, char **argv);
void readOptions(int argc, char **argv, options * o);
void newStandard(options * o);
void newNonStandard(options * o);
void print_help(int argc, char **argv);

#endif /* main_h__ */