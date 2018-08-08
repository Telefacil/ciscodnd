# ciscodnd
To enable and disable the dnd (do not disturb) feature on Cisco SPA phones. 

## Why?
In an office with many employees the telephones if not turned off may ring and ring without the owner to take it. When runned on the startup and shutdown scripts the telephone will be only operative when the computer is on.

## How it works?
Usage: 
```bash
[sudo] ciscodnd [ip] dnd/-dnd
```
* dnd option: Enables "Do not disturb"
* -dnd option: Disables "Do not disturb"
* If you don't provide an IP, you have to put it on "config" file, like the example
```
ip=192.168.0.78
```
* Depending on your temporary directory permissions, you have to run it with sudo (only Linux and macOS)

For example: 
```bash
ciscodnd 192.168.0.78 dnd #Enables "Do not disturb" on phone with that IP
```

## How to compile it?
### Compile on Linux or macOS
You just need to run:
```bash
make
```

### Compile on Windows
Run Visual Studio and build the project.

Check that you have Microsoft Visual C++ Redistributable Package installed.

## Information and compiled version in Windows and macOS

### En Español 

### In English 


## About us

Check one of our services (in Spanish) or if you are in Spain and need a virtual PBX.
https://www.telefacil.com/centralita-virtual.php

Our company (in Spanish):
https://www.duocom.es/
