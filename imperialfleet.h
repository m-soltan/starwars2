#include <vector>
#include "rebelfleet.h"

#ifndef STARWARS2_IMPERIALFLEET_H
#define STARWARS2_IMPERIALFLEET_H

class ImperiumMember : public virtual Participant, public ArmedUnit {
//	void beHit(ArmedUnit a);
//	void beHit(RebelStarship r);
public:
	explicit ImperiumMember(AttackPower a) : ArmedUnit(a) {}
	void attack(const std::shared_ptr<RebelStarship> &r);
	~ImperiumMember() override = 0;
};

class ImperialStarship :
		public ImperiumMember,
		public Starship {
public:
	ImperialStarship(ShieldPoints sP, AttackPower a) :
			ImperiumMember(a),
			Starship(sP) {
	}
	~ImperialStarship() override = 0;
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
	template <typename T>
	static std::vector<unitPtr> upCastPointers(T list);
	size_t count() const override;
	explicit Squadron(std::vector<unitPtr> list);
	Squadron(std::initializer_list<unitPtr> list);
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
		std::vector<std::shared_ptr<ImperialStarship>>);
std::shared_ptr<Squadron> createSquadron(
		std::initializer_list<std::shared_ptr<ImperialStarship>>);
std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints sP, AttackPower a);

#endif //STARWARS2_IMPERIALFLEET_H
