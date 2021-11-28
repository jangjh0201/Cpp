#include <iostream>
#include <string>
#include "Mycode.h"

using namespace std;

void Unit::getAttacked(Unit& unit) {
	cout << unit.rush << endl;
	int realDamage = unit.damage - this->armour;
	//���ݷº��� ������ ���� ��� ������ = 0
	if (realDamage <= 0) realDamage = 0;
	this->hp -= realDamage;

	//������ �޾� ü���� 0�� �Ǹ� ������ �� �� ������ ��.
	if (this->hp > 0) {
		cout << this->name << "'s hp: " << this->hp << endl;
	}
	else {
		this->alive = false;
		cout << this->name << " die" << endl;
		cout << this->name << " not alive" << endl;
	}
};

void Unit::Fight(Unit& unit) {
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
};

void Dropship::Load(Unit& unit) {
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

void Dropship::Drop() {
	int i = 0;
	while (i < this->unitCount) {
		cout << unitArr[i]->GetName() << " drop" << endl;
		unitArr[i]->SetAttackable(true);
		i++;
	}
	delete[] unitArr;
};

void Dropship::printStatus() {
	int i = 0;
	cout << "empty: " << slot << endl;
	cout << "---------dropship---------" << endl;
	while (i <= this->unitCount) {
		cout << unitArr[i]->GetName() << " ";
		i++;
	}
	cout << endl << "---------dropship---------" << endl;
};