
import javax.xml.crypto.dsig.Reference;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class AcademicImpl extends UnicastRemoteObject implements AcademicInterface {


  protected AcademicImpl() throws RemoteException {
    super();
  }

    @Override
    public String getRequisition(int option, String disciplineId, int user, String comment) throws RemoteException {
      String response = getAllTitles();
      return response;
    }

    //All titles of all disciplines
    public String getAllTitles(){
        AcademicData disList = new AcademicData();
        String res = "";
        for (int i = 0; i < disList.data.length; i++ ){
            res = res + disList.data[i].title + "\n";
        }
        return res;
    }
}
