#include "rebelfleet.h"

ShieldPoints Starship::getShield() const { return shield; }

void Starship::takeDamage(AttackPower a) {
	assert(a >= 0);
	shield = std::max(0, shield - a);
}

Participant::~Participant() = default;

Starship::~Starship() = default;

AttackPower ArmedUnit::getAttackPower() { return attackPower; }

ArmedUnit::~ArmedUnit() = default;

RebelStarship::~RebelStarship() = default;

Explorer::Explorer(ShieldPoints sP, Speed s) : RebelStarship(sP, s) {
	assert(checkSpeed());
}

StarCruiser::StarCruiser(ShieldPoints sP, Speed s, AttackPower a) :
		RebelStarship(sP, s), ArmedUnit(a) {
	assert(speed >= 99'999 && speed < minSpeed);
}

XWing::XWing(ShieldPoints sP, Speed s, AttackPower a) :
		RebelStarship(sP, s), ArmedUnit(a) {
	assert(checkSpeed());
}

std::shared_ptr<Explorer> createExplorer(ShieldPoints sP, Speed s) {
	return std::shared_ptr<Explorer>(new Explorer(sP, s));
}

std::shared_ptr<StarCruiser> createStarCruiser(ShieldPoints sP, Speed s, AttackPower a) {
	return std::shared_ptr<StarCruiser>(new StarCruiser(sP, s, a));
}

std::shared_ptr<XWing> createXWing(ShieldPoints sP, Speed s, AttackPower a) {
	return std::shared_ptr<XWing>(new XWing(sP, s, a));
}
