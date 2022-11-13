#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ModeleArbre.h"
#include "BST.h"

/************   Proc�dure clrscr  ****************/

void ClrScr()
{
    system("cls||clear");
}

/************   Proc�dure entete  ****************/

void Entete()
{
    printf("*******************************************\n");
    printf("*** ALSDD: Arbres binaires de recherche ***\n");
    printf("*******************************************\n\n");
}


/**************   Proc�dure menu  ****************/

void Menu()
{
    Entete();
    printf ("1. Construction d'un arbre binaire de recherche \n");
    printf ("2. Informations sur l'arbre \n");
    printf ("3. Affichage en pr%cordre \n", 130);
    printf ("4. Affichage en inordre \n");
    printf ("5. Affichage en postordre \n");
    printf ("6. Recherche d'une valeur \n");
    printf ("7. Insertion d'une nouvelle valeur \n");
    printf ("8. Suppression d'une valeur \n");
    printf ("9. Dessin de l'arbre (avec Graphviz) \n");
    printf ("0. Quitter \n\n");

    printf ("> Votre choix : ");
}

/**************   Fonction r�cursive NbNoeuds  ****************/

// Fonction qui d�termine le nombre de noeuds dans un arbre binaire
int NbNoeuds (PtrNoeud R)
{
    if (R == NULL)
        return 0;
    else
        return (1 + NbNoeuds(FG(R)) + NbNoeuds(FD(R)));
}

/**************   Fonction r�cursive NbFeuilles  ****************/

// Fonction qui d�termine le nombre de feuilles dans un arbre binaire
int NbFeuilles (PtrNoeud R)
{
    if (R == NULL)
        return 0;
    else
        if (FG(R)==NULL && FD(R)==NULL)
            return 1;
        else
            return (NbFeuilles(FG(R)) + NbFeuilles(FD(R)));
}

/**************   Fonction r�cursive Profondeur  ****************/

// Fonction qui d�termine la profondeur d'un arbre binaire
int Profondeur (PtrNoeud R)
{
    if (R == NULL)
        return -1;
    else
        return (1 + Max(Profondeur(FG(R)), Profondeur(FD(R))));
}

/**************   Fonction r�cursive StrictBinaire  ****************/

// Fonction qui d�termine si un arbre binaire est strictement binaire
bool StrictBinaire (PtrNoeud R)
{
    if (R == NULL)
        return true;
    else
        if ( (FG(R)==NULL && FD(R)!=NULL) || (FG(R)!=NULL && FD(R)==NULL) )
            return false;
        else
            return (StrictBinaire(FG(R)) && StrictBinaire (FD(R)));
}

/**************   Fonction r�cursive Complet  ****************/

// Proc�dure qui d�termine si un arbre binaire est complet
bool Complet (PtrNoeud R)
{
    int p1, p2;
    if (R == NULL)
        return true;
    else
    {
        p1 = Profondeur (FG(R));
        p2 = Profondeur (FD(R));
        return (Complet(FG(R)) && Complet (FD(R)) && (p1==p2));
    }
}

/**************   Proc�dure r�cursive Rech  ****************/

// Proc�dure qui recherche une valeur dans un arbre binaire de recherche
void Rech (PtrNoeud R, TVal val, PtrNoeud* P, PtrNoeud* Q)
{
    if (R == NULL)      // Dans ce cas val n�existe pas
    {
        *P = NULL;
        *Q = NULL;
    }
    else
    {
        if (val == Info(R))     // Dans ce cas val existe dans le noeud R
        {
            *P = R;
            *Q = NULL;
        }
        else    // Dans ce cas il faut continuer la recherche dans : FG (R) ou FD (R)
        {
            if (val < Info(R))
                Rech (FG(R), val, P, Q);
            else
                Rech (FD(R), val, P, Q);
            if (*Q == NULL)     // Mettre � jour Q apr�s les appels r�cursifs
                *Q = R;
        }
    }
}

/**************   Proc�dure insert  ****************/

// Proc�dure it�rative qui ins�re une nouvelle valeur dans un arbre binaire de recherche
void Insert (PtrNoeud* R, TVal val)
{
    PtrNoeud P, Q;
    if ((*R) == NULL)   // Si l�arbre est vide, l��l�ment ins�r� devient la racine de l�arbre
    {
        *R = CreerNoeud(val);
    }
    else
    {
        Rech(*R, val, &P, &Q);      // Chercher la valeur � ins�rer dans l�arbre
        if (P == NULL)              // Ins�rer la valeur si elle n�existe pas
        {
            P = CreerNoeud(val);    // Cr�er le nouveau noeud contenant val
            if (val < Info(Q))      // Connecter P avec Q (dernier noeud visit�)
                Aff_FG(Q, P);
            else
                Aff_FD(Q, P);
        }
        else
        {
            printf("\n>> ERREUR: valeur (%d) existante !", val);     // La valeur existe d�j�
        }
    }
}

/**************   Proc�dure supp  ****************/

// Proc�dure qui supprime une valeur d'un arbre binaire de recherche
void Supp (PtrNoeud* R, TVal val)
{
    PtrNoeud P, PereP, Q, PereQ;

    Rech(*R, val, &P, &PereP);
    if (P == NULL)
            printf("\n>> ERREUR: la valeur (%d) n'existe pas !", val);
    else
    {
        if (FG (P) == NULL )
        {
            if (FD (P) == NULL)     // Cas 1
            {
                if (PereP != NULL)
                {
                    if (P == FG (PereP))
                        Aff_FG(PereP, NULL);
                    else
                        Aff_FD(PereP, NULL);
                }
                else    // PereP = NIL
                {
                    *R = NULL;    // Suppression du dernier �l�ment de l�arbre
                }
            }
            else    // Cas 2
            {
                if (PereP != NULL)
                {
                    if (P == FG (PereP))
                        Aff_FG(PereP, FD(P));
                    else
                        Aff_FD(PereP, FD(P));
                }
                else
                {
                    *R = FD(P);     // Mise � jour de la racine
                }
            }
        }
        else
        {
            if (FD(P) == NULL)  // Cas 3
            {
                if (PereP != NULL)
                {
                    if (P == FG (PereP))
                        Aff_FG(PereP, FG(P));
                    else
                        Aff_FD(PereP, FG(P));
                }
                else
                {
                    *R = FG(P);    // Mise � jour de la racine
                }
            }
            else        // Cas 4
            {
                // 1. Rechercher le plus petit descendant du sous-arbre droit de (P)
                Q = FD(P);
                PereQ = P;
                while (FG (Q) != NULL)
                {
                    PereQ = Q;
                    Q = FG (Q);
                }
                // 2. Remplacer Info(P) par Info(Q)
                Aff_info(P, Info (Q));
                // 3. Remplacer Q par FD(Q)
                if (Q == FG(PereQ))
                    Aff_FG (PereQ, FD(Q));
                else
                    Aff_FD (PereQ, FD(Q));

		         P = Q;     // Car c'est Q qui va �tre r�ellement supprim�
            }
        }
        LibererNoeud(P);
    }
}

/**************   Fonction constrMan  ****************/

// Fonction qui permet de construire un arbre binaire de recherche avec n valeurs introduite manuellement
PtrNoeud ConstrMan (int n)
{
    PtrNoeud R = NULL, P, Q;
    TVal val;
    int i = 1;

    while(i<=n)
    {
        printf (">> Valeur (%d) = ", i);
        scanf ("%d", &val);
        Rech (R, val, &P, &Q);
        if (P != NULL)
            printf(">> ERREUR: la valeur (%d) existe d%cj%c !\n", val, 130, 133);
        else
        {
            Insert (&R, val);
            i++;
        }
    }
    printf("\n>> Arbre construit correctement !", val);
    return R;
}

/**************   Fonction constrAlea  ****************/

// Fonction qui permet de construire un arbre binaire de recherche avec n valeurs g�n�r�es al�atoirement
PtrNoeud ConstrAlea (int n)
{
    PtrNoeud R = NULL, P, Q;
    TVal val;
    int i = 1;

    printf ("\n>> Valeurs ins%cr%ces dans l'arbre : ", 130, 130);

    while(i<=n)
    {
        val = rand()%(NB_MAX-NB_MIN)+NB_MIN;
        Rech (R, val, &P, &Q);
        if (P == NULL)
        {
            Insert (&R, val);
            printf ("%d | ", val);
            i++;
        }
    }
    return R;
}

/**************   Proc�dure preordre  ****************/

// Proc�dure qui permet de visiter les noeuds de l'arbre en pr�ordre
void Preordre (PtrNoeud R)
{
    if (R != NULL)
    {
        printf ("%d | ", Info(R));
        Preordre (FG(R));
        Preordre (FD(R));
    }
}

/**************   Proc�dure inordre  ****************/

// Proc�dure qui permet de visiter les noeuds de l'arbre en inordre
void Inordre (PtrNoeud R)
{
    if (R != NULL)
    {
        Inordre (FG(R));
        printf ("%d | ", Info(R));
        Inordre (FD(R));
    }
}

/**************   Proc�dure postordre  ****************/

// Proc�dure qui permet de visiter les noeuds de l'arbre en postordre
void Postordre (PtrNoeud R)
{
    if (R != NULL)
    {
        Postordre (FG(R));
        Postordre (FD(R));
        printf ("%d | ", Info(R));
    }
}

/**************   Proc�dure dessinArbre  ****************/

//Proc�dure qui permet de g�n�rer le fichier (.dot) utilis� pour le dessin de l'arbre
void DessinArbre (PtrNoeud R, FILE* f, int* nbNil)
{
    if (R != NULL)
    {
        // Dessiner un arc vers le fils gauche
        if (FG(R) != NULL)
        {
            fprintf(f, "  \"%d\" -- \"%d\" \n", Info(R), Info(FG(R)));
        }
        else
        {
            fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
            fprintf(f, "  \"%d\" -- \"NIL%d\" ", Info(R), (*nbNil)++);
            fprintf(f, " [style=invis];\n");
        }

        // Dessiner un fils NIL virtuel et invisible au milieu (pour une meilleure s�paration des fils gauches et droits)
        fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
        fprintf(f, "  \"%d\" -- \"NIL%d\" ", Info(R), (*nbNil)++);
        fprintf(f, " [style=invis];\n");

        // Dessiner un arc vers le fils droit
        if (FD(R)!= NULL)
        {
            fprintf(f, "  \"%d\" -- \"%d\" \n", Info(R), Info(FD(R)));
        }
        else
        {
            fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
            fprintf(f, "  \"%d\" -- \"NIL%d\" ", Info(R), (*nbNil)++);
            fprintf(f, " [style=invis];\n");
        }

        // Dessiner les sous-arbres gauche et droit
        DessinArbre(FG(R), f, nbNil);
        DessinArbre(FD(R), f, nbNil);
   }
}
