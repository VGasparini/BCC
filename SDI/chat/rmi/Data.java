
import java.rmi.*;
import java.util.*;

public interface Data extends Remote {
   public int getID() throws RemoteException;

   public List<String> getData() throws RemoteException;

   public String getSetter() throws RemoteException;

   public void setData(List<String> s) throws RemoteException;
}
