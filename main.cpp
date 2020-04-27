#include "Gameplay.h"

#define velocity 255.f

int main()
{
	Gameplay gameplay(velocity);
	gameplay.run();
	return 0;
}