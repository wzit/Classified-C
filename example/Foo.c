
#include "../libcbang/CBang.h"
#include "FooClass.h"

int main(int argc, char **argv) {
	cbang_init();
	foo_class_init();

	Object o = message(ObjectClass, "init", NULL);
	message(o, "print");
	o = message(o, "release");
	printf("\n");

	String st = message(StringClass, "initWithString", NULL, "test");
	message(st, "print");
	st = message(st, "release");
	printf("\n");

	File f = message(FileClass, "initWithFilename", NULL, "../README.md");
	Scanner s = message(ScannerClass, "initWithFile", NULL, f);
	Integer i = message(IntegerClass, "initWithInt", NULL, 1);
	while (i->value != 0) {
		String token = message(s, "next");
		fprintf(stderr, "%s ", token->value);
		message(token, "release");

		i = message(i, "release");
		i = message(s, "has_next");
	}
	i = message(i, "release");
	s = message(s, "release");
	f = message(f, "release");
	printf("\n");

	Null n = message(NullClass, "init", NULL);
	message(n, "print");
	printf("\n");
	n = message(n, "release");

	String ohhai = message(StringClass, "initWithString", NULL, "OH HAI!");
	message(ohhai, "print");
	printf("\n");
	ohhai = message(ohhai, "release");

	Foo mys = message(FooClass, "init", NULL, 77, "Foo");
	message(mys, "concatenate", " Fighters");
	message(mys, "print");
	printf("\n");

	i = message(mys, "length");
	printf("Length of string: %d\n", i->value);
	i = message(i, "release");
	mys = message(mys, "release");

	Stack stack = message(StackClass, "init", NULL);
	message(stack, "push", message(StringClass, "initWithString", NULL, "Ryan"));
	message(stack, "push", message(StringClass, "initWithString", NULL, "Tanner"));
	message(stack, "pop");
	// message(stack, "pop");
	String str = message(stack, "peek");
	if (str) {
		printf("%s\n", str->value);
	}
	stack = message(stack, "release");

	printf("\n");
}
