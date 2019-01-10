#include "battle.h"

bool Clock2_3_5::isAttackTime() const {
	if (currentTime % 2 || currentTime % 3)
		return false;
	else
		return currentTime % 5 != 0;
}

void Clock2_3_5::modTime(galaxyTime_t x) {
	currentTime += x;
}

Clock2_3_5::Clock2_3_5(int timeStart, int timeLimit) :
		timeStart(timeStart),
		timeLimit(timeLimit) {
}

void SpaceBattle::attack() {}

SpaceBattle::Builder::Builder() {
	battle = std::shared_ptr<SpaceBattle>(new SpaceBattle());
}

SpaceBattle::Builder SpaceBattle::Builder::maxTime(galaxyTime_t x) {
	timeLimit = x + 1;
	hasTimeLimit = true;
	return *this;
}

SpaceBattle::Builder SpaceBattle::Builder::ship(
		std::shared_ptr<ImperiumMember> s) {
	battle->imperials.push_back(s);
	return *this;
}

SpaceBattle::Builder SpaceBattle::Builder::ship(
		std::shared_ptr<RebelStarship> s) {
	battle->rebels.push_back(s);
	return *this;
}

SpaceBattle::Builder SpaceBattle::Builder::startTime(galaxyTime_t x) {
	timeStart = x;
	hasTimeStart = true;
	return *this;
}

SpaceBattle SpaceBattle::Builder::build() {
	assert(hasTimeLimit && hasTimeStart);
	auto *c = new Clock2_3_5(timeStart, timeLimit);
	battle->clock = std::shared_ptr<Clock2_3_5>(c);
	return SpaceBattle(*battle);
}

size_t SpaceBattle::countImperialFleet() const {
	size_t ans = 0;
	for (const auto &e : imperials)
		ans += e->count();
	return ans;
}

size_t SpaceBattle::countRebelFleet() const {
	size_t ans = 0;
	for (const auto &e : rebels)
		if (e->getShield() > 0) ++ans;
	return ans;
}

void SpaceBattle::tick(galaxyTime_t x) {
	if (clock->isAttackTime())
		attack();
	clock->modTime(x);
}
