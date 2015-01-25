wsclient
========

Simple websocket CLI (command line interface) client

Build
-----

./configure
make

Windows
-------
wsclient.vcxproj 

Dependencies
------------
WebSocket++	http://www.zaphoyd.com/websocketpp/
argtable2.13
boost

Usage
-----

wsclient
 [-vuh] <url> [-l <locale>]
websocket CLI client
  <url>                     e.g. ws://localhost:8084/
  -v, --verbose             connection messages to stderr
  -l, --locale=<locale>     e.g. russian_russia.1251, ru_RU.UTF-8
  -u, --utf8                locale use UTF-8
  -h, --help                print this help and exit

Examples:

./wsclient ws://localhost:8084/



