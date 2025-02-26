##
## EPITECH PROJECT, 2025
## SOURCES_MK
## File description:
## Sources for Makefile
##

VPATH += src/

SRC += src/Main.cpp

SRC += src/Exception/AException.cpp

SRC += src/Utilities/Utilities.cpp

SRC += src/Parser/Parser.cpp

SRC += src/User/User.cpp \
	src/User/Manager.cpp

SRC += src/Server/Server.cpp

SRC += src/Server/Session/Manager.cpp \
	src/Server/Session/Session.cpp

SRC += src/Server/Socket/Socket.cpp

SRC += src/Server/Command/Manager.cpp \
	src/Server/Command/Commands/Help.cpp \
	src/Server/Command/Commands/User.cpp \
	src/Server/Command/Commands/Pass.cpp \
	src/Server/Command/Commands/Noop.cpp \
	src/Server/Command/Commands/Quit.cpp
