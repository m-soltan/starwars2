#include "rebelfleet.h"
#include "imperialfleet.h"

#ifndef STARWARS2_BATTLE_H
#define STARWARS2_BATTLE_H

using galaxyTime_t = int;
constexpr galaxyTime_t defaultMaxTime = INT_MAX;
constexpr galaxyTime_t defaultMinTime = 0;

class Clock {
public:
	virtual void modTime(galaxyTime_t) = 0;
	virtual bool isAttackTime() const = 0;
};

class Clock2_3_5 : public Clock {
	int timeStart, timeLimit;
	int currentTime = 0;
public:
	Clock2_3_5(int timeStart, int timeLimit);
	
	bool isAttackTime() const override;
	void modTime(galaxyTime_t x) override;
};

class SpaceBattle {
	std::shared_ptr<Clock> clock;
	std::vector<std::shared_ptr<ImperiumMember>> imperials;
	std::vector<std::shared_ptr<RebelStarship>> rebels;
	
	SpaceBattle() = default;
	SpaceBattle(SpaceBattle &other) = default;
	void attack();
public:
	class Builder {
		bool hasTimeLimit = false, hasTimeStart = false;
		galaxyTime_t timeLimit = defaultMaxTime, timeStart = defaultMinTime;
		std::shared_ptr<SpaceBattle> battle;
	public:
		Builder();
		Builder maxTime(galaxyTime_t);
		Builder ship(std::shared_ptr<ImperiumMember>);
		Builder ship(std::shared_ptr<RebelStarship>);
		Builder startTime(galaxyTime_t);
		SpaceBattle build();
	};
	size_t countImperialFleet() const;
	size_t countRebelFleet() const;
	void tick(galaxyTime_t);
};

#endif //STARWARS2_BATTLE_H
