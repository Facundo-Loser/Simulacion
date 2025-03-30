/* External definitions for single-server queueing system. */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "lcgrand.h" /* Header file for random-number generator. */
#include "queue.h"

#define Q_LIMIT 100  /* Limit on queue length. */
#define BUSY      1  /* Mnemonics for server's being busy */
#define IDLE      0  /* and idle. */

void  initialize(void);
void  timing(void);
void  arrive(void);
void  depart(void);
void  report(void);
void  update_time_avg_stats(void);
float expon(float mean);            // sin usar
float gen_next_interarrive(void);
float  gen_next_depart(void);
void debug();
float gen_next_interarrive2(); // usa la formula de (1/lambda) * ln(1-r)
float gen_next_depart2();      // usa la formula de (1/lambda) * ln(1-r)
void arrive2();                // no genera mas nuevos arribos, solo ejecuta el existente
void end_sim();                // end the simulation if still there's people in queue

// variables:
int final_condition;           // cond finalizacion del ciclo (sin usar)
int next_event_type;           // tipo del prox event 1: arrive, 2: depart
float sim_time;                // reloj de la simulacion
int server_status;             // estado del serv 1: ocupado, 2: libre
int num_in_q;                  // number of clients in queue
float time_last_event;         // tiempo del ultimo evento
float time_next_event[3];      // [1]: prox arribo, [2]: cuando se desocupa el servidor
Queue client_queue;            // cola de clientes
int num_custs_delayed;         // numero de customers retrasados
float total_of_delays;         // acumulador de los delays de cada customer
float area_num_in_q;           // area bajo la curva del grafico de long de queue
float area_server_status;      // area bajo la curva del uso del servidor

int main(void) { /* Main function. */

    /* Initialize the simulation. */

    initialize();

    /* Run the simulation while more delays are still needed. */

    while (sim_time < 300) {
        printf("DEBUG BEGINNING OF CYCLE");
        debug();

        /* Determine the next event. */

        timing();

        /* Update time-average statistical accumulators. */

        update_time_avg_stats();

        /* Invoke the appropriate event function. */

        switch (next_event_type) {
            case 1:
                arrive();
                break;
            case 2:
                depart();
                break;
        }

        printf("DEBUG END OF CYCLE******");
        debug();
    }

    // chequear si todavia quedan clients en cola y terminar correctamente la simulacion

    end_sim();

    /* Invoke the report generator and end the simulation. */

    report();

    return 0;
}


void initialize(void)  /* Initialization function. */
{
    /* Initialize the simulation clock. */

    sim_time = 0.0;

    /* Initialize the state variables. */

    server_status   = IDLE;
    num_in_q        = 0;
    time_last_event = 0;

    // Initialize the statistical counters. num_custs_delayed, total_of_delays, area_num_in_q, area_server_status

     num_custs_delayed = 0;
     total_of_delays = 0.0;
     area_num_in_q = 0.0;
     area_server_status = 0.0;

     // initialize the queue
     client_queue = initialization();

    /* Initialize event list.  Since no customers are present, the departure
       (service completion) event is eliminated from consideration. */

    time_next_event[1] = sim_time + gen_next_interarrive(); // Planificacion del primer arribo
    time_next_event[2] = 1.0e+30;                           // infinito (servidor libre)

    next_event_type = 0; // por las dudas
}


void timing(void)  /* Timing function. */
{
    int   i;
    float min_time_next_event = 1.0e+29;

    next_event_type = 0; // Al final debe quedar en 1 en caso de que el proximo evento sea un arribo, 2: si es la salida de un servicio

    /* Determine the event type of the next event to occur. */
    if (time_next_event[1] < time_next_event[2]) {
        min_time_next_event = time_next_event[1];
        next_event_type = 1;                        // arribo
    } else {
        min_time_next_event = time_next_event[2];
        next_event_type = 2;                        // depart - salida
    }

    /* advance the simulation clock. */
    sim_time = min_time_next_event;
}


void arrive(void)  /* Arrival event function. */
{
    float delay;

    /* Schedule next arrival. */

    time_next_event[1] = sim_time + gen_next_interarrive();

    /* Check to see whether server is busy. */

    if (server_status == BUSY) {

        /* Server is busy, so increment number of customers in queue. */
        if (server_status == BUSY) num_in_q++;

        update_time_avg_stats(); // como incremente la cola actualizo los estadisticos

        /* Check to see whether an overflow condition exists. */

        if (num_in_q > Q_LIMIT) exit(2);

        /* Guardar el tiempo de arribo de esta entidad para los calculos estadisticos */
        Cliente c;
        c.timeArrived = sim_time;
        push(c, &client_queue);
    }

    else {

        /* Server libre, tener en  cuenta la entidad que pasa directamente al server para los calculos estadisticos */
        num_custs_delayed++; // ???? osea no tardo nada pero cuenta

        /* Schedule a departure (service completion). */
        server_status = BUSY;
        time_next_event[2] = sim_time + gen_next_depart();
    }
}


void depart(void)  /* Departure event function. */
{
    int   i;
    float delay;

    /* Check to see whether the queue is empty. */

    if (num_in_q == 0) {
        /* The queue is empty so make the server idle and eliminate the
           departure (service completion) event from consideration. */
        server_status = IDLE;
        time_next_event[2] = 1.0e+30;
    }

    else {

        /* The queue is nonempty, so decrement the number of customers in
           queue. */
        num_in_q--;

        update_time_avg_stats(); // salio un cliente de la cola -> actualizo los estadisticos

        Cliente c = pop(&client_queue);

        /* Compute the delay of the customer who is beginning service and update
           the total delay accumulator. */
        delay = sim_time - c.timeArrived;
        total_of_delays += delay;

        /* Increment the number of customers delayed, and schedule departure. */
        num_custs_delayed++;

        time_next_event[2] = sim_time + gen_next_depart();

    }
}


void report(void)  /* Report generator function. */
{
    /* Compute and write estimates of desired measures of performance. */
    printf("\n\n^^^^^^^^^^^^^^^^^^REPORT^^^^^^^^^^^^^^^^^^\n");
    //Average delay in queue
    printf("Average delay in queue: %f\n", total_of_delays/num_custs_delayed);

    //Average number in queue
    printf("Average number in queue: %f\n", area_num_in_q/sim_time);

    //Server utilization
    printf("Server utilization: %f\n",area_server_status/sim_time);
}


void update_time_avg_stats(void)  /* Update area accumulators for time-average
                                     statistics. */
{
    float time_since_last_event;

    /* Compute time since last event, and update last-event-time marker. */

    time_since_last_event = sim_time - time_last_event;
    time_last_event       = sim_time;

    /* Update area under number-in-queue function. */
    area_num_in_q += time_since_last_event * (float)num_in_q;

    /* Update area under server-busy indicator function. */
    if (server_status == BUSY) {
        area_server_status += time_since_last_event * server_status;
    }
}


float gen_next_interarrive()
{
  float rand_number = lcgrand(4);

  if (0.0 <= rand_number && rand_number <= 0.05) return 5.0;
  if (0.05 < rand_number && rand_number <= 0.1)  return 10.0;
  if (0.1 < rand_number && rand_number <= 0.2)   return 15.0;
  if (0.2 < rand_number && rand_number <= 0.3)   return 20.0;
  if (0.3 < rand_number && rand_number <= 0.6)   return 25.0;
  if (0.6 < rand_number && rand_number <= 0.8)   return 30.0;
  if (0.8 < rand_number && rand_number <= 0.95)  return 35.0;
  if (0.95 < rand_number && rand_number <= 1.0)  return 40.0;

  // sino entra en estos casos es un error
  printf("!gen_next_interarrive() -> NO VALIDO rand_number: %f\n", rand_number);
  exit(1); // termino el programa
}

float  gen_next_depart()
{
  float rand_number = lcgrand(8);

  if (0.0 <= rand_number && rand_number <= 0.15) return 10.0;
  if (0.15 < rand_number && rand_number <= 0.4)  return 20.0;
  if (0.4 < rand_number && rand_number <= 0.8)   return 30.0;
  if (0.8 < rand_number && rand_number <= 1.0)   return 40.0;

  //sino entra en estos casos es un error
  printf("!gen_next_depart() -> NO VALIDO rand_number: %f\n", rand_number);
  exit(1); // termino el programa
}

// shows the states of all variables:
void debug() {
    printf("********************************\n");
    printf("sim_time           : %f\n", sim_time);
    printf("server_status      : %d\n", server_status);
    printf("num_in_q           : %d\n", num_in_q);
    printf("time_last_event    : %f\n", time_last_event);
    printf("time_next_event    : [%f , %f]\n", time_next_event[1], time_next_event[2]);
    printf("num_custs_delayed  : %d\n", num_custs_delayed);
    printf("total_of_delays    : %f\n", total_of_delays);
    printf("area_num_in_q      : %f\n", area_num_in_q);
    printf("area_server_status : %f\n", area_server_status);
    printf("next_event_type    : %d\n", next_event_type);
}

float gen_next_interarrive2() {
    float r = lcgrand(7); // con 7: 0.86 pero igual no me da siempre cerca de 0.75
    float lambda = 3.0;

    float rand_number = (-1.0/lambda) * log(1 - r); // a veces puede retornar >= 1

    if (0.0 <= rand_number && rand_number <= 0.05) return 5.0;
    if (0.05 < rand_number && rand_number <= 0.1)  return 10.0;
    if (0.1 < rand_number && rand_number <= 0.2)   return 15.0;
    if (0.2 < rand_number && rand_number <= 0.3)   return 20.0;
    if (0.3 < rand_number && rand_number <= 0.6)   return 25.0;
    if (0.6 < rand_number && rand_number <= 0.8)   return 30.0;
    if (0.8 < rand_number && rand_number <= 0.95)  return 35.0;
    if (0.95 < rand_number)  return 40.0; // pq a veces rand_number > 1 (para que no se rompa)

    // sino entra en estos casos es un error
    printf("!gen_next_interarrive2() -> NO VALIDO rand_number: %f\n", rand_number);
    exit(1); // termino el programa
}

float gen_next_depart2() {
    float r = lcgrand(8);
    float lambda = 4.0;

    float rand_number = (-1.0/lambda) * log(1 - r);

    if (0.0 <= rand_number && rand_number <= 0.15) return 10.0;
    if (0.15 < rand_number && rand_number <= 0.4)  return 20.0;
    if (0.4 < rand_number && rand_number <= 0.8)   return 30.0;
    if (0.8 < rand_number)   return 40.0; // pq a veces rand_number > 1 (para que no se rompa)

    //sino entra en estos casos es un error
    printf("!gen_next_depart2() -> NO VALIDO rand_number: %f\n", rand_number);
    exit(1); // termino el programa
}


void arrive2() {
    float delay;

    // **** don't generate more arrivals ****

    /* Check to see whether server is busy. */

    if (server_status == BUSY) {

        /* Server is busy, so increment number of customers in queue. */
        if (server_status == BUSY) num_in_q++;

        update_time_avg_stats(); // como incremente la cola actualizo los estadisticos

        /* Check to see whether an overflow condition exists. */

        if (num_in_q > Q_LIMIT) exit(2);

        /* Guardar el tiempo de arribo de esta entidad para los calculos estadisticos */
        Cliente c;
        c.timeArrived = sim_time;
        push(c, &client_queue);

        time_next_event[1] = 1.0e+30; // no hay mas arribos
    }

    else {

        /* Server libre, tener en  cuenta la entidad que pasa directamente al server para los calculos estadisticos */


        /* Schedule a departure (service completion). */
        server_status = BUSY;
        time_next_event[2] = sim_time + gen_next_depart();
    }
}

// end the simulation if still there's people in queue
void end_sim() {
    // mientras haya clientes en cola o haya un arribo sin ejecutar o quede un cliente en el server seguir
    while ((num_in_q > 0) || (time_next_event[1] <= 1.0e+30) || (time_next_event[2] <= 1.0e+30)) {
        printf("DEBUG BEGINNING OF CYCLE");
        debug();

        /* Determine the next event. */

        timing();

        /* Update time-average statistical accumulators. */

        update_time_avg_stats();

        /* Invoke the appropriate event function. */

        switch (next_event_type) {
            case 1:
                arrive2(); // no genera mas nuevos arribos, solo ejecuta el existente
                break;
            case 2:
                depart();
                break;
        }

        printf("DEBUG END OF CYCLE******");
        debug();
    }
}