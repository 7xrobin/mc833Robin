// @functioname:
//	1: getDisciplinesTitles() 
// 	2: listAllDiscplinesInfos()
// 	3: getDisciplineProgram(discipline_id);
//  4: getDisciplineInfo(req.disciplineId);	
//  5: getDisciplineComments(req.disciplineId);	
//	6: setDisciplineComments(req.userType, req.disciplineId, req.payload);	

struct headerMsg{
	int userType;				//0: Student; 1: Professor
    int functionName; 			// Request Function Id
    int sizePayload; 			//Total Bytes of Payload 
    char disciplineId[10];			
    char payload[777];
};

