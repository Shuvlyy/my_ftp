##
## EPITECH PROJECT, 2025
## SOURCES_MK
## File description:
## Sources for Makefile
##

VPATH += src/

SRC += src/Main.cpp

SRC += src/Exception/AException.cpp

SRC += src/Utilities/Utilities.cpp \
	src/Utilities/DirContentFormatter.cpp

SRC += src/Logger/Logger.cpp \
	src/Logger/Log.cpp

SRC += src/Parser/Parser.cpp

SRC += src/Server/Signal/Manager.cpp \
	src/Server/Signal/Handlers/Int.cpp \
	src/Server/Signal/Handlers/Term.cpp

SRC += src/User/User.cpp \
	src/User/Manager.cpp

SRC += src/Server/Server.cpp

SRC += src/Server/Session/Manager.cpp \
	src/Server/Session/Session.cpp

SRC += src/Server/Socket/Socket.cpp \
	src/Server/Socket/DataSocket.cpp

SRC += src/Server/Command/Manager.cpp \
	src/Server/Command/Commands/Help.cpp \
	src/Server/Command/Commands/User.cpp \
	src/Server/Command/Commands/Pass.cpp \
	src/Server/Command/Commands/Noop.cpp \
	src/Server/Command/Commands/Quit.cpp \
	src/Server/Command/Commands/Cwd.cpp \
	src/Server/Command/Commands/Pwd.cpp \
	src/Server/Command/Commands/Cdup.cpp \
	src/Server/Command/Commands/Dele.cpp \
	src/Server/Command/Commands/Port.cpp \
	src/Server/Command/Commands/Pasv.cpp \
	src/Server/Command/Commands/List.cpp \
	src/Server/Command/Commands/Type.cpp \
	src/Server/Command/Commands/Stor.cpp \
	src/Server/Command/Commands/Retr.cpp

#SRC += Dashboard/Dashboard.cpp \
#	Dashboard/View/AView.cpp \
#	Dashboard/View/Views/Main/Main.cpp \
#	Dashboard/View/Views/LogViewer/LogViewer.cpp
