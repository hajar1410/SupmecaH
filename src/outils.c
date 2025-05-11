// outils.c - Fonctions utilitaires diverses
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outils.h"


// Trouve le plus petit ID libre non utilisé dans le tableau
int trouver_id_libre(const Animal animaux[], int nb) {
    int id = 1;
    int trouvé;

    while (1) {
        trouvé = 0;
        for (int i = 0; i < nb; i++) {
            if (animaux[i].id == id) {
                trouvé = 1;
                break;
            }
        }
        if (!trouvé) return id; // Retourne le premier ID libre trouvé
        id++;
    }
}

// Fonction de tri par insertion
void tri_insertion(int* tableau, int taille) {
    // Allouer une copie du tableau pour ne pas modifier l'original
    int* copie = malloc(taille * sizeof(int));

    // Copier les éléments dans le nouveau tableau
    for (int i = 0; i < taille; i++) {
        copie[i] = tableau[i];
    }

    // Algorithme de tri par insertion
    for (int i = 1; i < taille; i++) {
        int cle = tableau[i];
        int j = i - 1;

        // Déplacer les éléments plus grands que la clé
        while (j >= 0 && tableau[j] > cle) {
            tableau[j + 1] = tableau[j];
            j--;
        }
        tableau[j + 1] = cle;
    }
}

// Affiche l'inventaire des animaux par tranches d'âge (quartiles)
void inventaire_age(const Animal animaux[], int nb) {
    if (nb == 0) {
        printf("Aucun animal dans le chenil.\n");
        return;
    }

    int annee = 2025;
    int ages[MAX_ANIMAUX];

    // Calcul des âges
    for (int i = 0; i < nb; i++) {
        ages[i] = annee - animaux[i].annee_naissance;
        if (ages[i] < 0) ages[i] = 0;
    }

    // Tri des âges
    tri_insertion(ages, nb);

    int q1 = nb / 4;
    int q2 = nb / 2;
    int q3 = (3 * nb) / 4;

    int borne_q1 = ages[q1 - 1];
    int borne_q2 = ages[q2 - 1];
    int borne_q3 = ages[q3 - 1];
    int borne_q4 = ages[nb - 2];

    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    for (int i = 0; i < nb; i++) {
        if (ages[i] <= borne_q1) c1++;
        else if (ages[i] <= borne_q2) c2++;
        else if (ages[i] <= borne_q3) c3++;
        else c4++;
    }

    printf("\n--- INVENTAIRE PAR ÂGE (quartiles) ---\n");
    printf("Total : %d animaux\n", nb);
    printf("Quartile 1 : %d animaux (%d à %d ans)\n", c1, ages[0], borne_q1);
    printf("Quartile 2 : %d animaux (%d à %d ans)\n", c2, borne_q1 + 1, borne_q2);
    printf("Quartile 3 : %d animaux (%d à %d ans)\n", c3, borne_q2 + 1, borne_q3);
    printf("Quartile 4 : %d animaux (%d à %d ans)\n", c4, borne_q3 + 1, borne_q4);
}

// Calcule le temps de nettoyage quotidien et hebdomadaire
void calcul_charges_nettoyage(const Animal animaux[], int nb) {
    int total_jour = 0;
    int total_hebdo = 0;

    for (int i = 0; i < nb; i++) {
        const char *e = animaux[i].espece;

        if (strcmp(e, "Hamster") == 0 || strcmp(e, "Chat") == 0) {
            total_jour += 10;
            total_hebdo += 20;
        } else if (strcmp(e, "Autruche") == 0) {
            total_jour += 20;
            total_hebdo += 45;
        } else if (strcmp(e, "Chien") == 0) {
            total_jour += 5;
            total_hebdo += 20;
        } else {
            total_jour += 2; // Cas générique (cage vide ou espèce inconnue)
        }
    }

    printf("\n--- CHARGE DE NETTOYAGE (DAY_CLEAN) ---\n");
    printf("Temps par jour   : %d minutes (%.2f heures)\n", total_jour, total_jour / 60.0);
    printf("Supplément semaine : %d minutes (%.2f heures)\n", total_hebdo, total_hebdo / 60.0);
    printf("Total hebdomadaire : %d minutes (%.2f heures)\n",
           total_jour * 7 + total_hebdo, (total_jour * 7 + total_hebdo) / 60.0);
}