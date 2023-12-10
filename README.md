# StackLib
Simple (and fast) FIFO and LIFO stack implementation coded in C.
## Usage
```c  
#include <stack.h>

int main(){  
// Create empty stack struct  
struct Stack stack;  
// Initialize struct, pass address of struct object and size of stack  
int retcode = stack_lifo_new(&stack, 1024);   
if (retcode != 0) return -1;
// This is example value  
int temp_value_to_push = 5;  
// Push value to stack, function accepts address of stack object, address of your object you want to push, and size of this object
retcode = stack_push(&stack, & temp_value_to_push, sizeof(int));  
if (retcode != 0) return -1;  
// Create object for popping value from stack
int popped_val;
// Pop value. Function accepts same arguments as stack_push(). 
retcode = stack_pop(&stack, &popped_val, sizeof(int));
if (retcode != 0) return -1;
int peeked_val
//Peek value. Same arguments.
retcode = stack_peek(&stack, &peeked_val, sizeof(int));
if (retcode != 0) return -1;
}  
```
For FIFO stack usage is just the same, but instead of stack_lifo_new() use stack_fifo_new().

_Every function returns error code, please use it!_

## Building

For building shared library use:
```sh
make shared
```

For running performance test, use:
```sh
make perftest
```
First test disables any optimization. Second test uses -O2 optimization.

## Benchmarks
Benchmark 1.  
CPU: Mediatek Helio P60  
Optimization: disabled  
```
LIFO stack init time:   0.000240s
Size of LIFO stack:     1024MB
Random number gen time: 12.059866s
Random numbers count:   268435456
LIFO stack push time:   7.275902s
Verification time:      7.022767s
FIFO stack init time:   0.233565s
Size of FIFO stack:     1024MB
FIFO stack push time:   6.912942s
Verification time:      7.018106s

Total time:             40.523388s
Clear working time:     28.463522s
```

Benchmark 2.  
CPU: Mediatek Helio P60.  
Optimization: O2.  
```
LIFO stack init time:   0.000380s
Size of LIFO stack:     1024MB
Random number gen time: 10.468492s
Random numbers count:   268435456
LIFO stack push time:   3.902848s
Verification time:      4.066953s
FIFO stack init time:   0.151579s
Size of FIFO stack:     1024MB
FIFO stack push time:   3.873532s
Verification time:      3.998540s

Total time:             26.462324s
Clear working time:     15.993832s
```

Benchmark 3.  
CPU: AMD FX-8350 3.7GHz  
RAM: 16GB DDR3 1600MHz  
Optimization: disabled.   
```
LIFO stack init time:   0.000072s
Size of LIFO stack:     1024MB
Random number gen time: 8.324505s
Random numbers count:   268435456
LIFO stack push time:   3.413590s
Verification time:      2.526034s
FIFO stack init time:   0.003983s
Size of FIFO stack:     1024MB
FIFO stack push time:   3.646913s
Verification time:      2.982696s

Total time:             20.897793s
Clear working time:     12.573288s
```
Benchmark 4.  
CPU: AMD FX-8350 3.7GHz  
RAM: 16GB DDR3 1600MHz  
Optimization: O2.  
```
LIFO stack init time:   0.000074s
Size of LIFO stack:     1024MB
Random number gen time: 8.813018s
Random numbers count:   268435456
LIFO stack push time:   1.561284s
Verification time:      1.525924s
FIFO stack init time:   0.004173s
Size of FIFO stack:     1024MB
FIFO stack push time:   1.637242s
Verification time:      1.524214s

Total time:             15.065929s
Clear working time:     6.252911s
```
