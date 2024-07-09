main: src/*
	gcc src/main.c src/shaders/shaders.c src/textures/textures.c glad/glad.c -o main -lGL -lglfw -lm

clean:
	rm main
