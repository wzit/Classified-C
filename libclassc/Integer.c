
#include "Classified-C.h"

Class IntegerClass = NULL;

static void *newWithInt(void *v, va_list *args);

static void *initWithInt(void *v, va_list *args);
static void *dealloc(void *v, va_list *args);
static void *equals(void *v, va_list *args);
static void *description(void *v, va_list *args);

void integer_class_init() {
	IntegerClass = msg(ClassClass, "new", "Integer", ObjectClass);

	push_back(IntegerClass->static_methods, mmethod("newWithInt", &newWithInt));
	
	push_back(IntegerClass->instance_methods, mmethod("initWithInt", &initWithInt));
	push_back(IntegerClass->instance_methods, mmethod("dealloc", &dealloc));
	push_back(IntegerClass->instance_methods, mmethod("equals", &equals));
	push_back(IntegerClass->instance_methods, mmethod("description", &description));
}

void *newWithInt(void *v, va_list *args) {
	Integer o = cc_alloc(sizeof(struct _Integer));
	initWithInt(o, args);
	((Object)o)->root = IntegerClass;
	return o;
}

void *initWithInt(void *v, va_list *args) {
	Integer o = (Integer)v;
	o->value = va_arg(*args, size_t);
	return o;
}

void *dealloc(void *v, va_list *args) {
	Integer o = (Integer)v;
	return msg_cast(ObjectClass, o, "dealloc");
}

void *equals(void *v, va_list *args) {
	Integer o = (Integer)v;
	size_t other = va_arg(*args, size_t);

	if (o->value == other) {
		return YES;
	}

	return NO;
}

void *description(void *v, va_list *args) {
	Integer o = (Integer)v;
	return msg(StringClass, "newWithFormatCString", "%d", o->value);
}