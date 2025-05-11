#ifndef UTILS_H
#define UTILS_H

#include "animal.h"

int trouver_id_libre(const Animal animaux[], int nb);
void tri_insertion(int* tableau, int taille);
void inventaire_age(const Animal animaux[], int nb);
void calcul_charges_nettoyage(const Animal animaux[], int nb);

#endif
