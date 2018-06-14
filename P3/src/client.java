
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.util.Scanner;

public class client {

    //Proxy local
    protected  static AcademicInterface stub = null;

    public static void main(String[] args) throws RemoteException {
        try {
            stub = (AcademicInterface) Naming.lookup(AcademicInterface.LOOKUP);
        }catch (Exception e){
            System.err.println("Exception: " + e.getMessage() );
        }
        executeTasks();
    }

    public static void executeTasks() throws RemoteException {
        Scanner scanner = new Scanner(System.in);
        int option;
        int user = 0;
        String comment = "";
        String disId = "";
        long[] times = new long[30];

        System.out.println("Digite a Opção que deseja executar (Números de 1-6): ");
        option  = scanner.nextInt();

        if(option >2) {
            System.out.println("Digite o identificador da disciplina (MC102 por exemplo): ");
            disId = scanner.next();
            if (option == 6) {
                System.out.println("Digite 0 se for aluno ou 1 se professor:  ");
                user = scanner.nextInt();
                System.out.println("Digite seu comentario: ");
                comment = scanner.next();
            }
        }

        for (int i = 0; i<30; i++){
            long startTime = System.nanoTime(); // Inicia a contagem do tempo
            System.out.println(stub.getRequisition(option, disId, user, comment));
            times[i] = System.nanoTime() - startTime;
        }
        for (int i = 0; i<30; i++){
            System.out.println(times[i]);
        }

        executeTasks();
    }
}
