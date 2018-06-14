

public interface AcademicInterface  extends java.rmi.Remote{

  public final static String LOOKUP =   "Academicystem";

  public String getRequisition(int option, String disciplineId, int user, String comment) throws java.rmi.RemoteException;
}
