
#include "../include/data.h"
#include "../include/entry.h"
#include "../include/list-private.h"
#include "../include/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* Função que cria uma nova lista (estrutura list_t a ser definida pelo
 * grupo no ficheiro list-private.h).
 * Em caso de erro, retorna NULL.
 */
struct list_t *list_create(){
    struct list_t *list;
    list=malloc(sizeof(struct list_t));
    list->head=malloc(sizeof(struct node_t));
    list->head=NULL;
   

}

/* Função que elimina uma lista, libertando *toda* a memoria utilizada
 * pela lista.
 */
void list_destroy(struct list_t *list){
    if(list->head!=NULL){

        list_destroy_aux(list->head);
    }
    
free(list);
}

void list_destroy_aux(struct node_t *head){


    if(head->next!=NULL){
        list_destroy_aux(head->next);

    }
entry_destroy(head->entry);
free(head);

}



/* Função que adiciona no final da lista (tail) a entry passada como
* argumento caso não exista na lista uma entry com key igual àquela
* que queremos inserir.
* Caso exista, os dados da entry (value) já existente na lista serão
* substituídos pelos os da nova entry.
* Retorna 0 (OK) ou -1 (erro).
*/

int list_add(struct list_t *list, struct entry_t *entry){
int value;

if(entry==NULL ||entry->key==NULL||entry->value==NULL||list==NULL){
    
    return -1;
    
}else{
    if(list->head==NULL){
        list->head=malloc(sizeof(struct node_t));
        list->head->entry=entry;
    }else {

    list_add_aux(list->head,entry);
    
    }
    return 0;
}

}

void list_add_aux(struct node_t *node,struct entry_t *entry){
    if(strcmp(node->entry->key,entry->key)==0){
        entry_destroy(node->entry);
        node->entry=entry;
        return;

    }else if(node->next!=NULL){
        list_add_aux(node->next,entry);   
    }else{
        node->next=malloc(sizeof(struct node_t));
        node->next->entry=entry;
        node->next->next=NULL;
        return;
    }
    

}

/* Função que elimina da lista a entry com a chave key.
 * Retorna 0 (OK) ou -1 (erro).
 */
int list_remove(struct list_t *list, char *key){
int value;
struct node_t *current =list->head;
struct node_t *previous=list->head;

if(list==NULL||list->head==NULL){
    value=-1;
}else{
    if(strcmp(current->entry->key,key)==0){
        entry_destroy(list->head->entry);
        list->head=current->next;
        return 0;
        }


    while(current!=NULL){
        if(strcmp(current->entry->key,key)==0){
            entry_destroy(current->entry);
            previous->next=current->next;
            return 0;
        }
        
    previous=current;
    current=current->next;
   
    
}
return 0;
}


}







/* Função que obtém da lista a entry com a chave key.
 * Retorna a referência da entry na lista ou NULL em caso de erro.
 * Obs: as funções list_remove e list_destroy vão libertar a memória
 * ocupada pela entry ou lista, significando que é retornado NULL
 * quando é pretendido o acesso a uma entry inexistente.
*/
struct entry_t *list_get(struct list_t *list, char *key){

    if(list==NULL||key==NULL||list->head==NULL){
        return NULL;
    }

return list_get_aux(list->head,key);
}


struct entry_t *list_get_aux(struct node_t *node, char *key)
{
    if(strcmp(node->entry->key,key)==0) {
        return node->entry;
    }else if(node->next!=NULL){
    list_get_aux(node->next,key);
    }else{
        return NULL;
    }


}


/* Função que retorna o tamanho (número de elementos (entries)) da lista,
 * ou -1 (erro).
 */
int list_size(struct list_t *list){
if(list->head==NULL||list->head->entry==NULL){
    return 0;
}

return list_size_aux(list->head);
}



int list_size_aux(struct node_t *node){
    if(node->next!=NULL){
        return 1+list_size_aux(node->next);
    }
    else{
        return 1;
    }

}

/* Função que devolve um array de char* com a cópia de todas as keys da 
 * tabela, colocando o último elemento do array com o valor NULL e
 * reservando toda a memória necessária.
 */
char **list_get_keys(struct list_t *list){
char **val;
val=malloc(sizeof(struct entry_t)*(list_size(list)+1));
struct node_t *current=list->head ;

if(list==NULL||list->head==NULL){
    free(val);
    return NULL;
}

for(int i=0;i<list_size(list);i++){
    val[i]=malloc(sizeof(current->entry->key));
    strcmp(val[i],current->entry->key);

}


return val;
}




/* Função que liberta a memória ocupada pelo array das keys da tabela,
 * obtido pela função list_get_keys.
 */
void list_free_keys(char **keys){

    for (int i = 0; i < (sizeof(keys)/sizeof(keys[0])); i++)
    {
        free(keys[i]);
    }
    


    free(keys);
}

/* Função que imprime o conteúdo da lista para o terminal.
 */
void list_print(struct list_t *list){
    char **keys=list_get_keys(list);
    int count=0;

    while(keys[count] ==NULL){
        printf("%s : ...",keys[count]);
        count++;
    }



}


