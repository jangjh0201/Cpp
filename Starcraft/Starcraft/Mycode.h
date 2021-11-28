#include <iostream>
#include <string>

#ifndef Mycode
#define Mycode

using namespace std;

class Terran {
public:
	string info = "Terran";
	string minLack = "Not enough minerals.";
	string gasLack = "Insufficient Vespene gas.";
};

class Protoss {
public:
	string info = "Protoss";
	string minLack = "You've not enough minerals.";
	string gasLack = "You require more Vespene gas.";
};

class Unit {
protected:
	string name, init, rush;
	int mineral, gas, hp, damage, armour, slotSize;
	bool attackable, alive = true;

private:
	void getAttacked(Unit& unit);

public:
	void Fight(Unit& unit);

	string GetName() { return this->name; }
	string GetInit() { return this->init; }
	string GetRush() { return this->rush; }
	int GetMIneral() { return this->mineral; }
	int GetGas() { return this->gas; }
	int GetHp() { return this->hp; }
	int GetDamage() { return this->damage; }
	int GetArmour() { return this->armour; }
	int GetSlotSize() { return this->slotSize; }
	bool GetAttackable() { return this->attackable; }
	bool GetAlive() { return this->alive; }

	void SetName(const string name) { this->name = name; }
	void SetInit(const string init) { this->init = init; }
	void SetRush(const string rush) { this->rush = rush; }
	void SetMIneral(int mineral) { this->mineral = mineral; }
	void SetGas(int gas) { this->gas = gas; }
	void SetHp(int hp) { this->hp = hp; }
	void SetDamage(int damage) { this->damage = damage; }
	void SetArmour(int armour) { this->armour = armour; }
	void SetSlotSize(int slotSize) { this->slotSize = slotSize; }
	void SetAttackable(bool attackable) { this->attackable = attackable; }
	void SetAlive(bool alive) { this->alive = alive; }
};

class smallUnit : public Unit { public: smallUnit() { slotSize = 1; } };
class mediumUnit : public Unit { public: mediumUnit() { slotSize = 2; } };
class largeUnit : public Unit { public: largeUnit() { slotSize = 4; } };

class Marine : public smallUnit, private Terran {
public:
	Marine() {
		name = "marine";
		init = "You wanna piece of me, boy?";
		rush = "Go! Go! Go!";

		mineral = 50;
		gas = 0;
		hp = 40;
		damage = 6;
		armour = 0;
		attackable = true;
	}
};

class Tank : public largeUnit, private Terran {
public:
	Tank() {
		name = "tank";
		init = "Ready to roll out!";
		rush = "Move it!";

		mineral = 150;
		gas = 50;
		hp = 150;
		damage = 30;
		armour = 1;
		attackable = true;
	}
};

class Zealot : public mediumUnit, private Protoss {
public:
	Zealot() {
		name = "zealot";
		init = "My life for Aiur";
		rush = "For Adun!";

		mineral = 100;
		gas = 0;
		hp = 160;
		damage = 16;
		armour = 1;
		attackable = true;
	}
};

class Dragoon : public largeUnit, private Protoss {
public:
	Dragoon() {
		name = "dragoon";
		init = "I have returned!";
		rush = "Confirmed.";

		mineral = 125;
		gas = 50;
		hp = 180;
		damage = 20;
		armour = 1;
		attackable = true;
	}
};

class Dropship : public largeUnit, private Terran {
private:
	int slot = 8;
	int unitCount = 0;
	Unit** unitArr = new Unit*[8];

	/*
	1. Unit unitArr[8] : Unit 객체를 받을 수 있는 8칸 Array 선언. 그러나 Call by value라 외부 객체 참조 불가. 동적 할당 불가.
	2. Unit* unitArr[8] : Unit 객체를 받을 수 있는 8칸 *Array 선언. 외부 객체 참조 가능. 그러나 동적 할당 불가.
	3. Unit* unitArr = new Unit[8] : Unit 객체를 받을 수 있는 8칸 동적 Array 선언. 그러나 Call by value라 외부 객체 참조 불가.
	4. Unit** unitArr = new Unit*[8] : *Unit 객체를 받을 수 있는 8칸 동적 **Array 선언.
	*/

public:
	Dropship() {
		name = "dropship";
		init = "Can I take your order?";

		mineral = 100;
		gas = 100;
		hp = 150;
		armour = 1;
		attackable = false;
	}

	void Load(Unit& unit);
	void Drop();

private:
	void printStatus();
};

template <class T>
class Building {
private:
	T t;
public:
	void Buy(Unit& unit, int& mineral, int& gas) {
		if (mineral >= unit.GetMIneral()) {
			mineral -= unit.GetMIneral();
			if (gas >= unit.GetGas()) {
				gas -= unit.GetGas();
				cout << unit.GetInit() << endl;
			}
			else
				cout << t.minLack << endl;
		}
		else
			cout << t.gasLack << endl;
	}
};

#endif // !Mycode