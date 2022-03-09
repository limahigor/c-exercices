all:
	gcc src/datalogger.c -c `pkg-config --cflags --libs gtk+-3.0`
	gcc src/callbacks.c -c `pkg-config --cflags --libs gtk+-3.0`
	gcc src/time_module.c -c `pkg-config --cflags --libs gtk+-3.0`
	gcc src/processor.c -c `pkg-config --cflags --libs gtk+-3.0`
	mv *.o build/
	gcc -O3 -s -o testes/datalogger build/datalogger.o build/callbacks.o build/time_module.o build/processor.o `pkg-config --cflags --libs gtk+-3.0` -lm

datalogger:
	gcc src/datalogger.c -c `pkg-config --cflags --libs gtk+-3.0`
	mv datalogger.o build/

callbacks:
	gcc src/callbacks.c -c `pkg-config --cflags --libs gtk+-3.0`
	mv callbacks.o build/
	
time:
	gcc src/time_module.c -c `pkg-config --cflags --libs gtk+-3.0`
	mv time_module.o build/

join:
	gcc -O3 -s -o testes/datalogger build/datalogger.o build/callbacks.o build/time_module.o `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm testes/datalogger
