Proyecto: Proceso.o Cola_Procesos.o Despachador.o  Funciones.o
	gcc -g -o Proyecto  main.c Despachador.o Proceso.o Cola_Procesos.o Funciones.o
	gcc -o child child.c
Funciones:
	gcc -c Funciones.c
Proceso:
	gcc  -c Proceso.c
Cola: Proceso.o
	gcc -c Cola_Procesos.c
Despachador: Proceso.o Cola_Procesos.o Funciones.o
	gcc -c Despachador.c
gdb: Proyecto
	gdb --args Proyecto listaprocesos.in
run: Proyecto
	./Proyecto listaprocesos.in
Clear:
	rm *.o
	rm Proyecto
	rm child
