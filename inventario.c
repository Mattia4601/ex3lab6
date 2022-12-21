#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"

//funzione che alloca la tabella inventario e il vettore di oggetti al suo interno
tabInv_t* creaTabInv(int maxInv){
    tabInv_t *pTabInv;

    pTabInv = malloc(sizeof(tabInv_t));
    if (pTabInv==NULL){
        printf("Errore allocazione tabInv\n");
        exit(-1);
    }
    pTabInv->nInv = 0;
    pTabInv->maxInv = maxInv;
    pTabInv->vettInv = (inv_t*) malloc(maxInv*sizeof(inv_t));
    if (pTabInv->vettInv == NULL){
        printf("Errore allocazione vettInv\n");
        exit(-1);
    }
    return pTabInv;
}
//dealloca lo spazio usato per la tabella inventario
void cancellaTabInv(tabInv_t *pTabInv){
    free(pTabInv->vettInv);
    free((pTabInv));
}
//stampa i dettagli di un oggetto
void stampaOggetto(inv_t oggetto){

    printf("Nome oggetto: %s     Tipo: %s\n",oggetto.nome,oggetto.tipo);
    printf("Statistiche oggetto:\n");
    printf("hp: %d   mp: %d   atk: %d   def: %d   mag: %d   spr: %d\n",
           oggetto.stat.hp,oggetto.stat.mp,oggetto.stat.atk,oggetto.stat.def,oggetto.stat.mag,oggetto.stat.spr);
}
//funzione che legge da file i vari oggetti e li salva nella tabella inventario
void leggiOggetti(char *filename,tabInv_t *p_tabInv){
    FILE *fp;
    int i=0;
    fp = fopen(filename,"r");
    if (fp == NULL){
        printf("Errore apertura file\n");
        exit(-1);
    }
    fscanf(fp,"%d",&(p_tabInv)->nInv);

    while ( fscanf(fp,"%s%s%d%d%d%d%d%d",p_tabInv->vettInv[i].nome,p_tabInv->vettInv[i].tipo,
                  &(p_tabInv)->vettInv[i].stat.hp,&(p_tabInv)->vettInv[i].stat.mp,&(p_tabInv)->vettInv[i].stat.atk,
            &(p_tabInv)->vettInv[i].stat.def,&(p_tabInv)->vettInv[i].stat.mag,&(p_tabInv)->vettInv[i].stat.spr) != 8){
        i++;
    }
    fclose(fp);
}

//funzione che ricerca un oggetto per nome
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int SearchObjByName(tabInv_t *ptabInv, char *name){
    int i=0;
    //semplice ricerca lineare
    for (i=0; i<ptabInv->nInv; i++){
        if(strcmp(name,ptabInv->vettInv[i].nome)==0){
            return i;
        }
    }
    //se non viene trovato
    return -1;
}

/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *getByIndex(tabInv_t *ptabInv, int index){
    return &(ptabInv->vettInv[index]);
}

void stampaTabInv(tabInv_t *pTabInv){
    int i;
    if (pTabInv->nInv == 0 || pTabInv->vettInv == NULL){
        printf("tabella inventario vuota\n");
        return;
    }
    for (i=0;i<pTabInv->nInv;i++){
        //per tutti gli oggetti dell'inventario
        stampaOggetto(pTabInv->vettInv[i]);
    }
}