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
	std::cout << user.name << " " << user.score << " " << user.a2 << "\n";
	user = IOManager::GetPlayerData(user);
	std::cout << user.name << " " << user.score << " " << user.a2 << "\n";
	system("pause");
}