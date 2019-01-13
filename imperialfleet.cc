#include <iostream>

#include "imperialfleet.h"

using std::shared_ptr;
template <typename T>
using initList = std::initializer_list<T>;

void ImperiumMember::attack(const std::shared_ptr<RebelStarship> &r) {
	r->takeDamage(getAttackPower());
	r->react(this);
}

size_t Squadron::count() const {
	size_t ans = 0;
	for (const auto &unit : roster)
		ans += unit->count();
	return ans;
}

AttackPower Squadron::totalPower(std::vector<Squadron::unitPtr> list) {
	AttackPower ans = 0;
	for (const auto &it : list)
		if (it->count())
			ans += it->getAttackPower();
	return ans;
}

AttackPower Squadron::getAttackPower() const {
	return totalPower(roster);
}

ShieldPoints Squadron::getShield() const {
	ShieldPoints ans = 0;
	for (const auto &it : roster)
		ans += it->getShield();
	return ans;
}

Squadron::Squadron(std::vector<Squadron::unitPtr> list) :
		ImperiumMember(totalPower(list)),
		roster(std::move(list)) {
	assert(!roster.empty());
}

void Squadron::takeDamage(AttackPower a) {
	for (const auto &e : roster)
		if (e->count())
			e->takeDamage(a);
}

shared_ptr<DeathStar> createDeathStar(ShieldPoints sP, AttackPower a) {
	return shared_ptr<DeathStar>(new DeathStar(sP, a));
}

shared_ptr<ImperialDestroyer> createImperialDestroyer(
		ShieldPoints sP,
		AttackPower a) {
	return shared_ptr<ImperialDestroyer>(new ImperialDestroyer(sP, a));
}

shared_ptr<Squadron> createSquadron(
		std::vector<shared_ptr<ImperiumMember>> list) {
	return shared_ptr<Squadron>(new Squadron(std::move(list)));
}

shared_ptr<TIEFighter> createTIEFighter(ShieldPoints sP, AttackPower a) {
	return shared_ptr<TIEFighter>(new TIEFighter(sP, a));
}
