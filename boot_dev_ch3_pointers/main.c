#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

typedef struct {
  size_t length;
  char buffer[64];
} TextBuffer;

int smart_append(TextBuffer* dest, const char* src);

int main(void){
    TextBuffer textbuff = {
        .length = 0,
        .buffer = {0},
    };
    char text[] = "This is a long string that will fill the whole buffer and leave";

    smart_append(&textbuff, text);

    return 0;
}

int smart_append(TextBuffer* dest, const char* src) {
  if(!dest || !src){
    return 1;
  }

  const int max_buff = 64;
  int src_len = strlen(src);
  int remaining_space = max_buff - dest->length;

  if(remaining_space < src_len){
    strncpy(dest->buffer, src, (remaining_space-1));
    strcat(dest->buffer, "\0");
    return 1;
  }

  strcat(dest->buffer, src);
  strcat(dest->buffer, "\0");
  dest->length += (src_len + 1);
  printf("%ld", dest->length);
  printf("%s", dest->buffer);
  return 0;
}
