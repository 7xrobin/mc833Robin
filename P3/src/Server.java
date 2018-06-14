

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

/* Classe que implementa o servidor do sistema para o cliente */

public class Server extends AcademicImpl{
  protected Server() throws RemoteException {
  }

  public static void main(String[] args) {

    try {
      // Instancia o objeto com as funções providas
      AcademicImpl aca = new AcademicImpl();

      System.out.println("Inicializando servidor...");


      // Coloca o serviço no registro de objetos do RMI
      LocateRegistry.createRegistry(1099); // 1099 é a porta padrão
      Naming.rebind(AcademicInterface.LOOKUP, aca); // modifica o nome para aquele acordado na interface
      System.out.println("Servidor pronto.");

    } catch (RemoteException e) {
      e.printStackTrace();
    } catch (MalformedURLException e) {
      e.printStackTrace();
    }
  }
}

