


#include "../include/data.h"
#include "../include/entry.h"
#include <stdlib.h>
#include <string.h>



/* Função que cria uma entry, reservando a memória necessária e
 * inicializando-a com a string e o bloco de dados passados.
 */
struct entry_t *entry_create(char *key, struct data_t *data){
    struct entry_t *entry;

    entry = malloc(sizeof(struct entry_t)); 
    entry->key=malloc(strlen(key)+1);
    entry->key=key;
    entry->value=data;

    return entry;
}

/* Função que inicializa os elementos de uma entrada na tabela com o
 * valor NULL.
 */
void entry_initialize(struct entry_t *entry){
    entry->key=NULL;
    entry->value=NULL;

}

/* Função que elimina uma entry, libertando a memória por ela ocupada
 */
void entry_destroy(struct entry_t *entry){
if(entry!=NULL){
    data_destroy(entry->value);
    free(entry->key);
    free(entry);
}
}

/* Função que duplica uma entry, reservando a memória necessária para a
 * nova estrutura.
 */
struct entry_t *entry_dup(struct entry_t *entry){

    struct entry_t *ptr;

    ptr=malloc(sizeof(struct entry_t));
    ptr->key=malloc(strlen(entry->key));
    ptr->key=strcpy(ptr->key,entry->key);
    ptr->value=data_dup(entry->value);
   


    return  ptr ;    
}

/* Função que substitui o conteúdo de uma entrada entry_t.
*  Deve assegurar que destroi o conteúdo antigo da mesma.
*/
void entry_replace(struct entry_t *entry, char *new_key, struct data_t *new_value){

    data_destroy(entry->value);
    free(entry->key);


    entry->value=new_value;
    entry->key=new_key;
}


/* Função que compara duas entradas e retorna a ordem das mesmas.
*  Ordem das entradas é definida pela ordem das suas chaves.
*  A função devolve 0 se forem iguais, -1 se entry1<entry2, e 1 caso contrário.
*/
int entry_compare(struct entry_t *entry1, struct entry_t *entry2){
int val;
if(entry1->key==entry2->key){
    val=0;

}else if(entry1->key<entry2->key){
    val=-1;
}else{
    val=1;
}


return val;
}



