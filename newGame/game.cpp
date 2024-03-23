#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iterator>
#include <sstream>
#include <set>
#include <utility>

#define sizeArray 9
#define icon_player '@'
#define icon_coin '$'
#define icon_tower '&'
#define player_config "config//config_player.txt"
#define field_config "config//config_field.txt"
#define coin_config "config//config_coin.txt"
#define creep_config "config//config_creep.txt"

using namespace std;

set<pair<int, int>> all_coordinates;
void generateUniqueCoordinates(int& x, int& y);

class Item
{
    private:
        string name;
        int price;
        string type;
    public:

        int getPrice()
        {
            return price;
        }

        string getName()
        {
            return name;
        }

        void setName(string name)
        {
            this->name = name;
        }

        void setPrice(int price)
        {
            this->price = price;
        }

        void setType(string type)
        {
            this->type = type;
        }

        string getType()
        {
            return type;
        }

        virtual ~Item() {}
};

class Potion : public Item
{
    private:

        int power;

    public:

        Potion(string name, string type, int power, int price)
        {
            this->power = power;
            setType(type);
            setPrice(price);
            setName(name);
        }

        void setPower(int power)
        {
            this->power = power;
        }

        int getPower()
        {
            return power;
        }
};

class player
{
    protected:

        string name;
        int x;
        int y;
    
    public:
        void setName(string name)
        {
            this->name = name;
        }

        string getName()
        {
            return name;
        }

        void setX(int x)
        {
            this->x = x;
        }

        int getX()
        {
            return x;
        }

        void setY(int y)
        {
            this->y = y;
        }

        int getY()
        {
            return y;
        }

        player()
        {
            x = 1;
            y = 1;
        }

        player(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
};

class attribute
{
    private:
        float agility;
        float strength;
        float intelligence;

    public:
        float getAgility()
        {
            return agility;
        }

        void setAgility(float agility)
        {
            this->agility = agility;
        }

        float getStrength()
        {
            return strength;
        }

        void setStrength(float strength)
        {
            this->strength = strength;
        }

        float getIntelligence()
        {
            return intelligence;
        }

        void setIntelligence(float intelligence)
        {
            this->intelligence = intelligence;
        }
};

class hero : public player, public attribute
{
    private:
        int armor;
        int damage;
        int max_health;
        float lvl;
        int xp;
        int xpToLvlUP;
        int silver;
        int miss;
        int current_health;

        void setArmor()
        {
            armor = round(getAgility() * 0.9);
        }

        void setDamage()
        {
            damage = round((getAgility() * 1.9) + (getStrength() * 1.9));
        }

        void setMaxHealth()
        {
            max_health = round(200 + (getStrength() * 49.9));
        }

    public:
        // --

        class Inventory
        {
            private:
                int size;
                vector<Item> items;
            public:

            void addItem(Item item) {
                items.push_back(item);
            }

            void removeItem(int index)
            {
                if(index >= 0 and index < items.size())
                {
                    items.erase(items.begin() + index);
                }
                else
                {
                    cout << "Out of range. Invent." << endl;
                    exit(1);
                }
            }

            void usePotion(int index, hero &gamer)
            {
                Potion* potion = dynamic_cast<Potion*>(&items[index]);
                if (potion != nullptr) {
                    if (potion->getType() == "hp") {
                    gamer.setCurrentHealth(gamer.getCurrentHealth() + potion->getPower());
                    if (gamer.getCurrentHealth() > gamer.getMaxHealth())
                    {
                        gamer.setCurrentHealth(gamer.getMaxHealth());
                    }
                }
                }

                removeItem(index);
            }

            vector<Item> getItems()
            {
                return items;
            }
        };

        Inventory invent;

        // --

        int getCurrentHealth()
        {
            return current_health;
        }

        int getMiss()
        {
            return miss;
        }

        int getArmor()
        {
            return armor;
        }

        int getDamage()
        {
            return damage;
        }

        int getMaxHealth()
        {
            return max_health;
        }

        void setCurrentHealth(int current_health)
        {
            this->current_health = current_health;
        }

        void setMiss(int miss)
        {
            this->miss = miss;
        }

        void setXP(int xp)
        {
            this->xp = xp;
        }

        int getXP()
        {
            return xp;
        }

        void setLvl(float lvl)
        {
            this->lvl = lvl;
        }

        float getLvl()
        {
            return lvl;
        }

        void lvlUp(int scores)
        {
            xp += scores;

            while (xp >= xpToLvlUP)
            {
                xp -= xpToLvlUP;

                lvl++;

                setAgility(getAgility()+1);
                setStrength(getStrength()+1);
                setIntelligence(getIntelligence()+1);

                setMaxHealth();
                setArmor();
                setDamage();
                forceMiss();

                setCurrentHealth(getMaxHealth());

                xpToLvlUP = xpToLvlUP * lvl;

                
            }
        }

        void forceLvlUp() {
            for (int i = 1; i < lvl; i++) {

                setAgility(getAgility()+1);
                setStrength(getStrength()+1);
                setIntelligence(getIntelligence()+1);

                setMaxHealth();
                setArmor();
                setDamage();
                setCurrentHealth(getMaxHealth());

            }
            xpToLvlUP = xpToLvlUP * lvl;
        }

        int getXpToLvlUP()
        {
            return xpToLvlUP;
        }

        void setSilver(int silver)
        {
            this->silver = silver;
        }

        int getSivler()
        {
            return silver;
        }

        void displayHealthBar() {
            const int barWidth = 20;
            cout << "HP: ";
            int pos = barWidth * current_health / max_health;
            for (int i = 0; i < barWidth; i++) {
                if (i < pos) {
                    cout << "|";
                } else if (i == pos) {
                    cout << "|";
                } else {
                    cout << " ";
                }
            }
            cout << " " << current_health << "/" << max_health << "\n";
        }

        void writeToFile(const string& filename) {
            ofstream outfile(filename);

            if (!outfile) {
                cout << "Не удалось открыть файл для записи" << endl;
                return;
            }

            outfile << "Player_name = " << name << "\n";
            outfile << "Max_Health = " << max_health << "\n";
            outfile << "Current_Health = " << current_health << "\n";
            outfile << "Armor = " << armor << "\n";
            outfile << "damage = " << damage << "\n";
            outfile << "Lvl = " << lvl << "\n";
            outfile << "XP = " << xp << "\n";
            outfile << "Silver = " << silver << "\n";
            outfile << "Agility = " << getAgility() << "\n";
            outfile << "Strength = " << getStrength() << "\n";
            outfile << "Intelligence = " << getIntelligence() << "\n";

            outfile.close();
        }

        void readFromFile(const string& filename) {
            ifstream infile(filename);

            if (!infile) {
                cout << "Не удалось открыть файл для чтения" << endl;
                return;
            }

            string line;
            while (getline(infile, line)) {
                size_t pos = line.find(" = ");
                if (pos != string::npos) {
                    string key = line.substr(0, pos);
                    string value = line.substr(pos + 3);

                    if (key == "Player_name") {
                        name = value;
                    } else if (key == "Max_Health") {
                        max_health = stoi(value);
                    } else if (key == "Current_Health") {
                        current_health = stoi(value);
                    } else if (key == "Armor") {
                        armor = stoi(value);
                    } else if (key == "damage") {
                        damage = stoi(value);
                    } else if (key == "Lvl") {
                        lvl = stoi(value);
                    } else if (key == "XP") {
                        xp = stoi(value);
                    } else if (key == "Silver") {
                        silver = stoi(value);
                    } else if (key == "Agility") {
                        setAgility(stoi(value));
                    } else if (key == "Strength") {
                        setStrength(stoi(value));
                    } else if (key == "Intelligence") {
                        setIntelligence(stoi(value));
                    }
                }
            }

            infile.close();
        }

        void forceMiss() {
            miss = getAgility() / 200;
        }

        hero()
        {
            x = 1;
            y = 1;

            xpToLvlUP = 100;

            setAgility(0);
            setStrength(0);
            setIntelligence(0);

            armor = 0;
            damage = 4;
            max_health = 100;
            lvl = 1;
            xp = 0;
            silver = 0;
            current_health = max_health;

        }
  
};

class gameField
{
    private:

        vector<vector<char>> field;

    public:


        void setField(vector<vector<char>> field)
        {
            this->field = field;
        }

        vector<vector<char>> getField()
        {
            return field;
        }

        bool isCoin(int x, int y)
        {
            return field[y][x] == icon_coin;
        }

        bool ishero(int x, int y)
        {
            return field[y][x] == icon_player;
        }

        void output()
        {
            for (size_t i = 0; i < sizeArray; i++)
            {
                for (size_t j = 0; j < sizeArray; j++)
                {
                    cout << field[i][j] << "\t";
                }
                cout << "\n";
            }
        }

        void writeToFile(const string& filename) {
    ofstream outfile(filename);

    if (!outfile) {
        cerr << "Не удалось открыть файл для записи" << endl;
        return;
    }

    for (const auto &row : field) {
        for (const auto &element : row) {
            outfile << element << ' ';
        }
        outfile << '\n';
    }

    outfile.close();
}

    void readFromFile(const string& filename) {
        ifstream infile(filename);

        if (!infile) {
            cerr << "Не удалось открыть файл для чтения" << endl;
            return;
        }

        string line;
        vector<vector<char>> newField;
        while (getline(infile, line)) {
            istringstream iss(line);
            vector<char> row((istream_iterator<char>(iss)), istream_iterator<char>());
            newField.push_back(row);
        }

        setField(newField);

        infile.close();
    }
};

class coin
{
    protected:
        int amount;
        vector<int> x;
        vector<int> y;
        int value;

    public:
        void setX(vector<int> x)
        {
            this->x = x;
        }

        vector<int> getX()
        {
            return x;
        }

        void setY(vector<int> y)
        {
            this->y = y;
        }

        vector<int> getY()
        {
            return y;
        }

        void setValue(int value)
        {
            this->value = value;
        }

        int getValue()
        {
            return value;
        }

        void setAmount(int amount)
        {
            this->amount = amount;
        }

        int getAmount()
        {
            return amount;
        }

        void coinInnit() {
            srand(time(0));
            for (int i = 0; i < amount; i++) {
                int x, y;
                generateUniqueCoordinates(x, y);
                this->x.push_back(x);
                this->y.push_back(y);
            }
        }

        void writeToFile(const string& filename) {
            ofstream outfile(filename);

            if (!outfile) {
                cout << "Не удалось открыть файл для записи" << endl;
                return;
            }

            outfile << "Amount = " << amount << "\n";
            outfile << "Value = " << value << "\n";

            for (size_t i = 0; i < x.size(); i++) {
                outfile << "X[" << i << "] = " << x[i] << "\n";
                outfile << "Y[" << i << "] = " << y[i] << "\n";
            }

            outfile.close();
        }

        void readFromFile(const string& filename) {
            ifstream infile(filename);

            if (!infile) {
                cout << "Не удалось открыть файл для чтения" << endl;
                return;
            }

            string line;
            while (getline(infile, line)) {
                size_t pos = line.find(" = ");
                if (pos != string::npos) {
                    string key = line.substr(0, pos);
                    string value = line.substr(pos + 3);

                    if (key == "Amount") {
                        amount = stoi(value);
                    } else if (key == "Value") {
                        value = stoi(value);
                    } else if (key.substr(0, 2) == "X[") {
                        x.push_back(stoi(value));
                    } else if (key.substr(0, 2) == "Y[") {
                        y.push_back(stoi(value));
                    }
                }
            }

            infile.close();
        }

        coin()
        {
            value = 200;
        }
};

class creep : public coin
{
    private:
        int damage, health, armor, lvl;
        int silver_value;
        int miss;
        string name;

    public:

        int getMiss()
        {
            return miss;
        }

        int getArmor()
        {
            return armor;
        }

        int getDamage()
        {
            return damage;
        }

        int getHealth()
        {
            return health;
        }

        void setMiss(int miss)
        {
            this->miss = miss;
        }

        void setHealth(int health)
        {
            this->health = health;
        }

        int getSilverValue()
        {
            return silver_value;
        }

        void setLvl(int lvl)
        {
            this->lvl = lvl;
        }

        int getLvl()
        {
            return lvl;
        }

        void setName()
        {
            this->name = name;
        }

        string getName()
        {
            return name;
        }

        creep()
        {
        }

        void writeToFile(const string& filename) {
            ofstream outfile(filename);

            if (!outfile) {
                cout << "Не удалось открыть файл для записи" << endl;
                return;
            }

            outfile << "Name = " << name << "\n";
            outfile << "Damage = " << damage << "\n";
            outfile << "Health = " << health << "\n";
            outfile << "Armor = " << armor << "\n";
            outfile << "Lvl = " << lvl << "\n";
            outfile << "Silver_value = " << silver_value << "\n";

            coin::writeToFile(filename + "_coin");

            outfile.close();
        }

        void readFromFile(const string& filename) {
            ifstream infile(filename);

            if (!infile) {
                cerr << "Не удалось открыть файл для чтения" << endl;
                return;
            }

            string line;
            while (getline(infile, line)) {
                size_t pos = line.find(" = ");
                if (pos != string::npos) {
                    string key = line.substr(0, pos);
                    string value = line.substr(pos + 3);

                    if (key == "Name") {
                        name = value;
                    } else if (key == "Damage") {
                        damage = stoi(value);
                    } else if (key == "Health") {
                        health = stoi(value);
                    } else if (key == "Armor") {
                        armor = stoi(value);
                    } else if (key == "Lvl") {
                        lvl = stoi(value);
                    } else if (key == "Silver_value") {
                        silver_value = stoi(value);
                    }
                }
            }

            coin::readFromFile(filename + "_coin");

            infile.close();
        }

        creep(string name)
        {
            armor = 1;
            damage = 7;
            health = 50;
            silver_value = 30;
            lvl = 1;
            miss = 0.1;

            amount = 2;

            this->name = name;

            coinInnit();
        }
        
};

class Tower
{
    private:
        int range;
        int amount;
        vector<int> x;
        vector<int> y;
        int value;
        
    public:

        vector<int> getX()
        {
            return x;
        }

        vector<int> getY()
        {
            return y;
        }

        void setX(vector<int> x)
        {
            this->x = x;
        }

        void setY(vector<int> y)
        {
            this->y = y;
        }

        int getAmount()
        {
            return amount;
        }

        int getRange()
        {
            return range;
        }

        void setRange(int range)
        {
            this->range = range;
        }

        void towerInnit() {
            srand(time(0));
            for (int i = 0; i < amount; i++) {
                int x, y;
                generateUniqueCoordinates(x, y);
                this->x.push_back(x);
                this->y.push_back(y);
            }
        }

        void towerVision(player &gamer) {
            for (int di = 0; di < amount; di++)
            {
                for (int i = -range; i <= range; i++) {
                    for (int j = -range; j <= range; j++) {
                        if ((y[di] + j == gamer.getY()) and (x[di] + i == gamer.getX())) {
                            cout << "Gotcha!" << endl;
                        }
                    }
                }
            }
        }

        Tower(int range)
        {
            this->range = range;
            value = 500;
            amount = 1;
            towerInnit();
        }
};

class Attack {
    private:

        hero gamer;
        creep mob;
        int cnt;

    public:

        Attack(hero &gamer, creep &mob)
        {
            this->gamer = gamer;
            this->mob = mob;
            cnt = 0;
        }

        void attackOnCreep()
        {
            int damage = mob.getHealth() - (gamer.getDamage() - (gamer.getDamage()*(mob.getArmor() * 0.05)));

            mob.setHealth(damage);

            if (mob.getHealth() < 0)
            {
                mob.setHealth(0);
            }

            if (mob.getHealth() == 0)
            {
                gamer.setSilver(gamer.getSivler()+mob.getSilverValue());
                gamer.lvlUp(mob.getValue());
            }

            mobCounterAttack();
        }

        void attackOnPlayer()
        {
            int damage = gamer.getCurrentHealth() - (mob.getDamage() - (mob.getDamage()*gamer.getArmor()*0.05));

            gamer.setCurrentHealth(damage);

            if (gamer.getCurrentHealth() <= 0)
            {
                gamer.setCurrentHealth(0);
            }
        }

        void mobCounterAttack() {

            srand(time(0));

            if (rand() % 2 == 0) {
                attackOnPlayer();
            } else {
                return;
            }
        }

        hero &getGamer()
        {
            return gamer;
        }

        creep &getMob()
        {
            return mob;
        }
};

template <typename T>
class Shop
{
    private:
        vector<T> items;
        string name;
    public:

        void setItems(vector<T> items)
        {
            this->items = items;
        }

        vector<T> getItems()
        {
            return items;
        }

        void setName(string name)
        {
            this->name = name;
        }

        string getName()
        {
            return name;
        }

        void addItem(T &item)
        {
            items.push_back(item);
        }

        void addArrayItems(vector<T> items)
        {
            this->items = items;
        }

        void showItem(string name, int index)
        {
            if (index < items.size() and (name == items[index].getName()))
            {
                cout << items[index].getName();
            }
        }

        Shop(string name)
        {
            this->name = name;
        }

};


void run();
void creationField(gameField &gField, hero &gamer, creep &mob, Tower &turret);
void movement(gameField &gField, hero &gamer, char key);
void coinClaim(hero &gamer, creep &mob, bool &menu);
void stats_menu(hero &gamer, bool &game);
vector<Potion> potionInnit();
void shopMenu(bool &shop, hero &gamer);
void invent(bool &inv, hero& gamer);

int main()
{
    system("mkdir config");
    run();
}

void generateUniqueCoordinates(int& x, int& y) {
    do {
        x = rand() % (sizeArray - 2) + 1;
        y = rand() % (sizeArray - 2) + 1;
    } while (all_coordinates.find(make_pair(x, y)) != all_coordinates.end());

    all_coordinates.insert(make_pair(x, y));
}

void creationField(gameField &gField, hero &gamer, creep &mob, Tower &turret)
{
    vector<vector<char>> FieldArr(sizeArray, vector<char>(sizeArray));

    for (size_t i = 0; i < sizeArray; i++)
    {
        for (size_t j = 0; j < sizeArray; j++)
        {
            if (i == 0 or i == sizeArray - 1 or j == 0 or j == sizeArray - 1)
            {
                FieldArr[i][j] = '#';
            }
            else
            {
                FieldArr[i][j] = ' ';
            }
        }
    }

    vector<int> xmob,ymob, xturret, yturret;

    xmob = mob.getX();
    ymob = mob.getY();

    xturret = turret.getX();
    yturret = turret.getY();

    for (int i = 0; i < mob.getAmount(); i++)
    {
        FieldArr[ymob[i]][xmob[i]] = icon_coin;
    }

    for (int i = 0; i < turret.getAmount(); i++)
    {
        FieldArr[yturret[i]][xturret[i]] = icon_tower;
    }

    FieldArr[gamer.getY()][gamer.getX()] = icon_player;

    gField.setField(FieldArr);

}

void movement(gameField &gField, hero &gamer, char key)
{
    switch (key)
    {
    case 'w':
        if (gField.getField()[gamer.getY()-1][gamer.getX()] != '#' and gField.getField()[gamer.getY()-1][gamer.getX()] != '&')
        {
            gamer.setY(gamer.getY()-1);
        }
        break;

    case 's':
        if (gField.getField()[gamer.getY()+1][gamer.getX()] != '#' and gField.getField()[gamer.getY()+1][gamer.getX()] != '&')
        {
            gamer.setY(gamer.getY()+1);
        }
        break;

    case 'a':
        if (gField.getField()[gamer.getY()][gamer.getX()-1] != '#' and gField.getField()[gamer.getY()][gamer.getX()-1] != '&')
        {
            gamer.setX(gamer.getX()-1);
        }
        break;

    case 'd':
        if (gField.getField()[gamer.getY()][gamer.getX()+1] != '#' and gField.getField()[gamer.getY()][gamer.getX()+1] != '&')
        {
            gamer.setX(gamer.getX()+1);
        }
        break;
    
    default:
        break;
    }
    
}

void attack_menu(bool &menu, hero &gamer, creep &mob)
{
    char key;

    Attack atk(gamer, mob);

    while(menu)
    {
        system("cls");

        cout << "You: " << endl;
        cout << "===========================" << endl;
        cout << "Name: " << gamer.getName() << endl;
        cout << "Level: " << gamer.getLvl() << endl;
        cout << "===========================" << endl;
        gamer.displayHealthBar();
        cout << "Armor: " << gamer.getArmor() << endl;
        cout << "Damage: " << gamer.getDamage() << endl;
        cout << "===========================" << endl << endl;

        cout << "Enemy:" << endl;
        cout << "===========================" << endl;
        cout << "Name: " << mob.getName() << endl;
        cout << "Level: " << mob.getLvl() << endl;
        cout << "===========================" << endl;
        cout << "Health: " << mob.getHealth() << endl;
        cout << "Armor: " << mob.getArmor() << endl;
        cout << "Damage: " << mob.getDamage() << endl;
        cout << "===========================" << endl << endl;

        cout << "Choose an action." << endl;
        cout << "Press 'a' to attack." << endl;
        cout << "Press 'q' to escape." << endl;
        cout << "Press 'd' to defence." << endl;

        if(_kbhit)
        {
            key = _getch();

            if (key == 'q')
            {
                menu = false;
            } else if (key == 'a')
            {
                atk.attackOnCreep();
                gamer = atk.getGamer();
                mob = atk.getMob();
                if (mob.getHealth() == 0)
                {
                    menu = false;
                    mob.setHealth(50);
                }
            }

        }

        if (gamer.getCurrentHealth() == 0)
        {
            cout << "YOU DIED" << endl;
            gamer.writeToFile(player_config);
            mob.writeToFile(creep_config);
            exit(0);
        }

    }
    
}

void coinClaim(hero &gamer, creep &mob, bool &menu)
{
    vector<int> x_mob,y_mob;
    x_mob = mob.getX();
    y_mob = mob.getY();

    for (int i = 0; i < mob.getAmount(); i++)
    {
        if (x_mob[i] ==  gamer.getX() and y_mob[i] == gamer.getY())
        {
            menu = true;
            x_mob.erase(x_mob.begin() + i);
            y_mob.erase(y_mob.begin() + i);
            mob.setAmount(mob.getAmount() - 1);
            attack_menu(menu, gamer, mob);
            break;
        }
    }

    mob.setX(x_mob);
    mob.setY(y_mob);
}

void stats_menu(hero &gamer, bool &menu)
{
    system("cls");

    cout << "===========================" << endl;
    cout << "Name: " << gamer.getName() << endl;
    cout << "Level: " << gamer.getLvl() << endl;
    cout << "===========================" << endl;
    cout << "Max Health: " << gamer.getMaxHealth() << endl;
    cout << "Current Health: " << gamer.getCurrentHealth() << endl;
    cout << "Armor: " << gamer.getArmor() << endl;
    cout << "Damage: " << gamer.getDamage() << endl;
    cout << "===========================" << endl;
    cout << "Agility: " << gamer.getAgility() << endl;
    cout << "Strength: " << gamer.getStrength() << endl;
    cout << "Intelligence: " << gamer.getIntelligence() << endl;
    cout << "===========================" << endl;
    cout << "Press 'p' to continue";

    char key;
    do
    {
        if(_kbhit())
        {
            key = _getch();
        }
    } while (key != 'p');

    menu = false;
}

vector<Potion> potionInnit()
{
    vector<Potion> potions;

    Potion baseHeal("Healing Potion", "hp", 50, 20);
    Potion superHeal("Super Healing Potion", "hp", 100, 40);

    potions.push_back(baseHeal);
    potions.push_back(superHeal);

    return potions;
}

void shopMenu(bool &shop, hero &gamer)
{
    shop = true;
    Shop<Potion> potionShop("potions");
    potionShop.addArrayItems(potionInnit());

    int selectedItem = 0;

    while (shop) {
        system("cls");
        cout << "==============================" << endl;
        for (int i = 0; i < potionShop.getItems().size(); i++) {
            if (i == selectedItem)
                cout << "> ";
            else
                cout << "  ";
            cout << potionShop.getItems()[i].getName() << " - " << potionShop.getItems()[i].getPrice() << " Silver" << endl;
            cout << "==============================" << endl;
        }
        cout << "Your silver: " << gamer.getSivler() << endl;
        cout << "==============================" << endl;
        cout << "Press 'E' to buy an Item" << endl;
        cout << "Press 'p' to continue";

        char key = getch();
        if (key == 'w' && selectedItem > 0) {
            selectedItem--;
        }
        else if (key == 's' && selectedItem < potionShop.getItems().size() - 1) {
            selectedItem++;
        }
        else if (key == 'e') {

            if (gamer.getSivler() >= potionShop.getItems()[selectedItem].getPrice()) {
                gamer.setSilver(gamer.getSivler() - potionShop.getItems()[selectedItem].getPrice());
                gamer.invent.addItem(potionShop.getItems()[selectedItem]);
                cout << "You bought: " << potionShop.getItems()[selectedItem].getName() << endl;
            }

        } else if (key == 'p') {
            shop = false;
        }
    }
}

void invent(bool &inv, hero& gamer)
{
    inv = true;

    int selectedItem = 0;

    while (inv)
    {
        system("cls");
        cout << "===========================" << endl;
        for (int i = 0; i < gamer.invent.getItems().size(); i++) {
            if (i == selectedItem)
                cout << "> ";
            else
                cout << "  ";
            cout << gamer.invent.getItems()[i].getName() << endl;
            cout << "===========================" << endl;
        }
        cout << "Press 'p' to continue";

        

        char key = getch();

        if (key == 'w' && selectedItem > 0) {
            selectedItem--;
        }
        else if (key == 's' && selectedItem < gamer.invent.getItems().size() - 1) {
            selectedItem++;
        }
        else if (key == 'p') {
            inv = false;
        } else if (key == 'e') {
            gamer.invent.usePotion(selectedItem, gamer);
        }
        
    }
}

void run()
{
    creep mob("Goblin");
    gameField gf;
    hero gamer;

    bool game = true;
    bool menu = false;
    bool inv = false;
    bool prof = true;
    bool shop = false;

    Tower turret(1);
    string name;

    int profile = -1;

    while (prof) {

        cout << "Do you want to create a new profile or upload an existing one(1,2): ", cin >> profile;

        if (profile == 1) {
            
            char c;
            cout << "Your prev profile will be replaced. Continue? y/n: ";
            cin >> c;
            
            if (c == 'y') {
                cout << "Enter your name: ", cin >> name;
                gamer.setName(name);

                gamer.writeToFile(player_config);
                gf.writeToFile(field_config);
                mob.writeToFile(creep_config);
                prof = false;
            } else if (c == 'n') {
                
            } else {
                cout << "Write y/n" << endl;
            }
            
        } else if (profile == 2) {
            gamer.readFromFile(player_config);
            gf.readFromFile(field_config);
            mob.readFromFile(creep_config);
            gamer.forceLvlUp();
            prof = false;
        }
    }


    while (game)
    {
        if (!menu)
        {
            system("cls");
            creationField(gf, gamer, mob, turret);
            gf.output();
            turret.towerVision(gamer);

            cout << "XP: " << gamer.getXP() << endl;
            cout << "Need to lvlUP: " << gamer.getXpToLvlUP() << endl;
            gamer.displayHealthBar();
            cout << "Press 'E' to open stats" << endl;
            cout << "Press 'B' to open shop" << endl;
            cout << "Press 'I' to open Inventory" << endl;
        }

        if (_kbhit)
        {
            char key = _getch();

            if (key == 'q')
            {
                game = false;
            } 
            else if (key == 'e')
            {
                stats_menu(gamer, menu);
            }
            else if (key == 'b')
            {
                shopMenu(shop, gamer);
            } else if (key == 'i')
            {
                invent(inv, gamer);
            }
            else if (!menu and !shop and !inv)
            {
                movement(gf, gamer, key);
            }
        }
        coinClaim(gamer, mob, menu);

        gamer.writeToFile(player_config);
        gf.writeToFile(field_config);
        mob.writeToFile(creep_config);

        if (gamer.getCurrentHealth() == 0)
        {
            cout << "YOU DIED" << endl;
            exit(0);
        }
    }
}