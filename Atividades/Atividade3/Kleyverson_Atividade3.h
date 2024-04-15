/*Criar uma segunda classe. Todas as classes devem ter sempre dois contructores, 
sendo um de cópia, um atributo e um método que não  seja set ou get. 

Criar dois atributos static que não sejam arrays e nem const. 
Eles devem ser instanciados e usados efetivamente nas classes. 

Criar um atributo const static e mostrar o uso dentro da classe. 

Criar dois métodos static e mostrar o uso no main. 

Ter pelo menos um método inline nas suas classes. 

Criar dois arrays dentro da classe, sendo um deles um const static. 
Mostrar o uso desses arrays na classe - não apenas inicialização e preenchimento. 

Usar pelo menos dois loops, um for e um while, na sua classe. 

Todo set que recebe uma string deve limitar o tamanho da string usando o método substr.
Para fazer o diagrama usar o https://www.planttext.com/.
Não colocar sets e gets no diagrama UML (mas precisam estar no código no repositório). 
Sem o diagrama UML e vídeo o trabalho não será avaliado.*/

//// Criar uma segunda classe. Todas as classes devem ter sempre dois contructores, 
//sendo um de cópia, um atributo e um método que não  seja set ou get.

      //O .h da classe 1 sem o set e gets
      class Individual
      {
      public:
            Individual(); // Construtor vazio
            Individual(string, string, double, double, double);
            Individual(const Individual &); // Constructor de cópia
            ~Individual(); // Destructor
            void restoreHp(double);
            double buyItem(double) const;
            void print() const;

      private:
            string name; // std::string
            string breed;
            double hp;
            double strength;
            double money;
            const int MAXSIZENAME = 10;
            const int MAXSIZEBREED = 5;
      };

      //O .h da classe 2 sem o set e gets
      class Weapon
      {
      public:
            Weapon(double,double,string,string); // Primeiro constructor
            Weapon(const Weapon &); // Constructor de cópia

            void restoreWeapon();
            
            // Métodos relacionados aos arrays
            void exibirClassificacoes() const;
            void definirValorMedidas ();
            void exibirMedidas() const;
            void print();

      private:
            double durability;
            double strength;
            string type;
            string range;
            int restorations; // Nº de restauções feitas
            
            static int numRestores; // Nº máximo de restaurações
            static int numWeapons;
            
             // Classificação das armas: S, A, B, C, D
            // Criar um método que mostre as classificações das armas
            static const int NUMCLASSIFICACAOARMAS = 5;
            static const string CLASSIFICACOES[ NUMCLASSIFICACAOARMAS ];
            
            
            // Comprimento, largura, peso
            // Criar um método que mostre as medidas das armas
            static const int NUMDEMEDIDAS = 3;
            static string medidas[ NUMDEMEDIDAS ];
            double valorMedidas[ NUMDEMEDIDAS ];
      };
     
      //Uso no main das duas classes
      // Classe 1
          // Criando um objeto const a partir do constructor vazio
          const Individual elfMage;
          elfMage.print();
      
          // Criando um objeto a partir do segundo constructor
          Individual healer("Kley","Elfo",50,30,600);
          healer.print();
      
          // Criando um objeto a partir do constructor de cópia
          Individual otherHealer(healer);
          otherHealer.print();
      
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
      
          otherHealer.restoreHp(80);
          cout << "O HP aumentou para " << otherHealer.getHp() << "\n\n";
      
          cout << "Saldo atual: " << otherHealer.getMoney() << "\n\n";
          double saldo = otherHealer.buyItem(500);
          otherHealer.setMoney(saldo);
      
          otherHealer.print();

      // Classe 2
          Weapon excalibur(100,70,"espada","medio");
          excalibur.print();
      
          Weapon otherExcalibur(excalibur);
          otherExcalibur.restoreWeapon();
          otherExcalibur.restoreWeapon();
          otherExcalibur.restoreWeapon();
          otherExcalibur.restoreWeapon();
          cout << "Restorations: " << otherExcalibur.getRestorations() << "\n\n";
      
          otherExcalibur.restoreWeapon();
          cout << "Restorations: " << otherExcalibur.getRestorations();
      
          cout << "\n\nNumero maximo de restauracoes que podem ser realizadas: " << Weapon::getNumRestores();
      
          Weapon shinExcalibur(otherExcalibur);
      
          cout << "\n\nNumero de armas ja criadas: " << Weapon::getNumWeapons();
          cout << "\n\n";
      
          shinExcalibur.exibirClassificacoes();
          cout << "\n";
          shinExcalibur.definirValorMedidas();
          cout << "\n";
          shinExcalibur.exibirMedidas();
          cout << "\n";


//// Criar dois atributos static que não sejam arrays e nem const. 
//Eles devem ser instanciados e usados efetivamente nas classes. 

      //No .h da classe
      static int numRestores; // Nº máximo de restaurações
      static int numWeapons;

      //Inicialização
      int Weapon::numRestores = 3;
      int Weapon::numWeapons = 0;

      //Uso efetivo nos métodos
      inline static int getNumRestores() { return numRestores; }
      inline static int getNumWeapons() { return numWeapons; }

      //Uso desses métodos no main
      cout << "\n\nNumero maximo de restauracoes que podem ser realizadas: " << Weapon::getNumRestores();
      cout << "\n\nNumero de armas ja criadas: " << Weapon::getNumWeapons();

//// Criar um atributo const static e mostrar o uso dentro da classe.

      //No .h da classe
      static const int NUMCLASSIFICACAOARMAS = 5;
      static const string CLASSIFICACOES[ NUMCLASSIFICACAOARMAS ];

      //Inicialização 
      const string Weapon::CLASSIFICACOES[ NUMCLASSIFICACAOARMAS ] = {"S","A","B","C","D"};

      //Uso efetivo nos métodos
      void Weapon::exibirClassificacoes() const{
            cout << "As armas podem ser classificadas em:\n";
            for(int i = 0; i < NUMCLASSIFICACAOARMAS; i++)
            {
                  cout << CLASSIFICACOES[ i ] << "\n"; 
            }
      }

      //Uso desses métodos no main
      hinExcalibur.exibirClassificacoes();

//// Criar dois métodos static e mostrar o uso no main. 

      //No .h da classe
      inline static int getNumRestores() { return numRestores; }
      inline static int getNumWeapons() { return numWeapons; }

      //Implementação
    
      //Uso desses métodos no main
      cout << "\n\nNumero maximo de restauracoes que podem ser realizadas: " << Weapon::getNumRestores();
      Weapon shinExcalibur(otherExcalibur);
      cout << "\n\nNumero de armas ja criadas: " << Weapon::getNumWeapons();


//// Ter pelo menos um método inline nas suas classes. 

      //No .h da classe
      inline static int getNumRestores() { return numRestores; }

      //Implementação
    
      //Uso desses métodos no main
      cout << "\n\nNumero maximo de restauracoes que podem ser realizadas: " << Weapon::getNumRestores();
      Weapon shinExcalibur(otherExcalibur);

//// Criar dois arrays dentro da classe, sendo um deles um const static. 
//Mostrar o uso desses arrays na classe - não apenas inicialização e preenchimento. 

      //No .h da classe
      static const int NUMCLASSIFICACAOARMAS = 5;
      static const string CLASSIFICACOES[ NUMCLASSIFICACAOARMAS ];
      
      
      // Comprimento, largura, peso
      static const int NUMDEMEDIDAS = 3;
      static string medidas[ NUMDEMEDIDAS ];
      double valorMedidas[ NUMDEMEDIDAS ];

      //Inicialização 
      const string Weapon::CLASSIFICACOES[ NUMCLASSIFICACAOARMAS ] = {"S","A","B","C","D"};
      string Weapon::medidas [ NUMDEMEDIDAS] = {"Comprimento","Largura","Peso"};

      //Uso efetivo nos métodos - não apenas preenchimento
      void Weapon::exibirClassificacoes() const{
          cout << "As armas podem ser classificadas em:\n";
          for(int i = 0; i < NUMCLASSIFICACAOARMAS; i++)
          {
              cout << CLASSIFICACOES[ i ] << "\n"; 
          }
      }
      
      void Weapon::definirValorMedidas()
      {
          // Comprimento, largura, peso
          // Exemplo
          double value[] = {79,15,3};
          for(int i = 0; i < NUMDEMEDIDAS; i++)
          {
              valorMedidas[i] = value[i];
          }
      }
      
      void Weapon::exibirMedidas() const
      {
          cout << "As medidas da arma sao:\n";
          int i = 0;
          while(i < NUMDEMEDIDAS)
          {
              cout << medidas[i] <<": "<< valorMedidas[i] << "\n";
              i++;
          }
      }

      //Uso desses métodos no main
      shinExcalibur.exibirClassificacoes();
      cout << "\n";
      shinExcalibur.definirValorMedidas();
      cout << "\n";
      shinExcalibur.exibirMedidas();


//// Usar pelo menos dois loops, um for e um while, na sua classe.

      //No cpp da classe
      for(int i = 0; i < NUMCLASSIFICACAOARMAS; i++)
      {
            cout << CLASSIFICACOES[ i ] << "\n"; 
      }

      double value[] = {79,15,3};
      for(int i = 0; i < NUMDEMEDIDAS; i++)
      {
            valorMedidas[i] = value[i];
      }

      int i = 0;
      while(i < NUMDEMEDIDAS)
      {
            cout << medidas[i] <<": "<< valorMedidas[i] << "\n";
            i++;
      }
    
      //Uso no main dos métodos que tem os loops
      shinExcalibur.exibirClassificacoes();
      cout << "\n";
      shinExcalibur.definirValorMedidas();
      cout << "\n";
      shinExcalibur.exibirMedidas();


/* Todo set que recebe uma string deve limitar o tamanho da string usando o método substr. Para fazer o diagrama usar o https://www.planttext.com/.
Não colocar sets e gets no diagrama UML (mas precisam estar no código no repositório). 
Sem o diagrama UML e vídeo o trabalho não será avaliado.


