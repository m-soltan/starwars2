#include <vector>
#include "rebelfleet.h"

#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

class ImperiumMember : public virtual Participant, public ArmedUnit {
public:
	explicit ImperiumMember(AttackPower a) : ArmedUnit(a) {}
	void attack(const std::shared_ptr<RebelStarship> &r);
	~ImperiumMember() override = default;
};

// as required by the project description
// doesn't do much besides passing the inheritance from Starship
class ImperialStarship :
		public ImperiumMember,
		public Starship {
public:
	ImperialStarship(ShieldPoints sP, AttackPower a) :
			ImperiumMember(a),
			Starship(sP) {
	}
	~ImperialStarship() override = default;
};

class DeathStar : public ImperialStarship {
public:
	DeathStar(ShieldPoints sP, AttackPower a) : ImperialStarship(sP, a) {}
};

class ImperialDestroyer : public ImperialStarship {
public:
	ImperialDestroyer(ShieldPoints sP, AttackPower a) :
			ImperialStarship(sP, a) {
	}
};

class Squadron : public ImperiumMember {
	typedef std::shared_ptr<ImperiumMember> unitPtr;
	std::vector<unitPtr> roster;
	template <typename T>
	static AttackPower totalPower(T list);
public:
	AttackPower getAttackPower() const override;
	ShieldPoints getShield() const override;
	size_t count() const override;
	explicit Squadron(std::vector<unitPtr> list);
	void takeDamage(AttackPower) override;
};

class TIEFighter : public ImperialStarship {
public:
	TIEFighter(ShieldPoints sP, AttackPower a) :
			ImperialStarship(sP, a) {
	}
};

std::shared_ptr<DeathStar> createDeathStar(ShieldPoints sP, AttackPower a);
std::shared_ptr<ImperialDestroyer> createImperialDestroyer(
		ShieldPoints sP,
		AttackPower a);
std::shared_ptr<Squadron> createSquadron(
		std::vector<std::shared_ptr<ImperiumMember>>);
std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints sP, AttackPower a);

#endif //STARWARS2_IMPERIALFLEET_H
