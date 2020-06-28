build:
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	-o ../GameEngine \
	-I"./lib/lua" \
	-L"./lib/lua" \
	-llua \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

clean:
	rm ../GameEngine;

run:
	../GameEngine;
