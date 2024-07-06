main: src/main.c
	gcc src/main.c glad/glad.c -o main -lGL -lglfw

clean:
	rm main
