#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

sem_t sempong,semping;

void ping(int n)
{
  //Printea ping
  for(int i=0;i<n;i++){
     sem_down(semping);
     printf("ping\n");
     sem_up(sempong);
  }
}

void pong(int n)
{
  //Printea ping
  for(int i=0;i<n;i++){
     sem_down(sempong);
     printf("pong\n");
     sem_up(semping);
  }
}

int
main(int argc, char *argv[])
{
  sem_open(sempong,0); //Inicializo el semaforo con un recurso
  sem_open(semping,1); //Inicializo el semaforo sin recursos esperando al recurso del otro semaforo
  //Fujo de programa -> 1 forkeo para tener 2 semaforos funcionando al mismo tiempo
  //                 -> 2 arranco ping con 1 recurso y pong con 0 
  //                 -> 3 libero recurso de un semaforo para entregarselo al otro

  fd = fork(); //Forkeo
  if (fd < 0) 
  {
    printf("Fork error\n");
    exit(0);
  } else if (fd == 0) //Es el hijo
  {
    ping(n);
  } else 
  {
    //Hace falta el wait?
    pong(n); // ->Tiene que ejecutar n veces el pong esperando y liberando recursos con el hijo. PEnsalo bien pa
    wait();//NO deberia haber diferencia
  }
  
  
  sem_close(sempong);//Cierro ambos semaforos
  sem_close(semping);
}
