#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack() { vm.stackTop = vm.stack; }

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                                          \
  do {                                                                         \
    double b = pop();                                                          \
    double a = pop();                                                          \
    push(a op b);                                                              \
  } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("STACK   | ");
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");

    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(constant);
      printValue(constant);
      printf("\n");
      break;
    }
    case OP_ADD:
      BINARY_OP(+);
      break;
    case OP_SUBTRACT:
      BINARY_OP(-);
      break;
    case OP_MULTIPLY:
      BINARY_OP(*);
      break;
    case OP_DIVIDE:
      BINARY_OP(/);
      break;
    case OP_NEGATE: {
      // Negate the top value on the stack.
      // Do this in place to prevent from popping and re-pushing to the stack.
      // Also remember that the stack top is one past the last value.
      *(vm.stackTop - 1) *= -1;
      break;
    }
    case OP_RETURN:
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

void initVM() { resetStack(); }

void freeVM() {}

InterpretResult interpret(Chunk *chunk) {
  vm.chunk = chunk;
  vm.ip = chunk->code;
  return run();
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() { return *(--vm.stackTop); }