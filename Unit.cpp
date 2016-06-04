#include "Unit.h"

Unit::Unit(UnitType ut)
{
}


Unit::~Unit()
{
}

int Unit::Attack(const Unit &unit){ return 0; }
int Unit::TakeDamage(int damage){ return 0; }
bool Unit::Move(vector<int> coords){ return true; }
