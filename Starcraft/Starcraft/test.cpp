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
	bool alive = true;
	bool attackable;

	void fight(Unit& unit) {
		unit.getAttacked(*this);

		if (unit.hp <= 0) {
			cout << unit.name << " die" << endl;
			cout << unit.name << " not alive" << endl;
			cout << this->name << "'s hp: " << this->hp << endl;
		}

		//���� �޾Ҵ� ������ ������ ���, ������ ���ֿ��� �ݰ���.
		if (unit.alive)
			this->getAttacked(unit);

		cout << endl;
	}

	int attack() {
		return this->damage;
	}

	//getAttacked() �Լ��� ȣ���� ������ ���ݹ���.
	virtual void getAttacked(Unit& unit) {
		if (this->name == "dropship")
			cout << "dropship can not attack" << endl;
		else {
			cout << this->name << " attack" << endl;
			int real_damage = unit.attack() - this->armour;
			//���ݷº��� ������ ���� ��� ������ = 0
			if (real_damage <= 0)
				real_damage = 0;

			this->hp -= real_damage;
			//������ �޾� ü���� 0�� �Ǹ� ������ �� �� ������ ��.
			if (this->hp <= 0)
				this->alive = false;
			else
				cout << this->name << "'s hp: " << this->hp << endl;
		}
	}
};
class smallUnit : public Unit {
};
class mediumUnit : public Unit {
};
class largeUnit : public Unit {
};

class Marine : public smallUnit {
public:
	Marine() {
		name = "marine";
		mineral = 50;
		gas = 0;
		hp = 40;
		damage = 6;
		armour = 0;
	}
	void buy(int& mineral, int& gas) {
		int flag = 0; // ������ ���� �������� �Ǻ�. flag ���� 2�� ���� ���� ����.
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

	//overriding
	void getAttacked(Unit& unit) {
		if (this->attackable == true) {
			cout << "Go! Go! Go!" << endl;
			int real_damage = this->attack() - unit.armour;
			//���ݷº��� ������ ���� ��� ������ = 0
			if (real_damage <= 0)
				real_damage = 0;

			unit.hp -= real_damage;
			if (unit.hp <= 0)
				unit.alive = false;
			else
				cout << unit.name << "'s hp: " << unit.hp << endl;
		}
		else {
			cout << this->name << " can not attack" << endl;
			cout << unit.name << "'s hp: " << unit.hp << endl;
		}
	}
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
	//overriding
	void getAttacked(Unit& unit) {
		if (this->attackable == true) {
			cout << "Move it!" << endl;
			int real_damage = this->attack() - unit.armour;
			//���ݷº��� ������ ���� ��� ������ = 0
			if (real_damage <= 0)
				real_damage = 0;

			unit.hp -= real_damage;
			if (unit.hp <= 0)
				unit.alive = false;
			else
				cout << unit.name << "'s hp: " << unit.hp << endl;
		}
		else {
			cout << this->name << " can not attack" << endl;
			cout << unit.name << "'s hp: " << unit.hp << endl;
		}
	}
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
	//overriding
	void getAttacked(Unit& unit) {
		if (this->attackable == true) {
			cout << "For Adun!" << endl;
			int real_damage = this->attack() - unit.armour;
			//���ݷº��� ������ ���� ��� ������ = 0
			if (real_damage <= 0)
				real_damage = 0;

			unit.hp -= real_damage;
			if (unit.hp <= 0)
				unit.alive = false;
			else
				cout << unit.name << "'s hp: " << unit.hp << endl;
		}
		else {
			cout << this->name << " can not attack" << endl;
			cout << unit.name << "'s hp: " << unit.hp << endl;
		}
	}
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
	//overriding
	void getAttacked(Unit& unit) {
		if (this->attackable == true) {
			cout << "Confirmed." << endl;
			int real_damage = this->attack() - unit.armour;
			//���ݷº��� ������ ���� ��� ������ = 0
			if (real_damage <= 0)
				real_damage = 0;

			unit.hp -= real_damage;
			if (unit.hp <= 0)
				unit.alive = false;
			else
				cout << unit.name << "'s hp: " << unit.hp << endl;
		}
		else {
			cout << this->name << " can not attack" << endl;
			cout << unit.name << "'s hp: " << unit.hp << endl;
		}
	}
};

class Dropship : public largeUnit {
public:
	int slot = 8;
	int unit_count;
	Unit* unit_arr = new Unit[8];
	int i = 0;

	Dropship() {
		name = "Dropship";
		mineral = 100;
		gas = 100;
		hp = 150;
		damage = 0;
		armour = 1;
	}

	~Dropship() {
	}

	void load(Unit& unit) {
		unit_arr[i] = unit;

		if (unit_arr[i].name == "marine") {
			cout << "marine �� �迭 �ּ� :" << &unit_arr[i] << endl;
			slot -= 1;
			if (slot < 0) {
				cout << "not enough empty slot" << endl << endl;
				i--;
			}
			else {
				cout << "dropship load " << unit_arr[i].name << endl;
				printStatus();
				unit_arr[i].attackable = false;
				i++;
			}
		}
		else if (unit_arr[i].name == "zealot") {
			cout << "zealot �� �迭 �ּ� :" << &unit_arr[i] << endl;
			slot -= 2;
			if (slot < 0) {
				cout << "not enough empty slot" << endl << endl;
				i--;
			}
			else {
				cout << "dropship load " << unit_arr[i].name << endl;
				printStatus();
				unit_arr[i].attackable = false;
				i++;
			}
		}
		else if (unit_arr[i].name == "tank" || unit_arr[i].name == "dragoon") {
			cout << "tank �� �迭 �ּ� :" << &unit_arr[i] << endl;
			slot -= 4;
			if (slot < 0) {
				cout << "not enough empty slot" << endl << endl;
				i--;
			}
			else {
				cout << "dropship load " << unit_arr[i].name << endl;
				printStatus();
				unit_arr[i].attackable = false;
				i++;
			}
		}
	}

	void printStatus() {
		int j = 0;
		cout << "empty: " << slot << endl;
		cout << "---------dropship---------" << endl;
		while (j <= i) {
			cout << unit_arr[j].name << " ";
			j++;
		}
		cout << endl << "---------dropship---------" << endl;
	}

	void drop() {
		int j = 0;
		while (j <= i) {
			cout << "drop�� �� �迭 �ּ� :" << &unit_arr[j] << endl;
			cout << unit_arr[j].name << " drop" << endl;
			unit_arr[j].attackable = true;
			j++;
		}
	}
	void buy(int& mineral, int& gas) {
		int flag = 0; // ������ ���� �������� �Ǻ�. flag ���� 2�� ���� ���� ����.
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
			cout << "Can I take your order?" << endl;
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
	marine.buy(mineral, gas);
	//cout << mineral << endl;

	tank.buy(mineral, gas);
	zealot.buy(mineral, gas);
	dragoon.buy(mineral, gas);
	dropship.buy(mineral, gas);
	cout << "------------------------------" << endl;

	dropship.load(zealot);
	dropship.load(marine);
	dropship.load(tank);
	dropship.load(dragoon);

	zealot.getAttacked(dragoon);
	marine.getAttacked(dragoon);
	tank.getAttacked(dragoon);

	cout << endl;
	dropship.drop();
	cout << endl;

	zealot.getAttacked(dragoon);
	marine.getAttacked(dragoon);
	tank.getAttacked(dragoon);
	dropship.getAttacked(dragoon);

	return 0;
}