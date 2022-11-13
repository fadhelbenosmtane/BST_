#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ModeleArbre.h"
#include "BST.h"

int main (int argc, char* argv[])
{
    PtrNoeud R = NULL, P, Q;
    char choix[20];
    char choix2[20];
    char nomf[50];      // Utilisée pour contenir le nom du fichier
    char cmd[100];      // Utilisée pour exécuter la commande système qui permet de dessiner l'arbre
    bool stop = false, stop2;
    int n;
    int sortie = 1;     // Utilisée pour les noms des fichiers du dessin de l'arbre
    int nbNil = 0;          // Utilisée dans (dessinerArbre) pour le dessin de l'arbre
    TVal val;

    FILE *f;	        // Fichier (.dot) utilisé pour le dessin de l'arbre avec (Graphviz)

    srand(time(NULL));

    do
    {
        ClrScr();
        Menu ();
        scanf ("%s", choix);
        switch (choix[0])
        {
             case '1':
                    do
                    {
                        ClrScr();
                        Entete();
                        printf ("1. Construction de l'arbre \n");
                        printf ("   ----------------------- \n\n");

                        stop2 = false;
                        printf ("1. Construction al%catoire \n\n", 130);
                        printf ("2. Construction manuelle \n\n");
                        printf ("> Votre choix : ");

                        scanf ("%s", choix2);
                        switch (choix2[0])
                        {
                            case '1':ClrScr();
                                    Entete();
                                    printf ("1. Construction de l'arbre \n");
                                    printf ("   ----------------------- \n\n");
                                    printf ("> Construction al%catoire de l'arbre\n\n", 130);
                                    printf (">> Veuillez introduire le nombre de noeuds : ");
                                    scanf ("%d", &n);
                                    R = ConstrAlea (n);
                                    stop2 = true;
                                    break;

                            case '2': ClrScr();
                                    Entete();
                                    printf ("1. Construction de l'arbre \n");
                                    printf ("   ----------------------- \n\n");
                                    printf ("> Construction manuelle de l'arbre\n\n");
                                    printf (">> Veuillez introduire le nombre de noeuds : ");
                                    scanf ("%d", &n);
                                    printf ("\n");
                                    R = ConstrMan (n);
                                    stop2 = true;
                                    break;
                        }
                    } while (!stop2);

                    printf ("\n\n> Appuyer sur ENTREE pour continuer ... ");
                    fflush(stdin);  // Vider le buffer (fonction non standard: à utiliser sous Windows seulement)
                    getchar();
                    break;

            case '2': ClrScr();
                    Entete();
                    printf ("2. Informations sur l'arbre \n");
                    printf ("   ------------------------ \n\n");
                    if (R == NULL)
                    {
                        printf ("> ERREUR : Arbre vide ! \n");
                    }
                    else
                    {
                        printf (">> Nombre de noeuds : %d \n\n", NbNoeuds(R));
                        printf (">> Nombre de feuilles : %d \n\n", NbFeuilles(R));
                        printf (">> Profondeur : %d \n\n", Profondeur(R));
                        printf (">> Arbre strictrement binaire : ");
                        if (StrictBinaire(R))
                            printf ("Oui \n\n");
                        else
                            printf ("Non \n\n");

                        printf (">> Arbre complet : ");
                        if (Complet(R))
                            printf ("Oui \n");
                        else
                            printf ("Non \n");
                    }

                    printf ("\n> Appuyer sur ENTREE pour continuer ... ");
                    fflush(stdin);
                    getchar();
                    break;

            case '3': ClrScr();
                    Entete();
                    printf ("3. Affichage en pr%cordre \n", 130);
                    printf ("   --------------------- \n\n");
                    if (R == NULL)
                        printf ("> ERREUR : Arbre vide !");
                    else
                    {
                        printf (">> Valeurs : ");
                        Preordre(R);
                    }

                    printf ("\n\n> Appuyer sur ENTREE pour continuer ... ");
                    fflush(stdin);
                    getchar();
                    break;

            case '4': ClrScr();
                    Entete();
                    printf ("4. Affichage en inordre \n");
                    printf ("   -------------------- \n\n");
                    if (R == NULL)
                        printf ("> ERREUR : Arbre vide !");
                    else
                    {
                        printf (">> Valeurs : ");
                        Inordre(R);
                    }

                    printf ("\n\n> Appuyer sur ENTREE pour continuer ... ");
                    fflush(stdin);
                    getchar();
                    break;

             case '5': ClrScr();
                    Entete();
                    printf ("5. Affichage en postordre \n");
                    printf ("   ---------------------- \n\n");
                    if (R == NULL)
                        printf ("> ERREUR : Arbre vide !");
                    else
                    {
                        printf (">> Valeurs : ");
                        Postordre(R);
                    }

                    printf ("\n\n> Appuyer sur ENTREE pour continuer ... ");
                    fflush(stdin);
                    getchar();
                    break;

            case '6': ClrScr();
                    Entete();
                    printf ("6. Recherche d'une valeur \n");
                    printf ("   ---------------------- \n\n");
                    if (R == NULL)
                        printf ("> ERREUR : Arbre vide !");
                    else
                    {
                        printf (">> Veuillez introduire la valeur %c chercher : ", 133);
                        scanf ("%d", &val);
                        Rech (R, val, &P, &Q);
                        if (P == NULL)
                            printf ("\n>> La valeur %d n'existe pas !", val);
                        else
                            printf ("\n>> La valeur %d se trouve dans le noeud d'adresse %p", val, P);
                    }

                    printf ("\n\n> Appuyer sur ENTREE pour continuer ... ");
                    fflush(stdin);
                    getchar();
                    break;

            case '7': ClrScr();
                    Entete();
                    printf ("7. Insertion d'une nouvelle valeur \n");
                    printf ("   ------------------------------- \n\n");

                    printf (">> Veuillez introduire la valeur %c inserer : ", 133);
                    scanf ("%d", &val);
                    Rech (R, val, &P, &Q);
                    if (P == NULL)
                    {
                        Insert (&R, val);
                        printf ("\n>> La valeur %d est ins%cr%ce correctement !", val, 130, 130);
                    }
                    else
                        printf("\n>> ERREUR: valeur (%d) existante !", val);

                    printf ("\n\n> Appuyer sur ENTREE pour continuer ... ");
                    fflush(stdin);
                    getchar();
                    break;

            case '8': ClrScr();
                    Entete();
                    printf ("8. Suppression d'une valeur \n");
                    printf ("   ------------------------ \n\n");
                    if (R == NULL)
                    {
                        printf ("> ERREUR : Arbre vide !");
                    }
                    else
                    {
                        printf (">> Veuillez introduire la valeur %c supprimer : ", 133);
                        scanf ("%d", &val);
                        n = NbNoeuds (R);
                        Supp (&R, val);
                        if (NbNoeuds(R) < n)
                            printf ("\n>> La valeur %d est supprim%ce correctement !", val, 130);
                    }

                    printf ("\n\n> Appuyer sur ENTREE pour continuer ... ");
                    fflush(stdin);
                    getchar();
                    break;

            case '9': ClrScr();
                    Entete();
                    printf ("9. Dessin de l'arbre \n");
                    printf ("   ----------------- \n\n");
                    if (R == NULL)
                    {
                        printf ("> ERREUR : Arbre vide !");
                    }
                    else
                    {
                        sprintf(nomf, "arbre%d.dot", sortie);
                        f = fopen(nomf,"w");        // Ouverture du fichier en écriture.
                        fprintf(f, "graph arbre {\n");
                        fprintf(f, "\tordering = out;\n");
                        fprintf(f, "\tsplines = false;\n");
                        nbNil = 0;
                        DessinArbre(R, f, &nbNil);
                        fprintf(f, "}\n");
                        fclose(f);
                        sprintf(cmd, "dot -Tpng arbre%d.dot -o arbre%d.png", sortie, sortie);
                        system(cmd);
                        sprintf(cmd, "arbre%d.png", sortie);
                        system(cmd);
                        sortie++;
                        printf (">> L'arbre est dessin%c correctement !", 130);
                    }

                    printf ("\n\n> Appuyer sur ENTREE pour continuer ... ");
                    fflush(stdin);
                    getchar();
                    break;

            case '0': stop = true;
                    break;
        }

    }while (!stop);

    return EXIT_SUCCESS;
}
