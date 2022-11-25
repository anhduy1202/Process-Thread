# Process-Thread
> Program to implement different pattern using process and thread

# Help menu
``` ./main -h ``` or ``` ./main --help ```

```
Help commands 
 
-h --help: print this help 
 
[NUMBER OF THINGS] [WORD] [PATTERN]: program input format 
 
[NUMBER OF THINGS]: number of threads / subprocesses to create, has to be from 1 to 256 
 
[WORD]: process or thread 
 
[PATTERN]: pick a pattern, between 1 to 3 
 
Example: 
 
12 thread 2: Create 12 threads with pattern 2 
 
30 process 1: Create 30 subprocesses with pattern 1 
```

# Pattern 1

![image](https://user-images.githubusercontent.com/58461444/203975141-b4246ad8-0ee6-486f-9241-39f95c6725b4.png)

## Process Output

```./main 10 process 1```

```
Process 1 beginning 
Process 4 beginning 
Process 2 beginning 
Process 3 beginning 
Process 5 beginning 
Process 7 beginning 
Process 8 beginning 
Process 9 beginning 
Process 10 beginning 
Process 6 beginning 
Process 1 exiting 
Process 2 exiting 
Process 3 exiting 
Process 4 exiting 
Process 5 exiting 
Process 6 exiting 
Process 7 exiting 
Process 8 exiting 
Process 9 exiting 
Process 10 exiting 
```

## Thread Pattern 1
```./main 10 thread 1```

```
Thread 1 beginning 
Thread 2 beginning 
Thread 3 beginning 
Thread 4 beginning 
Thread 5 beginning 
Thread 6 beginning 
Thread 7 beginning 
Thread 8 beginning 
Thread 9 beginning 
Thread 10 beginning 
Thread 1 exitting 
Thread 2 exitting 
Thread 3 exitting 
Thread 4 exitting 
Thread 5 exitting 
Thread 6 exitting 
Thread 7 exitting 
Thread 8 exitting 
Thread 9 exitting 
Thread 10 exitting 
```

# Pattern 2

![image](https://user-images.githubusercontent.com/58461444/203975518-63478391-ec4a-47c4-8056-d18752c7c350.png)

## Process output
```./main 5 process 2```

```
Hello. I'm child 0
Hello. I'm child 1
Hello. I'm child 2
Hello. I'm child 3
Hello. I'm child 4
Goodbye, I'm 4
Goodbye, I'm 3
Goodbye, I'm 2
Goodbye, I'm 1
Goodbye, I'm 0
Waitting for 413
```

## Thread output
``` ./main 5 thread 2```

```
Created main thread with tid: 139645303760448 
 
Thread 1 begins 
Thread 2 begins 
Thread 3 begins 
Thread 4 begins 
Thread 5 begins 
Thread 5 exitting 
Thread 4 exitting 
Thread 3 exitting 
Thread 2 exitting 
Thread 1 exitting 
Joined main thread with tid: 139645303760448 
```

