enum StackType;

struct Stack{                                             void* sptr;                                       void* bptr;
	void* srcptr;
        size_t size;                                      size_t allocated;                                 int16_t type;                             };

void stack_lifo_new(struct Stack* stack, size_t initial_size);
void stack_fifo_new(struct Stack* stack, size_t initial_size);
int stack_push(struct Stack* stack, void* element, size_t elementsize);
int stack_pop(struct Stack* stack, void* element, size_t elementsize);
