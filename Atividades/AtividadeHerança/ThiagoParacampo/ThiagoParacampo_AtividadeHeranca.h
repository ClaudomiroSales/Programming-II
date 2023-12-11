/*Criar três hierarquia, sendo duas de três níveis, como explicado em sala e 
no Classroom. Fazer a sobrecarga para cada classe dos operadores =, ==, ≠, ! e << 
(friend). Usar sempre que possível o static_cast para reaproveitamento de código. 
Para cada classe do seu projeto criar pelo menos três constructores, 
sendo um o constructor de cópia. É necessário ter a funcionalidade: 1. 
leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
processamento das variáveis de status e 3. salvamento dessas variáveis. 
Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/


//// Geral - parte para revisão
    //Diagrama UML    //>>>Comentário: a terceira hierarquia faltou um lado
                      //GameObject deveria ter outro lado
    //Organização do código 

//// O .h das classes bases

////Classe Base 1 - Interactable.h


class Interactable
{
    friend ostream& operator<<  ( ostream&, const Interactable& );
    friend int      operator!   ( const Interactable& );
public:
    Interactable            (  );
    Interactable            ( char, char );
    Interactable            ( const Interactable& );
    virtual ~Interactable   (  );

    void interact   (  );
    
   ...

    const Interactable& operator=       ( const Interactable& );
    int                 operator==      ( const Interactable& );
    int                 operator!=      ( const Interactable& );

protected:
    char actual_representation;
    char before_interaction;
    char after_interaction;
};

#endif // INTERACTABLE_H

////Classe Base 2 - GameObject.h


/**
 * Essa classe administra qualquer objeto presente no jogo.
*/

//>>>Comentário: Não tem métodos

class GameObject
{
    friend ostream& operator<<  ( ostream&, const GameObject& );
    friend int      operator!   ( const GameObject& );
public:

    GameObject  (  );
    GameObject  ( Vector2D, char );
    GameObject  ( const GameObject& );

    virtual ~GameObject();

   
    const GameObject&   operator=   ( const GameObject& );
    int                 operator==  ( const GameObject& );
    int                 operator!=  ( const GameObject& );

protected:
    Vector2D* position = 0;
    char representation;
};

#endif

////Classe Base 3 - Battle.h


class Battle
{
    friend ostream& operator<<  ( ostream&, const Battle& );
    friend int      operator!   (const Battle& );
public:
    Battle(  );
    Battle( Entity&, Entity& );
    Battle( const Battle& );

    virtual ~Battle(  );

    virtual bool begin_battle   (  )    = 0;
    void planTurn( const Attack&, const Attack& );
    void executeTurn();

   

    const Battle& operator= ( const Battle& );
    int operator==          ( const Battle& );
    int operator!=          ( const Battle& );

protected:
    Entity* primeiro_ptr    = 0;
    Entity* segundo_ptr     = 0;

    const Attack* attack_primeiro_ptr = 0;
    const Attack* attack_segundo_ptr  = 0;
    
    int turno;
};

#endif // BATTLE_H


//// O .h da hierarquia 1

////Classe 1 - Item.h

//>>>Comentário: não tem métodos

class Item : public Interactable
{
    friend ostream& operator<<  ( ostream&, const Item& );
    friend int      operator!   ( const Item& );
public:
    Item            ( );
    Item            ( string, string );
    Item            ( const Item& );
    virtual ~Item   ( );
    
   

    const Item& operator=   ( const Item& );
    int         operator==  ( const Item& );
    int         operator!=  ( const Item& );

protected:
    const static u_int8_t   MAX_ITEM_STACK;
    const static size_t     MAX_NAME_SIZE;
    const static size_t     MAX_DESCRIPTION_SIZE;
    const static string     DEFAULT_ITEM_NAME;
    const static string     DEFAULT_DESCRIPTION;

    string name;
    string description;
};

#endif

////Classe 2 - Armor.h

//>>>Comentário: não tem métodos

class Armor : public Item
{
    friend ostream& operator<<  ( ostream&, const Armor& );
    friend int      operator!   (const Armor& );
public:
    Armor();
    Armor( double, double = 0.0, double = 1.0 );
    Armor( const Armor& );
    virtual ~Armor();

   

    const Armor& operator=  ( const Armor& );
    int operator==          ( const Armor& );
    int operator!=          ( const Armor& );

protected:
    const static string DEFAULT_ARMOR_NAME;

    double  damage_reduction;
    double  min_strength;
    double  weight;
};  

#endif // ARMOR_H

///Classe 3 - Consumable

//>>>Comentário: não tem métodos

class Entity; // Só pra dizer que entity existe.

class Consumable : public Item
{
    friend ostream& operator<<  ( ostream&, const Consumable& );
    friend int      operator!   ( const Consumable& );
public:

    Consumable  (  );
    Consumable  ( string, string, double = 1.0f );
    Consumable  ( const Consumable& );

    virtual ~Consumable();

   

    const Consumable&   operator=   ( const Consumable& );
    int                 operator==  ( const Consumable& );
    int                 operator!=  ( const Consumable& );

private:
    double health_factor;   // Ratio usado em operações - porcentagem!
};

#endif // CONSUMABLE_H

/// Classe 4 - Weapon.h


class Weapon : public Item
{
    friend ostream& operator<<  ( ostream&, const Weapon& );
    friend int      operator!   (const Weapon& );
public:
    Weapon();
    Weapon( string, double, int = 100 );
    Weapon( const Weapon& );
    virtual ~Weapon();

    void    increaseDurability  ( double );
    void    decreaseDurability  ( int );

    

    const Weapon& operator= ( const Weapon& );
    int operator==          ( const Weapon& );
    int operator!=          ( const Weapon& );

protected:
    const static string DEFAULT_WEAPON_NAME;

    double  damage;
    int     durability;
};  

#endif // WEAPON_H


//// O .h da hierarquia 2

////Classe 1 - Entity.h


/* Define as partes default de vector< BodyPart > */
#define DEFAULT_ENTITY_BODY_PARTS { \
    { "HEAD" , 2.0f }, \
    { "FRONT", 1.0f }, \
    { "BACK", 1.5f  } }



/**
 * Classe que abstrai tudo que se move e pode batalhar!
*/
class Entity : public GameObject
{
    friend ostream& operator<<  ( ostream&, const Entity& );
    friend int      operator!   ( const Entity& );
public:
    Entity                  ( );
    Entity                  (   string,
                                double = 100.0f, 
                                double = 100.0f,
                                double = 50.0f,
                                double = 25.0f,
                                Vector2D = { 0 },
                                vector< BodyPart > = DEFAULT_ENTITY_BODY_PARTS );
    Entity                  ( const Entity& );
    virtual ~Entity         ( );


    void    move                        ( Direction );
    void    equipWeapon                 ( const Weapon& );
    void    attack                      ( Entity&, const Attack& );
    void    receiveDamage               ( double );
    double  calculateDamageModifier     (  );
    void    heal                        ( double );
    void    guard                       ( );
    void    grabItem                    ( Item& );
    void    useItem                     ( Item& );
    void    useItem                     ( size_t );

    void showInventory                  ( ) const;
    const BodyPart& chooseRandBodyPart  ( ) const;

    // void battle     ( Entity& );

    inline bool isUnarmed()     const { return (equiped_weapon_ptr == 0) ? true : false; }
    inline bool isGuarding()    const { return this->guarding; }

    
    const Entity&   operator=   ( const Entity& );
    int             operator==  ( const Entity& );
    int             operator!=  ( const Entity& );

private:

    static bool isBodyPartValid( BodyPart& );

    void copyInventory      ( const vector< InventoryItem* >* const );
    void deleteInventory    (  );
    void copyWeapon         ( const Weapon* const );

    const static size_t NAME_MAX_SIZE;             // Máximo de um item que pode ser carregado
    const static size_t ITEM_MAX_STACK;             // Máximo de um item que pode ser carregado
    const static size_t BODY_PART_DESC_MAX_SIZE;    // Tamanho máximo da string do BodyPart
    const static string DEFAULT_NAME;               // Nome padrão de entidades não declaradas

    string  name;        // Nome que identifica identidade
    double  maxHealth;   // Vida máxima permitida pelo nível do personagem
    double  health;      // Vida atual da entidade
    double  stamina;     // Permite o ataque
    double  strength;    // Impacta no modificador de dano
    double  dexterity;   // O quão rápido a Stamina sobe
    bool    guarding;
    vector< BodyPart > bodyParts;

    Weapon* equiped_weapon_ptr = 0;                 // Arma equipada pela entidade
    vector< InventoryItem* >* inventory_ptr = 0;        // Inventário da entidade
};

#endif // ENTITY_H

////Classe 2 - Player.h


class Player : public Entity
{
    friend ostream& operator<<  ( ostream&, const Player& );
    friend int      operator!   ( const Player& );
public:
    Player();
    Player( string,
            double = 100.0f,
            double = 100.0f,
            double = 50.0f,
            double = 25.0f,
            Vector2D = { 0 },
            vector< BodyPart > = DEFAULT_ENTITY_BODY_PARTS );
    Player( const Player& );
    virtual ~Player();

    // void receiveInput   ( );
    void addAttack      ( Attack& );
 
  

    const Player&   operator=   ( const Player& );
    int             operator==  ( const Player& );
    int             operator!=  ( const Player& );

private:
    void copyAttacks        ( const Player& );
    void deleteAttacks      (  );

    static unsigned int numPlayers;
    vector< Attack* >   attacks;        // É melhor um ponteiro de ataques ou só ataques?
};

#endif // PLAYER_H

/// Classe 3 - Enemy.h


class Enemy : public Entity
{
    friend ostream& operator<<  ( ostream&, const Enemy& );
    friend int      operator!   ( const Enemy& );
public:
    Enemy   ();
    Enemy   (   string,
                double = 100.0f,
                double = 100.0f,
                double = 50.0f,
                double = 25.0f,
                Vector2D = { 0 },
                vector< BodyPart > = DEFAULT_ENTITY_BODY_PARTS,
                map< int, Attack * > = { } );
    Enemy   ( const Enemy& );
    virtual ~Enemy  ( );

    /* Métodos static não podem ser const */
    inline static unsigned short getNumEnemies() { return Enemy::numEnemies; }
    map< int, Attack* > *const getAttacksAndProbabilities() { return &this->probabilitiesAndAttacks; };


    const Attack *const chooseAttack            (  );
    void enrageEnemy                ( Enemy& )  const;
    void addAttackAndProbability    ( Attack*, int );

    const Enemy&    operator=   ( const Enemy& );
    int             operator==  ( const Enemy& );
    int             operator!=  ( const Enemy& );

private:
    const static unsigned int   MAX_NUM_ENEMIES;
    const static unsigned short MIN_ENEMIES_TO_RAGE;
    
    static unsigned short numEnemies;

    //Isso é o melhor jeito de fazer as coisas? 
    map< int, Attack* > probabilitiesAndAttacks;
};

#endif // ENEMY_H


//// O .h da hierarquia 3

////Classe 1 - BossBattle.h

class BossBattle : Battle
{
    friend ostream& operator<<  ( ostream&, const BossBattle& );
    friend int      operator!   (const BossBattle& );
public:
    BossBattle  (  );
    BossBattle  ( Entity& );
    BossBattle  ( const BossBattle& );

    virtual ~BossBattle(  );

    bool begin_battle( ) override;
    void add_phase( Enemy& );

    const BossBattle& operator= ( const BossBattle& );
    int operator==              ( const BossBattle& );
    int operator!=              ( const BossBattle& );

protected:
    vector<Enemy*> boss_phases;
    int phase_number;
};

#endif // BossBattle_H


//// Mostrar implementação de método que especializa a derivada
 /// Mostrar reaproveitamente de código da base

//// Hierarquia 1
////Classe 1 - Item
// Nota: Nenhum método - futura classe abstrata

//>>>Comentário: set, gets e prints não cumpre requisitos
//increaseDurability é praticamente um set

////Classe 2 - Consumable.h
void Consumable::consume_item(Entity& entidade)
{
    entidade.setHealth( entidade.getHealth() * this->health_factor );
}

////Classe 3 - Weapon.h
void Weapon::increaseDurability( double ratio)
{
    if (ratio < 0)
        return;
    this->setDurability( (int) (durability + (durability * ratio)) );
}

void Weapon::decreaseDurability( int amount )
{
    if (amount < 0)
        return;
    this->setDurability( this->durability - amount );
}

////Classe 3 - Armor.h
// Nada por enquanto, só atributos especializados.

//// Hierarquia 2 - GameObject

////Classe 1 - Entity
/**
 * Move a entidade através da matriz
 * @param where Direcão baseada no Enum Direction
*/

//>>>Comentário: addAttack é apenas atualização de um vetor

void Entity::move( Direction where )
{
    switch (where)
    {
    case UP:
        this->setPosition( 
            Vector2D { this->position->x, this->position->y - 1 } 
        );
        break;
    
    case RIGHT:
        this->setPosition( 
            Vector2D { this->position->x + 1, this->position->y } 
        );
        break;
    
    case DOWN:
        this->setPosition( 
            Vector2D { this->position->x, this->position->y + 1 } 
        );
        break;

    case LEFT:
        this->setPosition( 
            Vector2D { this->position->x - 1, this->position->y } 
        );
        break;
    
    default:
        break;
    }
}

////Classe 2 - Player.h
/**
 * Adiciona um ataque no vetor de ataques.
 * @param atk Ataque a ser adicionado.
*/
void Player::addAttack( Attack& atk )
{
    this->attacks.push_back( new Attack( atk ) );
}

/**
 * Copia o vetor de ataques de outro Player.
 * @param other O player do qual o inventário será copiado.
*/
void Player::copyAttacks(const Player& other )
{
    if ( !this->attacks.empty() )
        this->deleteAttacks();

    for ( const auto& otherAtk : other.attacks )
        this->attacks.push_back( new Attack( *otherAtk ) );
}

/**
 * Deleta os ponteiros de ataques dentro do Vetor attacks.
*/

//>>>Comentário: idem comentário anterior

void Player::deleteAttacks( )
{
    for ( auto& atk : this->attacks )
        if ( atk )
            delete atk;
    this->attacks.clear();
}

////Classe 2 - Enemy.h
// Cria atributo especializado para ataques. Toda a lógica de ataque está na classe Entity
/**
 * Escolhe aleatoriamente um ataque do map.
*/
const Attack *const Enemy::chooseAttack( )
{
    std::random_device rd;
    std::mt19937 gerador(rd());
    std::uniform_int_distribution<int> distribuicao(1, 100);
    int chance = distribuicao(gerador);

    Attack* chosen_attack = 0;

    for (const auto& par : this->probabilitiesAndAttacks)
    {
        if (chance < par.first)
        {
            return par.second;
        }
        chosen_attack = par.second;
    }

    return chosen_attack;
}

//// Hierarquia 3

////Classe 1 - NormalBattle.h
// Especialização completa da função begin_battle
/**
 * TODO: Verificar se é Enemy - Player ou Player - Enemy ou Enemy - Enemy
*/
bool NormalBattle::begin_battle()
{
    size_t chosen_attack;

    // Verifica se é Player ou Enemy
    Player* player_ptr  = dynamic_cast<Player*> (this->primeiro_ptr);
    Enemy*  enemy_ptr   = dynamic_cast<Enemy*>  (this->segundo_ptr);

    while ( player_ptr->getHealth() > 0
            && enemy_ptr->getHealth() > 0 )
    {
        system("clear");
        std::cout << "==========================\n";
        std::cout << " | " << player_ptr->getName() << "\t|\t" << enemy_ptr->getName() << "\t|\n";
        std::cout << " | " << player_ptr->getHealth() << "\t\t|\t" << enemy_ptr->getHealth() << "\t|\n";
        std::cout << "==========================\n";
        std::cout << "Escolha seu ataque!\n";
        std::cout << "==========================\n";
        for ( size_t i = 0; i < player_ptr->getAttacks().size(); ++i)
        {
            std::cout << "( " << i << " ) - " << *player_ptr->getAttacks().at(i) << "\n"; 
        }
        std::cout << "Escolha: ";
        std::cin >> chosen_attack;

        this->planTurn(
            *player_ptr->getAttacks().at( chosen_attack ),  *enemy_ptr->chooseAttack()
        );
        system("clear");
        this->executeTurn();
        std::cin >> chosen_attack;
    }

    if ( player_ptr->getHealth() > 0 )
    {
        system("clear");
        std::cout << "VOCÊ GANHOU!\n";
        std::cin >> chosen_attack;
        return true;
    }
    system("clear");
    std::cout << "GAME OVER\n";
    std::cin >> chosen_attack;
    return false;
}

////Classe 2 - BossBattle.h
/// Lógica de Batalha diferente!
/**
 * TODO: Verificar se é Enemy - Player ou Player - Enemy ou Enemy - Enemy
*/
bool BossBattle::begin_battle()
{
    size_t chosen_attack;

    // Verifica se é Player ou Enemy
    Player* player_ptr  = dynamic_cast<Player*> (this->primeiro_ptr);

    for (auto& phase : this->boss_phases)
    {
        this->segundo_ptr = phase;
        Enemy*  enemy_ptr   = dynamic_cast<Enemy*>  (this->segundo_ptr);
        
        while ( player_ptr->getHealth() > 0
                && enemy_ptr->getHealth() > 0 )
        {
            system("clear");
            std::cout << "==========================\n";
            std::cout << " | " << player_ptr->getName() << "\t|\t * " << enemy_ptr->getName() << " * \t|\n";
            std::cout << " | " << player_ptr->getHealth() << "\t\t|\t" << enemy_ptr->getHealth() << "\t|\n";
            std::cout << "==========================\n";
            std::cout << "Escolha seu ataque!\n";
            std::cout << "==========================\n";
            for ( size_t i = 0; i < player_ptr->getAttacks().size(); ++i)
            {
                std::cout << "( " << i << " ) - " << *player_ptr->getAttacks().at(i) << "\n"; 
            }
            std::cout << "Escolha: ";
            std::cin >> chosen_attack;

            this->planTurn(
                *player_ptr->getAttacks().at( chosen_attack ),  *enemy_ptr->chooseAttack()
            );
            system("clear");
            this->executeTurn();
            std::cin >> chosen_attack;
        }

        system("clear");
        if (this->phase_number != this->boss_phases.size() - 1)
        {
            std::cout << "O cavaleiro negro se debate, mas seu coração é mais forte!\nEle não está morto, ainda.\nAsas começam a sair da sua armadura!\n";
            std::cout << "Ele está mais forte!\n";
            std::cin >> chosen_attack;
            this->phase_number++;
        }

        if ( player_ptr->getHealth() <= 0 )
            return false;
    }

    if ( player_ptr->getHealth() > 0 )
        return true;
    return false;
}


//// Fazer a sobrecarga para todas as classes dos operadores =, ==, ≠ e << (friend)

//// Operator=
//// Base 1 - Interactable.h
const Interactable &Interactable::operator=(const Interactable& other)
{
    if (this != &other)
    {
        this->after_interaction = other.after_interaction;
        this->before_interaction = other.before_interaction;
    }
    return *this;
}

//>>>Comentário: static_cast isadp corretamente

////Derivadas da Base 1 - mostrar uso static_cast
/// Derivada 1 - Item.h
const Item& Item::operator= ( const Item& right )
{
    if (&right != this)
    {
        static_cast<Interactable> (*this) = static_cast<Interactable> (right);
        this->name = right.name;
        this->description = right.description;
    }
    return *this;
}

/// Derivada 2 - Armor.h
const Armor &Armor::operator=(const Armor &right)
{
    if (&right != this)
    {
        static_cast<Item> (*this) = static_cast<Item> (right);
        this->damage_reduction = right.damage_reduction;
        this->min_strength = right.min_strength;
        this->weight = right.weight;
    }
    return *this;
}

/// Derivada 3 - Weapon
const Weapon& Weapon::operator= (const Weapon& right)
{
    if (&right != this)
    {
        static_cast<Item> (*this) = static_cast<Item> (right);
        this->damage = right.damage;
        this->durability = right.durability;
    }
    return *this;
}

/// Derivada 4 - Consumable.h
const Consumable &Consumable::operator=(const Consumable &right)
{
    if (&right != this)
    {
        static_cast<Item> (*this) = static_cast<Item> (right);
        this->name = right.name;
        this->description = right.description;
    }
    return *this;
}

//// Base 2
const GameObject &GameObject::operator=(const GameObject& other)
{
    if (this != &other)
    {
        if (other.position != 0)
        {
            if (this->position != 0)
                delete this->position;
            this->position = new Vector2D {other.position->x, other.position->y };
        }
        this->representation = other.representation;
    }
    return *this;
}

////Derivadas da Base 2 - mostrar uso static_cast
// Derivada 1 - Entity
const Entity& Entity::operator= ( const Entity& right )
{
    if (this != &right)
    {
        static_cast<GameObject> (*this) = static_cast<GameObject> (right);
        this->name = right.name;
        this->maxHealth = right.maxHealth;
        this->health = right.health;
        this->stamina = right.stamina;
        this->strength = right.strength;
        this->dexterity = right.dexterity;
        this->bodyParts = right.bodyParts;

        this->copyWeapon( right.equiped_weapon_ptr );
        this->copyInventory( right.inventory_ptr );
    }
    return *this;
}

// Derivada 2 - Player.h
const Player &Player::operator=(const Player& other)
{
    if (this != &other)
    {
        static_cast<Entity> (*this) = static_cast<Entity> (other);

        if (this->attacks.empty())
            this->deleteAttacks();
    
        this->copyAttacks(other);
    }
    return *this;
}

// Derivada 3 - Enemy.h
const Enemy &Enemy::operator=(const Enemy& other)
{
    if (this != &other)
    {
        static_cast<Entity> (*this) = static_cast<Entity> (other);
    }
    return *this;
}

//// Base 3
/**
 * Veja que Battle não é permitido de criar novas entidades
 * ou ataques, mas sim usar o endereço de objetos já existem.
 * Por isso, tome cuidado ao usar esse operador.
*/
const Battle &Battle::operator=(const Battle& other)
{
    if (this != &other)
    {
        if (other.primeiro_ptr != nullptr)
            this->primeiro_ptr = other.primeiro_ptr;
        if (other.segundo_ptr != nullptr)
            this->segundo_ptr = other.segundo_ptr;
        if (other.attack_primeiro_ptr != nullptr)
            this->attack_primeiro_ptr = other.attack_segundo_ptr;
        if (other.attack_segundo_ptr != nullptr)
            this->attack_segundo_ptr = other.attack_segundo_ptr;
    }
    return *this;
}

////Derivadas da Base 3 - mostrar uso static_cast
// Derivada da Base 3 - Boss Batle
/**
 * Não é possível usar static_cast para uma classe abstrata, como é
 * o caso de Battle. O máximo que podemos fazer é 
*/
const BossBattle& BossBattle::operator=(const BossBattle& other)
{
    if (this != &other)
    {
        Enemy* enemy_ptr;
        Player* player_ptr;
        // Is primeiro_ptr a player or an enemy?
        player_ptr = dynamic_cast<Player*> (other.primeiro_ptr);
        if (player_ptr == nullptr)
        {
            enemy_ptr = dynamic_cast<Enemy*> ( other.primeiro_ptr );
            if (enemy_ptr != nullptr)
                this->primeiro_ptr = new Enemy( *enemy_ptr );
        }
        else
        {
            this->primeiro_ptr = new Player( *player_ptr );
        }
        
        // Is segundo_ptr a player?
        player_ptr = dynamic_cast<Player*> (other.segundo_ptr);
        if (player_ptr == nullptr)
        {
            enemy_ptr = dynamic_cast<Enemy*> (other.segundo_ptr);
            if (enemy_ptr != nullptr)
                this->segundo_ptr = new Enemy( *enemy_ptr );
        }
        else
        {
            this->segundo_ptr = new Player( *player_ptr );
        }
        this->turno = other.turno;
    }
    return *this;
}

//// Operators== e !=
//// Base 1
int Interactable::operator==(const Interactable& other)
{
    return ( this->before_interaction == other.before_interaction
            && this->after_interaction == other.after_interaction );
}

int Interactable::operator!=(const Interactable& other)
{
    return !( *this == other );
}

////Derivadas da Base 1 - mostrar uso static_cast
/// Derivada da Base 1 - Item.h
int Item::operator== ( const Item& right )
{
    if ( static_cast<Interactable> (*this) == static_cast<Interactable> (right)
        && this->name == right.name)
        return 1;
    return 0;
}

int Item::operator!= (const Item& right)
{
    return !( *this == right );
}

/// Derivada da Base 1 - Armor.h
int Armor::operator== (const Armor& right )
{
    return ( static_cast<Item> (*this) == static_cast<Item> (right)
            && this->damage_reduction == right.damage_reduction
            && this->weight == right.weight
            && this->min_strength == right.min_strength );
}

int Armor::operator!= (const Armor& right)
{
    return !( *this == right );
}

/// Derivada da Base 1 - Consumable.h
int Consumable::operator== ( const Consumable& right )
{    
    return ( static_cast<Item> (*this) == static_cast<Item> (right) 
            && this->health_factor == right.health_factor );
}

int Consumable::operator!= (const Consumable& right)
{
    return !( *this == right );
}

/// Derivada da Base 1 - Weapon.h
int Weapon::operator== (const Weapon& right )
{
    return ( static_cast<Item> (*this) == static_cast<Item> (right)
            && this->damage == right.damage );
}

//// Base 2 - GameObject.h
int GameObject::operator==(const GameObject& other)
{
    return ( this->representation == other.representation );
}

int GameObject::operator!=(const GameObject& other)
{
    return !( *this == other );
}

////Derivadas da Base 2 - mostrar uso static_cast
/// Derivada da Base 2 - Entity.h
int Entity::operator==(const Entity& right)
{
    if (this->name == right.name
        && static_cast<GameObject> (*this) == static_cast<GameObject> (right))
    {
        return 1;
    }
    return 0;
}

int Entity::operator!=(const Entity& right)
{
    return !( *this == right );
}

/// Derivada da Base 2 - Player.h
bool Player::compareAttacks(const Player& other)
{
    for (size_t i = 0; i < other.attacks.size(); ++i)
    {
        if ( *this->attacks.at(i) != *other.attacks.at(i) )
            return false;
    }
    return true;
}

int Player::operator==(const Player& other)
{
    return ( static_cast<Entity> ( *this ) == static_cast<Entity> (other) 
            && this->compareAttacks( other ) ) ;
}

int Player::operator!=(const Player& other)
{
    return !( *this == other );
}

/// Derivada da Base 2 - Enemy.h

bool Enemy::compareAttacks(const Enemy& other)
{
    bool is_equal = false;
    for ( auto& pair : this->probabilitiesAndAttacks )
    {
        for (auto& other_pair : other.probabilitiesAndAttacks )
        {
            if (pair.first == other_pair.first && *pair.second == *other_pair.second)
            {
                is_equal = true;
                break;
            }
            is_equal = false;
        }
    }
    return is_equal;
}

int Enemy::operator==(const Enemy& other)
{
    return ( static_cast<Entity> ( *this ) == static_cast<Entity> (other)
            && this->compareAttacks( other )) ;
}

int Enemy::operator!=(const Enemy& other)
{
    return !( *this == other );
}

//// Base 3 - Battle.h
// NOTA: Battle é uma classe abstrata, não há porque realizar overload de operador.

////Derivadas da Base 3 - mostrar uso static_cast
// Derivada da Base 3 - NormalBattle.h
int NormalBattle::operator==( const NormalBattle& other )
{
    return ( *this->primeiro_ptr == *other.primeiro_ptr 
            && *this->segundo_ptr == *other.segundo_ptr );
}

int NormalBattle::operator!=( const NormalBattle& other )
{
    return !( *this == other );
}

/// Derivada da Base 3 - BossBattle.h
int BossBattle::operator==( const BossBattle& other )
{
    return ( *this->primeiro_ptr == *other.primeiro_ptr 
            && *this->segundo_ptr == *other.segundo_ptr );
}

int BossBattle::operator!=( const BossBattle& other )
{
    return !( *this == other );
}

//// Operator<<
//// Base 1
ostream &operator<<(ostream& output, const Interactable& inter)
{
    output << "Abstract Interactable object: " << inter.before_interaction
        << " -> " << inter.after_interaction << "\n";
    return output; 
}
////Derivadas da Base 1 - mostrar uso static_cast
/// Derivada da Base 1 - Item.h
ostream& operator<< ( ostream& output, const Item& item )
{
    output << static_cast<Interactable> (item);
    output << item.name << " | " << item.description;
    return output;
}

/// Derivada da Base 1 - Armor.h
ostream& operator<< (ostream& output, const Armor& armor)
{
    output << static_cast<Item> (armor);
    output << "\n======   Armor   =====\n";
    output << "* " << armor.name << "\n";
    output << "* Damage Reduction: \t" << armor.damage_reduction << "\n";
    output << "* Strength required: \t" << armor.min_strength << "\n";
    output << "* Weight: \t" << armor.weight << "\n";
    return output;  
}

/// Derivada da Base 1 - Weapon.h
ostream& operator<< (ostream& output, const Weapon& weapon)
{
    output << static_cast<Item> (weapon);
    output << "\n======   WEAPON   =====\n";
    output << "* " << weapon.name << "\n";
    output << "* Damage: \t" << weapon.damage << "\n";
    output << "* Durability: \t" << weapon.durability << "\n";
    return output;  
}

/// Derivada da Base 1 - Consumable.h
ostream& operator<< ( ostream& output, const Consumable& item )
{
    output << static_cast<Item> (item)
    output << "Consumable: " << item.name << " | " << item.description;
    return output;
}

//// Base 2
ostream &operator<<(ostream& output, const GameObject& object)
{
    output << "Object " << object.getRepresentation() <<
        " at (" << object.getPosition().x << ", " << object.getPosition().y
        << ")\n";
    return output;
}
////Derivadas da Base 2 - mostrar uso static_cast
/// Derivada da Base 2 - Entity.h
ostream &operator<<(ostream& output, const Entity& entity )
{
    output << static_cast<GameObject> (entity);
    output << " === Entity " << entity.name << " === \n";
    output << "Entity: " << entity.name << "\n";
    output << "Health: " << entity.health << "\n";
    output << "Stamina: " << entity.stamina << "\n";
    output << "Strength: " << entity.strength << "\n";
    output << "Dexterity: " << entity.dexterity;
    if (entity.equiped_weapon_ptr == 0)
    {
        output << "\n === Weapon === \n";
        output << " Unarmed \n";
    }
    else
        output << *entity.equiped_weapon_ptr;
    output << " === Body Parts === \n";
    for (const auto& part : entity.bodyParts)
        output << part.partDescription << "\n";
    output << " ======================== \n";
    return output;
}

//>>>Comentário: Por que não tem static_cast aqui

/// Derivada da Base 2 - Enemy.h
ostream &operator<<(ostream& output, const Enemy& enemy)
{
    output << " * Enemy Entity" << enemy.getName() << " *\n";
    output << *(dynamic_cast<const Entity*> (&enemy));  // Static_cast não funciona????
    return output;
}

/// Derivada da Base 2 - Player.h
ostream &operator<<(ostream& output, const Player& player)
{
    output << " * Player Entity" << player.getName() << " *\n";
    // Static cast não funciona aqui???
    output << *(dynamic_cast<const Entity*> (&player));
    return output;
}

//// Base 3 - Battle.h
// NOTA: A classe Battle é abstrata. Todos seus overloads foram feitos na classe concreta!

////Derivadas da Base 3 - mostrar uso static_cast
/// Derivada da Base 3 - NormalBattle.h
ostream &operator<<(ostream& output, const NormalBattle& battle)
{
    output << battle.primeiro_ptr->getName() << " VS. " << battle.segundo_ptr->getName() << "\n";
    output << battle.primeiro_ptr->getHealth() << " | " << battle.segundo_ptr->getHealth() << "\n";
    output << "Turno: " << battle.turno << "\n";
    return output;
}

/// Derivada da Base 3 - BossBattle.h
ostream &operator<<(ostream& output, const BossBattle& battle)
{
    output << battle.primeiro_ptr->getName() << " VS. * " << battle.segundo_ptr->getName() << " * \n";
    output << battle.primeiro_ptr->getHealth() << " | * " << battle.segundo_ptr->getHealth() << " * \n";
    output << "Turno: " << battle.turno << "\n";
    return output;
}

//// Para cada classe do seu projeto criar pelo menos dois constructores, 
 //sendo um o constructor de cópia 
 ////Mostrar uso de reaproveitamento de código da base na derivada

//// Base 1 - Interactable.h - Constructores
////Constructor 1
Interactable::Interactable()
{
    this->before_interaction = 'B';   
    this->after_interaction = 'A';   
}

/// Construtor 2
Interactable::Interactable(char before, char after)
{
    this->setBefore(before);
    this->setAfter(after);
}

////Constructor de cópia
Interactable::Interactable(const Interactable& other)
{
    this->before_interaction = other.before_interaction;
    this->after_interaction = other.after_interaction;
}

//// Base 2 - GameObject - constructores
////Constructor 1
GameObject::GameObject()
{
    this->position = 0;
    this->representation = 'O';
}

////Constructor 2
GameObject::GameObject(Vector2D pos, char representation)
{
    this->setPosition( pos );
    this->setRepresentation( representation );
}

////Constructor de cópia
GameObject::GameObject(const GameObject& other)
{
    if (other.position != 0)
        this->position = new Vector2D { other.position->x, other.position->y };
    this->representation = other.representation;
}

//// Base 3 - Battle.h - constructores
////Constructor 1
Battle::Battle()
{
    this->primeiro_ptr = 0;
    this->segundo_ptr = 0;
    this->turno = 0;
}

////Constructor 2
Battle::Battle(Entity& primeiro, Entity& segundo)
{
    this->primeiro_ptr = &primeiro;
    this->segundo_ptr = &segundo;
    this->turno = 0;
}

////Constructor de cópia 
/* Somente atribuição de ponteiros. Battle não faz nenhuma alocação!*/
Battle::Battle(const Battle& other)
{
    this->primeiro_ptr = other.primeiro_ptr;
    this->segundo_ptr = other.segundo_ptr;
    this->turno = other.turno;
}
////Derivadas - constructores

//// Hierarquia 1

////Classe 1 - Item.h
////Constructor 1
Item::Item() : Interactable()
{
    this->name = Item::DEFAULT_ITEM_NAME;
    this->description = Item::DEFAULT_DESCRIPTION;
}

////Constructor 2
Item::Item( string name, string description) : Interactable()
{
    this->setName(name);
    this->setDescription(description);
}
////Constructor de Cópia
Item::Item( const Item& other ) : Interactable( other )
{
    this->name = other.name;
    this->description = other.description;
}

//// Classe 2 - Armor.h
////Constructor 1
Armor::Armor() : Item()
{
    this->damage_reduction = 0.0f;
    this->min_strength = 0.0f;
    this->weight = 0.0f;
}

////Constructor 2
Armor::Armor(double damage_reduction, double min_strength, double weight) : Item()
{
    this->setDamageReduction( damage_reduction );
    this->setMinStrength( min_strength );
    this->setWeight( weight );
}

////Constructor de Cópia
Armor::Armor( const Armor& other ) : Item( static_cast<Armor> (other) )
{
    this->damage_reduction = other.damage_reduction;
    this->min_strength = other.min_strength;
    this->weight = other.weight;
}
             
//// Classe 3 - Consumable.h
////Constructor 1
Consumable::Consumable() : Item()
{
    this->health_factor = 1.0;
}

////Constructor 2
Consumable::Consumable(string name, string description, double health_factor)
    : Item( name, description )
{
    this->setHealthFactor( health_factor );
}

//>>>Comentário: Ok

////Constructor de Cópia
Consumable::Consumable(const Consumable& other) : Item( static_cast<Item> (other) )
{
    this->health_factor = other.health_factor;
}


//// Classe 3 - Weapon.h
////Constructor 1
Weapon::Weapon() : Item()
{
    this->setName( Weapon::DEFAULT_WEAPON_NAME );
    this->setDamage( 0.0f );
    this->setDurability( 100 );
}

////Constructor 2
Weapon::Weapon(string name, double damage, int durability) : Item()
{
    // cout << "Creating weapon " << name << "...\n";
    this->setName(name);
    this->setDamage(damage);
    this->setDurability(durability);
}

////Constructor de Cópia
Weapon::Weapon( const Weapon& other ) : Item( static_cast<Item> (other) )
{
    this->name = other.name;
    this->damage = other.damage;
    this->durability = other.durability;
}

//// Hierarquia 2

////Classe 1 - Entity
////Constructor 1
/* Cria uma Entidade vazia com valores padrão */
Entity::Entity() : GameObject(  )
{
    this->name      = Entity::DEFAULT_NAME;
    this->health    = 100.0f;
    this->maxHealth = 100.0f;
    this->stamina   = 100.0f;
    this->strength  = 50.0f;
    this->dexterity = 25.0f;

    this->guarding = false;
    this->equiped_weapon_ptr = 0;
    this->bodyParts = DEFAULT_ENTITY_BODY_PARTS;
    this->inventory_ptr = new vector< InventoryItem* >;
}

////Constructor 2
Entity::Entity( string name,
                double health,
                double stamina,
                double strength,
                double dexterity,
                Vector2D position,
                vector< BodyPart > bodyParts ) : GameObject( position, 'E' )
{
    this->setName( name );
    this->setMaxHealth( health );
    this->setHealth( health );
    this->setStamina( stamina );
    this->setStrength( strength );
    this->setDexterity( dexterity );


    this->guarding = false;
    this->equiped_weapon_ptr = 0;

    this->setBodyParts( bodyParts );
    this->inventory_ptr = new vector< InventoryItem* >;
}

////Constructor de Cópia
Entity::Entity( const Entity& other ) : GameObject( static_cast<GameObject> (other) )
{
    this->name = other.name;
    this->health = other.health;
    this->maxHealth = other.maxHealth;
    this->stamina = other.stamina;
    this->dexterity = other.dexterity;

    this->guarding = other.guarding;

    this->copyWeapon( other.equiped_weapon_ptr );
    this->copyInventory( other.inventory_ptr );

    this->bodyParts = other.bodyParts;
}

////Classe 2 - Player
////Constructor 1
Player::Player() : Entity()
{
    Player::numPlayers++;
}

////Constructor 2
Player::Player( string name,
                double health,
                double stamina,
                double strength,
                double dexterity,
                Vector2D position,
                vector< BodyPart > bodyParts )
: Entity( name, health, stamina, strength, dexterity, position, bodyParts )
{
    Player::numPlayers++;
}

////Constructor de Cópia
Player::Player( const Player& other )
: Entity ( static_cast<Entity> (other) )
{
    this->copyAttacks( other );
    Player::numPlayers++;
}

////Classe 3 - Enemy
////Constructor 1
Enemy::Enemy() : Entity()
{   
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";

    numEnemies++;
}

////Constructor 2
Enemy::Enemy(   string name,
                double health,
                double stamina,
                double strength,
                double dexterity,
                Vector2D position,
                vector< BodyPart > bodyParts,
                map< int, Attack* > attacks_and_probabilities )
: Entity( name, health, stamina, strength, dexterity, position, bodyParts )
{
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";

    probabilitiesAndAttacks = map< int, Attack* > ();

    numEnemies++;
}

////Constructor de Cópia
Enemy::Enemy( const Enemy& other ) : Entity( static_cast<Entity> (other) )
{
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";
    numEnemies++;

    // Copia map
    if (!other.probabilitiesAndAttacks.empty())
    {
        for ( auto& prob_and_attacks : other.probabilitiesAndAttacks )
        {
            std::cout << *prob_and_attacks.second << std::endl;
            this->addAttackAndProbability(
                new Attack (*prob_and_attacks.second), prob_and_attacks.first
            );
        }
    }
}

//// Hierarquia 3

////Classe 1 - NormalBattle.h
////Constructor 1
// Nota: Perdão pelos construtores professor. Porque Battle não faz nenhum tipo
// Nota: de alocação. Não fazia muito sentido aplicar construtores mais complexos.
// Nota: Isso era necessário para que eu pudesse usar BossBattle como uma classe
// Nota: concreta de Battle.
NormalBattle::NormalBattle() : Battle()
{
}

////Constructor 2
NormalBattle::NormalBattle(Entity& primeiro, Entity& segundo) : Battle( primeiro, segundo )
{
}

////Constructor de Cópia
NormalBattle::NormalBattle(const NormalBattle& battle) : Battle( battle )
{
}

////Classe 2 - BossBattle.h
////Constructor 1
BossBattle::BossBattle() : Battle()
{
    this->phase_number = 0;
}

BossBattle::BossBattle(Entity& primeiro ) : Battle()
{
    this->setPrimeiro( primeiro );
    this->phase_number = 0;
}

////Constructor de cópia
void BossBattle::copyBossPhases(const BossBattle& other)
{
    if (other.boss_phases.empty())
        return;
    for (auto& phase : other.boss_phases )
        this->add_phase( *phase );
}

BossBattle::BossBattle(const BossBattle& other) : Battle( other )
{
    this->phase_number = other.phase_number;
    this->segundo_ptr = other.segundo_ptr;
    this->copyBossPhases( other );
}

//>>>Comentário: era para mostrar o código de carregamento e salvamento

//// Carregamento e salvamento de arquivos
    /*É necessário ter a funcionalidade: 1. 
      leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
      processamento das variáveis de status e 3. salvamento dessas variáveis. 
      Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/

//Link arquivo de configuração no repositório
src/Weapons/
src/Attacks/ 
    //Link vídeo mostrando a execução do código usando o arquivo de configuração
https://youtu.be/Sn9s7rKg81k

//>>>Comentário: esse vídeo era apenas para demostrar o uso. No outro era que
//você explicaria o código.
