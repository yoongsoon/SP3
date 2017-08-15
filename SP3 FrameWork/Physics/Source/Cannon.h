#pragma once

#include "WeaponInfo.h"
#include "SceneBase.h"
#include "Vector3.h"
//include where them projectile header???
#include <list>
class Cannon
	: public Weapon_Info
{
public:
	Cannon();
	virtual ~Cannon();
	//initializer of dafault values
	void Init(void);
private:

};
