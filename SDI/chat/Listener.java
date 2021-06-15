import java.io.*;
import java.net.*;

import java.nio.file.Files;
import java.nio.file.Paths;

class Listener extends Thread {

  private static MultiThreadMultiCastClient client;
  private static MulticastSocket multicastSocket = null;
  private static DatagramPacket inPacket = null;
  private static byte[] inBuf = new byte[256];
  private int count = 1;

  public Listener(MultiThreadMultiCastClient client) {
    this.client = client;
  }

  public void run() {
    try {

      multicastSocket = new MulticastSocket(8888);
      InetAddress address = InetAddress.getByName("224.0.0.6");

      multicastSocket.joinGroup(address);
    } catch (UnknownHostException e) {
      System.err.println(e);
    } catch (IOException e) {
      System.err.println(e);
    }
    try {
      while (!client.closed) {
        inPacket = new DatagramPacket(inBuf, inBuf.length);
        multicastSocket.receive(inPacket);
        String request = new String(inBuf, 0, inPacket.getLength());
        System.out.println(request);
        try {
          String path = new String(
              client.basePath + "/data/recieved/" + client.clientName + "-" + (count++) + ".client");
          Files.write(Paths.get(path), request.getBytes());
        } catch (IOException e) {
          System.out.println("IO: " + e.getMessage());
        }
      }
    } catch (IOException e) {
      System.out.println("IO: " + e.getMessage());
    }
  }
}
