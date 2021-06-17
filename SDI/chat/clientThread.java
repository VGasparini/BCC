import java.io.*;
import java.net.*;
import java.util.*;

import java.nio.file.Files;
import java.nio.file.Paths;

class clientThread extends Thread {

  private BufferedReader inFromServer = null;
  private BufferedReader inFromFile = null;
  private PrintStream outToServer = null;
  private Socket clientSocket = null;
  private final clientThread[] threads;
  private DatagramSocket socket = null;
  private int maxClientsCount;
  private DatagramPacket sendPacket = null;
  private InetAddress address = null;
  private byte[] sendData;
  final int PORT = 8888;
  private int count = 1;

  static String basePath = new String("/home/alu2020s2/gasparini/chat");

  public clientThread(Socket clientSocket, clientThread[] threads, InetAddress address, DatagramSocket socket) {
    this.clientSocket = clientSocket;
    this.address = address;
    this.threads = threads;
    this.socket = socket;
    maxClientsCount = threads.length;

    // System.out.println("New client thread connected at " + address);
  }

  public void run() {
    int maxClientsCount = this.maxClientsCount;
    clientThread[] threads = this.threads;

    try {
      inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
      outToServer = new PrintStream(clientSocket.getOutputStream());
      outToServer.println("Set a nickname!");
      String nickname = inFromServer.readLine();
      File folder = new File(basePath + "/data/sent/" + nickname);
      folder.mkdirs();
      outToServer.println("Hello " + nickname);
      outToServer.println("send_file To send the example file\n/quit To leave from chat");

      sendData = ("<" + nickname + "> logged in").getBytes();
      sendPacket = new DatagramPacket(sendData, sendData.length, address, PORT);
      socket.send(sendPacket);

      while (true) {
        String request = inFromServer.readLine();
        if (request.startsWith("/quit")) {
          break;
        } else if (request.startsWith("/send_file")) {
          sendData = ("<" + nickname + "> sending file").getBytes();
          sendPacket = new DatagramPacket(sendData, sendData.length, address, PORT);
          socket.send(sendPacket);
          try {
            StringBuilder fileText = new StringBuilder();
            String path = new String(basePath + "/data/server/sample.serv");
            inFromFile = new BufferedReader(new FileReader(new File(path)));
            while (inFromFile.ready()) {
              while (fileText.length() < 100 && inFromFile.ready()) {
                fileText.append((char) inFromFile.read());
              }
              sendData = fileText.toString().getBytes();
              sendPacket = new DatagramPacket(sendData, sendData.length, address, PORT);
              socket.send(sendPacket);
            }
            sendData = "\0".getBytes();
            sendPacket = new DatagramPacket(sendData, sendData.length, address, PORT);
            socket.send(sendPacket);
          } catch (SocketException e) {
            System.out.println("Socket: " + e.getMessage());
          } catch (IOException e) {
            System.out.println("IO: " + e.getMessage());
          }
        } else {
          sendData = ("<" + nickname + ">: " + request).getBytes();
          sendPacket = new DatagramPacket(sendData, sendData.length, address, PORT);

          socket.send(sendPacket);
        }
      }

      outToServer.println("disconnecting <" + nickname + ">");
      outToServer.close();

      try {
        Thread.sleep(2000);
      } catch (InterruptedException ie) {
      }
      sendData = ("<" + nickname + "> disconnected").getBytes();
      sendPacket = new DatagramPacket(sendData, sendData.length, address, PORT);

      socket.send(sendPacket);

      for (int i = 0; i < maxClientsCount; i++) {
        if (threads[i] == this) {
          threads[i] = null;
        }
      }

      inFromServer.close();
      clientSocket.close();
    } catch (IOException e) {
      System.out.println("IO: " + e.getMessage());
    }
  }
}
