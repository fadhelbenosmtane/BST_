#ifndef     BST_H
#define     BST_H	1

/*
 *  Les fonctions/procédures implémentées dans ce programme
*/
#include <stdbool.h>

#define Max(a,b) ((a) > (b) ? (a) : (b))
#define Min(a,b) ((a) < (b) ? (a) : (b))

#define NB_MAX 100
#define NB_MIN 1

void ClrScr ();

void Entete ();

void Menu ();

int NbNoeuds (PtrNoeud R);

int NbFeuilles (PtrNoeud R);

int Profondeur (PtrNoeud R);

bool StrictBinaire (PtrNoeud R);

bool Somplet (PtrNoeud R);

void Rech (PtrNoeud R, TVal val, PtrNoeud* P, PtrNoeud* Q);

void Insert (PtrNoeud* R, TVal val);

void Supp (PtrNoeud* R, TVal val);

PtrNoeud ConstrMan (int n);

PtrNoeud ConstrAlea (int n);

void Preordre (PtrNoeud R);

void Inordre (PtrNoeud R);

void Postordre (PtrNoeud R);

void DessinArbre (PtrNoeud R, FILE* f, int* nbNil);


#endif /* BST.h  */
