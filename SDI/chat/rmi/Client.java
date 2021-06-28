import java.rmi.registry.*;
import java.io.*;
import java.util.*;

public class Client implements Runnable {
  private static Integer messageID = 0;
  static String host, nickname = null, fileStream;
  static Registry registry;
  static Data stub;
  public static boolean connected = false;
  public static Thread clientThread = null;
  static int time_count = 5;

  public static void downloadFile(String fileName) throws Exception {
    try {
      String path = "client/" + nickname;
      new File(path).mkdir();
      FileWriter output = new FileWriter(path + "/" + fileName);
      output.write(fileStream);
      output.close();
    } catch (IOException e) {
      System.out.println("IO[client:23]: " + e.getMessage());
    }
  }

  public static void uploadFile(String filePath) throws Exception {
    try {
      InputStream input = new FileInputStream(filePath);
      byte[] array = new byte[1024 * 1024];
      input.read(array);
      input.close();
      fileStream = new String(array);
      fileStream = fileStream.trim();
    } catch (Exception e) {
      throw e;
    }
  }

  public static void receive() throws Exception {
    try {
      connect();
      int stubID = stub.getID();
      if (stubID != messageID) {
        String s = stub.getSetter();
        messageID = stubID;
        if (!s.equals(nickname) && s != null) {
          messageID = stubID;
          List<String> stubData = stub.getData();
          fileStream = stubData.get(1).trim();
          String fileName = new String(stubData.get(0) + "_" + stubID + ".client");
          downloadFile(fileName);
          System.out.println("<" + stubData.get(0) + "> sent a file");
        }
      }
    } catch (Exception e) {
      System.out.println("RMI[client:63]: " + e.getMessage());
      throw e;
    }
  }

  public static void sendFile() throws Exception {
    try {
      connect();
      List<String> sendData = new ArrayList<String>();
      sendData.add(nickname);
      sendData.add(fileStream);
      stub.setData(sendData);
      System.out.println("<" + nickname + "> send file");
    } catch (Exception e) {
      System.out.println("SendFile[client:96]: " + e.getMessage());
      throw e;
    }
  }

  public static void connect() throws Exception {
    try {
      registry = LocateRegistry.getRegistry(host, 2891);
      stub = (Data) registry.lookup("gasparini_frohlich_server");
      if (!connected)
        System.out.println("<" + nickname + "> logged in");
      connected = true;
    } catch (Exception e) {
      connected = false;
      System.out.println("RMI[client:96]: " + e.getMessage());
      throw e;
    }
  }

  public static void main(String[] args) {
    host = "ens1";

    try {
      BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
      System.out.println("Set a nickname!");
      nickname = inFromUser.readLine();
    } catch (IOException e) {
      System.out.println("IO[client:123]: " + e.getMessage());
    }

    while (true) {
      try {
        receive();
        time_count = 5;
        if (clientThread == null) {
					System.out.println("/send filename - To send a file located on project root folder (try with 1Mb sample named 'sample.file')\n/quit - To leave from chat\n/help - List commands ");
          clientThread = new Thread(new Client());
          clientThread.start();
					//break;
        }
      } catch (Exception ex) {
        if (time_count < 20) {
          System.out.println("Trying to reconnect in " + time_count + " seconds");
          connected = false;
        } else {
          System.out.println("Reconnect attempt failed\nExiting...");
          System.exit(0);
        }
        try {
          Thread.sleep(time_count * 1000);
          time_count += 5;
        } catch (Exception ew) {
          System.out.println("Reconnect attempt failed\nExiting...");
          System.exit(0);
        }
      }
    }
  }

  public void run() {
    BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
    String request;
    while (true) {
      try {
      	request = inFromUser.readLine();
				if (request.startsWith("/send ")) {
  	      uploadFile(request.replace("/send ", ""));
	        sendFile();
				} else if (request.startsWith("/quit")) {
					System.exit(0);
				} else if (request.startsWith("/help")) {
					System.out.println("/send filename - To send a file located on project root folder (try with 1Mb sample named 'sample.file')\n/quit - To leave from chat\n/help - List commands ");
				} else {
					System.out.println("Comando nao reconhecido, utilize /help para ver a lista de comandos");
				}

      } catch (Exception e) {
        System.out.println("SendFile[client:138]: " + e.getMessage());
      }
    }
  }
}
