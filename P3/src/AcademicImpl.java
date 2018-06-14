
import javax.xml.crypto.dsig.Reference;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class AcademicImpl extends UnicastRemoteObject implements AcademicInterface {


  protected AcademicImpl() throws RemoteException {
    super();
  }

    @Override
    public String getRequisition(int option, String disciplineId, int user, String comment) throws RemoteException {
      String response = getAllDisciplines();
      return response;
    }

    public String getAllDisciplines(){
        AcademicData disList = new AcademicData();
        return disList.data[0].id;
    }
}
