rm -f z--.exe dummy.cpp

g++ z--.cpp src/lexer.cpp src/parser.cpp src/emitter.cpp -o z--.exe

z-- test.z