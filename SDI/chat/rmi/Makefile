COMPILER = javac
TARGET = Client.class Server.class Data.class

all: $(TARGET) setup

Client.class: Client.java
	$(COMPILER) Client.java

Server.class: Server.java
	$(COMPILER) Server.java

Data.class: Data.java
	$(COMPILER) Data.java

run_server:
	java Server

run_client:
	java Client

setup:
	mkdir server
	mkdir client
	base64 /dev/urandom | head -c 1MB > ./sample.file

clean:
	rm -rf *~ $(TARGET) server client