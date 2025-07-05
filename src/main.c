#include <string.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  int constant;

  // // -((1.2 + 3.4) / 5.6)
  constant = addConstant(&chunk, 1.2);

  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  constant = addConstant(&chunk, 3.4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_ADD, 123);

  constant = addConstant(&chunk, 5.6);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_DIVIDE, 123);
  writeChunk(&chunk, OP_NEGATE, 123);

  writeChunk(&chunk, OP_RETURN, 123);

  disassembleChunk(&chunk, "-((1.2 + 3.4) / 5.6)");

  // 1 * 2 + 3
  // constant = addConstant(&chunk, 1.0);
  // writeChunk(&chunk, OP_CONSTANT, 123);
  // writeChunk(&chunk, constant, 123);

  // constant = addConstant(&chunk, 2.0);
  // writeChunk(&chunk, OP_CONSTANT, 123);
  // writeChunk(&chunk, constant, 123);

  // writeChunk(&chunk, OP_MULTIPLY, 123);

  // constant = addConstant(&chunk, 3.0);
  // writeChunk(&chunk, OP_CONSTANT, 123);
  // writeChunk(&chunk, constant, 123);

  // writeChunk(&chunk, OP_ADD, 123);
  // writeChunk(&chunk, OP_RETURN, 123);

  // disassembleChunk(&chunk, "1 * 2 + 3");

  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);

  return 0;
}
