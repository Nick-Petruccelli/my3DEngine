main: src/main.c
	gcc src/main.c src/shaders/shaders.c glad/glad.c -o main -lGL -lglfw -lm

clean:
	rm main
