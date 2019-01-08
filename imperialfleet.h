#include <vector>
#include "rebelfleet.h"

#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

class ImperialStarship : public ArmedUnit, public Starship {
public:
	ImperialStarship(ShieldPoints sP, AttackPower a) :
			ArmedUnit(a),
			Starship(sP) {}
	~ImperialStarship() override = 0;
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

class Squadron : public ArmedUnit, public Participant {
	typedef std::shared_ptr<ImperialStarship> unitPtr;
	std::vector<unitPtr> roster;
	template <typename T>
	static AttackPower totalPower(T list);
public:
	explicit Squadron(std::vector<unitPtr> list);
	Squadron(std::initializer_list<unitPtr> list);
	void takeDamage(AttackPower) override;
};

class TIEFighter : public ImperialStarship {
public:
	TIEFighter(ShieldPoints sP, AttackPower a) :
			ImperialStarship(sP, a) {}
};

std::shared_ptr<DeathStar> createDeathStar(ShieldPoints sP, AttackPower a);
std::shared_ptr<ImperialDestroyer> createImperialDestroyer(
		ShieldPoints sP,
		AttackPower a);
std::shared_ptr<Squadron> createSquadron(
		std::vector<std::shared_ptr<ImperialStarship>>);
std::shared_ptr<Squadron> createSquadron(
		std::initializer_list<std::shared_ptr<ImperialStarship>>);
std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints sP, AttackPower a);

#endif //STARWARS2_IMPERIALFLEET_H
