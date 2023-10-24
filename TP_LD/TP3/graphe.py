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
    n = len(graphe)  # Nombre de sommets
    # Chaque sommet a au moins une couleur
    for i in range(n):
        clauses.append([3*i+1, 3*i+2, 3*i+3])
    # Un sommet ne peut pas avoir plus d'une couleur
    for i in range(n):
        clauses.append([-3*i-1, -3*i-2])
        clauses.append([-3*i-1, -3*i-3])
        clauses.append([-3*i-2, -3*i-3])
    # Les sommets adjacents ne peuvent pas avoir la même couleur
    for i in range(n):
        for j in graphe[i]:
            for k in range(1, 4):  # Pour chaque couleur
                clauses.append([-3*i-k, -3*j-k])
    return clauses

def dominating_set_sat(graphe, k):
    clauses = []
    n = len(graphe)
    # Au moins un sommet dans le dominating set pour chaque voisinage
    for i in range(n):
        clause = []
        for j in range(k):
            clause.append(i * k + j + 1)  # Variable représentant si le sommet i est dans le set j
        clauses.append(clause)

    # Pas plus de k sommets dans le dominating set
    for i in range(n):
        for j in range(k):
            for l in range(j+1, k):
                clauses.append([-(i * k + j + 1), -(i * k + l + 1)])
    return clauses

def hamiltonien_sat(graphe):
    n = len(graphe)
    clauses = []

    # Chaque sommet doit apparaître dans le chemin
    for i in range(1, n + 1):
        clauses.append([i + n * j for j in range(n)])

    # Un sommet ne peut apparaître qu'une seule fois dans le chemin
    for i in range(1, n + 1):
        for j in range(n):
            for k in range(j + 1, n):
                clauses.append([-(i + n * j), -(i + n * k)])

    # Chaque position dans le chemin doit être occupée
    for j in range(n):
        clauses.append([i + n * j for i in range(1, n + 1)])

    # Pas plus d'un sommet par position dans le chemin
    for j in range(n):
        for i in range(1, n + 1):
            for k in range(i + 1, n + 1):
                clauses.append([-(i + n * j), -(k + n * j)])

    # Les sommets non adjacents ne peuvent pas être consécutifs dans le chemin
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            if i != j and j not in graphe[i - 1]:  # Si i et j ne sont pas adjacents
                for k in range(n - 1):
                    clauses.append([-(i + n * k), -(j + n * (k + 1))])

    return clauses

# Fonction pour résoudre le problème 2-SAT, potentiellement en utilisant une bibliothèque externe

def resoudre_2sat(clauses):
    def dfs(v):
        low[v] = index[v] = len(stack)
        stack.append(v)
        on_stack[v] = True

        for w in adj[v]:
            if index[w] == -1:
                dfs(w)
                low[v] = min(low[v], low[w])
            elif on_stack[w]:
                low[v] = min(low[v], index[w])

        if low[v] == index[v]:
            component = set()
            while stack[-1] != v:
                component.add(stack[-1])
                on_stack[stack.pop()] = False
            component.add(stack[-1])
            on_stack[stack.pop()] = False
            components.append(component)

    # Construire un graphe des implications
    adj = [[] for _ in range(2 * len(clauses))]
    for clause in clauses:
        a, b = clause
        adj[-a].append(b)
        adj[-b].append(a)

    # Initialiser les structures pour Tarjan's
    index = [-1] * len(adj)
    low = [0] * len(adj)
    on_stack = [False] * len(adj)
    stack = []
    components = []

    # Trouver les composantes fortement connexes
    for v in range(len(adj)):
        if index[v] == -1:
            dfs(v)

    # Vérifier si une variable et sa négation sont dans la même composante
    for component in components:
        for var in component:
            if -var in component:
                return None  # Insoluble

    # Si nous arrivons ici, le problème est soluble.
    # La fonction pourrait être étendue pour construire une solution.
    return True

# Exemple d'utilisation

if __name__ == "__main__":
    # Exemple de graphe représenté comme une liste d'adjacence.
    # Ce graphe est non orienté et contient des cycles.
    graphe_exemple = [
        [1, 2, 4],  # les voisins du sommet 0
        [0, 3, 4],  # les voisins du sommet 1
        [0, 4, 5],  # les voisins du sommet 2
        [1, 6],  # les voisins du sommet 3
        [0, 1, 2, 6],  # les voisins du sommet 4
        [2, 7, 8],  # les voisins du sommet 5
        [3, 4, 7],  # les voisins du sommet 6
        [5, 6, 8],  # les voisins du sommet 7
        [5, 7]  # les voisins du sommet 8
    ]

    # Le graphe ci-dessus peut être visualisé comme suit :
    #
    #     0---1---3
    #    /|    \   \
    #   / |     \   6
    #  2  |      \ / \
    #   \ |       4   7
    #    \|      /     \
    #     5-----8-------5
    #
    # C'est un graphe non orienté avec 9 sommets et plusieurs arêtes entre eux.

    # Test des fonctions de base
    print("Il y a une arête entre 0 et 1:", existe_arete(graphe_exemple, 0, 1))
    print("Nombre d'arêtes dans le graphe:", nombre_aretes(graphe_exemple))
    print("Voisins du sommet 0:", liste_voisins(graphe_exemple, 0))
    print("Est-ce un chemin valide:", est_chemin(graphe_exemple, [0, 1, 2]))

    # Pour les fonctions SAT, vous devrez les intégrer avec votre solveur SAT spécifique.
    # Les fonctions ci-dessus génèrent des clauses, mais l'envoi de ces clauses à un solveur
    # et l'interprétation des résultats est une étape supplémentaire qui dépend de votre environnement.
