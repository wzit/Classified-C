
#ifndef CB_OBJECT_H
#define CB_OBJECT_H

typedef struct _CBObject *Object;

struct _CBObject {
	Class root;
	int retaincount;
};

extern Class ObjectClass;

void object_class_init();
Object object_init(void *v);

#endif
