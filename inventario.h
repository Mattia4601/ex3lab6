#ifndef ASDLAB6_INVENTARIO_H
#define ASDLAB6_INVENTARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 50

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct {
    char nome[M];
    char tipo[M];
    stat_t stat;
}inv_t;

typedef struct {
    inv_t *vettInv;
    int nInv;
    int maxInv;
}tabInv_t;

typedef struct {
    int inUso;
    inv_t **vettEq;
}tabEquip_t;

typedef tabInv_t *tabInv; //tabInv è un tipo puntatore a tabella inventario tabInv_t *


//funzioni
tabInv_t* creaTabInv(int maxInv);
void cancellaTabInv(tabInv_t *pTabInv);
void stampaOggetto(inv_t oggetto);
void leggiOggetti(char *filename,tabInv_t *p_tabInv);
int SearchObjByName(tabInv_t *ptabInv, char *name);
inv_t *getByIndex(tabInv_t *ptabInv, int index);
void stampaTabInv(tabInv_t *pTabInv);
#endif //ASDLAB6_INVENTARIO_H
