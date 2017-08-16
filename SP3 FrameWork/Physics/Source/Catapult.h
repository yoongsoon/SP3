#pragma once



#include "WeaponInfo.h"
#include "SceneBase.h"
#include "Vector3.h"
//include where them projectile header???
#include <list>
class Catapult
	: public Weapon_Info
{
public:
	Catapult();
	virtual ~Catapult();
	//initializer of dafault values
	void Init(void);
private:

};
