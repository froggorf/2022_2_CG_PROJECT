#include "game_world.h"
#include "object.h"

#include <vector>
#include <string>

// 상속 받아서 virtual함수 각각 사용하려면 *로 받아야할듯함
std::vector<Object*> objects[2];

template <class T>
GLvoid add_object(T o, int depth) {
	T* object = new T;
	memcpy(object, &o, sizeof(T));
	objects[depth].push_back(object);
}

template <class T>
GLvoid add_objects(T* o, int depth) {
	int count = sizeof(o) / sizeof(T);
	for (int i = 0; i < count; i++) {
		T* object = new T;
		memcpy(object, &o, sizeof(T));
		objects[depth].push_back(object);
	}
}
//def remove_object(o) :
//    for layer in objects :
//		if o in layer :
//			layer.remove(o)
//			del o
//			return
//raise ValueError('Trying destroy non existing object')
template <class T>
GLvoid remove_object(T* o) {
	for (int i = 0; i < 2; i++)  for (int j = 0; j < (int)objects[i].size; j++) {
		if (objects[i][j] == o) {
			delete objects[i][j];
			objects[i].erase(objects[i].begin() + j);
		}
	}
}



//
//def all_objects() :
//    for layer in objects :
//for o in layer :
//yield o
//
//def clearAI() :
//    for o in objects[AIOBJECT] :
//        objects[AIOBJECT].remove(o)
//        del o
//
//        def clearBackground() :
//        for o in objects[BACKOBJECT] :
//            objects[BACKOBJECT].remove(o)
//            del o
//
//
//            def clear() :
//            for o in all_objects() :
//                del o
//                for layer in objects :
//layer.clear()