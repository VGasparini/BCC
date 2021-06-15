import java.io.*;
import java.net.*;

import java.nio.file.Files;
import java.nio.file.Paths;

public class MultiThreadMultiCastClient implements Runnable {

    private static Socket clientSocket = null;
    private static PrintStream outToServer = null;
    private static BufferedReader inFromServer = null;
    private static BufferedReader inFromUser = null;
    public static boolean closed = false;
    public String clientName;
    public static String nickname;
    private static int msgcounter = 1;
    private static InetAddress address = null;

    static String basePath = new String("/home/alu2020s2/gasparini");

    public static void main(String[] args) {
        int portNumber = 2891;
        String host = "ens1";

        System.out.println("Client: connected to host " + host + ":" + portNumber);

        try {
            address = InetAddress.getByName(host);
            clientSocket = new Socket(address, portNumber);
            inFromUser = new BufferedReader(new InputStreamReader(System.in));
            outToServer = new PrintStream(clientSocket.getOutputStream());
            inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        } catch (UnknownHostException e) {
            System.out.println("Host: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO: " + e.getMessage());
        }

        if (clientSocket != null && outToServer != null && inFromServer != null) {
            try {
                new Thread(new MultiThreadMultiCastClient()).start();
                while (!closed) {
                    String tag = new String(inFromUser.readLine().trim());
                    outToServer.println(tag);
                    try {
                        String path = new String(basePath + "/data/sent/" + nickname + "_" + msgcounter + ".chat");
                        Files.write(Paths.get(path), tag.getBytes());
                        msgcounter++;
                    } catch (IOException e) {
                        System.out.println("IO: " + e.getMessage());
                    }
                }
                outToServer.close();
                inFromServer.close();
                clientSocket.close();
            } catch (IOException e) {
                System.out.println("IO: " + e.getMessage());
            }
        }
    }

    public void run() {
        String responseLine;
        boolean getNickname = true;

        try {
            while ((responseLine = inFromServer.readLine()) != null) {
                if (!responseLine.startsWith("Set a nickname") && getNickname) {
                    clientName = responseLine.replace("Hello ", "");
                    nickname = clientName;
                    getNickname = false;
                    File folder = new File(basePath + "/data/recieved/" + nickname);
                    folder.mkdirs();
                    new Thread(new Listener(this)).start();
                }
                System.out.println(responseLine);
                if (responseLine.startsWith("disconnecting")) {
                    break;
                }
            }
            closed = true;
        } catch (IOException e) {
            System.out.println("IO: " + e.getMessage());
        }
    }
}
