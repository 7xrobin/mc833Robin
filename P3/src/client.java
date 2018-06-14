
import java.rmi.Naming;
import java.util.Scanner;

public class client {

    //Proxy local
    protected  static AcademicInterface stub = null;

    public static void main(String[] args){

      Scanner scanner = new Scanner(System.in);
      System.out.println("Opção: ");
      int option  = scanner.nextInt();
      try {
        stub = (AcademicInterface) Naming.lookup(AcademicInterface.LOOKUP);
        System.out.println(stub.getRequisition(option, "", 0, ""));
      }catch (Exception e){
        System.err.println("Exception: " + e.getMessage() );
      }


    }
}
