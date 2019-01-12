#include "rebelfleet.h"

constexpr Speed rebelLow = 99'999;
constexpr Speed rebelMid = 299'796;
constexpr Speed rebelCap = 10 * rebelMid + 1;

ShieldPoints Starship::getShield() const { return shield; }

size_t Starship::count() const {
	if (getShield()) return 1;
	else return 0;
}

void Starship::takeDamage(AttackPower a) {
	assert(a >= 0);
	shield = std::max(0, shield - a);
}

AttackPower ArmedUnit::getAttackPower() const { return attackPower; }

bool RebelStarship::checkSpeed(Speed min, Speed max) const {
	return speed >= min && speed < max;
}

void NotReacting::react(Participant *) const {}

void Retaliating::react(Participant *attacker) const {
	attacker->takeDamage(getAttackPower());
}

Explorer::Explorer(ShieldPoints sP, Speed s) :
		NotReacting(sP, s) {
	assert(checkSpeed(rebelMid, rebelCap));
}

StarCruiser::StarCruiser(ShieldPoints sP, Speed s, AttackPower a) :
		Retaliating(sP, s, a) {
	assert(checkSpeed(rebelLow, rebelMid));
	auto ptr = std::shared_ptr<ArmedUnit>(new StarCruiser(*this));
}

XWing::XWing(ShieldPoints sP, Speed s, AttackPower a) :
		Retaliating(sP, s, a) {
	assert(checkSpeed(rebelMid, rebelCap));
	auto ptr = std::shared_ptr<ArmedUnit>(new XWing(*this));
}

std::shared_ptr<Explorer> createExplorer(ShieldPoints sP, Speed s) {
	return std::shared_ptr<Explorer>(new Explorer(sP, s));
}

std::shared_ptr<StarCruiser> createStarCruiser(
		ShieldPoints sP,
		Speed s,
		AttackPower a) {
	return std::shared_ptr<StarCruiser>(new StarCruiser(sP, s, a));
}

std::shared_ptr<XWing> createXWing(ShieldPoints sP, Speed s, AttackPower a) {
	return std::shared_ptr<XWing>(new XWing(sP, s, a));
}
