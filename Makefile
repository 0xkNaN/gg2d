all:
	g++ ./main.cpp ./gg2d/*.cpp -lstdc++ -lSDL2 -lSDL2_image -lz -o game
# g++ ./main.cpp ./framework/*.cpp ./framework/include/**/*.cpp -lstdc++ -lSDL2 -lSDL2_image -lz -o game