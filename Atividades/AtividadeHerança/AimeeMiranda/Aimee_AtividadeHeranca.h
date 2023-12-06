/*Criar três hierarquia, sendo duas de três níveis, como explicado em sala e 
no Classroom. Fazer a sobrecarga para cada classe dos operadores =, ==, ≠, ! e << 
(friend). Usar sempre que possível o static_cast para reaproveitamento de código. 
Para cada classe do seu projeto criar pelo menos três constructores, 
sendo um o constructor de cópia. É necessário ter a funcionalidade: 1. 
leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
processamento das variáveis de status e 3. salvamento dessas variáveis. 
Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/


//// Geral - parte para revisão
    //Diagrama UML    
        //>>>Comentário: era para ter dois. Um geral e outro só com os 
        //relacionamentos. Não foi seguido.
    //Organização do código 
        //>>>Comentário: Não segue algumas normas de código: operador << está em 
        //em uma posição incorreta

    //>>>Comentário: Não tem nada de static_cast. Não tem métodos que especializam
    //a classe

//// O .h das classes bases


////Classe base 1    

class Jogador
{
    public:
        
        Jogador(int); //cria nome de jogador aleatorio
        Jogador(string); //informa nome de jogador
        Jogador(string, int, int, int, vector<int>, int, vector<int>); //load Jogador
        Jogador(const Jogador&); //construtor de copia
        //~Jogador(); //destrutor 

        ...       
        
        //>>>Comentário: posição incorreta
        friend ostream& operator<<(ostream& os, const Jogador& jogador);
        

        //>>>Comentário: era para ter apenas o operador acima que faz o mesmo
        void printTerritoriosConquistados( Tabuleiro tabuleiro);
        
        ...
        
        
        string iniciarAtaque();
        string atacarTerritorio(Tabuleiro *tabuleiroPtr);
        string fortificarTerritorio(string territorioA, string territorioB);
        string redirecionarTerritorio(string territorioA, string territorioB);
        static string encerrarAtaque();
        
        inline bool isPrimeiraRodada() const {return qtdRodada == 0 ? true: false;}; //adicionar no diagrama

    private:
        const string NOME;

        static int qtdRodada;
        static int qtdExercitosReserva;
        static int qtdExercitosTotal;
        static vector<int> idTerritoriosConquistados;
        static vector<int> idCartasTerritorio;
        const string OBJETIVOSECRETO;
};

//>>>Comentário: Não tem nada na classe Exercito só constructores

     ////Classe base 2


class Exercito
{
    public:
        Exercito();
        Exercito(const Exercito& outro); //construtor de copia
        ~Exercito(); //destrutor

    private:
};

//>>>Comentário: Não tem nada na classe Carta só constructores

     ////Classe base 3


class Carta
{
    public:
        Carta();
        Carta(const Carta& outro); //construtor de copia
        ~Carta(); //destrutor

    private:
};



-------------------------------JOGADOR-------------------------------

//>>>Comentário: Não tem nada na classe Maquina só constructores. E idem para o resto

//// O .h da hierarquia 1

class Maquina : public Jogador
{
    public:
        Maquina();
        Maquina(const Maquina& outro); //construtor de copia
        ~Maquina(); //destrutor

    private:
};


     ////Classe 2

class Humano : public Jogador
{
    public:
        Humano();
        Humano(const Humano& outro); //construtor de copia
        ~Humano(); //destrutor

    private:
};


     ///E assim por diante

-------------------------------EXERCITO-------------------------------
//// O .h da hierarquia 2

     ////Classe 1

class Armamento: public Exercito
{
    public:
        Armamento();
        Armamento(const Armamento& outro); //construtor de copia
        ~Armamento(); //destrutor

    private:
};


     ////Classe 2

class Tropa: public Exercito
{
    public:
        Tropa();
        Tropa(const Tropa& outro); //construtor de copia
        ~Tropa(); //destrutor

    private:
};


     ///E assim por diante

-------------------------------CARTA-------------------------------
//// O .h da hierarquia 3

     ////Classe 1


class CartaTerritorio: public Carta
{
    public:
        CartaTerritorio();
        CartaTerritorio(const CartaTerritorio& outro); //construtor de copia
        ~CartaTerritorio(); //destrutor

    private:
};


     ////Classe 2

class ObjetivoSecreto : public Carta
{
    public:
        ObjetivoSecreto();
        ObjetivoSecreto(const ObjetivoSecreto& outro); //construtor de copia
        ~ObjetivoSecreto(); //destrutor

    private:
};


     ///E assim por diante

//>>>Comentário: Não feito

//// Mostrar implementação de método que especializa a derivada
 /// Mostrar reaproveitamente de código da base

-------------------------------HUMANO-------------------------------
    //// Hierarquia 1

         ////Classe 1


class Democracia : public Humano
{
    public:
        Democracia();
        Democracia(const Democracia& outro); //construtor de copia
        ~Democracia(); //destrutor

    private:
};


         ////Classe 2

class Imperio : public Humano
{
    public:
        Imperio();
        Imperio(const Imperio& outro); //construtor de copia
        ~Imperio(); //destrutor

    private:
};


         ///E assim por diante

-------------------------------ARMAMENTO-------------------------------
    //// Hierarquia 2

         ////Classe 1


class Biologico: public Armamento
{
    public:
        Biologico();
        Biologico(const Biologico& outro); //construtor de copia
        ~Biologico(); //destrutor

    private:
};


         ////Classe 2

class Cyber: public Armamento
{
    public:
        Cyber();
        Cyber(const Cyber& outro); //construtor de copia
        ~Cyber(); //destrutor

    private:
};


         ////Classe 3

class Fisico: public Armamento
{
    public:
        Fisico();
        Fisico(const Fisico& outro); //construtor de copia
        ~Fisico(); //destrutor

    private:
};


         ///E assim por diante

-------------------------------TROPA-------------------------------
    //// Hierarquia 3

         ////Classe 1


class Aerea: public Tropa
{
    public:
        Aerea();
        Aerea(const Aerea& outro); //construtor de copia
        ~Aerea(); //destrutor

    private:
};


         ////Classe 2

class Marinha: public Tropa
{
    public:
        Marinha();
        Marinha(const Marinha& outro); //construtor de copia
        ~Marinha(); //destrutor

    private:
};


         ////Classe 3

class Terrestre: public Tropa
{
    public:
        Terrestre();
        Terrestre(const Terrestre& outro); //construtor de copia
        ~Terrestre(); //destrutor

    private:
};

//>>>Comentário: considerando esse h. posso considerar que a sua tarefa não foi feita


         ///E assim por diante



//// Fazer a sobrecarga para todas as classes dos operadores =, ==, ≠ e << (friend)

     //// Operator=
         //// Base 1

             ////Derivadas da Base 1 - mostrar uso static_cast

         //// Base 2

             ////Derivadas da Base 2 - mostrar uso static_cast

        //// Base 3

             ////Derivadas da Base 3 - mostrar uso static_cast


     //// Operators== e !=
         //// Base 1

             ////Derivadas da Base 1 - mostrar uso static_cast

         //// Base 2

             ////Derivadas da Base 2 - mostrar uso static_cast

        //// Base 3

             ////Derivadas da Base 3 - mostrar uso static_cast

     //// Operator<<
        //// Base 1

            ////Derivadas da Base 1 - mostrar uso static_cast

        //// Base 2

            ////Derivadas da Base 2 - mostrar uso static_cast

       //// Base 3

            ////Derivadas da Base 3 - mostrar uso static_cast


//// Para cada classe do seu projeto criar pelo menos dois constructores, 
 //sendo um o constructor de cópia 
 ////Mostrar uso de reaproveitamento de código da base na derivada

    //// Base 1 - constructores
        ////Constructor 1

        ////Constructor de cópia

    //// Base 2 - constructores
        ////Constructor 1

        ////Constructor de cópia

    //// Base 3 - constructores
        ////Constructor 1

        ////Constructor de cópia 

    ////Derivadas - constructores

        //// Hierarquia 1

             ////Classe 1
                 ////Constructor 1

                 ////Constructor de cópia

             ////Classe 2
                 ////Constructor 1

                 ////Constructor de cópia
             
             ///E assim por diante


        //// Hierarquia 2

             ////Classe 1
                 ////Constructor 1

                 ////Constructor de cópia

             ////Classe 2
                 ////Constructor 1

                 ////Constructor de cópia

             ///E assim por diante


      //// Hierarquia 2

             ////Classe 1
                 ////Constructor 1

                 ////Constructor de cópia

             ////Classe 2
                 ////Constructor 1

                 ////Constructor de cópia

             ///E assim por diante

//>>>Comentário: era para colocar o código aqui

//// Carregamento e salvamento de arquivos
    /*É necessário ter a funcionalidade: 1. 
      leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
      processamento das variáveis de status e 3. salvamento dessas variáveis. 
      Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/

    //Link arquivo de configuração no repositório
    https://github.com/Eemiaa/Game-WAR-PROJECT/tree/dev-2.0/Database

//>>>Comentário: era para ser uma demostração. Mostrava o arquivo. Alterava ele
// e depois rodava o cógigo. Alterava novamente e rodava o código.
// Conforme foi feito em sala

    //Link vídeo mostrando a execução do código usando o arquivo de configuração
    https://drive.google.com/file/d/1H93uBx3aXKLE_Hc5DNM-liFuhsE4IpUC/view?usp=sharing