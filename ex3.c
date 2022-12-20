#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inventario.h"
#include "personaggi.h"

#define N_SCELTE 7
#define DBG 0

enum { falso, vero };
typedef int bool;

void stampaMenu(char *scelte[], int *selezione){
    int i=0;
    printf("\nMENU'\n");
    for(i=0;i<N_SCELTE;i++)
        printf("%2d > %s\n",i,scelte[i]);
    scanf(" %d",selezione);
}

int main() {
    link x;
    char *scelte[] = {
            "Uscita",
            "Stampa personaggi",
            "Stampa inventario",
            "Cerca personaggio",
            "Aggiungi personaggio",
            "Elimina personaggio",
            "Modifica equip"
    };

    char codiceRicerca[M],nomeOgg[M];
    int selezione;
    bool fineProgramma;

    tabInv_t *tabInv;
    tabPg_t *tabPg;
    pg_t pg, *p_pg;

    tabInv = creaTabInv(50);//ipotizzo che ci siano massimo 50 oggetti nel file

#if DBG
    stampaTabInv(tabInv);
#endif /* DBG */

    tabPg = allocaTabPg();
    tabPg=leggiFilePg("pg.txt");

#if DBG
    stampaTabPg(tabPg);
#endif /* DBG */

    fineProgramma = falso;

    do {
        stampaMenu(scelte, &selezione);
        switch(selezione){

            case 0: {
                fineProgramma = vero;
            } break;

            case 1: {
                stampaTabPg(tabPg);
            } break;

            case 2: {
                stampaTabInv(tabInv);
            } break;

            case 3: {//ricerca personaggio per codice
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                x=searchPgByCode(tabPg,codiceRicerca);
                if(x==NULL){
                    printf("personaggio non trovato\n");
                    exit(-1);
                }
                printPg(&(x->personaggio));
            } break;

            case 4: {//aggiungi personaggio alla tabella di personaggi
                modListaPg(tabPg,1);
            } break;

            case 5: {//elimina personaggio da tabella di personaggi
                modListaPg(tabPg,0);
            } break;

            case 6: {//modifica equipaggiamento di un personaggio
                printf("Digitare codice del personaggio a cui modificare l'equipaggiamento\n");
                scanf("%s",codiceRicerca);
                x= searchPgByCode(tabPg,codiceRicerca);
                if(x==NULL){
                    printf("personaggio non trovato\n");
                    exit(-1);
                }
                printf("Digitare 1 se si vuole aggiungere un oggetto all'equipaggiamento\n");
                printf("Oppure 0 se si vuole rimuovere un oggetto dall'equipaggiamento\n");
                int flag;
                scanf("%d",&flag);
                printf("Scrivere nome oggetto\n");
                scanf("%s",nomeOgg);
                modificaEquip(&(x->personaggio),nomeOgg,tabInv,flag);
                if (DBG){
                    printPg(&(x->personaggio));
                }
            } break;

            default:{
                printf("Scelta non valida\n");
            } break;
        }
    } while(!fineProgramma);

    freeTabPg(tabPg);
    cancellaTabInv(tabInv);

    return 0;
}
