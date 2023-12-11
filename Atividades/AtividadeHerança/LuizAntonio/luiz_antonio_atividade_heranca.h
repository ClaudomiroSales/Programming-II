/*Criar três hierarquia, sendo duas de três níveis, como explicado em sala e 
no Classroom. Fazer a sobrecarga para cada classe dos operadores =, ==, ≠, ! e << 
(friend). Usar sempre que possível o static_cast para reaproveitamento de código. 
Para cada classe do seu projeto criar pelo menos três constructores, 
sendo um o constructor de cópia. É necessário ter a funcionalidade: 1. 
leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
processamento das variáveis de status e 3. salvamento dessas variáveis. 
Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/


//// Geral - parte para revisão
    //Diagrama UML - //>>>Comentário: faltou o outro lado de spells mas vou considerar
    // pelo trabalho está bem elaborado
    //Organização do código 

//// O .h das classes bases

     ////Classe base 1    


#include "../Items/Weapons/Sword.h"
#include "../Items/Armors/Armor.h"
#include "../Utils/Date.h"



enum item_type {
    // NONE = -1,
    SWORD = 0,
    ARMOR = 1,
    TOTAL_ITEM_TYPES = 2
};

enum weapon_type {
    UNARMED = 0,
    STEEL_SWORD = 1,
    IGNI = 2,
    // SILVER_SWORD = 2,
    // TOTAL_WEAPON_TYPES = 3
};

struct inventory_items {
    vector<Sword*> swords;
    vector<Armor*> armors;
};

class Entity {
public:
    Entity();
    Entity(const Entity &other_entity);
    ~Entity();

    ...
    
    // add an item and deletes it
    void add_item(Item &);
    // just deletes an inventory item
    void remove_item(int item_type, int item_index);

    // add an item from a source and deletes it
    void grab_item(vector<Item*> &source_items, int item_index = 0);
    // remove an item and put it somewhere
    void drop_item(vector<Item*> &destiny_items, int item_type, int item_index);

    void print_inventory() const;

    virtual void life_regen(int);
    virtual void stamina_regen(int);
    virtual void gain_xp(int);

    virtual void level_up() = 0;
    virtual void update_atributes() = 0;
    virtual void update_all_resistances() = 0;
    virtual void update_all_weaknesses() = 0;
    
    virtual void attack(Entity &, int) = 0;
    virtual void receive_damage(int physical_damage, 
                                int fire_damage = 0, 
                                int poison_damage = 0, 
                                int ice_damage = 0, 
                                int silver_damage = 0);
    bool spend_stamina(int stamina_spent);

    ...
   

    //void update_global_level();
    
    const Entity &operator=(const Entity &);
    int operator==(const Entity &) const;
    int operator!=(const Entity &) const;
    bool operator!() const;
protected:
    string name;
    int age;
    double coins;
    int max_health;
    int health;
    int max_stamina;
    int stamina;
    string category;
    int level;
    int next_level_xp;
    int xp;
    bool is_stunned = false;

    inventory_items inventory;

    int physical_weakness;
    int fire_weakness;
    int poison_weakness;
    int ice_weakness;
    int silver_weakness;

    int total_physical_resistance;
    int total_fire_resistance;
    int total_poison_resistance;
    int total_ice_resistance;
    int total_silver_resistance;

    const static string CATEGORIES[7];
    const static int MAX_NAME_SIZE = 20;
    Date date_of_birth;

    const static int NEXT_LEVEL_XP_LINEAR_COEF = 10;
    const static int NEXT_LEVEL_XP_ANGULAR_COEF = 10;
private:
    //static int global_danger;
};

...



     ////Classe base 2


class Item {
public:
    Item();
    Item(string name, string description);
    Item(const Item &other_Item);
    ~Item();
    
    
    ...
   

    virtual map<string, int> use(int technique) = 0;
    
    const Item &operator=(const Item &);
    int operator==(const Item &other_Item) const;
    int operator!=(const Item &other_Item) const;
protected:
    string name;
    string description;
private:
    const static int MAX_NAME_SIZE = 20;
    const static int MAX_DESCRIPTION_SIZE = 100;
};


     ////Classe base 3

//>>>Comentário: não retornar maps, a não ser por const ref

class Spell {
public:
    Spell();
    Spell(const Spell &other_spell);
    ~Spell();
    
    ...
    virtual map<string, int> cast(int technique) = 0;
    
    const Spell &operator=(const Spell &);
    int operator==(const Spell &other_spell) const;
    int operator!=(const Spell &other_spell) const;
protected:
    string name;
    string description;
    bool is_unlocked;
private:
    const static int MAX_NAME_SIZE = 20;
    const static int MAX_DESCRIPTION_SIZE = 100;
};




//// O .h da hierarquia 1

     ////Classe 1

struct equipped_items {
    Sword* steel_sword; 
    Armor* armor;
};

class Human: public Entity {
    friend ostream &operator<< (ostream &out, const Human &human);
public:
    Human();
    Human(string name,
        int age=30, 
        double coins=100, 
        int level = 10,
        string category="E");
    Human(const Human &other_human);
    ~Human();

    virtual void equip_item(int item_type, int item_index);
    virtual void unequip_item(int item_type);
    ...

    virtual void level_up();
    virtual void update_atributes();
    virtual void update_all_resistances();
    virtual void update_all_weaknesses();
    
    virtual void attack(Entity &entity, int weapon_type = UNARMED);
    virtual void receive_damage(int physical_damage, 
                                int fire_damage = 0, 
                                int poison_damage = 0, 
                                int ice_damage = 0, 
                                int silver_damage = 0);

    const Human &operator=(const Human &);
    bool operator==(const Human &other_human) const;
    bool operator!=(const Human &other_human) const;
protected:
    equipped_items equipped;
private:
    const static int HEALTH_LINEAR_COEF = 5;
    const static int HEALTH_ANGULAR_COEF = 3;

    const static int STAMINA_LINEAR_COEF = 5;
    const static int STAMINA_ANGULAR_COEF = 3;
};


     ////Classe 2

class Ghoul: public Entity {
    friend ostream &operator<<(ostream &out, const Ghoul &ghoul);
public:
    Ghoul();
    Ghoul(string name, 
        int age=200, 
        double coins=30, 
        int level = 10,
        string category="E");
    Ghoul(const Ghoul &other_ghoul): Entity(other_ghoul) { };
    ~Ghoul();

...    
    void level_up();
    void update_atributes();
    void update_all_resistances();
    void update_all_weaknesses();

    void attack(Entity &entity, int weapon_type = UNARMED);
    void receive_damage(int physical_damage, 
                        int fire_damage, 
                        int poison_damage, 
                        int ice_damage, 
                        int silver_damage);
    
    ...
    const Ghoul &operator=(const Ghoul &);
    int operator==(const Ghoul &) const;
    int operator!=(const Ghoul &) const;
    bool operator!() const;
private:
    const static int HEALTH_LINEAR_COEF = 5;
    const static int HEALTH_ANGULAR_COEF = 2;

    const static int STAMINA_LINEAR_COEF = 5;
    const static int STAMINA_ANGULAR_COEF = 2;

    bool is_enraged = false;

    int silver_weakness = 1;

    const static int GHOUL_ATTACK_COST = 10;
    const static int MAX_GHOUL_DAMAGE = 7;
    const static int MIN_GHOUL_DAMAGE = 3;
};


     ///Classe 3

struct Signs {
    Igni * igni;
};

class Witcher: public Human {
    friend ostream &operator<< (ostream &out, const Witcher &witcher);
public:
    Witcher();
    Witcher(string name,
        int age=200,
        double coins=200, 
        int level = 10,
        string category="E");
    Witcher(const Witcher &other_witcher);
    ~Witcher();

   ...

    void load_inventory(string file_name_swords="./save-files/config-witcher/config_swords.txt", 
                        string file_name_armors="./save-files/config-witcher/config_armors.txt");
    void save_inventory(string file_name_swords="./save-files//config-witcher/config_swords.txt", 
                        string file_name_armors="./save-files/config-witcher/config_armors.txt");

    void store_item(int item_type, int item_index);
    void unstore_item(string item_name);
    ...

    void update_atributes();

    // simply attack one entity
    void attack(Entity &entity, int weapon_type = UNARMED);
    // attacks one or more entities
    /*
    void attack(vector<Entity*> &entities, 
                int entity_index = 0, 
                int weapon_type = UNARMED, 
                int attack_type = 0);
    */

    const Witcher &operator=(const Witcher &);
    bool operator==(const Witcher &other_witcher) const;
    bool operator!=(const Witcher &other_witcher) const;
private:
    const static int HEALTH_LINEAR_COEF = 10;
    const static int HEALTH_ANGULAR_COEF = 5;
    
    const static int STAMINA_LINEAR_COEF = 10;
    const static int STAMINA_ANGULAR_COEF = 5;

    Signs signs;

    bool is_close_to_chest;
    map<string, Item*> personal_chest;

    const static int WITCHER_ATTACK_COST = 10;
    const static int MAX_WITCHER_DAMAGE = 10;
    const static int MIN_WITCHER_DAMAGE = 7;
    //static int player_level;
};

#endif // WITCHER_H

     ///E assim por diante

//// O .h da hierarquia 2

     ////Classe 1


class Armor : public Item{
    friend ostream &operator<< (ostream &out, const Armor &armor);
public:
    Armor();
    Armor(string name, string description, int physical_defense, 
                                           int fire_defense = 0, 
                                           int poison_defense = 0, 
                                           int ice_defense = 0, 
                                           int silver_defense = 0);
    Armor(const Armor &other_armor);
    ~Armor();
    
    ...

    virtual map<string, int> use(int technique = 0);

    const Armor &operator=(const Armor &);
    int operator==(const Armor &other_armor) const;
    int operator!=(const Armor &other_armor) const;
private:
    int physical_defense = 0;
    int fire_defense = 0;
    int poison_defense = 0;
    int ice_defense = 0;
    int silver_defense = 0;

};



     ////Classe 2
     //>>>Comentário:  Por que Weapon não tem o operator <<

class Weapon : public Item {
public:
    Weapon();
    Weapon(const Weapon &other_Weapon);
    ~Weapon();
    
    ...

    virtual map<string, int> use(int technique) = 0;

    const Weapon &operator=(const Weapon &);
    int operator==(const Weapon &other_Weapon) const;
    int operator!=(const Weapon &other_Weapon) const;
protected:
    int physical_damage;
    int fire_damage;
    int poison_damage;
    int ice_damage;
    int silver_damage;
};


     ///Classe 3

enum technique {
    FAST_ATTACK = 1,
    STRONG_ATTACK = 2,
    GROUP_ATTACK = 3
};

class Sword : public Weapon {
    friend ostream &operator<< (ostream &out, const Sword &sword);
public:
    Sword();
    Sword(string name, string description, int physical_damage, 
                                           int fire_damage = 0, 
                                           int poison_damage = 0, 
                                           int ice_damage = 0, 
                                           int silver_damage = 0);
    Sword(const Sword &other_sword);
    ~Sword();
 
    virtual map<string, int> use(int technique = FAST_ATTACK);

    const Sword &operator=(const Sword &);
    int operator==(const Sword &other_sword) const;
    int operator!=(const Sword &other_sword) const;
};



     ///E assim por diante

//// O .h da hierarquia 3

     ////Classe 1


class Sign : public Spell{
public:
    Sign();
    Sign(const Sign &other_sign);
    ~Sign();

...

    virtual map<string, int> cast(int technique) = 0;

    const Sign &operator=(const Sign &);
    int operator==(const Sign &other_sign) const;
    int operator!=(const Sign &other_sign) const;
protected:
    int stamina_cost;
};



     ////Classe 2


class Igni : public Sign{
    friend ostream &operator<<(ostream &out, const Igni &igni);
public:
    Igni();
    Igni(string name, 
         string description, 
         bool is_unlocked, 
         int stamina_cost, 
         int fire_damage, 
         int area);
    Igni(const Igni &other_Igni);
    ~Igni();

    ...

    virtual map<string, int> cast(int technique = 0);

    const Igni &operator=(const Igni &);
    int operator==(const Igni &other_Igni) const;
    int operator!=(const Igni &other_Igni) const;
private:
    int fire_damage;
    int area;
};

#endif // IGNI_H
     ///E assim por diante


//// Mostrar implementação de método que especializa a derivada
 /// Mostrar reaproveitamente de código da base

    //// Hierarquia 1

         ////Classe 1
         // O Humano reaproveita os atributos
// protected:
    // relacionados a identidade
    string name;
    int age;
    double coins;
    // vida e estamina
    int max_health;
    int health;
    int max_stamina;
    int stamina;
    // relacionados ao nivel
    string category;
    int level;
    int next_level_xp;
    int xp;
    // status temporario
    bool is_stunned = false;
    // capacidade de possuir um inventario de outras classes
    // descendentes de "item"
    inventory_items inventory;
    struct inventory_items {
    vector<Sword*> swords;
    vector<Armor*> armors;
    };
    // fraquezas
    int physical_weakness;
    int fire_weakness;
    int poison_weakness;
    int ice_weakness;
    int silver_weakness;
    // resistencias
    int total_physical_resistance;
    int total_fire_resistance;
    int total_poison_resistance;
    int total_ice_resistance;
    int total_silver_resistance;
    // e algumas variaveis estaticas que sao comuns a todas as classes
    const static string CATEGORIES[7];
    const static int MAX_NAME_SIZE = 20;
    Date date_of_birth;

    const static int NEXT_LEVEL_XP_LINEAR_COEF = 10;
    const static int NEXT_LEVEL_XP_ANGULAR_COEF = 10;

    // bem como metodos para:
    // regenerar vida e estamina e ganhar xp para subir de nivel
    void life_regen(int);
    void stamina_regen(int);
    void gain_xp(int);

    // metodos para adicionar e remover itens do inventario
    // add an item and deletes it
    void add_item(Item &);
    // just deletes an inventory item
    void remove_item(int item_type, int item_index);

    // add an item from a source and deletes it
    void grab_item(vector<Item*> &source_items, int item_index = 0);
    // remove an item and put it somewhere
    void drop_item(vector<Item*> &destiny_items, int item_type, int item_index);

    // e metodo para receber dano
    void receive_damage(int physical_damage, 
                        int fire_damage = 0, 
                        int poison_damage = 0, 
                        int ice_damage = 0, 
                        int silver_damage = 0);
    // e o ser humano se especializa na capacidade de equipar 
    // itens do inventario
    //protected:
    equipped_items equipped;

    struct equipped_items {
        Sword* steel_sword; 
        Armor* armor;
    };
    // metodos que usam o item ao equipar e removem o bonus ao desequipar
    void Human::equip_item(int item_type, int item_index) {
    if (item_type == SWORD) {
        if (item_index < 0 || item_index >= inventory.swords.size()) {
            cout << "Invalid sword index.\n";
            return;
        }
        if (equipped.steel_sword != 0) {
            cout << "Unequipped " << *equipped.steel_sword << ".\n";
            unequip_item(item_type);
        }
        equipped.steel_sword = new Sword(*inventory.swords[item_index]);
        cout << "Equipped " << *equipped.steel_sword << ".\n";
        delete inventory.swords[item_index];
        inventory.swords.erase(inventory.swords.begin() + item_index);
    }
    else if (item_type == ARMOR) {
        if (item_index < 0 || item_index >= inventory.armors.size()) {
            cout << "Invalid armor index.\n";
            return;
        }
        if (equipped.armor != 0) {
            cout << "Unequipped " << *equipped.armor << ".\n";
            unequip_item(item_type);
        }
        equipped.armor = new Armor(*inventory.armors[item_index]);
        cout << "Equipped " << *equipped.armor << ".\n";
        delete inventory.armors[item_index];
        inventory.armors.erase(inventory.armors.begin() + item_index);
        update_all_resistances();
    }
    else {
        cout << "Item type not recognized.\n";
    }
}

void Human::unequip_item(int item_type) {
    if (item_type == SWORD) {
        if (equipped.steel_sword == 0) {
            cout << "No sword equipped.\n";
            return;
        }
        add_item(*equipped.steel_sword);
        equipped.steel_sword = 0;
    }
    else if (item_type == ARMOR) {
        if (equipped.armor == 0) {
            cout << "No armor equipped.\n";
            return;
        }
        add_item(*equipped.armor);
        equipped.armor = 0;
        update_all_resistances();
    }
    else {
        cout << "Item type not recognized.\n";
    }
}
    // tambem possui sua forma de aumentar seus atributos baseado
    // em coeficientes globais para uma equação linear em função do level
    //private:
    const static int HEALTH_LINEAR_COEF = 5;
    const static int HEALTH_ANGULAR_COEF = 3;

    const static int STAMINA_LINEAR_COEF = 5;
    const static int STAMINA_ANGULAR_COEF = 3;

void Human::level_up() {
    level++;
    
    update_atributes();

    life_regen(max_health);
    stamina_regen(max_stamina);

    }

void Human::update_atributes() {
    next_level_xp = NEXT_LEVEL_XP_LINEAR_COEF + NEXT_LEVEL_XP_ANGULAR_COEF * level;
    max_health = HEALTH_LINEAR_COEF + HEALTH_ANGULAR_COEF * level;
    max_stamina = STAMINA_LINEAR_COEF + STAMINA_ANGULAR_COEF * level;
}

         ////Classe 2
        // O Ghoul reaproveita os mesmos atributos e metodos de entity
        // que o humano, pois são descendentes diretos de entity
        // e o ghoul se especializa em seu:
        // attack, que é puramente virtual em entity,
    void Ghoul::attack(Entity &entity, int weapon_type) {
    if (!spend_stamina(GHOUL_ATTACK_COST)) {
        return;
    }
    cout << name << " attacked " << entity.getName() << ".\n";
    // Dano aleatorio entre MIN_GHOUL_DAMAGE e MAX_GHOUL_DAMAGE
    srand(static_cast<unsigned int>(time(nullptr)));
    int damage = MIN_GHOUL_DAMAGE + rand() % (MAX_GHOUL_DAMAGE - MIN_GHOUL_DAMAGE + 1);
    // depois de gerar o dano aleatorio adiciona o level do Ghoul

    damage = damage + getLevel();
    entity.receive_damage(damage);

    return;
}
        // e receive_damage no qual pode se enfurecer caso chegue em 10% de vida
        // ganhando um bonus de defesa
    void Ghoul::receive_damage(int physical_damage, int fire_damage, int poison_damage, int ice_damage, int silver_damage) {
    Entity::receive_damage(physical_damage, fire_damage, poison_damage, ice_damage, silver_damage);
    if (getHealth() < getMax_health() * 0.1) {
        if (!is_enraged) {
            setIs_enraged(true);
        }
    }
    return;
}
        // Classe 3
        // O Witcher deriva de Human, todos os seus atributos protected
        // e se especializa em:
        // possuir um bau pessoal de itens
        map<string, Item*> personal_chest;
        // que só pode acessar ao estar perto dele
        bool is_close_to_chest;
        // podendo guardar itens
        void Witcher::store_item(int item_type, int item_index) {
    if (!is_close_to_chest) {
        cout << "You are not close to the personal chest.\n";
        return;
    }
    // Checks if item_type is valid for existing items
    if (item_type < 0 || item_type > 1) {
        cout << "Item type not found.\n";
        return;
    }
    // Checks if item_index is valid for corresponding inventory section
    if (item_type == SWORD) {
        if (item_index < 0 || item_index >= inventory.swords.size() ) {
            cout << "Item not found.\n";
            return;
        }
        personal_chest[this->inventory.swords[item_index]->getName()] = this->inventory.swords[item_index];
    }
    else if (item_type == ARMOR) {
        if (item_index < 0 || item_index >= inventory.armors.size() ) {
            cout << "Item not found.\n";
            return;
        }
        personal_chest[this->inventory.armors[item_index]->getName()] = this->inventory.armors[item_index];
    }
    else {
        cout << "Item not found.\n";
        return;
    }
}
        // e retirar itens
        void Witcher::unstore_item(string item_name) {
    if (!is_close_to_chest) {
        cout << "You are not close to the personal chest.\n";
        return;
    }
    if (personal_chest.find(item_name) == personal_chest.end()) {
        cout << "Item not found.\n";
        return;
    }
    if (Sword * sword = dynamic_cast<Sword *>(personal_chest[item_name])) {
        this->inventory.swords.push_back(sword);
        delete sword;
    }
    else if (Armor * armor = dynamic_cast<Armor *>(personal_chest[item_name])) {
        this->inventory.armors.push_back(armor);
        delete armor;
    }
    else {
        cout << "Item not deleted.\n";
    }
    personal_chest.erase(item_name);
}

void Witcher::print_personal_chest() const {
    for (auto const& x : personal_chest)
    {
        cout << x.first << ':'; // string (key)
        x.second->print_info(); // string's value 
        cout << "\n";
    }
}
        // tambem evolui atributos baseado em equação linear
        // em função do nivel
    //private:
    const static int HEALTH_LINEAR_COEF = 10;
    const static int HEALTH_ANGULAR_COEF = 5;
    
    const static int STAMINA_LINEAR_COEF = 10;
    const static int STAMINA_ANGULAR_COEF = 5;

void Witcher::update_atributes() {
    max_health = HEALTH_LINEAR_COEF + HEALTH_ANGULAR_COEF * level;
    max_stamina = STAMINA_LINEAR_COEF + STAMINA_ANGULAR_COEF * level;
}

        // possui metodo de salvar e carregar seu inventario

void Witcher::save_inventory(string name_file_swords, string name_file_armors) {
    // First creates a buffer map to store the atributes of each item
    map<string, string> items_atributes_buffer;
    // First save the swords
    ofstream output_file(name_file_swords);
    if (!output_file.is_open()) {
        cerr << "Error opening file." << '\n';
        return; // Exit with an error code
    }

    for (auto sword : this->inventory.swords) {
        items_atributes_buffer["name"] = sword->getName();
        items_atributes_buffer["description"] = sword->getDescription();
        items_atributes_buffer["physical_damage"] = to_string(sword->getPhysical_damage());
        items_atributes_buffer["fire_damage"] = to_string(sword->getFire_damage());
        items_atributes_buffer["poison_damage"] = to_string(sword->getPoison_damage());
        items_atributes_buffer["ice_damage"] = to_string(sword->getIce_damage());
        items_atributes_buffer["silver_damage"] = to_string(sword->getSilver_damage());
        // Convert string spaces from string atributes to underscores
        // so that the file can be read again
        for (auto &x : items_atributes_buffer) {
            replace(x.second.begin(), x.second.end(), ' ', '_');
        }
        // Stores values in buffer iteratively
        for (auto const& x : items_atributes_buffer) {
            output_file << x.first << " = " << x.second << '\n';
        }
        // Stores next item separator
        output_file << "next = item\n";
        items_atributes_buffer.clear();
    }
    // Closes swords file
    output_file.close();

    // Then save the armors
    // Reuse same ofstream variable
    output_file.open(name_file_armors);
        if (!output_file.is_open()) {
        cerr << "Error opening file." << '\n';
        return; // Exit with an error code
    }

    for (auto armor : this->inventory.armors) {
        items_atributes_buffer["name"] = armor->getName();
        items_atributes_buffer["description"] = armor->getDescription();
        items_atributes_buffer["physical_defense"] = to_string(armor->getPhysical_defense());
        items_atributes_buffer["fire_defense"] = to_string(armor->getFire_defense());
        items_atributes_buffer["poison_defense"] = to_string(armor->getPoison_defense());
        items_atributes_buffer["ice_defense"] = to_string(armor->getIce_defense());
        items_atributes_buffer["silver_defense"] = to_string(armor->getSilver_defense());
        // Convert string spaces from string atributes to underscores
        // so that the file can be read again
        for (auto &x : items_atributes_buffer) {
            replace(x.second.begin(), x.second.end(), ' ', '_');
        }
        // Stores values in buffer iteratively
        for (auto const& x : items_atributes_buffer) {
            output_file << x.first << " = " << x.second << '\n';
        }
        // Stores next item separator
        output_file << "next = item\n";
        items_atributes_buffer.clear();
    }

    // Closes armors file
    output_file.close();
}

void Witcher::load_inventory(string name_file_swords, string name_file_armors) {

    // First creates a buffer map to store the atributes of each item
    map<string, string> items_atributes_buffer;
    // First load the swords
    ifstream input_file(name_file_swords);
    if (!input_file.is_open()) {
        cerr << "Error opening  " << name_file_swords << " file." << '\n';
        return; // Exit with an error code
    }
    // Unpacking variables
    string line;
    string atribute_name;
    char equal_sign;
    string value;

    while (getline(input_file, line)) {
        istringstream line_stream(line);
        line_stream >> atribute_name >> equal_sign >> value;
        // Skips to next sword and stores the previous one
        // reusing the same buffer for all swords
        if (atribute_name == "next" && equal_sign == '=' && value == "item") {
            // Converts underscores from string atributes to spaces
            // so that the string turns back to original form
            for (auto &x : items_atributes_buffer) {
                replace(x.second.begin(), x.second.end(), '_', ' ');
            }
            // Creates a temporary sword and adds it to the inventory
            Sword * new_sword = new Sword(items_atributes_buffer["name"], 
                                    items_atributes_buffer["description"], 
                                    stoi(items_atributes_buffer["physical_damage"]),
                                    stoi(items_atributes_buffer["fire_damage"]),
                                    stoi(items_atributes_buffer["poison_damage"]),
                                    stoi(items_atributes_buffer["ice_damage"]),
                                    stoi(items_atributes_buffer["silver_damage"]));
            // add_item already cleans "new_sword" buffer
            add_item(*new_sword);
            // Cleans buffer variable
            items_atributes_buffer.clear();
        }
        // Stores values in buffer iteratively
        items_atributes_buffer[atribute_name] = value;
    }
    // Closes swords file
    input_file.close();

    // Then load the armors
    // Reuse same ifstream variable
    input_file.open(name_file_armors);
        if (!input_file.is_open()) {
        cerr << "Error opening " << name_file_armors << " file." << '\n';
        return; // Exit with an error code
    }

    while (getline(input_file, line)) {
        istringstream line_stream(line);
        // Reuses same unpacking variables
        line_stream >> atribute_name >> equal_sign >> value;
        // Skips to next armor and stores the previous one
        // reusing the same buffer for all armors
        if (atribute_name == "next" && equal_sign == '=' && value == "item") {
            // Converts underscores from string atributes to spaces
            // so that the string turns back to original form
            for (auto &x : items_atributes_buffer) {
                replace(x.second.begin(), x.second.end(), '_', ' ');
            }
            // Creates a temporary armor and adds it to the inventory
            Armor * new_armor = new Armor(items_atributes_buffer["name"], 
                                    items_atributes_buffer["description"], 
                                    stoi(items_atributes_buffer["physical_defense"]), 
                                    stoi(items_atributes_buffer["fire_defense"]),
                                    stoi(items_atributes_buffer["poison_defense"]),
                                    stoi(items_atributes_buffer["ice_defense"]),
                                    stoi(items_atributes_buffer["silver_defense"]));
            // add_item already cleans "new_armor" buffer
            add_item(*new_armor);
            // Cleans buffer variable
            items_atributes_buffer.clear();
        }
        // Stores values in buffer iteratively
        // Reuses same map
        items_atributes_buffer[atribute_name] = value;
    }
    // Closes armors file
    input_file.close();

    return;
}
        // tambem se especializa no seu ataque possuindo diversas
        // formas de atacar

void Witcher::attack(Entity &entity, int weapon_type) {

    cout << name << " attacked " << entity.getName() << ".\n";

    // testing stunned inside attack, must be removed later
    if (is_stunned) {
        cout << name << " is stunned and can't attack.\n";
        is_stunned = false;
        return;
    }

    // prepare damage buffer variables to update each damage type
    // and stamina spent acording to what is choosed to attack
    int total_physical_damage = 0;
    int total_fire_damage = 0;
    int total_poison_damage = 0;
    int total_ice_damage = 0;
    int total_silver_damage = 0;

    int stamina_spent = 0;

    map<string, int> sword_info_buffer;
    map<string, int> sign_info_buffer;

    // Random unarmed base damage MIN_WITCHER_DAMAGE and MAX_WITCHER_DAMAGE
    srand(static_cast<unsigned int>(time(nullptr)));
    int bonus_witcher_damage = MIN_WITCHER_DAMAGE + rand() % (MAX_WITCHER_DAMAGE - MIN_WITCHER_DAMAGE + 1);
    // cout << "bonus_witcher_damage: " << bonus_witcher_damage << "\n";

    // First checks if the witcher is unarmed
    switch (weapon_type)
    {
    case STEEL_SWORD:
        if (equipped.steel_sword == 0) {
            weapon_type = UNARMED;
        }
        break;
    case IGNI:
        if (signs.igni == 0) {
            weapon_type = UNARMED;
        }
        if (signs.igni->getIs_unlocked() == false) {
            weapon_type = UNARMED;
        }
        break;
    default:
        // If weapon_type is invalid, witcher is unarmed
        weapon_type = UNARMED;
        break;
    }

    // Then puts each damage type to damage buffer variables
    // according to the respective weapon choosed
    switch (weapon_type)
    {
    case UNARMED:
        // Always check stamina first
        if (!spend_stamina(WITCHER_ATTACK_COST)) {
            return;
        }

        cout << name << " is attacking " << entity.getName() << " with his fists.\n";

        total_physical_damage += bonus_witcher_damage;

        break;
    case STEEL_SWORD:
        // uses sword to calculate stamina and damage
        sword_info_buffer = equipped.steel_sword->use();
        
        // Always check stamina first
        if (!spend_stamina(sword_info_buffer["stamina_cost"])) {
            return;
        }
        
        // base damage
        total_physical_damage += bonus_witcher_damage;

        // item damage
        total_physical_damage += sword_info_buffer["physical_damage"];
        // cout << "total_physical_damage: " << sword_info_buffer["physical_damage"] << "\n";

        total_fire_damage += sword_info_buffer["fire_damage"];
        // cout << "total_fire_damage: " << sword_info_buffer["fire_damage"] << "\n";

        total_poison_damage += sword_info_buffer["poison_damage"];
        // cout << "total_poison_damage: " << sword_info_buffer["poison_damage"] << "\n";

        total_ice_damage += sword_info_buffer["ice_damage"];
        // cout << "total_ice_damage: " << sword_info_buffer["ice_damage"] << "\n";

        total_silver_damage += sword_info_buffer["silver_damage"];
        // cout << "total_silver_damage: " << sword_info_buffer["silver_damage"] << "\n";

        break;
    case IGNI:
        cout << "Witcher is casting igni.\n";
        
        // uses igni to calculate stamina and damage
        sign_info_buffer = signs.igni->cast();
        
        // Always check stamina first
        if (!spend_stamina(sign_info_buffer["stamina_cost"])) {
            return;
        }
        
        // sign damage
        total_fire_damage += sign_info_buffer["fire_damage"];
        // cout << "total_fire_damage: " << igni_info_buffer["fire_damage"] << "\n";
        
        break;
    
    
    
    }

    // After calculating all damage especifically
    // sends it to attacked entity

    entity.receive_damage(total_physical_damage, total_fire_damage, total_poison_damage, total_ice_damage, total_silver_damage);

    return;
}

         ///E assim por diante

    //// Hierarquia 2

         ////Classe 1
        // a classe weapon tambem é abstrata e herda de item as propriedades
        // de possuir nome e descrição
    //protected:
    string name;
    string description;
    // e se especializa em possuir multiplos tipos de dano, pois
    // isso é caracteristico de armas
    //protected:
    int physical_damage;
    int fire_damage;
    int poison_damage;
    int ice_damage;
    int silver_damage;

         ////Classe 2
        // a classe armor herda de item as mesmas caracteristicas que weapon
        // pois descendem diretamente de item
        // e armor se especializa em possuir multiplos tipos de defesa,
        // pois isso é caracteristico desse tipo de item
    // private:
    int physical_defense = 0;
    int fire_defense = 0;
    int poison_defense = 0;
    int ice_defense = 0;
    int silver_defense = 0;

    // e ao ativar seu metodo use() retorna um map com os valores
    // de defesa que serão adicionados ao usuario da armadura
    map<string, int> Armor::use(int technique) {
    // cout << "Using Armor...\n";
    map<string, int> defenses;

    defenses["physical_defense"] = physical_defense;
    defenses["fire_defense"] = fire_defense;
    defenses["poison_defense"] = poison_defense;
    defenses["ice_defense"] = ice_defense;
    defenses["silver_defense"] = silver_defense;
    
    return defenses;
}
        // Classe 3 
        // a classe sword herda de weapon a capacidade de posuir danos
        // e se especializa em possuir um metodo use() que receber como parametro
        // um determinado tipo de tecnica para aumentar o dano de um determinado
        // usuario
        map<string, int> Sword::use(int technique) {
    // cout << "Using Sword...\n";
    // cout << "Technique: " << technique << "\n";

    map<string, int> info_buffer;
    info_buffer["physical_damage"] = physical_damage;
    info_buffer["fire_damage"] = fire_damage;
    info_buffer["poison_damage"] = poison_damage;
    info_buffer["ice_damage"] = ice_damage;
    info_buffer["silver_damage"] = silver_damage;
    info_buffer["stamina_cost"] = 0;
    info_buffer["area"] = 1;

    switch (technique) {
        case FAST_ATTACK:
            cout << "Fast attack\n";
            info_buffer["stamina_cost"] += 4;
            info_buffer["physical_damage"] -= 1;
            break;
        case STRONG_ATTACK:
            cout << "Strong attack\n";
            info_buffer["stamina_cost"] += 8;
            info_buffer["physical_damage"] += 2;
            break;
        case GROUP_ATTACK:
            cout << "Group attack\n";
            info_buffer["stamina_cost"] += 12;
            info_buffer["physical_damage"] -= 2;
            info_buffer["area"] = 3;
            break;
        default:
            cout << "Invalid attack\n";
            break;
    }

    return info_buffer;
}

         ///E assim por diante


    //// Hierarquia 3

         ////Classe 1
        // a classe sign herda de spell as propriedades de possuir nome,
        // descrição e se estar desbloqueada ou não, para usuários q chegaram
        // a um determinado nivel de conhecimento
    //protected:
    string name;
    string description;
    bool is_unlocked;
        // e se especializa em possuir um custo de estamina para ser ativada
        // pois essa classe de feitiços é considerada simples e não usa um 
        // atributo místico como mana
    // protected:
    int stamina_cost;
        // a partir disso, ela da origem a diversos sinais de propriedades
        // completamente diferentes

         ////Classe 2
        // a classe igni herda de sign as mesmas propriedades
        // e se especializa em possuir um dano de fogo e uma area de efeito
    //private:
    int fire_damage;
    int area;
        // e um metodo para conceder esse dano ao usuario
        map<string, int> Igni::cast(int technique) {

    map<string, int> sign_info;

    sign_info["is_unlocked"] = is_unlocked;
    sign_info["fire_damage"] = fire_damage;
    sign_info["area"] = area;
    sign_info["stamina_cost"] = stamina_cost;

    return sign_info;
}
         ///E assim por diante



//// Fazer a sobrecarga para todas as classes dos operadores =, ==, ≠ e << (friend)

     //// Operator=
         //// Base 1
         const Entity &Entity::operator=(const Entity &assigned_entity) {
    if (this != &assigned_entity) {
        this->name = assigned_entity.name;
        this->age = assigned_entity.age;
        this->coins = assigned_entity.coins;

        this->max_health = assigned_entity.max_health;
        this->health = assigned_entity.health;
        this->max_stamina = assigned_entity.max_stamina;
        this->stamina = assigned_entity.stamina;

        this->category = assigned_entity.category;
        this->level = assigned_entity.level;
        this->next_level_xp = assigned_entity.next_level_xp;
        this->xp = assigned_entity.xp;

        this->is_stunned = assigned_entity.is_stunned;

        this->physical_weakness = assigned_entity.physical_weakness;
        this->fire_weakness = assigned_entity.fire_weakness;
        this->poison_weakness = assigned_entity.poison_weakness;
        this->ice_weakness = assigned_entity.ice_weakness;
        this->silver_weakness = assigned_entity.silver_weakness;

        this->total_physical_resistance = assigned_entity.total_physical_resistance;
        this->total_fire_resistance = assigned_entity.total_fire_resistance;
        this->total_poison_resistance = assigned_entity.total_poison_resistance;
        this->total_ice_resistance = assigned_entity.total_ice_resistance;
        this->total_silver_resistance = assigned_entity.total_silver_resistance;

        // primeiro limpa o vetor para preenche-lo
        for (auto sword : this->inventory.swords) {
            delete sword;
        }
        this->inventory.swords.clear();
        for (auto sword : assigned_entity.inventory.swords) {
            Sword * new_sword = new Sword(*sword);
            this->inventory.swords.push_back(new_sword);
        }
        for (auto armor : this->inventory.armors) {
            delete armor;
        }
        this->inventory.armors.clear();
        for (auto armor : assigned_entity.inventory.armors) {
            Armor * new_armor = new Armor(*armor);
            this->inventory.armors.push_back(new_armor);
        }
    }

    return *this; // permite a forma a = b = c

             ////Derivadas da Base 1 - mostrar uso static_cast
             // Ghoul
             // não pode usar static_cast pois é filho de uma classe abstrata
    //const Ghoul &Ghoul::operator=(const Ghoul &other_ghoul) {
    if (this == &other_ghoul) {
        return *this;
    }
    Entity::operator=(other_ghoul);
    this->is_enraged = other_ghoul.is_enraged;
    
    return *this;
}
            // Human
    //const Human &Human::operator=(const Human &other_human) {
    if (this != &other_human) {
        // forma não permitida pela classe abstrata
        //*static_cast< Entity * >( this ) = static_cast< Entity >( other_human );
        // forma sugerida pela IA
        Entity::operator=(other_human);
        if (other_human.equipped.steel_sword == 0) equipped.steel_sword = 0;
        else {
            delete equipped.steel_sword;
            equipped.steel_sword = new Sword(*other_human.equipped.steel_sword);
        }

        if (other_human.equipped.armor == 0) equipped.armor = 0;
        else {
            delete equipped.armor;
            equipped.armor = new Armor(*other_human.equipped.armor);
        }
    }
    return *this;


            // Witcher
    const Witcher &Witcher::operator=(const Witcher &other_witcher) {
    if (this != &other_witcher) {
        *static_cast< Human * >( this ) = static_cast< Human >( other_witcher );
        delete this->signs.igni;
        this->signs.igni = other_witcher.signs.igni;
        this->is_close_to_chest = other_witcher.is_close_to_chest;
    }
    return *this;
}

         //// Base 2
         // Item
    const Item &Item::operator=(const Item &other_Item) {
    this->name = other_Item.name;
    this->description = other_Item.description;
    return *this;
}
             ////Derivadas da Base 2 - mostrar uso static_cast
            // Armor
    const Armor &Armor::operator=(const Armor &other_Armor) {
    // forma não permitida pela classe abstrata Item
    //static_cast<Item &>(*this) = static_cast<const Item &>(other_Armor);
    Item::operator=(other_Armor);
    this->physical_defense = other_Armor.physical_defense;
    this->fire_defense = other_Armor.fire_defense;
    this->poison_defense = other_Armor.poison_defense;
    this->ice_defense = other_Armor.ice_defense;
    this->silver_defense = other_Armor.silver_defense;

    return *this;
}
        // Weapon
    const Weapon &Weapon::operator=(const Weapon &other_weapon) {
    // Item is abstract, so we can't do this:
    //static_cast<Item>(*this) = static_cast<Item>(other_weapon);
    // So we do this:
    Item::operator=(other_weapon);

    this->physical_damage = other_weapon.physical_damage;
    this->fire_damage = other_weapon.fire_damage;
    this->poison_damage = other_weapon.poison_damage;
    this->ice_damage = other_weapon.ice_damage;
    this->silver_damage = other_weapon.silver_damage;

    return *this;
}

        // Sword
    const Sword &Sword::operator=(const Sword &other_sword) {
    // Weapon is abstract, so we can't do this:
    //static_cast<Weapon>(*this) = static_cast<Weapon>(other_sword);
    // So we do this:
    Weapon::operator=(other_sword);
    made_of_silver = other_sword.made_of_silver;

    return *this;
}

        //// Base 3
        // Spell
    const Spell &Spell::operator=(const Spell &other_spell) {
    this->name = other_spell.name;
    this->description = other_spell.description;
    return *this;
}
             ////Derivadas da Base 3 - mostrar uso static_cast
        // Sign
    const Sign &Sign::operator=(const Sign &other_sign) {
    if (this != &other_sign) {
        // forma não permitida pela classe abstrata Spell
        //static_cast<Spell &>(*this) = static_cast<const Spell &>(other_sign);
        Spell::operator=(other_sign);
        this->is_unlocked = other_sign.is_unlocked;
        this->stamina_cost = other_sign.stamina_cost;
    }
    return *this;
}
        // Igni
    const Igni &Igni::operator=(const Igni &other_igni) {
    if (this != &other_igni) {
        // forma não permitida pela classe abstrata Sign
        //static_cast<Sign &>(*this) = static_cast<const Sign &>(other_igni);
        Sign::operator=(other_igni);
        this->fire_damage = other_igni.fire_damage;
        this->area = other_igni.area;
    }
    return *this;
}

     //// Operators== e !=
         //// Base 1
    int Entity::operator==(const Entity &other_entity) const {
    // atributes check
    if (this->name != other_entity.name) return 0;
    if (this->age != other_entity.age) return 0;
    if (this->coins != other_entity.coins) return 0;

    if (this->max_health != other_entity.max_health) return 0;
    if (this->health != other_entity.health) return 0;
    if (this->max_stamina != other_entity.max_stamina) return 0;
    if (this->stamina != other_entity.stamina) return 0;

    if (this->category != other_entity.category) return 0;
    if (this->level != other_entity.level) return 0;
    if (this->next_level_xp != other_entity.next_level_xp) return 0;
    if (this->xp != other_entity.xp) return 0;

    if (this->physical_weakness != other_entity.physical_weakness) return 0;
    if (this->fire_weakness != other_entity.fire_weakness) return 0;
    if (this->poison_weakness != other_entity.poison_weakness) return 0;
    if (this->ice_weakness != other_entity.ice_weakness) return 0;
    if (this->silver_weakness != other_entity.silver_weakness) return 0;

    if (this->total_physical_resistance != other_entity.total_physical_resistance) return 0;
    if (this->total_fire_resistance != other_entity.total_fire_resistance) return 0;
    if (this->total_poison_resistance != other_entity.total_poison_resistance) return 0;
    if (this->total_ice_resistance != other_entity.total_ice_resistance) return 0;
    if (this->total_silver_resistance != other_entity.total_silver_resistance) return 0;
    
    if (this->is_stunned != other_entity.is_stunned) return 0;

    // inventory check
    //if (this->inventory.swords.empty() != other_entity.inventory.swords.empty()) return 0;
    if (this->inventory.swords.size() != other_entity.inventory.swords.size()) return 0;
    if (this->inventory.armors.size() != other_entity.inventory.armors.size()) return 0;
    
    for (auto sword : inventory.swords) {
        for (auto other_sword : other_entity.inventory.swords) {
            if (*sword != *other_sword) {
                return 0;
            }
        }
    }
    for (auto armor : inventory.armors) {
        for (auto other_armor : other_entity.inventory.armors) {
            if (*armor != *other_armor) {
                return 0;
            }
        }
    }
    return 1;
}

int Entity::operator!=(const Entity &other_entity) const {
    return !(*this == other_entity);
}
             ////Derivadas da Base 1 - mostrar uso static_cast
        // Ghoul
        // não pode usar static_cast pois é filho de uma classe abstrata
    int Ghoul::operator==(const Ghoul &other_ghoul) const {
    Entity::operator==(other_ghoul);
    if (this->is_enraged != other_ghoul.is_enraged) { return 0; }
    return 1;
}

int Ghoul::operator!=(const Ghoul &other_ghoul) const {
    return Entity::operator!=(other_ghoul);
}
        // Human
        // forma não permitida pela classe abstrata
        // static_cast< Entity * >( this ) = static_cast< Entity >( other_human );
    bool Human::operator==(const Human &other_human) const {
    Entity::operator==(other_human);

    // First checks if its empty
    if (equipped.steel_sword == 0 && other_human.equipped.steel_sword != 0) return false;
    if (equipped.steel_sword != 0 && other_human.equipped.steel_sword == 0) return false;
    // Then checks if its equal
    if (equipped.steel_sword != 0 && other_human.equipped.steel_sword != 0) {
        if (*equipped.steel_sword != *other_human.equipped.steel_sword) return false;
    }

    // First checks if its empty
    if (equipped.armor == 0 && other_human.equipped.armor != 0) return false;
    if (equipped.armor != 0 && other_human.equipped.armor == 0) return false;
    // Then checks if its equal
    if (equipped.armor != 0 && other_human.equipped.armor != 0) {
        if (*equipped.armor != *other_human.equipped.armor) return false;
    }

    return true;
}

bool Human::operator!=(const Human &other_human) const {
    return !(*this == other_human);
}

        // Witcher
    bool Witcher::operator==(const Witcher &other_witcher) const {
    static_cast< Human >( *this ) == static_cast< Human >( other_witcher );

    if (signs.igni != other_witcher.signs.igni) return false;
    if (is_close_to_chest != other_witcher.is_close_to_chest) return false;

    return true;
}

bool Witcher::operator!=(const Witcher &other_witcher) const {
    return !(*this == other_witcher);
}

         //// Base 2
         // Item
    int Item::operator==(const Item &other_Item) const {
    if (this->name != other_Item.name) return 0;
    if (this->description != other_Item.description) return 0;
    return 1;
}

int Item::operator!=(const Item &other_Item) const {
    return !(*this == other_Item);
}

             ////Derivadas da Base 2 - mostrar uso static_cast
        // Armor
    int Armor::operator==(const Armor &other_Armor) const {
    // forma não permitida pela classe abstrata Item
    //static_cast<const Item &>(*this) == static_cast<const Item &>(other_Armor);
    Item::operator==(other_Armor);
    if (this->physical_defense != other_Armor.physical_defense) return 0;
    if (this->fire_defense != other_Armor.fire_defense) return 0;
    if (this->poison_defense != other_Armor.poison_defense) return 0;
    if (this->ice_defense != other_Armor.ice_defense) return 0;
    if (this->silver_defense != other_Armor.silver_defense) return 0;
    
    return 1;
}

int Armor::operator!=(const Armor &other_Armor) const {
    return !(*this == other_Armor);
}
        // Weapon
    int Weapon::operator==(const Weapon &other_weapon) const {
    // Item is abstract, so we can't do this:
    // static_cast<Item>(*this) == static_cast<Item>(other_weapon);
    // So we do this:
    Item::operator==(other_weapon);

    if (this->physical_damage != other_weapon.physical_damage) return 0;
    if (this->fire_damage != other_weapon.fire_damage) return 0;
    if (this->poison_damage != other_weapon.poison_damage) return 0;
    if (this->ice_damage != other_weapon.ice_damage) return 0;
    if (this->silver_damage != other_weapon.silver_damage) return 0;

    return 1;
}

int Weapon::operator!=(const Weapon &other_weapon) const {
    return !(*this == other_weapon);
}
        // Sword
    int Sword::operator==(const Sword &other_sword) const {
    // Weapon is abstract, so we can't do this:
    // static_cast<Weapon>(*this) == static_cast<Weapon>(other_sword);
    // So we do this:
    Weapon::operator==(other_sword);
    if (this->made_of_silver != other_sword.made_of_silver) return 0;

    return 1;
}

int Sword::operator!=(const Sword &other_sword) const {
    return !(*this == other_sword);
}

        //// Base 3
        // Spell
    int Spell::operator==(const Spell &other_spell) const {
    if (this->name != other_spell.name) return 0;
    if (this->description != other_spell.description) return 0;
    return 1;
}

int Spell::operator!=(const Spell &other_spell) const {
    return !(*this == other_spell);
}
             ////Derivadas da Base 3 - mostrar uso static_cast
        // Sign
    int Sign::operator==(const Sign &other_sign) const {
    Spell::operator==(other_sign);

    if (this->stamina_cost == other_sign.stamina_cost) return 0;

    return 1;
}

int Sign::operator!=(const Sign &other_sign) const {
    return !(*this == other_sign);
}
        // Igni
    int Igni::operator==(const Igni &other_igni) const {
    Sign::operator==(other_igni);

    if (this->fire_damage != other_igni.fire_damage) return 0;
    if (this->area != other_igni.area) return 0;

    return 1;
}

int Igni::operator!=(const Igni &other_igni) const {
    return !(*this == other_igni);
}
     //// Operator<<
        //// Base 1
        // Entity
        // classe abstrata não possui cout, apenas print
    void Entity::print_info() const{
    cout << "Name: " << this->name << "\n";
    cout << "Category: " << this->category << "\n";
    cout << "Level: " << this->level << "\n";
    cout << "Age: " << this->age << "\n";
    cout << "Date of birth: ";
    this->date_of_birth.print();
    cout << "\n";
    cout << "Coins: " << this->coins << "\n";
    cout << "Health: " << this->health << "/" << this->max_health << "\n";
    cout << "Stamina: " << this->stamina << "/" << this->max_stamina << "\n";
    print_resistances();
    print_weaknesses();
    cout << "Temporary status: \n";
    cout << "Stunned: " << this->is_stunned << "\n";
    print_inventory();
}

            ////Derivadas da Base 1 - mostrar uso static_cast
        // Ghoul 
        // não pode usar static_cast pois é filho de uma classe abstrata
    ostream &operator<<(ostream &out, const Ghoul &ghoul) {
    ghoul.print_info();
    out << "Enraged: " << ghoul.is_enraged << "\n";
    
    return out;
}
        // Human
        // não pode usar static_cast pois é filho de uma classe abstrata
    ostream &operator<< (ostream &out, const Human &human) {
    human.print_info();
    out << "Equipped Items:\n";
    out << "Steel Sword: ";
    if (human.equipped.steel_sword == 0) out << "None\n";
    else out << *human.equipped.steel_sword << "\n";
    out << "Armor: ";
    if (human.equipped.armor == 0) out << "None\n";
    else out << *human.equipped.armor << "\n";
    return out;
}
        // Witcher
    ostream &operator<< (ostream &out, const Witcher &witcher) {
    out << static_cast<Human>(witcher);
    cout << "Witcher signs:\n";
    cout << *witcher.signs.igni << "\n";

    return out;
}

        //// Base 2
        // Item
        // classe abstrata não possui cout, apenas print
    void Item::print_info() const {
    cout << "Name: " << name << '\n';
    cout << "Description: " << description << '\n';
}

            ////Derivadas da Base 2 - mostrar uso static_cast
        // Armor
        // static_cast não é permitido pois Item é abstrata
    ostream &operator<< (ostream &out, const Armor &Armor){
    Armor.print_info();
    out << Armor.name << " (+" << Armor.physical_defense << " physical defense)\n";
    if (Armor.fire_defense > 0) out << " (+" << Armor.fire_defense << " fire defense)\n";
    if (Armor.poison_defense > 0) out << " (+" << Armor.poison_defense << " poison defense)\n";
    if (Armor.ice_defense > 0) out << " (+" << Armor.ice_defense << " ice defense)\n";
    if (Armor.silver_defense > 0) out << " (+" << Armor.silver_defense << " silver defense)\n";

    return out;
}
        // Weapon
        // a classe weapon tambem é abstrata, portanto não usa cout
    void Weapon::print_info() const {
    cout << name << " (+" << physical_damage << " physical damage)\n";
    if (fire_damage > 0) cout << " (+" << fire_damage << " fire damage)\n";
    if (poison_damage > 0) cout << " (+" << poison_damage << " poison damage)\n";
    if (ice_damage > 0) cout << " (+" << ice_damage << " ice damage)\n";
    if (silver_damage > 0) cout << " (+" << silver_damage << " silver damage)\n";

    cout << "\"" << description << "\"";
}   
        // Sword
        // static_cast não é permitido pois Weapon é abstrata
    ostream &operator<< (ostream &out, const Sword &sword){
    sword.print_info();
    out << sword.name << " (+" << sword.physical_damage << " physical damage)\n";
    if (sword.fire_damage > 0) out << " (+" << sword.fire_damage << " fire damage)\n";
    if (sword.poison_damage > 0) out << " (+" << sword.poison_damage << " poison damage)\n";
    if (sword.ice_damage > 0) out << " (+" << sword.ice_damage << " ice damage)\n";
    if (sword.silver_damage > 0) out << " (+" << sword.silver_damage << " silver damage)\n";

    return out;
}

       //// Base 3
         // Spell
        // classe abstrata não possui cout, apenas print
    void Spell::print_info() const {
    cout << "Name: " << name << '\n';
    cout << "Description: " << description << '\n';
}

            ////Derivadas da Base 3 - mostrar uso static_cast
        // Sign
        // a classe sign tambem é abstrata, portanto não usa cout
    void Sign::print_info() const {
    Spell::print_info();
    cout << "Is unlocked: " << is_unlocked << "\n";
    cout << "Stamina cost: " << stamina_cost << "\n";
}
        // Igni
        // static_cast não é permitido pois Sign é abstrata
    ostream &operator<< (ostream &out, const Igni &igni){
    igni.print_info();
    out << "Fire damage: " << igni.fire_damage << "\n";
    out << "Area: " << igni.area << "\n";

    return out;
}

//// Para cada classe do seu projeto criar pelo menos dois constructores, 
 //sendo um o constructor de cópia 
 ////Mostrar uso de reaproveitamento de código da base na derivada

    //// Base 1 - constructores
    // Entity
        ////Constructor 1
        // a classe é abstrata portanto o construtor não instancia nada
    Entity::Entity() {
    //cout << "Creating a new Entity...\n";
    name = "Entity";
    age = 0;
    coins = 0;
    max_health = 0;
    health = 0;
    max_stamina = 0;
    stamina = 0;
    category = "_";
    level = 0;
    next_level_xp = 10;
    xp = 0;

    physical_weakness = 1;
    fire_weakness = 1;
    poison_weakness = 1;
    ice_weakness = 1;
    silver_weakness = 1;

    total_physical_resistance = 0;
    total_fire_resistance = 0;
    total_poison_resistance = 0;
    total_ice_resistance = 0;
    total_silver_resistance = 0;

    is_stunned = false;
}
        ////Constructor de cópia
    Entity::Entity(const Entity &other_entity) {
    //cout << "Copying Entity...\n";
    this->name = other_entity.name;
    this->age = other_entity.age;
    this->coins = other_entity.coins;

    this->max_health = other_entity.max_health;
    this->health = other_entity.health;
    this->max_stamina = other_entity.max_stamina;
    this->stamina = other_entity.stamina;

    this->category = other_entity.category;
    this->level = other_entity.level;
    this->next_level_xp = other_entity.next_level_xp;
    this->xp = other_entity.xp;

    this->is_stunned = other_entity.is_stunned;

    this->physical_weakness = other_entity.physical_weakness;
    this->fire_weakness = other_entity.fire_weakness;
    this->poison_weakness = other_entity.poison_weakness;
    this->ice_weakness = other_entity.ice_weakness;
    this->silver_weakness = other_entity.silver_weakness;

    this->total_physical_resistance = other_entity.total_physical_resistance;
    this->total_fire_resistance = other_entity.total_fire_resistance;
    this->total_poison_resistance = other_entity.total_poison_resistance;
    this->total_ice_resistance = other_entity.total_ice_resistance;
    this->total_silver_resistance = other_entity.total_silver_resistance;

    for (auto sword : other_entity.inventory.swords) {
        Sword * new_sword = new Sword(*sword);
        this->inventory.swords.push_back(new_sword);
    }
    for (auto armor : other_entity.inventory.armors) {
        Armor * new_armor = new Armor(*armor);
        this->inventory.armors.push_back(new_armor);
    }

}

    //// Base 2 - constructores
    // Item
        ////Constructor 1
        // a classe é abstrata portanto o construtor não instancia nada
    Item::Item() {
    //cout << "Creating a new Item...\n";
    name = "Item";
    description = "A generic item.";
}
        ////Constructor de cópia
    Item::Item(const Item &other_Item) {
    this->name = other_Item.name;
    this->description = other_Item.description;
}

    //// Base 3 - constructores
    // Spell
        ////Constructor 1
        // a classe é abstrata portanto o construtor não instancia nada
    Spell::Spell() {
    //cout << "Creating a new Spell...\n";
    name = "Spell";
    description = "A generic Spell.";
    is_unlocked = false;
}
        ////Constructor de cópia 
    Spell::Spell(const Spell &other_spell) {
    this->name = other_spell.name;
    this->description = other_spell.description;
    this->is_unlocked = other_spell.is_unlocked;
}

    ////Derivadas - constructores

        //// Hierarquia 1
        // Entity

             ////Classe 1
             // Ghoul
                 ////Constructor 1
                 // como é filho de uma classe abstrata não pode usar
                 // static cast e como deve possuir valores padrão caracteristicos dele
                 // chamando funções q são puramente virtuais na abstrata Entity,
                 // a saber, level_up(), update_atributes(), update_all_resistances() e
                 // update_all_weaknesses(), sendo que algumas seguem uma equação da reta 
                 // com coeficientes declarados no escopo da classe derivada,
                 //  ele não poderia reaproveitar nada
    Ghoul::Ghoul() {
    //cout << "Creating a new Ghoul...\n";
    name = "Ghoul";
    age = 100;
    coins = 15;

    category = CATEGORIES[0];
    level = 0;
    xp = 0;

    update_atributes();
    life_regen(max_health);
    stamina_regen(max_stamina);

    update_all_resistances();
    update_all_weaknesses();

    bool is_stunned = false;
}

Ghoul::Ghoul(string name, 
             int age, 
             double coins, 
             int level,
             string category) {

    setName(name);
    setAge(age);
    setCoins(coins);

    setCategory(category);
    setLevel(level);
    setXp(0);

    update_atributes();
    life_regen(max_health);
    stamina_regen(max_stamina);

    update_all_resistances();
    update_all_weaknesses();

    is_stunned = false;
}
                 ////Constructor de cópia
                 // reaproveita a esmagadora maioria dos atributos e a copia do inventario
    Ghoul::Ghoul(const Ghoul &other_ghoul) : Entity(other_ghoul) {
    //cout << "Copying Ghoul...\n";

    this->is_enraged = other_ghoul.is_enraged;
    
}
             ////Classe 2
             // Human
                 ////Constructor 1
            // não pode reaproveitar o construtor pelo mesmo motivo da classe Ghoul acima
            Human::Human() {
    //cout << "Creating a new Human...\n";
    name = "Peasant";
    age = 30;
    coins = 50.00;

    category = CATEGORIES[0];
    level = 0;
    xp = 0;

    update_atributes();
    life_regen(max_health);
    stamina_regen(max_stamina);

    equipped.steel_sword = 0;
    equipped.armor = 0;

    is_stunned = false;

    date_of_birth = Date(1, 1, 1000 - age);

    update_all_resistances();
    update_all_weaknesses();
}

Human::Human(string name, 
            int age, 
            double coins, 
            int level,
            string category) {
                
    setName(name);
    setAge(age);
    setCoins(coins);

    setCategory(category);
    setLevel(level);
    setXp(0);
    update_atributes();
    life_regen(max_health);
    stamina_regen(max_stamina);


    equipped.steel_sword = new Sword();
    equipped.armor = new Armor();

    is_stunned = false;

    date_of_birth = Date(1, 1, 1000 - age);

    update_all_resistances();
    update_all_weaknesses();
}
                 ////Constructor de cópia
            // reaproveita a esmagadora maioria dos atributos e a copia do inventario
    Human::Human(const Human &other_human) : Entity(other_human) {
    //cout << "Copying Human...\n";

    if (other_human.equipped.steel_sword == 0) equipped.steel_sword = 0;
    else equipped.steel_sword = new Sword(*other_human.equipped.steel_sword);

    if (other_human.equipped.armor == 0) equipped.armor = 0;
    else equipped.armor = new Armor(*other_human.equipped.armor);

}
             ////Classe 3
            // Witcher
            ////Constructor 1
            // não pode reaproveitar o codigo de Human porq os seus valores devem ser incializados
            // de acordo com uma função da reta diferente da de Human
            Witcher::Witcher() {
    //cout << "Creating a new Witcher...\n";
    name = "Witcher";
    age = 200;
    coins = 150;

    category = CATEGORIES[0];
    level = 0;
    xp = 0;
    update_atributes();
    life_regen(max_health);
    stamina_regen(max_stamina);

    equipped.steel_sword = 0;
    equipped.armor = 0;

    signs.igni = new Igni();
    signs.igni->setIs_unlocked(true);
    
    is_stunned = false;

    is_close_to_chest = false;

    date_of_birth = Date(1, 1, 1000 - age);

}

Witcher::Witcher(string name, 
                 int age, 
                 double coins, 
                 int level,
                 string category) {
                
    setName(name);
    setAge(age);
    setCoins(coins);

    setCategory(category);
    setLevel(level);
    setXp(0);
    update_atributes();
    life_regen(max_health);
    stamina_regen(max_stamina);

    signs.igni = new Igni();
    signs.igni->setIs_unlocked(true);

    is_stunned = false;

    is_close_to_chest = false;

    date_of_birth = Date(1, 1, 1000 - age);

    equipped.steel_sword = new Sword();
    equipped.armor = new Armor();
    update_all_resistances();
}
            ////Constructor de cópia
            // reaproveita a esmagadora maioria dos atributos e a copia dos itens equipados
            // utilizando static_cast
    Witcher::Witcher(const Witcher &other_witcher) : Human(static_cast<Human>(other_witcher)) {
    //cout << "Copying Witcher...\n";
    is_close_to_chest = other_witcher.is_close_to_chest;
    signs.igni = other_witcher.signs.igni;
}
             ///E assim por diante


        //// Hierarquia 2
        // Item

             ////Classe 1
             // Armor
                 ////Constructor 1
                 // não usa static cast porq a classe base é abstrata e seus atributos padrão
                 // são diferentes
                 Armor::Armor() {
    //cout << "Creating a new Armor...\n";
    name = "Common Armor";
    description = "A common armor. Very used and not very protective.";
    physical_defense = 1;
    fire_defense = 0;
    poison_defense = 0;
    ice_defense = 0;
    silver_defense = 0;
}

Armor::Armor(string name, string description, 
                          int physical_defense, 
                          int fire_defense, 
                          int poison_defense, 
                          int ice_defense, 
                          int silver_defense) {
    setName(name);
    setDescription(description);
    setPhysical_defense(physical_defense);
    setFire_defense(fire_defense);
    setPoison_defense(poison_defense);
    setIce_defense(ice_defense);
    setSilver_defense(silver_defense);

}

                 ////Constructor de cópia
                 // reaproveita atributos
    Armor::Armor(const Armor &other_Armor) : Item(other_Armor) {
    this->physical_defense = other_Armor.physical_defense;
    this->fire_defense = other_Armor.fire_defense;
    this->poison_defense = other_Armor.poison_defense;
    this->ice_defense = other_Armor.ice_defense;
    this->silver_defense = other_Armor.silver_defense;

}

             ////Classe 2
                // Weapon
                 ////Constructor 1
            // não usa static cast porq a classe base é abstrata e sendo a propria derivada
            // abstrata tambem, seu construtor não instancia nada
    Weapon::Weapon() {
    //cout << "Creating a new weapon...\n";
    name = "A generic weapon";
    description = "A generic weapon. Very Used by the common folk.";
    physical_damage = 0;
    fire_damage = 0;
    poison_damage = 0;
    ice_damage = 0;
    silver_damage = 0;
}

                 ////Constructor de cópia
                // reaproveita atributos
    Weapon::Weapon(const Weapon &other_weapon) : Item(other_weapon){
    this->physical_damage = other_weapon.physical_damage;
    this->fire_damage = other_weapon.fire_damage;
    this->poison_damage = other_weapon.poison_damage;
    this->ice_damage = other_weapon.ice_damage;
    this->silver_damage = other_weapon.silver_damage;

}

                ////Classe 3
                    // Sword
                    ////Constructor 1
            // não usa static cast porq a classe base é abstrata e seus valores
            // padrão tambem são diferentes
    Sword::Sword() {
    //cout << "Creating a new Sword...\n";
    name = "Common Sword";
    description = "A common sword. Very Used by the common folk.";
    physical_damage = 2;
    fire_damage = 0;
    poison_damage = 0;
    ice_damage = 0;
    silver_damage = 0;
    made_of_silver = false;

}

Sword::Sword(string name, string description, 
                          int physical_damage, 
                          int fire_damage, 
                          int poison_damage, 
                          int ice_damage, 
                          int silver_damage,
                          bool made_of_silver) {
    setName(name);
    setDescription(description);
    setPhysical_damage(physical_damage);
    setFire_damage(fire_damage);
    setPoison_damage(poison_damage);
    setIce_damage(ice_damage);
    setSilver_damage(silver_damage);
    setMade_of_silver(made_of_silver);
}
                
            ////Constructor de cópia
            // reaproveita a maioria dos atributos
    Sword::Sword(const Sword &other_sword) : Weapon(other_sword){
    //cout << "Copying Sword...\n";
    made_of_silver = other_sword.made_of_silver;

}
             ///E assim por diante


      //// Hierarquia 3
      // Spell

             ////Classe 1
            // Sign
                 ////Constructor 1
    // não usa static cast porq a classe base é abstrata e sendo a propria derivada
    // abstrata tambem, seu construtor não instancia nada
    Sign::Sign() {
    this->name = "Sign";
    this->description = "A sign spell.";
    this->is_unlocked = false;
    this->stamina_cost = 0;
    }
                 ////Constructor de cópia
    // reaproveita atributos
    Sign::Sign(const Sign &other_sign) : Spell(other_sign) {
    this->stamina_cost = other_sign.stamina_cost;
}

             ////Classe 2
            // Igni
                 ////Constructor 1
    // não usa static cast porq a classe base é abstrata e seus valores
    // padrão tambem são diferentes
    Igni::Igni() {
    this->name = "Igni";
    this->description = "A fire spell that deals damage to 3 enemies at a time.";
    this->is_unlocked = false;
    this->stamina_cost = 6;
    this->fire_damage = 8;
    this->area = 3;
}

Igni::Igni(string name, 
           string description, 
           bool is_unlocked, 
           int stamina_cost, 
           int fire_damage, 
           int area) {
    this->name = name;
    this->description = description;
    this->is_unlocked = is_unlocked;
    this->stamina_cost = stamina_cost;
    this->fire_damage = fire_damage;
    this->area = area;
}

                 ////Constructor de cópia
            // reaproveita atributos
    Igni::Igni(const Igni &other_igni) : Sign(other_igni) {
    this->fire_damage = other_igni.fire_damage;
    this->area = other_igni.area;
}

             ///E assim por diante

//>>>Comentário: era para mostrar o código de salvamento aqui

//// Carregamento e salvamento de arquivos
    /*É necessário ter a funcionalidade: 1. 
      leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
      processamento das variáveis de status e 3. salvamento dessas variáveis. 
      Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/

    //Link arquivo de configuração no repositório
    // path para a pasta com os 3 arquivos de configuração:a-witcher-tale/save-files
    // Link : https://github.com/luiz-fleite/a-witcher-tale/tree/main/save-files/config-witcher

    //Link vídeo mostrando a execução do código usando o arquivo de configuração
    // Link : https://drive.google.com/drive/folders/19zTKEHwtlts1WFDu0uHt2Zwy0f5eKu12?usp=sharing
