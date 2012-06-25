
#define CLASS LinkedList
#define SUPER Object

#include "Classified-C.h"

proto(new);
proto(init);
proto(dealloc);
proto(description);
proto(length);
proto(pushFront);
proto(pushBack);
proto(removeFront);
proto(removeBack);
proto(getFront);
proto(getBack);
proto(get);
proto(performOnEach);
proto(clear);

defclass
	static(new);

	instance(init);
	instance(dealloc);
	instance(description);
	instance(length);
	instance(pushFront);
	instance(pushBack);
	instance(removeFront);
	instance(removeBack);
	instance(getFront);
	instance(getBack);
	instance(get);
	instance(performOnEach);
	instance(clear);
end

defcon(new)
	init(self, args);

	return self;
end

def(init)
	self->value = create_list();

	return self;
end

def(dealloc)
	free_list(self->value, &msg_release);

	return msgSuper("dealloc");
end

def(description)
	return msg(StringClass, "newWithFormatCString", "%s", "[LinkedList]");
end

def(length)
	return msg(msg(IntegerClass, "newWithInt", self->value->size), "autorelease");
end

def(pushFront)
	Object o = NEXT_ARG(Object);
	push_front(self->value, o);
	msg(o, "retain");

	return self;
end

def(pushBack)
	Object o = NEXT_ARG(Object);
	push_back(self->value, o);
	msg(o, "retain");

	return self;
end

def(removeFront)
	remove_front(self->value, &msg_release);

	return self;
end

def(removeBack)
	remove_back(self->value, &msg_release);

	return self;
end

def(getFront)
	return ll_front(self->value);
end

def(getBack)
	return ll_back(self->value);
end

def(get)
	return ll_get_index(self->value, NEXT_ARG(int));
end

def(performOnEach)
	cstring method_name = NEXT_ARG(cstring);

	traverse_with_args(self->value, call_method, method_name);

	return self;
end

def(clear)
	empty_list(self->value, &msg_release);

	return self;
end
