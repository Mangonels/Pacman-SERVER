#include "IOManager.cc"

int main(void) {

	Player user;
	user.name = "TheGreatDylan";
	user.score = 60;
	user.a1 = true;
	user.a2 = false;
	user.a3 = false;
	user.a4 = true;
	user.a5 = false;
	list<Player> aa;
	aa.resize(10);
	IOManager::SetRanking(aa);
	system("pause");
}