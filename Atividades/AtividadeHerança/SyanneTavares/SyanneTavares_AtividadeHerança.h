//>>>Comentário: Ótimo

// hierarquia 1 
#include "Quests.h" // nível 1
#include "DailyTasks.h" // nível 2
#include "GeneralMissions.h" // nível 2
// hierarquia 2
#include "Stories.h" // nível 1

#include "RelationshipStories.h" //nivel 2

#include "FriendshipActions.h" //nivel 2 -> nivel 3
#include "RomanticActions.h" //nivel 2 -> nivel 3

#include "CareerStories.h" //nivel 2

//hierarquia 3
#include "Location.h"
#include "Building.h"
#include "Workplace.h"
#include "LeisurePlace.h"
#include "SimsHouse.h"

/*Criar três hierarquia, sendo duas de três níveis, como explicado em sala e 
no Classroom. Fazer a sobrecarga para cada classe dos operadores =, ==, ≠, ! e << 
(friend). Usar sempre que possível o static_cast para reaproveitamento de código. 
Para cada classe do seu projeto criar pelo menos três constructores, 
sendo um o constructor de cópia. É necessário ter a funcionalidade: 1. 
leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
processamento das variáveis de status e 3. salvamento dessas variáveis. 
Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/


//// Geral - parte para revisão
    //Diagrama UML    - ok mas o só com a relação não precisa dos métodos e atributos
    //Organização do código - organização do código impecável

//// O .h das classes bases

//>>>Comentário: concluirMissao é apenas um print

     ////Classe base 1
    class Quests {

        friend ostream& operator<<(ostream& out, const Quests& mission);

    public:
        Quests();
        Quests(const string& nome, const string icon = "",int rewardsSimsCash=25);
        Quests(const Quests& other);
        ~Quests();

        ...

        void concluirMissao();

        // Operadores
        Quests& operator=(const Quests& other);
        bool operator==(const Quests& other) const;
        bool operator!=(const Quests& other) const;
        bool operator!() const;

        
    private:
        string nome;
        string icon;
        int rewardsSimsCash;
        bool concluida;

        // Limitar o tamanho das strings
        static const int MAX_STRING_LENGTH = 100;

        // Função auxiliar para limitar o tamanho da string
        string limitarTamanhoString(const string& str);
    };

    //>>>Comentário: Stories não tem métodos

     ////Classe base 2
    class Stories {
        friend ostream& operator<<(ostream& out, const Stories& story);
    public:
        Stories();
        Stories(const string&, const string&, const string&,const map<int,string>);
        Stories(const Stories& other);
        ~Stories();
       
        
        Stories& operator=(const Stories& other);
        bool operator==(const Stories& other) const;
        bool operator!=(const Stories& other) const;
        bool operator!() const;
        void operator++();//acrescenta 1 a parte


    private:
        string title;
        string subtitle;
        string description;
        map<int,string> capitulos; //recompensa por capítulo
        int parte;
    };

    ////Classe base 3

    //>>>Comentário: Idem Location

        enum emojiRepresentation {
            HOUSES,
            BUILDINGS
        };

        class Location
        {
            friend ostream &operator<<(ostream &, const Location &);

            public:
                Location();
                Location(const Location &other);
                Location(const tuple<int, int> &, const emojiRepresentation &, const string & = "Sem proprietário");
                ~Location();

                ...
               
                // Operadores
                Location &operator=(const Location &);
                bool operator==(const Location &) const;
                bool operator!=(const Location &) const;
                bool operator!() const;
                
            private:
                tuple<int, int> proporcaoTerreno;
                const emojiRepresentation OPTIONMENU;
                string proprietario;
        };

//// O .h da hierarquia 1

     ////Classe 1
    class DailyTasks : public Quests {
        friend ostream& operator<<(ostream& out, const DailyTasks& dailyMission);

    public:
        DailyTasks();
        DailyTasks(const string&, const string&, int);
        DailyTasks(const DailyTasks& other);
        ~DailyTasks();

        void showEndsIn() const;
        bool hasExpired() const;
        // Operadores
        DailyTasks& operator=(const DailyTasks& other);
        bool operator==(const DailyTasks& other) const;
        bool operator!=(const DailyTasks& other) const;
        bool operator!() const;

        string tempoRestanteAteFinalDoDia() const;

    private:
        Data endsIn;
    };

     ////Classe 2
    //>>>Comentário: aqui está um pouco melhor


    class GeneralMissions : public Quests {

        friend ostream& operator<<(ostream& out, const GeneralMissions& generalMissions);

    public:
        GeneralMissions();
        GeneralMissions(const string& nome, const string& icon, int recompensa, const string& subtitulo,const string& descricao);
        GeneralMissions(const GeneralMissions& other);
        ~GeneralMissions();

        ...

        // Operadores
        GeneralMissions& operator=(const GeneralMissions& other);
        bool operator==(const GeneralMissions& other) const;
        bool operator!=(const GeneralMissions& other) const;
        bool operator!() const;
            
        void completed();
        void completeObjectiveBonus();

    private:

        string description;
        string subtitle;
    };
     ///E assim por diante

//// O .h da hierarquia 2

    //>>>Comentário: não tem métodos

     ////Classe 1
    class RelationshipStories : public Stories {
        friend ostream& operator<<(ostream& out, const RelationshipStories& story);

    public:
        RelationshipStories();
        RelationshipStories(const string&, const string&, const string&, const map<int, string>&,const string&);
        RelationshipStories(const RelationshipStories& other);
        ~RelationshipStories();

        RelationshipStories& operator=(const RelationshipStories& other);
        bool operator==(const RelationshipStories& other) const;
        bool operator!=(const RelationshipStories& other) const;
        bool operator!() const;

        string getSimInvolved() const {return simInvolved;};

    private:
        string simInvolved;
    };

    ////Classe 2
    //>>>Comentário: Ok

    class CareerStories : public Stories {

        friend ostream& operator<<(ostream& out, const CareerStories& story);

        public:
        
            CareerStories();
            CareerStories(const string&, const string&, const string&, const map<int, string> &,const string &,const string &,const vector<string>&);
            CareerStories(const CareerStories& other);
            ~CareerStories();

            CareerStories& operator=(const CareerStories& other);
            bool operator==(const CareerStories& other) const;
            bool operator!=(const CareerStories& other) const;
            bool operator!() const;
        ...

            void iniciarEvento(Sims*,const eventType&);

        private:

            string worker;
            string workplace;
            int pontosDeCarreira=0;
            static const int MAX_POINTS_CAREER = 100;
            
            static const map<string,int> STANDARD_SHIFT;
            static const map<string,int> QUICK_SHIFT ;

            vector<string> actions;

    };

    ///Classe 1.1
    struct Action
    {
        string actionName;
        int custo; //energia
        int pontosDeEvento;
    }; 

    //>>>Comentário: Ok

    class FriendshipActions : public RelationshipStories {
        friend ostream& operator<<(ostream& out, const FriendshipActions& );

        public:
            FriendshipActions();
            FriendshipActions(const RelationshipStories&, const vector <Action> &);
            FriendshipActions(const FriendshipActions& other);
            ~FriendshipActions();

            FriendshipActions& operator=(const FriendshipActions& other);
            bool operator==(const FriendshipActions& other) const;
            bool operator!=(const FriendshipActions& other) const;
            bool operator!() const;

            void showActions()const ;
            void executeAction (Sims*,int);
           ...
        private:

            const int MAXPONTOSEVENTOS=10;
            int currentPontos;
            vector <Action> actions;
    };
    ///Classe 1.2
    enum Actions {PIADA=1,CANTADA,CONVERSA,BEIJO};

    class RomanticActions : public RelationshipStories {
        
        friend ostream& operator<<(ostream& out, const RomanticActions& );

        public:

            RomanticActions();
            RomanticActions(const RelationshipStories&, const string& );
            RomanticActions(const string&, const string&, const string&, const map<int, string>&,const string&, const string& );
            RomanticActions(const RomanticActions& other);
            ~RomanticActions();

            RomanticActions& operator=(const RomanticActions& other);
            bool operator==(const RomanticActions& other) const;
            bool operator!=(const RomanticActions& other) const;
            bool operator!() const;

            void startEvent(Sims*);
            void setRelationshipStatus(const string &);
            inline string getRelationshipStatus() const { return relationshipStatus; };
            inline string getPair() const { return pair; };

        private:
            string pair;
            string relationshipStatus;
            const int UPCAP=10; // limite pra subir de cap
    };

//// O .h da hierarquia 3

     ////Classe 1
    struct features
    {
        vector <string> comodos;
        int numAndares;
        bool temPiscina;
        string estilo;
    };

    class SimsHouse : public Location
    {
    
        friend ostream &operator<<(ostream &, const SimsHouse &);
    
    public:
        // construtores e destrutores sempre começam a parte pública da classe
        SimsHouse(); // Construtor-> método chamado pra inicializar os atributos a classe
        SimsHouse(const tuple<int,int> & , double,const string & , const string & =""); // declarando o construtor com parâmetros.
        SimsHouse( const SimsHouse & ); //construtor de cópia
        ~SimsHouse();//Destrutor -> relacionado a desalocaçao de memória 

       
      ...
        //Demais métodos 
        void efetuarVenda(Sims &);
        void setFeatures(const vector<string>& ,int,bool,string);
        void addComodo(const string& );
        void removeComodo(const string&);
        void verFeatures() const;

        ...
        static void mostrarVizinhanca();

        //operadores
        const SimsHouse &operator=(const SimsHouse &);  // assign SimsHouse
        int operator==(const SimsHouse &) const; // compare equal
        int operator!=(const SimsHouse &) const; // compare !equal
        bool operator!() const;

    private:

        bool premium;
        double valor; // em simCash
        features housefeatures;

        const string ENDERECO;
        const int MAXTAMSTRINGS= 25;
        //atributos static
        const static double MINVALORPREMIUM;
        const static int MAXNUMENDERECOS = 9; 
        static int numEnderecos;
        static int numLotesPossuidos;// número de casas vendidas
        static string enderecosList[ MAXNUMENDERECOS ];
    };

     ////Classe 2
    class Building : public Location
    {
            friend ostream &operator<<(ostream &, const Building &);

        public:
            Building();
            Building(const tuple<int, int> &, const string & ,const string & = "", const string & = "");
            ~Building();

          ...

            // Método específico
            void chooseBuildingModel();
            ...
            
            // Operadores
            Building &operator=(const Building &);
            bool operator==(const Building &) const;
            bool operator!=(const Building &) const;
            bool operator!() const;
        private:
            string districtName;
            string name;
            string model;

    };
     ///Classe 2.1
    class Workplace : public Building
    {
            friend ostream &operator<<(ostream &, const Workplace &);

        public:
            Workplace();
            Workplace(const tuple<int, int> &, const CareerStories &,const string & = "Sem Proprietário", const string & = "", const string & = "");
            ~Workplace();
...

            void goToWork(Sims *sims);
            // Operadores
            Workplace &operator=(const Workplace &);
            bool operator==(const Workplace &) const;
            bool operator!=(const Workplace &) const;
            bool operator!() const;
        private:
        
            CareerStories careerStorie;

    };
    ///classe 2.2
    class LeisurePlace : public Building
    {
            friend ostream &operator<<(ostream &, const LeisurePlace &);

        public:
        
            LeisurePlace();
            LeisurePlace(const tuple<int, int> &,const string &, const string &,const FriendshipActions&,const RomanticActions&);
            LeisurePlace(const LeisurePlace &other);
            ~LeisurePlace();

           ...
            // Método específico
            void socialize(Sims*);

            // Operadores
            const LeisurePlace &operator=(const LeisurePlace &);
            bool operator==(const LeisurePlace &) const;
            bool operator!=(const LeisurePlace &) const;
            bool operator!() const;

        private:
            vector<Sims> simsList;
            FriendshipActions friendshipActions;
            RomanticActions romanticActions;
    };
//// Mostrar implementação de método que especializa a derivada
 /// Mostrar reaproveitamente de código da base

    //// Hierarquia 1 - Quests
         ////Classe 1 - DailyTasks
        string DailyTasks::tempoRestanteAteFinalDoDia() const {
            // Obtém o relógio atual
            auto agora = system_clock::now();

            // Converte para o tipo de tempo local
            auto tempoLocal = system_clock::to_time_t(agora);
            tm* infoTempo = localtime(&tempoLocal);

            // Calcula o tempo restante até o final do dia
            int horasRestantes = 23 - infoTempo->tm_hour;
            int minutosRestantes = 59 - infoTempo->tm_min;

            // Formata o resultado
            std::stringstream resultado;
            resultado << setw(2) << setfill('0') << horasRestantes << ":"
                    << setw(2) << setfill('0') << minutosRestantes;

            return resultado.str();
        }

         ////Classe 2 - GeneralMission
        void GeneralMissions::completed()
        {
            nCompleted++;
            if (nCompleted == BONUS_MAX){
                completeObjectiveBonus();
                return;
            }
            concluirMissao();
            cout<<*this;
            return;
        }
        void GeneralMissions::completeObjectiveBonus(){

            cout << VERDE<<"\nParabés vc concluíu suas "<<BONUS_MAX<<" primeiras missões!\n"<<RESET<<"\n";
            cout << "\nAs recompensas serão duplicadas!!!\n";

            setRewards(getRewards() * 2);  // Dobrar as recompensas no contexto do jogo
            concluirMissao();
            cout<<*this;
            return;
        }

    //// Hierarquia 2 - Stories

         ////Classe 1 - CarrerStories

        // Método para iniciar um evento padrão
        void CareerStories::iniciarEvento(Sims* sim, const eventType& type) {
            
            map<string, int> typeEvent;
            int points = 0;
            int pointsMaxEvent = (type == QUICKSHIFT)? 15: 60;
            if (sim->getNome() != getSimWorker()) {
                cout << VERMELHO<<"Erro: O Sim não corresponde ao trabalhador associado a este evento.\n"<<RESET;
                return;
            }

            typeEvent = (type == STANDARDSHIFT) ? STANDARD_SHIFT : QUICK_SHIFT;

            while (points< pointsMaxEvent) {
                // Exibir menu de ações
                cout<<"\n+----------------------------------------+\n";
                cout << "Menu de Ações:\n";
                for (size_t i = 0; i < actions.size(); ++i) {
                    cout << i + 1 << ". " << actions[i] << "\n";
                }
                cout << "-1. Finalizar o evento\n";

                int choice;
                cout << "Insira a ação que deseja executar:";
                cin >> choice;

                // Verificar se a entrada é um número
                if (cin.fail()) {
                    cin.clear(); // Limpar o sinal de falha
                    cin.ignore(INT_MAX, '\n'); // Descartar a entrada inválida
                    cout << VERMELHO << "Entrada inválida. Insira um número. Tente novamente.\n" << RESET;
                    continue; // Pular para a próxima iteração do loop
                }

                // Restaurar o buffer do teclado no caso de uma entrada válida
                cin.ignore(INT_MAX, '\n');

                if (choice == -1) {
                    cout << "Evento interrompido\n";
                    break;  // Finalizar o evento
                }

                // Executar ação escolhida
                if (choice >= 1 && static_cast<size_t>(choice - 1) < actions.size()) {
                    // Simular ação entre sims e subtrair energia
                    // Adicionar pontos de evento
                    points += 5;
                    sim->diminuirEnergia(1);

                    system("clear");
                    cout <<VERDE<<"Ação executada: " << actions[choice - 1] << "\n"<<RESET;
                    cout << "Pontos de evento: ⭐ " << points << "\n";

                } else {
                    cout << "Escolha inválida. Tente novamente.\n";
                }
            }

            pontosDeCarreira+=typeEvent["recompensaPC"];
            sim->addSimCash(typeEvent["recompensaSimCash"]);
            sim->addXp(10);

            cout<< "\n+--------------------+\n";
            cout<< VERDE<<"Bom trabalho!!✅\n"<<RESET;
            cout<< "Trabalhar em um turno"<<((type == STANDARDSHIFT)? " normal":" rápido")<<" "<<typeEvent["duracao"]<<"h - recompensas:\n";
            cout<< "❇️ 10 xp\n";
            cout<< "❇️ "<< typeEvent["recompensaSimCash"] <<" SimCash\n";
            cout<< "❇️ "<< typeEvent["recompensaPC"]<<" pontos de carreira.\n";

            // Verificar se os pontos atingiram o limite
            if (getPontosCarreira() >= getMaxPointsCareer())
            {
                //Incrementar a parte da classe base CareerStories
                CareerStories::operator++();
                // Zerar pontos para o próximo evento
                pontosDeCarreira = 0;
            }
        }

        ////Classe 1.1 - FriendshipsActions
        void FriendshipActions::showActions() const {
            cout << "\n| Friendship Actions:\n";
            for (int i = 0; i < actions.size(); ++i) {
                
                cout << i + 1 << ". " << actions[i].actionName;
                cout<< "\nGanha: ⭐ " << actions[i].pontosDeEvento;
                cout <<"\nCusta: ⚡ " << actions[i].custo;
                cout<<"\n+-------------------------------+\n";
            }
        }

        void FriendshipActions::executeAction( Sims *sim, int index) {

            
            cout<<VERDE<<"Executando: "<<actions[index-1].actionName<<"\n"<<RESET;
            if (index-1 >= 0 && static_cast<size_t>(index-1) < actions.size()) {
                currentPontos += actions[index-1].pontosDeEvento;
                sim->setEnergia(sim->getEnergia() - actions[index-1].custo);
                if (currentPontos >= MAXPONTOSEVENTOS) {
                    int recompensa = getRecompensaCap(getParte());
                    //Sims ganha a recompensa por capítulo    
                    sim->setSimCash(sim->getSimCash() + recompensa );
                    sim->addXp(recompensa);
                    // Incrementa a parte da classe base Stories
                    Stories::operator++();
                    // Zera a pontuação pro pŕoxima parte da história
                    currentPontos = 0;
                } 
            }
        }        

        ////Classe 2.2 - RomanticStories
        // Método para iniciar um evento romântico
        void RomanticActions::startEvent(Sims* sim) {
            int points = 0;
            if (sim->getNomeCompleto() != pair){
                resetParte();// reinicia os capítulos caso necessário; 
                pair = sim->getNomeCompleto();
            }
            cout<<getSimInvolved()<<" ❤️ "<< pair <<"\n";
            while (true) {
                // Exibir menu de ações
                cout<<"\n+----------------------------------------+\n";
                cout << "Menu de Ações:\n";
                cout << "1. Contar piada paqueradora " << EMOJI_PIADA << "\n";
                cout << "2. Dar cantada em " << EMOJI_CANTADA << "\n";
                cout << "3. Ficar de conversa fiada " << EMOJI_CONVERSA << "\n";
                cout << "4. Beijar " << EMOJI_BEIJO << "\n";
                cout << "-1. Finalizar o evento\n";

                int choice;
                cout << "Insira a ação que deseja executar:";
                cin >> choice;

                // Verificar se a entrada é um número
                if (cin.fail()) {
                    cin.clear(); // Limpar o sinal de falha
                    cin.ignore(INT_MAX, '\n'); // Descartar a entrada inválida
                    cout << VERMELHO << "Entrada inválida. Insira um número. Tente novamente.\n" << RESET;
                    continue; // Pular para a próxima iteração do loop
                }

                // Restaurar o buffer do teclado no caso de uma entrada válida
                cin.ignore(INT_MAX, '\n');

                if (choice == -1) {
                    break; // Finalizar o evento
                }
                system("clear");
                cout<<VERDE;
                // Executar ação escolhida
                switch (choice) {
                    case PIADA:
                        // Simular ação entre sims e subtrair energia
                        // Adicionar pontos de evento
                        points += 10;
                        cout << "Executando ação: Contar piada paqueradora " << EMOJI_PIADA << "\n";
                        break;
                    case CANTADA:
                        // Simular ação entre sims e subtrair energia
                        // Adicionar pontos de evento
                        points += 10;
                        cout << "Executando ação: Dar cantada em " << EMOJI_CANTADA << "\n";
                        break;
                    case CONVERSA:
                        // Simular ação entre sims e subtrair energia
                        // Adicionar pontos de evento
                        points += 10;
                        cout << "Executando ação: Ficar de conversa fiada " << EMOJI_CONVERSA << "\n";
                        break;
                    case BEIJO:
                        // Simular ação entre sims e subtrair energia
                        // Adicionar pontos de evento
                        points += 10;
                        cout << "Executando ação: Beijar " << EMOJI_BEIJO << "\n";
                        break;
                    default:
                        cout <<VERMELHO<< "Escolha inválida. Tente novamente.\n";
                        break;
                }
                cout<<RESET;
                cout<<"\nPontos de evento:  ⭐ "<<points<<"\n";
                // Verificar se os pontos atingiram o limite
                if (points >= UPCAP) {
                    // Incrementar a parte da classe base Stories
                    Stories::operator++();
                    // Zerar pontos para o próximo evento
                    points = 0;
                    break; // Finalizar o evento
                }
            }
        }

    //// Hierarquia 3 - Location

         ////Classe 1 - SimsHouse

        void SimsHouse::mostrarVizinhanca()
        {
            cout <<
            R"(
        ____          _     _       _                                 _               
        / /\ \  __   _(_)___(_)_ __ | |__   __ _ _ __   ___ __ _   ___(_)_ __ ___  ___ 
        / /  \ \ \ \ / / |_  / | '_ \| '_ \ / _` | '_ \ / __/ _` | / __| | '_ ` _ \/ __|
        \ \  / /  \ V /| |/ /| | | | | | | | (_| | | | | (_| (_| | \__ \ | | | | | \__ \
        \_\/_/    \_/ |_/___|_|_| |_|_| |_|\__,_|_| |_|\___\__,_| |___/_|_| |_| |_|___/
                                                        )_)                            )";

            cout << "\n==========================================\n";
            cout << "\033[1m Monte Salgado\033[0m\n" ;
            cout << numLotesPossuidos << " de " << MAXNUMENDERECOS << " lotes Possuídos"; 
            cout << "\n==========================================\n";
            for ( int i = 0; i < numEnderecos;i++){
                cout << "\033[1;32m ❇️ \033[0m" << enderecosList[i]<< "\n";
            }
            cout << "\n==========================================\n";
        }
        void SimsHouse::verFeatures() const {
            cout << "Características da casa em " << ENDERECO << ":" << "\n";
            cout << "Número de andares: " << housefeatures.numAndares << "\n";
            cout << "Estilo: " << housefeatures.estilo << "\n";
            cout << "Possui piscina: " << (housefeatures.temPiscina ? "Sim" : "Não") << "\n";

            cout << housefeatures.comodos.size()<<" Cômodos:" << "\n";
            for (const string& comodo : housefeatures.comodos) {
                cout << " ❇️ " << comodo << "\n";
            }
        }

         ////Classe 2 - Buldings

            void Building::chooseBuildingModel()
            {

                string simples = R"(
                _
                _|=|__________
                /              \
            /                \
            /__________________\
            ||  || /--\ ||  ||
            ||[]|| | .| ||[]||
            ()||__||_|__|_||__||()
            ( )|-|-|-|====|-|-|-|( ) 
            ^^^^^^^^^^====^^^^^^^^^^^

                )";

                string classico =  R"(

                _._._._       _._._._       _._._._ 
                | ___ |_._._._| ___ |_._._._| ___ |
                | |_| |  ___  | |_| |  ___  | |_| |
                |_III_|  |_|  |_III_|  |_|  |_III_| ^!^
            ^     | ___ |__III__| ___ |__III__| ___ |
                ^  | |_| |  ___  | |_| |  ___  | |_| |   ^!^
                |_III_|  |_|  |_III_|  |_|  |_III_|
                | ___ |__III__| ___ |__III__| ___ | _)o(_
                | |_| |  ___  | |_| |  ___  | |_| | /(|)\
            /)  |_III_|  |_|  |_III_|  |_|  |_III_|   H
            _/ )  | ___ |__III__|_____|__III__| ___ |   H
            ~^~^~ | |_| |"""""""||~|~||"""""""| |_| |   H
                ^~'|_III_|@@@@@@@||_|_||@@@@@@@|_III_|^~^H '
            @@@@@@@@@@@@@@     @/=====\@     @@@@@@@@@@@@@@

                )";

                string moderno =R"(
            __                   ___      
            |""|  ___    _   __  |"""|  __ 
            |""| |"""|  |"| |""| |"""| |""| 
            |""| |"""|  |"| |""| |"""| |""| 
            |""| |"""|  |"| |""| |"""| |""| 
            "'''"''"'""'"""''"''''"""'""'""'
                )";

                cout << "Escolha um modelo para o prédio '" << getName() << "':\n";

                // ASCII Art para os modelos
                cout << "1. Modelo Simples\n";

                cout<< simples <<"\n";

                cout << "2. Modelo Clássico\n";
                cout<<classico<<"\n";

                cout << "3. Modelo Moderno\n";
                cout<<moderno <<"\n";

                int escolha;
                cout << "Digite o número do modelo desejado: ";
                cin >> escolha;

                switch (escolha)
                {
                case 1:
                    setModel(simples);
                    break;
                case 2:
                    setModel(classico);
                    break;
                case 3:
                    setModel(moderno);
                    break;
                default:
                    cout << "Escolha inválida. Modelo padrão (Simples) será definido.\n";
                    setModel("Simples");
                    break;
                }

                cout << "Modelo selecionado: " << getModel() << "\n";
            }

            void Building::displayFloorPlan() const
    {
        int width, height;
        std::tie(width, height) = getProporcaoTerreno();

        // Exemplo básico de representação ASCII art da planta baixa
        std::cout << "Planta Baixa para " << getName() << " (Proporção de Terreno: " << width << "x" << height << "):\n";

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                {
                    // Bordas do prédio
                    std::cout << "#";
                }
                else
                {
                    // Espaço interno do prédio
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }
            
            ////Classe 2.1 - Workplace
                void Workplace::goToWork(Sims *sim){
            system("clear");
            cout<<"+------------+------------+--------------+--------------+\n";
            cout << "Bem-vindo ao seu local de trabalho!\n";
            cout << "Escolha uma opção:\n";
            cout <<VERDE<< "1. "<<RESET<<"🚀 Trabalhar em um turno rápido - iniciar evento\n";
            cout <<VERDE<< "2. "<<RESET<<"🕒 Trabalhar em um turno normal - iniciar evento\n";

            int escolha;
            cout << "Opção: ";
            cin >> escolha;

            if (escolha == 1)
            {
                system("clear");
                // Trabalhar em um turno rápido - iniciar evento
                careerStorie.iniciarEvento(sim, QUICKSHIFT);
            }
            else if (escolha == 2)
            {
                // Trabalhar em um turno normal - iniciar evento
                system("clear");
                careerStorie.iniciarEvento(sim, STANDARDSHIFT);
            }
            else
            {
                cout << "Opção inválida.\n";
            }
        }

            ////Classe 2.2 - leisurePlace

            void LeisurePlace::socialize(Sims *sim)
        {
            // Mostrar lista de Sims disponíveis para socialização
            cout << "Escolha um sim para socializar:\n";
            for (size_t i = 0; i < simsList.size(); ++i)
            {
                cout << i + 1 << ". " << simsList[i].getNomeCompleto() << "\n";
            }

            // Receber a opção escolhida pelo usuário
            int escolha;
            cout << "Opção: ";
            cin >> escolha;

            // Verificar se a escolha está dentro dos limites
            if (escolha < 1 || escolha > static_cast<int>(simsList.size()))
            {
                cout << VERMELHO<<"Opção inválida.\n"<<RESET;
                return;
            }

            // Obter o Sim escolhido
            Sims &simEscolhido = simsList[escolha - 1];
            system("clear"); // Comando para limpar o terminal em sistemas Unix-like (Linux, macOS)
            cout<<VERDE<<"sim Escolhido: "<<simEscolhido.getNomeCompleto()<<RESET<<"\n";
            // Mostrar opções de ação
            cout<<"+--------------------------------------------------------+\n";
            cout << "Escolha uma ação:\n";
            cout << "1. Ações de amizade\n";
            cout << "2. Ações românticas\n";

            // Receber a opção de ação
            int opcaoAcao;
            cout << "Opção: ";
            cin >> opcaoAcao;
            system("clear"); // Comando para limpar o terminal em sistemas Unix-like (Linux, macOS)
            // Executar a ação correspondente
            if(opcaoAcao == 1)
            {
                sim->fazerApresentacaoAgradavel(simEscolhido);


                for (int i = 1; i <= friendshipActions.getActions().size();i++)
                {
                    friendshipActions.executeAction(sim,i);
                }
            
            }
            else if (opcaoAcao == 2)
            {
                romanticActions.startEvent(&simEscolhido);
            }
            else
            {
                cout << "Opção inválida.\n";
            }
        }

//// Fazer a sobrecarga para todas as classes dos operadores =, ==, ≠ e << (friend)

     //// Operator=
         //// Base 1 - Quests
            const Quests& Quests::operator=(const Quests& other) {
                if (this != &other) {
                    nome = other.nome;
                    icon = other.icon;
                    rewardsSimsCash = other.rewardsSimsCash;
                    concluida = other.concluida;
                }
                return *this;
            }

            //>>>Comentário: Ok muito bem
             
            ////Derivadas da Base 1 - mostrar uso static_cast
                const GeneralMissions& GeneralMissions::operator=(const GeneralMissions& other) {
                    if (this != &other) {
                        *static_cast< Quests * >( this ) = static_cast< Quests >( other );
                        description = other.description;
                        subtitle = other.subtitle;
                    }
                    return *this;
                }
                
                const DailyTasks& DailyTasks::operator=(const DailyTasks& other) {
                    if (this != &other) {
                        // Copie os atributos da missão
                        *static_cast< Quests * >( this ) = static_cast< Quests >( other );
                        endsIn = other.endsIn;
                    }
                    return *this;
                }

         //// Base 2
            const Stories& Stories::operator=(const Stories& other) {
                if (this != &other) {
                    title = other.title;
                    subtitle = other.subtitle;
                    description = other.description;
                    capitulos = other.capitulos;
                    parte = other.parte;
                }
                return *this;
            }

             ////Derivadas da Base 2 - mostrar uso static_cast
                const CareerStories& CareerStories::operator=(const CareerStories& other) {
                    if (this != &other)
                    {
                        *static_cast<Stories*>(this) = static_cast<Stories>(other);
                        worker = other.worker;
                        workplace = other.workplace;
                        actions = other.actions;
                    }
                    return *this;
                }

                const RelationshipStories& RelationshipStories::operator=(const RelationshipStories& other) {
                    if (this != &other) {
                        *static_cast<Stories*>(this) = static_cast<Stories>(other);
                        simInvolved = other.simInvolved;
                    }
                    return *this;
                }

                const FriendshipActions& FriendshipActions::operator=(const FriendshipActions& other) {
                    if (this != &other) {
                        *static_cast< RelationshipStories * >( this ) = static_cast< RelationshipStories >( other );
                        currentPontos = other.currentPontos;
                        actions = other.actions;
                    }
                    return *this;
                }
                
                const RomanticActions& RomanticActions::operator=(const RomanticActions& other) {
                    if (this != &other) {
                        *static_cast< RelationshipStories * >( this ) = static_cast< RelationshipStories >( other );	
                        pair = other.pair;
                        relationshipStatus = other.relationshipStatus;
                    }
                    return *this;
                }
        //// Base 3
            Location &Location::operator=(const Location &other)
            {
                if (this != &other)
                {
                    proporcaoTerreno = other.proporcaoTerreno;
                    proprietario = other.proprietario;
                }
                return *this;
            }

             ////Derivadas da Base 3 - mostrar uso static_cast

                const SimsHouse &SimsHouse::operator=(const SimsHouse &house) {
                    if (this != &house) {
                        static_cast<Location &>(*this) = static_cast<const Location &>(house);
                        this->premium = house.premium;
                        this->valor = house.valor;
                    }
                    return *this;
                }

                const Building &Building::operator=(const Building &other)
                {
                    if (this != &other)
                    {
                        static_cast<Location &>(*this) = static_cast<const Location &>(other);
                        districtName = other.districtName;
                        name = other.name;
                        model = other.model;
                    }
                    return *this;
                }
     //// Operators== e !=
         //// Base 1
        bool Quests::operator==(const Quests& other) const {
            return (nome == other.nome && icon == other.icon && rewardsSimsCash == other.rewardsSimsCash && concluida == other.concluida);
        }
        bool Quests::operator!=(const Quests& other) const {
            return !(*this == other);
        }
                    ////Derivadas da Base 1 - mostrar uso static_cast
                        bool GeneralMissions::operator==(const GeneralMissions& other) const {
                            return (static_cast< Quests >( *this ) == static_cast< Quests >( other ) 
                            && description == other.description 
                            && subtitle == other.subtitle);
                        }
                        bool GeneralMissions::operator!=(const GeneralMissions& other) const {
                            return !(*this == other);
                        }

                        bool DailyTasks::operator==(const DailyTasks& other) const {
                            // Compare os atributos da missão
                            return (endsIn == other.endsIn && static_cast< Quests >( *this ) == static_cast< Quests >( other ));
                        }
                        bool DailyTasks::operator!=(const DailyTasks& other) const {
                            // Use o operador == para verificar a diferença
                            return !(*this == other);
                        }

         //// Base 2
        bool Stories::operator==(const Stories& other) const {
            return (title == other.title && subtitle == other.subtitle && description == other.description &&
                    capitulos == other.capitulos && parte == other.parte);
        }
        bool Stories::operator!=(const Stories& other) const {
            return !(*this == other);
        }
             ////Derivadas da Base 2 - mostrar uso static_cast
                bool CareerStories::operator==(const CareerStories& other) const {
                    return static_cast< Stories >( *this ) == static_cast< Stories >( other ) &&
                    worker == other.worker && workplace == other.workplace;
                }
                bool CareerStories::operator!=(const CareerStories& other) const {
                    return !(*this == other);
                }
                
                bool RelationshipStories::operator==(const RelationshipStories& other) const {
                    return static_cast< Stories >( *this ) == static_cast< Stories >( other ) && (simInvolved == other.simInvolved);
                }
                bool RelationshipStories::operator!=(const RelationshipStories& other) const {
                    return !(*this == other);
                }
                
                bool FriendshipActions::operator==(const FriendshipActions& other) const {
                    return 
                    (    
                        static_cast<RelationshipStories>(*this) == static_cast<RelationshipStories>(other) &&
                        currentPontos == other.currentPontos &&

                        ( //para comparar os elementos dos vetores actions dos dois 
                            std::equal(actions.begin(), actions.end(), other.actions.begin(), other.actions.end(), 
                            [](const Action& a, const Action& b)
                            {
                                return (   
                                            a.actionName == b.actionName && 
                                            a.custo == b.custo &&
                                            a.pontosDeEvento == b.pontosDeEvento
                                        ); 
                            }
                            )
                        )
                    );
                }
                bool FriendshipActions::operator!=(const FriendshipActions& other) const {
                    return !(*this == other);
                }
                
                bool RomanticActions::operator==(const RomanticActions& other) const {
                    return (static_cast< RelationshipStories >( *this ) == static_cast< RelationshipStories >( other )&&
                        pair == other.pair &&
                        relationshipStatus == other.relationshipStatus);
                }
                bool RomanticActions::operator!=(const RomanticActions& other) const {
                    return !(*this == other);
                }

        //// Base 3
        bool Location::operator==(const Location &other) const
        {
            return (proporcaoTerreno == other.proporcaoTerreno &&
                    OPTIONMENU == other.OPTIONMENU &&
                    proprietario == other.proprietario);
        }
        bool Location::operator!=(const Location &other) const
        {
            return !(*this == other);
        }

                    ////Derivadas da Base 3 - mostrar uso static_cast
                    int SimsHouse::operator==(const SimsHouse &house) const {
                        return ( static_cast<const Location &>(*this) == static_cast<const Location &>(house) &&
                                this->ENDERECO == house.ENDERECO);
                    }
                    int SimsHouse::operator!=(const SimsHouse &house) const {
                        return !(*this == house);
                    }
                    
                    bool Building::operator==(const Building &other) const
                    {
                        return (static_cast<const Location &>(*this) == static_cast<const Location &>(other) &&
                                districtName == other.districtName &&
                                name == other.name &&
                                model == other.model);
                    }
                    bool Building::operator!=(const Building &other) const
                    {
                        return !(*this == other);
                    }

                    bool Workplace::operator==(const Workplace &other) const
                    {
                        return (static_cast<const Building &>(*this)==static_cast<const Building &>(other) &&
                                careerStorie == other.careerStorie);
                    }
                    bool Workplace::operator!=(const Workplace &other) const
                    {
                        return !(*this == other);
                    }
                    
                    bool LeisurePlace::operator==(const LeisurePlace &other) const
                    {
                        return (static_cast<const Building &>(*this) == static_cast<const Building &>(other) &&
                                simsList == other.simsList &&
                                friendshipActions == other.friendshipActions &&
                                romanticActions == other.romanticActions
                                &&
                                ( //para comparar os elementos dos vetores actions dos dois 
                                equal(simsList.begin(), simsList.end(), other.simsList.begin(), other.simsList.end(), 
                                [](const Sims& simA, const Sims& simB)
                                {
                                    return ( simA == simB  ); 
                                }
                                )
                            ));
                    }
                    bool LeisurePlace::operator!=(const LeisurePlace &other) const
                    {
                        return !(*this == other);
                    }
     //// Operator<<
        //// Base 1

        ostream& operator<<(ostream& out, const Quests& mission) {
            out << "\n+-----------------------+\n";
            out << "|       Quest       |\n";
            out << "+-----------------------+\n";
            out << "| "<< mission.getNome() <<" "<< mission.getIcon() << "\n";
            out << "| Rewards: " << mission.getRewards() << " SimsCash\n";
            out << "| Completed: " << (mission.isConcluida() ? "Yes" : "No") << "\n";
            return out;
        }
            ////Derivadas da Base 1 - mostrar uso static_cast
            ostream& operator<<(ostream& out, const GeneralMissions& generalMissions) {
                out << "| -=-=-= General Mission-=-=-=\n";
                out << static_cast<const Quests&>(generalMissions);  // Mostra os atributos da classe base
                out << "| " << generalMissions.getDescription() << "\n";
                out << "| Descrição: " << generalMissions.getSubtitle() << "\n";
                out << "+-----------------------+\n";
                return out;
            }
            ostream& operator<<(ostream& out, const DailyTasks& dailyMission) {
                // Exiba de forma estilizada os atributos da missão
                if (dailyMission.hasExpired()){
                    out<<"Missão expirada.\n";
                    return out;
                }
                out << static_cast< Quests>( dailyMission );
                out << "| Data: ";
                dailyMission.showEndsIn();
                out << "\n| Atualiza em: 🕗 "<< dailyMission.tempoRestanteAteFinalDoDia();
                out << "\n+-----------------------+\n";


                return out;
            }

        //// Base 2
        ostream& operator<<(ostream& out, const Stories& story) {
            int lineWidth = 80;  // Suponha uma largura de linha padrão para ilustração

            // Centraliza o título
            int titleWidth = static_cast<int>(story.getTitle().length());
            int leftPaddingTitle = (lineWidth - titleWidth) / 2;

            // Centraliza o subtítulo
            int subtitleWidth = static_cast<int>(story.getSubtitle().length());
            int leftPaddingSubtitle = (lineWidth - subtitleWidth) / 2;

            // Centraliza a descrição
            int descriptionWidth = static_cast<int>(story.getDescription().length());
            int leftPaddingDescription = (lineWidth - descriptionWidth) / 2;

            out << "\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- História =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            out << setw(leftPaddingTitle) << "" << "\033[1m" << story.getTitle() << "\033[0m\n";  // Adiciona negrito
            out << setw(leftPaddingSubtitle) << "" << story.getSubtitle() << "\n";
            out << setw(leftPaddingDescription) << "" << story.getDescription() << "\n";

            out << "| Parte: " << story.getParte() << "\n";
            // Exiba os capítulos
            out << "| Capítulos:\n";
            int i = 1;
            for (const auto& [recompensa, nome] : story.capitulos) {
                // Verifique se o índice coincide com a parte atual
                if (i == story.getParte()) {
                    // Use ciano para destacar o capítulo atual
                    out << "|   Parte " << i << ": \033[1;36m" << nome << " | " << recompensa << "SimsCash e xp \033[0m\n";
                } else {
                    out << "|   Parte " << i << ": " << nome << " | " << recompensa << "SimsCash e xp\n";
                }
                i++;
            }
            return out;
        }

            ////Derivadas da Base 2 - mostrar uso static_cast
            ostream& operator<<(ostream& out, const CareerStories& story) {
                out << static_cast<const Stories&>(story);  // Chamando o operador de saída da classe base
                out << "| Current Pontos de Carreira no capítulo: " << story.pontosDeCarreira << "\n";
                out << "| Sim: " << story.worker << "\n";
                out << "| local: " << story.workplace << "\n";

                out << "Actions:\n";
                for (const auto& action : story.actions) {
                    out << "- " << action << "\n";
                }
                return out;
            }
            ostream& operator<<(ostream& out, const RelationshipStories& story) {
                out << static_cast<const Stories&>(story);
                out << "| Sim Envolvido: " << story.getSimInvolved() << "\n";
                return out;
            }
            ostream& operator<<(ostream& out, const FriendshipActions& actions) {
                // Chama o operador << da classe base
                out << static_cast<RelationshipStories>(actions);
                out << "| Pontos de evento: " << actions.getCurrentPontos() << "\n";
                return out;
            }
            ostream& operator<<(ostream& out, const RomanticActions& romanticActions) {
                // Chama o operador << da classe base
                out << static_cast<const RelationshipStories&>(romanticActions);

                // Adiciona informações específicas de RomanticActions
                out << "| pair: "<<romanticActions.pair;
                out << "\n| Relationship Status: " <<romanticActions.relationshipStatus<< "\n";

                return out;
            }

       //// Base 3
        ostream &operator<<(ostream &out, const Location &location)
        {
            out<<R"(  
            ____    ____       _        _ _                     _       
        / /\ \  |  _ \  ___| |_ __ _| | |__   ___  ___    __| | ___  
        / /  \ \ | | | |/ _ \ __/ _` | | '_ \ / _ \/ __|  / _` |/ _ \ 
        / /    \ \| |_| |  __/ || (_| | | | | |  __/\__ \ | (_| | (_) |
        /_/      \_\____/ \___|\__\__,_|_|_| |_|\___||___/  \__,_|\___/ 
        | | ___   ___ __ _| |                                           
        | |/ _ \ / __/ _` | |                                           
        | | (_) | (_| (_| | |                                           
        |_|\___/ \___\__,_|_|                                           
        \ \      / /                                                    
        \ \    / /                                                     
        \ \  / /                                                      
        \_\/_/                                                       
        
        )"<<"\n";

            out<<"==========================\n";
            out << "Proporção de Terreno: " << "(" << std::get<0>(location.proporcaoTerreno) << ", " << std::get<1>(location.proporcaoTerreno) << ")\n"
                << "Representação Emoji: ";
            switch (location.OPTIONMENU)
            {
            case HOUSES:
                out << "🏡";
                break;
            case BUILDINGS:
                out << "🏢";
                break;
            default:
                out << "Desconhecido";
            }

            out << "\nProprietário: " << location.proprietario << "\n";

            return out;
        }
            ////Derivadas da Base 3 - mostrar uso static_cast
                ostream &operator<<(ostream &out, const SimsHouse &house)
                {
                    out << static_cast<const Location &>(house);// Chama o operador << da classe base Location

                    out << "==========================================\n";
                    out <<R"(
                ____     ___                       _               
                / /\ \   / _ \__   _____ _ ____   _(_) _____      __
                / /  \ \ | | | \ \ / / _ \ '__\ \ / / |/ _ \ \ /\ / /
                \ \  / / | |_| |\ V /  __/ |   \ V /| |  __/\ V  V / 
                \_\/_/_  \___/  \_/ \___|_|    \_/ |_|\___| \_/\_/  
                / ___|(_)_ __ ___  ___| | | | ___  _   _ ___  ___    
                \___ \| | '_ ` _ \/ __| |_| |/ _ \| | | / __|/ _ |   
                ___) | | | | | | \__ \  _  | (_) | |_| \__ \  __/   
                |____/|_|_| |_| |_|___/_| |_|\___/ \__,_|___/\___|  

                    )";
                out << (house.premium ? "Premium💎" : "")<< "\n";
                out << "==========================================\n";
                out << "\033[1;32m ❇️ Endereço: \033[0m" << house.ENDERECO<< "\n";
                out << "\033[1;32m ❇️ valor: \033[0m" << house.valor << " housesCash\n";
                out << "============================================\n";

                return out;
                }
                ostream &operator<<(ostream &out, const Building &building)
                {
                    out << static_cast<const Location &>(building) // Chama o operador << da classe base Location
                    << "\n🌆 District Name: " << building.districtName
                    << "\n🏢 Name: " << building.name
                    <<"\n" <<building.model;
                    
                    return out;
                }

                ostream &operator<<(ostream &out, const Workplace &workplace)
                {
                    out << static_cast<const Building &>(workplace) // Chama o operador << da classe base Building
                    << "\nStories Career: " << workplace.careerStorie;
                    return out;
                }
                
                ostream &operator<<(ostream &out, const LeisurePlace &leisurePlace)
                {
                    out << static_cast<const Building &>(leisurePlace) // Chama o operador << da classe base Building
                    << "\nSims List: ";
                        leisurePlace.showSimsList();
                    out<< "\n Ações de amizade: " << leisurePlace.friendshipActions
                    << "\n Ações românticas: " << leisurePlace.romanticActions;
                    return out;
                }
                
//// Para cada classe do seu projeto criar pelo menos dois constructores, 
 //sendo um o constructor de cópia 
 ////Mostrar uso de reaproveitamento de código da base na derivada

    //// Base 1 - constructores
        ////Constructor 1
        Quests::Quests(const string& nome, const string icon, int rewardsSimsCash)
        :rewardsSimsCash(rewardsSimsCash),concluida(false) 
        {
            setNome(nome);
            setIcon(icon);
        }

        ////Constructor de cópia
        Quests::Quests(const Quests& other)
            : nome(other.nome),
            icon(other.icon),
            rewardsSimsCash(other.rewardsSimsCash),
            concluida(other.concluida) {}

    //// Base 2 - constructores
        ////Constructor 1
        Stories::Stories(const string& title, const string& subtitle, const string& description, const map<int, string> capitulos)
        : title(title), subtitle(subtitle), description(description), capitulos(capitulos), parte(1)
        {

        }
        ////Constructor de cópia
        Stories::Stories(const Stories& other)
            : title(other.title), subtitle(other.subtitle), description(other.description), capitulos(other.capitulos), parte(other.parte) {}

    //// Base 3 - constructores
        ////Constructor 1
        Location::Location(const tuple<int, int> &proporcao, const emojiRepresentation &optionMenu, const string &proprietario)
        : proporcaoTerreno(proporcao), OPTIONMENU(optionMenu), proprietario(proprietario)
        {

}
        ////Constructor de cópia 
        Location::Location(const Location &other)
        : proporcaoTerreno(other.proporcaoTerreno), OPTIONMENU(other.OPTIONMENU), proprietario(other.proprietario) {}

    ////Derivadas - constructores

        //// Hierarquia 1

             ////Classe 1
                 ////Constructor 1
                GeneralMissions::GeneralMissions(const string& nome, const string& icon, int recompensa, const string& subtitulo, const string& descricao )
                : Quests(nome, icon, recompensa)
                {
                    setSubtitle(subtitulo);
                    setDescription(descricao);
                }
                 ////Constructor de cópia

                GeneralMissions::GeneralMissions(const GeneralMissions& other)
                : Quests(static_cast< Quests >( other )),
                    description(other.description),
                    subtitle(other.subtitle)
                {}
             ////Classe 2
                 ////Constructor 1
                    DailyTasks::DailyTasks(const string& nome, const string& icon, int recompensa)
                    : Quests(nome, icon, recompensa), endsIn(Data::getDataAtual()) 
                    {
                    }
                 ////Constructor de cópia
                    DailyTasks::DailyTasks(const DailyTasks& other) 
                    :Quests(static_cast< Quests >( other )), endsIn(other.endsIn) 
                    {
                    }             

        //// Hierarquia 2

             ////Classe 1
                 ////Constructor 1
                    CareerStories::CareerStories(const string& title, const string& subtitle, const string& content, const map<int, string>& chapters, const string& worker, const string& workplace, const vector<string>& actions)
                    : Stories(title, subtitle, content, chapters), worker(worker), workplace(workplace),actions(actions)
                    {

                    }
                 ////Constructor de cópia
                    CareerStories::CareerStories(const CareerStories& other)
                    : Stories(static_cast< Stories>( other )), worker(other.worker), workplace(other.workplace), actions(other.actions) 
                    {

                    }
             ////Classe 2
                 ////Constructor 1

                    RelationshipStories::RelationshipStories(const string& titulo, const string& subtitulo, const string& descricao, const map<int, string>& capitulos,const string& sim)
                    : Stories(titulo,subtitulo,descricao,capitulos),simInvolved(sim)
                    {

                    }

                 ////Constructor de cópia
                    RelationshipStories::RelationshipStories(const RelationshipStories& other)
                    : Stories(static_cast< Stories >( other )), simInvolved(other.simInvolved)
                    {

                    }

            ////Classe 3
                 ////Constructor 1
                    FriendshipActions::FriendshipActions(const RelationshipStories& relationshipStories,const vector <Action> & actionsList)
                    :RelationshipStories(relationshipStories), currentPontos(0), actions(actionsList)
                    {

                    }

                 ////Constructor de cópia
                    FriendshipActions::FriendshipActions(const FriendshipActions& other)
                    : RelationshipStories(static_cast< RelationshipStories >( other )), MAXPONTOSEVENTOS(other.MAXPONTOSEVENTOS), currentPontos(other.currentPontos), actions(other.actions) {}

            ////Classe 4
                 ////Constructor 1
                    RomanticActions::RomanticActions(const RelationshipStories& relationshipStories, const string& pair)
                    : RelationshipStories(relationshipStories), pair(pair), relationshipStatus("Não definido"), UPCAP(50)
                    {

                    }
                 ////Constructor de cópia
                    RomanticActions::RomanticActions(const RomanticActions& other)
                    : RelationshipStories(static_cast< RelationshipStories >( other )), pair(other.pair), relationshipStatus(other.relationshipStatus), UPCAP(other.UPCAP) {}

      //// Hierarquia 2

             ////Classe 1
                 ////Constructor 1
                    SimsHouse::SimsHouse(const tuple<int, int> & proporcaoTerreno,double valor,const string & ENDERECO,const string &  proprietario )
                    :ENDERECO(ENDERECO),Location(proporcaoTerreno,HOUSES,proprietario)
                    {
                        cout << "Inicializando SimHouse.\n";
                        setValor(valor);
                        enderecosList[numEnderecos] = ENDERECO;
                        numEnderecos++;
                    }
                 ////Constructor de cópia
                    SimsHouse::SimsHouse(const SimsHouse &houseCopia)
                    :ENDERECO(houseCopia.ENDERECO),Location(static_cast<Location> (houseCopia))
                    {
                        cout << "Inicializando SimHouse.\n";
                        this->premium = houseCopia.premium;
                        this->valor = houseCopia.valor;
                        enderecosList[numEnderecos] = ENDERECO;
                        numEnderecos++;
                    }

             ////Classe 2
                 ////Constructor 1
                    Building::Building(const tuple<int, int> &proporcao,const string & proprietario,const string &districtName, const string &name)
                    : Location(proporcao, BUILDINGS,proprietario), districtName(districtName),name(name), model("")
                    {
                    }
                 ////Constructor de cópia
                    Building::Building(const Building &other)
                        : Location(static_cast<Location>(other)), districtName(other.districtName), name(other.name), model(other.model) 
                    {

                    }
             ////Classe 3
                 ////Constructor 1
                    Workplace::Workplace(const tuple<int, int> &proporcao, const CareerStories &careerStorie,const string & proprietario, const string &districtName, const string &name)
                    :Building(proporcao,proprietario,districtName,name), careerStorie(careerStorie)
                    {
                    }
                 ////Constructor de cópia
                    Workplace::Workplace(const Workplace &other)
                        : Building(static_cast<Building>(other)), careerStorie(other.careerStorie) {}

            ////Classe 4
                 ////Constructor 1
                    LeisurePlace::LeisurePlace(const tuple<int, int>& proporcao, const string& districtName, const string& name, const FriendshipActions& friendshipActions, const RomanticActions& romanticActions)
                    :Building(proporcao,districtName, name), friendshipActions(friendshipActions), romanticActions(romanticActions)
                    {
                        // Adicionando objetos Sims à lista
                        simsList.emplace_back("Claudomiro", "Sales", 'M', 9,30,20000 );
                        simsList.emplace_back("Jake", "Sully", 'M', 5);
                        simsList.emplace_back("Ana", "Caetano", 'F',7,30,1000000);
                        simsList.emplace_back("Vitória", "Falcão", 'F',9,30,1000000);
                        simsList.emplace_back("Mike", "Tulio", 'M',7,30,1000000);
                        simsList.emplace_back("Lucas", "Mamede", 'M',7,30,1000000);

                    }
                 ////Constructor de cópia
                    LeisurePlace::LeisurePlace(const LeisurePlace &other)
                        : Building(static_cast<Building>(other)), simsList(other.simsList), friendshipActions(other.friendshipActions), romanticActions(other.romanticActions) {}

//>>>Comentário: Tinha no trablaho anterior mas aqui era para colocar novamente
//o código do processo de carregamento e salvamento

//// Carregamento e salvamento de arquivos
    /*É necessário ter a funcionalidade: 1. 
      leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
      processamento das variáveis de status e 3. salvamento dessas variáveis. 
      Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/

    //Link arquivo de configuração no repositório
        // https://github.com/syannekaroline/TheSimsMobile/blob/main/build/infosGame.txt
    //Link vídeo mostrando a execução do código usando o arquivo de configuração

        // https://youtu.be/NrsGuFa4kP8