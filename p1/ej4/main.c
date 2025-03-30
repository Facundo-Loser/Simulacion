/* External definitions for single-server queueing system. */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "lcgrand.h"  /* Header file for random-number generator. */
#include "queue.h"    /* Para la cola de los clientes */

#define Q_LIMIT 100  /* Limit on queue length. */
#define BUSY      1  /* Mnemonics for server's being busy */
#define IDLE      0  /* and idle. */

void  initialize(void);
void  timing(void);
void  arrive(void);
void  depart(void);
void  report(void);
void  update_time_avg_stats(void);
float expon(float mean);
float gen_next_interarrive(void);
float gen_next_depart(void);
void debug();

float sim_time;           // reloj de la simulacion
int server_status;        // hay un servidor (1 ocupado / 0 desocupado)
int num_in_q;             // numero de personas en cola
float time_last_event;    // tiempo del ultimo evento
float time_next_event[3]; // array de los eventos futuros (hay 1 solo servidor) (pos[1]: arribo y demas pos son los servidores)

Queue cola_clientes;        // almacena la cola de clientes

int num_custs_delayed;      // para contar los clientes (SIN USAR!!!!!!!!!!!)
float total_of_delays;        // aca guardo el tiempo que que se retrsan en la cola (al final divido por n)
float area_num_in_q;        // area bajo la curva de q (longitud promedio de la cola)
float area_server_status;   // utilizacion del servidor

int next_event_type;        // tipo del prox. evento (1:arrive y 0:depart)

int final_condition;        // cond. de finalizacion del ciclo
float final_time = 300;

int num_entities; // contador de cant de clientes que pasan por el sist.

int main(void)  /* Main function. */
{

    /* Initialize the simulation. */

    initialize();

    /* Run the simulation while more delays are still needed. */

    while (sim_time <= final_time) {
        printf("*****PRINCIPIO CICLO*****");
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
        printf("*****FIN CICLO*****");
        debug();
    }

    /* Invoke the report generator and end the simulation. */

    report();

    return 0;
}

void initialize(void)  /* Initialization function. */
{
    // para que lcgrand() retorne siempre un num distinto:
    // Diferente semilla para cada stream
    lcgrandst(time(NULL), 4);     // para arribos
    lcgrandst(time(NULL) + 1, 8); // para servicio

    // Inicializo la cola:
    cola_clientes = initialization();

    sim_time = 0.0;

    /* Initialize the state variables. */

    server_status   = IDLE; // inactivo
    num_in_q        = 0;    // ?
    time_last_event = 0;    // ?

    // Initialize the statistical counters. num_custs_delayed, total_of_delays, area_num_in_q, area_server_status

     num_custs_delayed = 0;  // ?
     total_of_delays = 0;    // ?
     area_num_in_q = 0;      // ?
     area_server_status = 0; // ?

    /* Initialize event list.  Since no customers are present, the departure
       (service completion) event is eliminated from consideration. */

    time_next_event[1] = sim_time + gen_next_interarrive(); // planificacion del primer arribo
    time_next_event[2] = 1.0e+30;                           // infinito

    num_entities = 1;

    // en los servidores guardo cuanto tiempo tarda en salir
}

void timing(void)  /* Timing function. */
{
    int i;
    float min_time_next_event = 1.0e+29;

    next_event_type = 0; // Al final debe quedar en 1 en caso de que el proximo evento sea un arribo, 2: si es la salida de un servicio

    /* Determine the event type of the next event to occur. */

    if (time_next_event[1] < time_next_event[2]) {
        next_event_type = 1;
        min_time_next_event = time_next_event[1];
    } else {
        next_event_type = 2;
        min_time_next_event = time_next_event[2];
    }


    /* advance the simulation clock. */
    sim_time = min_time_next_event;
}


void arrive(void)  /* Arrival event function. */
{
    float delay;

    /* Schedule next arrival. */

    float next_interarrive = gen_next_interarrive();
    time_next_event[1] = sim_time + next_interarrive;
    num_entities++; // cuento otra entidad

    printf("\n\t#Next interarrive time: %f\n", next_interarrive);

    /* Check to see whether server is busy. */

    if (server_status == BUSY) {

        /* Server is busy, so increment number of customers in queue. */
        Cliente c;
        c.timeArrived = sim_time;

        push(c, &cola_clientes);
        num_in_q++;

        //delay = sim_time;
        //total_of_delays += delay;

        /* Check to see whether an overflow condition exists. */

        if (num_in_q > Q_LIMIT) {

            exit(2); // limite es 100
        }

        /* Guardar el tiempo de arribo de esta entidad para los calculos estadisticos */
        // se guarda en la cola

    }

    else {

        /* Server libre, tener en  cuenta la entidad que pasa directamente al server para los calculos estadisticos */
        server_status = BUSY;

        /* Schedule a departure (service completion). */
        float next_depart = gen_next_depart();
        time_next_event[2] = sim_time + next_depart;

        printf("\n\t#Depart time: %f\n", next_depart);
    }
}


void depart(void)  /* Departure event function. */
{
    int i;
    float delay;

    /* Check to see whether the queue is empty. */

    if (num_in_q == 0) {

        /* The queue is empty so make the server idle and eliminate the
           departure (service completion) event from consideration. */
        server_status = IDLE;
        time_next_event[2] = 1.0e+29;
        //num_custs_delayed++;
        //total_time_delayed queda igual
    }

    else {

        /* The queue is nonempty, so decrement the number of customers in
           queue. */

        Cliente c = pop(&cola_clientes);
        num_in_q--;

        /* Compute the delay of the customer who is beginning service and update
           the total delay accumulator. */
        total_of_delays += sim_time - c.timeArrived;

        /* Increment the number of customers delayed, and schedule departure. */
        num_custs_delayed++;

        float next_depart = gen_next_depart();
        time_next_event[2] = sim_time + next_depart;

        printf("\n\t #Depart time: %f\n", next_depart);
    }
}


void report(void)  /* Report generator function. */
{
    printf("\n^^^^^^^^^^^^^^^^REPORT^^^^^^^^^^^^^^^^\n");
    /* Compute and write estimates of desired measures of performance. */
    //printf("**********************DEBUG**********************\n");

    //Average delay in queue
    printf("Average delay in queue  : %f\n", total_of_delays/num_entities);

    //Average number in queue
    printf("Average number in queue : %f\n", area_num_in_q/final_time); // o / 100?

    //Server utilization
    printf("Server utilization      : %f\n", area_server_status/final_time);

}

void update_time_avg_stats(void)  /* Update area accumulators for time-average
                                     statistics. */
{
    float time_since_last_event;

    /* Compute time since last event, and update last-event-time marker. */

    time_since_last_event = sim_time - time_last_event;
    time_last_event       = sim_time;

    /* Update area under number-in-queue function. */
    area_num_in_q += time_since_last_event * (float)num_in_q; // long prom cola

    /* Update area under server-busy indicator function. */
    area_server_status += time_since_last_event * server_status; //?
}


float gen_next_interarrive()
{
    float rand_num = lcgrand(4);

    if (rand_num >= 0 && rand_num <= 0.05) {
        return 5;
    } else if (rand_num > 0.05 && rand_num <= 0.1) {
        return 10;
    } else if (rand_num > 0.1 && rand_num <= 0.2) {
        return 15;
    } else if (rand_num > 0.2 && rand_num <= 0.3) {
        return 20;
    } else if (rand_num > 0.3 && rand_num <= 0.6) {
        return 25;
    } else if (rand_num > 0.6 && rand_num <= 0.8) {
        return 30;
    } else if (rand_num > 0.8 && rand_num <= 0.95) {
        return 35;
    } else if (rand_num > 0.95 && rand_num <= 1) {
        return 40;
    }
}

float  gen_next_depart()
{
  float rand_num = lcgrand(8);

  if (rand_num >= 0 && rand_num <= 0.15) {
    return 10;
  } else if (rand_num > 0.15 && rand_num <= 0.4) {
    return 20;
  } else if (rand_num > 0.4 && rand_num <= 0.8) {
    return 30;
  } else if (rand_num > 0.8 && rand_num <= 1) {
    return 40;
  }
}

// shows the states of all variables:
void debug() {
    printf("*********************Debug*********************\n");
    printf("sim_time           : %f\n", sim_time);
    printf("server_status      : %d\n", server_status);
    printf("num_in_q           : %d\n", num_in_q);
    printf("time_last_event    : %f\n", time_last_event);
    printf("time_next_event    : [%f , %f]\n", time_next_event[1], time_next_event[2]);
    printf("num_custs_delayed  : %d\n", num_custs_delayed);
    printf("total_of_delays    : %d\n", total_of_delays);
    printf("area_num_in_q      : %f\n", area_num_in_q);
    printf("area_server_status : %f\n", area_server_status);
    printf("next_event_type    : %d\n", next_event_type);
    printf("num_entities       : %d\n", num_entities);
}
