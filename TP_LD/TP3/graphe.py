# Fonctions pour les opérations de base sur les graphes

def existe_arete(graphe, i, j):
    return j in graphe[i]

def nombre_aretes(graphe):
    return sum(len(voisins) for voisins in graphe) // 2

def liste_voisins(graphe, sommet):
    return graphe[sommet]

def est_chemin(graphe, sommets):
    return all(sommets[i+1] in graphe[sommets[i]] for i in range(len(sommets)-1))

# Fonctions pour coder des problèmes spécifiques pour un solveur SAT

def trois_color_sat(graphe):
    clauses = []
    # ... [Insérez ici le code pour générer les clauses SAT] ...
    return clauses

def dominating_set_sat(graphe, k):
    clauses = []
    # ... [Insérez ici le code pour générer les clauses SAT] ...
    return clauses

def hamiltonien_sat(graphe):
    clauses = []
    # ... [Insérez ici le code pour générer les clauses SAT] ...
    return clauses

# Fonction pour résoudre le problème 2-SAT, potentiellement en utilisant une bibliothèque externe

def resoudre_2sat(clauses):
    # ... [Insérez ici le code pour résoudre 2-SAT] ...
    pass

# Exemple d'utilisation

if __name__ == "__main__":
    # Exemple de graphe représenté comme une liste d'adjacence
    graphe_exemple = [
        [1, 2],  # les voisins du sommet 0
        [0, 2],  # les voisins du sommet 1
        [0, 1]   # les voisins du sommet 2
    ]

    # Test des fonctions de base
    print("Il y a une arête entre 0 et 1:", existe_arete(graphe_exemple, 0, 1))
    print("Nombre d'arêtes dans le graphe:", nombre_aretes(graphe_exemple))
    print("Voisins du sommet 0:", liste_voisins(graphe_exemple, 0))
    print("Est-ce un chemin valide:", est_chemin(graphe_exemple, [0, 1, 2]))

    # Pour les fonctions SAT, vous devrez les intégrer avec votre solveur SAT spécifique.
    # Les fonctions ci-dessus génèrent des clauses, mais l'envoi de ces clauses à un solveur
    # et l'interprétation des résultats est une étape supplémentaire qui dépend de votre environnement.
