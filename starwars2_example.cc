
#include "starwars2_tests.h"
#include <cassert>
#include "imperialfleet.h"
#include "rebelfleet.h"
#include "battle.h"

int main() {
    example();
    clocktest();
    battle_result_draw();
    battle_result_imperium();
    battle_result_rebellion();
    unit_counting();
    squadron_test();
    attack_order();
}
