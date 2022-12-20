#ifndef ASDLAB6_PERSONAGGI_H
#define ASDLAB6_PERSONAGGI_H

#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"
#define M 50

typedef struct {
    char codice[M];
    char nome[M];
    char classe[M];
    tabEquip_t *equip;
    stat_t stat;
}pg_t;

typedef struct nodoPg_s nodoPg_t;
typedef struct nodoPg_s *link;
struct nodoPg_s{
    pg_t personaggio;
    link next;
};

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

inv_t** allocaVet_pEquip(int nMaxOggetti);
tabPg_t* allocaTabPg();
void freeVetEquip(inv_t **vEquip);
void freeTabPg(tabPg_t *p_tabPg);
void printPg(pg_t *p_pg);
link searchPgByCode(tabPg_t *pTabPg,char codice[M]);
void modificaEquip(pg_t *p_Pg,char nomeOgg[M],tabInv_t *pTabInv,int flag);
void modListaPg(tabPg_t *pTabPg,int flag);
tabPg_t* leggiFilePg(char *filename);
void stampaTabPg(tabPg_t *pTabPg);
#endif //ASDLAB6_PERSONAGGI_H
