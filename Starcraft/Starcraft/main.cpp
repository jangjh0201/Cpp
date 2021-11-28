#include <iostream>
#include "Mycode.h"

using namespace std;

int main() {
	Marine marine;
	Tank tank;
	Zealot zealot;
	Dragoon dragoon;
	Dropship dropship;

	Building <Protoss> protoss_building;
	Building <Terran> terran_building;

	int mineral = 1000;
	int gas = 1000;

	terran_building.Buy(marine, mineral, gas);
	terran_building.Buy(tank, mineral, gas);
	protoss_building.Buy(zealot, mineral, gas);
	protoss_building.Buy(dragoon, mineral, gas);
	protoss_building.Buy(dropship, mineral, gas);
	cout << "------------------------------" << endl;

	dropship.Load(zealot);
	dropship.Load(marine);
	dropship.Load(tank);
	dropship.Load(dragoon);

	zealot.Fight(dragoon);
	marine.Fight(dragoon);
	tank.Fight(dragoon);

	dropship.Drop();

	zealot.Fight(dragoon);
	marine.Fight(dragoon);
	tank.Fight(dragoon);
	dropship.Fight(dragoon);

	return 0;
}