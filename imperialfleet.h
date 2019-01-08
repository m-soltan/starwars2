#include "rebelfleet.h"

#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

class ImperialStarship : public Starship, public ArmedUnit {
protected:
	ImperialStarship(ShieldPoints sP, AttackPower a) :
			ArmedUnit(a),
			Starship(sP) {}
};

class DeathStar : public ImperialStarship {
public:
	DeathStar(ShieldPoints sP, AttackPower a) : ImperialStarship(sP, a) {}
};

class ImperialDestroyer : public ImperialStarship {
public:
	ImperialDestroyer(ShieldPoints sP, AttackPower a) :
			ImperialStarship(sP, a) {}
};

// TODO
class Squadron : public ImperialStarship {};

class TIEFighter : public ImperialStarship {
public:
	TIEFighter(ShieldPoints sP, AttackPower a) :
			ImperialStarship(sP, a) {}
};

std::shared_ptr<DeathStar> createDeathStar(ShieldPoints sP, AttackPower a);
std::shared_ptr<ImperialDestroyer> createImperialDestroyer(
		ShieldPoints sP,
		AttackPower a);
std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints sP, AttackPower a);

#endif //STARWARS2_IMPERIALFLEET_H
