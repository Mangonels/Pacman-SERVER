#include "IOManager.hh"

int main(void) {

	
	Player user;
	user.name = "TheGreatDylan";
	user.score = 65;
	user.a1 = true;
	user.a2 = false;
	user.a3 = false;
	user.a4 = true;
	user.a5 = false;
	list<Player> ranking;
	ranking.resize(10);

	ranking = IOManager::GetRanking();
	ranking = IOManager::InsertResultInOrder(ranking, user);
	IOManager::SetRanking(ranking);

	return 0;
}