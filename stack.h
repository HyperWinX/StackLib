enum StackType;

struct Stack{                                             void* sptr;                                       void* bptr;
	void* srcptr;
        size_t size;                                      size_t allocated;                                 int16_t type;                             };

int stack_lifo_new(struct Stack* stack, size_t initial_size);
int stack_fifo_new(struct Stack* stack, size_t initial_size);
int stack_push(struct Stack* stack, void* element, size_t elementsize);
int stack_pop(struct Stack* stack, void* element, size_t elementsize);
int stack_peek(struct Stack* stack, void* element, size_t elementsize);
int is_empty(struct Stack* stack);
int is_full(struct Stack* stack);
void stack_destroy(struct Stack* stack);
