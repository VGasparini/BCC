import java.io.*;
import java.net.*;

public class FileTransfer{
	private DatagramSocket auxSocket = null;
	private int packetSize;
	private byte[] transferData;

	public FileTransfer(DatagramSocket auxSocket, int packetSize){
		this.auxSocket = auxSocket;
		this.packetSize = packetSize;
		this.transferData = new byte[packetSize];
	}

	public void sendFile(File transferFile, InetAddress IPAddress, int port) throws Exception{
            long length = transferFile.length();
            int offset = 0;
            long parts = length/256;
            InputStream in = new FileInputStream(transferFile);
            int i;
            for (i = 0; i < parts; i++){
                in.read(this.transferData);
                offset += 256;
                DatagramPacket sendPacket = new DatagramPacket(this.transferData,this.transferData.length,IPAddress,port);
                this.auxSocket.send(sendPacket);
            }
            int aux = (int)(length%256);
            if (aux > 0){
                in.read(this.transferData);
                for (i = aux; i < 256; i++){
                        this.transferData[i] = '\0';
                }
                DatagramPacket sendPacket = new DatagramPacket(this.transferData,this.transferData.length,IPAddress,port);
                this.auxSocket.send(sendPacket);
            }
            this.transferData[0] = '\0';
            DatagramPacket sendPacket = new DatagramPacket(this.transferData,this.transferData.length,IPAddress,port);
            this.auxSocket.send(sendPacket);
	}

	public void receiveFile(FileWriter transferFile) throws Exception {
		DatagramPacket receivePacket = new DatagramPacket(this.transferData, this.transferData.length);
        	while (true){
                	this.auxSocket.receive(receivePacket);
                	String s = new String(receivePacket.getData());
					System.out.println(s);
                	if (s.charAt(0) == '\0'){
                        	break;
                	} else {
                        	transferFile.write(s);
                	}
        	}
	}
}
