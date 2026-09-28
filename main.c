#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Small wrapper around the state we need to store
typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

// Function to create/allocate new input buffer
InputBuffer* new_input_buffer() {
  InputBuffer *input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

// Function to print a prompt to the user
void print_promt() { printf("db > "); }

// Read a line of input, 'lineptr' point to the buffer containing the read line, 'size' use to save the size of allocated buffer
ssize_t getline(char **lineptr, size_t *size, FILE *stream);
void read_input(InputBuffer *input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1; // Get rid of '\0' char
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer *input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

int main(int argc, char *argv[]) {
  InputBuffer *input_buffer = new_input_buffer();

  // Infinite loop that prints the prompt
  while (true) {
    print_promt();
    read_input(input_buffer);

    // Process line of input
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'. \n", input_buffer->buffer);
    }
  }
}
