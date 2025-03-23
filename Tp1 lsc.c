#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;
} Noeud;

Noeud* creer(int valeur) {
    Noeud *nouveau = (Noeud*)malloc(sizeof(Noeud));
    if (nouveau == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }
    nouveau->valeur = valeur;
    nouveau->suivant = NULL;
    return nouveau;
}

void affiche(Noeud *debut) {
    Noeud *aide = debut;
    while (aide != NULL) {
        printf("%d -> ", aide->valeur);
        aide = aide->suivant;
    }
    printf("NULL\n");
}

Noeud* ajouterD(Noeud *debut, int valeur) {
    Noeud *nouveau = creer(valeur);
    nouveau->suivant = debut;
    return nouveau;
}

Noeud* ajouterF(Noeud *debut, int valeur) {
    Noeud *nouveau = creer(valeur);
    if (debut == NULL) {
        return nouveau;
    }
    Noeud *aide = debut;
    while (aide->suivant != NULL) {
        aide = aide->suivant;
    }
    aide->suivant = nouveau;
    return debut;
}

int taille(Noeud *debut) {
    int count = 0;
    Noeud *aide = debut;
    while (aide != NULL) {
        count++;
        aide = aide->suivant;
    }
    return count;
}

Noeud* insertionpos(Noeud *debut, int pos, int valeur) {
    if (pos < 1 || pos > taille(debut) + 1) {
        printf("Position invalide\n");
        return debut;
    }
    if (pos == 1) {
        return ajouterD(debut, valeur);
    }
    Noeud *nouveau = creer(valeur);
    Noeud *aide = debut;
    for (int i = 1; i < pos - 1; i++) {
        aide = aide->suivant;
    }
    nouveau->suivant = aide->suivant;
    aide->suivant = nouveau;
    return debut;
}

void rechercher(Noeud *debut, int valeur) {
    Noeud *aide = debut;
    int pos = 1;
    while (aide != NULL) {
        if (aide->valeur == valeur) {
            printf("Valeur %d trouvee a la position %d\n", valeur, pos);
            return;
        }
        aide = aide->suivant;
        pos++;
    }
    printf("Valeur %d non trouvee\n", valeur);
}

Noeud* suppressionD(Noeud *debut) {
    if (debut == NULL) {
        printf("Liste vide\n");
        return NULL;
    }
    Noeud *temp = debut;
    debut = debut->suivant;
    free(temp);
    return debut;
}

Noeud* suppressionF(Noeud *debut) {
    if (debut == NULL) {
        printf("Liste vide\n");
        return NULL;
    }
    if (debut->suivant == NULL) {
        free(debut);
        return NULL;
    }
    Noeud *aide = debut;
    while (aide->suivant->suivant != NULL) {
        aide = aide->suivant;
    }
    free(aide->suivant);
    aide->suivant = NULL;
    return debut;
}

Noeud* suppressionP(Noeud *debut, int pos) {
    if (pos < 1 || pos > taille(debut)) {
        printf("Position invalide\n");
        return debut;
    }
    if (pos == 1) {
        return suppressionD(debut);
    }
    Noeud *aide = debut;
    for (int i = 1; i < pos - 1; i++) {
        aide = aide->suivant;
    }
    Noeud *temp = aide->suivant;
    aide->suivant = aide->suivant->suivant;
    free(temp);
    return debut;
}

Noeud* modifierD(Noeud *debut, int valeur) {
    if (debut == NULL) {
        printf("Liste vide\n");
        return NULL;
    }
    debut->valeur = valeur;
    return debut;
}

Noeud* modifierF(Noeud *debut, int valeur) {
    if (debut == NULL) {
        printf("Liste vide\n");
        return NULL;
    }
    Noeud *aide = debut;
    while (aide->suivant != NULL) {
        aide = aide->suivant;
    }
    aide->valeur = valeur;
    return debut;
}

Noeud* modifierP(Noeud *debut, int pos, int valeur) {
    if (pos < 1 || pos > taille(debut)) {
        printf("Position invalide\n");
        return debut;
    }
    Noeud *aide = debut;
    for (int i = 1; i < pos; i++) {
        aide = aide->suivant;
    }
    aide->valeur = valeur;
    return debut;
}

int main() {
    Noeud *liste = NULL;

    liste = ajouterF(liste, 10);
    liste = ajouterF(liste, 20);
    liste = ajouterF(liste, 30);

    printf("Liste initiale : ");
    affiche(liste);

    liste = ajouterD(liste, 5);
    printf("Apres ajout au debut : ");
    affiche(liste);

    liste = ajouterF(liste, 40);
    printf("Apres ajout a la fin : ");
    affiche(liste);

    printf("Taille de la liste : %d\n", taille(liste));

    liste = insertionpos(liste, 3, 15); // Correction ici
    printf("Apres insertion a la position 3 : ");
    affiche(liste);

    rechercher(liste, 20);

    liste = suppressionD(liste);
    printf("Apres suppression du premier element : ");
    affiche(liste);

    liste = suppressionF(liste);
    printf("Après suppression du dernier element : ");
    affiche(liste);

    liste = suppressionP(liste, 2);
    printf("Apres suppression a la position 2 : ");
    affiche(liste);

    liste = modifierD(liste, 100);
    printf("Apres modification du premier element : ");
    affiche(liste);

    liste = modifierF(liste, 200);
    printf("Apres modification du dernier element : ");
    affiche(liste);

    liste = modifierP(liste, 2, 150);
    printf("Apres modification a la position 2 : ");
    affiche(liste);

    return 0;
}
