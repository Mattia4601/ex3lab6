#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>



//alloca il vettore di equipaggiamento oggetti
inv_t** allocaVet_pEquip(int nMaxOggetti){
    inv_t **v_pEquip;

    v_pEquip = calloc(nMaxOggetti,sizeof(inv_t*));
    if (v_pEquip==NULL){
        printf("errore allocazione vettore equip\n");
    }
    return v_pEquip;
}
//alloca una tabella personaggi
tabPg_t* allocaTabPg(){
    tabPg_t *pTabPg;
    pTabPg = malloc(sizeof(tabPg_t));
    if (pTabPg==NULL){
        printf("Errore allocazione tabella personaggi\n");
    }
    pTabPg->headPg=NULL;
    pTabPg->tailPg=NULL;
    pTabPg->nPg=0;
    return pTabPg;
}
//dealloca vettore di equipaggiamento oggetti
void freeVetEquip(inv_t **vEquip){
    free(vEquip);
}
//dealloca tabella di personaggi
void freeTabPg(tabPg_t *p_tabPg){
    link p,x;
    for (p=p_tabPg->headPg; p!=NULL; p=x){
        x=p->next;
        freeVetEquip(p->personaggio.equip->vettEq);
        free(p->personaggio.equip);
        free(p);
    }
    free(p_tabPg);
}

//stampa dei dettagli di un personaggio e del relativo equipaggiamento se presente
void printPg(pg_t *p_pg){
    int i;
    printf("Codice: %s  Nome: %s  Classe: %s\n",p_pg->codice,p_pg->nome,p_pg->classe);
    if (p_pg->equip->inUso > 0){
        printf("%d oggetti presenti nel suo equipaggiamento: \n",p_pg->equip->inUso);
        for (i=0; i<p_pg->equip->inUso;i++){
            stampaOggetto(*p_pg->equip->vettEq[i]);
        }
    }
    else{
        printf("Nessun oggetto presente nel suo equipaggiamento\n");
    }
    /* se ci sono degli oggetti nell'equipaggiamento le statistiche del personaggio sono già state ricalcolate */
    printf("Statistiche del personaggio:\n");
    printf("hp: %d   mp: %d   atk: %d   def: %d   mag: %d   spr: %d\n",
           p_pg->stat.hp,p_pg->stat.mp,p_pg->stat.atk,p_pg->stat.def,p_pg->stat.mag,p_pg->stat.spr);
}
//ricerca per codice di un personaggio
link searchPgByCode(tabPg_t *pTabPg,char codice[M]){
    link x;

    if (pTabPg->headPg == NULL){
        printf("Lista personaggi vuota\n");
        exit(-1);
    }
    for (x=pTabPg->headPg;x!=NULL;x=x->next){
        if (strcmp(codice,x->personaggio.codice)==0){
            return x;
        }
    }
    return NULL;//codice non trovato
}

//modifica dell'equipaggiamento di un personaggio, aggiunta o rimozione di un oggetto, se flag 1 aggiungo se 0 rimuovo
void modificaEquip(pg_t *p_Pg,char nomeOgg[M],tabInv_t *pTabInv,int flag){
    int ok=0,j,i,k,oggIndex;
    i=p_Pg->equip->inUso;
    if (flag == 1){
        // aggiungo l'oggetto all'equipaggiamento del personaggio
        oggIndex=SearchObjByName(pTabInv,nomeOgg);
        if (oggIndex == -1){
            printf("Oggetto non trovato\n");
            return;
        }
        p_Pg->equip->vettEq[i] = &(pTabInv->vettInv[oggIndex]);
        p_Pg->equip->inUso ++;
        //aggiorno stat pg
        p_Pg->stat.hp += pTabInv->vettInv[oggIndex].stat.hp;
        p_Pg->stat.mp += pTabInv->vettInv[oggIndex].stat.mp;
        p_Pg->stat.atk += pTabInv->vettInv[oggIndex].stat.atk;
        p_Pg->stat.def += pTabInv->vettInv[oggIndex].stat.def;
        p_Pg->stat.mag += pTabInv->vettInv[oggIndex].stat.mag;
        p_Pg->stat.spr += pTabInv->vettInv[oggIndex].stat.spr;
    }
    else if(flag == 0){
        //rimuovo l'oggetto dall'equipaggiamento del personaggio
        for (j=0;j<i && ok==0;j++){//scandisco il vettore di equipaggiamento del personaggio
            if (strcmp(nomeOgg,p_Pg->equip->vettEq[j]->nome)==0){
                ok=1;//segno che ho trovato e tolto l'oggetto
                p_Pg->stat.hp -= p_Pg->equip->vettEq[j]->stat.hp;
                p_Pg->stat.mp -= p_Pg->equip->vettEq[j]->stat.mp;
                p_Pg->stat.atk -= p_Pg->equip->vettEq[j]->stat.atk;
                p_Pg->stat.def -= p_Pg->equip->vettEq[j]->stat.def;
                p_Pg->stat.mag -= p_Pg->equip->vettEq[j]->stat.mag;
                p_Pg->stat.spr -= p_Pg->equip->vettEq[j]->stat.spr;
                p_Pg->equip->vettEq[j] = NULL;//tolgo l'oggetto e aggiorno le statistiche
                //adesso devo scalare il vettore
                for (k=j+1;p_Pg->equip->vettEq[k]!=NULL;k++){
                    p_Pg->equip->vettEq[k-1] = p_Pg->equip->vettEq[k];
                }
                return;
            }
        }
    }
}

//inserimento o cancellazione di un personaggio
void modListaPg(tabPg_t *pTabPg,int flag){
    pg_t tmpPg;
    link p,x;
    int ok=0;
    char codice[M];
    if (flag == 1){//dobbiamo aggiungere un persinaggio alla lista
        printf("scrivere separati da uno spazio codice,nome,classe e statistiche del personaggio\n");
        fscanf(stdin,"%s,%s,%s",tmpPg.codice,tmpPg.nome,tmpPg.classe);
        fscanf(stdin,"%d%d%d%d%d%d",&tmpPg.stat.hp,&tmpPg.stat.mp,&tmpPg.stat.atk,&tmpPg.stat.def,&tmpPg.stat.mag,&tmpPg.stat.spr);

        //se la lista e' vuota inserisco in testa che corrisponde alla coda
        if(pTabPg->headPg == NULL && pTabPg->tailPg == NULL){
            (pTabPg->headPg->personaggio) = (pTabPg->tailPg->personaggio) = tmpPg;
            (pTabPg->headPg->next) = (pTabPg->tailPg->next) = NULL;
        }
        else{//se nella lista c'e' gia' qualche elemento
            (pTabPg->tailPg->next->personaggio) = tmpPg;
            (pTabPg->tailPg) = (pTabPg->tailPg->next);//aggiorno la coda della lista
        }
    }
    else if(flag==0){//dobbiamo rimuovere un personaggio
        //chiedo all'utente il codice del personaggio da eliminare
        printf("Scrivere codice del personaggio da eliminare:\n");
        fscanf(stdin,"%s",codice);
        for (p=NULL,x=pTabPg->headPg;ok==0 && x!=NULL;p=x, x=x->next){
            if (strcmp(x->personaggio.codice,codice)==0){
                ok=1;
                if(x==pTabPg->headPg && x==pTabPg->tailPg){
                    pTabPg->headPg=pTabPg->tailPg=NULL;
                }
                else if(x==pTabPg->headPg){
                    pTabPg->headPg = x->next;
                }
                else if(pTabPg->tailPg == x){
                    pTabPg->tailPg = p;
                    p->next = NULL;
                }
                else{
                    p->next = x->next;
                }
                if (x->personaggio.equip != NULL){
                    //se ha un equipaggiamento devo liberare la memoria ad esso allocata
                    free(x->personaggio.equip->vettEq);
                    free(x->personaggio.equip);
                }
                free(x);
            }
        }
    }
}

tabPg_t* leggiFilePg(char *filename){
    tabPg_t *pTabPg;
    FILE *fp;
    pg_t tmpPg;
    tmpPg.equip= NULL;
    pTabPg=allocaTabPg();
    fp = fopen(filename,"r");
    if (fp == NULL){
        printf("Errore apertura file pg\n");
        exit(-1);
    }
    while(fscanf(fp,"%s%s%s%d%d%d%d%d%d",tmpPg.codice,tmpPg.nome,tmpPg.classe,&tmpPg.stat.hp,&tmpPg.stat.mp,&tmpPg.stat.atk,
                 &tmpPg.stat.def,&tmpPg.stat.mag,&tmpPg.stat.spr)==9){
        if (pTabPg->headPg == NULL && pTabPg->tailPg == NULL){//inserimento in testa perché lista e' vuota
            pTabPg->headPg->personaggio.equip = malloc(sizeof(tabEquip_t));
            pTabPg->headPg->personaggio.equip->vettEq = allocaVet_pEquip(8);
            pTabPg->headPg->personaggio = pTabPg->tailPg->personaggio = tmpPg;
            pTabPg->nPg++;//aggiorno contatore dei personaggi in lista
        }
        else{//altrimenti inserisco in coda alla lista
            pTabPg->tailPg->next->personaggio.equip = calloc(1,sizeof(tabEquip_t));
            pTabPg->tailPg->next->personaggio.equip->vettEq = allocaVet_pEquip(8);
            pTabPg->tailPg->next->personaggio = tmpPg;
            pTabPg->tailPg = pTabPg->tailPg->next;//aggiorno la coda della lista
            pTabPg->nPg++;//aggiorno contatore dei personaggi in lista
        }
    }
    fclose(fp);
    return pTabPg;
}

void stampaTabPg(tabPg_t *pTabPg){
    link x;
    if(pTabPg->headPg == NULL){
        printf("Tabella personaggi vuota\n");
        return;
    }
    for (x=pTabPg->headPg;x!=NULL; x=x->next){
        printPg(&(x->personaggio));
    }
}