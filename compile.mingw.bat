
rem set INC_DIR_SOCKET=socket\src
rem set GCC_FLAGS=-I %INC_DIR_SOCKET%

mkdir compiled 
mkdir debug
g++ -I lib\socket\src -I lib\base64 -c lib\webserver\webserver.cpp -o compiled\webserver.o
g++ -I lib\socket\src           -c main.cpp -o compiled\main.o
g++                         -c lib\stdHelpers\stdHelpers.cpp -o compiled\stdHelpers.o
g++                         -c lib\UrlHelper\UrlHelper.cpp -o compiled\UrlHelper.o
g++ -I lib\socket\src           -c lib\socket\src\Socket.cpp -o compiled\Socket.o
g++                         -c lib\base64\base64.cpp     -o compiled\base64.o

g++                         -c lib\controllers\controllers.cpp     -o compiled\controllers.o
g++                         -c lib\services\data\data.cpp     -o compiled\data.o
g++                         -c lib\services\store\store.cpp     -o compiled\store.o

g++ compiled\webserver.o compiled\base64.o compiled\main.o compiled\stdHelpers.o compiled\UrlHelper.o compiled\Socket.o compiled\controllers.o compiled\data.o compiled\store.o -lwsock32 -o debug\WebServer.exe

rmdir / Q / S compiled

.\debug\Webserver.exe

