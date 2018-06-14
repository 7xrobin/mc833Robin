

public class AcademicData {

    public Discipline[] data = new Discipline[5];

    public  void AcademicData(){
      for( int i=0; i<5; i++){
         this.data[i] = new Discipline();
      }
        this.data[0].id = "MC102";
        this.data[0].title = "Algoritmos e Programação de Computadores";
        this.data[0].program = "Conceitos básicos de organização de computadores. Construção de algoritmos e sua representação em pseudocódigo e linguagens de alto nível. Desenvolvimento sistemático e implementação de programas. Estruturação, depuração, testes e documentação de programas. Resolução de problemas.";
        this.data[0].schedule = "Seg 10h-12h / Ter 10h-12h / Qui 10h-12h";
        this.data[0].commentary = "Fácil de Passar";

        this.data[1].id = "MC202";
        this.data[1].title = "Estruturas de Dados";
        this.data[1].program = "Estruturas básicas para representação de informações: listas, árvores, grafos e suas generalizações. Algoritmos para construção, consulta e manipulação de tais estruturas. Desenvolvimento, implementação e testes de programas usando tais estruturas em aplicações específicas.";
        this.data[1].schedule = "Ter 10h-12h / Qui 10h-12h / Qui 14h-16h";
        this.data[1].commentary = "";


        this.data[3].id = "MC358";
        this.data[3].title = "Fundamentos Matemáticos da Computação";
        this.data[3].program = "Conceitos básicos de matemática discreta e de lógica para computação. Técnicas de provas, indução matemática. Relações e conceitos de teoria de grafos. Modelagem de problemas usando grafos.";
        this.data[3].schedule = "Ter 19h-21h / Qua 19h-21h";
        this.data[3].commentary = "";

        this.data[4].id = "MC536";
        this.data[4].title = "Bancos de Dados: Teoria e Prática";
        this.data[4].program = "Arquiteturas de sistemas de gerenciamento de bancos de dados. Modelagem de dados: modelos conceituais e lógicos, incluindo o modelo relacional e normalização. Álgebra relacional. Linguagens de definição e de manipulação de dados. Otimização de consultas. Mecanismos de proteção, recuperação e segurança. Controle de concorrência. Bancos de dados não relacionais. Projeto e desenvolvimento de ferramentas e técnicas utilizadas na solução de problemas de sistemas de informação, utilizando bancos de dados. Modelagem, especificação, projeto e implementação de aplicações em sistemas de informação.";
        this.data[4].schedule = "Ter 19h-21h / Qui 19h-23h";
        this.data[4].commentary = "";



        this.data[5].id = "MC833";
        this.data[5].title = "Programação de Redes de Computadores";
        this.data[5].program = "Programação utilizando diferentes tecnologias de comunicação: sockets, TCP e UDP, e chamada de método remoto.";
        this.data[5].schedule = "Qui 10h-12h";
        this.data[5].commentary = "";

  }
}
