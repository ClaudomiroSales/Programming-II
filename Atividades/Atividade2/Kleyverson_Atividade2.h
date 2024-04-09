/*Na classe atual implementar ter pelo menos três constructores, sendo dois deles o 
constructor vazio e o constructor de cópia. A classe deve ter pelo menos 
dois atributos não-const, sendo um deles uma string, e um ATRIBUTO const. 
Criar para cada atributo os métodos set e get. A classe deve ter dois métodos 
que não sejam set e get, um que seja const e outro não const. 
No main mostrar o uso da classe com objetos CONST e não-const da sua classe. 
Todo set que recebe uma string deve limitar o tamanho da string usando o método substr.
Para fazer o diagrama usar o https://www.planttext.com/. 
Não colocar sets e gets no diagrama UML.
Sem o diagrama UML e vídeo o trabalho não será avaliado.*/

//// Três constructores, sendo dois deles o constructor vazio e o constructor de cópia.

     //No .h da classe
     Individual(); // Construtor vazio
     Individual(string, string, double, double, double);
     Individual(const Individual &); // Constructor de cópia

     //Implementação no cpp da classe
     Individual::Individual()
     {
       cout << "Inicializando Individaul no constructor vazio.\n";
       name = "Maria"; // Nome padrão
       breed = "Elfo";
       hp = 100;
       strength = 70;
       money = 500;
     }

     Individual::Individual(string myName,string myBreed,double myHp,double myStrength,double myMoney)
     {
       cout << "Inicializando Individaul no segundo constructor.\n";
       name = myName;
       breed = myBreed;
       hp = myHp;
       strength = myStrength;
       money = myMoney;
     }

     Individual::Individual(const Individual& other)
     {
       cout << "Inicializando Individaul no constructor de copia.\n";
       this->name = other.name;
       this->breed = other.breed;
       this->hp = other.hp;
       this->strength = other.strength;
       this->money = other.money;
     }

     //Uso no main dos três constructores
     const Individual elfMage;
     Individual healer("Kley","Elfo",50,30,600);
     Individual otherHealer(healer);

//// Dois atributos não-const, sendo um deles uma string, e um ATRIBUTO const.

     //No .h da classe
     string name; // std::string
     double hp;
     const int MAXSIZENAME = 10;

     //Inicialização nos contructores
     Individual::Individual()
     {
       //...
       name = "Maria"; // Nome padrão
       hp = 100;
     }

     Individual::Individual(string myName,string myBreed,double myHp,double myStrength,double myMoney)
     {
       //...
       name = myName;
       hp = myHp;
     }

     Individual::Individual(const Individual& other)
     {
       //...
       this->name = other.name;
       this->hp = other.hp;
     }

     //Uso nos métodos
     void Individual::setName(string myName)
     {
       if (myName.length() > MAXSIZENAME)
       {
         name = myName.substr(0,MAXSIZENAME);
         cout << "Nome alterado, mas excedeu o tamanho minimo. \n";
         return;
       }
     
       name = myName;
     }

     void Individual::restoreHp(double refill)
     {
       this->hp+=refill;
     }

     void Individual::print( ) const
     {
       //...
       cout << "Nome: " << name << "\n";
       cout << "HP: " << hp << "\n";
     }

//// Criar para cada atributo os métodos set e get

     /*Todo set que recebe uma string deve limitar o tamanho da 
     string usando o método substr.*/

     //No .h da classe
     void setName(string);
     void setBreed(string);
     void setHp(double);
     void setStrength(double);
     void setMoney(double);

     string getName() const;
     string getBreed() const;
     double getHp() const;
     double getStrength() const;
     double getMoney() const;

     //Implementação no cpp da classe
     void Individual::setName(string myName)
     {
       if (myName.length() > MAXSIZENAME)
       {
         name = myName.substr(0,MAXSIZENAME);
         cout << "Nome alterado, mas excedeu o tamanho minimo. \n";
         return;
       }
     
       name = myName;
     }
     
     void Individual::setBreed(string myBreed)
     {
       if (myBreed.length() > MAXSIZEBREED)
         {
           breed = myBreed.substr(0,MAXSIZEBREED);
           cout << "Tipo da raca alterado, mas o nome excedeu o tamanho minimo. \n";
           return;
         }
     
         breed = myBreed;
     }
     
     void Individual::setHp(double myHp)
     {
       this->hp = myHp;
     }
     
     void Individual::setStrength(double myStrength)
     {
       this->strength = myStrength;
     }
     
     void Individual::setMoney(double myMoney)
     {
       this->money = myMoney;
     }
     
     string Individual::getName() const
     {
       return name;
     }
     
     string Individual::getBreed() const
     {
       return breed;
     }
     
     double Individual::getHp() const
     {
       return hp;
     }
     
     double Individual::getStrength() const
     {
       return strength;
     }
     
     double Individual::getMoney() const
     {
       return money;
     }

     //Uso dos sets e gets no main
     cout << "Nome antigo: " << otherHealer.getName() << "\n";
     otherHealer.setName("Kleyversonnnnnn");
     cout << "Novo nome: " << otherHealer.getName() << "\n\n";

     cout << "Raca antiga: " << otherHealer.getBreed() << "\n";
     otherHealer.setBreed("Humano");
     cout << "Nova raca: " << otherHealer.getBreed() << "\n\n";

     cout << "Forca antiga: " << otherHealer.getStrength() << "\n";
     otherHealer.setStrength(50);
     cout << "Nova forca: " << otherHealer.getStrength() << "\n\n";

     cout << "HP antigo: " << otherHealer.getHp() << "\n";
     otherHealer.setHp(100);
     cout << "Novo HP: " << otherHealer.getHp() << "\n\n";

     cout << "O HP aumentou para " << otherHealer.getHp() << "\n\n";

     cout << "Saldo atual: " << otherHealer.getMoney() << "\n\n";
     otherHealer.setMoney(saldo);


//// A classe deve ter dois métodos, um que seja const e outro não const.

     //Método const no .h da classe
     double buyItem(double) const;

     //Implementação do método const no .cpp
     double Individual::buyItem(double itemValue) const
     {
       double saldo = this->money;
     
       if(itemValue > this->money)
       {
         cout << "Dinheiro insuficiente\n\n";
         return saldo;
       }
     
       saldo-=itemValue;
       cout << "Parabens pela compra!\n\n";
       
       return saldo;
     }

     //Uso do método const no main
     double saldo = otherHealer.buyItem(500);
     
     //Método não-const no .h da classe
     void restoreHp(double);

     //Implementação do método não-const no .cpp
     void Individual::restoreHp(double refill)
     {
       this->hp+=refill;
     }

     //Uso do método não-const no main
     otherHealer.restoreHp(80);

//// No main mostrar o uso da classe com objetos CONST e não-const da sua classe
     // Criando um objeto const a partir do constructor vazio
     const Individual elfMage;
     elfMage.print();
     
     // Criando um objeto a partir do segundo constructor
     Individual healer("Kley","Elfo",50,30,600);
     healer.print();

     // Criando um objeto a partir do constructor de cópia
     Individual otherHealer(healer);
     otherHealer.print();

