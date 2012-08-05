/*
  SCProtocol - Arduino libary for simple command based protocols
  Copyright (c) 2012 Vincent Landgraf.  All right reserved.
  
  Project home: https://github.com/threez/SCProtocol

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "SCProtocol.h"

SCProtocol::SCProtocol()
:maxCommands(1), countCommands(0), commandMode(false), bytesLeft(0), calledCommand(NULL), buffer(NULL), bufferCursor(0)
{
  resizeTo(1);
}

SCProtocol::~SCProtocol() {
  free(commands);
  if (buffer != NULL) free(buffer);
}

void SCProtocol::attach(int id, SCProtocolCallback callback, int bytes) {
  if (countCommands + 1 >= maxCommands) resizeTo(maxCommands * 2);
  
  SCProtocolCommand *command = &commands[countCommands++];
  command->id = id;
  command->callback = callback;
  command->bytes = bytes;
}

void SCProtocol::process(int input) {
  if (commandMode) {
    parseNext(input);
  } else {
    parseCommand(input);
  }
}

void SCProtocol::parseNext(int input) {
  buffer[bufferCursor++] = (char)input;
  if (bytesLeft == bufferCursor) execute();
}

void SCProtocol::parseCommand(int input) {
  for (int i = 0; i < countCommands; i++) {
    if (commands[i].id == input) {
      calledCommand = &commands[i];
      break;
    }
  }
  
  if (calledCommand != NULL) {
    commandMode = true;
    bytesLeft = calledCommand->bytes;
    
    if (bytesLeft == 0) execute();
    else {
      if (buffer != NULL) free(buffer);
      buffer = (char *)malloc(sizeof(char) * calledCommand->bytes + 1);
      bufferCursor = 0;
    }
  } else {
    Serial.println("BAD Command unknown");
  }
}

void SCProtocol::execute() {
  buffer[bytesLeft] = '\0';
  (*calledCommand->callback)(buffer);
  calledCommand = NULL;
  commandMode = false;
}

void SCProtocol::resizeTo(int newMaxCommands) {
  commands = (SCProtocolCommand*)realloc(commands, sizeof(SCProtocolCommand) * newMaxCommands);
  maxCommands = newMaxCommands;
}
