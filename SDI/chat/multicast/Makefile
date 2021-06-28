COMPILER = javac
TARGET = clientThread.class Listener.class MulticastClient.class MulticastServer.class

all: $(TARGET) setup

clientThread.class: clientThread.java
	$(COMPILER) clientThread.java

Listener.class: Listener.java
	$(COMPILER) Listener.java

MulticastClient.class: MulticastClient.java
	$(COMPILER) MulticastClient.java

MulticastServer.class: MulticastServer.java
	$(COMPILER) MulticastServer.java

run_server:
	java MulticastServer

run_client:
	java MulticastClient

setup:
	mkdir data
	mkdir data/server
	base64 /dev/urandom | head -c 64 > ./data/server/sample.serv

clean:
	rm -rf *~ $(TARGET) data 