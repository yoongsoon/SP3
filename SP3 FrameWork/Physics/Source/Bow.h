#pragma once



#include "WeaponInfo.h"
#include "SceneBase.h"
#include "Vector3.h"
//include where them projectile header???
#include <list>
class Bow
	: public Weapon_Info
{
public:
	Bow();
	virtual ~Bow();
	//initializer of dafault values
	void Init(void);
private:

};
