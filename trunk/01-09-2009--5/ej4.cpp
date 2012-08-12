#include <pthread.h>

class Thread {
// esta es la implementacion basica de un thread. Todo hilo tendra que heredar de este.
protected:
	// este es el metodo que habra que sobreescribir. Es el metodo que hara el trabajo
	// que querramos que haga el thread.
	virtual void correr() = 0;
private:
	// esta funcion de callback es importante, es la que llama pthread_create
	static void* callback(void* aux) {
		((Thread*) aux)->correr();
		return 0;
	}
	// struct que tiene la informacion de pthread
	pthread_t thread;
	
public:
	Thread(): corriendo(false){}
	
	virtual ~Thread() {}
	
	// al iniciar el hilo, se ahce pthread_create
	// los parametros son:
	// 1) la estructura pthread_t
	// 2) atributos que se le quiera asignar al thread en momento de creacion (NULL si no se quiere nada)
	// 3) puntero a la funcion de callbak que va a llamar
	// 4) argumento que recibira la funcion de callback
	void iniciar() {
		corriendo = true;
		pthread_create(thread, 0, Thread::callback, this);
	}
	
	void detener() {
		corriendo = false;
	}
	
	// Este metodo sincroniza los hilos
	// la funcion POSIX llamada es pthread_join, que recibe:
	// 1) la estructura pthread_t que este ejecutandose
	// 2) Un puntero a donde queremos que guarde el valor de retorno de la funcion de callback,
	// si no queremos que nos retorne nada, pasamos NULL
	void sincronizar() {
		pthread_join(thread, NULL); 
	}
	
	bool corriendo() {
		return corriendo;
	}
};

class Producer : public Thread {
// como atributo privado tendria algo del estilo:
// ColaBloqueante& cola;
// que seria una referencia a una cola compartida entre el Producer y el Consumer
public:
	void run() {
		while (corriendo()) {
			// aca haria cosas que luego encolaria
			// por ejemplo, espero cosas de un socket
			// o de un archivo
		}
	}
};

class Consumer : public Thread {
// como atributo privado tendria algo del estilo:
// ColaBloqueante& cola;
// que seria una referencia a una cola compartida entre el Producer y el Consumer
public:
	void run() {
		while (corriendo()) {
			// aca estaria esperando a que haya elementos en una
			// cola
			// si los hay, ejecuto lo que tenga que ejecutar
			// por ejemplo, mostrar los datos por pantalla
		}
	}
};
