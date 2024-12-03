#include <memory>
#include "src/Game.h"

int main()
{
	auto game = std::make_unique<Game>(640, 480);
	return game->Exec();
}
