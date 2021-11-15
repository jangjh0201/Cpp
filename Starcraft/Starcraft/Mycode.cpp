#include <iostream>
#include <string>

using namespace std;

class Unit {
protected:
	string name, verse;
	int mineral, gas, hp, damage, armour, slotSize;
	bool attackable, alive = true;

private:
	void getAttacked(Unit& unit) {
		cout << unit.verse << endl;
		int realDamage = unit.damage - this->armour;
		//공격력보다 방어력이 높은 경우 데미지 = 0
		if (realDamage <= 0) realDamage = 0;
		this->hp -= realDamage;

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

public:
	Unit() {
	}
	
	~Unit() {
	}

	void Fight(Unit& unit) {
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

	string GetName() { return this->name; }
	string GetVerse() { return this->verse; }
	int GetMIneral() { return this->mineral; }
	int GetGas() { return this->gas; }
	int GetHp() { return this->hp; }
	int GetDamage() { return this->damage; }
	int GetArmour() { return this->armour; }
	int GetSlotSize() { return this->slotSize; }
	bool GetAttackable() { return this->attackable; }
	bool GetAlive() { return this->alive; }

	void SetName(const string name) { this->name = name; }
	void SetVerse(const string verse) { this->verse = verse; }
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

class Marine : public smallUnit {
public:
	Marine() {
		name = "marine";
		verse = "Go! Go! Go!";
		mineral = 50;
		gas = 0;
		hp = 40;
		damage = 6;
		armour = 0;
		attackable = true;
	}

	void Buy(int& mineral, int& gas) {
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
		verse = "Move it!";
		mineral = 150;
		gas = 50;
		hp = 150;
		damage = 30;
		armour = 1;
		attackable = true;
	}

	void Buy(int& mineral, int& gas) {
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
		verse = "For Adun!";
		mineral = 100;
		gas = 0;
		hp = 160;
		damage = 16;
		armour = 1;
		attackable = true;
	}

	void Buy(int& mineral, int& gas) {
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
		verse = "Confirmed.";
		mineral = 125;
		gas = 50;
		hp = 180;
		damage = 20;
		armour = 1;
		attackable = true;
	}

	void Buy(int& mineral, int& gas) {
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

	void Buy(int& mineral, int& gas) {
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
	
	void Load(Unit& unit) {
		if (this->slot - unit.GetSlotSize() < 0) {
			cout << "not enough empty slot" << endl << endl;
		}
		else {
			unitArr[unitCount] = &unit;
			unitArr[unitCount]->SetAttackable(false);
			cout << "dropship load " << unitArr[unitCount]->GetName() << endl;

			printStatus();
			this->slot -= unit.GetSlotSize();
			this->unitCount++;
		}
	};

	void Drop() {
		int i = 0;
		while (i < this->unitCount) {
			cout << unitArr[i]->GetName() << " drop" << endl;
			unitArr[i]->SetAttackable(true);
			i++;
		}
		delete unitArr;
	};
private:
	void printStatus() {
		int i = 0;
		cout << "empty: " << slot << endl;
		cout << "---------dropship---------" << endl;
		while (i <= this->unitCount) {
			cout << unitArr[i]->GetName() << " ";
			i++;
		}
		cout << endl << "---------dropship---------" << endl;
	};
};

int main() {
	Marine marine;
	Tank tank;
	Zealot zealot;
	Dragoon dragoon;
	Dropship dropship;

	int mineral = 1000;
	int gas = 1000;

	marine.Buy(mineral, gas);
	tank.Buy(mineral, gas);
	zealot.Buy(mineral, gas);
	dragoon.Buy(mineral, gas);
	dropship.Buy(mineral, gas);
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