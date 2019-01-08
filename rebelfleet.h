#include <algorithm>
#include <cassert>

#ifndef STARWARS2_REBELFLEET_H
#define STARWARS2_REBELFLEET_H

using AttackPower = int;
using ShieldPoints = int;
using Speed = int;

constexpr Speed minSpeed = 299'796;

class Participant {
public:
	virtual void takeDamage(AttackPower) = 0;
	virtual ~Participant() = 0;
};

class Starship : public Participant {
protected:
	ShieldPoints shield;
	explicit Starship(ShieldPoints sP) : shield(sP) {}
public:
	ShieldPoints getShield() const;
	void takeDamage(AttackPower) override;
	~Starship() override = 0;
};

class ArmedUnit {
	AttackPower attackPower;
public:
	explicit ArmedUnit(AttackPower attack) : attackPower(attack) {}
	AttackPower getAttackPower();
	virtual ~ArmedUnit() = 0;
};

class RebelStarship : public Starship {
protected:
	bool checkSpeed() { return speed >= minSpeed && speed <= 10 * minSpeed; }
public:
	Speed speed;
//	RebelStarship() : Starship(0), speed(0) {}
	RebelStarship(ShieldPoints sP, Speed s) :
			Starship(sP), speed(s) {}
	~RebelStarship() override = 0;
};

class Explorer : public RebelStarship {
public:
	Explorer(ShieldPoints, Speed);
	~Explorer() override = default;
};
class StarCruiser : public ArmedUnit, public RebelStarship {
public:
	StarCruiser(ShieldPoints, Speed, AttackPower);
};
class XWing : public ArmedUnit, public RebelStarship {
public:
	XWing(ShieldPoints, Speed, AttackPower);
};

std::shared_ptr<Explorer> createExplorer(ShieldPoints sP, Speed s);
std::shared_ptr<StarCruiser> createStarCruiser(
		ShieldPoints sP,
		Speed s,
		AttackPower a);
std::shared_ptr<XWing> createXWing(ShieldPoints sP, Speed s, AttackPower a);

#endif //STARWARS2_REBELFLEET_H
