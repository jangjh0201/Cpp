#include <iostream>
#include <string>

using namespace std;

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

class smallUnit : virtual public Unit { public: smallUnit() { slotSize = 1; } };
class mediumUnit : virtual public Unit { public: mediumUnit() { slotSize = 2; } };
class largeUnit : virtual public Unit { public: largeUnit() { slotSize = 4; } };

class Terran : virtual public Unit {
public:
	string init;

	void buy(int& mineral, int& gas) {
		if (mineral >= this->mineral) {
			mineral -= this->mineral;
			if (gas >= this->gas) {
				gas -= this->gas;
				cout << init << endl;
			}
			else
				cout << "Insufficient Vespene gas." << endl;
		}
		else
			cout << "Not enough minerals." << endl;
	}
};

class Protoss : virtual public Unit {
public:
	string init;

	void buy(int& mineral, int& gas) {
		if (mineral >= this->mineral) {
			mineral -= this->mineral;
			if (gas >= this->gas) {
				gas -= this->gas;
				cout << init << endl;
			}
			else
				cout << "You require more Vespene gas." << endl;
		}
		else
			cout << "You've not enough minerals." << endl;
	}
};

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

	int mineral = 10;
	int gas = 10;

	marine.buy(mineral, gas);
	tank.buy(mineral, gas);
	zealot.buy(mineral, gas);
	dragoon.buy(mineral, gas);
	dropship.buy(mineral, gas);

	return 0;
}