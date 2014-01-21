/* Copyright (c) 2010-2013. MRSG Team. All rights reserved. */

/* This file is part of MRSG and MRA++.

MRSG and MRA++ are free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MRSG and MRA++ are distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MRSG and MRA++.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef MRSG_COMMON_H
#define MRSG_COMMON_H

#include <msg/msg.h>
#include <xbt/sysdep.h>
#include <xbt/log.h>
#include <xbt/asserts.h>

int*        dist_bruta;
double*     task_exec;
double*     avg_task_exec;

/* Short message names  */
#define SMS_START "SMS-S"
#define SMS_GET_CHUNK "SMS-GC"
#define SMS_GET_INTER_PAIRS "SMS-GIP"
#define SMS_HEARTBEAT "SMS-HB"
#define SMS_TASK "SMS-T"
#define SMS_TASK_DONE "SMS-TD"

#define NONE (-1)
#define MAX_SPECULATIVE_COPIES 3

/** @brief  Communication ports. */
enum port_e {
    PORT_MASTER,
    PORT_DATA_REQ,
    PORT_SLOTS_START
};

/** @brief  Possible execution phases. */
enum phase_e {
    MAP,
    REDUCE
};

/** @brief  Possible task states. */
enum task_state_e {
    /* The initial state must be the first enum. */
    T_STATE_PENDING,
    T_STATE_TIP,
    T_STATE_TIP_SLOW,
    T_STATE_DONE
};

struct job_s {
    int         finished;
    int         tasks_pending[2];
    int*        task_has_spec_copy[2];
    int*        task_state[2];
    m_task_t**  task_list[2];
} job;

/** @brief  Information sent as the task data. */
struct task_info_s {
    enum phase_e  phase;
    int           slot_port;
    int*          slots;
    size_t        id;
    size_t        src;
    size_t        wid;
    m_task_t      task;
};

typedef struct task_info_s* task_info_t;

/** @brief  Information sent by the workers with every heartbeat. */
struct heartbeat_s {
    int  slots_av[2];
};

typedef struct heartbeat_s* heartbeat_t;

struct config_s {
    double  chunk_size;
    double  cpu_required_map;
    double  cpu_required_reduce;
    double  grid_average_speed;
    double  grid_cpu_power;
    double  map_out_size;
    int     chunk_count;
    int     chunk_replicas;
    int     heartbeat_interval;
    int     map_slots;
    int     number_of_maps;
    int     number_of_reduces;
    int     number_of_workers;
    int     reduce_slots;
} config;

struct stats_s {
    int   map_local;
    int   map_remote;
    int   map_spec_l;
    int   map_spec_r;
    int   reduce_normal;
    int   reduce_spec;
    int*  maps_processed;
    int*  reduces_processed;
} stats;

m_host_t     master_host;
m_host_t*    worker_hosts;
heartbeat_t  w_heartbeat;

/**
 * @brief  Get the ID of a worker.
 * @param  worker  The worker node.
 * @return The worker's ID number.
 */
size_t get_worker_id (m_host_t worker);

/** 
 * @brief  Send a message/task.
 * @param  str   The message.
 * @param  cpu   The amount of cpu required by the task.
 * @param  net   The message size in bytes.
 * @param  data  Any data to attatch to the message.
 * @param  dest  The destination host.
 * @param  port  The destination port.
 */
void send (const char* str, double cpu, double net, void* data, m_host_t dest, int port);

/** 
 * @brief  Send a short message, of size zero.
 * @param  str   The message.
 * @param  dest  The destination host.
 * @param  port  The destination port.
 */
void send_sms (const char* str, m_host_t dest, int port);

/** 
 * @brief  Receive a message/task.
 * @param  port  The port to listen.
 * @return The received message/task.
 */
m_task_t receive (int port);

/** 
 * @brief  Compare the message from a task with a string.
 * @param  msg  The message/task.
 * @param  str  The string to compare with.
 * @return A positive value if matches, zero if doesn't.
 */
int message_is (m_task_t msg, const char* str);

/**
 * @brief  Return the maximum of two values.
 */
int maxval (int a, int b);

#endif /* !MRSG_COMMON_H */