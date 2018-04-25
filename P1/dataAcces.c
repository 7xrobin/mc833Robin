#include "base.h"
#include <string.h>
#include <stdlib.h>

discipline disciplines[5] = {
	{
		.id = "MC102",
		.title = "Algoritmos e Programação de Computadores",
		.program = "Conceitos básicos de organização de computadores. Construção de algoritmos e sua representação em pseudocódigo e linguagens de alto nível. Desenvolvimento sistemático e implementação de programas. Estruturação, depuração, testes e documentação de programas. Resolução de problemas.",
		.schedule = "Seg 10h-12h / Ter 10h-12h / Qui 10h-12h",
		.commentary = ""
	},
	
	{
		.id = "MC202",
		.title = "Estruturas de Dados",
		.program = "Estruturas básicas para representação de informações: listas, árvores, grafos e suas generalizações. Algoritmos para construção, consulta e manipulação de tais estruturas. Desenvolvimento, implementação e testes de programas usando tais estruturas em aplicações específicas.",
		.schedule = "Ter 10h-12h / Qui 10h-12h / Qui 14h-16h",
		.commentary = ""
	},
	
	{
		.id = "MC358",
		.title = "Fundamentos Matemáticos da Computação",
		.program = "Conceitos básicos de matemática discreta e de lógica para computação. Técnicas de provas, indução matemática. Relações e conceitos de teoria de grafos. Modelagem de problemas usando grafos.",
		.schedule = "Ter 19h-21h / Qua 19h-21h",
		.commentary = ""
	},
	
	{
		.id = "MC536",
		.title = "Bancos de Dados: Teoria e Prática",
		.program = "Arquiteturas de sistemas de gerenciamento de bancos de dados. Modelagem de dados: modelos conceituais e lógicos, incluindo o modelo relacional e normalização. Álgebra relacional. Linguagens de definição e de manipulação de dados. Otimização de consultas. Mecanismos de proteção, recuperação e segurança. Controle de concorrência. Bancos de dados não relacionais. Projeto e desenvolvimento de ferramentas e técnicas utilizadas na solução de problemas de sistemas de informação, utilizando bancos de dados. Modelagem, especificação, projeto e implementação de aplicações em sistemas de informação.",
		.schedule = "Ter 19h-21h / Qui 19h-23h",
		.commentary = ""
	},
	
	{
		.id = "MC833",
		.title = "Programação de Redes de Computadores",
		.program = "Programação utilizando diferentes tecnologias de comunicação: sockets, TCP e UDP, e chamada de método remoto.",
		.schedule = "Qui 10h-12h",
		.commentary = ""
	},

};


char* getAllDisciplinesList() {
	char *disciplines_list = NULL;
	disciplines_list = malloc(2 * sizeof(char));
	disciplines_list[0] = '\0';


	int db_length = sizeof(disciplines)/sizeof(discipline);

	for (int i = 0; i < db_length; i++) {
		disciplines_list = realloc(disciplines_list, (strlen(disciplines_list) +
													  strlen(disciplines[i].id) +
													  strlen(disciplines[i].title) + 4) * sizeof(char));
		strcat(disciplines_list, disciplines[i].id);
		strcat(disciplines_list, " - ");
		strcat(disciplines_list, disciplines[i].title);
		strcat(disciplines_list, "\n");
	}

	strcat(disciplines_list, "\n");

	return disciplines_list;
}

char* getRequest(int functionName){
	char* resp;
	if(functionName == 1){
		resp = getAllDisciplinesList();
	}
	return resp;
}
