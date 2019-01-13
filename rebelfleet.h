#include <algorithm>
#include <climits>
#include <memory>
#include <cassert>

#ifndef STARWARS2_REBELFLEET_H
#define STARWARS2_REBELFLEET_H

using AttackPower = int;
using ShieldPoints = int;
using Speed = int;

class Participant {
public:
	virtual size_t count() const = 0;
	virtual ShieldPoints getShield() const = 0;
	virtual void takeDamage(AttackPower) = 0;
	virtual ~Participant() = default;
};

class Starship : public virtual Participant {
	ShieldPoints shield;
protected:
	explicit Starship(ShieldPoints sP) : shield(sP) {}
public:
	size_t count() const override;
	ShieldPoints getShield() const override;
	void takeDamage(AttackPower) override;
	~Starship() override = default;
};

class ArmedUnit {
	AttackPower attackPower;
protected:
	explicit ArmedUnit(AttackPower attack) : attackPower(attack) {}
public:
	virtual AttackPower getAttackPower() const;
	virtual ~ArmedUnit() = default;
};

class RebelStarship : public Starship {
	Speed speed;
protected:
	bool checkSpeed(Speed min, Speed max) const;
public:
	virtual void react(Participant *) const = 0;
	RebelStarship(ShieldPoints sP, Speed s) :
			Starship(sP), speed(s) {
	}
	~RebelStarship() override = default;
};

class NotReacting : public RebelStarship {
protected:
	NotReacting(ShieldPoints shield, Speed s) :
			RebelStarship(shield, s) {
	}
public:
	void react(Participant *) const override;
	~NotReacting() override = default;
};

class Retaliating : public RebelStarship, public ArmedUnit {
protected:
	Retaliating(ShieldPoints shield, Speed s, AttackPower a) :
			RebelStarship(shield, s),
			ArmedUnit(a) {
	}
public:
	void react(Participant *) const override;
	~Retaliating() override = default;
};

class Explorer : public NotReacting {
public:
	Explorer(ShieldPoints, Speed);
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
