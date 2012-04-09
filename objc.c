
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "list.h"

#include "objc.h"
#include "objc_null.h"

list *class_list;

int method_name_equals(const void *methodp, va_list args);
int class_name_equals(const void *class, va_list args);

void _objc_init() {
	class_list = create_list();

	push_back(class_list, _objc_null_init());
}

void objc_message_send(var o, string message, void *ret) {
	method *the_method = get_first_occurrence(o->class->v_table, method_name_equals, message);

	if (!the_method) {
		fprintf(stderr, "Object of class %s does not respond to message \"%s\"\n", o->class->name, message);
		exit(EXIT_FAILURE);
	}

	the_method->f_pointer(o, ret);
}

int method_name_equals(const void *methodp, va_list args) {
	string name;
	method *the_method = (method *)methodp;

	vsprintf(name, "%s", args);

	if (strcmp(the_method->name, name) == 0) {
		return 1;
	}

	return 0;
}

obj *objc_constructor(string class_name) {
	class *the_class = get_first_occurrence(class_list, class_name_equals, class_name);

	if (!the_class) {
		fprintf(stderr, "Cannot construct object of class \"%s\"\n", class_name);
		exit(EXIT_FAILURE);
	}

	return the_class->constructor();
}

int class_name_equals(const void *classp, va_list args) {
	string name;
	class *the_class = (class *)classp;

	vsprintf(name, "%s", args);

	if (strcmp(the_class->name, name) == 0) {
		return 1;
	}

	return 0;
}