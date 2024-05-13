rm -f z--.exe output.exe output.cpp

g++ z--.cpp src/lexer.cpp src/parser.cpp src/emitter.cpp -o z--.exe

z-- test.z