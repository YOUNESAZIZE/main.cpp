#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

class Equipment
{
	list<string> _items;
	int _bucklerLife;
	bool _bucklerTwo;

	int _greatSword;

public:
	void AddItem(const string &item)
	{
		_items.push_back(item);

		if(item == "buckler")
		{
			_bucklerLife = 3;
			_bucklerTwo = false;
		}

		if(item == "Great Sword")
			_greatSword = 0;
	}

	int GetDamage()
	{
		int dmg = 2;

		if(HasItem("Great Sword"))
		{
			dmg = (_greatSword < 2) ? 12 : 0;
			_greatSword = (_greatSword + 1) % 3;
		}
		else if(HasItem("hand sword"))
			dmg = 5;
		else if(HasItem("hand axe"))
			dmg = 6;

		if(dmg > 0 && HasItem("armor"))
			dmg -= 1;

		return dmg;
	}

	bool HasItem(const string &an_item) const
	{
		for(const string &item : _items)
			if(item == an_item)
				return true;

		return false;
	}

	bool Block(bool from_axe)
	{
		if(HasItem("buckler"))
		{
			_bucklerTwo = ! _bucklerTwo;

			if(_bucklerTwo)
			{
				if(from_axe)
				{
					_bucklerLife--;

					if(!_bucklerLife)
						_items.remove("buckler");
				}

				return true;
			}
		}

		return false;
	}
};


class Warrior
{
    int _hitPoints;
	Equipment _equipment;
    string _level;

public:
    Warrior(int hp)
    {
        _hitPoints = hp;
    }

    int HitPoints() const
    {
        return _hitPoints;
    }

    void Equip(const string &item)
    {
		_equipment.AddItem(item);
    }

    void Engage(Warrior &opponent)
    {
        int round = 0;
        while(HitPoints() > 0 && opponent.HitPoints() > 0)
        {
            if(round % 2 == 0)
                DoBlow(opponent);
            else
                opponent.DoBlow(*this);

            round++;
        }
    }

public:
    void DoBlow(Warrior &opponent)
    {
		if(!opponent.Block(*this))
			opponent.Hurt(_equipment.GetDamage());
    }

	bool Block(Warrior &opponent)
	{
		return _equipment.Block(opponent._equipment.HasItem("hand axe"));
	}

	void Hurt(int damage)
	{
		if(_equipment.HasItem("armor"))
			damage -= 3;

		_hitPoints -= min(damage, _hitPoints);
	}
};

class Swordsman : public Warrior
{
public:
	Swordsman(string level = string())
		: Warrior(100)
	{
		Equip("hand sword");
	}

};

class Viking : public Warrior
{
public:
	Viking()
		: Warrior(120)
	{
		Equip("hand axe");
	}
};

class Highlander : public Warrior
{
public:
	Highlander(string level = string())
		: Warrior(150)
	{
		Equip("Great Sword");
	}
};


static void SwordsmanVsViking()
{
    Swordsman swordsman;
    Viking viking;
    swordsman.Engage(viking);
    cout << "Swordsman (0) = " << swordsman.HitPoints() << endl;
    cout << "Viking (35) = " << viking.HitPoints() << endl;
    cout << endl;
}


static void SwordsmanWithBucklerVsVikingWithBuckler()
{
    Swordsman swordsman;
    swordsman.Equip("buckler");
    Viking viking;
    viking.Equip("buckler");
    swordsman.Engage(viking);
    cout << "SwordsmanWithBuckler (0) = " << swordsman.HitPoints() << endl;
    cout << "VikingWithBuckler (70) = " << viking.HitPoints() << endl;
    cout << endl;
}


static void ArmoredSwordsmanVsHighlander()
{
    Highlander highlander;
    Swordsman swordsman;
    swordsman.Equip("buckler");
    swordsman.Equip("armor");
    swordsman.Engage(highlander);
    cout << "ArmoredSwordsman (0) = " << swordsman.HitPoints() << endl;
    cout << "Highlander (10) = " << highlander.HitPoints() << endl;
    cout << endl;
}




 */
static void ViciousSwordsmanVsVeteranHighlander()
{
	Swordsman swordsman("Vicious");
	SwordsmanVsViking();
	SwordsmanWithBucklerVsVikingWithBuckler();
	ArmoredSwordsmanVsHighlander();
	ViciousSwordsmanVsVeteranHighlander();
	return 0;
}


int main(int argc, char *argv[])
{
	SwordsmanVsViking();
	SwordsmanWithBucklerVsVikingWithBuckler();
	ArmoredSwordsmanVsHighlander();
	ViciousSwordsmanVsVeteranHighlander();
	return 0;
}
