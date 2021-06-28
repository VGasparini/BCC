import java.io.*;
import java.net.*;

public class MulticastServer {

  private static ServerSocket serverSocket = null;
  private static Socket clientSocket = null;

  private static final int maxClientsCount = 10;
  private static final clientThread[] threads = new clientThread[maxClientsCount];
  private static InetAddress address = null;

  static DatagramSocket socket = null;

  static String basePath = new String("/home/alu2020s2/gasparini/chat");

  public static void main(String args[]) {

    File folder = new File(basePath + "/data/received");
    folder.mkdirs();
    folder = new File(basePath + "/data/sent");
    folder.mkdirs();

    int portNumber = 2891;
    System.out.println("Server: running on port " + portNumber);

    try {
      socket = new DatagramSocket();
      address = InetAddress.getByName("224.0.0.6");
    } catch (IOException e) {
      System.out.println("IO: " + e.getMessage());
    }

    try {
      serverSocket = new ServerSocket(portNumber);
    } catch (IOException e) {
      System.out.println("IO: " + e.getMessage());
    }

    while (true) {
      try {
        clientSocket = serverSocket.accept();
        int i = 0;
        for (i = 0; i < maxClientsCount; i++) {
          if (threads[i] == null) {
            (threads[i] = new clientThread(clientSocket, threads, address, socket)).start();
            break;
          }
        }
        if (i == maxClientsCount) {
          PrintStream os = new PrintStream(clientSocket.getOutputStream());
          os.println("Max connections reached");
          os.close();
          clientSocket.close();
        }
      } catch (IOException e) {
        System.out.println("IO: " + e.getMessage());
      }
    }
  }
}
