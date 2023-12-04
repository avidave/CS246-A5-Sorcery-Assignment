#ifndef _ABILITY_H_
#define _ABILITY_H_

#include <vector>
#include <string>
#include "owner.h"
#include "card.h"
#include "collection.h"
#include "ritual.h"

using namespace std;

class Ability {
	protected:
		vector<string> targets;
	public:
		Ability(vector<string> targets);
		vector<string> get_targets();
		virtual string getType() = 0;
		virtual bool activate(Owner &p, int pos);
		virtual bool activate(Owner *p);
		virtual bool activate(Card *c, int pos, Owner *p);
		virtual bool activate(Ritual *r);
		//virtual void activate(Card &c, Owner &p) = 0;
		//virtual void activate(Owner &p1, Owner &p2) = 0;

};

class Damage : public Ability {
	int damage;
	public:
		Damage(vector<string> targets, int damage);
		string getType() override;
		bool activate(Owner &p, int pos) override;
};

class DamageAll : public Ability {
	int damage;
	public:
		DamageAll(vector<string> targets, int damage);
		string getType() override;
		bool activate(Owner *p) override;
};

class Move : public Ability {
	public:
		Move(vector<string> targets);
		string getType() override;
		bool activate(Card *c, int pos, Owner *p) override;

};


class Destroy : public Ability {
	public:
		Destroy(vector<string> targets);
		string getType() override;
		bool activate(Card *c, int pos, Owner *p) override;
};


class Charge : public Ability {
	int num;
	public:
		Charge(vector<string> targets, int num);
		string getType() override;
		bool activate(Ritual *r) override;
};

#endif
