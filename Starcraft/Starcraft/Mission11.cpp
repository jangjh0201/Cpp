#include <iostream>
#include <string>

using namespace std;

class Unit {
public:
	string name;
	int mineral;
	int gas;
	int hp;      //유닛의 체력
	int damage, armour;   //유닛의 공격력, 방어력
	int slotSize;
	bool alive = true;
	bool attackable;

	string str;
	
	void fight(Unit& unit) {
		if (this->attackable == false) { 
			cout << this->name << " can not attack" << endl;
		}
		else {
			unit.getAttacked(*this);

			//공격 받았던 유닛이 생존한 경우, 공격한 유닛에게 반격함.
			if (unit.alive && unit.attackable) {
				this->getAttacked(unit);
			}
		}
	}

	//getAttacked() 함수를 호출한 유닛이 공격받음.
	void getAttacked(Unit& unit) {
		cout << unit.str << endl;
		int real_damage = unit.damage - this->armour;
		//공격력보다 방어력이 높은 경우 데미지 = 0
		if (real_damage <= 0) real_damage = 0;
		this->hp -= real_damage;

		//공격을 받아 체력이 0이 되면 공격을 할 수 없도록 함.
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

class smallUnit : public Unit { public: smallUnit() { slotSize = 1; } };
class mediumUnit : public Unit { public: mediumUnit() { slotSize = 2; } };
class largeUnit : public Unit { public: largeUnit() { slotSize = 4; } };

class Marine : public smallUnit {
public:
	Marine() {
		name = "marine";
		mineral = 50;
		gas = 0;
		hp = 40;
		damage = 6;
		armour = 0;
		attackable = true;
		str = "Go! Go! Go!";
	}

	void buy(int& mineral, int& gas) {
		int flag = 0; // 유닛을 생성 가능한지 판별. flag 값이 2일 때만 생성 가능.
		if (mineral >= this->mineral) {
			mineral -= this->mineral;
			flag++;
		}
		else
			cout << "Not enough minerals." << endl;

		if (gas >= this->gas) {
			gas -= this->gas;
			flag++;
		}
		else
			cout << "Insufficient Vespene gas." << endl;

		if (flag == 2)
			cout << "You wanna piece of me, boy?" << endl;
	};
};

class Tank : public largeUnit {
public:
	Tank() {
		name = "tank";
		mineral = 150;
		gas = 50;
		hp = 150;
		damage = 30;
		armour = 1;
		attackable = true;
		str = "Move it!";
	}

	void buy(int& mineral, int& gas) {
		int flag = 0;

		if (mineral >= this->mineral) {
			mineral -= this->mineral;
			flag++;
		}
		else
			cout << "Not enough minerals." << endl;

		if (gas >= this->gas) {
			gas -= this->gas;
			flag++;
		}
		else
			cout << "Insufficient Vespene gas." << endl;

		if (flag == 2)
			cout << "Ready to roll out!" << endl;
	};
};

class Zealot : public mediumUnit {
public:
	Zealot() {
		name = "zealot";
		mineral = 100;
		gas = 0;
		hp = 160;
		damage = 16;
		armour = 1;
		attackable = true;
		str = "For Adun!";
	}

	void buy(int& mineral, int& gas) {
		int flag = 0;
		if (mineral >= this->mineral) {
			mineral -= this->mineral;
			flag++;
		}
		else
			cout << "You've not enough minerals." << endl;

		if (gas >= this->gas) {
			gas -= this->gas;
			flag++;
		}
		else
			cout << "You require more Vespene gas." << endl;

		if (flag == 2)
			cout << "My life for Aiur" << endl;
	};
};

class Dragoon : public largeUnit {
public:
	Dragoon() {
		name = "dragoon";
		mineral = 125;
		gas = 50;
		hp = 180;
		damage = 20;
		armour = 1;
		attackable = true;
		str = "Confirmed.";
	}

	void buy(int& mineral, int& gas) {
		int flag = 0;
		if (mineral >= this->mineral) {
			mineral -= this->mineral;
			flag++;
		}
		else
			cout << "You've not enough minerals." << endl;

		if (gas >= this->gas) {
			gas -= this->gas;
			flag++;
		}
		else
			cout << "You require more Vespene gas." << endl;

		if (flag == 2)
			cout << "I have returned!" << endl;
	};
};

class Dropship : public largeUnit {
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
		mineral = 100;
		gas = 100;
		hp = 150;
		armour = 1;
		attackable = false;
	}
	
	~Dropship() {

	};

	void buy(int& mineral, int& gas) {
		int flag = 0;
		if (mineral >= this->mineral) {
			mineral -= this->mineral;
			flag++;
		}
		else
			cout << "Not enough minerals" << endl;

		if (gas >= this->gas) {
			gas -= this->gas;
			flag++;
		}
		else
			cout << "Insufficient Vespene gas" << endl;

		if (flag == 2)
			cout << "Can I take your order?" << endl;
	};

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

	int mineral = 1000;
	int gas = 1000;

	marine.buy(mineral, gas);
	tank.buy(mineral, gas);
	zealot.buy(mineral, gas);
	dragoon.buy(mineral, gas);
	dropship.buy(mineral, gas);
	cout << "------------------------------" << endl;

	dropship.load(zealot);
	dropship.load(marine);
	dropship.load(tank);
	dropship.load(dragoon);

	dragoon.attackable = false;

	zealot.fight(dragoon);
	marine.fight(dragoon);
	tank.fight(dragoon);

	dropship.drop();

	zealot.fight(dragoon);
	marine.fight(dragoon);
	tank.fight(dragoon);
	dropship.fight(dragoon);

	return 0;
}