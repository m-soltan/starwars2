#include <iostream>

#include "imperialfleet.h"

using std::shared_ptr;
template <typename T>
using initList = std::initializer_list<T>;

//ImperialStarship::~ImperialStarship() = default;

void ImperiumMember::attack(const std::shared_ptr<RebelStarship> &r) {
	r->takeDamage(getAttackPower());
	takeDamage(r->dS->retaliate());
}

size_t Squadron::count() const {
	size_t ans = 0;
	for (const auto &e : roster)
		ans += e->count();
	return ans;
}

template <typename T>
AttackPower Squadron::totalPower(T list) {
	AttackPower ans = 0;
	for (const auto &it : list)
		if (it->count())
			ans += it->getAttackPower();
	return ans;
}

template <typename T>
std::vector<Squadron::unitPtr> Squadron::upCastPointers(T list) {
	std::vector<Squadron::unitPtr> ans;
	ans.reserve(list.size());
	for (const auto &e : list)
		ans.emplace_back(Squadron::unitPtr(e));
	return ans;
}

Squadron::Squadron(std::vector<Squadron::unitPtr> list) :
		ImperiumMember(totalPower<std::vector<Squadron::unitPtr>>(list)),
		roster(std::move(list)) {}

Squadron::Squadron(initList<Squadron::unitPtr> list) :
		ImperiumMember(totalPower<initList<Squadron::unitPtr>>(list)),
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
	Squadron *s = new Squadron(Squadron::upCastPointers(std::move(list)));
	return shared_ptr<Squadron>(s);
}

shared_ptr<Squadron> createSquadron(
		std::vector<shared_ptr<ImperiumMember>> list) {
	return shared_ptr<Squadron>(new Squadron(std::move(list)));
}

shared_ptr<Squadron> createSquadron(
		std::initializer_list<shared_ptr<ImperialStarship>> list) {
	return shared_ptr<Squadron>(new Squadron(Squadron::upCastPointers(list)));
}

shared_ptr<Squadron> createSquadron(
		std::initializer_list<shared_ptr<ImperiumMember>> list) {
	return shared_ptr<Squadron>(new Squadron(list));
}
