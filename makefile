all: 
	gcc main.c auxiliar.c -o main
	./main NRU compressor.log 16 2
	./main LRU compressor.log 16 2

	./main NRU compressor.log 16 4
	./main LRU compressor.log 16 4
	
	./main NRU matriz.log 8 2
	./main LRU matriz.log 8 2
	
	./main NRU compilador.log 16 2
	./main LRU compilador.log 16 2

	./main NRU simulador.log 16 2
	./main LRU simulador.log 16 2
	
	./main NRU simulador.log 16 4
	./main LRU simulador.log 16 4