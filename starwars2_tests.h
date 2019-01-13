#include <cassert>
#include "imperialfleet.h"
#include "rebelfleet.h"
#include "battle.h"

void example() {
  auto xwing = createXWing(100, 300000, 50);
  auto explorer = createExplorer(150, 400000);
  auto cruiser = createStarCruiser(1234, 100000, 11);
  auto deathStar = createDeathStar(10000, 75);
  auto fighter = createTIEFighter(50, 9);
  auto destroyer = createImperialDestroyer(150, 20);
  auto squadron = createSquadron({deathStar, fighter});

  auto battle = SpaceBattle::Builder()
      .ship(squadron)
      .startTime(2)
      .maxTime(23)
      .ship(xwing)
      .ship(explorer)
      .build();

  assert(battle.countRebelFleet() == 2);
  assert(battle.countImperialFleet() == 2);

  battle.tick(3);
  assert(battle.countRebelFleet() == 2);
  assert(battle.countImperialFleet() == 1);

  battle.tick(1);
  assert(battle.countRebelFleet() == 2);
  assert(battle.countImperialFleet() == 1);

  battle.tick(4);
  assert(battle.countRebelFleet() == 0);
  assert(battle.countImperialFleet() == 1);

  std::cerr<<"(imperium)"<<std::endl;
  battle.tick(1); // Wypisuje "IMPERIUM WON\n".
}


void clocktest() {
  auto xwing = createXWing(100, 300000, 50);
  auto explorer = createExplorer(150, 400000);
  auto cruiser = createStarCruiser(1234, 100000, 11);
  auto deathStar = createDeathStar(10000, 75);
  auto fighter = createTIEFighter(50, 9);
  auto destroyer = createImperialDestroyer(150, 20);
  auto squadron = createSquadron({deathStar, fighter});
  auto battle = SpaceBattle::Builder()
    .ship(squadron)
    .startTime(1)
    .maxTime(20)
    .ship(xwing)
    .ship(explorer)
    .build();

  battle.tick(4);

  battle.tick(2);

  battle.tick(3);

  battle.tick(1);

  battle.tick(2);

  battle.tick(2);


  battle.tick(6);
  battle.tick(3);

  assert(battle.countRebelFleet() == 2);
  assert(battle.countImperialFleet() == 2);

  battle.tick(2);
  assert(battle.countRebelFleet() == 2);
  assert(battle.countImperialFleet() == 1);

  battle.tick(3);
  assert(battle.countRebelFleet() == 2);
  assert(battle.countImperialFleet() == 1);

  battle.tick(4);
  assert(battle.countRebelFleet() == 0);
  assert(battle.countImperialFleet() == 1);

  std::cerr<<"(imperium)"<<std::endl;
  battle.tick(1); // Wypisuje "IMPERIUM WON\n".
}

void battle_result_draw() {
  auto xwing = createXWing(1, 300000, 1);
  auto deathStar = createDeathStar(1, 1);
  auto battle = SpaceBattle::Builder()
    .ship(xwing)
    .startTime(2)
    .maxTime(20)
    .ship(deathStar)
    .build();

  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 1);
  battle.tick(1);
  assert(battle.countRebelFleet() == 0);
  assert(battle.countImperialFleet() == 0);

  std::cerr<<"(draw)"<<std::endl;
  battle.tick(1);
}

void battle_result_imperium() {
  auto xwing = createXWing(1, 300000, 1);
  auto deathStar = createDeathStar(2, 1);
  auto battle = SpaceBattle::Builder()
    .ship(xwing)
    .startTime(2)
    .maxTime(20)
    .ship(deathStar)
    .build();

  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 1);
  battle.tick(1);

  assert(battle.countRebelFleet() == 0);
  assert(battle.countImperialFleet() == 1);

  std::cerr<<"(imperium)"<<std::endl;
  battle.tick(1);
}

void battle_result_rebellion() {
  auto xwing = createXWing(2, 300000, 1);
  auto deathStar = createDeathStar(1, 1);
  auto battle = SpaceBattle::Builder()
    .ship(xwing)
    .startTime(2)
    .maxTime(20)
    .ship(deathStar)
    .build();

  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 1);
  battle.tick(1);

  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 0);

  std::cerr<<"(rebellion)"<<std::endl;
  battle.tick(1);
}

void damage_from_destroyed_ships() {
  {
  auto xwing = createXWing(2, 300000, 1);
  auto deathStar = createDeathStar(1, 1);
  auto deathStar2 = createDeathStar(2, 0);
  auto battle = SpaceBattle::Builder()
    .ship(xwing)
    .startTime(2)
    .maxTime(20)
    .ship(deathStar)
    .ship(deathStar2)
    .build();

  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 2);
  battle.tick(1);
  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 1);

  std::cerr<<"(rebellion)"<<std::endl;
  battle.tick(1);

  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 0);
  }
  {
  auto xwing = createXWing(1, 300000, 1);
  auto deathStar = createDeathStar(2, 1);
  auto xwing2 = createXWing(2,1, 0);
  auto battle = SpaceBattle::Builder()
    .ship(xwing)
    .startTime(2)
    .maxTime(20)
    .ship(deathStar)
    .ship(xwing2)
    .build();

  assert(battle.countRebelFleet() == 2);
  assert(battle.countImperialFleet() == 1);
  battle.tick(1);
  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 1);

  std::cerr<<"(imperium)"<<std::endl;
  battle.tick(1);

  assert(battle.countRebelFleet() == 0);
  assert(battle.countImperialFleet() == 1);
  }
  {
  auto xwing = createXWing(2, 300000, 1);
  auto deathStar = createDeathStar(1, 1);
  auto deathStar2 = createDeathStar(2, 0);
  auto squadron = createSquadron({deathStar, deathStar2});
  auto battle = SpaceBattle::Builder()
    .ship(xwing)
    .startTime(2)
    .maxTime(20)
    .ship(squadron)
    .build();

  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 2);
  battle.tick(1);
  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 1);

  std::cerr<<"(rebellion)"<<std::endl;
  battle.tick(1);

  assert(battle.countRebelFleet() == 1);
  assert(battle.countImperialFleet() == 0);
  }
}

void unit_counting() {

  auto deathStar = createDeathStar(1, 1);
  auto deathStar2 = createDeathStar(2, 0);

  auto deathStar3 = createDeathStar(1, 1);
  auto deathStar4 = createDeathStar(2, 0);

  auto squadron = createSquadron({deathStar, deathStar2});

  auto squadron2 = createSquadron({squadron, deathStar3, deathStar4});
  auto battle = SpaceBattle::Builder()
    .startTime(0)
    .maxTime(20)
    .ship(squadron2)
    .build();

  assert(battle.countRebelFleet() == 0);
  assert(battle.countImperialFleet() == 4);
}

void attack_order() {
  {
    auto deathStar = createDeathStar(1, 1);
    auto deathStar2 = createDeathStar(2, 0);

    auto xwing = createXWing(2, 300000, 1);

    auto xwing2 = createXWing(1, 300000, 1);

    auto squadron = createSquadron({deathStar, deathStar2});
    auto battle = SpaceBattle::Builder()
      .startTime(2)
      .maxTime(20)
      .ship(deathStar)
      .ship(deathStar2)
      .ship(xwing)
      .ship(xwing2)
      .build();

    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 2);

    battle.tick(1);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 0);

    std::cerr<<"(rebellion)"<<std::endl;
    battle.tick(1);
  }

  {
    auto deathStar = createDeathStar(1, 1);
    auto deathStar2 = createDeathStar(2, 0);

    auto xwing = createXWing(2, 300000, 1);

    auto xwing2 = createXWing(1, 300000, 1);

    auto squadron = createSquadron({deathStar, deathStar2});
    auto battle = SpaceBattle::Builder()
      .startTime(2)
      .maxTime(20)
      .ship(squadron)
      .ship(xwing)
      .ship(xwing2)
      .build();

    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 2);

    battle.tick(1);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 0);

    std::cerr<<"(rebellion)"<<std::endl;
    battle.tick(1);
  }

  {
    auto deathStar = createDeathStar(1, 0);
    auto deathStar2 = createDeathStar(1, 1);

    auto xwing = createXWing(1, 300000, 1);

    auto battle = SpaceBattle::Builder()
      .startTime(2)
      .maxTime(20)
      .ship(deathStar)
      .ship(deathStar2)
      .ship(xwing)
      .build();

    assert(battle.countRebelFleet() == 1);
    assert(battle.countImperialFleet() == 2);

    battle.tick(1);

    assert(battle.countRebelFleet() == 0);
    assert(battle.countImperialFleet() == 0);

    std::cerr<<"(draw)"<<std::endl;
    battle.tick(1);
  }

}

void squadron_test() {

  auto deathStar = createDeathStar(1, 1);
  auto deathStar2 = createDeathStar(2, 0);
  auto squadron = createSquadron({deathStar, deathStar2});


  assert(squadron->count() == 2);
  assert(squadron->getAttackPower() == 1);
  assert(squadron->getShield() == 3);

  squadron->takeDamage(1);

  assert(squadron->count() == 1);
  assert(squadron->getAttackPower() == 0);
  assert(squadron->getShield() == 1);

}
