#include "IOManager.cc"

int main(void) {

	Player user;
	user.name = "TheGreatDylan";
	user.score = 420;
	user.a1 = true;
	user.a2 = false;
	user.a3 = true;
	user.a4 = false;
	user.a5 = true;
	
	IOManager::SetPlayerData(user);

}