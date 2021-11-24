#include <iostream>
#include <string>

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
public:
	string name;
	int mineral;
	int gas;
	int hp;      //������ ü��
	int damage, armour;   //������ ���ݷ�, ����
	int slotSize;
	bool alive = true;
	bool attackable;

	string rush;
	string init;

	void fight(Unit& unit) {
		if (this->attackable == false) {
			cout << this->name << " can not attack" << endl;
		}
		else {
			unit.getAttacked(*this);

			//���� �޾Ҵ� ������ ������ ���, ������ ���ֿ��� �ݰ���.
			if (unit.alive && unit.attackable) {
				this->getAttacked(unit);
			}
		}
	}

	//getAttacked() �Լ��� ȣ���� ������ ���ݹ���.
	void getAttacked(Unit& unit) {
		cout << unit.rush << endl;
		int real_damage = unit.damage - this->armour;
		//���ݷº��� ������ ���� ��� ������ = 0
		if (real_damage <= 0) real_damage = 0;
		this->hp -= real_damage;

		//������ �޾� ü���� 0�� �Ǹ� ������ �� �� ������ ��.
		if (this->hp > 0) {
			cout << this->name << "'s hp: " << this->hp << endl;
		}
		else {
			this->alive = false;
			cout << this->name << " die" << endl;
			cout << this->name << " not alive" << endl;
		}
	}
};

template <typename T>
class Building {
private:
	T t;
public:
	Building() {
		cout << t.info << " building construction completed." << endl;
	}
	void buy(Unit& unit, int& mineral, int& gas) {
		if (mineral >= unit.mineral) {
			mineral -= unit.mineral;
			if (gas >= unit.gas) {
				gas -= unit.gas;
				cout << unit.init << endl;
			}
			else
				cout << t.minLack << endl;
		}
		else
			cout << t.gasLack << endl;
	}
};

class smallUnit : public Unit { public: smallUnit() { slotSize = 1; } };
class mediumUnit : public Unit { public: mediumUnit() { slotSize = 2; } };
class largeUnit : public Unit { public: largeUnit() { slotSize = 4; } };

class Marine : public smallUnit, public Terran {
public:
	Marine() {
		name = "marine";
		mineral = 50;
		gas = 0;
		hp = 40;
		damage = 6;
		armour = 0;
		attackable = true;
		rush = "Go! Go! Go!";
		init = "You wanna piece of me, boy?";
	}
};

class Tank : public largeUnit, public Terran {
public:
	Tank() {
		name = "tank";
		mineral = 150;
		gas = 50;
		hp = 150;
		damage = 30;
		armour = 1;
		attackable = true;
		rush = "Move it!";
		init = "Ready to roll out!";
	}
};

class Zealot : public mediumUnit, public Protoss {
public:
	Zealot() {
		name = "zealot";
		mineral = 100;
		gas = 0;
		hp = 160;
		damage = 16;
		armour = 1;
		attackable = true;
		rush = "For Adun!";
		init = "My life for Aiur";
	}
};

class Dragoon : public largeUnit, public Protoss {
public:
	Dragoon() {
		name = "dragoon";
		mineral = 125;
		gas = 50;
		hp = 180;
		damage = 20;
		armour = 1;
		attackable = true;
		rush = "Confirmed.";
		init = "I have returned!";
	}
};

class Dropship : public largeUnit, public Terran {
private:
	int slot = 8;
	int unitCount = 0;
	Unit** unitArr = new Unit*[8];

	/*
	1. Unit unitArr[8] : Unit ��ü�� ���� �� �ִ� 8ĭ Array ����. �׷��� Call by value�� �ܺ� ��ü ���� �Ұ�. ���� �Ҵ� �Ұ�.
	2. Unit* unitArr[8] : Unit ��ü�� ���� �� �ִ� 8ĭ *Array ����. �ܺ� ��ü ���� ����. �׷��� ���� �Ҵ� �Ұ�.
	3. Unit* unitArr = new Unit[8] : Unit ��ü�� ���� �� �ִ� 8ĭ ���� Array ����. �׷��� Call by value�� �ܺ� ��ü ���� �Ұ�.
	4. Unit** unitArr = new Unit*[8] : *Unit ��ü�� ���� �� �ִ� 8ĭ ���� **Array ����.
	*/

public:
	Dropship() {
		name = "dropship";
		mineral = 100;
		gas = 100;
		hp = 150;
		armour = 1;
		attackable = false;
		init = "Can I take your order?";
	}

	~Dropship() {}

	void load(Unit& unit) {
		if (this->slot - unit.slotSize < 0) {
			cout << "not enough empty slot" << endl << endl;
		}
		else {
			unitArr[unitCount] = &unit;
			unitArr[unitCount]->attackable = false;
			cout << "dropship load " << unitArr[unitCount]->name << endl;

			printStatus();
			this->slot -= unit.slotSize;
			this->unitCount++;
		}
	};

	void drop() {
		int i = 0;
		while (i < this->unitCount) {
			cout << unitArr[i]->name << " drop" << endl;
			unitArr[i]->attackable = true;
			i++;
		}
		delete[] unitArr;
	};

	void printStatus() {
		int i = 0;
		cout << "empty: " << slot << endl;
		cout << "---------dropship---------" << endl;
		while (i <= this->unitCount) {
			cout << unitArr[i]->name << " ";
			i++;
		}
		cout << endl << "---------dropship---------" << endl;
	}
};

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

	protoss_building.buy(zealot, mineral, gas);
	terran_building.buy(marine, mineral, gas);

	marine.attackable = false;
	zealot.fight(marine);

	return 0;
}