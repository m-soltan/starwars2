#include <utility>

#include <utility>

#include "imperialfleet.h"

using std::shared_ptr;

ImperialStarship::~ImperialStarship() = default;

template <typename T>
AttackPower Squadron::totalPower(T list) {
	AttackPower ans = 0;
	auto it = list.begin();
	while (it != list.end()) {
		ans += it[0]->getAttackPower();
	}
	return ans;
}

Squadron::Squadron(std::vector<Squadron::unitPtr> list) :
		ArmedUnit(totalPower<std::vector<Squadron::unitPtr>>(list)),
		roster(std::move(list)) {}

Squadron::Squadron(std::initializer_list<Squadron::unitPtr> list) :
		ArmedUnit(totalPower<std::initializer_list<Squadron::unitPtr>>(list)),
		roster(list) {}

void Squadron::takeDamage(AttackPower a) {
	for (const auto &e : roster)  e->takeDamage(a);
}

shared_ptr<DeathStar> createDeathStar(ShieldPoints sP, AttackPower a) {
	return shared_ptr<DeathStar>(new DeathStar(sP, a));
}

shared_ptr<ImperialDestroyer> createImperialDestroyer(
		ShieldPoints sP,
		AttackPower a) {
	return shared_ptr<ImperialDestroyer>(new ImperialDestroyer(sP, a));
}

shared_ptr<TIEFighter> createTIEFighter(ShieldPoints sP, AttackPower a) {
	return shared_ptr<TIEFighter>(new TIEFighter(sP, a));
}

shared_ptr<Squadron> createSquadron(
		std::vector<shared_ptr<ImperialStarship>> list) {
	return shared_ptr<Squadron>(new Squadron(std::move(list)));
}

shared_ptr<Squadron> createSquadron(
		std::initializer_list<shared_ptr<ImperialStarship>> list) {
	return shared_ptr<Squadron>(new Squadron(list));
}