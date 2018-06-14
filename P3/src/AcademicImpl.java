
import javax.xml.crypto.dsig.Reference;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Objects;

public class AcademicImpl extends UnicastRemoteObject implements AcademicInterface {

   private  AcademicData disList;
  protected AcademicImpl() throws RemoteException {
    super();
  }

    @Override
    public String getRequisition(int option, String disciplineId, int user, String comment) throws RemoteException {
      this.disList = new AcademicData();
      String response = "";
      switch (option){
          case 1:
              response = getAllTitles();
              break;
          case 2:
              response = listAlldisicplines();
              break;
          case 3:
              response = getDisciplineSchedule(disciplineId);
              break;
          case 4:
              response = getDisciplineProgram(disciplineId);
              break;
          case 5:
              response = getDisciplineComments(disciplineId);
              break;
          case 6:
              response = setComment(disciplineId, user, comment);
              break;
      }
      return response;
    }

    private String setComment(String disciplineId, int user, String comment) {
        String res = disciplineId + " Não encontrada\n";
        for (int i = 0; i < this.disList.data.length; i++) {
            if (this.disList.data[i].id.equals(disciplineId)) {
                if(user == 0){
                    res = "Aluno não pode adicionar comentário";
                }
                else {
                    this.disList.data[i].commentary = comment;
                    res = "Comentario adicionado. "+ "\n";
                }
            }
        }
        return res;
    }

    private String getDisciplineComments(String disciplineId) {
        String res = disciplineId + " Não encontrada\n";
        for (int i = 0; i < this.disList.data.length; i++) {
            if (this.disList.data[i].id.equals(disciplineId)) {
                res = this.disList.data[i].commentary + "\n";
            }
        }
        return res;
    }

    private String getDisciplineSchedule(String disciplineId){
        String res = disciplineId + " Não encontrada\n";
        for (int i = 0; i < this.disList.data.length; i++ ){
            if (this.disList.data[i].id.equals(disciplineId)){
                res = this.disList.data[i].schedule + "\n";
            }
        }
        return res;
    }

    private String getDisciplineProgram(String disciplineId){
        String res = disciplineId + " Não encontrada\n";
        for (int i = 0; i < this.disList.data.length; i++ ){
            if (this.disList.data[i].id.equals(disciplineId)){
                res = this.disList.data[i].program + "\n";
            }
        }
        return res;
    }

    private String listAlldisicplines(){
        String res = "";
        for (int i = 0; i < this.disList.data.length; i++ ){
            res = res + "Id: " + this.disList.data[i].id + "\n";
            res = res + "title: " + this.disList.data[i].title + "\n";
            res = res + "program:" + this.disList.data[i].program + "\n";
            res = res + "schedule:" + this.disList.data[i].schedule + "\n";
            res = res + "commentary:" + this.disList.data[i].commentary + "\n";
            res = res + "\n\n";
        }
        return  res;
    }

    //All titles of all disciplines
    public String getAllTitles(){
        String res = "";
        for (int i = 0; i < this.disList.data.length; i++ ){
            res = res + this.disList.data[i].title + "\n";
        }
        return res;
    }
}
