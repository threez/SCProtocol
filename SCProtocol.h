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

#ifndef _SCProtocol_h
#define _SCProtocol_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class SCProtocol {
private:
  typedef void (*SCProtocolCallback) (char* data);
  struct SCProtocolCommand {
    int id;
    SCProtocolCallback callback;
    int bytes;
  }* commands;
  int countCommands, maxCommands;
  SCProtocolCommand* calledCommand;
  int bytesLeft;
  char* buffer;
  int bufferCursor;
  boolean commandMode;
  
public:
  SCProtocol();
  ~SCProtocol();
  void attach(int, SCProtocolCallback, int);
  void process(int);
  
private:
  void parseNext(int);
  void parseCommand(int);
  void execute();
  void resizeTo(int);
};

#endif
