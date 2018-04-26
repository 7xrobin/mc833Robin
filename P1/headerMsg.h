// @functioname:
//	1: getDisciplinesTitles() 
// 	2: listAllDiscplinesInfos()
// 	3: getDisciplineProgram(discipline_id);
//  4: Get discipline infos
//  5: Get comments of a discipline
//	6: Write some comment in discipline (Just Professor)

typedef enum {student, professor} USER;
struct headerMsg{
	int userType;				//0: Student; 1: Professor
    int functionName; 			// Request Function Id
    int sizePayload; 			//Total Bytes of Payload 
    char disciplineId[10];			
    char payload[777];
};

