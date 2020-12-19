# UDP-client-server
App for Windows in CPP implementing client-server connection via UDP using winsock2 and ws2tcpip.

The app consists from two separate programs: UDPClient and UDPServer.

Both programs can be run from Visual Studio (.sln and .vcxproj files are provided) or from makefiles using MinGW (just type make in console while being in project folder). Static library ws2_32.lib is necessary, as it is linked both in VS (with pragma comment) and g++.
