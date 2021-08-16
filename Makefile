all : Server_system Client_system

Server_system:
	cd Server/src; $(MAKE)

Client_system:
	cd Client/src; $(MAKE)