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
//	assert(a >= 0);
	shield = std::max(0, shield - a);
}


//Participant::~Participant() = default;

//Starship::~Starship() = default;

AttackPower ArmedUnit::getAttackPower() { return attackPower; }

ArmedUnit::~ArmedUnit() = default;

bool RebelStarship::checkSpeed(Speed min, Speed max) const {
	return speed >= min && speed < max;
}

//RebelStarship::~RebelStarship() = default;

Explorer::Explorer(ShieldPoints sP, Speed s) :
		RebelStarship(sP, s) {
	assert(checkSpeed(rebelMid, rebelCap));
	dS = std::shared_ptr<DefenseStrategy>(new DoesNotRetaliate());
}

StarCruiser::StarCruiser(ShieldPoints sP, Speed s, AttackPower a) :
		RebelStarship(sP, s), ArmedUnit(a) {
	assert(checkSpeed(rebelLow, rebelMid));
	auto ptr = std::shared_ptr<ArmedUnit>(new StarCruiser(*this));
	dS = std::shared_ptr<DefenseStrategy>(new Retaliates(ptr));
}

XWing::XWing(ShieldPoints sP, Speed s, AttackPower a) :
		RebelStarship(sP, s), ArmedUnit(a) {
	assert(checkSpeed(rebelMid, rebelCap));
	auto ptr = std::shared_ptr<ArmedUnit>(new XWing(*this));
	dS = std::shared_ptr<DefenseStrategy>(new Retaliates(ptr));
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
