#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
  int mythreadindex;
  int numberofchildren;
} ThreadParams;

int input_validation(int number, int mode, int pattern);
void thread_mode();
void process_mode();
void process_pattern_1_child(int id);
void process_pattern_2_child(int curr_id, int child_left);
void process_pattern_1();
void process_pattern_2();
void thread_pattern_1();
void thread_pattern_2();
void *thread_func(int tid);
void *thread_func2(ThreadParams *params);
// helper function
void print_menu();

int MODE = 0; // process : 1, thread: 2
int number_of_things = 0;
int pattern = 0;
int debug_on = 0; // 0: off, 1: on

int main(int argc, char *argv[]) {
  int next_idx = 1;
  int position = 1;
  // Process command line args
  while (next_idx < argc) {
    if (!strcmp(argv[next_idx], "-h") ||
               !strcmp(argv[next_idx], "--help")) {
      ++next_idx;
      print_menu();
      exit(1);
      }
    else if (argc < 4) {
      printf("ERROR: NOT ENOUGH ARGUMENTS \n \nexpect to have 4, but "
             "received %d \n \n",
             argc - 1);
      print_menu();
      exit(1);
    } else if (!strcmp(argv[next_idx], "-d")) {
      ++next_idx;
      debug_on = 1;
      position += 1;
    } else if (!strcmp(argv[next_idx], "process")) {
      ++next_idx;
      MODE = 1;
      ++next_idx;
    } else if (!strcmp(argv[next_idx], "thread")) {
      ++next_idx;
      MODE = 2;
      ++next_idx;
    } else {
      ++next_idx;
    }
  }
  number_of_things = atoi(argv[position]);
  pattern = atoi(argv[position + 2]);
  if (debug_on) {
    printf("number of things %d \n \n", number_of_things);
    printf("Pattern: %d \n \n", pattern);
    printf("Mode: %d \n \n", MODE);
}
  if (!input_validation(number_of_things, MODE, pattern)) {
    exit(1);
  }
  switch (MODE) {
  case 2: // thread
    thread_mode();
    break;
  default:
    process_mode();
  }
}

int input_validation(int number, int mode, int pattern) {

  if (number < 1 || number > 256) {
    printf("ERROR: INPUT VALIDATION \n");
    printf("Number of things has to be between 1 and 256");
    return 0;
  }
  if (mode == 0) {
    printf("ERROR: INPUT VALIDATION \n");
    printf("Invalid option! Either process or thread");
    return 0;
  }
  if (pattern < 1 || pattern > 2) {
    printf("ERROR: INPUT VALIDATION \n");
    printf("Invalid pattern! Has to be between 1 to 2");
    return 0;
  }
  return 1;
}

void process_mode() {
  switch (pattern) {
  case 1:
    process_pattern_1();
    break;
  case 2:
    process_pattern_2();
    break;
  default:
    printf("invalid");
  }
}

void thread_mode() {
  switch (pattern) {
  case 1:
    thread_pattern_1();
    break;
  case 2:
    thread_pattern_2();

  default:
    printf("invalid");
  }
}

void *thread_func(int tid) {
  printf("Thread %d beginning \n", tid + 1);
  sleep(rand() % 8 + 1);
}

void *thread_func2(ThreadParams *params) {
  printf("Thread %d begins \n", params->mythreadindex);
  sleep(rand() % 8 + 1);
  if (params->numberofchildren != 0) {
    ThreadParams *childparams = malloc(sizeof(ThreadParams));
    childparams->mythreadindex = params->mythreadindex + 1;
    childparams->numberofchildren = params->numberofchildren - 1;
    pthread_t tid;
    int create_status = pthread_create(&tid, NULL, thread_func2, childparams);
    if (create_status != 0) {
    printf("Error creating thread %d \n \n", childparams->mythreadindex);
  } 
  else {
    if(debug_on) {
      printf("Thread %d is created \n \n", childparams->mythreadindex);
    }
  }
    pthread_join(tid, NULL);
    free(childparams);
  }
  printf("Thread %d exitting \n", params->mythreadindex);
}

void thread_pattern_1() {
  pthread_t parent_tid;
  pthread_t *child_tid = malloc(sizeof(pthread_t) * number_of_things);
  int *thread_ids = malloc(sizeof(int) * number_of_things);
  for (int i = 0; i < number_of_things; i++) {
    thread_ids[i] = i;
    int create_status = pthread_create(&child_tid[i], NULL, thread_func, thread_ids[i]);
    if (create_status != 0) {
      printf("Error creating thread %d \n \n", i);
    } 
    else {
      if(debug_on) {
        printf("Thread %d is created \n \n", i);
      }
    }
  }

  for (int i = 0; i < number_of_things; i++) {
    int join_status = pthread_join(child_tid[i], NULL);
    if (join_status != 0) {
    printf("Error joining thread %d \n \n", i);
  } 
  else {
    if(debug_on) {
      printf("Thread %d is joined \n \n", i);
    }
  }
    printf("Thread %d exitting \n", i + 1);
  }
}

void thread_pattern_2() {
  ThreadParams *childparams = malloc(sizeof(ThreadParams));
  childparams->mythreadindex = 1;
  childparams->numberofchildren = number_of_things - 1;
  pthread_t tid;
  int main_thread = pthread_create(&tid, NULL, thread_func2, childparams);
  if (main_thread != 0) {
     printf("Error creating main thread\n \n");
  } else {
    printf("Created main thread with tid: %lu \n \n", tid);
  }
  pthread_join(tid, NULL);
  printf("Joined main thread with tid: %lu \n", tid);
}

void process_pattern_1_child(int id) {
  printf("Process %d beginning \n", id);
  sleep(rand() % 8 + 1);
  exit(0);
}

void process_pattern_2_child(int curr_id, int child_left) {
  printf("Hello. I'm child %d\n", curr_id);
  if (child_left > 0) {
    int pid = fork();
    if (pid == 0) {
      process_pattern_2_child(curr_id + 1, child_left - 1);
    }
    waitpid(pid, NULL, 0);
  }
  sleep(rand() % 8 + 1);
  printf("Goodbye, I'm %d\n", curr_id);
  exit(0);
}

void process_pattern_1() {
  for (int i = 0; i < number_of_things; i++) {
    pid_t child_pid;
    child_pid = fork();
    if (child_pid < 0) {
      if (debug_on) {
        printf("ERROR! UNABLE TO FORK  \n \n");
      }
      exit(1);
    }
    if (child_pid == 0) {
      if (debug_on) {
        printf("PROCESS CREATED  \n \n");
      }
      process_pattern_1_child(i + 1);
    }
  }
  for (int i = 0; i < number_of_things; i++) {
    wait(NULL);
    printf("Process %d exiting \n", i + 1);
  }
}

void process_pattern_2() {
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    process_pattern_2_child(0, number_of_things - 1);
  }
  if (pid < 0) {
    printf("ERROR! UNABLE TO FORK  \n \n");
    exit(1);
  }
  waitpid(pid, NULL, 0);
  printf("Waitting for %d\n", pid);
  exit(0);
}

// helper function
void print_menu() {
  printf("\nHelp commands \n \n"
         "-h --help: print this help \n \n"
         "[NUMBER OF THINGS] [WORD] [PATTERN]: program input format \n \n"
         "[NUMBER OF THINGS]: number of threads / subprocesses to create, has "
         "to be from 1 to 256 \n \n"
         "[WORD]: process or thread \n \n"
         "[PATTERN]: pick a pattern, between 1 to 3 \n \n"
         "Example: \n \n"
         "12 thread 2: Create 12 threads with pattern 2 \n \n"
         "30 process 1: Create 30 subprocesses with pattern 1 \n \n");
}