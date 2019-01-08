#include "imperialfleet.h"

using std::shared_ptr;

shared_ptr<DeathStar> createDeathStar(ShieldPoints sP, AttackPower a) {
	return shared_ptr<DeathStar>(new DeathStar(sP, a));
}

shared_ptr<ImperialDestroyer> createImperialDestroyer(
		ShieldPoints sP,
		AttackPower a) {
	return shared_ptr<ImperialDestroyer>(new ImperialDestroyer(sP, a));
}

shared_ptr<TIEFighter> createTIEFighter(ShieldPoints sP, AttackPower a) {
	return shared_ptr<TIEFighter>(new TIEFighter(sP, a));
}