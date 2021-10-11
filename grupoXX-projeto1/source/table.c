#include "../include/data.h"
#include "../include/entry.h"
#include "../include/table.h"
#include "../include/table-private.h"
#include "../include/list.h"
#include "../include/list-private.h"
#include <stdlib.h>
#include <string.h>

struct table_t; /* A definir pelo grupo em table-private.h */

int f_hash(char *key, int size){
    
    int soma = 0;
    
    int tam = strlen(key);

    for(int i = 0; i < tam; i++)
        soma = soma + key[i];

    return soma % size;

}

/* Função para criar/inicializar uma nova tabela hash, com n
 * linhas (n = módulo da função hash)
 * Em caso de erro retorna NULL.
 */
struct table_t *table_create(int n){

    if(n < 1)  //Insuficent size
        return NULL;

    struct table_t *table =malloc(sizeof(struct table_t));

    
    
    if(table->list == NULL){
        free(table);
        return NULL;
    }

    table->size = 0;

    for (int i = 0; i < n; i++)
        table->list[i] = list_create();        
        
    table->size=n;    
    return table;
}

/* Função para libertar toda a memória ocupada por uma tabela.
 */
void table_destroy(struct table_t *table){
    for(int i=0;i<table->size;i++){
    list_destroy(table->list[i]);
}

    free(table);
    
}

/* Função para adicionar um par chave-valor à tabela.
 * Os dados de entrada desta função deverão ser copiados, ou seja, a
 * função vai *COPIAR* a key (string) e os dados para um novo espaço de
 * memória que tem de ser reservado. Se a key já existir na tabela,
 * a função tem de substituir a entrada existente pela nova, fazendo
 * a necessária gestão da memória para armazenar os novos dados.
 * Retorna 0 (ok) ou -1 em caso de erro.
 */
int table_put(struct table_t *table, char *key, struct data_t *value){

    /*int l = list_add(table->list, entry_create(key, value));

    table->size++;

    return l;*/

    int hash =f_hash(key,table->size);  //Nos dice la direccion donde se va a almacenar el par chave-valor
    
    struct list_t *ultimo_list = (table->list[hash]);

    if(ultimo_list->head->entry->value == NULL){         //Si la posicion donde quiero insertar datos esta vacía
        table->list[hash]->head->entry->key = strdup(key);
        table->list[hash]->head->entry->value = data_dup(value);
        table->size++;
        return 0;
    }

    else{               //Si la posicion donde quiero insertar datos NO esta vacía

        while(ultimo_list->head->next != NULL)
            ultimo_list = ultimo_list->head->next;
        
        for(int i = table->size-1; i >= 0; i--){
            if(table->list[i]->head->entry->key == NULL){
                table->list[i]->head->entry->key = strdup(key);
                table->list[i]->head->entry->value = data_dup(value);
                ultimo_list->head->next = (table->list[i]);
                return 0;
            }
        }

    }
    
    return -1; //En caso de que no pueda introducir los datos, se produce un error
}

/* Função para obter da tabela o valor associado à chave key.
 * A função deve devolver uma cópia dos dados que terão de ser
 * libertados no contexto da função que chamou table_get, ou seja, a
 * função aloca memória para armazenar uma *CÓPIA* dos dados da tabela,
 * retorna o endereço desta memória com a cópia dos dados, assumindo-se
 * que esta memória será depois libertada pelo programa que chamou
 * a função.
 * Devolve NULL em caso de erro.
 */
struct data_t *table_get(struct table_t *table, char *key){

    int h_k = f_hash(key, table->size);

    struct list_t *l = (table->list[h_k]);

    struct entry_t *e = list_get(l,key);
        
    return e->value;
}

/* Função para remover um elemento da tabela, indicado pela chave key, 
 * libertando toda a memória alocada na respetiva operação table_put.
 * Retorna 0 (ok) ou -1 (key not found).
 */
int table_del(struct table_t *table, char *key){
    
    int h_k = f_hash(key, table->size);

    struct list_t *l = (table->list[h_k]);

    if(l->head->entry->value != NULL){         //Si la posicion donde quiero eliminar datos no esta vacía
        list_remove(l,key);
        return 0;
    }

    else
        return -1;
    
}

/* Função que devolve o número de elementos contidos na tabela.
 */
int table_size(struct table_t *table){
    int size=0;   
    for(int i=0;i<table->size;i++){
        size=size+list_size(table->list[i]);
    }
     return size;         
}

/* Função que devolve um array de char* com a cópia de todas as keys da
 * tabela, colocando o último elemento do array com o valor NULL e
 * reservando toda a memória necessária.
 */
char **table_get_keys(struct table_t *table){
    
    char **l_keys =malloc(sizeof(char *) * (table->size + 1));

    int j = 0;

    for(int i = 0; i < table->size; i++){
       
        if (table->list[i]->head->entry->key != NULL){
            l_keys[j] = strdup(table->list[i]->head->entry->key);
            j++;
        }
    
    }

    return l_keys;
}


/* Função que liberta toda a memória alocada por table_get_keys().
 */
void table_free_keys(char **keys){

    int i = 0;

    while(keys[i] == NULL){
        free(keys[i]);
        i++;
    }

    free(keys);
}

/* Função que imprime o conteúdo da tabela.
 */
void table_print(struct table_t *table){

    for(int i= 0; i < table->size; i++)
       list_print(table->list[i]);

}
