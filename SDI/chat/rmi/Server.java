import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;
import java.util.*;
import java.io.*;

public class Server implements Data {
  public Server() {
  }

  public String setterName = null, fileStream = null;
  public int messageID = 0;

  public void saveData() throws Exception {
    try {
      FileWriter output = new FileWriter("server/" + setterName + "_" + messageID + ".serv");
      output.write(fileStream);
      output.close();
    } catch (IOException e) {
      System.out.println("IO[server:20]: " + e.getMessage());
    }
  }

  public static void main(String[] args) {
    try {
      Server server = new Server();
      Data stub = (Data) UnicastRemoteObject.exportObject(server, 0);
      Registry registry = LocateRegistry.createRegistry(2891);
      registry.bind("gasparini_frohlich_server", stub);
      System.out.println("Server: running!");
    } catch (Exception e) {
      System.out.println("RMI[server:32]: " + e.getMessage());
    }
  }

  public List<String> getData() throws RemoteException {
    List<String> receiveData = new ArrayList<String>();
    receiveData.add(setterName);
    receiveData.add(fileStream);
    return receiveData;
  }

  public void setData(List<String> receiveData) throws RemoteException {
    try {
      messageID++;
      setterName = receiveData.get(0);
      fileStream = receiveData.get(1);
      System.out.println("<" + setterName + "> sent a file");
      saveData();
    } catch (Exception e) {
      System.out.println("SetData[server:51]: " + e.getMessage());
    }
  }

  public int getID() throws RemoteException {
    return messageID;
  }

  public String getSetter() throws RemoteException {
    return setterName;
  }
}
