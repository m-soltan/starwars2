#include "rebelfleet.h"

ShieldPoints Starship::getShield() const { return shield; }

void Starship::takeDamage(AttackPower a) {
	assert(a >= 0);
	shield = std::max(0, shield - a);
}

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