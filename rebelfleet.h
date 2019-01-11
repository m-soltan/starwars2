#include <algorithm>
#include <cassert>

#ifndef STARWARS2_REBELFLEET_H
#define STARWARS2_REBELFLEET_H

using AttackPower = int;
using ShieldPoints = int;
using Speed = int;

class Participant {
public:
	virtual size_t count() const = 0;
	virtual void takeDamage(AttackPower) = 0;
//	virtual ~Participant() = 0;
};

class Starship : public virtual Participant {
	ShieldPoints shield;
protected:
	explicit Starship(ShieldPoints sP) : shield(sP) {}
public:
	ShieldPoints getShield() const;
	size_t count() const override;
	void takeDamage(AttackPower) override;
//	~Starship() override = 0;
};

class ArmedUnit {
	AttackPower attackPower;
protected:
	explicit ArmedUnit(AttackPower attack) : attackPower(attack) {}
public:
	AttackPower getAttackPower() const;
//	virtual ~ArmedUnit() = 0;
};

class DefenseStrategy {
public:
	virtual AttackPower getRetaliation() const = 0;
};

class Retaliates : public DefenseStrategy {
	std::shared_ptr<ArmedUnit> aU;
public:
	explicit Retaliates(std::shared_ptr<ArmedUnit> ship) :
			aU(std::move(ship)) {
	}
	AttackPower getRetaliation() const override {
		return aU->getAttackPower();
	}
};

class DoesNotRetaliate : public DefenseStrategy {
public:
	AttackPower getRetaliation() const override { return 0; }
};

class RebelStarship : public Starship {
	Speed speed;
	std::shared_ptr<DefenseStrategy> dS;
protected:
	bool checkSpeed(Speed min, Speed max) const;
	virtual void react(std::shared_ptr<Participant>) const = 0;
public:
	RebelStarship(ShieldPoints sP, Speed s) :
			Starship(sP), speed(s) {
	}
//	~RebelStarship() override = 0;
};

class NonRetaliating : public RebelStarship {
protected:
	void react(std::shared_ptr<Participant>) const override;
};

class Retaliating : public RebelStarship, public ArmedUnit {
protected:
	void react(std::shared_ptr<Participant>) const override;
};

class Explorer : public NonRetaliating {
public:
	Explorer(ShieldPoints, Speed);
//	~Explorer() override = default;
};
class StarCruiser : public Retaliating {
public:
	StarCruiser(ShieldPoints, Speed, AttackPower);
};
class XWing : public Retaliating {
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
