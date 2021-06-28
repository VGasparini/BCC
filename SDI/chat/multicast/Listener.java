import java.io.*;
import java.net.*;

import java.nio.file.Files;
import java.nio.file.Paths;

class Listener extends Thread {

  private static MulticastClient client;
  private static MulticastSocket multicastSocket = null;
  private static DatagramPacket inPacket = null;
  private static byte[] inBuf = new byte[256];
  private int count = 1;

  public Listener(MulticastClient client) {
    this.client = client;
  }

  public void run() {
    try {

      multicastSocket = new MulticastSocket(8888);
      InetAddress address = InetAddress.getByName("224.0.0.6");

      multicastSocket.joinGroup(address);
    } catch (UnknownHostException e) {
      System.out.println("Host[Listener:27]: " + e);
    } catch (IOException e) {
      System.out.println("IO[Listener:29]: " + e);
    }
    try {
      while (!client.closed) {
        inPacket = new DatagramPacket(inBuf, inBuf.length);
        multicastSocket.receive(inPacket);
        String request = new String(inBuf, 0, inPacket.getLength());
        String requestNickname = (request.split(">")[0]).replace("<", "");
        boolean isFromSelf = requestNickname.startsWith(client.clientName);
        // System.out.println(request);
        if (request.startsWith("<"+ requestNickname +"> sending file")) {
            String fileData = "";
            inPacket = new DatagramPacket(inBuf, inBuf.length);
            multicastSocket.receive(inPacket);
            request = new String(inBuf, 0, inPacket.getLength());
            while (!request.startsWith("\0")) {
              fileData += request;
              inPacket = new DatagramPacket(inBuf, inBuf.length);
              multicastSocket.receive(inPacket);
              request = new String(inBuf, 0, inPacket.getLength());
            }
            try {
              if (!isFromSelf){
                  String path = new String(client.basePath + "/data/received/" + client.clientName + "/sample.client");
                  Files.write(Paths.get(path), fileData.getBytes());
                  System.out.println("New file received!");
              } else {
                  System.out.println("File sended");
              }
            } catch (IOException e) {
              System.out.println("IO[Listener:54]: " + e.getMessage());
            }
        } else if (request.contains("\0")) {
            System.out.println("New file received!");
        } else {
            System.out.println(request);
            try {
              String path = new String(client.basePath + "/data/received/" + client.clientName + "/" + requestNickname
                  + "_" + (count++) + ".client");
              Files.write(Paths.get(path), request.getBytes());
            } catch (IOException e) {
              System.out.println("IO[Listener:65]: " + e.getMessage());
            }
        }

      }
    } catch (IOException e) {
      System.out.println("IO[Listener:71]: " + e.getMessage());
    }
  }
}
