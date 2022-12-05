#include "key_events.h"

GLboolean key_down[KEYEND];

GLboolean* GetKeyDown() {
	return key_down;
}