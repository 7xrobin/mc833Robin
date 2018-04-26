#include "base.h"
#include <string.h>
#include <stdlib.h>

#define ERROR_STRING "Disciplina não encontrada"
#define ERROR_USER "Você não tem permição para executar essa ação"

discipline disciplines[5] = {
	{
		.id = "MC102",
		.title = "Algoritmos e Programação de Computadores",
		.program = "Conceitos básicos de organização de computadores. Construção de algoritmos e sua representação em pseudocódigo e linguagens de alto nível. Desenvolvimento sistemático e implementação de programas. Estruturação, depuração, testes e documentação de programas. Resolução de problemas.",
		.schedule = "Seg 10h-12h / Ter 10h-12h / Qui 10h-12h",
		.commentary = "Fácil de Passar"
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


char* getDisciplinesTitles() {
	char *disciplines_list = NULL;
	disciplines_list = malloc(1 * sizeof(char));
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
// Return infos of one discipline as string
char* returnDisciplineInfo(discipline disc) {
	char *discipline_info;

	discipline_info = malloc((strlen(disc.id) + strlen(disc.title) + strlen(disc.program)
							 + strlen(disc.schedule) + strlen(disc.commentary) + 15) * sizeof(char));


	strcpy(discipline_info, disc.id);
	strcat(discipline_info, " - ");
	strcat(discipline_info, disc.title);
	strcat(discipline_info, " - ");
	strcat(discipline_info, disc.program);
	strcat(discipline_info, " - ");
	strcat(discipline_info, disc.schedule);
	strcat(discipline_info, " - ");
	strcat(discipline_info, disc.commentary);
	strcat(discipline_info, "\n");

	return discipline_info;
}

discipline* findDiscipline(char discipline_id[]) {

	// Getting number of elements in disciplines array
	int db_length = sizeof(disciplines)/sizeof(discipline);

	// Searching for discipline with given id
	for (int i = 0; i < db_length; i++) {
		if (strcmp(disciplines[i].id, discipline_id) == 0) {
			return &disciplines[i];
		}
	}
	printf("Disciplina não encontrada\n" );
	return NULL;
}

char* getDisciplineProgram(char discipline_id[]) {
	char* discipline_prog;

	discipline *disc = findDiscipline(discipline_id);

	if(disc == NULL){
		return ERROR_STRING;
	}

	discipline_prog = malloc((strlen(disc->program) + 1)  * sizeof(char));
	strcat(discipline_prog, disc->program);
	strcat(discipline_prog, "\n");

	return discipline_prog;
}

char* getDisciplineComments(char discipline_id[]) {
	discipline *disc = findDiscipline(discipline_id);
	char *discipline_commentary = malloc((strlen(disc->commentary) + 20) * sizeof(char));
	if(disc == NULL){
		return ERROR_STRING;
	}
	strcpy(discipline_commentary, "Comments: ");
	strcat(discipline_commentary, disc->commentary);
	strcat(discipline_commentary, "\n\n");

	return discipline_commentary;
}
char* setDisciplineComments(int user, char discipline_id[], char commentary[]) {
	if(user == 0){
		return ERROR_USER;
	}
	discipline *disc = findDiscipline(discipline_id);
	if(disc == NULL){
		return ERROR_STRING;
	}

	// disc->commentary = realloc(disc->commentary, strlen(commentary) * sizeof(char));
	
	strcpy(disc->commentary, commentary);

	return disc->commentary;
}

char* getDisciplineInfo(char discipline_id[]) {
	// Finding discipline by id and getting its information
	discipline *disc = findDiscipline(discipline_id);
	if(disc == NULL){
		return ERROR_STRING;
	}
	return returnDisciplineInfo(*disc);
}

char* listAllDiscplinesInfos() {
	char *disciplines_infos;
	char *disc_info;
	disciplines_infos = malloc(1 * sizeof(char));
	disciplines_infos[0] = '\0';

	// Getting number of elements in disciplines array
	int db_length = sizeof(disciplines)/sizeof(discipline);

	// Searching for discipline with given id
	for (int i = 0; i < db_length; i++) {
		disc_info = returnDisciplineInfo(disciplines[i]);

		disciplines_infos = (char*) realloc(disciplines_infos, (strlen(disciplines_infos) +
																strlen(disc_info)) * sizeof(char));

		strcat(disciplines_infos, disc_info);
	}
	free(disc_info);
	return disciplines_infos;
}


char* getRequest(struct headerMsg req){
	char* resp;
	switch(req.functionName){
		case 1:
			resp = getDisciplinesTitles();
			break;
		case 2:
			resp = 	listAllDiscplinesInfos();
			break;
		case 3:
			resp = 	getDisciplineProgram(req.disciplineId);
			break;
		case 4:
			resp = getDisciplineInfo(req.disciplineId);	
			break;
		case 5:
			resp = getDisciplineComments(req.disciplineId);	
			break;
		case 6:
			resp = setDisciplineComments(req.userType, req.disciplineId, req.payload);	
			break;	


	}
	
	return resp;
}
