/*Expandir a hierarquia da atividade anterior: três hierarquias de três níveis.
Sendo que em uma das hierarquias há dois níveis de classes 
abstratas. Uma das classes abstratas precisa ter pelo menos dois métodos virtuais 
puros. Para cada lado da hierarquia criar ao menos duas classes concretas. 
E pelo menos duas classes concretas herdando de uma dessas outras classes concretas. 
Cada classe, além dos métodos herdados, precisa ter pelo menos um método que tenha 
alguma funcionalidade, que não seja set e get. Para cada classe do seu 
 projeto criar pelo menos três constructores, sendo um o constructor de cópia. Em uma 
 das hierarquias deve haver alocação de memória usando um vector< ptr * >, onde ptr é 
 um ponteiro de uma de
suas classes criadas que tem relação de composição. Ter um atributo static e um 
atributo const static.  Fazer a sobrecarga para cada classe 
dos operadores =, ==, ≠, ! e << (friend) para as classes concretas. Usar sempre que 
possível o static_cast para reaproveitamento de código - mas não é possível usar
 para classes abstract.  Criar um vector de ponteiros de uma das classes abstrata e 
 armazenar nele objtetos de classes concretas. Usar dynamic_cast e typeid para fazer 
 algo significativo com partes dessas classes concretas. Carregamento e salvamento de 
 arquivos: é necessário ter a funcionalidade de 1. leitura de arquivos para 
 configuração das suas classes e variáveis de status, 2. processamento das variáveis 
 de status e 3. salvamento dessas variáveis. Todos os projetos devem ter um diagrama 
 mostrando a hierarquia. Sem o diagrama e os dois videos, o trabalho não será avaliado.*/


//// Geral - parte para revisão
    //Diagrama UML    
    //Organização do código 

////Importante
//// Cada classe, além dos métodos herdados, precisa ter pelo menos um método que tenha 
//alguma funcionalidade, que não seja set e get.

//// O .h das classes bases

     //Classe abstract base 1    

     //Classe abstract base 2

     //Classe abstract base 3

//// O .h da hierarquia 1 (abstract base 1)

     //Classe Abstract 1 que herda da base abstract
        //Deve ter seu próprio método virtual puro

     //Classe 2 - concrete

     //E assim por diante

//// O .h da hierarquia 2 (abstract base 2)

     //Classe 1 (abstract or concrete)

     //Classe 2

     //E assim por diante

//// O .h da hierarquia 3 (abstract base 3)

     //Classe 1

     //Classe 2

     //E assim por diante

////Implementação de constructores default de cópia

    ///Bases abstract

        //Classe abstract base 1    

        //Classe abstract base 2

        //Classe abstract base 3

    ////Classes concretas - mostrar reaproveitamento de código

        /// Hierarquia 1 (abstract base 1)

            //Classe Abstract 1 que herda da base abstract
        
            //Classe 2 - concrete

            //E assim por diante

        /// Hierarquia 2 (abstract base 1)

            //Classe 1 - concrete
        
            //Classe 2 - concrete

            //E assim por diante

        /// Hierarquia 2 (abstract base 1)

            //Classe 1 - concrete
        
            //Classe 2 - concrete

            //E assim por diante

//// Mostrar implementação dos métodos virtuais puros nas classes concretas
 /// Mostrar reaproveitamente de código da base

    /// Hierarquia 1

         //Classe 1

         //Classe 2

         //E assim por diante

    /// Hierarquia 2

         //Classe 1

         //Classe 2

         //E assim por diante


    /// Hierarquia 3

         //Classe 1

         //Classe 2

         //E assim por diante

//// Em uma das hierarquias deve haver alocação de memória usando um vector< ptr * >, 
// onde ptr é um ponteiro de uma de
//suas classes criadas que tem relação de composição.

    /// Mostrar .h como este vector (com apenas ele presente) usando "..." para omitir
    //o resto

    /// Mostrar inicialização do vector 

    /// Mostrar o método que aplica new nele

    /// Mostrar método em que ele é usado efetivamente
    //preenchimento, set e get serão ignorados

    ///Mostrar destructor


//// Ter um atributo static e um atributo const static.

    /// .h mostrando apenas eles e o método que os manipula

    /// Inicialização no .cpp

    /// Mostra método(s) em que são usados efetivamente


//// Fazer a sobrecarga para todas as classes dos operadores =, ==, ≠ e << (friend)

     /// Operator=
        /// Base 1

             //Derivadas da Base 1 - mostrar uso static_cast

        /// Base 2

             //Derivadas da Base 2 - mostrar uso static_cast

        /// Base 3

             //Derivadas da Base 3 - mostrar uso static_cast


     //// Operators== e !=
         // Base 1

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

//// Carregamento e salvamento de arquivos
    /*É necessário ter a funcionalidade: 1. 
      leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
      processamento das variáveis de status e 3. salvamento dessas variáveis. 
      Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/

    //Link arquivo de configuração no repositório

    //Link vídeo mostrando a execução do código usando o arquivo de configuração