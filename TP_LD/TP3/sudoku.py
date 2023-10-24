from pycryptosat import Solver

# Fonctions de base pour la linéarisation et la délinéarisation
def linearisation(i, j, k):
    return 81*i + 9*j + k + 1

def delinearisation(index):
    index -= 1
    i, index = divmod(index, 81)
    j, k = divmod(index, 9)
    return i, j, k

# Génération de clauses pour différentes contraintes
def au_moins_un_nombre_par_case():
    clauses = []
    for i in range(9):
        for j in range(9):
            clauses.append([linearisation(i, j, k) for k in range(9)])
    return clauses

def au_plus_un_nombre_par_case():
    clauses = []
    for i in range(9):
        for j in range(9):
            for x in range(9):
                for y in range(x+1, 9):
                    clauses.append([-linearisation(i, j, x), -linearisation(i, j, y)])
    return clauses

def contraintes_lignes():
    clauses = []
    for k in range(9):
        for i in range(9):
            for j in range(9):
                for l in range(j+1, 9):
                    clauses.append([-linearisation(i, j, k), -linearisation(i, l, k)])
    return clauses

def contraintes_colonnes():
    clauses = []
    for k in range(9):
        for j in range(9):
            for i in range(9):
                for l in range(i+1, 9):
                    clauses.append([-linearisation(i, j, k), -linearisation(l, j, k)])
    return clauses

def contraintes_blocs():
    clauses = []
    for k in range(9):
        for a in range(3):
            for b in range(3):
                for u in range(3):
                    for v in range(3):
                        for w in range(u, 3):
                            for x in range(3):
                                if u == w and v >= x:
                                    continue
                                i1 = 3*a + u
                                j1 = 3*b + v
                                i2 = 3*a + w
                                j2 = 3*b + x
                                clauses.append([-linearisation(i1, j1, k), -linearisation(i2, j2, k)])
    return clauses

def conditions_initiales(grille):
    clauses = []
    for i in range(9):
        for j in range(9):
            cellule = grille[i][j]
            if cellule:
                clauses.append([linearisation(i, j, cellule-1)])
    return clauses

# Fonction principale pour résoudre le Sudoku
def resoudre_sudoku(grille):
    solver = Solver()

    # Ajouter toutes les clauses au solveur
    clauses = (
        au_moins_un_nombre_par_case()
        + au_plus_un_nombre_par_case()
        + contraintes_lignes()
        + contraintes_colonnes()
        + contraintes_blocs()
        + conditions_initiales(grille)
    )
    for clause in clauses:
        solver.add_clause(clause)

    # Résoudre le Sudoku
    solution = solver.solve()
    solution_valide = solution[1] if solution[0] else None

    # Si une solution est trouvée, construire la grille de Sudoku résolue
    if solution_valide:
        grille_resolue = []
        for i in range(9):
            ligne = []
            for j in range(9):
                for k in range(9):
                    if solution_valide[linearisation(i, j, k)-1]:
                        ligne.append(k+1)
                        break
            grille_resolue.append(ligne)
        return grille_resolue
    else:
        return None  # Aucune solution trouvée

# Exemple d'utilisation avec une grille de Sudoku
if __name__ == "__main__":
    # Grille de Sudoku à résoudre, avec des zéros représentant des cases vides
    grille_sudoku = [
        [5, 3, 0, 0, 7, 0, 0, 0, 0],
        [6, 0, 0, 1, 9, 5, 0, 0, 0],
        [0, 9, 8, 0, 0, 0, 0, 6, 0],
        [8, 0, 0, 0, 6, 0, 0, 0, 3],
        [4, 0, 0, 8, 0, 3, 0, 0, 1],
        [7, 0, 0, 0, 2, 0, 0, 0, 6],
        [0, 6, 0, 0, 0, 0, 2, 8, 0],
        [0, 0, 0, 4, 1, 9, 0, 0, 5],
        [0, 0, 0, 0, 8, 0, 0, 7, 9]
    ]

    solution = resoudre_sudoku(grille_sudoku)
    if solution:
        print("Sudoku résolu :")
        for ligne in solution:
            print(ligne)
    else:
        print("Pas de solution trouvée.")
