#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data.h"
#include "../include/entry.h"
#include "serialization.h"

/* Serializa uma estrutura data num buffer que será alocado
 * dentro da função. Além disso, retorna o tamanho do buffer
 * alocado ou -1 em caso de erro.
 */
int data_to_buffer(struct data_t *data, char **data_buf){

  fgets(*data_buf, 256, data);

  int data_buf_size;

  data_buf_size = sizeof(data_buf);

  if (data_buf == NULL)
    return -1;
  else
    return data_buf_size;

 }

/* De-serializa a mensagem contida em data_buf, com tamanhos
 * data_buf_size, colocando-a e retornando-a numa struct
 * data_t, cujo espaco em memoria deve ser reservado.
 * Devolve NULL em caso de erro.
 */
struct data_t *buffer_to_data(char *data_buf, int data_buf_size){

  int size;
  if (size <= 0){
    return NULL;
  }
  struct data_t *p;
  p = (struct data_t *) malloc (sizeof (struct data_t));

  if (p == NULL){
    return NULL;
  }

  p->datasize = size;
  p->data = malloc(size);

  if (p->data == NULL) {
    free(p);
    return NULL;
  }

	return memcpy(p, data_buf, data_buf_size);

}

/* Serializa uma estrutura entry num buffer que sera alocado
 * dentro da função. Além disso, retorna o tamanho deste
 * buffer alocado ou -1 em caso de erro.
 */
int entry_to_buffer(struct entry_t *data, char **entry_buf){

  fgets (*entry_buf, 256, data);

  int entry_buf_size;

  entry_buf_size = sizeof(entry_buf);

  if (entry_buf == NULL)
    return -1;
  else
    return entry_buf_size;

}

/* De-serializa a mensagem contida em entry_buf, com tamanho
 * entry_buf_size, colocando-a e retornando-a numa struct
 * entry_t, cujo espaco em memoria deve ser reservado.
 * Devolve NULL em caso de erro.
 */
struct entry_t *buffer_to_entry(char *entry_buf, int entry_buf_size){

  int size;
  if (size <= 0){
    return NULL;
  }
  struct data_t *p;
  p = (struct data_t *) malloc (sizeof (struct data_t));

  if (p == NULL){
    return NULL;
  }

  p->datasize = size;
  p->data = malloc(size);

  if (p->data == NULL) {
    free(p);
    return NULL;
  }

	return memcpy(p, entry_buf, entry_buf_size);

}